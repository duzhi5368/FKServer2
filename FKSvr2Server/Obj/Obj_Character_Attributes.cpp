#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////
// 文件名：Obj_Character_Attributes.cpp
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
#include "Obj_Character.h"

//StrikePoint
INT	Obj_Character::GetMaxStrikePointRefix(VOID)
{
	if(TRUE==GetMaxStrikePointRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_STRIKE_POINT, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_STRIKE_POINT, nValue);
		ClearMaxStrikePointRefixDirtyFlag();		
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_STRIKE_POINT);
}
VOID Obj_Character::SetMaxStrikePointRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_STRIKE_POINT, nValue);
	MarkMaxStrikePointRefixDirtyFlag();
}
//Rage
INT	Obj_Character::GetMaxRageRefix(VOID)
{
	if(TRUE==GetMaxRageRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_RAGE, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_RAGE, nValue);
		ClearMaxRageRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_RAGE);
}
VOID Obj_Character::SetMaxRageRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_RAGE, nValue);
	MarkMaxRageRefixDirtyFlag();
}
//Vigor
//LEVEL
//Attr1: Str
INT	Obj_Character::GetStrRefix(VOID)
{
	if(TRUE==GetStrRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_STR, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_STR, nValue);
		ClearStrRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_STR);
}
VOID Obj_Character::SetStrRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_STR, nValue);
	MarkStrRefixDirtyFlag();
}
//Attr1: Spr
INT Obj_Character::GetSprRefix(VOID)
{
	if(TRUE==GetSprRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_SPR, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_SPR, nValue);
		ClearSprRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_SPR);
}
VOID Obj_Character::SetSprRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_SPR, nValue);
	MarkSprRefixDirtyFlag();
}
//Attr1: Con
INT Obj_Character::GetConRefix(VOID)
{
	if(TRUE==GetConRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CON, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CON, nValue);
		ClearConRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CON);
}
VOID Obj_Character::SetConRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CON, nValue);
	MarkConRefixDirtyFlag();
}
//Attr1: Int
INT Obj_Character::GetIntRefix(VOID)
{
	if(TRUE==GetIntRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_INT, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_INT, nValue);
		ClearIntRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_INT);
}
VOID Obj_Character::SetIntRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_INT, nValue);
	MarkIntRefixDirtyFlag();;
}
//Attr1: Dex
INT Obj_Character::GetDexRefix(VOID)
{
	if(TRUE==GetDexRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEX, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEX, nValue);
		ClearDexRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEX);
}
VOID Obj_Character::SetDexRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEX, nValue);
	MarkDexRefixDirtyFlag();
}
//HP
INT Obj_Character::GetMaxHPRefix(VOID)
{
	if(TRUE==GetMaxHPRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_HP, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_HP, nValue);
		ClearMaxHPRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_HP);
}
VOID Obj_Character::SetMaxHPRefix(INT const nHp)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_HP, nHp);
	MarkMaxHPRefixDirtyFlag();
}
INT Obj_Character::GetHPRegenerateRefix(VOID)
{
	if(TRUE==GetHPRegenerateRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_HP_REGENERATE, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_HP_REGENERATE, nValue);
		ClearHPRegenerateRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_HP_REGENERATE);
}
VOID Obj_Character::SetHPRegenerateRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_HP_REGENERATE, nValue);
	MarkHPRegenerateRefixDirtyFlag();
}

//MP
INT Obj_Character::GetMaxMPRefix(VOID)
{
	if(TRUE==GetMaxMPRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_MP, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_MP, nValue);
		ClearMaxMPRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_MP);
}
VOID Obj_Character::SetMaxMPRefix(INT const nMp)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MAX_MP, nMp);
	MarkMaxMPRefixDirtyFlag();
}
INT Obj_Character::GetMPRegenerateRefix(VOID)
{
	if(TRUE==GetMPRegenerateRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MP_REGENERATE, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MP_REGENERATE, nValue);
		ClearMPRegenerateRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MP_REGENERATE);
}
VOID Obj_Character::SetMPRegenerateRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MP_REGENERATE, nValue);
	MarkMPRegenerateRefixDirtyFlag();
}
//CampID
const _CAMP_DATA *Obj_Character::GetCampData(VOID)
{
	const _CAMP_DATA *pCampData = GetBaseCampData();
	if ( pCampData != NULL )
	{
		m_CampDataRefix = *pCampData;
		m_CampDataRefix.m_nCampID = GetCampID();
		return &m_CampDataRefix;
	}
	else
	{
		return NULL;
	}
}

INT	Obj_Character::GetCampIDRefix(VOID)
{
	if(TRUE==GetCampIDRefixDirtyFlag())
	{
		INT nValue = INVALID_ID;
		if(TRUE==Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CAMP, nValue))
		{
			SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CAMP, nValue);
		}
		ClearCampIDRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CAMP);
}
VOID Obj_Character::SetCampIDRefix(CampID_t const nID)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CAMP, nID);
	MarkCampIDRefixDirtyFlag();
}
//modelID
INT Obj_Character::GetModelID(VOID)
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
INT	Obj_Character::GetModelIDRefix(VOID)
{
	if(TRUE==GetModelIDRefixDirtyFlag())
	{
		INT nValue = INVALID_ID;
		if(TRUE==Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MODEL_ID, nValue))
		{
			SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MODEL_ID, nValue);
		}
		ClearModelIDRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MODEL_ID);
}
VOID Obj_Character::SetModelIDRefix(ID_t const nID)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MODEL_ID, nID);
	MarkModelIDRefixDirtyFlag();
}
//mountID
INT Obj_Character::GetMountID(VOID)
{
	if(TRUE==GetMountIDDirtyFlag())
	{
		INT nValue=GetMountIDRefix();
		if(INVALID_ID==nValue)
		{
			nValue=GetBaseMountID();
		}
		SetIntAttr(CharIntAttrs_T::ATTR_MOUNT_ID, nValue);
		ClearMountIDDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_MOUNT_ID);
}
INT	Obj_Character::GetMountIDRefix(VOID)
{
	if(TRUE==GetMountIDRefixDirtyFlag())
	{
		INT nValue = INVALID_ID;
		if(TRUE==Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MOUNT_ID, nValue))
		{
			SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MOUNT_ID, nValue);
		}
		ClearMountIDRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MOUNT_ID);
}
VOID Obj_Character::SetMountIDRefix(ID_t const nID)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MOUNT_ID, nID);
	MarkMountIDRefixDirtyFlag();
}
//Exp Refix
INT Obj_Character::GetExpRefix(VOID)
{
	if(TRUE==GetExpRefixDirtyFlag())
	{
		INT nValue = GetBaseExpRefix();
		nValue += GetExpRefixRefix();
		0>nValue?nValue=0:NULL;
		MAX_EXP_REFIX_IN_CHAR<nValue?nValue=MAX_EXP_REFIX_IN_CHAR:NULL;
 		SetIntAttr(CharIntAttrs_T::ATTR_EXP_REFIX, nValue);
		ClearExpRefixDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_EXP_REFIX);
}
INT	Obj_Character::GetExpRefixRefix(VOID)
{
	if(TRUE==GetExpRefixRefixDirtyFlag())
	{
		INT nValue = INVALID_ID;
		if(TRUE==Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_EXP_REFIX, nValue))
		{
			SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_EXP_REFIX, nValue);
		}
		ClearExpRefixRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_EXP_REFIX);
}
VOID Obj_Character::SetExpRefixRefix(ID_t const nID)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_EXP_REFIX, nID);
	MarkExpRefixRefixDirtyFlag();
}
//StealthLevel
INT Obj_Character::GetStealthLevel(VOID)
{
	if(TRUE==GetStealthLevelDirtyFlag())
	{
		INT nValue=GetStealthLevelRefix() + 0;//0 is base stealth level for every character
		SetIntAttr(CharIntAttrs_T::ATTR_STEALTH_LEVEL, nValue);
		ClearStealthLevelDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_STEALTH_LEVEL);
}
INT	Obj_Character::GetStealthLevelRefix(VOID)
{
	if(TRUE==GetStealthLevelRefixDirtyFlag())
	{
		INT nValue = 0;//0 is default stealth level for every character
		if(TRUE==Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_STEALTH_LEVEL, nValue))
		{
			SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_STEALTH_LEVEL, nValue);
		}
		ClearStealthLevelRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_STEALTH_LEVEL);
}
VOID Obj_Character::SetStealthLevelRefix(ID_t const nID)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_STEALTH_LEVEL, nID);
	MarkStealthLevelRefixDirtyFlag();
}
//DetectLevel
INT Obj_Character::GetDetectLevel(VOID)
{
	if(TRUE==GetDetectLevelDirtyFlag())
	{
		INT nValue=GetDetectLevelRefix() + 0;//0 is base stealth level for every character
		SetIntAttr(CharIntAttrs_T::ATTR_DETECT_LEVEL, nValue);
		ClearDetectLevelDirtyFlag();
	}
	return GetIntAttr(CharIntAttrs_T::ATTR_DETECT_LEVEL);
}
INT	Obj_Character::GetDetectLevelRefix(VOID)
{
	if(TRUE==GetDetectLevelRefixDirtyFlag())
	{
		INT nValue = 0;//0 is default stealth level for every character
		if(TRUE==Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DETECT_LEVEL, nValue))
		{
			SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DETECT_LEVEL, nValue);
		}
		ClearDetectLevelRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DETECT_LEVEL);
}
VOID Obj_Character::SetDetectLevelRefix(ID_t const nID)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DETECT_LEVEL, nID);
	MarkDetectLevelRefixDirtyFlag();
}

//Alive flag
BOOL Obj_Character::IsAlive(VOID)
{
	if(0>=GetHP())
	{
		return FALSE;
	}
	if(TRUE==GetAliveDirtyFlag())
	{
		BOOL bValue = TRUE;
		if(TRUE==Impact_GetBoolAttrRefix(CharBoolAttrs_T::ATTR_ALIVE, bValue))
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_ALIVE, bValue);
		}
		else
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_ALIVE, TRUE);
		}
		ClearAliveDirtyFlag();
	}
	return GetBoolAttr(CharBoolAttrs_T::ATTR_ALIVE);
}
BOOL Obj_Character::IsAliveInDeed(VOID)
{
	return 0<GetHP();
}
BOOL Obj_Character::IsDie(VOID)
{
	return (!IsAliveInDeed());
}
VOID Obj_Character::ClearAliveFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_ALIVE, FALSE);
}
VOID Obj_Character::MarkAliveFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_ALIVE, TRUE);
}
//Obj_Character::In Combat flag
BOOL Obj_Character::InCombat(VOID) const
{
	return GetBoolAttr(CharBoolAttrs_T::ATTR_IN_COMBAT);
}
VOID Obj_Character::ClearCombatFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_IN_COMBAT, FALSE);
}
VOID Obj_Character::MarkCombatFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_IN_COMBAT, TRUE);
}
// Can move flag
BOOL Obj_Character::CanMove(VOID)
{
	if(TRUE==GetCanMoveDirtyFlag())
	{
		BOOL bValue = TRUE;
		if(TRUE==Impact_GetBoolAttrRefix(CharBoolAttrs_T::ATTR_CAN_MOVE, bValue))
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_MOVE, bValue);
		}
		else
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_MOVE, TRUE);
		}
		ClearCanMoveDirtyFlag();
	}
	return GetBoolAttr(CharBoolAttrs_T::ATTR_CAN_MOVE);
}
VOID Obj_Character::ClearCanMoveFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_MOVE, FALSE);
}
VOID Obj_Character::MarkCanMoveFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_MOVE, TRUE);
}
// Can Action flag 1
BOOL Obj_Character::CanActionFlag1(VOID)
{
	if(TRUE==GetCanAction1DirtyFlag())
	{
		BOOL bValue = TRUE;
		if(TRUE==Impact_GetBoolAttrRefix(CharBoolAttrs_T::ATTR_CAN_ACTION1, bValue))
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_ACTION1, bValue);
		}
		else
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_ACTION1, TRUE);
		}
		ClearCanAction1DirtyFlag();
	}
	return GetBoolAttr(CharBoolAttrs_T::ATTR_CAN_ACTION1);
}
VOID Obj_Character::ClearCanActionFlag1(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_ACTION1, FALSE);
}
VOID Obj_Character::MarkCanActionFlag1(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_ACTION1, TRUE);
}
// Can Action flag 2
BOOL Obj_Character::CanActionFlag2(VOID)
{
	if(TRUE==GetCanAction2DirtyFlag())
	{
		BOOL bValue = TRUE;
		if(TRUE==Impact_GetBoolAttrRefix(CharBoolAttrs_T::ATTR_CAN_ACTION2, bValue))
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_ACTION2, bValue);
		}
		else
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_ACTION2, TRUE);
		}
		ClearCanAction2DirtyFlag();
	}
	return GetBoolAttr(CharBoolAttrs_T::ATTR_CAN_ACTION2);
}
VOID Obj_Character::ClearCanActionFlag2(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_ACTION2, FALSE);
}
VOID Obj_Character::MarkCanActionFlag2(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_ACTION2, TRUE);
}
// Unbreakable flag
BOOL Obj_Character::IsUnbreakable(VOID)
{
	if(TRUE==GetUnbreakableDirtyFlag())
	{
		BOOL bValue = FALSE;//default value should be FALSE
		if(TRUE==Impact_GetBoolAttrRefix(CharBoolAttrs_T::ATTR_UNBREAKABLE, bValue))
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_UNBREAKABLE, bValue);
		}
		else
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_UNBREAKABLE, FALSE);//default value should be FALSE
		}
		ClearUnbreakableDirtyFlag();
	}
	return GetBoolAttr(CharBoolAttrs_T::ATTR_UNBREAKABLE);
}
VOID Obj_Character::ClearUnbreakableFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_UNBREAKABLE, FALSE);
}
VOID Obj_Character::MarkUnbreakableFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_UNBREAKABLE, TRUE);
}
/*
// InStealthMode flag
BOOL Obj_Character::InStealthMode(VOID)
{
	if(TRUE==GetInStealthModeDirtyFlag())
	{
		BOOL bValue = FALSE;//default value should be FALSE
		if(TRUE==Impact_GetBoolAttrRefix(CharBoolAttrs_T::ATTR_IN_STEALTH_MODE, bValue))
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_IN_STEALTH_MODE, bValue);
		}
		else
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_IN_STEALTH_MODE, FALSE);//default value should be FALSE
		}
		ClearInStealthModeDirtyFlag();
	}
	return GetBoolAttr(CharBoolAttrs_T::ATTR_IN_STEALTH_MODE);
}
VOID Obj_Character::ClearInStealthModeFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_IN_STEALTH_MODE, FALSE);
}
VOID Obj_Character::MarkInStealthModeFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_IN_STEALTH_MODE, TRUE);
}
// CanDetectStealth flag
BOOL Obj_Character::CanDetectStealth(VOID)
{
	if(TRUE==GetCanDetectStealthDirtyFlag())
	{
		BOOL bValue = FALSE;//default value should be FALSE
		if(TRUE==Impact_GetBoolAttrRefix(CharBoolAttrs_T::ATTR_CAN_DETECT_STEALTH, bValue))
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_DETECT_STEALTH, bValue);
		}
		else
		{
			SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_DETECT_STEALTH, FALSE);//default value should be FALSE
		}
		ClearCanDetectStealthDirtyFlag();
	}
	return GetBoolAttr(CharBoolAttrs_T::ATTR_CAN_DETECT_STEALTH);
}
VOID Obj_Character::ClearCanDetectStealthFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_DETECT_STEALTH, FALSE);
}
VOID Obj_Character::MarkCanDetectStealthFlag(VOID)
{
	SetBoolAttr(CharBoolAttrs_T::ATTR_CAN_DETECT_STEALTH, TRUE);
}
*/
// Attr2: Move Speed
INT Obj_Character::GetMoveSpeedRefix(VOID)
{
	if(TRUE==GetMoveSpeedRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MOVE_SPEED, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MOVE_SPEED, nValue);
		ClearMoveSpeedRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MOVE_SPEED);
}
VOID Obj_Character::SetMoveSpeedRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MOVE_SPEED, nValue);
	MarkMoveSpeedRefixDirtyFlag();
}
// Attr2: Attack Speed
INT	Obj_Character::GetAttackSpeedRefix(VOID)
{
	if(TRUE==GetAttackSpeedRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_SPEED, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_SPEED, nValue);
		ClearAttackSpeedRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_SPEED);
}
VOID Obj_Character::SetAttackSpeedRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_SPEED, nValue);
	MarkAttackSpeedRefixDirtyFlag();
}
// Attr2: Miss
INT	Obj_Character::GetMissRefix(VOID)
{
	if(TRUE==GetMissRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MISS, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MISS, nValue);
		ClearMissRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MISS);
}
VOID Obj_Character::SetMissRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_MISS, nValue);
	MarkMissRefixDirtyFlag();
}
// Attr2 Hit
INT	Obj_Character::GetHitRefix(VOID)
{
	if(TRUE==GetHitRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_HIT, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_HIT, nValue);
		ClearHitRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_HIT);
}
VOID Obj_Character::SetHitRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_HIT, nValue);
	MarkHitRefixDirtyFlag();
}
// Attr2 Critical
INT	Obj_Character::GetCriticalRefix(VOID)
{
	if(TRUE==GetCriticalRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CRITICAL, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CRITICAL, nValue);
		ClearCriticalRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CRITICAL);
}
VOID Obj_Character::SetCriticalRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_CRITICAL, nValue);
	MarkCriticalRefixDirtyFlag();
}
// Attr2: Attack and Defence power physics
INT	Obj_Character::GetAttackPhysicsRefix(VOID)
{
	if(TRUE==GetAttackPhysicsRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_PHY, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_PHY, nValue);
		ClearAttackPhysicsRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_PHY);
}
VOID Obj_Character::SetAttackPhysicsRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_PHY, nValue);
	MarkAttackPhysicsRefixDirtyFlag();
}
INT	Obj_Character::GetDefencePhysicsRefix(VOID)
{
	if(TRUE==GetDefencePhysicsRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEFENCE_PHY, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEFENCE_PHY, nValue);
		ClearDefencePhysicsRefixDirtyFlag();		
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEFENCE_PHY);
}
VOID Obj_Character::SetDefencePhysicsRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEFENCE_PHY, nValue);
	MarkDefencePhysicsRefixDirtyFlag();
}
// Attr2: Attack and Defence power of Magic
INT	Obj_Character::GetAttackMagicRefix(VOID)
{
	if(TRUE==GetAttackMagicRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_MAGIC, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_MAGIC, nValue);
		ClearAttackMagicRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_MAGIC);
}
VOID Obj_Character::SetAttackMagicRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_MAGIC, nValue);
	MarkAttackMagicRefixDirtyFlag();
}
INT	Obj_Character::GetDefenceMagicRefix(VOID)
{
	if(TRUE==GetDefenceMagicRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEFENCE_MAGIC, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEFENCE_MAGIC, nValue);
		ClearDefenceMagicRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEFENCE_MAGIC);
}
VOID Obj_Character::SetDefenceMagicRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_DEFENCE_MAGIC, nValue);
	MarkDefenceMagicRefixDirtyFlag();
}
// Attr2: Attack and Defence power of Cold
INT	Obj_Character::GetAttackColdRefix(VOID)
{
	if(TRUE==GetAttackColdRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_COLD, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_COLD, nValue);
		ClearAttackColdRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_COLD);
}
VOID Obj_Character::SetAttackColdRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_COLD, nValue);
	MarkAttackColdRefixDirtyFlag();
}
INT	Obj_Character::GetDefenceColdRefix(VOID)
{
	if(TRUE==GetResistColdRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_COLD, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_COLD, nValue);
		ClearResistColdRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_COLD);
}
VOID Obj_Character::SetDefenceColdRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_COLD, nValue);
	MarkResistColdRefixDirtyFlag();
}
// Attr2: Attack and Defence power of Fire
INT	Obj_Character::GetAttackFireRefix(VOID)
{
	if(TRUE==GetAttackFireRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_FIRE, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_FIRE, nValue);
		ClearAttackFireRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_FIRE);
}
VOID Obj_Character::SetAttackFireRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_FIRE, nValue);
	MarkAttackFireRefixDirtyFlag();
}
INT	Obj_Character::GetDefenceFireRefix(VOID)
{
	if(TRUE==GetResistFireRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_FIRE, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_FIRE, nValue);
		ClearResistFireRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_FIRE);
}
VOID Obj_Character::SetDefenceFireRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_FIRE, nValue);
	MarkResistFireRefixDirtyFlag();
}
// Attr2: Attack and Defence power of Light
INT	Obj_Character::GetAttackLightRefix(VOID)
{
	if(TRUE==GetAttackLightRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_LIGHT, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_LIGHT, nValue);
		ClearAttackLightRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_LIGHT);
}
VOID Obj_Character::SetAttackLightRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_LIGHT, nValue);
	MarkAttackLightRefixDirtyFlag();
}
INT	Obj_Character::GetDefenceLightRefix(VOID)
{
	if(TRUE==GetResistLightRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_LIGHT, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_LIGHT, nValue);
		ClearResistLightRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_LIGHT);
}
VOID Obj_Character::SetDefenceLightRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_LIGHT, nValue);
	MarkResistLightRefixDirtyFlag();
}
// Attr2: Attack and Defence power of Poison
INT	Obj_Character::GetAttackPoisonRefix(VOID)
{
	if(TRUE==GetAttackPoisonRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_POISON, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_POISON, nValue);
		ClearAttackPoisonRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_POISON);
}
VOID Obj_Character::SetAttackPoisonRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_ATTACK_POISON, nValue);
	MarkAttackPoisonRefixDirtyFlag();
}
INT	Obj_Character::GetDefencePoisonRefix(VOID)
{
	if(TRUE==GetResistPoisonRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_POISON, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_POISON, nValue);
		ClearResistPoisonRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_POISON);
}
VOID Obj_Character::SetDefencePoisonRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_RESIST_POISON, nValue);
	MarkResistPoisonRefixDirtyFlag();
}
// Attr2 Reduce Slower Duration
INT	Obj_Character::GetReduceSlowerDurationRefix(VOID)
{
	if(TRUE==GetReduceSlowerDurationRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_SLOWER_DURATION, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_SLOWER_DURATION, nValue);
		ClearReduceSlowerDurationRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_SLOWER_DURATION);
}
VOID Obj_Character::SetReduceSlowerDurationRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_SLOWER_DURATION, nValue);
	MarkReduceSlowerDurationRefixDirtyFlag();
}
// Attr2 Reduce Weaken Duration
INT	Obj_Character::GetReduceWeakenDurationRefix(VOID)
{
	if(TRUE==GetReduceWeakenDurationRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_WEAKEN_DURATION, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_WEAKEN_DURATION, nValue);
		ClearReduceWeakenDurationRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_WEAKEN_DURATION);
}
VOID Obj_Character::SetReduceWeakenDurationRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_WEAKEN_DURATION, nValue);
	MarkReduceWeakenDurationRefixDirtyFlag();
}
// Attr2 Reduce Faint Duration
INT	Obj_Character::GetReduceFaintDurationRefix(VOID)
{
	if(TRUE==GetReduceFaintDurationRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_FAINT_DURATION, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_FAINT_DURATION, nValue);
		ClearReduceFaintDurationRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_FAINT_DURATION);
}
VOID Obj_Character::SetReduceFaintDurationRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_FAINT_DURATION, nValue);
	MarkReduceFaintDurationRefixDirtyFlag();
}
// Attr2 Reduce Poisoned Duration
INT	Obj_Character::GetReducePoisonedDurationRefix(VOID)
{
	if(TRUE==GetReducePoisonedDurationRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_POISONED_DURATION, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_POISONED_DURATION, nValue);
		ClearReducePoisonedDurationRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_POISONED_DURATION);
}
VOID Obj_Character::SetReducePoisonedDurationRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_REDUCE_POISONED_DURATION, nValue);
	MarkReducePoisonedDurationRefixDirtyFlag();
}
// Attr2 VisionRange
INT	Obj_Character::GetVisionRangeRefix(VOID)
{
	if(TRUE==GetVisionRangeRefixDirtyFlag())
	{
		INT nValue = 0;
		Impact_GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_VISION_RANGE, nValue);
		SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_VISION_RANGE, nValue);
		ClearVisionRangeRefixDirtyFlag();
	}
	return GetIntAttrRefix(CharIntAttrRefixs_T::REFIX_VISION_RANGE);
}
VOID Obj_Character::SetVisionRangeRefix(INT const nValue)
{
	SetIntAttrRefix(CharIntAttrRefixs_T::REFIX_VISION_RANGE, nValue);
	MarkVisionRangeRefixDirtyFlag();
}

//reset data
//整数属性
VOID Obj_Character::ResetIntAttrs(VOID)
{
	m_IntAttrs.ResetAttrs();
	m_IntAttrs.SetAttr(CharIntAttrs_T::ATTR_CAMP, INVALID_ID);
	m_IntAttrs.SetAttr(CharIntAttrs_T::ATTR_MODEL_ID, INVALID_ID);
	MarkAllIntAttrDirtyFlags();
}

//整数属性修正
VOID Obj_Character::ResetIntAttrRefixs(VOID)
{
	m_IntAttrRefixs.ResetAttrs();
	m_IntAttrRefixs.SetAttr(CharIntAttrRefixs_T::REFIX_CAMP, INVALID_ID);
	m_IntAttrRefixs.SetAttr(CharIntAttrRefixs_T::REFIX_MODEL_ID, INVALID_ID);
	MarkAllIntAttrRefixDirtyFlags();
}

//BOOL属性
VOID Obj_Character::ResetBoolAttr(VOID)
{
	m_BoolAttrs.ResetAttrs();
	MarkAllBoolAttrDirtyFlags();
}

