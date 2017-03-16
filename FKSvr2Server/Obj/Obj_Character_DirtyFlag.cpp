#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////
// 文件名：Obj_Character_DirtyFlag.cpp
// 功能说明：角色层属性的脏标记操作
//
// 修改记录：
//
//
//
///////////////////////////////////////////////////////////////////////////////

#include "Obj_Character.h"
//MaxStrikePoint
BOOL Obj_Character::GetMaxStrikePointDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_MAX_STRIKE_POINT)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_STRIKE_POINT);
}
VOID Obj_Character::ClearMaxStrikePointDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_MAX_STRIKE_POINT);
}
VOID Obj_Character::MarkMaxStrikePointDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MAX_STRIKE_POINT);
}
BOOL Obj_Character::GetMaxStrikePointRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_STRIKE_POINT);
}
VOID Obj_Character::ClearMaxStrikePointRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_STRIKE_POINT);
}
VOID Obj_Character::MarkMaxStrikePointRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_STRIKE_POINT);	
}
//Max Rage
BOOL Obj_Character::GetMaxRageDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_MAX_RAGE)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_RAGE);
}
VOID Obj_Character::ClearMaxRageDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_MAX_RAGE);
}
VOID Obj_Character::MarkMaxRageDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MAX_RAGE);
}
BOOL Obj_Character::GetMaxRageRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_RAGE);
}
VOID Obj_Character::ClearMaxRageRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_RAGE);
}
VOID Obj_Character::MarkMaxRageRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_RAGE);	
}
//Str
BOOL Obj_Character::GetStrDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_STR)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_STR);
}
VOID Obj_Character::ClearStrDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_STR);
}
VOID Obj_Character::MarkStrDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_STR);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_PHY);

}
BOOL Obj_Character::GetStrRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_STR);
}
VOID Obj_Character::ClearStrRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_STR);
}
VOID Obj_Character::MarkStrRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_STR);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_STR);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_PHY);
}
//Spr
BOOL Obj_Character::GetSprDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_SPR)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_SPR);
}
VOID Obj_Character::ClearSprDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_SPR);
}
VOID Obj_Character::MarkSprDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_SPR);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_MAGIC);
}
BOOL Obj_Character::GetSprRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_SPR);
}
VOID Obj_Character::ClearSprRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_SPR);
}
VOID Obj_Character::MarkSprRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_SPR);	
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_SPR);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_MAGIC);
}
//Con
BOOL Obj_Character::GetConDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_CON)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_CON);
}
VOID Obj_Character::ClearConDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_CON);
}
VOID Obj_Character::MarkConDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_CON);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MAX_HP);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_DEFENCE_PHY);
}
BOOL Obj_Character::GetConRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_CON);
}
VOID Obj_Character::ClearConRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_CON);
}
VOID Obj_Character::MarkConRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_CON);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_CON);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MAX_HP);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_DEFENCE_PHY);
}
//Int
BOOL Obj_Character::GetIntDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_INT)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_INT);
}
VOID Obj_Character::ClearIntDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_INT);
}
VOID Obj_Character::MarkIntDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_INT);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MAX_MP);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_DEFENCE_MAGIC);
}
BOOL Obj_Character::GetIntRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_INT);
}
VOID Obj_Character::ClearIntRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_INT);
}
VOID Obj_Character::MarkIntRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_INT);	
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_INT);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MAX_MP);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_DEFENCE_MAGIC);
}
//Dex
BOOL Obj_Character::GetDexDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_DEX)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_DEX);
}
VOID Obj_Character::ClearDexDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_DEX);
}
VOID Obj_Character::MarkDexDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_DEX);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_HIT);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MISS);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_CRITICAL);
}
BOOL Obj_Character::GetDexRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_DEX);
}
VOID Obj_Character::ClearDexRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_DEX);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_DEX);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_HIT);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MISS);
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_CRITICAL);
}
VOID Obj_Character::MarkDexRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_DEX);	
}
//MaxHP
BOOL Obj_Character::GetMaxHPDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_MAX_HP)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_HP);
}
VOID Obj_Character::ClearMaxHPDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_MAX_HP);
}
VOID Obj_Character::MarkMaxHPDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MAX_HP);
}
BOOL Obj_Character::GetMaxHPRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_HP);
}
VOID Obj_Character::ClearMaxHPRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_HP);
}
VOID Obj_Character::MarkMaxHPRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_HP);	
}
//HP Regenerate
BOOL Obj_Character::GetHPRegenerateDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_HP_REGENERATE)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_HP_REGENERATE);
}
VOID Obj_Character::ClearHPRegenerateDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_HP_REGENERATE);
}
VOID Obj_Character::MarkHPRegenerateDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_HP_REGENERATE);
}
BOOL Obj_Character::GetHPRegenerateRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_HP_REGENERATE);
}
VOID Obj_Character::ClearHPRegenerateRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_HP_REGENERATE);
}
VOID Obj_Character::MarkHPRegenerateRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_HP_REGENERATE);	
}
//MAX MP
BOOL Obj_Character::GetMaxMPDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_MAX_MP)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_MP);
}
VOID Obj_Character::ClearMaxMPDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_MAX_MP);
}
VOID Obj_Character::MarkMaxMPDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MAX_MP);
}
BOOL Obj_Character::GetMaxMPRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_MP);
}
VOID Obj_Character::ClearMaxMPRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_MP);
}
VOID Obj_Character::MarkMaxMPRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_MAX_MP);	
}
//MP Regenerate
BOOL Obj_Character::GetMPRegenerateDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_MP_REGENERATE)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MP_REGENERATE);
}
VOID Obj_Character::ClearMPRegenerateDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_MP_REGENERATE);
}
VOID Obj_Character::MarkMPRegenerateDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MP_REGENERATE);
}
BOOL Obj_Character::GetMPRegenerateRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MP_REGENERATE);
}
VOID Obj_Character::ClearMPRegenerateRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_MP_REGENERATE);
}
VOID Obj_Character::MarkMPRegenerateRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_MP_REGENERATE);	
}

//CampID
BOOL Obj_Character::GetCampIDDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_CAMP)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_CAMP);
}
VOID Obj_Character::ClearCampIDDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_CAMP);
}
VOID Obj_Character::MarkCampIDDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_CAMP);
}
BOOL Obj_Character::GetCampIDRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_CAMP);
}
VOID Obj_Character::ClearCampIDRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_CAMP);
}
VOID Obj_Character::MarkCampIDRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_CAMP);	
}
//ModelID
BOOL Obj_Character::GetModelIDDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_MODEL_ID)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MODEL_ID);
}
VOID Obj_Character::ClearModelIDDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_MODEL_ID);
}
VOID Obj_Character::MarkModelIDDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MODEL_ID);
}
BOOL Obj_Character::GetModelIDRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MODEL_ID);
}
VOID Obj_Character::ClearModelIDRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_MODEL_ID);
}
VOID Obj_Character::MarkModelIDRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_MODEL_ID);	
}
//MountID
BOOL Obj_Character::GetMountIDDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_MOUNT_ID)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MOUNT_ID);
}
VOID Obj_Character::ClearMountIDDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_MOUNT_ID);
}
VOID Obj_Character::MarkMountIDDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MOUNT_ID);
}
BOOL Obj_Character::GetMountIDRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MOUNT_ID);
}
VOID Obj_Character::ClearMountIDRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_MOUNT_ID);
}
VOID Obj_Character::MarkMountIDRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_MOUNT_ID);	
}
//EXP Refix
BOOL Obj_Character::GetExpRefixDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_EXP_REFIX)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_EXP_REFIX);
}
VOID Obj_Character::ClearExpRefixDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_EXP_REFIX);
}
VOID Obj_Character::MarkExpRefixDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_EXP_REFIX);
}
BOOL Obj_Character::GetExpRefixRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_EXP_REFIX);
}
VOID Obj_Character::ClearExpRefixRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_EXP_REFIX);
}
VOID Obj_Character::MarkExpRefixRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_EXP_REFIX);	
}
//Stealth Level
BOOL Obj_Character::GetStealthLevelDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_STEALTH_LEVEL)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_STEALTH_LEVEL);
}
VOID Obj_Character::ClearStealthLevelDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_STEALTH_LEVEL);
}
VOID Obj_Character::MarkStealthLevelDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_STEALTH_LEVEL);
}
BOOL Obj_Character::GetStealthLevelRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_STEALTH_LEVEL);
}
VOID Obj_Character::ClearStealthLevelRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_STEALTH_LEVEL);
}
VOID Obj_Character::MarkStealthLevelRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_STEALTH_LEVEL);	
	OnStealthLevelChanged();
}
//Detect Level
BOOL Obj_Character::GetDetectLevelDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_DETECT_LEVEL)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_DETECT_LEVEL);
}
VOID Obj_Character::ClearDetectLevelDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_DETECT_LEVEL);
}
VOID Obj_Character::MarkDetectLevelDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_DETECT_LEVEL);
}
BOOL Obj_Character::GetDetectLevelRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_DETECT_LEVEL);
}
VOID Obj_Character::ClearDetectLevelRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_DETECT_LEVEL);
}
VOID Obj_Character::MarkDetectLevelRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_DETECT_LEVEL);
	OnDetectLevelChanged();
}

//Alive
BOOL Obj_Character::GetAliveDirtyFlag(VOID)
{
	return m_BoolAttrDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_ALIVE);
		//|| m_BoolAttrRefixDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_ALIVE);
}
VOID Obj_Character::ClearAliveDirtyFlag(VOID)
{
	m_BoolAttrDirtyFlags.ClearFlagByIndex(CharBoolAttrs_T::ATTR_ALIVE);
}
VOID Obj_Character::MarkAliveDirtyFlag(VOID)
{
	m_BoolAttrDirtyFlags.MarkFlagByIndex(CharBoolAttrs_T::ATTR_ALIVE);
}
/*
BOOL Obj_Character::GetAliveRefixDirtyFlag(VOID)
{
	return m_BoolAttrRefixDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_ALIVE);
}
VOID Obj_Character::ClearAliveRefixDirtyFlag(VOID)
{
	m_BoolAttrRefixDirtyFlags.ClearFlagByIndex(CharBoolAttrs_T::ATTR_ALIVE);
}
VOID Obj_Character::MarkAliveRefixDirtyFlag(VOID)
{
	m_BoolAttrRefixDirtyFlags.MarkFlagByIndex(CharBoolAttrs_T::ATTR_ALIVE);	
}
*/
//CanMove
BOOL Obj_Character::GetCanMoveDirtyFlag(VOID)
{
	return m_BoolAttrDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_CAN_MOVE);
		//|| m_BoolAttrRefixDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_CAN_MOVE);
}
VOID Obj_Character::ClearCanMoveDirtyFlag(VOID)
{
	m_BoolAttrDirtyFlags.ClearFlagByIndex(CharBoolAttrs_T::ATTR_CAN_MOVE);
}

VOID Obj_Character::MarkCanMoveDirtyFlag(VOID)
{
	m_BoolAttrDirtyFlags.MarkFlagByIndex(CharBoolAttrs_T::ATTR_CAN_MOVE);
}
/*
BOOL Obj_Character::GetCanMoveRefixDirtyFlag(VOID)
{
	return m_BoolAttrRefixDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_CAN_MOVE);
}
VOID Obj_Character::ClearCanMoveRefixDirtyFlag(VOID)
{
	m_BoolAttrRefixDirtyFlags.ClearFlagByIndex(CharBoolAttrs_T::ATTR_CAN_MOVE);
}
VOID Obj_Character::MarkCanMoveRefixDirtyFlag(VOID)
{
	m_BoolAttrRefixDirtyFlags.MarkFlagByIndex(CharBoolAttrs_T::ATTR_CAN_MOVE);	
}
*/
//CanAction Flag 1
BOOL Obj_Character::GetCanAction1DirtyFlag(VOID)
{
	return m_BoolAttrDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_CAN_ACTION1);
		//|| m_BoolAttrRefixDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_CAN_ACTION2);
}
VOID Obj_Character::ClearCanAction1DirtyFlag(VOID)
{
	m_BoolAttrDirtyFlags.ClearFlagByIndex(CharBoolAttrs_T::ATTR_CAN_ACTION1);
}
VOID Obj_Character::MarkCanAction1DirtyFlag(VOID)
{
	m_BoolAttrDirtyFlags.MarkFlagByIndex(CharBoolAttrs_T::ATTR_CAN_ACTION1);
}
//CanAction Flag 2
BOOL Obj_Character::GetCanAction2DirtyFlag(VOID)
{
	return m_BoolAttrDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_CAN_ACTION2);
		//|| m_BoolAttrRefixDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_CAN_ACTION2);
}
VOID Obj_Character::ClearCanAction2DirtyFlag(VOID)
{
	m_BoolAttrDirtyFlags.ClearFlagByIndex(CharBoolAttrs_T::ATTR_CAN_ACTION2);
}
VOID Obj_Character::MarkCanAction2DirtyFlag(VOID)
{
	m_BoolAttrDirtyFlags.MarkFlagByIndex(CharBoolAttrs_T::ATTR_CAN_ACTION2);
}
/*
BOOL Obj_Character::GetCanActionRefixDirtyFlag(VOID)
{
	return m_BoolAttrRefixDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_CAN_ACTION);
}
VOID Obj_Character::ClearCanActionRefixDirtyFlag(VOID)
{
	m_BoolAttrRefixDirtyFlags.ClearFlagByIndex(CharBoolAttrs_T::ATTR_CAN_ACTION);
}
VOID Obj_Character::MarkCanActionRefixDirtyFlag(VOID)
{
	m_BoolAttrRefixDirtyFlags.MarkFlagByIndex(CharBoolAttrs_T::ATTR_CAN_ACTION);	
}
*/
//Unbreakable
BOOL Obj_Character::GetUnbreakableDirtyFlag(VOID)
{
	return m_BoolAttrDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_UNBREAKABLE);
		//|| m_BoolAttrRefixDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_UNBREAKABLE);
}
VOID Obj_Character::ClearUnbreakableDirtyFlag(VOID)
{
	m_BoolAttrDirtyFlags.ClearFlagByIndex(CharBoolAttrs_T::ATTR_UNBREAKABLE);
}
VOID Obj_Character::MarkUnbreakableDirtyFlag(VOID)
{
	m_BoolAttrDirtyFlags.MarkFlagByIndex(CharBoolAttrs_T::ATTR_UNBREAKABLE);
}
/*
BOOL Obj_Character::GetUnbreakableRefixDirtyFlag(VOID)
{
	return m_BoolAttrRefixDirtyFlags.GetFlagByIndex(CharBoolAttrs_T::ATTR_UNBREAKABLE);
}
VOID Obj_Character::ClearUnbreakableRefixDirtyFlag(VOID)
{
	m_BoolAttrRefixDirtyFlags.ClearFlagByIndex(CharBoolAttrs_T::ATTR_UNBREAKABLE);
}
VOID Obj_Character::MarkUnbreakableRefixDirtyFlag(VOID)
{
	m_BoolAttrRefixDirtyFlags.MarkFlagByIndex(CharBoolAttrs_T::ATTR_UNBREAKABLE);	
}
*/
//Move Speed
BOOL Obj_Character::GetMoveSpeedDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_MOVE_SPEED)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MOVE_SPEED);
}
VOID Obj_Character::ClearMoveSpeedDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_MOVE_SPEED);
}	
VOID Obj_Character::MarkMoveSpeedDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MOVE_SPEED);
}
BOOL Obj_Character::GetMoveSpeedRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MOVE_SPEED);
}
VOID Obj_Character::ClearMoveSpeedRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_MOVE_SPEED);
}
VOID Obj_Character::MarkMoveSpeedRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_MOVE_SPEED);	
}
//Attack Speed
BOOL Obj_Character::GetAttackSpeedDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_SPEED)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_SPEED);
}
VOID Obj_Character::ClearAttackSpeedDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_SPEED);
}
VOID Obj_Character::MarkAttackSpeedDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_SPEED);
}
BOOL Obj_Character::GetAttackSpeedRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_SPEED);
}
VOID Obj_Character::ClearAttackSpeedRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_SPEED);
}
VOID Obj_Character::MarkAttackSpeedRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_SPEED);	
}
//Hit
BOOL Obj_Character::GetHitDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_HIT)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_HIT);
}
VOID Obj_Character::ClearHitDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_HIT);
}
VOID Obj_Character::MarkHitDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_HIT);
}
BOOL Obj_Character::GetHitRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_HIT);
}
VOID Obj_Character::ClearHitRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_HIT);
}
VOID Obj_Character::MarkHitRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_HIT);	
}
//Miss
BOOL Obj_Character::GetMissDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_MISS)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MISS);
}
VOID Obj_Character::ClearMissDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_MISS);
}
VOID Obj_Character::MarkMissDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_MISS);
}
BOOL Obj_Character::GetMissRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_MISS);
}
VOID Obj_Character::ClearMissRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_MISS);
}
VOID Obj_Character::MarkMissRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_MISS);	
}
//Critical
BOOL Obj_Character::GetCriticalDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_CRITICAL)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_CRITICAL);
}
VOID Obj_Character::ClearCriticalDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_CRITICAL);
}
VOID Obj_Character::MarkCriticalDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_CRITICAL);
}
BOOL Obj_Character::GetCriticalRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_CRITICAL);
}
VOID Obj_Character::ClearCriticalRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_CRITICAL);
}
VOID Obj_Character::MarkCriticalRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_CRITICAL);	
}
//Attack Physics
BOOL Obj_Character::GetAttackPhysicsDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_PHY)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_PHY);
}
VOID Obj_Character::ClearAttackPhysicsDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_PHY);
}
VOID Obj_Character::MarkAttackPhysicsDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_PHY);
}
BOOL Obj_Character::GetAttackPhysicsRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_PHY);
}
VOID Obj_Character::ClearAttackPhysicsRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_PHY);
}
VOID Obj_Character::MarkAttackPhysicsRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_PHY);	
}
//Defence Physics
BOOL Obj_Character::GetDefencePhysicsDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_DEFENCE_PHY)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_DEFENCE_PHY);
}
VOID Obj_Character::ClearDefencePhysicsDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_DEFENCE_PHY);
}
VOID Obj_Character::MarkDefencePhysicsDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_DEFENCE_PHY);
}
BOOL Obj_Character::GetDefencePhysicsRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_DEFENCE_PHY);
}
VOID Obj_Character::ClearDefencePhysicsRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_DEFENCE_PHY);
}
VOID Obj_Character::MarkDefencePhysicsRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_DEFENCE_PHY);	
}
//Attack Magic
BOOL Obj_Character::GetAttackMagicDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_MAGIC)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_MAGIC);
}
VOID Obj_Character::ClearAttackMagicDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_MAGIC);
}
VOID Obj_Character::MarkAttackMagicDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_MAGIC);
}
BOOL Obj_Character::GetAttackMagicRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_MAGIC);
}
VOID Obj_Character::ClearAttackMagicRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_MAGIC);
}
VOID Obj_Character::MarkAttackMagicRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_MAGIC);	
}
//Defence Magic
BOOL Obj_Character::GetDefenceMagicDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_DEFENCE_MAGIC)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_DEFENCE_MAGIC);
}
VOID Obj_Character::ClearDefenceMagicDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_DEFENCE_MAGIC);
}
VOID Obj_Character::MarkDefenceMagicDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_DEFENCE_MAGIC);
}
BOOL Obj_Character::GetDefenceMagicRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_DEFENCE_MAGIC);
}
VOID Obj_Character::ClearDefenceMagicRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_DEFENCE_MAGIC);
}
VOID Obj_Character::MarkDefenceMagicRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_DEFENCE_MAGIC);	
}
//Attack Cold
BOOL Obj_Character::GetAttackColdDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_COLD)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_COLD);
}
VOID Obj_Character::ClearAttackColdDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_COLD);
}
VOID Obj_Character::MarkAttackColdDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_COLD);
}
BOOL Obj_Character::GetAttackColdRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_COLD);
}
VOID Obj_Character::ClearAttackColdRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_COLD);
}
VOID Obj_Character::MarkAttackColdRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_COLD);	
}
//Resist Cold
BOOL Obj_Character::GetResistColdDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_RESIST_COLD)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_COLD);
}
VOID Obj_Character::ClearResistColdDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_RESIST_COLD);
}
VOID Obj_Character::MarkResistColdDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_RESIST_COLD);
}
BOOL Obj_Character::GetResistColdRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_COLD);
}
VOID Obj_Character::ClearResistColdRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_COLD);
}
VOID Obj_Character::MarkResistColdRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_COLD);	
}
//Attack Fire
BOOL Obj_Character::GetAttackFireDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_FIRE)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_FIRE);
}
VOID Obj_Character::ClearAttackFireDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_FIRE);
}
VOID Obj_Character::MarkAttackFireDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_FIRE);
}
BOOL Obj_Character::GetAttackFireRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_FIRE);
}
VOID Obj_Character::ClearAttackFireRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_FIRE);
}
VOID Obj_Character::MarkAttackFireRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_FIRE);	
}
//Resist Fire
BOOL Obj_Character::GetResistFireDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_RESIST_FIRE)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_FIRE);
}
VOID Obj_Character::ClearResistFireDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_RESIST_FIRE);
}
VOID Obj_Character::MarkResistFireDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_RESIST_FIRE);
}
BOOL Obj_Character::GetResistFireRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_FIRE);
}
VOID Obj_Character::ClearResistFireRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_FIRE);
}
VOID Obj_Character::MarkResistFireRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_FIRE);	
}
//Attack Light
BOOL Obj_Character::GetAttackLightDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_LIGHT)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_LIGHT);
}
VOID Obj_Character::ClearAttackLightDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_LIGHT);
}
VOID Obj_Character::MarkAttackLightDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_LIGHT);
}
BOOL Obj_Character::GetAttackLightRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_LIGHT);
}
VOID Obj_Character::ClearAttackLightRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_LIGHT);
}
VOID Obj_Character::MarkAttackLightRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_LIGHT);	
}
//Resist Light
BOOL Obj_Character::GetResistLightDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_RESIST_LIGHT)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_LIGHT);
}
VOID Obj_Character::ClearResistLightDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_RESIST_LIGHT);
}
VOID Obj_Character::MarkResistLightDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_RESIST_LIGHT);
}
BOOL Obj_Character::GetResistLightRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_LIGHT);
}
VOID Obj_Character::ClearResistLightRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_LIGHT);
}
VOID Obj_Character::MarkResistLightRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_LIGHT);	
}
//Attack Poison
BOOL Obj_Character::GetAttackPoisonDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_POISON)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_POISON);
}
VOID Obj_Character::ClearAttackPoisonDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_POISON);
}
VOID Obj_Character::MarkAttackPoisonDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_ATTACK_POISON);
}
BOOL Obj_Character::GetAttackPoisonRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_POISON);
}
VOID Obj_Character::ClearAttackPoisonRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_POISON);
}
VOID Obj_Character::MarkAttackPoisonRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_ATTACK_POISON);	
}
//Resist Poison
BOOL Obj_Character::GetResistPoisonDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_RESIST_POISON)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_POISON);
}
VOID Obj_Character::ClearResistPoisonDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_RESIST_POISON);
}
VOID Obj_Character::MarkResistPoisonDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_RESIST_POISON);
}
BOOL Obj_Character::GetResistPoisonRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_POISON);
}
VOID Obj_Character::ClearResistPoisonRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_POISON);
}
VOID Obj_Character::MarkResistPoisonRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_RESIST_POISON);	
}
//Reduce Slower Duration
BOOL Obj_Character::GetReduceSlowerDurationDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_SLOWER_DURATION)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_SLOWER_DURATION);
}
VOID Obj_Character::ClearReduceSlowerDurationDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_SLOWER_DURATION);
}
VOID Obj_Character::MarkReduceSlowerDurationDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_SLOWER_DURATION);
}
BOOL Obj_Character::GetReduceSlowerDurationRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_SLOWER_DURATION);
}
VOID Obj_Character::ClearReduceSlowerDurationRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_SLOWER_DURATION);
}
VOID Obj_Character::MarkReduceSlowerDurationRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_SLOWER_DURATION);	
}
//Reduce Weaken Duration
BOOL Obj_Character::GetReduceWeakenDurationDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_WEAKEN_DURATION)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_WEAKEN_DURATION);
}
VOID Obj_Character::ClearReduceWeakenDurationDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_WEAKEN_DURATION);
}
VOID Obj_Character::MarkReduceWeakenDurationDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_WEAKEN_DURATION);
}
BOOL Obj_Character::GetReduceWeakenDurationRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_WEAKEN_DURATION);
}
VOID Obj_Character::ClearReduceWeakenDurationRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_WEAKEN_DURATION);
}
VOID Obj_Character::MarkReduceWeakenDurationRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_WEAKEN_DURATION);	
}
//Reduce Faint Duration
BOOL Obj_Character::GetReduceFaintDurationDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_FAINT_DURATION)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_FAINT_DURATION);
}
VOID Obj_Character::ClearReduceFaintDurationDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_FAINT_DURATION);
}
VOID Obj_Character::MarkReduceFaintDurationDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_FAINT_DURATION);
}
BOOL Obj_Character::GetReduceFaintDurationRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_FAINT_DURATION);
}
VOID Obj_Character::ClearReduceFaintDurationRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_FAINT_DURATION);
}
VOID Obj_Character::MarkReduceFaintDurationRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_FAINT_DURATION);	
}
//Reduce Poison Duration
BOOL Obj_Character::GetReducePoisonedDurationDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_POISONED_DURATION)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_POISONED_DURATION);
}
VOID Obj_Character::ClearReducePoisonedDurationDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_POISONED_DURATION);
}
VOID Obj_Character::MarkReducePoisonedDurationDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_REDUCE_POISONED_DURATION);
}
BOOL Obj_Character::GetReducePoisonedDurationRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_POISONED_DURATION);
}
VOID Obj_Character::ClearReducePoisonedDurationRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_POISONED_DURATION);
}
VOID Obj_Character::MarkReducePoisonedDurationRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_REDUCE_POISONED_DURATION);	
}
//Vision Range
BOOL Obj_Character::GetVisionRangeDirtyFlag(VOID)
{
	return m_IntAttrDirtyFlags.GetFlagByIndex(CharIntAttrs_T::ATTR_VISION_RANGE)
		|| m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_VISION_RANGE);
}
VOID Obj_Character::ClearVisionRangeDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.ClearFlagByIndex(CharIntAttrs_T::ATTR_VISION_RANGE);
}
VOID Obj_Character::MarkVisionRangeDirtyFlag(VOID)
{
	m_IntAttrDirtyFlags.MarkFlagByIndex(CharIntAttrs_T::ATTR_VISION_RANGE);
}
BOOL Obj_Character::GetVisionRangeRefixDirtyFlag(VOID)
{
	return m_IntAttrRefixDirtyFlags.GetFlagByIndex(CharIntAttrRefixs_T::REFIX_VISION_RANGE);
}
VOID Obj_Character::ClearVisionRangeRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.ClearFlagByIndex(CharIntAttrRefixs_T::REFIX_VISION_RANGE);
}
VOID Obj_Character::MarkVisionRangeRefixDirtyFlag(VOID)
{
	m_IntAttrRefixDirtyFlags.MarkFlagByIndex(CharIntAttrRefixs_T::REFIX_VISION_RANGE);	
}

