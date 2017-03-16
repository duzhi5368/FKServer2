#include "stdafx.h"

#include "CharacterManager.h"
#include "Scene.h"




CharacterManager::CharacterManager( )
{
__ENTER_FUNCTION

	m_pObjIDs = new ObjID_t[DEFAULT_OBJ_COUNT] ;
	Assert( m_pObjIDs ) ;
	for( UINT i=0; i<DEFAULT_OBJ_COUNT; i++ )
	{
		m_pObjIDs[i] = INVALID_ID ;
	}
	m_TotalSize = DEFAULT_OBJ_COUNT ;
	m_Count = 0 ;
	m_pScene = NULL ;

__LEAVE_FUNCTION
}

CharacterManager::~CharacterManager( )
{
__ENTER_FUNCTION

	SAFE_DELETE_ARRAY( m_pObjIDs ) ;
	m_TotalSize = 0 ;
	m_Count = 0 ;
	m_pScene = NULL ;

__LEAVE_FUNCTION
}

VOID CharacterManager::CleanUp( )
{
__ENTER_FUNCTION

	m_Count = 0 ;
	for( UINT i=0; i<m_TotalSize ; i++ )
	{
		m_pObjIDs[i] = INVALID_ID ;
	}
	m_pScene = NULL ;

__LEAVE_FUNCTION
}

BOOL CharacterManager::AddCharacter( Obj_Character* pCharacter )
{
__ENTER_FUNCTION

	m_pObjIDs[m_Count] = pCharacter->GetID() ;
	pCharacter->SetCharacterID( m_Count ) ;
	m_Count ++ ;
	if( m_Count >= m_TotalSize )
	{
		BOOL ret = Resize( DEFAULT_OBJ_COUNT ) ;
		if( !ret )
		{
			Assert( FALSE ) ;
			return FALSE ;
		}
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL CharacterManager::DelCharacter( ObjID_t ObjID )
{
__ENTER_FUNCTION

	Obj_Character* pCharacter = (Obj_Character*)(GetScene()->GetObjManager()->GetObj(ObjID)) ;
	Assert( pCharacter ) ;
	
	UINT index = (UINT)(pCharacter->GetCharacterID()) ;
	Assert( index<m_Count ) ;

	Assert( m_Count > 0 ) ;
	Assert( m_pObjIDs[index]==ObjID ) ;

	m_pObjIDs[index] = m_pObjIDs[m_Count-1] ;
	pCharacter->SetCharacterID( INVALID_ID ) ;

	Obj_Character* pNewCharacter = (Obj_Character*)(GetScene()->GetObjManager()->GetObj(m_pObjIDs[index])) ;
	Assert( pNewCharacter ) ;

	pNewCharacter->SetCharacterID( index ) ;

	m_Count -- ;
	Assert( m_Count>=0 ) ;


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

Obj_Character* CharacterManager::GetCharacter( ObjID_t ObjID )
{
__ENTER_FUNCTION

	Obj_Character* pCharacter = (Obj_Character*)(GetScene()->GetObjManager()->GetObj(ObjID)) ;
	Assert( pCharacter ) ;

	return pCharacter ;

__LEAVE_FUNCTION

	return NULL ;
}

BOOL CharacterManager::KillCharacter( Obj_Character* pCharacter )
{
__ENTER_FUNCTION

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL CharacterManager::HeartBeat( UINT uTime )
{
__ENTER_FUNCTION

	UINT nCount = GetCount() ;
	for( UINT i=0; i<nCount; i++ )
	{
		Obj_Character* pCharacter = (Obj_Character*)(GetScene()->GetObjManager()->GetObj(m_pObjIDs[i])) ;
		if( pCharacter==NULL )
			continue ;

		if ( pCharacter->IsActiveObj() )
			pCharacter->HeartBeat(uTime ) ;
		else
			pCharacter->HeartBeat_OutZone(uTime ) ;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL CharacterManager::BroadCast( Packet* pPacket, Obj_Character* pOwn )
{
__ENTER_FUNCTION

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL CharacterManager::Resize( UINT iSize )
{
__ENTER_FUNCTION

	ObjID_t* pNew = new ObjID_t[m_TotalSize+iSize] ;
	if( !pNew )
	{
		Assert( pNew ) ;
		return FALSE ;
	}

	memcpy( pNew, m_pObjIDs, sizeof(ObjID_t)*m_TotalSize ) ;
	m_TotalSize = m_TotalSize+iSize ;

	SAFE_DELETE_ARRAY( m_pObjIDs ) ;

	m_pObjIDs = pNew ;


	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}





