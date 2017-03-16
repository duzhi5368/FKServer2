// PetPool.h
// 
//////////////////////////////////////////////////////

#ifndef __PETPOOL_H__
#define __PETPOOL_H__

#include "Type.h"
#include "ObjPool.h"
#include "Obj_Pet.h"

typedef ObjPool< Obj_Pet >	PetPool;

extern PetPool	*g_pPetPool;

#endif	// __PETPOOL_H__
