// SpecialPool.h

#ifndef __SPECIALPOOL_H__
#define __SPECIALPOOL_H__

#include "Type.h"
#include "ObjPool.h"
#include "Obj_Special.h"

typedef ObjPool< Obj_Special > SpecialPool;

extern SpecialPool* g_pSpecialPool;

#endif // __SPECIALPOOL_H__
