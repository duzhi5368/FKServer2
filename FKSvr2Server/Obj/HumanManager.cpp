#include "stdafx.h"
// HumanManager.cpp

#include "Scene.h"
#include "ObjManager.h"
#include "Obj_Human.h"

#include "HumanManager.h"

HumanManager::HumanManager( VOID )
{
__ENTER_FUNCTION
__LEAVE_FUNCTION
}

HumanManager::~HumanManager( VOID )
{
__ENTER_FUNCTION
__LEAVE_FUNCTION
}

Obj_Human *HumanManager::GetHuman( ObjID_t idObj )
{
__ENTER_FUNCTION

	Obj_Human *pHuman = (Obj_Human*)(GetScene()->GetObjManager()->GetObj( idObj ));
	if ( pHuman == NULL )
	{
		return NULL;
	}

	if ( pHuman->GetObjType() != Obj::OBJ_TYPE_HUMAN )
	{
		Assert( (pHuman->GetObjType() == Obj::OBJ_TYPE_HUMAN) && "HumanManager::GetHuman" );
		return NULL;
	}
	return pHuman;

__LEAVE_FUNCTION

	return NULL ;
}

