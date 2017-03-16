#include "stdafx.h"
// Character_MenPai.cpp

#include "Obj_Character.h"
#include "MenPais.h"

#include "LogicManager.h"
using namespace Combat_Module::Skill_Module;
using namespace MenPai_Module;

VOID 	Obj_Character::MenPai_OnDamage(INT nDamage)
{
	__ENTER_FUNCTION
	if(Obj::OBJ_TYPE_HUMAN == GetObjType())
	{
		Obj_Human& rMe = (Obj_Human&)(*this);
		MenPaiID_t	nMenPai= rMe.GetMenPai();
		if(INVALID_ID==nMenPai)
		{
			AssertEx(FALSE,"[Obj_Character::MenPai_OnDamage]: Invalid Men pai id!");
			return;
		}
		MenPai_T const* pMenPai = g_MenPaiLogicList.GetLogicById(nMenPai);
		if(NULL==pMenPai)
		{
			AssertEx(FALSE,"[Obj_Character::MenPai_OnDamage]: NULL MenPai Logic pointer found!");
			return;
		}
		pMenPai->OnDamage(rMe, nDamage);
	}
	__LEAVE_FUNCTION
}
VOID 	Obj_Character::MenPai_OnDamageTarget(INT nDamage)
{
	__ENTER_FUNCTION
	if(Obj::OBJ_TYPE_HUMAN == GetObjType())
	{
		Obj_Human& rMe = (Obj_Human&)(*this);
		MenPaiID_t	nMenPai= rMe.GetMenPai();
		if(INVALID_ID==nMenPai)
		{
			AssertEx(FALSE,"[Obj_Character::MenPai_OnDamage]: Invalid Men pai id!");
			return;
		}
		MenPai_T const* pMenPai = g_MenPaiLogicList.GetLogicById(nMenPai);
		if(NULL==pMenPai)
		{
			AssertEx(FALSE,"[Obj_Character::MenPai_OnDamage]: NULL MenPai Logic pointer found!");
			return;
		}
		pMenPai->OnDamageTarget(rMe, nDamage);
	}
	__LEAVE_FUNCTION
}

VOID 	Obj_Character::MenPai_OnMyTrapActivated(Obj_Special& rTrap)
{
	__ENTER_FUNCTION
	if(Obj::OBJ_TYPE_HUMAN == GetObjType())
	{
		Obj_Human& rMe = (Obj_Human&)(*this);
		MenPaiID_t	nMenPai= rMe.GetMenPai();
		if(INVALID_ID==nMenPai)
		{
			AssertEx(FALSE,"[Obj_Character::MenPai_OnMyTrapActivated]: Invalid Men pai id!");
			return;
		}
		MenPai_T const* pMenPai = g_MenPaiLogicList.GetLogicById(nMenPai);
		if(NULL==pMenPai)
		{
			AssertEx(FALSE,"[Obj_Character::MenPai_OnMyTrapActivated]: NULL MenPai Logic pointer found!");
			return;
		}
		pMenPai->OnMyTrapActivated(rMe, rTrap);
	}
	__LEAVE_FUNCTION
}
VOID 	Obj_Character::MenPai_OnHealTarget(INT nHealed)
{
	__ENTER_FUNCTION
	if(Obj::OBJ_TYPE_HUMAN == GetObjType())
	{
		Obj_Human& rMe = (Obj_Human&)(*this);
		MenPaiID_t	nMenPai= rMe.GetMenPai();
		if(INVALID_ID==nMenPai)
		{
			AssertEx(FALSE,"[Obj_Character::MenPai_OnHealTarget]: Invalid Men pai id!");
			return;
		}
		MenPai_T const* pMenPai = g_MenPaiLogicList.GetLogicById(nMenPai);
		if(NULL==pMenPai)
		{
			AssertEx(FALSE,"[Obj_Character::MenPai_OnHealTarget]: NULL MenPai Logic pointer found!");
			return;
		}
		pMenPai->OnHealTarget(rMe, nHealed);
	}
	__LEAVE_FUNCTION
}
VOID 	Obj_Character::MenPai_OnDepleteStrikePoints(INT nStrikePoints)
{
	__ENTER_FUNCTION
	if(Obj::OBJ_TYPE_HUMAN == GetObjType())
	{
		Obj_Human& rMe = (Obj_Human&)(*this);
		MenPaiID_t	nMenPai= rMe.GetMenPai();
		if(INVALID_ID==nMenPai)
		{
			AssertEx(FALSE,"[Obj_Character::MenPai_OnDepleteStrikePoints]: Invalid Men pai id!");
			return;
		}
		MenPai_T const* pMenPai = g_MenPaiLogicList.GetLogicById(nMenPai);
		if(NULL==pMenPai)
		{
			AssertEx(FALSE,"[Obj_Character::MenPai_OnDepleteStrikePoints]: NULL MenPai Logic pointer found!");
			return;
		}
		pMenPai->OnDepleteStrikePoints(rMe, nStrikePoints);
	}
	__LEAVE_FUNCTION
}

