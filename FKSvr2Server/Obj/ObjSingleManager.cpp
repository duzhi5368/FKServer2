#include "stdafx.h"
// ObjSingleManager.cpp

#include "Obj.h"

#include "ObjSingleManager.h"
#include "Log.h"

ObjSingleManager::ObjSingleManager( VOID )
{
__ENTER_FUNCTION

	m_papObjs					= NULL;
	m_uCount					= 0;
	m_uLength					= 0;
	m_uLogicInterval			= 0;
	m_uCurrentLogicInterval	= 0;

	m_pScene		= NULL;
	//m_LogicTimer

 __LEAVE_FUNCTION
}

ObjSingleManager::~ObjSingleManager( VOID )
{
__ENTER_FUNCTION

	Term() ;

	Assert( m_papObjs == NULL && "ObjSingleManager::~ObjSingleManager m_papObjs not free" );

__LEAVE_FUNCTION
}

BOOL ObjSingleManager::Init( const _OBJSINGLEMANAGER_INIT *pInit )
{
__ENTER_FUNCTION

	Assert( m_papObjs == NULL && "ObjSingleManager::Init m_papObjs not free" );

	if ( pInit == NULL )
	{
		Assert( pInit != NULL && "ObjSingleManager::Init" );
		return FALSE;
	}

	if ( pInit->m_uLength == 0 )
	{
		Assert( pInit->m_uLength > 0 && "ObjSingleManager::Init" );
		return FALSE;
	}

	if ( pInit->m_pScene == NULL )
	{
		Assert( pInit->m_pScene != NULL && "ObjSingleManager::Init" );
		return FALSE;
	}

	m_uCount		= 0;
	m_uLength		= pInit->m_uLength;
	m_papObjs = new Obj* [m_uLength];
	memset( m_papObjs, 0, sizeof( Obj* ) * m_uLength );

	m_uLogicInterval			= pInit->m_uLogicInterval;
	m_uCurrentLogicInterval	= pInit->m_uLogicInterval;

	m_pScene		= pInit->m_pScene;
	m_LogicTimer.BeginTimer( pInit->m_uLogicInterval, pInit->m_uCurrentTime );

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

VOID ObjSingleManager::Term( VOID )
{
__ENTER_FUNCTION

	if ( m_papObjs )
	{
		delete [] m_papObjs;
		m_papObjs = NULL;
	}
	m_uCount					= 0;
	m_uLength					= 0;

	m_uLogicInterval			= 0;
	m_uCurrentLogicInterval	= 0;

	m_pScene					= NULL;
	m_LogicTimer.CleanUp();

__LEAVE_FUNCTION
}

VOID ObjSingleManager::Reset( )
{
__ENTER_FUNCTION

	m_uCount					= 0;
	memset( m_papObjs, 0, sizeof( Obj* ) * m_uLength );

__LEAVE_FUNCTION
}

VOID ObjSingleManager::SetLoadFactor( FLOAT fFactor )
{
__ENTER_FUNCTION

	m_uCurrentLogicInterval = (UINT)((FLOAT)(m_uLogicInterval) * fFactor);
	m_LogicTimer.SetTermTime( m_uCurrentLogicInterval );

__LEAVE_FUNCTION
}

BOOL ObjSingleManager::HeartBeat( UINT uTime/* = 0*/ )
{
__ENTER_FUNCTION

	if( !m_LogicTimer.CountingTimer(uTime ) )
		return TRUE;

	UINT i;
	BOOL bResult;
	for ( i = 0; i < m_uCount; i++ )
	{
		if ( m_papObjs[i] != NULL )
		{
			_MY_TRY
			{
				if ( m_papObjs[i]->IsActiveObj() )
				{
					bResult = m_papObjs[i]->HeartBeat(uTime );
				}
				else
				{
					bResult = m_papObjs[i]->HeartBeat_OutZone(uTime );
				}
			}
			_MY_CATCH
			{
				SaveCodeLog( ) ;
			}
		}
	}
	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL ObjSingleManager::Add( Obj *pObj )
{
__ENTER_FUNCTION

	if ( pObj == NULL )
	{
		Assert( pObj != NULL && "ObjSingleManager::Add" );
		return FALSE;
	}

	if ( m_uCount >= m_uLength )
	{
		UINT uNewSize;
		uNewSize = m_uLength * 2;
		BOOL bResult = Resize(uNewSize );
		if ( !bResult )
		{
			Assert( m_uCount < m_uLength && "ObjSingleManager::Add resize error" );
			return FALSE;
		}
	}

	m_papObjs[m_uCount] = pObj;
	pObj->SetSingleMgrIndex( m_uCount );
	m_uCount++;
	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL ObjSingleManager::Remove( Obj *pObj )
{
__ENTER_FUNCTION

	if ( pObj == NULL )
	{
		Assert( pObj != NULL && "ObjSingleManager::Remove" );
		return FALSE;
	}

	UINT uIndex = pObj->GetSingleMgrIndex( );
	if (uIndex >= m_uCount )
	{
		Assert(uIndex < m_uCount && "ObjSingleManager::Remove" );
		return FALSE;
	}

	m_uCount--;
	m_papObjs[m_uCount]->SetSingleMgrIndex(uIndex );
	m_papObjs[uIndex] = m_papObjs[m_uCount];
	m_papObjs[m_uCount] = NULL;

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}
//
//BOOL ObjSingleManager::KillObjSingle( ObjSingle* pObj )
//{
//__ENTER_FUNCTION
//
//	return TRUE;
//
//__LEAVE_FUNCTION
//
//	return FALSE;
//}
//
//BOOL ObjSingleManager::BroadCast( Packet* pPacket, ObjSingle* pOwn )
//{
//__ENTER_FUNCTION
//
//	return TRUE;
//
//__LEAVE_FUNCTION
//
//	return FALSE;
//}

BOOL ObjSingleManager::Resize( UINT uSize )
{
__ENTER_FUNCTION

	Obj **papSave = m_papObjs;
	m_papObjs = new Obj* [uSize];
	if ( papSave != NULL )
	{
		memcpy( m_papObjs, papSave, sizeof( Obj* ) * m_uCount );
	}
	memset( &(m_papObjs[m_uCount]), 0, sizeof( Obj* ) * (uSize - m_uCount) );
	m_uCount =uSize;

	delete [] papSave;
	papSave = NULL;
	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}
