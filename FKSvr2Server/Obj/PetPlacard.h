// PetPlacard.h
//
// 功能：宠物公告板
// 
///////////////////////////////////////////////////////

#ifndef __PETPLACARD_H__
#define __PETPLACARD_H__

#include "DB_Struct.h"
#include "GameStruct_Pet.h"

////////////////////////////////////////////////
// PetPlacard
////////////////////////////////////////////////
#define PET_PLACARD_ITEM_NUM	(256)
class PetPlacard
{
public:
	PetPlacard(VOID);
	~PetPlacard(VOID);

	BOOL Init(VOID);
	VOID CleanUp(VOID);

	BOOL AddItem(const _PET_PLACARD_ITEM *pItem);
	VOID RemoveItem(INT nIndex);

	INT GetIndexByHumanGUID(GUID_t guidHuman)const;

	const _PET_PLACARD_ITEM *GetValidItem(INT nIndex)const;
	const _PET_PLACARD_ITEM *FirstValidItem(INT *pnIndex)const;
	const _PET_PLACARD_ITEM *PrevValidItem(INT *pnIndex)const;
	const _PET_PLACARD_ITEM *NextValidItem(INT *pnIndex)const;

protected:
	// 待优化
	_PET_PLACARD_ITEM		m_aItems[PET_PLACARD_ITEM_NUM];
};

////////////////////////////////////////////////
// PetPlacardSystem
////////////////////////////////////////////////
class Obj_Human;
class PetPlacardSystem
{
public:
	PetPlacardSystem(VOID);
	~PetPlacardSystem(VOID);

	BOOL Init(VOID);
	VOID CleanUp(VOID);

	BOOL HeartBeat(UINT uTime);

	// 发布公告
	ORESULT IssuePlacard(Obj_Human *pIssuer, PET_GUID_t guidPet, const CHAR *pszMessage);

	// 取消公告
	VOID CancelPlacard(GUID_t guidHuman);

	const PetPlacard *GetPetPlacard(VOID)const
	{
		return &m_PetPlacard;
	}

protected:
	PetPlacard		m_PetPlacard;
};

#endif	// __PETPLACARD_H__
