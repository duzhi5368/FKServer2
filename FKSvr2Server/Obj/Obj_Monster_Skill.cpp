#include "stdafx.h"
#include "Obj_Monster.h"
#include "Scene.h"
#include "Config.h"
#include "GameTable.h"
#include "Obj_Character.h"
#include "LogicManager.h"

using namespace Combat_Module::Skill_Module;
VOID 	Obj_Monster::Impact_InitList(VOID)
{
	__ENTER_FUNCTION
	_IMPACT_LIST& rList = Impact_GetImpactList();
	rList.CleanUp();
	__LEAVE_FUNCTION
}
VOID	Obj_Monster::SetCooldown(CooldownID_t const nID, Time_t nCooldown)
{
	__ENTER_FUNCTION
	
	if(0<=nID)
	{
		m_nCooldown = nCooldown;
	}
	else
	{
		AssertEx(NULL,"[Obj_Monster::SetCooldown]: Index out of range!");
	}
	__LEAVE_FUNCTION
}
BOOL	Obj_Monster::IsCooldowned(CooldownID_t const nID) const
{
	__ENTER_FUNCTION
	if(0<=nID)
	{
		return 0>=m_nCooldown;
	}
	return FALSE;
	__LEAVE_FUNCTION
	return FALSE;
}
BOOL Obj_Monster::HeartBeat_Cooldown(UINT uTime)
{
	__ENTER_FUNCTION
	INT nDeltaTime = GetLogicTime();
	if(0<m_nCooldown)
	{
		m_nCooldown = m_nCooldown<nDeltaTime?0:m_nCooldown-nDeltaTime;
	}
	__LEAVE_FUNCTION
	return TRUE;
}
BOOL	Obj_Monster::HeartBeat_Recover(UINT uTime)
{
	__ENTER_FUNCTION
	int nCount=0;
	m_nElapsedRevocerTick += GetLogicTime();
	if(FALSE==IsAliveInDeed())
	{
		return TRUE;
	}
	while(0<m_nElapsedRevocerTick)
	{
		m_nElapsedRevocerTick-= RECOVER_INTERVAL;
		++nCount;
	}
	if(0<nCount)
	{
		/** 进行回红操作 */
		INT nCur = GetHP( ); 
		INT nMax = GetMaxHP();
		INT nHPRegenerate = GetHPRegenerate();
		if(nCur<nMax && 0<nHPRegenerate)
		{
			nCur += nHPRegenerate*nCount ;
			nCur<nMax?nCur:nCur=nMax;
			SetHP(nCur) ;
		}	
	}
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}
