#include "stdafx.h"
// Character_Skill.cpp

#include "Obj_Character.h"
#include "SkillInfo.h"
#include "Skill_Core.h"
#include "AI_Character.h"
#include "GCCharSkill_Missed.h"
#include "GCDetailHealsAndDamages.h"
#include "Scene.h"
#include "GameTable.h"
#include "Obj_Pet.h"
#include "Obj_Monster.h"
#include "AI_Monster.h"
#include "ActionDelegator.h"


using namespace Action_Module;
using namespace Combat_Module::Skill_Module;
using namespace Combat_Module;
using namespace Combat_Module;
using namespace Combat_Module::Camp_Stand;
using namespace Packets;

static VOID BroadCast_HealAndDamageMsg(Obj_Character* pThis, Obj_Character* pTarget,GCDetailHealsAndDamages& rMsg);

// 计算对方对我来说是否为隐身的
BOOL CalcIsTargetStealth(INT nThisLevel, INT nThisDetectLevel, const WORLD_POS *pThisPos, INT nTargetLevel, INT nTargetStealthLevel, const WORLD_POS *pTargetPos)
{
	if(nTargetStealthLevel <= 0)
		return FALSE;

	//Claculate Detect distance
	//INT StealthParam1 = 1;
	//INT StealthParam2 = 1;
	//INT StealthParam3 = 1;
	//INT StealthParam4 = 0;
	//
	//INT nDeltaLevel = nThisLevel - nTargetLevel;
	//INT nDeltaStealth = nThisDetectLevel - nTargetStealthLevel;
	//INT nDetectRange = StealthParam2*nDeltaLevel + StealthParam2*nDeltaStealth + StealthParam4;
	//nDetectRange = StealthParam1 * nDetectRange;
	//nDetectRange = min(15, nDetectRange);
	//FLOAT fCurrentDistanceSq = MyLengthSq(pThisPos, pTargetPos);
	//if(fCurrentDistanceSq <= nDetectRange*nDetectRange)
	INT nDeltaLevel = nThisDetectLevel + nThisLevel;
	INT nStealthLevel = nTargetStealthLevel + nTargetLevel;
	if(nStealthLevel > nDeltaLevel)
	{
		return TRUE;
	}
	return FALSE;
}



VOID Obj_Character::GM_killObj(VOID)
{
__ENTER_FUNCTION
	INT nHP = GetHP();
	
	HealthIncrement(-nHP, this);		

__LEAVE_FUNCTION
}

VOID Obj_Character::GM_ForceDie(Obj_Character* pKiller)
{
	__ENTER_FUNCTION
	if(TRUE==IsAliveInDeed()&&TRUE==IsActiveObj())
	{
		SetHP(0);
		OnDie(pKiller->GetID());
	}
	__LEAVE_FUNCTION
}

VOID Obj_Character::HealthIncrement(INT nIncrement, Obj_Character* pCharacter, BOOL bCritical)
{
	__ENTER_FUNCTION
	if(TRUE==IsActiveObj())
	{
		INT nValue = GetHP() + nIncrement;
		GCDetailHealsAndDamages msg;
		msg.SetReceiverID(GetID());
		if(pCharacter)
		{
			msg.SetSenderID(pCharacter->GetID());
			msg.SetSenderLogicCount(pCharacter->GetLogicCount());
		}
		else
		{
			msg.SetSenderID(INVALID_ID);
			msg.SetSenderLogicCount(0);
		}
		msg.SetHpModification(nIncrement);
		msg.SetCriticalHitFlag(bCritical);
		BroadCast_HealAndDamageMsg(this, pCharacter,msg);
		if(0<=nIncrement)
		{
			//OnHeal
			if(GetMaxHP()<nValue)
			{
				nValue=GetMaxHP();
			}
			INT nOldHP = GetHP();
			SetHP(nValue);
			if(nOldHP <= 0 && GetHP() > 0)
			{
				OnRelive((pCharacter)?(pCharacter->GetID()):INVALID_ID);
			}
		}
		else
		{
			// set hp now
			//打断和干扰动作进行
			GetGlobalActionDelegator().DisturbCurrentAction(*this);
			AI_Character *pAI = GetAIObj();
			INT nOldHP = GetHP();
			if(0>nValue)
			{
				nValue=0;
			}
			SetHP(nValue);

			if(NULL!=pAI)
			{
				pAI->OnDamage(-nIncrement, pCharacter);
			}
			if(nOldHP > 0 && GetHP() <= 0)
			{
				OnDie(pCharacter->GetID());
			}
		}
	}
	__LEAVE_FUNCTION
}
VOID Obj_Character::ManaIncrement(INT nIncrement, Obj_Character* pCharacter)
{
	__ENTER_FUNCTION
	if(TRUE==IsActiveObj())
	{
		INT nValue = GetMP() + nIncrement;
		GCDetailHealsAndDamages msg;
		msg.SetReceiverID(GetID());
		if(pCharacter)
		{
			msg.SetSenderID(pCharacter->GetID());
			msg.SetSenderLogicCount(pCharacter->GetLogicCount());
		}
		else
		{
			msg.SetSenderID(INVALID_ID);
			msg.SetSenderLogicCount(0);
		}
		msg.SetMpModification(nIncrement);
		msg.SetCriticalHitFlag(FALSE);
		BroadCast_HealAndDamageMsg(this, pCharacter,msg);
		if(0<=nIncrement)
		{
			//OnHeal
			if(GetMaxMP()<nValue)
			{
				nValue = GetMaxMP();
			}
			SetMP(nValue);
		}
		else
		{   //OnDamage
			if(0>nValue)
			{
				nValue=0;
			}
			SetMP(nValue);
		}
	}
	__LEAVE_FUNCTION
}
VOID Obj_Character::RageIncrement(INT nIncrement, Obj_Character* pCharacter)
{
	__ENTER_FUNCTION
	if(TRUE==IsActiveObj()&&Obj::OBJ_TYPE_HUMAN == GetObjType())
	{
		INT nValue = GetRage() + nIncrement;
		GCDetailHealsAndDamages msg;
		msg.SetReceiverID(GetID());
		if(pCharacter)
		{
			msg.SetSenderID(pCharacter->GetID());
			msg.SetSenderLogicCount(pCharacter->GetLogicCount());
		}
		else
		{
			msg.SetSenderID(INVALID_ID);
			msg.SetSenderLogicCount(0);
		}
		msg.SetRageModification(nIncrement);
		msg.SetCriticalHitFlag(FALSE);
		BroadCast_HealAndDamageMsg(this, pCharacter,msg);
		if(0<=nIncrement)
		{
			//OnHeal
			if(GetMaxRage()<nValue)
			{
				nValue = GetMaxRage();
			}
			SetRage(nValue);
		}
		else
		{   //OnDamage
			if(0>nValue)
			{
				nValue=0;
			}
			SetRage(nValue);
		}
	}
	__LEAVE_FUNCTION
}
VOID Obj_Character::StrikePointIncrement(INT nIncrement, Obj_Character* pCharacter)
{
	__ENTER_FUNCTION
	if(TRUE==IsActiveObj()&&Obj::OBJ_TYPE_HUMAN == GetObjType())
	{
		
		INT nValue = GetStrikePoint() + nIncrement;
		GCDetailHealsAndDamages msg;
		msg.SetReceiverID(GetID());
		if(pCharacter)
		{
			msg.SetSenderID(pCharacter->GetID());
			msg.SetSenderLogicCount(pCharacter->GetLogicCount());
		}
		else
		{
			msg.SetSenderID(INVALID_ID);
			msg.SetSenderLogicCount(0);
		}
		msg.SetStrikePointModification(nIncrement);
		msg.SetCriticalHitFlag(FALSE);
		BroadCast_HealAndDamageMsg(this, pCharacter,msg);
		if(0<=nIncrement)
		{
			//OnHeal
			if(GetMaxStrikePoint()<nValue)
			{
				nValue = GetMaxStrikePoint();
			}
			SetStrikePoint(nValue);
		}
		else
		{   //OnDamage
			if(0>nValue)
			{
				nValue=0;
			}
			SetStrikePoint(nValue);
		}
	}
	__LEAVE_FUNCTION
}
VOID  Obj_Character::RefixSkill(SkillInfo_T& rSkill)
{
	__ENTER_FUNCTION
	Skill_RefixSkill(rSkill);
	Impact_RefixSkill(rSkill);
	__LEAVE_FUNCTION
}
VOID Obj_Character::RefixImpact(OWN_IMPACT& rImpactNeedRedix)
{
	__ENTER_FUNCTION
	return Impact_RefixImpact(rImpactNeedRedix);
	__LEAVE_FUNCTION
}
VOID Obj_Character::RefixRageRegeneration(INT& rRageRegeneration)
{
	__ENTER_FUNCTION
	return Impact_RefixRageRegeneration(rRageRegeneration);
	__LEAVE_FUNCTION
}

BOOL Obj_Character::IsEnemyCamp(Obj_Character& rTar)
{
__ENTER_FUNCTION

	Obj_Character *pOwner_A = GetOwner();
	Obj_Character *pOwner_B = rTar.GetOwner();
	if ( pOwner_A != NULL || pOwner_B != NULL )
	{
		if ( pOwner_A == &rTar
			|| pOwner_B == this
			|| pOwner_A == pOwner_B )
		{
			return FALSE;
		}
	}

	ENUM_RELATION eRelation = CalcRelationType( GetCampData()->m_nCampID, rTar.GetCampData()->m_nCampID, &g_CampAndStandDataMgr );
	if ( eRelation == RELATION_FRIEND )
		return FALSE;
	else
		return TRUE;

	return FALSE;
__LEAVE_FUNCTION
	return FALSE;
}
BOOL Obj_Character::IsFriendCamp(Obj_Character& rTar)
{
__ENTER_FUNCTION
	return FALSE==IsEnemyCamp(rTar);
__LEAVE_FUNCTION
	return FALSE;
}
BOOL Obj_Character::CanUseSkillNow(VOID)
{
__ENTER_FUNCTION
	if(0<GetActionTime())
	{
		return FALSE;
	}
	return GetGlobalActionDelegator().CanDoNextAction(*this);
__LEAVE_FUNCTION
	return FALSE;
}
VOID	Obj_Character::Skill_ExecFromItemScript(SkillID_t const nID)
{
	__ENTER_FUNCTION
	SkillInfo_T& rSkillInfo = GetSkillInfo();
	TargetingAndDepletingParams_T& rParams = GetTargetingAndDepletingParams();
	if(TRUE!=CanUseSkillNow())
	{
		return;
		//InterruptSkillNow();
	}
	AI_Character* pAI = GetAIObj();
	if(NULL!=pAI)
	{
		pAI->Stop();
		rParams.SetIgnoreConditionCheckFlag(FALSE);
		ObjID_t nTargetID = rParams.GetTargetObj();
		WORLD_POS pos = rParams.GetTargetPosition();
		BYTE nLevel = rParams.GetSkillLevel();
		pAI->UseSkill(nID,nLevel,nTargetID,pos.m_fX,pos.m_fZ,-1.0f,INVALID_ID);	
	}
	__LEAVE_FUNCTION
	return;
}

VOID	Obj_Character::Skill_ExecFromScript(SkillID_t const nID, BYTE nLevel, ObjID_t nTargetID, WORLD_POS& pos, FLOAT fDir, BOOL bPassSkillCheck)
{
	__ENTER_FUNCTION
	SkillInfo_T& rSkillInfo = GetSkillInfo();
	TargetingAndDepletingParams_T& rParams = GetTargetingAndDepletingParams();
	if(TRUE!=CanUseSkillNow())
	{
		//InterruptSkillNow();
	}
	AI_Character* pAI = GetAIObj();
	if(NULL!=pAI)
	{
		pAI->Stop();
		rParams.SetIgnoreConditionCheckFlag(bPassSkillCheck);
		pAI->UseSkill(nID,nLevel,nTargetID,pos.m_fX,pos.m_fZ,fDir, INVALID_ID);	
	}
	__LEAVE_FUNCTION
	return;
}

BOOL 	Obj_Character::Skill_IsSkillCooldowned(SkillID_t nID)
{
__ENTER_FUNCTION
	SkillTemplateData_T const* pSkillTemplate = g_SkillTemplateDataMgr.GetInstanceByID(nID);
	if(NULL==pSkillTemplate)
	{
		return FALSE;
	}
	CooldownID_t nCooldownID = (CooldownID_t)(pSkillTemplate->GetCooldownID());
	if(INVALID_ID==nCooldownID || pSkillTemplate->IsAutoShotSkill())
	{
		if(0<GetAutoRepeatCooldown())
		{
			return FALSE;
		}
		return TRUE; //不存在冷却或已经冷却
	}
	else if(FALSE==IsCooldowned(nCooldownID))
	{
		return FALSE;//冷却中
	}
	return TRUE;
__LEAVE_FUNCTION
	return FALSE;
}

BOOL	Obj_Character::IsPrevCanViewMe( const Obj *pObj )
{
__ENTER_FUNCTION
	if(NULL==pObj)
	{
		return FALSE;
	}
	if(FALSE==IsCharacterObj(pObj->GetObjType()))
	{
		return FALSE;
	}
	if(TRUE==IsPartner((Obj_Character*)pObj))
	{
		return TRUE;
	}
	if(m_nView_PrevStealthLevel != 0)
	{
		Obj_Character * pCharacter = (Obj_Character*)pObj;
		BOOL bResult = CalcIsTargetStealth(pCharacter->GetPrevLevel(), pCharacter->GetPrevDetectLevel(), pCharacter->getWorldPos(),
			GetLevel(), GetStealthLevel(), getWorldPos());
		if(bResult)
		{
			return FALSE;
		}
	}
	return TRUE;
__LEAVE_FUNCTION
	return FALSE;
}

BOOL	Obj_Character::IsCanViewMe( const Obj *pObj )
{
__ENTER_FUNCTION
	if(NULL==pObj)
	{
		return FALSE;
	}
	if(FALSE==IsCharacterObj(pObj->GetObjType()))
	{
		return FALSE;
	}
	if(TRUE==IsPartner((Obj_Character*)pObj))
	{
		return TRUE;
	}
	if(InStealthMode())
	{
		Obj_Character * pCharacter = (Obj_Character*)pObj;
		BOOL bResult = CalcIsTargetStealth(pCharacter->GetLevel(), pCharacter->GetDetectLevel(), pCharacter->getWorldPos(),
			GetLevel(), GetStealthLevel(), getWorldPos());
		if(bResult)
		{
			return FALSE;
		}
	}
	return TRUE;
__LEAVE_FUNCTION
	return FALSE;
}
BOOL	Obj_Character::InStealthMode(VOID)
{
__ENTER_FUNCTION
	return 0<GetStealthLevel();
__LEAVE_FUNCTION
	return FALSE;
}

BOOL Obj_Character::Skill_CanUseThisSkillInThisStatus(SkillID_t nSkillID)
{
	__ENTER_FUNCTION
	if(INVALID_ID==nSkillID)
	{
		return FALSE;
	}
	Skill_Module::SkillTemplateData_T const* pSkillTemplate = g_SkillTemplateDataMgr.GetInstanceByID(nSkillID);
	if(NULL==pSkillTemplate)
	{
		return FALSE;
	}
	// 技能是否受到标记1限制
	if(TRUE==pSkillTemplate->GetDisableByFlag1())
	{
		if(FALSE==CanActionFlag1())
		{
			return FALSE;
		}
	}
	// 技能是否受到标记2限制
	if(TRUE==pSkillTemplate->GetDisableByFlag2())
	{
		if(FALSE==CanActionFlag2())
		{
			return FALSE;
		}
	}
	// 技能是否受到标记3限制
	if(TRUE==pSkillTemplate->GetDisableByFlag3())
	{
		if(INVALID_ID != GetMountID())
		{
			return FALSE;
		}
	}
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}

Obj* Obj_Character::Skill_CreateObjSpecial(WORLD_POS const& rPosition, INT nDataID)
{
	__ENTER_FUNCTION
	TargetingAndDepletingParams_T& rParams = GetTargetingAndDepletingParams();
	Obj_Special* pObjSpecial = NULL;
	Scene* pScene=getScene();
	if(NULL!=pScene)
	{
		pObjSpecial = (Obj_Special*)(pScene->NewObject(Obj::OBJ_TYPE_SPECIAL));
		if(NULL!=pObjSpecial)
		{
			_OBJ_SPECIAL_INIT initer;
			initer.m_nOwnerID = GetID();
			initer.m_nDataID = nDataID;
			initer.m_Pos = rPosition;
			pObjSpecial->Init(&initer);
		}
	}
	return pObjSpecial;
	__LEAVE_FUNCTION
	return NULL;
}
BOOL Obj_Character::Skill_RefixSkill(SkillInfo_T& rSkillInfo)
{
	__ENTER_FUNCTION
	if(Obj::OBJ_TYPE_MONSTER==GetObjType())
	{
		return TRUE;
	}
	if(Obj::OBJ_TYPE_HUMAN==GetObjType())
	{
		_SKILL_LIST& rList = ((Obj_Human*)this)->Skill_GetSkillList();

		BYTE rCount=rList.m_Count;
		SkillInfo_T PassiveSkill;
		for(INT i=0; rCount>i; ++i)
		{
			_OWN_SKILL& rSkill = rList.m_aSkill[i];
			BYTE level = rSkill.GetSkillLevel();

			PassiveSkill.Init();
			if(TRUE==g_SkillCore.InstanceSkill(PassiveSkill, *this, rSkill.m_nSkillID, level))
			{
				SkillLogic_T const* pLogic = Skill_GetLogic(PassiveSkill);
				if(NULL!=pLogic)
				{
					pLogic->Refix_SkillInstance(PassiveSkill, rSkillInfo);
				}
			}
		}
	}
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}
Obj_Character* Obj_Character::CreateGuard(UINT uDataID, INT nBaseAI /* = 0*/, INT nExtAI/* = 0*/)
{
	__ENTER_FUNCTION
	_OBJ_MONSTER_INIT	init;

	init.m_uDataID			=	uDataID;
	init.m_Pos.m_fX			=	getWorldPos()->m_fX - 3.f;
	init.m_Pos.m_fZ			=	getWorldPos()->m_fZ;
	init.m_RespawnTime		=	-1;
	init.m_BaseAI			=	nBaseAI;
	init.m_ExtAIScript		=   nExtAI;
	init.m_idScript			=	-1;

    Scene* pScene = getScene();
	if (!pScene) {
		return NULL;
	}

	pScene->GetMap()->VerifyPos(&(init.m_Pos) );
	if (FALSE == pScene->GetMap()->IsCanGo(init.m_Pos,0) )
	{
		init.m_Pos = *getWorldPos();
	}

	ObjID_t MonsterID = pScene->CreateTempMonster((const _OBJ_MONSTER_INIT*)&init);

	Obj* pObj = pScene->GetObjManager()->GetObj(MonsterID);
	if (pObj && pObj->GetObjType() == Obj::OBJ_TYPE_MONSTER)
	{
		((Obj_Monster*)pObj)->SetBaseCampID(GetBaseCampID() );
		//((Obj_Monster*)pObj)->SetCampType( GetCampType() );
		AI_Monster* pAI = (AI_Monster*)((Obj_Monster*)pObj)->GetAIObj();
		if (pAI)
		{
			pAI->SetSpeedyOfRecover(0.f);
		}
		return (Obj_Character*)pObj;
	}

	__LEAVE_FUNCTION
	return NULL;
}

static VOID BroadCast_HealAndDamageMsg(Obj_Character* pThis, Obj_Character* pTarget,GCDetailHealsAndDamages& rMsg)
{
	Obj_Human* pHuman = NULL;
	if(NULL!=pThis)
	{
		if(Obj::OBJ_TYPE_HUMAN==pThis->GetObjType())
		{
			//给玩家自己发消息	
			pHuman = (Obj_Human*)pThis;
			Player* pGamePlayer = pHuman->GetPlayer();
			if(NULL!=pGamePlayer)
			{
				pGamePlayer->SendPacket(&rMsg) ;
			}				
		}
		if(Obj::OBJ_TYPE_PET==pThis->GetObjType())
		{
			Obj_Human* pCreator = NULL;
			Obj_Pet* pPet = (Obj_Pet*)pThis;
			pCreator = pPet->GetCreator();
			if(pCreator != NULL)
			{
				Player* pGamePlayer = pCreator->GetPlayer();
				if(NULL!=pGamePlayer)
				{
					pGamePlayer->SendPacket(&rMsg) ;
				}
			}
		}
	}
	if(NULL!=pTarget)
	{
		if(Obj::OBJ_TYPE_HUMAN==pTarget->GetObjType())
		{
			pHuman = (Obj_Human*)pTarget;
			Player* pGamePlayer = pHuman->GetPlayer();
			if(NULL!=pGamePlayer)
			{
				pGamePlayer->SendPacket(&rMsg) ;
			}				
		}
		if(Obj::OBJ_TYPE_PET==pTarget->GetObjType())
		{
			Obj_Human* pCreator = NULL;
			Obj_Pet* pPet = (Obj_Pet*)pTarget;
			pCreator = pPet->GetCreator();
			Player* pGamePlayer = pCreator->GetPlayer();
			if(NULL!=pGamePlayer)
			{
				pGamePlayer->SendPacket(&rMsg) ;
			}				
		}
		
	}
}
