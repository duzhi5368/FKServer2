#include "stdafx.h"
// ObjManager.cpp

#include "Obj.h"
#include "ObjManager.h"

ObjID_t ObjManager::m_aidBegin[OBJ_ID_TYPE_NUMBERS] = { 0, 15000 };

ObjManager::ObjManager( VOID )
{
__ENTER_FUNCTION

	memset( m_appObjs, 0, sizeof( m_appObjs ) );
	memset( m_aCount, 0, sizeof( m_aCount ) );
	memset( m_aPosition, 0, sizeof( m_aPosition ) );
	memset( m_aLength, 0, sizeof( m_aLength ) );

__LEAVE_FUNCTION
}

ObjManager::~ObjManager( VOID )
{
__ENTER_FUNCTION

	UINT i;
	for ( i = 0; i < OBJ_ID_TYPE_NUMBERS; i++ )
	{
		Assert( m_appObjs[i] == NULL && "ObjManager::~ObjManager obj list not free" );
	}

__LEAVE_FUNCTION
}

BOOL ObjManager::Init( const _OBJMAGAGER_INIT *pInit )
{
__ENTER_FUNCTION

	if ( pInit == NULL )
	{
		Assert( pInit != NULL && "ObjManager::Init" );
		return FALSE;
	}

	UINT i;
	for ( i = 0; i < OBJ_ID_TYPE_NUMBERS; i++ )
	{
		Assert( m_appObjs[i] == NULL && "ObjManager::Init obj list not free" );
	}

	for ( i = 0; i < OBJ_ID_TYPE_NUMBERS; i++ )
	{
		if ( pInit->m_aInitCount[i] > 0 )
		{
			m_appObjs[i] = new Obj* [pInit->m_aInitCount[i]];
			memset( m_appObjs[i], 0, sizeof( Obj* ) * pInit->m_aInitCount[i] );
		}
		m_aLength[i] = pInit->m_aInitCount[i];
	}
	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

VOID ObjManager::Term( VOID )
{
__ENTER_FUNCTION

	UINT i;
	for ( i = 0; i < OBJ_ID_TYPE_NUMBERS; i++ )
	{
		if ( m_appObjs[i] != NULL )
		{
			delete [] m_appObjs[i];
		}
	}
	memset( m_appObjs, 0, sizeof( m_appObjs ) );
	memset( m_aCount, 0, sizeof( m_aCount ) );
	memset( m_aPosition, 0, sizeof( m_aPosition ) );
	memset( m_aLength, 0, sizeof( m_aLength ) );

__LEAVE_FUNCTION
}

BOOL ObjManager::AddObj( Obj *pObj, ENUM_OBJ_ID_TYPE eIDType/* = OBJ_ID_TYPE_NORMAL*/ )
{
__ENTER_FUNCTION
	if ( eIDType <= OBJ_ID_TYPE_INVALID || eIDType >= OBJ_ID_TYPE_NUMBERS )
	{
		Assert( eIDType > OBJ_ID_TYPE_INVALID && eIDType < OBJ_ID_TYPE_NUMBERS && "ObjManager::AddObj invalid obj id type" );
		return FALSE;
	}

	if ( m_aCount[eIDType] == m_aLength[eIDType] )
	{
		Assert( m_aCount[eIDType] < m_aLength[eIDType] && "ObjManager::AddObj id list is full, must resize" );
		UINT uMaxLength;
		if ( eIDType < OBJ_ID_TYPE_NUMBERS - 1 )
		{
			uMaxLength = m_aidBegin[eIDType+1] - m_aidBegin[eIDType];
		}
		else
		{
			uMaxLength = (ObjID_t)(INVALID_ID) - 1 - m_aidBegin[eIDType];
		}

		if ( m_aLength[eIDType] <uMaxLength )
		{
			// resize
			UINT uNewSize = m_aLength[eIDType] * 2;
			uNewSize = min(uMaxLength,uNewSize );
			BOOL bResult = Resize( eIDType,uNewSize );
			if ( !bResult )
			{
				Assert( FALSE && "ObjManager::AddObj call resize failed" );
				return FALSE;
			}
		}
		else
		{
			Assert( m_aLength[eIDType] <uMaxLength && "ObjManager::AddObj can not resize" );
			return FALSE;
		}
	}

	ObjID_t idCur;
	UINT uLength;
	uLength = m_aLength[eIDType];
	while ( TRUE )
	{
		idCur = (ObjID_t)(m_aPosition[eIDType]);
		if( m_appObjs[eIDType][idCur] == NULL )
		{
			m_appObjs[eIDType][idCur] = pObj;

			pObj->SetID( idCur + m_aidBegin[eIDType] );

			m_aCount[eIDType]++;
			return TRUE;
		}

		m_aPosition[eIDType]++;

		if( m_aPosition[eIDType] ==uLength )
			m_aPosition[eIDType] = 0;
	}

	return FALSE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL ObjManager::RemoveObj( ObjID_t idObj )
{
__ENTER_FUNCTION

	if ( idObj == INVALID_ID )
	{
		Assert( idObj != INVALID_ID && "ObjManager::RemoveObj invalid obj id" );
		return FALSE;
	}

	ENUM_OBJ_ID_TYPE eIDType = GetObjIDType( idObj );
	if ( idObj > m_aidBegin[eIDType] + (ObjID_t)(m_aLength[eIDType]) )
	{
		Assert( idObj > m_aidBegin[eIDType] + (ObjID_t)(m_aLength[eIDType]) && "ObjManager::RemoveObj not find object" );
		return FALSE;
	}

	Obj *pRemoveObj = m_appObjs[eIDType][idObj - m_aidBegin[eIDType]];
	if ( pRemoveObj == NULL )
	{
		Assert( pRemoveObj != NULL && "ObjManager::RemoveObj not find object" );
		return FALSE;
	}

	if ( pRemoveObj->GetID() != idObj )
	{
		Assert( pRemoveObj->GetID() != idObj && "ObjManager::RemoveObj can not remove" );
		return FALSE;
	}
	pRemoveObj->SetID( INVALID_ID );

	m_appObjs[eIDType][idObj-m_aidBegin[eIDType]] = NULL;

	m_aCount[eIDType]--;
	return TRUE;

__LEAVE_FUNCTION
	return FALSE;
}

BOOL ObjManager::Resize( ENUM_OBJ_ID_TYPE eIDType, UINT uNewSize )
{
__ENTER_FUNCTION

	Obj **ppSave = m_appObjs[eIDType];
	m_appObjs[eIDType] = new Obj* [uNewSize];
	if ( ppSave != NULL )
	{
		memcpy( m_appObjs[eIDType], ppSave, sizeof( Obj* ) * m_aLength[eIDType] );
		delete [] ppSave;
		ppSave = NULL;
	}
	memset( &(m_appObjs[eIDType][m_aLength[eIDType]]), 0, sizeof( Obj* ) * (uNewSize - m_aLength[eIDType]) );
	m_aLength[eIDType] =uNewSize;

	delete [] ppSave;
	ppSave = NULL;

	return TRUE;

__LEAVE_FUNCTION
	return FALSE;
}
