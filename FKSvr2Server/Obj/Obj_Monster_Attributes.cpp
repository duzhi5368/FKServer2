#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////
// 文件名：Obj_Monster_Attributes.cpp
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
#include "Obj_Monster.h"
#include "GameTable.h"
#include "AI_Monster.h"

////////////////////////////////////////////////////////////////////////////////
//角色属性部分
//StrikePoint
INT	Obj_Monster::GetMaxStrikePoint(VOID)
{
	return 0;
}
INT Obj_Monster::GetMaxRage(VOID)
{
	return 0;
}
//Attr1: Str
INT	Obj_Monster::GetStr(VOID)
{
	return 0;
}
INT	Obj_Monster::GetBaseStr(VOID)
{
	return 0;
}
VOID Obj_Monster::SetBaseStr(INT const nValue)
{
	//don't modify this attribute
}
//Attr1: Spr
INT	Obj_Monster::GetSpr(VOID)
{
	return 0;
}
INT	Obj_Monster::GetBaseSpr(VOID)
{
	return 0;
}
VOID Obj_Monster::SetBaseSpr(INT const nValue)
{
	//don't modify this attribute
}
//Attr1: Con
INT	Obj_Monster::GetCon(VOID)
{
	return 0;
}
INT	Obj_Monster::GetBaseCon(VOID)
{
	return 0;
}
VOID Obj_Monster::SetBaseCon(INT const nValue)
{
	//don't modify this attribute
}
//Attr1: Int
INT	Obj_Monster::GetInt(VOID)
{
	return 0;
}
INT	Obj_Monster::GetBaseInt(VOID)
{
	return 0;
}
VOID Obj_Monster::SetBaseInt(INT const nValue)
{
	//don't modify this attribute
}
//Attr1: Dex
INT	Obj_Monster::GetDex(VOID)
{
	return 0;
}
INT	Obj_Monster::GetBaseDex(VOID)
{
	return 0;
}
VOID Obj_Monster::SetBaseDex(INT const nValue)
{
	//don't modify this attribute
}

INT Obj_Monster::GetMaxHP(VOID) 
{
__ENTER_FUNCTION

	if(TRUE==GetMaxHPDirtyFlag())
	{
		INT nValue=GetBaseMaxHP()+GetMaxHPRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_MAX_HP, nValue);
		ClearMaxHPDirtyFlag();
		if(GetHP()>nValue) SetHP(nValue);
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MAX_HP);

__LEAVE_FUNCTION

	return 1 ;
}

INT Obj_Monster::GetBaseMaxHP(VOID)
{
__ENTER_FUNCTION

	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_MAXHP ) ;

__LEAVE_FUNCTION

	return 1 ;
}

VOID Obj_Monster::SetBaseMaxHP(INT const nHp)
{ // forbiden modify this attribute
}

INT	Obj_Monster::GetHPRegenerate(VOID) 
{
__ENTER_FUNCTION

	if(TRUE==GetHPRegenerateDirtyFlag())
	{
		INT nValue=GetBaseHPRegenerate()+GetHPRegenerateRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_HP_REGENERATE, nValue);
		ClearHPRegenerateDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_HP_REGENERATE);

__LEAVE_FUNCTION

	return 1 ;
}
 
INT Obj_Monster::GetBaseHPRegenerate(VOID)
{
__ENTER_FUNCTION

	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_RESTOREHP) ;	

__LEAVE_FUNCTION

	return 1 ;
}

VOID 	Obj_Monster::SetBaseHPRegenerate(INT const nValue)
{// forbiden modify this attribute
}

//MP
INT Obj_Monster::GetMaxMP(VOID)
{
	/*
	if(TRUE==GetMaxMPDirtyFlag())
	{
		INT nValue=GetBaseMaxMP()+GetMaxMPRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_MAX_MP, nValue);
		ClearMaxMPDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MAX_MP);
	*/
	return 0;
}

INT Obj_Monster::GetBaseMaxMP(VOID)
{
	//return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_MAXMP) ;	
	return 0;
}

VOID Obj_Monster::SetBaseMaxMp(INT const nMp)
{// forbiden modify this attribute
}

INT Obj_Monster::GetMPRegenerate(VOID)
{
	/*
	if(TRUE==GetMPRegenerateDirtyFlag())
	{
		INT nValue=GetBaseMPRegenerate()+GetMPRegenerateRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_MP_REGENERATE, nValue);
		ClearMPRegenerateDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MP_REGENERATE);
	*/
	return 0;
}
 
INT Obj_Monster::GetBaseMPRegenerate(VOID)
{
	//return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_RESTOREMP) ;	
	return 0;
}

VOID 	Obj_Monster::SetBaseMPRegenerate(INT const nValue)
{// forbiden modify this attribute
}

const _CAMP_DATA *Obj_Monster::GetBaseCampData(VOID)const
{
	return &m_CampData;
}

VOID Obj_Monster::SetBaseCampData(const _CAMP_DATA *pCampData)
{
	m_CampData = *pCampData;
}

//CampID
INT Obj_Monster::GetCampID(VOID)
{
__ENTER_FUNCTION

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

__LEAVE_FUNCTION

	return 0 ;
}

INT Obj_Monster::GetBaseCampID(VOID) const
{
	//return 1;//临时测试
	return m_CampData.m_nCampID;
}

VOID	Obj_Monster::SetBaseCampID(INT const nID)
{
__ENTER_FUNCTION
	m_CampData.m_nCampID = nID;
	MarkCampIDDirtyFlag();
__LEAVE_FUNCTION
}

//modelID
INT Obj_Monster::GetModelID(VOID)
{
__ENTER_FUNCTION

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
__LEAVE_FUNCTION
	return -1 ;
}

INT Obj_Monster::GetBaseModelID(VOID) const
{
	return -1; // need modify	
}

VOID	Obj_Monster::SetBaseModelID(INT const nID)
{ // forbiden modify this attribute
}
// Alive flag, wraped in ObjCharacter
// In Combat flag, wraped in ObjCharacter
// Can move flag, wraped in ObjCharacter
// Can Action flag, wraped in ObjCharacter
// Unbreakable flag, wraped in ObjCharacter
BOOL	Obj_Monster::IsUnbreakable(VOID)
{
__ENTER_FUNCTION

  //  if (GetMonsterAI()->AIParam(AIPARAM_CANNOTATTACK) > 0)
		//return TRUE;

	return Obj_Character::IsUnbreakable();
__LEAVE_FUNCTION
	return FALSE ;
}

// Attr2: Move Speed, wraped in ObjCharacter
FLOAT	Obj_Monster::GetMoveSpeed(VOID)
{
__ENTER_FUNCTION

	if(TRUE==GetMoveSpeedDirtyFlag())
	{
		INT nValue=GetBaseMoveSpeed()+GetMoveSpeedRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_MOVE_SPEED, nValue);
		ClearMoveSpeedDirtyFlag();
	}
	FLOAT fMoveSpeed = GetIntAttr(CharIntAttrs_T::ATTR_MOVE_SPEED)/10.0f;//LM修改
	ENUM_MOVE_MODE eMoveMode = GetMoveMode();
	if(eMoveMode == MOVE_MODE_HOBBLE)
	{//变成基础速度的50%
		fMoveSpeed = fMoveSpeed*0.5f;
	}
	else if(eMoveMode == MOVE_MODE_RUN)
	{//变成基础速度的150%
		fMoveSpeed = fMoveSpeed*1.5f;
	}
	return fMoveSpeed;
__LEAVE_FUNCTION
	return 1.0f ;
}

INT	Obj_Monster::GetBaseMoveSpeed(VOID)
{
__ENTER_FUNCTION

	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_SPEED) ;	
__LEAVE_FUNCTION
	return 1 ;
}

VOID	Obj_Monster::SetBaseMoveSpeed(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack Speed
INT Obj_Monster::GetAttackSpeed(VOID)
{
__ENTER_FUNCTION

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
__LEAVE_FUNCTION
	return 1 ;
}

INT Obj_Monster::GetBaseAttackSpeed(VOID)
{
	INT nAttackSpeed = g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_ATTACKSPEED);
	if(75<nAttackSpeed)
	{
		nAttackSpeed = 75;
	}
	if(-300>nAttackSpeed)
	{
		nAttackSpeed = -300;
	}
	nAttackSpeed = BASE_ATTACK_SPEED - nAttackSpeed;
	return BASE_ATTACK_SPEED;
}

VOID	Obj_Monster::SetBaseAttackSpeed(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Miss
INT Obj_Monster::GetMiss(VOID)
{
__ENTER_FUNCTION
	if(TRUE==GetMissDirtyFlag())
	{
		INT nValue=GetBaseMiss()+GetMissRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_MISS, nValue);
		ClearMissDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MISS);
__LEAVE_FUNCTION
	return 1 ;
}

INT Obj_Monster::GetBaseMiss(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_MISS) ;	
}

VOID	Obj_Monster::SetBaseMiss(INT const nValue)
{// forbiden modify this attribute
}

// Attr2 Hit
INT Obj_Monster::GetHit(VOID)
{
__ENTER_FUNCTION
	if(TRUE==GetHitDirtyFlag())
	{
		INT nValue=GetBaseHit()+GetHitRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_HIT, nValue);
		ClearHitDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_HIT);
__LEAVE_FUNCTION
	return 1 ;
}

INT Obj_Monster::GetBaseHit(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_HIT) ;
}

VOID	Obj_Monster::SetBaseHit(INT const nValue)
{// forbiden modify this attribute
}

// Attr2 Critical
INT Obj_Monster::GetCritical(VOID)
{
	if(TRUE==GetCriticalDirtyFlag())
	{
		INT nValue=GetBaseCritical()+GetCriticalRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_CRITICAL, nValue);
		ClearCriticalDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_CRITICAL);
}

INT Obj_Monster::GetBaseCritical(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_CRITRATE) ;	
}

VOID	Obj_Monster::SetBaseCritical(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power physics
INT Obj_Monster::GetAttackPhysics(VOID)
{
	if(TRUE==GetAttackPhysicsDirtyFlag())
	{
		INT nValue=GetBaseAttackPhysics()+GetAttackPhysicsRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_PHY, nValue);
		ClearAttackPhysicsDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_PHY);
}

INT Obj_Monster::GetBaseAttackPhysics(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_ATTACKRATE_P) ;	
}

VOID	Obj_Monster::SetBaseAttackPhysics(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Monster::GetDefencePhysics(VOID)
{
	if(TRUE==GetDefencePhysicsDirtyFlag())
	{
		INT nValue=GetBaseDefencePhysics()+GetDefencePhysicsRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_PHY, nValue);
		ClearDefencePhysicsDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_PHY);
}

INT Obj_Monster::GetBaseDefencePhysics(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_DEFENCE_P) ;	
}

VOID	Obj_Monster::SetBaseDefencePhysics(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Magic
INT Obj_Monster::GetAttackMagic(VOID)
{
	if(TRUE==GetAttackMagicDirtyFlag())
	{
		INT nValue=GetBaseAttackMagic()+GetAttackMagicRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_MAGIC, nValue);
		ClearAttackMagicDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_MAGIC);
}

INT Obj_Monster::GetBaseAttackMagic(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_ATTACKRATE_M) ;	
}

VOID	Obj_Monster::SetBaseAttackMagic(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Monster::GetDefenceMagic(VOID)
{
	if(TRUE==GetDefenceMagicDirtyFlag())
	{
		INT nValue=GetBaseDefenceMagic()+GetDefenceMagicRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_MAGIC, nValue);
		ClearDefenceMagicDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_DEFENCE_MAGIC);
}

INT Obj_Monster::GetBaseDefenceMagic(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_DEFENCE_M) ;	
}

VOID	Obj_Monster::SetBaseDefenceMagic(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Cold
INT Obj_Monster::GetAttackCold(VOID)
{
	if(TRUE==GetAttackColdDirtyFlag())
	{
		INT nValue=GetBaseAttackCold()+GetAttackColdRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_COLD, nValue);
		ClearAttackColdDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_COLD);
}

INT Obj_Monster::GetBaseAttackCold(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_ATTACKCOLD) ;	
}

VOID	Obj_Monster::SetBaseAttackCold(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Monster::GetDefenceCold(VOID)
{
	if(TRUE==GetResistColdDirtyFlag())
	{
		INT nValue=GetBaseDefenceCold()+GetDefenceColdRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_COLD, nValue);
		ClearResistColdDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_COLD);
}

INT Obj_Monster::GetBaseDefenceCold(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_DEFENCECOLD) ;	
}

VOID	Obj_Monster::SetBaseDefenceCold(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Fire
INT Obj_Monster::GetAttackFire(VOID)
{
	if(TRUE==GetAttackFireDirtyFlag())
	{
		INT nValue=GetBaseAttackFire()+GetAttackFireRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_FIRE, nValue);
		ClearAttackFireDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_FIRE);
}

INT Obj_Monster::GetBaseAttackFire(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_ATTACKFIRE) ;	
}

VOID	Obj_Monster::SetBaseAttackFire(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Monster::GetDefenceFire(VOID)
{
	if(TRUE==GetResistFireDirtyFlag())
	{
		INT nValue=GetBaseDefenceFire()+GetDefenceFireRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_FIRE, nValue);
		ClearResistFireDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_FIRE);
}

INT Obj_Monster::GetBaseDefenceFire(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_ATTACKFIRE) ;	
}

VOID	Obj_Monster::SetBaseDefenceFire(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Light
INT Obj_Monster::GetAttackLight(VOID)
{
	if(TRUE==GetAttackLightDirtyFlag())
	{
		INT nValue=GetBaseAttackLight()+GetAttackLightRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_LIGHT, nValue);
		ClearAttackLightDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_LIGHT);
}

INT Obj_Monster::GetBaseAttackLight(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_ATTACKLIGHT) ;	
}

VOID	Obj_Monster::SetBaseAttackLight(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Monster::GetDefenceLight(VOID)
{
	if(TRUE==GetResistLightDirtyFlag())
	{
		INT nValue=GetBaseDefenceLight()+GetDefenceLightRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_LIGHT, nValue);
		ClearResistLightDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_LIGHT);
}

INT Obj_Monster::GetBaseDefenceLight(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_DEFENCELIGHT);	
}

VOID	Obj_Monster::SetBaseDefenceLight(INT const nValue)
{// forbiden modify this attribute
}

// Attr2: Attack and Defence power of Poison
INT Obj_Monster::GetAttackPoison(VOID)
{
	if(TRUE==GetAttackPoisonDirtyFlag())
	{
		INT nValue=GetBaseAttackPoison()+GetAttackPoisonRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_ATTACK_POISON, nValue);
		ClearAttackPoisonDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_ATTACK_POISON);
}

INT Obj_Monster::GetBaseAttackPoison(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_ATTACKPOISON) ;	
}

VOID	Obj_Monster::SetBaseAttackPoison(INT const nValue)
{// forbiden modify this attribute
}

INT Obj_Monster::GetDefencePoison(VOID)
{
	if(TRUE==GetResistPoisonDirtyFlag())
	{
		INT nValue=GetBaseDefencePoison()+GetDefencePoisonRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_RESIST_POISON, nValue);
		ClearResistPoisonDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_RESIST_POISON);
}
INT Obj_Monster::GetBaseDefencePoison(VOID)
{
	return g_MonsterAttrExTbl.Get( m_uDataID, CATTR_LEVEL2_DEFENCEPOISON) ;	
}

VOID	Obj_Monster::SetBaseDefencePoison(INT const nValue)
{// forbiden modify this attribute
}

// Attr2 Reduce Slower Duration
INT Obj_Monster::GetReduceSlowerDuration(VOID)
{
	return GetReduceSlowerDurationRefix();
}

// Attr2 Reduce Weaken Duration
INT Obj_Monster::GetReduceWeakenDuration(VOID)
{
	return GetReduceWeakenDurationRefix();
}

// Attr2 Reduce Faint Duration
INT Obj_Monster::GetReduceFaintDuration(VOID)
{
	return GetReduceFaintDurationRefix();
}

// Attr2 Reduce Poisoned Duration
INT Obj_Monster::GetReducePoisonedDuration(VOID)
{
	return GetReducePoisonedDurationRefix();
}

// Attr2 VisionRange
INT Obj_Monster::GetVisionRange(VOID)
{
	if(TRUE==GetVisionRangeDirtyFlag())
	{
		INT nValue=GetBaseVisionRange()+GetVisionRangeRefix();
		SetIntAttr(CharIntAttrs_T::ATTR_VISION_RANGE, nValue);
		ClearVisionRangeDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_VISION_RANGE);
}

INT Obj_Monster::GetBaseVisionRange(VOID)
{
	//return g_MonsterAttrExTbl.Get(UINT MonsterType, UINT AttrEx);
	return BASE_VISION_RANGE;
}

VOID	Obj_Monster::SetBaseVisionRange(INT const nValue)
{// forbiden modify this attribute
}


