// MonsterManager.h
// 
//////////////////////////////////////////////////////

#ifndef __MONSTERMANAGER_H__
#define __MONSTERMANAGER_H__

#include "Type.h"
#include "ObjSingleManager.h"

class Obj_Monster;
struct _MONSTER_INIT;
class MonsterManager : public ObjSingleManager
{
public:
	MonsterManager( VOID );
	virtual ~MonsterManager( VOID );

	Obj_Monster *GetMonster( ObjID_t idObj );

	virtual BOOL HeartBeat( UINT uTime = 0 );

	ObjID_t		FindMonsterByGUID( GUID_t guid ) ;

	BOOL InitMonsterData(_MONSTER_INIT *pInit, INT nDataID);

public:
	BOOL LoadMonster( const CHAR *pszFileName );
	BOOL RemoveAllMonster( VOID );
};

#endif	// __MONSTERMANAGER_H__
