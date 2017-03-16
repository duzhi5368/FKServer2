#include "stdafx.h"
// Obj_Platform.cpp

#include "Scene.h"
#include "GCNewPlatform.h"
#include "Obj_Platform.h"

VOID Obj_Platform::CleanUp()
{
	m_PlatformClass = 0;
	m_Script = (ScriptID_t)(0xFFFFFFFF);
}

BOOL Obj_Platform::Init( const _OBJ_INIT *pInit )
{
__ENTER_FUNCTION
	BOOL bResult = Obj_Static::Init( pInit );
	if ( !bResult )
		return FALSE;

	if ( pInit == NULL )
		return FALSE;

	const _OBJ_PLATFORM_INIT *pPlatformInit = (const _OBJ_PLATFORM_INIT*)pInit;

	SetPlatformClass(pPlatformInit->m_Class);
	m_type		= (BYTE)pPlatformInit->m_Type;
	m_Script	= pPlatformInit->m_Script;

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

Packet *Obj_Platform::CreateNewObjPacket( VOID )
{
__ENTER_FUNCTION

	if ( getScene() != NULL )
	{
		GCNewPlatform *pPacket = (GCNewPlatform*)(getScene()->m_pPacket_NewPlatform);
		pPacket->setObjID( GetID() );
		pPacket->setWorldPos( *(getWorldPos()) );
		pPacket->setDir( getDir() );
		pPacket->setType( GetPlatformType() );
		return pPacket;
	}
	else
	{
		Assert( getScene() != NULL && "Obj_Platform::CreateNewObjPacket" );
		return NULL;
	}

__LEAVE_FUNCTION

	return NULL;
}

VOID Obj_Platform::DestroyNewObjPacket( Packet *pPacket )
{
}
