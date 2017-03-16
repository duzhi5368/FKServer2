// PlatformPool.h

#ifndef __PLATFORMPOOL_H__
#define __PLATFORMPOOL_H__

#include "Type.h"
#include "ObjPool.h"
#include "Obj_Platform.h"

typedef ObjPool< Obj_Platform > PlatformPool;

extern PlatformPool* g_pPlatformPool;

#endif // __PLATFORMPOOL_H__
