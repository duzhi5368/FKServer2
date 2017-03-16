// PetManager.h
// 
//////////////////////////////////////////////////////

#ifndef __PETMANAGER_H__
#define __PETMANAGER_H__

#include "Type.h"
#include "ObjSingleManager.h"

class Obj_Pet;
class PetManager : public ObjSingleManager
{
public:
	friend class Obj_Pet;

	PetManager( VOID );
	virtual ~PetManager( VOID );

	virtual BOOL HeartBeat( UINT uTime = 0 );

	Obj_Pet *GetPet( ObjID_t idObj );

	// 从文件Load宠物信息
	BOOL	LoadPet( const CHAR *pszFileName );
	// 删除所有Pet
	BOOL	RemoveAllPet( VOID );
	// 删除某个Pet
	BOOL	RemovePet( ObjID_t idObj );
	// 创建一个Pet
	BOOL	CreatePet( INT nDataID, WORLD_POS* pPos, ObjID_t& rPetID );
	//// 初始化一个Pet模型
	//BOOL	InitPet(INT idModel, ItemContainer& rPetContainer, INT index);
	// 生成一个捕捉后宠物的GUID
	BOOL	CreateGUIDOfPet(_PET_DB *pPetDB, ObjID_t idHuman, ObjID_t idPet);
	// 生成一个宠物的属性 --bNeedLevelFluctuate 是否需要等级浮动 --bReturnToChild 是否要进行还童
	BOOL	MakeCapturePetAttrib(_PET_DB *pPetDB, BOOL bNeedLevelFluctuate=TRUE, BOOL bReturnToChild=FALSE);
	// 通过DataID去付值一个PET DB
	BOOL	InitPetDB( _PET_DB *pPetDB, INT nDataID );

protected:
	// 生成宠物的性格类型
	VOID		CreateAITypeOfPet(_PET_DB& rPetDB);
	// 获得宠物类型
	VOID		CreateTypeOfPet(_PET_DB& rPetDB, BOOL bNeedLevelFluctuate, BOOL bReturnToChild);
	// 获得宠物属性点， idData为宠物的编号不是ObjID
    VOID		CreateRemainPointOfPet(_PET_DB& rPetDB);
	// 获得宠物技能，idData为宠物的编号不是ObjID
    VOID		CreateSkillOfPet(_PET_DB& rPetDB);
	// 获得宠物成长率，idData为宠物的编号不是ObjID
	VOID		CreateGrowRateOfPet(_PET_DB& rPetDB);
	// 获得宠物资质，idData为宠物的编号不是ObjID
	VOID		CreatePerceptionOfPet(_PET_DB& rPetDB);
	// 辅助function
	VOID		AddPetSkill(_PET_SKILL *paSkillList, INT& rSkillIndex);

};

#endif	// __PETMANAGER_H__
