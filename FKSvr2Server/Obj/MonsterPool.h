

#ifndef __MONSTERPOOL_H__
#define __MONSTERPOOL_H__

#include "Type.h"
#include "ObjPool.h"
#include "Obj_Monster.h"

typedef ObjPool< Obj_Monster >	MonsterPool;

extern MonsterPool* g_pMonsterPool ;

#endif
