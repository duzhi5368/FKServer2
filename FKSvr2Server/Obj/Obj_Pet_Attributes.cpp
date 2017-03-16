#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////
// 文件名：Obj_Pet_Attributes.cpp
// 功能说明：角色层属性
//
// 修改记录：
//	将所有的m_pdbPet转换成Pet的主人Human->pPetDB，Pet本身不拥有任务DB数据
//  修改所有关于m_pdbPet的数据
//
///////////////////////////////////////////////////////////////////////////////
#include "Type.h"
#include "Scene.h"
#include "GameDefine.h"
#include "GameDefine2.h"
#include "Obj_Pet.h"
#include "GameTable.h"
#include "Obj_Human.h"
#include "ItemOperator.h"


VOID Obj_Pet::IncrementExp(INT nExp)
{
__ENTER_FUNCTION
	// 如果已经到达等级上限则直接返回
	if (GetLevel() == PET_LEVEL_NUM)
	{
		return ;
	}

	// 判断是否 >= 该级别升级的经验
	INT nCurExp = GetExp();
	nCurExp += nExp;
	INT nNeedExp = g_PetLevelUpTbl.GetExp(GetLevel());

	while (nCurExp > nNeedExp)
	{
		LevelUp();
		nCurExp -= nNeedExp;
		if (GetLevel() == PET_LEVEL_NUM)
		{
			nCurExp = 0;
			break;
		}
	}
	SetExp(nCurExp);
	
__LEAVE_FUNCTION
}
////////////////////////////////////////////////////////////////////////////////
//角色属性部分
//StrikePoint
INT	Obj_Pet::GetMaxStrikePoint(VOID)
{
	return 0;
}
//Rage
INT Obj_Pet::GetMaxRage(VOID)
{
	return 0;
}
//Attr1: Str
INT	Obj_Pet::GetStr(VOID)
{
	if(TRUE==GetStrDirtyFlag())
	{
		INT nValue=GetBaseStr()+GetStrRefix();
		
		SetIntAttr(CharIntAttrs_T::ATTR_STR, nValue);
		ClearStrDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_STR);
}

INT	Obj_Pet::GetBaseStr(VOID)
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_BaseAttrLevel1.Get(CATTR_LEVEL1_STR);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetLvl1Attr(CATTR_LEVEL1_STR);
}

VOID 	Obj_Pet::SetBaseStr(INT const nValue)
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_BaseAttrLevel1.Set(CATTR_LEVEL1_STR, nValue);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);	

	g_ItemOperator.SetLvl1Attr(pPetContainer, m_nIndex, CATTR_LEVEL1_STR, nValue);
	MarkStrDirtyFlag();
	MarkAttackPhysicsDirtyFlag();
}

//Attr1: Spr
INT	Obj_Pet::GetSpr(VOID)
{
	if(TRUE==GetSprDirtyFlag())
	{
		INT nValue=GetBaseSpr()+GetSprRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_SPR, nValue);
		ClearSprDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_SPR);
}

INT	Obj_Pet::GetBaseSpr(VOID)
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_BaseAttrLevel1.Get(CATTR_LEVEL1_SPR);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetLvl1Attr(CATTR_LEVEL1_SPR);

}

VOID	Obj_Pet::SetBaseSpr(INT const nValue)
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_BaseAttrLevel1.Set(CATTR_LEVEL1_SPR, nValue);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);	

	g_ItemOperator.SetLvl1Attr(pPetContainer, m_nIndex, CATTR_LEVEL1_SPR, nValue);
	MarkSprDirtyFlag();
	MarkAttackMagicDirtyFlag();
}

//Attr1: Con
INT	Obj_Pet::GetCon(VOID)
{
	
	if(TRUE==GetConDirtyFlag())
	{
		INT nValue=GetBaseCon()+GetConRefix();
		
		SetIntAttr(CharIntAttrs_T::ATTR_CON, nValue);
		ClearConDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_CON);
}

INT	Obj_Pet::GetBaseCon(VOID)
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_BaseAttrLevel1.Get(CATTR_LEVEL1_CON);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetLvl1Attr(CATTR_LEVEL1_CON);
}

VOID	Obj_Pet::SetBaseCon(INT const nValue)
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_BaseAttrLevel1.Set(CATTR_LEVEL1_CON, nValue);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);	

	g_ItemOperator.SetLvl1Attr(pPetContainer, m_nIndex, CATTR_LEVEL1_CON, nValue);
	MarkConDirtyFlag();
	MarkMaxHPDirtyFlag();
	MarkHPRegenerateDirtyFlag();
	MarkDefencePhysicsDirtyFlag();
}

//Attr1: Int
INT	Obj_Pet::GetInt(VOID)
{
	
	if(TRUE==GetIntDirtyFlag())
	{
		INT nValue=GetBaseInt()+GetIntRefix();
		
		SetIntAttr(CharIntAttrs_T::ATTR_INT, nValue);
		ClearIntDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_INT);
}

INT	Obj_Pet::GetBaseInt(VOID)
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_BaseAttrLevel1.Get(CATTR_LEVEL1_INT);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetLvl1Attr(CATTR_LEVEL1_INT);
}

VOID Obj_Pet::SetBaseInt(INT const nValue)
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_BaseAttrLevel1.Set(CATTR_LEVEL1_INT, nValue);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);	

	g_ItemOperator.SetLvl1Attr(pPetContainer, m_nIndex, CATTR_LEVEL1_INT, nValue);
	MarkIntDirtyFlag();
	MarkMaxMPDirtyFlag();
	MarkMPRegenerateDirtyFlag();
	MarkDefenceMagicDirtyFlag();
}

//Attr1: Dex
INT	Obj_Pet::GetDex(VOID)
{
	if(TRUE==GetDexDirtyFlag())
	{
		INT nValue=GetBaseDex()+GetDexRefix();
		
		SetIntAttr(CharIntAttrs_T::ATTR_DEX, nValue);
		ClearDexDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_DEX);
}

INT	Obj_Pet::GetBaseDex(VOID)
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_BaseAttrLevel1.Get(CATTR_LEVEL1_DEX);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX);
}

VOID	Obj_Pet::SetBaseDex(INT const nValue)
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_BaseAttrLevel1.Set(CATTR_LEVEL1_DEX, nValue);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);	

	g_ItemOperator.SetLvl1Attr(pPetContainer, m_nIndex, CATTR_LEVEL1_DEX, nValue);

	MarkDexDirtyFlag();
	MarkHitDirtyFlag();
	MarkMissDirtyFlag();
	MarkCriticalDirtyFlag();
}

//HP
INT	Obj_Pet::GetMaxHP(VOID) 
{
	if(TRUE==GetMaxHPDirtyFlag())
	{
		INT nValue=GetBaseMaxHP()+GetMaxHPRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_MAX_HP, nValue);
		ClearMaxHPDirtyFlag();
		if(GetHP()>nValue) SetHP(nValue);
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MAX_HP);
}
 
INT Obj_Pet::GetBaseMaxHP(VOID)
{
	//HP	初始HP+体质*体质对HP影响系数*体资+等级*等级对HP影响系数*成长
	FLOAT fGrowRate = 0.f;
	INT nAttribParam = 0;
	INT nLevel = GetLevel();
	INT nBaseParam = g_TableInit.m_PetConfig.m_BaseHP;
	FLOAT fAttribRate = g_TableInit.m_PetConfig.m_Con_HP_Pram;
	FLOAT fLevelRate = g_TableInit.m_PetConfig.m_Level_HP_Pram;

	if (!GetConstCreator())	
	{
		fGrowRate = m_PetDB.m_fGrowRate;
		nAttribParam = m_PetDB.m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_CON];
	}
	else
	{
		ItemContainer* pPetContainer = GetCreator()->GetPetContain();
		Item* pPetItem = pPetContainer->GetItem(m_nIndex);
		Assert(pPetItem);

		fGrowRate = pPetItem->GetGrowRate();
		nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_CON);
	}

	return (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
}

VOID 	Obj_Pet::SetBaseMaxHP(INT const nHp)
{
}

INT	Obj_Pet::GetHPRegenerate(VOID) 
{
	if(TRUE==GetHPRegenerateDirtyFlag())
	{
		INT nValue=GetBaseHPRegenerate()+GetHPRegenerateRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_HP_REGENERATE, nValue);
		ClearHPRegenerateDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_HP_REGENERATE);
}
 
INT Obj_Pet::GetBaseHPRegenerate(VOID)
{
	return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_RESTOREHP) ;	
}

VOID 	Obj_Pet::SetBaseHPRegenerate(INT const nValue)
{// forbiden modify this attribute
}

//MP
INT Obj_Pet::GetMaxMP(VOID)
{
	if(TRUE==GetMaxMPDirtyFlag())
	{
		INT nValue=GetBaseMaxMP()+GetMaxMPRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_MAX_MP, nValue);
		ClearMaxMPDirtyFlag();
		if(GetMP()>nValue) SetMP(nValue);
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MAX_MP);
}

INT Obj_Pet::GetBaseMaxMP(VOID)
{
	return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_MAXMP) ;	
}

VOID 	Obj_Pet::SetBaseMaxMp(INT const nMp)
{// forbiden modify this attribute
}

INT	Obj_Pet::GetMPRegenerate(VOID)
{
	if(TRUE==GetMPRegenerateDirtyFlag())
	{
		INT nValue=GetBaseMPRegenerate()+GetMPRegenerateRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_MP_REGENERATE, nValue);
		ClearMPRegenerateDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MP_REGENERATE);
}
 
INT Obj_Pet::GetBaseMPRegenerate(VOID)
{
	return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_RESTOREMP) ;	
}

VOID 	Obj_Pet::SetBaseMPRegenerate(INT const nValue)
{// forbiden modify this attribute
}

//CampID
const _CAMP_DATA *Obj_Pet::GetCampData(VOID)
{
	Obj_Character *pOwner = GetOwner();
	if (!pOwner)	
	{
		return Obj_Character::GetCampData();
	}
	return pOwner->GetCampData();
}

const _CAMP_DATA *Obj_Pet::GetBaseCampData(VOID)const
{
	if (!GetConstCreator())	
	{
		return &(m_PetDB.m_CampData);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetCampData();
}

VOID Obj_Pet::SetBaseCampData(const _CAMP_DATA *pCampData)
{
	if (!GetConstCreator())	
	{
		m_PetDB.m_CampData = *pCampData;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	g_ItemOperator.SetCampData(pPetContainer, m_nIndex, pCampData);

}

INT Obj_Pet::GetCampID(VOID)
{
	if(TRUE==GetCampIDDirtyFlag())
	{
		INT nValue=GetCampIDRefix();
		if(INVALID_ID==nValue)
		{
			nValue=GetBaseCampID();
		}
		SetIntAttr(CharIntAttrs_T::ATTR_CAMP, nValue);
		ClearCampIDDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_CAMP);
}

INT Obj_Pet::GetBaseCampID(VOID) const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_CampData.m_nCampID;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetCampData()->m_nCampID;
}

VOID	Obj_Pet::SetBaseCampID(INT const nID)
{ // forbiden modify this attribute , only allow to modify Campid Refix,
}

//modelID
INT Obj_Pet::GetModelID(VOID)
{
	if(TRUE==GetModelIDDirtyFlag())
	{
		INT nValue=GetModelIDRefix();
		if(INVALID_ID==nValue)
		{
			nValue=GetBaseModelID();
		}
		SetIntAttr(CharIntAttrs_T::ATTR_MODEL_ID, nValue);
		ClearModelIDDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MODEL_ID);
}

INT Obj_Pet::GetBaseModelID(VOID) const
{
	return INVALID_ID;
}

VOID	Obj_Pet::SetBaseModelID(INT const nID)
{ // forbiden modify this attribute
}

// Alive flag, wraped in ObjCharacter
// In Combat flag, wraped in ObjCharacter
// Can move flag, wraped in ObjCharacter
// Can Action flag, wraped in ObjCharacter
// Unbreakable flag, wraped in ObjCharacter
// Attr2: Move Speed, wraped in ObjCharacter
FLOAT	Obj_Pet::GetMoveSpeed(VOID)
{
	if(TRUE==GetMoveSpeedDirtyFlag())
	{
		INT nValue=GetBaseMoveSpeed()+GetMoveSpeedRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_MOVE_SPEED, nValue);
		ClearMoveSpeedDirtyFlag();
	}

	FLOAT fMoveSpeed  = GetIntAttr(CharIntAttrs_T::ATTR_MOVE_SPEED) / 10.f;//LM修改
	ENUM_MOVE_MODE eMoveMode = GetMoveMode();
	if(eMoveMode == MOVE_MODE_HOBBLE)
	{//变成基础速度的50%
		fMoveSpeed = fMoveSpeed*0.5f;
	}
	else if(eMoveMode == MOVE_MODE_RUN)
	{//变成基础速度的150%
		fMoveSpeed = fMoveSpeed*1.5f;
	}
	else if (eMoveMode == MOVE_MODE_SPRINT)
	{//变成基础速度的500%
		fMoveSpeed = fMoveSpeed*5.0f;
	}

	return fMoveSpeed;

}

INT	Obj_Pet::GetBaseMoveSpeed(VOID)
{
	return g_MonsterAttrExTbl.Get(GetDataID(), CATTR_LEVEL2_SPEED);	
}

VOID	Obj_Pet::SetBaseMoveSpeed(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack Speed
INT Obj_Pet::GetAttackSpeed(VOID)
{
	if(TRUE==GetAttackSpeedDirtyFlag())
	{
		INT nValue=GetBaseAttackSpeed()+GetAttackSpeedRefix();
		if(400<nValue)
		{
			nValue = 400;
		}
		if(25>=nValue)
		{
			nValue = 25;
		}		
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_SPEED, nValue);
		ClearAttackSpeedDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_SPEED);
}

INT Obj_Pet::GetBaseAttackSpeed(VOID)
{
	return BASE_ATTACK_SPEED;
	//return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_ATTACKSPEED) ;	
}

VOID	Obj_Pet::SetBaseAttackSpeed(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Miss
INT Obj_Pet::GetMiss(VOID)
{
	if(TRUE==GetMissDirtyFlag())
	{
		INT nValue=GetBaseMiss()+GetMissRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_MISS, nValue);
		ClearMissDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MISS);
}

INT Obj_Pet::GetBaseMiss(VOID)
{
	//闪避	初始物攻+敏捷*敏捷对闪避影响系数*敏资+等级*等级对闪避影响系数*成长
	FLOAT fGrowRate = 0.f;
	INT nLevel = GetLevel();

	if (!GetConstCreator())	
	{
		return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_MISS) ;
	}
	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	fGrowRate = pPetItem->GetGrowRate();;

	INT nBaseParam = g_TableInit.m_PetConfig.m_BasePhyAttack;
	FLOAT fAttribRate = g_TableInit.m_PetConfig.m_Dex_Miss_Pram;
	FLOAT fLevelRate = g_TableInit.m_PetConfig.m_Level_Miss_Pram;
	INT nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX);

	return (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);

}

VOID	Obj_Pet::SetBaseMiss(INT const nValue)
{// forbiden modify this attribute
}

// Attr2 Hit
INT Obj_Pet::GetHit(VOID)
{
	if(TRUE==GetHitDirtyFlag())
	{
		INT nValue=GetBaseHit()+GetHitRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_HIT, nValue);
		ClearHitDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_HIT);
}

INT Obj_Pet::GetBaseHit(VOID)
{
	//命中	初始物攻+敏捷*敏捷对命中影响系数*敏资+等级*等级对命中影响系数*成长
	FLOAT fGrowRate = 0.f;
	INT nLevel = GetLevel();

	if (!GetConstCreator())	
	{
		return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_HIT) ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	fGrowRate = pPetItem->GetGrowRate();;
	INT nBaseParam = g_TableInit.m_PetConfig.m_BasePhyAttack;
	FLOAT fAttribRate = g_TableInit.m_PetConfig.m_Dex_Hit_Pram;
	FLOAT fLevelRate = g_TableInit.m_PetConfig.m_Level_Hit_Pram;
	INT nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX);

	return (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
}

VOID	Obj_Pet::SetBaseHit(INT const nValue)
{// forbiden modify this attribute
}

// Attr2 Critical
INT Obj_Pet::GetCritical(VOID)
{
	if(TRUE==GetCriticalDirtyFlag())
	{
		INT nValue=GetBaseCritical()+GetCriticalRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_CRITICAL, nValue);
		ClearCriticalDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_CRITICAL);
}

INT Obj_Pet::GetBaseCritical(VOID)
{
	//会心	初始物攻+敏捷*敏捷对会心影响系数*敏资+等级*等级对会心影响系数*成长
	FLOAT fGrowRate = 0.f;
	INT nLevel = GetLevel();

	if (!GetConstCreator())	
	{
		return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_CRITRATE);
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	fGrowRate = pPetItem->GetGrowRate();;

	INT nBaseParam = g_TableInit.m_PetConfig.m_BaseCritical;
	FLOAT fAttribRate = g_TableInit.m_PetConfig.m_Dex_Critical_Pram;
	FLOAT fLevelRate = g_TableInit.m_PetConfig.m_Level_Critical_Pram;
	INT nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX);

	return (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
}

VOID	Obj_Pet::SetBaseCritical(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power physics
INT Obj_Pet::GetAttackPhysics(VOID)
{
	if(TRUE==GetAttackPhysicsDirtyFlag())
	{
		INT nValue=GetBaseAttackPhysics()+GetAttackPhysicsRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_PHY, nValue);
		ClearAttackPhysicsDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_PHY);
}

INT Obj_Pet::GetBaseAttackPhysics(VOID)
{
	//物攻	初始物攻+力量*力量对物攻影响系数*力资+等级*等级对物攻影响系数*成长
	FLOAT fGrowRate = 0.f;
	INT nLevel = GetLevel();
	if (!GetConstCreator())	
	{
		return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_ATTACKRATE_P) ;	
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	fGrowRate = pPetItem->GetGrowRate();;

	INT nBaseParam = g_TableInit.m_PetConfig.m_BasePhyAttack;
	FLOAT fAttribRate = g_TableInit.m_PetConfig.m_Str_PhyAttack_Pram;
	FLOAT fLevelRate = g_TableInit.m_PetConfig.m_Level_PhyAttack_Pram;
	INT nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_STR);

	return (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
}

VOID	Obj_Pet::SetBaseAttackPhysics(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Pet::GetDefencePhysics(VOID)
{
	if(TRUE==GetDefencePhysicsDirtyFlag())
	{
		INT nValue=GetBaseDefencePhysics()+GetDefencePhysicsRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_PHY, nValue);
		ClearDefencePhysicsDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_PHY);
}

INT Obj_Pet::GetBaseDefencePhysics(VOID)
{
	//物防	初始物攻+体质*体质对物防影响系数*体资+等级*等级对物防影响系数*成长
	FLOAT fGrowRate = 0.f;
	INT nLevel = GetLevel();
	if (!GetConstCreator())	
	{
		return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_DEFENCE_P) ;	
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	fGrowRate = pPetItem->GetGrowRate();;

	INT nBaseParam = g_TableInit.m_PetConfig.m_BasePhyDefence;
	FLOAT fAttribRate = g_TableInit.m_PetConfig.m_Con_PhyDefence_Pram;
	FLOAT fLevelRate = g_TableInit.m_PetConfig.m_Level_PhyDefence_Pram;
	INT nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_CON);
	
	return (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);

	
}

VOID	Obj_Pet::SetBaseDefencePhysics(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Magic
INT Obj_Pet::GetAttackMagic(VOID)
{
	if(TRUE==GetAttackMagicDirtyFlag())
	{
		INT nValue=GetBaseAttackMagic()+GetAttackMagicRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_MAGIC, nValue);
		ClearAttackMagicDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_MAGIC);
}

INT Obj_Pet::GetBaseAttackMagic(VOID)
{
	//魔攻	初始魔攻+灵气*灵气对魔攻攻影响系数*灵资+等级*等级对魔攻影响系数*成长
	FLOAT fGrowRate = 0.f;
	INT nLevel = GetLevel();
	if (!GetConstCreator())
	{
		 return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_ATTACKRATE_M) ;	
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	fGrowRate = pPetItem->GetGrowRate();;

	INT nBaseParam = g_TableInit.m_PetConfig.m_BaseMgcAttack;
	FLOAT fAttribRate = g_TableInit.m_PetConfig.m_Spr_MgcAttack_Pram;
	FLOAT fLevelRate = g_TableInit.m_PetConfig.m_Level_MgcAttack_Pram;
	INT nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_SPR);
	
	return (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
}

VOID	Obj_Pet::SetBaseAttackMagic(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Pet::GetDefenceMagic(VOID)
{
	if(TRUE==GetDefenceMagicDirtyFlag())
	{
		INT nValue=GetBaseDefenceMagic()+GetDefenceMagicRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_MAGIC, nValue);
		ClearDefenceMagicDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_MAGIC);
}

INT Obj_Pet::GetBaseDefenceMagic(VOID)
{
	//魔防	初始魔防+定力*定力对魔防影响系数*定资+等级*等级对魔防影响系数*成长
	FLOAT fGrowRate = 0.f;
	INT nLevel = GetLevel();

	if (!GetConstCreator())
	{
		return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_DEFENCE_M) ;	
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	fGrowRate = pPetItem->GetGrowRate();;

	INT nBaseParam = g_TableInit.m_PetConfig.m_BaseMgcDefence;
	FLOAT fAttribRate = g_TableInit.m_PetConfig.m_Int_MgcDefence_Pram;
	FLOAT fLevelRate = g_TableInit.m_PetConfig.m_Level_MgcDefence_Pram;
	INT nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_INT);
	
	return (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
}

VOID	Obj_Pet::SetBaseDefenceMagic(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Cold
INT Obj_Pet::GetAttackCold(VOID)
{
	if(TRUE==GetAttackColdDirtyFlag())
	{
		INT nValue=GetBaseAttackCold()+GetAttackColdRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_COLD, nValue);
		ClearAttackColdDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_COLD);
}

INT Obj_Pet::GetBaseAttackCold(VOID)
{
	return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_ATTACKCOLD) ;	
}

VOID	Obj_Pet::SetBaseAttackCold(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Pet::GetDefenceCold(VOID)
{
	if(TRUE==GetResistColdDirtyFlag())
	{
		INT nValue=GetBaseDefenceCold()+GetDefenceColdRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_COLD, nValue);
		ClearResistColdDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_COLD);
}

INT Obj_Pet::GetBaseDefenceCold(VOID)
{
	return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_DEFENCECOLD) ;	
}

VOID	Obj_Pet::SetBaseDefenceCold(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Fire
INT Obj_Pet::GetAttackFire(VOID)
{
	if(TRUE==GetAttackFireDirtyFlag())
	{
		INT nValue=GetBaseAttackFire()+GetAttackFireRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_FIRE, nValue);
		ClearAttackFireDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_FIRE);
}

INT Obj_Pet::GetBaseAttackFire(VOID)
{
	return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_ATTACKFIRE) ;	
}

VOID	Obj_Pet::SetBaseAttackFire(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Pet::GetDefenceFire(VOID)
{
	if(TRUE==GetResistFireDirtyFlag())
	{
		INT nValue=GetBaseDefenceFire()+GetDefenceFireRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_FIRE, nValue);
		ClearResistFireDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_FIRE);
}

INT Obj_Pet::GetBaseDefenceFire(VOID)
{
	return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_ATTACKFIRE) ;	
}

VOID	Obj_Pet::SetBaseDefenceFire(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Light
INT Obj_Pet::GetAttackLight(VOID)
{
	if(TRUE==GetAttackLightDirtyFlag())
	{
		INT nValue=GetBaseAttackLight()+GetAttackLightRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_LIGHT, nValue);
		ClearAttackLightDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_LIGHT);
}

INT Obj_Pet::GetBaseAttackLight(VOID)
{
	return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_ATTACKLIGHT) ;	
}

VOID	Obj_Pet::SetBaseAttackLight(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Pet::GetDefenceLight(VOID)
{
	if(TRUE==GetResistLightDirtyFlag())
	{
		INT nValue=GetBaseDefenceLight()+GetDefenceLightRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_LIGHT, nValue);
		ClearResistLightDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_LIGHT);
}

INT Obj_Pet::GetBaseDefenceLight(VOID)
{
	return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_DEFENCELIGHT) ;	
}

VOID	Obj_Pet::SetBaseDefenceLight(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Poison
INT Obj_Pet::GetAttackPoison(VOID)
{
	if(TRUE==GetAttackPoisonDirtyFlag())
	{
		INT nValue=GetBaseAttackPoison()+GetAttackPoisonRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_POISON, nValue);
		ClearAttackPoisonDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_POISON);
}

INT Obj_Pet::GetBaseAttackPoison(VOID)
{
	return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_ATTACKPOISON) ;	
}

VOID	Obj_Pet::SetBaseAttackPoison(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Pet::GetDefencePoison(VOID)
{
	if(TRUE==GetResistPoisonDirtyFlag())
	{
		INT nValue=GetBaseDefencePoison()+GetDefencePoisonRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_POISON, nValue);
		ClearResistPoisonDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_POISON);
}
INT Obj_Pet::GetBaseDefencePoison(VOID)
{
	return g_MonsterAttrExTbl.Get( GetDataID(), CATTR_LEVEL2_DEFENCEPOISON) ;	
}

VOID	Obj_Pet::SetBaseDefencePoison(INT const nValue)
{// forbiden modify this attribute
}

// Attr2 Reduce Slower Duration
INT Obj_Pet::GetReduceSlowerDuration(VOID)
{
	return GetReduceSlowerDurationRefix();
}

// Attr2 Reduce Weaken Duration
INT Obj_Pet::GetReduceWeakenDuration(VOID)
{
	return GetReduceWeakenDurationRefix();
}

// Attr2 Reduce Faint Duration
INT Obj_Pet::GetReduceFaintDuration(VOID)
{
	return GetReduceFaintDurationRefix();
}

// Attr2 Reduce Poisoned Duration
INT Obj_Pet::GetReducePoisonedDuration(VOID)
{
	return GetReducePoisonedDurationRefix();
}

// Attr2 VisionRange
INT Obj_Pet::GetVisionRange(VOID)
{
	if(TRUE==GetVisionRangeDirtyFlag())
	{
		INT nValue=GetBaseVisionRange()+GetVisionRangeRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_VISION_RANGE, nValue);
		ClearVisionRangeDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_VISION_RANGE);
}

INT Obj_Pet::GetBaseVisionRange(VOID)
{
	//return g_MonsterAttrExTbl.Get(UINT MonsterType, UINT AttrEx);
	return 16;
}

VOID	Obj_Pet::SetBaseVisionRange(INT const nValue)
{// forbiden modify this attribute
}


