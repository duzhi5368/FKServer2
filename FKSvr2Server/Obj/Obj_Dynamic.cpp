#include "stdafx.h"
// Obj_Dynamic.cpp

#include "Obj_Dynamic.h"

Obj_Dynamic::Obj_Dynamic( )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

Obj_Dynamic::~Obj_Dynamic( )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

VOID Obj_Dynamic::CleanUp( )
{
__ENTER_FUNCTION

	Obj::CleanUp( );

__LEAVE_FUNCTION
}

BOOL Obj_Dynamic::Init( const _OBJ_INIT *pInit )
{
__ENTER_FUNCTION

	BOOL bResult = Obj::Init( pInit );
	if ( !bResult )
		return FALSE;

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL Obj_Dynamic::HeartBeat(UINT uTime)
{
__ENTER_FUNCTION
	return Obj::HeartBeat(uTime);
__LEAVE_FUNCTION
	return FALSE;
}

BOOL Obj_Dynamic::HeartBeat_OutZone(UINT uTime)
{
__ENTER_FUNCTION
	return Obj::HeartBeat_OutZone(uTime);
__LEAVE_FUNCTION
	return FALSE;
}