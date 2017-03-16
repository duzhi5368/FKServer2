// SpecialManager.h
// 
//////////////////////////////////////////////////////

#ifndef __SPECIALMANAGER_H__
#define __SPECIALMANAGER_H__

#include "Type.h"
#include "ObjSingleManager.h"

class Obj_Special;
class SpecialManager :	public ObjSingleManager
{
public :
	SpecialManager( VOID );
	virtual ~SpecialManager( VOID );

	virtual BOOL HeartBeat( UINT uTime = 0 );

	Obj_Special *GetSpecial( ObjID_t idObj );

public :
	BOOL RemoveAllSpecial( VOID );
};


#endif // __SPECIALMANAGER_H__
