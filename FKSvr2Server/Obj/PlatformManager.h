// PlatformManager.h
// 
//////////////////////////////////////////////////////

#ifndef __PLATFORMMANAGER_H__
#define __PLATFORMMANAGER_H__

#include "Type.h"
#include "ObjSingleManager.h"

class Obj_Platform;
class PlatformManager :	public ObjSingleManager
{
public :
	PlatformManager( VOID );
	virtual ~PlatformManager( VOID );

	Obj_Platform *GetPlatform( ObjID_t idObj );

public :
	BOOL LoadPlatform( const CHAR *pszFileName );
	BOOL RemoveAllPlatform( VOID );
};


#endif // __PLATFORMMANAGER_H__
