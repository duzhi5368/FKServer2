#include "stdafx.h"
// Obj_Static.cpp

#include "Obj_Static.h"

Obj_Static::Obj_Static( )
{
__ENTER_FUNCTION


__LEAVE_FUNCTION
}

Obj_Static::~Obj_Static( )
{
__ENTER_FUNCTION


__LEAVE_FUNCTION
}

BOOL Obj_Static::HeartBeat( UINT uTime/* = 0*/ )
{
__ENTER_FUNCTION
	return Obj::HeartBeat(uTime);
__LEAVE_FUNCTION
	return FALSE;
}
