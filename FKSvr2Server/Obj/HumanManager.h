// HumanManager.h
// 
//////////////////////////////////////////////////////

#ifndef __HUMANMANAGER_H__
#define __HUMANMANAGER_H__

#include "Type.h"
#include "ObjSingleManager.h"

class Obj_Human;
class HumanManager : public ObjSingleManager
{
public:
	HumanManager( VOID );
	virtual ~HumanManager( VOID );

	Obj_Human *GetHuman( ObjID_t idObj );
};

#endif	// __HUMANMANAGER_H__
