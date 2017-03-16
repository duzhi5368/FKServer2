#include "stdafx.h"
// SpecialManager.cpp

#include "Log.h"
#include "Scene.h"
#include "ObjManager.h"
#include "Obj_Special.h"
#include "SpecialPool.h"

#include "SpecialManager.h"

SpecialManager::SpecialManager( VOID )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

SpecialManager::~SpecialManager( VOID )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

Obj_Special *SpecialManager::GetSpecial( ObjID_t idObj )
{
__ENTER_FUNCTION

	Obj_Special *pSpecial = (Obj_Special*)(GetScene()->GetObjManager()->GetObj( idObj ));
	if ( pSpecial == NULL )
	{
		return NULL;
	}

	if ( pSpecial->GetObjType() != Obj::OBJ_TYPE_SPECIAL )
	{
		Assert( (pSpecial->GetObjType() == Obj::OBJ_TYPE_SPECIAL) && "SpecialManager::GetSpecial" );
		return NULL;
	}
	return pSpecial;
__LEAVE_FUNCTION
	return NULL ;
}

BOOL SpecialManager::HeartBeat( UINT uTime )
{
__ENTER_FUNCTION

	if( !m_LogicTimer.CountingTimer(uTime ) )
		return TRUE;

#define MAX_REMOVE_SIZE 1024
	INT aNeedRemoveSpecial[MAX_REMOVE_SIZE] ;
	memset( aNeedRemoveSpecial, 0, sizeof(INT)*MAX_REMOVE_SIZE ) ;

	INT nRemoveCount=0 ;

	INT i;
	for ( i = 0; i < (INT)m_uCount; i++ )
	{
		if ( m_papObjs[i] != NULL )
		{
			if ( m_papObjs[i]->IsActiveObj() )
			{
				 m_papObjs[i]->HeartBeat(uTime ) ;
			}
			else
			{
				BOOL bRet = m_papObjs[i]->HeartBeat_OutZone(uTime) ;
				if( bRet==FALSE )
				{
					aNeedRemoveSpecial[nRemoveCount++] = i ;
				}
			}
		}
	}

	for( i=nRemoveCount-1; i>=0; i-- )
	{
		Obj_Special* pSpecial = (Obj_Special*)(m_papObjs[aNeedRemoveSpecial[i]]) ;
		if( pSpecial != NULL )
		{
			pSpecial->SetActiveFlag(FALSE);
			pSpecial->CleanUp();
			GetScene()->DeleteObject( pSpecial ) ;
		}
	}

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL SpecialManager::RemoveAllSpecial( )
{
__ENTER_FUNCTION

	Scene *pScene;
	Obj_Special *pSpecial;
	UINT i,uCount,uMaxCount,uLength;

	pScene		= GetScene();
	uCount		= 0;
	uMaxCount	= GetCount();
	uLength	= GetLength();

	for ( i = 0; i <uLength; i++ )
	{
		pSpecial = (Obj_Special*)(GetObjByIndex( 0 ));
		if ( pSpecial != NULL )
		{
			pSpecial->SetActiveFlag( FALSE );
			pSpecial->CleanUp();
			pScene->DeleteObject( pSpecial );
			uCount++;
			if (uCount >=uMaxCount )
				break;
		}
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}
