#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////
// 文件名：Obj_Human_Attributes.cpp
// 功能说明：角色层属性
//
// 修改记录：
//
//
//
///////////////////////////////////////////////////////////////////////////////
#include "Type.h"
#include "GameDefine.h"
#include "GameDefine2.h"
#include "GameDefine_Attr.h"
#include "Obj_Human.h"
#include "LogicManager.h"
#include "GameTable.h"
#include "Config.h"
using namespace Combat_Module::Skill_Module;
using namespace MenPai_Module;
////////////////////////////////////////////////////////////////////////////////
//角色属性部分
//Strike point
INT	Obj_Human::GetMaxStrikePoint(VOID)
{
	if(TRUE==GetMaxStrikePointDirtyFlag())
	{
		INT nValue=GetBaseMaxStrikePoint()+GetMaxStrikePointRefix();
		nValue>MAX_STRIKE_POINT?nValue=MAX_STRIKE_POINT:NULL;
		SetIntAttr(CharIntAttrs_T::ATTR_MAX_STRIKE_POINT, nValue);
		ClearMaxStrikePointDirtyFlag();
		if(GetStrikePoint()>nValue) SetStrikePoint(nValue);
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MAX_STRIKE_POINT);	
}
INT	Obj_Human::GetMaxRage(VOID)
{
	if(TRUE==GetMaxRageDirtyFlag())
	{
		INT nValue=GetBaseMaxRage()+GetMaxRageRefix();
		nValue>MAX_RAGE?nValue=MAX_RAGE:NULL;
		SetIntAttr(CharIntAttrs_T::ATTR_MAX_RAGE, nValue);
		ClearMaxRageDirtyFlag();
		if(GetRage()>nValue) SetRage(nValue);
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MAX_RAGE);	
}
//Attr1: Str
INT	Obj_Human::GetStr(VOID)
{
	if(TRUE==GetStrDirtyFlag())
	{
		INT nItemValue = 0;
		_ITEM_EFFECT* pIE = ItemEffect(IATTRIBUTE_STR) ;
		Assert( pIE ) ;
		if( pIE->IsActive() )
		{
			nItemValue= pIE->m_Attr.m_Value ;
		}
		INT nValue=GetBaseStr()+GetStrRefix()+nItemValue;
		
		SetIntAttr(CharIntAttrs_T::ATTR_STR, nValue);
		ClearStrDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_STR);
}

INT	Obj_Human::GetBaseStr(VOID)
{
	return m_DB.GetDBAttrLvl1(CATTR_LEVEL1_STR);
}

VOID 	Obj_Human::SetBaseStr(INT const nValue)
{
	m_DB.SetDBAttrLvl1(CATTR_LEVEL1_STR, nValue);
	MarkStrDirtyFlag();
	MarkAttackPhysicsDirtyFlag();
}

//Attr1: Spr
INT	Obj_Human::GetSpr(VOID)
{
	if(TRUE==GetSprDirtyFlag())
	{
		INT nItemValue = 0;
		_ITEM_EFFECT* pIE = ItemEffect(IATTRIBUTE_SPR) ;
		Assert( pIE ) ;
		if( pIE->IsActive() )
		{
			nItemValue= pIE->m_Attr.m_Value ;
		}
		INT nValue=GetBaseSpr()+GetSprRefix()+nItemValue;
		SetIntAttr(CharIntAttrs_T::ATTR_SPR, nValue);
		ClearSprDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_SPR);
}

INT	Obj_Human::GetBaseSpr(VOID)
{
	return m_DB.GetDBAttrLvl1(CATTR_LEVEL1_SPR);
}

VOID	Obj_Human::SetBaseSpr(INT const nValue)
{
	m_DB.SetDBAttrLvl1(CATTR_LEVEL1_SPR, nValue);
	MarkSprDirtyFlag();
	MarkAttackMagicDirtyFlag();
}

//Attr1: Con
INT	Obj_Human::GetCon(VOID)
{
	if(TRUE==GetConDirtyFlag())
	{
		INT nItemValue = 0;
		_ITEM_EFFECT* pIE = ItemEffect(IATTRIBUTE_CON) ;
		Assert( pIE ) ;
		if( pIE->IsActive() )
		{
			nItemValue= pIE->m_Attr.m_Value ;
		}
		INT nValue=GetBaseCon()+GetConRefix()+nItemValue;
		
		SetIntAttr(CharIntAttrs_T::ATTR_CON, nValue);
		ClearConDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_CON);
}

INT	Obj_Human::GetBaseCon(VOID)
{
	return m_DB.GetDBAttrLvl1(CATTR_LEVEL1_CON);
}

VOID	Obj_Human::SetBaseCon(INT const nValue)
{
	m_DB.SetDBAttrLvl1(CATTR_LEVEL1_CON, nValue);
	MarkConDirtyFlag();
	MarkMaxHPDirtyFlag();
	MarkHPRegenerateDirtyFlag();
	MarkDefencePhysicsDirtyFlag();
}

//Attr1: Int
INT	Obj_Human::GetInt(VOID)
{
	if(TRUE==GetIntDirtyFlag())
	{
		INT nItemValue = 0;
		_ITEM_EFFECT* pIE = ItemEffect(IATTRIBUTE_INT) ;
		Assert( pIE ) ;
		if( pIE->IsActive() )
		{
			nItemValue= pIE->m_Attr.m_Value ;
		}
		INT nValue=GetBaseInt()+GetIntRefix()+nItemValue;
		
		SetIntAttr(CharIntAttrs_T::ATTR_INT, nValue);
		ClearIntDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_INT);
}

INT	Obj_Human::GetBaseInt(VOID)
{
	return m_DB.GetDBAttrLvl1(CATTR_LEVEL1_INT);
}

VOID	Obj_Human::SetBaseInt(INT const nValue)
{
	m_DB.SetDBAttrLvl1(CATTR_LEVEL1_INT, nValue);
	MarkIntDirtyFlag();
	MarkMaxMPDirtyFlag();
	MarkMPRegenerateDirtyFlag();
	MarkDefenceMagicDirtyFlag();
}

//Attr1: Dex
INT	Obj_Human::GetDex(VOID)
{
	if(TRUE==GetDexDirtyFlag())
	{
		INT nItemValue = 0;
		_ITEM_EFFECT* pIE = ItemEffect(IATTRIBUTE_DEX) ;
		Assert( pIE ) ;
		if( pIE->IsActive() )
		{
			nItemValue= pIE->m_Attr.m_Value ;
		}
		INT nValue=GetBaseDex()+GetDexRefix()+nItemValue;
		
		SetIntAttr(CharIntAttrs_T::ATTR_DEX, nValue);
		ClearDexDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_DEX);
}

INT	Obj_Human::GetBaseDex(VOID)
{
	return m_DB.GetDBAttrLvl1(CATTR_LEVEL1_DEX);
}

VOID	Obj_Human::SetBaseDex(INT const nValue)
{
	m_DB.SetDBAttrLvl1(CATTR_LEVEL1_DEX, nValue);
	MarkDexDirtyFlag();
	MarkHitDirtyFlag();
	MarkMissDirtyFlag();
	MarkCriticalDirtyFlag();
}

//HP
INT	Obj_Human::GetMaxHP(VOID) 
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetMaxHPDirtyFlag())
	{
		INT nBaseAttr=GetBaseMaxHP();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_POINT_MAXHP);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//装备对属性的百分比影响
		pIE = ItemEffect(IATTRIBUTE_RATE_MAXHP);
		Assert( pIE ) ;
		if( pIE->IsActive() )
		{
			nItemRateRefix = Float2Int((nBaseAttr*(pIE->m_Attr.m_Value))/100.0f);
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetMaxHPRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_MAX_HP, nValue);
		ClearMaxHPDirtyFlag();
		if(GetHP()>nValue)	SetHP(nValue);
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MAX_HP);
	__LEAVE_FUNCTION
	return 0;
}
 
INT Obj_Human::GetBaseMaxHP(VOID)
{
	//门派
	INT nMenPaiID = GetMenPai() ;
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPaiID);
	if(NULL == pMenPaiLogic)
	{
		AssertEx(FALSE,"[Obj_Human::GetBaseMaxHP]: Can't not find MenPai Logic!");
		return 0;
	}
	//初始属性值
	INT nInitAttr = pMenPaiLogic->GetInitMaxHP();
	//一级属性对该属性的影响系数
	INT nAttrLevel1Refix = pMenPaiLogic->GetMaxHPConRefix();
	//等级对该属性的影响系数
	INT nLevelRefix = pMenPaiLogic->GetMaxHPLevelRefix();

	//计算基础基础属性
	INT nBase = nInitAttr+GetCon()*nAttrLevel1Refix+GetLevel()*nLevelRefix;
	nBase=Float2Int((nBase)/100.0f); //表里面的数值都是乘了100的，计算后应该修正回去
	0<=nBase?NULL:nBase=0;	
	return nBase;
}

VOID 	Obj_Human::SetBaseMaxHP(INT const nHp)
{ // forbiden modify this attribute
}

INT	Obj_Human::GetHPRegenerate(VOID) 
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetMaxMPDirtyFlag())
	{
		INT nBaseAttr=GetBaseHPRegenerate();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_RESTORE_HP);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetHPRegenerateRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_HP_REGENERATE, nValue);
		ClearHPRegenerateDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_HP_REGENERATE);
	__LEAVE_FUNCTION
	return 0;
}
 
INT Obj_Human::GetBaseHPRegenerate(VOID)
{
	//门派
	INT nMenPaiID = GetMenPai() ;
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPaiID);
	if(NULL == pMenPaiLogic)
	{
		AssertEx(FALSE,"[Obj_Human::GetBaseHPRegenerate]: Can't not find MenPai Logic!");
		return 0;
	}
	//初始属性值
	INT nInitAttr = pMenPaiLogic->GetInitHPRegenerate();
	//一级属性对该属性的影响系数
	INT nAttrLevel1Refix = pMenPaiLogic->GetHPRegenerateConRefix();
	//等级对该属性的影响系数
	INT nLevelRefix = pMenPaiLogic->GetHPRegenerateLevelRefix();

	//计算基础基础属性
	INT nBase = nInitAttr+GetCon()*nAttrLevel1Refix+GetLevel()*nLevelRefix;
	nBase=Float2Int((nBase)/100.0f); //表里面的数值都是乘了100的，计算后应该修正回去
	0<=nBase?NULL:nBase=0;	
	return nBase;
}

VOID 	Obj_Human::SetBaseHPRegenerate(INT const nValue)
{// forbiden modify this attribute
}
//MP
INT Obj_Human::GetMaxMP(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetMaxMPDirtyFlag())
	{
		INT nBaseAttr=GetBaseMaxMP();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_POINT_MAXMP);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//装备对属性的百分比影响
		pIE = ItemEffect(IATTRIBUTE_RATE_MAXMP);
		Assert( pIE ) ;
		if( pIE->IsActive() )
		{
			nItemRateRefix = Float2Int((nBaseAttr*(pIE->m_Attr.m_Value))/100.0f);
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetMaxMPRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_MAX_MP, nValue);
		ClearMaxMPDirtyFlag();
		if(GetMP()>nValue) SetMP(nValue);
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MAX_MP);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseMaxMP(VOID)
{
	//门派
	INT nMenPaiID = GetMenPai() ;
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPaiID);
	if(NULL == pMenPaiLogic)
	{
		AssertEx(FALSE,"[Obj_Human::GetBaseMaxMP]: Can't not find MenPai Logic!");
		return 0;
	}
	//初始属性值
	INT nInitAttr = pMenPaiLogic->GetInitMaxMP();
	//一级属性对该属性的影响系数
	INT nAttrLevel1Refix = pMenPaiLogic->GetMaxMPIntRefix();
	//等级对该属性的影响系数
	INT nLevelRefix = pMenPaiLogic->GetMaxMPLevelRefix();

	//计算基础基础属性
	INT nBase = nInitAttr+GetInt()*nAttrLevel1Refix+GetLevel()*nLevelRefix;
	nBase=Float2Int((nBase)/100.0f); //表里面的数值都是乘了100的，计算后应该修正回去
	0<=nBase?NULL:nBase=0;	
	return nBase;
}

VOID 	Obj_Human::SetBaseMaxMp(INT const nMp)
{// forbiden modify this attribute
}

INT	Obj_Human::GetMPRegenerate(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetMPRegenerateDirtyFlag())
	{
		INT nBaseAttr=GetBaseMPRegenerate();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_RESTORE_MP);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetMPRegenerateRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_MP_REGENERATE, nValue);
		ClearMPRegenerateDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MP_REGENERATE);
	__LEAVE_FUNCTION
	return 0;
}
 
INT Obj_Human::GetBaseMPRegenerate(VOID)
{
	//门派
	INT nMenPaiID = GetMenPai() ;
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPaiID);
	if(NULL == pMenPaiLogic)
	{
		AssertEx(FALSE,"[Obj_Human::GetBaseMPRegenerate]: Can't not find MenPai Logic!");
		return 0;
	}
	//初始属性值
	INT nInitAttr = pMenPaiLogic->GetInitMPRegenerate();
	//一级属性对该属性的影响系数
	INT nAttrLevel1Refix = pMenPaiLogic->GetMPRegenerateIntRefix();
	//等级对该属性的影响系数
	INT nLevelRefix = pMenPaiLogic->GetMPRegenerateLevelRefix();

	//计算基础基础属性
	INT nBase = nInitAttr+GetInt()*nAttrLevel1Refix+GetLevel()*nLevelRefix;
	nBase=Float2Int((nBase)/100.0f); //表里面的数值都是乘了100的，计算后应该修正回去
	0<=nBase?NULL:nBase=0;	
	return nBase;
}

VOID 	Obj_Human::SetBaseMPRegenerate(INT const nValue)
{// forbiden modify this attribute
}

const _CAMP_DATA *Obj_Human::GetBaseCampData(VOID)const
{
	return m_DB.GetDBCampData();
}

VOID Obj_Human::SetBaseCampData(const _CAMP_DATA *pCampData)
{
	m_DB.SetDBCampData(pCampData);
}

//CampID
INT Obj_Human::GetCampID(VOID)
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

INT Obj_Human::GetBaseCampID(VOID) const
{
	HumanDB * pDB=(HumanDB *)&m_DB;
	return pDB->GetDBCampData()->m_nCampID;
}

VOID	Obj_Human::SetBaseCampID(INT const nID)
{
	_CAMP_DATA stCampData = *(m_DB.GetDBCampData());
	stCampData.m_nCampID = nID;
	m_DB.SetDBCampData(&stCampData);
	MarkCampIDDirtyFlag();
}

//modelID
INT Obj_Human::GetBaseModelID(VOID) const
{
	return INVALID_ID; //Need modify
}

VOID	Obj_Human::SetBaseModelID(INT const nID)
{ // forbiden modify this attribute
}

// Alive flag, wraped in ObjCharacter
// In Combat flag, wraped in ObjCharacter
// Can move flag, wraped in ObjCharacter
// Can Action flag, wraped in ObjCharacter
// Unbreakable flag, wraped in ObjCharacter
BOOL	Obj_Human::IsUnbreakable(VOID)
{
	return (this->Obj_Character::IsUnbreakable())||IsGod()||IsHaveChangeSceneFlag();
}

// Attr2: Move Speed, wraped in ObjCharacter
FLOAT	Obj_Human::GetMoveSpeed(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;

	if( __GetTeamFollowFlag() )
	{
		if ( GetTeamInfo()->IsLeader()==FALSE )
		{
			return __GetTeamFollowSpeed();
		}
	}

	if(TRUE==GetMoveSpeedDirtyFlag())
	{
		INT nBaseAttr=GetBaseMoveSpeed();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_SPEED_RATE);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetMoveSpeedRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_MOVE_SPEED, nValue);
		ClearMoveSpeedDirtyFlag();
	}

	FLOAT fMoveSpeed = GetIntAttr(CharIntAttrs_T::ATTR_MOVE_SPEED) / 10.f;		//LM修改
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
	__LEAVE_FUNCTION
	return 0;

}

INT	Obj_Human::GetBaseMoveSpeed(VOID)
{
	return g_Config.m_ConfigInfo.m_DefaultMoveSpeed;	
}

VOID	Obj_Human::SetBaseMoveSpeed(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack Speed
INT Obj_Human::GetAttackSpeed(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetAttackSpeedDirtyFlag())
	{
		INT nBaseAttr=GetBaseAttackSpeed();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_ATTACK_SPEED);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetAttackSpeedRefix();
		nValue = nBaseAttr-nImpactAndSkillRefix-nItemPointRefix;
		nValue<0?nValue=0:NULL;
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
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseAttackSpeed(VOID)
{
	//return g_Config.m_ConfigInfo.m_DefaultAttackSpeed;
	return BASE_ATTACK_SPEED; //use 100 as base cooldown and other actiontime refix;
}

VOID	Obj_Human::SetBaseAttackSpeed(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Miss
INT Obj_Human::GetMiss(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetMissDirtyFlag())
	{
		INT nBaseAttr=GetBaseMiss();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nItemBasePointRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备的基础点数影响
		pIE = ItemEffect(IATTRIBUTE_BASE_MISS);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemBasePointRefix= pIE->m_Attr.m_Value;
		}
		// passive Skill refix start
		//	...
		// passive skill refix end
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_MISS);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetMissRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix+nItemBasePointRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_MISS, nValue);
		ClearMissDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MISS);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseMiss(VOID)
{
	//门派
	INT nMenPaiID = GetMenPai() ;
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPaiID);
	if(NULL == pMenPaiLogic)
	{
		AssertEx(FALSE,"[Obj_Human::GetBaseMiss]: Can't not find MenPai Logic!");
		return 0;
	}
	//初始属性值
	INT nInitAttr = pMenPaiLogic->GetInitMiss();
	//一级属性对该属性的影响系数
	INT nAttrLevel1Refix = pMenPaiLogic->GetMissDexRefix();
	//等级对该属性的影响系数
	INT nLevelRefix = pMenPaiLogic->GetMissLevelRefix();

	//计算基础基础属性
	INT nBase = nInitAttr+GetDex()*nAttrLevel1Refix+GetLevel()*nLevelRefix;
	nBase=Float2Int((nBase)/100.0f); //表里面的数值都是乘了100的，计算后应该修正回去
	0<=nBase?NULL:nBase=0;	
	return nBase;
}

VOID	Obj_Human::SetBaseMiss(INT const nValue)
{// forbiden modify this attribute
}

// Attr2 Hit
INT Obj_Human::GetHit(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetHitDirtyFlag())
	{
		INT nBaseAttr=GetBaseHit();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_HIT);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetHitRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_HIT, nValue);
		ClearHitDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_HIT);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseHit(VOID)
{
	//门派
	INT nMenPaiID = GetMenPai();
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPaiID);
	if(NULL == pMenPaiLogic)
	{
		AssertEx(FALSE,"[Obj_Human::GetBaseHit]: Can't not find MenPai Logic!");
		return 0;
	}
	//初始属性值
	INT nInitAttr = pMenPaiLogic->GetInitHit();
	//一级属性对该属性的影响系数
	INT nAttrLevel1Refix = pMenPaiLogic->GetHitDexRefix();
	//等级对该属性的影响系数
	INT nLevelRefix = pMenPaiLogic->GetHitLevelRefix();

	//计算基础基础属性
	INT nBase = nInitAttr+GetDex()*nAttrLevel1Refix+GetLevel()*nLevelRefix;
	nBase=Float2Int((nBase)/100.0f); //表里面的数值都是乘了100的，计算后应该修正回去
	0<=nBase?NULL:nBase=0;	
	return nBase;
}

VOID	Obj_Human::SetBaseHit(INT const nValue)
{// forbiden modify this attribute
}

// Attr2 Critical
INT Obj_Human::GetCritical(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetCriticalDirtyFlag())
	{
		INT nBaseAttr=GetBaseCritical();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_2ATTACK_RATE);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetCriticalRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_CRITICAL, nValue);
		ClearCriticalDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_CRITICAL);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseCritical(VOID)
{
	//门派
	INT nMenPaiID = GetMenPai() ;
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPaiID);
	if(NULL == pMenPaiLogic)
	{
		AssertEx(FALSE,"[Obj_Human::GetBaseCritical]: Can't not find MenPai Logic!");
		return 0;
	}
	//初始属性值
	INT nInitAttr = pMenPaiLogic->GetInitCritical();
	//一级属性对该属性的影响系数
	INT nAttrLevel1Refix = pMenPaiLogic->GetCriticalDexRefix();
	//等级对该属性的影响系数
	INT nLevelRefix = pMenPaiLogic->GetCriticalLevelRefix();

	//计算基础基础属性
	INT nBase = nInitAttr+GetDex()*nAttrLevel1Refix+GetLevel()*nLevelRefix;
	nBase=Float2Int((nBase)/100.0f); //表里面的数值都是乘了100的，计算后应该修正回去
	0<=nBase?NULL:nBase=0;	
	return nBase;
}

VOID	Obj_Human::SetBaseCritical(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power physics
INT Obj_Human::GetAttackPhysics(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetAttackPhysicsDirtyFlag())
	{
		INT nBaseAttr=GetBaseAttackPhysics();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nItemBasePointRefix=0;
		INT nItemBaseRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备的基础点数影响
		pIE = ItemEffect(IATTRIBUTE_BASE_ATTACK_P);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemBasePointRefix= pIE->m_Attr.m_Value;
		}
		// passive Skill refix start
		//	...
		// passive skill refix end
		//////////////////////////////////////////////////////////////////////
		//装备的基础百分率影响
		pIE = ItemEffect(IATTRIBUTE_RATE_ATTACK_EP);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemBaseRateRefix= Float2Int((nItemBasePointRefix*(pIE->m_Attr.m_Value))/100.0f);
		}
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_ATTACK_P);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//装备对属性的百分比影响
		pIE = ItemEffect(IATTRIBUTE_RATE_ATTACK_P);
		Assert(pIE) ;
		if(pIE->IsActive())
		{
			nItemRateRefix = Float2Int((nBaseAttr*(pIE->m_Attr.m_Value))/100.0f);
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetAttackPhysicsRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix+nItemBasePointRefix+nItemBaseRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_PHY, nValue);
		ClearAttackPhysicsDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_PHY);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseAttackPhysics(VOID)
{
	//门派
	INT nMenPaiID = GetMenPai() ;
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPaiID);
	if(NULL == pMenPaiLogic)
	{
		AssertEx(FALSE,"[Obj_Human::GetBaseAttackPhysics]: Can't not find MenPai Logic!");
		return 0;
	}
	//初始属性值
	INT nInitAttr = pMenPaiLogic->GetInitAttackPhysics();
	//一级属性对该属性的影响系数
	INT nAttrLevel1Refix = pMenPaiLogic->GetAttackPhysicsStrRefix();
	//等级对该属性的影响系数
	INT nLevelRefix = pMenPaiLogic->GetAttackPhysicsLevelRefix();

	//计算基础基础属性
	INT nBase = nInitAttr+GetStr()*nAttrLevel1Refix+GetLevel()*nLevelRefix;
	nBase=Float2Int((nBase)/100.0f); //表里面的数值都是乘了100的，计算后应该修正回去
	0<=nBase?NULL:nBase=0;	
	return nBase;
}

VOID Obj_Human::SetBaseAttackPhysics(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Human::GetDefencePhysics(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetDefencePhysicsDirtyFlag())
	{
		INT nBaseAttr=GetBaseDefencePhysics();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nItemBasePointRefix=0;
		INT nItemBaseRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备的基础点数影响
		pIE = ItemEffect(IATTRIBUTE_BASE_DEFENCE_P);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemBasePointRefix= pIE->m_Attr.m_Value;
		}
		// passive Skill refix start
		//	...
		// passive skill refix end
		//////////////////////////////////////////////////////////////////////
		//装备的基础百分率影响
		pIE = ItemEffect(IATTRIBUTE_RATE_DEFENCE_EP);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemBaseRateRefix= Float2Int((nItemBasePointRefix*(pIE->m_Attr.m_Value))/100.0f);
		}
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_DEFENCE_P);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//装备对属性的百分比影响
		pIE = ItemEffect(IATTRIBUTE_RATE_DEFENCE_P);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemRateRefix = Float2Int((nBaseAttr*(pIE->m_Attr.m_Value))/100.0f);
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetDefencePhysicsRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix+nItemBasePointRefix+nItemBaseRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_PHY, nValue);
		ClearDefencePhysicsDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_PHY);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseDefencePhysics(VOID)
{
	//门派
	INT nMenPaiID = GetMenPai() ;
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPaiID);
	if(NULL == pMenPaiLogic)
	{
		AssertEx(FALSE,"[Obj_Human::GetBaseDefencePhysics]: Can't not find MenPai Logic!");
		return 0;
	}
	//初始属性值
	INT nInitAttr = pMenPaiLogic->GetInitDefencePhysics();
	//一级属性对该属性的影响系数
	INT nAttrLevel1Refix = pMenPaiLogic->GetDefencePhysicsConRefix();
	//等级对该属性的影响系数
	INT nLevelRefix = pMenPaiLogic->GetDefencePhysicsLevelRefix();

	//计算基础基础属性
	INT nBase = nInitAttr+GetCon()*nAttrLevel1Refix+GetLevel()*nLevelRefix;
	nBase=Float2Int((nBase)/100.0f); //表里面的数值都是乘了100的，计算后应该修正回去
	0<=nBase?NULL:nBase=0;
	return nBase;
}

VOID	Obj_Human::SetBaseDefencePhysics(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Magic
INT Obj_Human::GetAttackMagic(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetAttackMagicDirtyFlag())
	{
		INT nBaseAttr=GetBaseAttackMagic();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nItemBasePointRefix=0;
		INT nItemBaseRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备的基础点数影响
		pIE = ItemEffect(IATTRIBUTE_BASE_ATTACK_M);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemBasePointRefix= pIE->m_Attr.m_Value;
		}
		// passive Skill refix start
		//	...
		// passive skill refix end
		//////////////////////////////////////////////////////////////////////
		//装备的基础百分率影响
		pIE = ItemEffect(IATTRIBUTE_RATE_ATTACK_EM);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemBaseRateRefix= Float2Int((nItemBasePointRefix*(pIE->m_Attr.m_Value))/1000.0f);
		}
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_ATTACK_M);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//装备对属性的百分比影响
		pIE = ItemEffect(IATTRIBUTE_RATE_ATTACK_M);
		Assert(pIE) ;
		if(pIE->IsActive())
		{
			nItemRateRefix = Float2Int((nBaseAttr*(pIE->m_Attr.m_Value))/1000.0f);
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetAttackMagicRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix+nItemBasePointRefix+nItemBaseRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_MAGIC, nValue);
		ClearAttackMagicDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_MAGIC);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseAttackMagic(VOID)
{
	//门派
	INT nMenPaiID = GetMenPai() ;
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPaiID);
	if(NULL == pMenPaiLogic)
	{
		AssertEx(FALSE,"[Obj_Human::GetBaseAttackMagic]: Can't not find MenPai Logic!");
		return 0;
	}
	//初始属性值
	INT nInitAttr = pMenPaiLogic->GetInitAttackMagic();
	//一级属性对该属性的影响系数
	INT nAttrLevel1Refix = pMenPaiLogic->GetAttackMagicSprRefix();
	//等级对该属性的影响系数
	INT nLevelRefix = pMenPaiLogic->GetAttackMagicLevelRefix();

	//计算基础基础属性
	INT nBase = nInitAttr+GetSpr()*nAttrLevel1Refix+GetLevel()*nLevelRefix;
	nBase=Float2Int((nBase)/100); //表里面的数值都是乘了100的，计算后应该修正回去	
	0<=nBase?NULL:nBase=0;	
	return nBase;
}

VOID	Obj_Human::SetBaseAttackMagic(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Human::GetDefenceMagic(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetDefenceMagicDirtyFlag())
	{
		INT nBaseAttr=GetBaseDefenceMagic();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nItemBasePointRefix=0;
		INT nItemBaseRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备的基础点数影响
		pIE = ItemEffect(IATTRIBUTE_BASE_DEFENCE_M);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemBasePointRefix= pIE->m_Attr.m_Value;
		}
		// passive Skill refix start
		//	...
		// passive skill refix end
		//////////////////////////////////////////////////////////////////////
		//装备的基础百分率影响
		pIE = ItemEffect(IATTRIBUTE_RATE_DEFENCE_EM);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemBaseRateRefix= Float2Int((nItemBasePointRefix*(pIE->m_Attr.m_Value))/1000.0f);
		}
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_DEFENCE_M);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//装备对属性的百分比影响
		pIE = ItemEffect(IATTRIBUTE_RATE_DEFENCE_M);
		Assert(pIE);
		if(pIE->IsActive())
		{
			nItemRateRefix = Float2Int((nBaseAttr*(pIE->m_Attr.m_Value))/100.0f);
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetDefenceMagicRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix+nItemBasePointRefix+nItemBaseRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_MAGIC, nValue);
		ClearDefenceMagicDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_MAGIC);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseDefenceMagic(VOID)
{
	//门派
	INT nMenPaiID = GetMenPai() ;
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPaiID);
	if(NULL == pMenPaiLogic)
	{
		AssertEx(FALSE,"[Obj_Human::GetBaseDefenceMagic]: Can't not find MenPai Logic!");
		return 0;
	}
	//初始属性值
	INT nInitAttr = pMenPaiLogic->GetInitDefenceMagic();
	//一级属性对该属性的影响系数
	INT nAttrLevel1Refix = pMenPaiLogic->GetDefenceMagicIntRefix();
	//等级对该属性的影响系数
	INT nLevelRefix = pMenPaiLogic->GetDefenceMagicLevelRefix();

	//计算基础基础属性
	INT nBase = nInitAttr+GetInt()*nAttrLevel1Refix+GetLevel()*nLevelRefix;
	nBase=Float2Int((nBase)/100.0f); //表里面的数值都是乘了100的，计算后应该修正回去
	0<=nBase?NULL:nBase=0;	
	return nBase;
}

VOID	Obj_Human::SetBaseDefenceMagic(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Cold
INT Obj_Human::GetAttackCold(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetAttackColdDirtyFlag())
	{
		INT nBaseAttr=GetBaseAttackCold();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_COLD_ATTACK);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetAttackColdRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_COLD, nValue);
		ClearAttackColdDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_COLD);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseAttackCold(VOID)
{
	return 0;	
}

VOID	Obj_Human::SetBaseAttackCold(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Human::GetDefenceCold(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetResistColdDirtyFlag())
	{
		INT nBaseAttr=GetBaseDefenceCold();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_COLD_RESIST);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetDefenceColdRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_COLD, nValue);
		ClearResistColdDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_COLD);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseDefenceCold(VOID)
{
	return 0;	
}

VOID	Obj_Human::SetBaseDefenceCold(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Fire
INT Obj_Human::GetAttackFire(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetAttackFireDirtyFlag())
	{
		INT nBaseAttr=GetBaseAttackFire();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_FIRE_ATTACK);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetAttackFireRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_FIRE, nValue);
		ClearAttackFireDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_FIRE);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseAttackFire(VOID)
{
	return 0;	
}

VOID	Obj_Human::SetBaseAttackFire(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Human::GetDefenceFire(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetResistFireDirtyFlag())
	{
		INT nBaseAttr=GetBaseDefenceFire();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_FIRE_RESIST);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetDefenceFireRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_FIRE, nValue);
		ClearResistFireDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_FIRE);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseDefenceFire(VOID)
{
	return 0;	
}

VOID	Obj_Human::SetBaseDefenceFire(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Light
INT Obj_Human::GetAttackLight(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetAttackLightDirtyFlag())
	{
		INT nBaseAttr=GetBaseAttackLight();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_LIGHT_ATTACK);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetAttackLightRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_LIGHT, nValue);
		ClearAttackLightDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_LIGHT);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseAttackLight(VOID)
{
	return 0;	
}

VOID	Obj_Human::SetBaseAttackLight(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Human::GetDefenceLight(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetResistLightDirtyFlag())
	{
		INT nBaseAttr=GetBaseDefenceLight();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_LIGHT_RESIST);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetDefenceLightRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_LIGHT, nValue);
		ClearResistLightDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_LIGHT);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseDefenceLight(VOID)
{
	return 0;	
}

VOID	Obj_Human::SetBaseDefenceLight(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Poison
INT Obj_Human::GetAttackPoison(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetAttackPoisonDirtyFlag())
	{
		INT nBaseAttr=GetBaseAttackPoison();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_POISON_ATTACK);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetAttackPoisonRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_POISON, nValue);
		ClearAttackPoisonDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_POISON);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseAttackPoison(VOID)
{
	return 0;	
}

VOID	Obj_Human::SetBaseAttackPoison(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Human::GetDefencePoison(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetResistPoisonDirtyFlag())
	{
		INT nBaseAttr=GetBaseDefencePoison();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_POISON_RESIST);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetDefencePoisonRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_POISON, nValue);
		ClearResistPoisonDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_POISON);
	__LEAVE_FUNCTION
	return 0;
}
INT Obj_Human::GetBaseDefencePoison(VOID)
{
	return 0;	
}

VOID	Obj_Human::SetBaseDefencePoison(INT const nValue)
{// forbiden modify this attribute
}

// Attr2 Reduce Slower Duration
INT Obj_Human::GetReduceSlowerDuration(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetReduceSlowerDurationDirtyFlag())
	{
		INT nBaseAttr=0;
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_COLD_TIME);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetReduceSlowerDurationRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_REDUCE_SLOWER_DURATION, nValue);
		ClearReduceSlowerDurationDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_REDUCE_SLOWER_DURATION);
	__LEAVE_FUNCTION
	return 0;
}

// Attr2 Reduce Weaken Duration
INT Obj_Human::GetReduceWeakenDuration(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetReduceWeakenDurationDirtyFlag())
	{
		INT nBaseAttr=0;
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_FIRE_TIME);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetReduceWeakenDurationRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_REDUCE_WEAKEN_DURATION, nValue);
		ClearReduceWeakenDurationDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_REDUCE_WEAKEN_DURATION);
	__LEAVE_FUNCTION
	return 0;
}

// Attr2 Reduce Faint Duration
INT Obj_Human::GetReduceFaintDuration(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetReduceFaintDurationDirtyFlag())
	{
		INT nBaseAttr=0;
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_LIGHT_TIME);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetReduceFaintDurationRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_REDUCE_FAINT_DURATION, nValue);
		ClearReduceFaintDurationDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_REDUCE_FAINT_DURATION);
	__LEAVE_FUNCTION
	return 0;
}

// Attr2 Reduce Poisoned Duration
INT Obj_Human::GetReducePoisonedDuration(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetReducePoisonedDurationDirtyFlag())
	{
		INT nBaseAttr=0;
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//装备对属性的点数影响
		pIE = ItemEffect(IATTRIBUTE_POISON_TIME);
		Assert( pIE );
		if( pIE->IsActive() )
		{
			nItemPointRefix= pIE->m_Attr.m_Value;
		}
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetReducePoisonedDurationRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_REDUCE_POISONED_DURATION, nValue);
		ClearReducePoisonedDurationDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_REDUCE_POISONED_DURATION);
	__LEAVE_FUNCTION
	return 0;
}

// Attr2 VisionRange
INT Obj_Human::GetVisionRange(VOID)
{
	__ENTER_FUNCTION
	_ITEM_EFFECT* pIE=NULL;
	if(TRUE==GetVisionRangeDirtyFlag())
	{
		INT nBaseAttr=GetBaseVisionRange();
		INT nImpactAndSkillRefix=0;
		INT nItemPointRefix=0;
		INT nItemRateRefix=0;
		INT nValue=0;
		//////////////////////////////////////////////////////////////////////
		//技能和效果对属性的影响
		nImpactAndSkillRefix=GetVisionRangeRefix();
		nValue = nBaseAttr+nImpactAndSkillRefix+nItemPointRefix+nItemRateRefix;
		SetIntAttr(CharIntAttrs_T::ATTR_VISION_RANGE, nValue);
		ClearVisionRangeDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_VISION_RANGE);
	__LEAVE_FUNCTION
	return 0;
}

INT Obj_Human::GetBaseVisionRange(VOID)
{
	//return g_MonsterAttrExTbl.Get(UINT MonsterType, UINT AttrEx);
	return BASE_VISION_RANGE;
}

VOID	Obj_Human::SetBaseVisionRange(INT const nValue)
{// forbiden modify this attribute
}


