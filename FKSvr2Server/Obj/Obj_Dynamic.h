// Obj_Dynamic.h
// 
/////////////////////////////////////////////////////////////////////////

#ifndef __OBJ_DYNAMIC_H__
#define __OBJ_DYNAMIC_H__

#include "Obj.h"

struct _OBJ_DYNAMIC_INIT : public _OBJ_INIT
{
	_OBJ_DYNAMIC_INIT( VOID )
	{
	}

	virtual VOID CleanUp( VOID )
	{
		_OBJ_INIT::CleanUp();
	}
};

class Obj_Dynamic : public Obj
{
public:
	Obj_Dynamic( );
	virtual ~Obj_Dynamic( );

	virtual ObjType		GetObjType( VOID )const{ return OBJ_TYPE_INVALID; }

	virtual VOID		CleanUp( );
	virtual BOOL		Init( const _OBJ_INIT *pInit );
	virtual BOOL		HeartBeat( UINT uTime=0 );
	virtual BOOL		HeartBeat_OutZone( UINT uTime=0 );
protected:
};

#endif	// __OBJ_DYNAMIC_H__
