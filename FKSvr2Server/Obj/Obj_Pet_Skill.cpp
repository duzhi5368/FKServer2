#include "stdafx.h"
#include "Obj_Pet.h"
#include "Scene.h"
#include "Config.h"
#include "GameTable.h"
#include "Obj_Character.h"
#include "LogicManager.h"
#include "ObjManager.h"
#include "ItemOperator.h"
#include "ObjManager.h"
#include "GCCoolDownUpdate.h"

using namespace Combat_Module::Skill_Module;
using namespace Packets;

BOOL Obj_Pet::Skill_Apperceive(VOID)
{
__ENTER_FUNCTION

#define MULTIPLE_VALUE (1000)

	if (!GetConstCreator())	
	{
		return FALSE;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	// 利用领悟技能的规则最终决定是否领悟到未学的技能
	INT nSkillCount = Skill_GetMaxCount_CortrolByAI() + Skill_GetMaxCount_CortrolByPlayer();
	INT nLearnedVoluntarySkillCount = Skill_GetCount_CortrolByPlayer();
	INT nLearnedPassiveSkillCount = Skill_GetCount_CortrolByAI();
	
	for (INT i = 0; i < PET_APPERCEIVESKILLRATE_NUM; ++i)
	{
		if ( g_PetApperceiveSkillTbl[i].m_nSkillCount == nSkillCount
			&& g_PetApperceiveSkillTbl[i].m_nLearnedVoluntarySkillCount == nLearnedVoluntarySkillCount
			&& g_PetApperceiveSkillTbl[i].m_nLearnedPassiveSkillCount	== nLearnedPassiveSkillCount )
		{
			INT nVoluntaryRate = g_PetApperceiveSkillTbl[i].m_nApperceiveVoluntarySkillRate;
			INT nPassiveRate = nVoluntaryRate + g_PetApperceiveSkillTbl[i].m_nApperceivePassiveSkillRate;

			INT nRet = rand() % 100;
			nRet *= MULTIPLE_VALUE;
			if (nRet < nVoluntaryRate)
			{// 主动技能的领悟
				PET_ATTR* pAttr = g_PetAttrTbl.GetAttr(pPetItem->GetDataID());
				if (pAttr)
				{
					return Skill_ModifySkill_Realize( pAttr->m_VoluntarySkill );
				}
			}
			else if (nRet < nPassiveRate)
			{
				PET_ATTR* pAttr = g_PetAttrTbl.GetAttr(pPetItem->GetDataID());
				if (pAttr)
				{// 找到一个未学习的技能就将他加入SkillList中
					SkillID_t idSkill = INVALID_ID;
					if (pAttr->m_PassiveSkill1 != INVALID_ID && !Skill_HaveSkill(pAttr->m_PassiveSkill1,1))
						idSkill = pAttr->m_PassiveSkill1;
					else if (pAttr->m_PassiveSkill2 != INVALID_ID && !Skill_HaveSkill(pAttr->m_PassiveSkill2,1))
						idSkill = pAttr->m_PassiveSkill2;
					else if (pAttr->m_PassiveSkill3 != INVALID_ID && !Skill_HaveSkill(pAttr->m_PassiveSkill3,1))
						idSkill = pAttr->m_PassiveSkill3;
					else if (pAttr->m_PassiveSkill4 != INVALID_ID && !Skill_HaveSkill(pAttr->m_PassiveSkill4,1))
						idSkill = pAttr->m_PassiveSkill4;

					if ( idSkill != INVALID_ID )
					{
						return Skill_ModifySkill_Realize( idSkill );
					}
				}
			}
			else
			{// 什么都不做
				return FALSE;
			}

			break;
		}
	}

	return FALSE;

__LEAVE_FUNCTION

	return FALSE;
}

// 得到可以由玩家控制的法术的数量
INT Obj_Pet::Skill_GetCount_CortrolByPlayer(VOID)
{
	__ENTER_FUNCTION
	if (INVALID_ID == m_OwnerID)	
	{
		return FALSE;
	}

	Obj* pOwner = getScene()->GetObjManager()->GetObj(m_OwnerID);
	if (!pOwner || pOwner->GetObjType() != Obj::OBJ_TYPE_HUMAN)
	{
		return FALSE;
	}

	ItemContainer* pPetContainer = ((Obj_Human*)pOwner)->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	const _PET_SKILL *pPetSkill = Skill_GetSkill( PET_SKILL_INDEX_CONTROL_BY_PLAYER );
	if ( pPetSkill->m_nSkillID != INVALID_ID )
		return 1;
	else
		return 0;

	__LEAVE_FUNCTION
	return 0;
}

// 得到可以由玩家控制的法术的最大数量
INT Obj_Pet::Skill_GetMaxCount_CortrolByPlayer(VOID)
{
	return 1;
}

// 得到由AI控制的法术的数量
INT Obj_Pet::Skill_GetCount_CortrolByAI(VOID)
{
	__ENTER_FUNCTION
	if (INVALID_ID == m_OwnerID)	
	{
		return FALSE;
	}

	Obj* pOwner = getScene()->GetObjManager()->GetObj(m_OwnerID);
	if (!pOwner || pOwner->GetObjType() != Obj::OBJ_TYPE_HUMAN)
	{
		return FALSE;
	}

	ItemContainer* pPetContainer = ((Obj_Human*)pOwner)->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);


	INT nMaxAISkillCount = Skill_GetMaxCount_CortrolByAI();
	INT nCount = 0;
	for (INT i = PET_SKILL_INDEX_CONTROL_BY_AI0; i < PET_SKILL_INDEX_CONTROL_BY_AI0 + nMaxAISkillCount; ++i)
	{// 被动法攻，被动蕴含都属于被动技能
		const _PET_SKILL *pPetSkill = Skill_GetSkill( i );
		if ( pPetSkill->m_nSkillID != INVALID_ID )
		{
			nCount++;
		}
	}
	return nCount;

	__LEAVE_FUNCTION
	return 0;
}

// 得到由AI控制的法术的最大数量
INT Obj_Pet::Skill_GetMaxCount_CortrolByAI(VOID)
{
	__ENTER_FUNCTION
	if (INVALID_ID == m_OwnerID)	
	{
		return FALSE;
	}

	Obj* pOwner = getScene()->GetObjManager()->GetObj(m_OwnerID);
	if (!pOwner || pOwner->GetObjType() != Obj::OBJ_TYPE_HUMAN)
	{
		return FALSE;
	}

	ItemContainer* pPetContainer = ((Obj_Human*)pOwner)->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	PET_ATTR *pPetAttr = g_PetAttrTbl.GetAttr(pPetItem->GetDataID());
	if ( pPetAttr != NULL )
	{
		return pPetAttr->m_PassiveSkillCount;
	}
	return 0;

	__LEAVE_FUNCTION
	return 0;
}

VOID 	Obj_Pet::Impact_InitList(VOID)
{
	__ENTER_FUNCTION
	_IMPACT_LIST& rList = Impact_GetImpactList();
	BYTE& rCount=rList.m_Count;
	if(MAX_IMPACT_NUM<rCount)
	{
		AssertEx(FALSE,"[Obj_Character::Impact_InitList]: List.count > MAX_IMPACT_NUM! check it now");
		rCount=MAX_IMPACT_NUM;
	}
	Impact_SetSNSeed(rCount);
	
	for(short i=0; rCount>i; ++i)
	{
		rList.m_aImpacts[i].SetSN(i);
	}
	__LEAVE_FUNCTION
}
VOID	Obj_Pet::SetCooldown(CooldownID_t const nID, Time_t nCooldown)
{
	__ENTER_FUNCTION
	Obj_Human* pOwner = GetCreator();
	if (NULL==pOwner)	
	{
		m_PetDB.m_CooldownList.RegisterCooldown(nID, nCooldown);
		return;
	}
	else
	{
		ItemContainer* pPetContainer = GetCreator()->GetPetContain();
		Item* pPetItem = pPetContainer->GetItem(m_nIndex);
		Assert(pPetItem);

		pPetItem->SetCooldown(nID, nCooldown);
		GCCooldownUpdate Msg;
		Msg.SetPetGuid(pPetItem->GetPetGUID());
		Msg.CooldownModified(nID, nCooldown);
		Player* pPlayer = pOwner->GetPlayer();
		if(NULL != pPlayer)
		{
			pPlayer->SendPacket(&Msg) ;
		}
	}
	__LEAVE_FUNCTION
}
BOOL	Obj_Pet::IsCooldowned(CooldownID_t const nID) const
{
	__ENTER_FUNCTION
	if (!GetConstCreator())	
	{
		return m_PetDB.m_CooldownList.IsSpecificSlotCooldownedByID(nID);
	}
	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->IsCooldowned(nID);
	__LEAVE_FUNCTION
	return FALSE;
}
BOOL Obj_Pet::HeartBeat_Cooldown(UINT uTime)
{
	__ENTER_FUNCTION
	INT nDeltaTime = GetLogicTime();
	if (!GetConstCreator())	
	{
		m_PetDB.m_CooldownList.HeartBeat(nDeltaTime);
		return FALSE;
	}
	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);
	pPetItem->HeartBeat_Cooldown(nDeltaTime);

	__LEAVE_FUNCTION
	return TRUE;
}
Time_t Obj_Pet::GetCooldownRemained(CooldownID_t const nID) const
{
	__ENTER_FUNCTION
	if (!GetConstCreator())	
	{
		return m_PetDB.m_CooldownList.GetRemainTimeByID(nID);
	}
	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);
	return pPetItem->GetCooldownRemained(nID);
	__LEAVE_FUNCTION
	return 0;
}

BOOL	Obj_Pet::HeartBeat_Recover(UINT uTime)
{
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
		INT nRegenerate = GetHPRegenerate();
		if(nCur<nMax && 0<nRegenerate)
		{
			nCur += nRegenerate*nCount ;
			nCur<nMax?nCur:nCur=nMax;
			SetHP(nCur) ;
		}
	}
	return TRUE;
}

BOOL Obj_Pet::Skill_HaveSkill( SkillID_t const nID, BYTE const nLevel ) const
{
__ENTER_FUNCTION

	if ( nID == INVALID_ID )
	{
		Assert( FALSE && "Obj_Pet::Skill_HaveSkill nID == INVALID_ID" );
		return TRUE;
	}

	if (INVALID_ID == m_OwnerID)	
	{
		return FALSE;
	}

	Obj* pOwner = (const_cast<Obj_Pet*>(this))->getScene()->GetObjManager()->GetObj(m_OwnerID);
	if (!pOwner || pOwner->GetObjType() != Obj::OBJ_TYPE_HUMAN)
	{
		return FALSE;
	}

	ItemContainer* pPetContainer = ((Obj_Human*)pOwner)->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);
	
	for (INT i = 0; i < PET_MAX_SKILL_COUNT; ++i)
	{
		if (pPetItem->GetSkill(i).m_nSkillID == nID)
		{
			return TRUE;
		}
	}

	return FALSE;

__LEAVE_FUNCTION

	return FALSE;
}

const _PET_SKILL *Obj_Pet::Skill_GetSkill( INT nIndex ) const
{
__ENTER_FUNCTION

	if (INVALID_ID == m_OwnerID)	
	{
		return NULL;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	if ( nIndex >= PET_MAX_SKILL_COUNT )
	{
		Assert( FALSE && "Obj_Pet::Skill_GetSkill  nIndex < PET_MAX_SKILL_COUNT" );
		return NULL;
	}

	return &(pPetItem->GetSkill(nIndex));

__LEAVE_FUNCTION

	return NULL;
}

BOOL Obj_Pet::Skill_ModifySkill_Study(SkillID_t nID)
{
__ENTER_FUNCTION

	SkillTemplateData_T const* pSkillTemplateData = g_SkillTemplateDataMgr.GetInstanceByID(nID);
	if ( pSkillTemplateData == NULL )
	{
		return FALSE;
	}

	//验证是否是合法的技能ID
	for(INT i=0; PET_MAX_SKILL_COUNT>i; ++i)
	{
		const _PET_SKILL *pPetSkill = Skill_GetSkill( i );
		if(nID == pPetSkill->m_nSkillID)
		{
			return FALSE;
		}
	}

	// 玩家操作还是AI操作
	BOOL bContrlByPlayer = pSkillTemplateData->GetOperateModeForPetSkill();
	if ( bContrlByPlayer )
	{
		return Skill_RegisterSkill( nID, PET_SKILL_INDEX_CONTROL_BY_PLAYER );
	}
	else
	{
		INT nMaxAISkillNum = Skill_GetMaxCount_CortrolByAI();
		INT nNonAISkillNum = 0;
		INT nSkillIndex;
		for ( nSkillIndex = PET_SKILL_INDEX_CONTROL_BY_AI0; nSkillIndex < PET_SKILL_INDEX_CONTROL_BY_AI0 + nMaxAISkillNum; nSkillIndex++ )
		{
			const _PET_SKILL *pPetSkill = Skill_GetSkill( nSkillIndex );
			if(nID == pPetSkill->m_nSkillID)
			{
				nNonAISkillNum++;
			}
		}

		const _PET_STUDYSKILL *pStudySkill = g_PetStudySkillTbl.Get( nMaxAISkillNum, nNonAISkillNum );
		if ( pStudySkill != NULL )
		{
			INT nPercent = rand() % 100;
			if ( nPercent > pStudySkill->m_nNewPercent )
			{
				for ( nSkillIndex = PET_SKILL_INDEX_CONTROL_BY_AI0; nSkillIndex < PET_SKILL_INDEX_CONTROL_BY_AI0 + nMaxAISkillNum; nSkillIndex++ )
				{
					const _PET_SKILL *pPetSkill = Skill_GetSkill( nSkillIndex );
					if( pPetSkill->m_nSkillID == INVALID_ID )
					{
						return Skill_RegisterSkill( nID, nSkillIndex );
					}
				}
			}
			else
			{
				if(nNonAISkillNum > 0)
				{
					nSkillIndex = rand()%nNonAISkillNum;
					INT i;
					for ( i = PET_SKILL_INDEX_CONTROL_BY_AI0; i < PET_SKILL_INDEX_CONTROL_BY_AI0 + nMaxAISkillNum; i++ )
					{
						const _PET_SKILL *pPetSkill = Skill_GetSkill( nSkillIndex );
						if( pPetSkill->m_nSkillID != INVALID_ID )
						{
							if(nSkillIndex == i)
							{
								return Skill_RegisterSkill( nID, nSkillIndex );
							}
							i++;
						}
					}
				}
			}
		}
	}
	return FALSE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL Obj_Pet::Skill_ModifySkill_Realize(SkillID_t nID)
{
__ENTER_FUNCTION

	SkillTemplateData_T const* pSkillTemplateData = g_SkillTemplateDataMgr.GetInstanceByID(nID);
	if ( pSkillTemplateData == NULL )
	{
		return FALSE;
	}

	//验证是否是合法的技能ID
	for(INT i=0; PET_MAX_SKILL_COUNT>i; ++i)
	{
		const _PET_SKILL *pPetSkill = Skill_GetSkill( i );
		if( pPetSkill->m_nSkillID == nID )
		{
			return FALSE;
		}
	}

	// 玩家操作还是AI操作
	BOOL bContrlByPlayer = pSkillTemplateData->GetOperateModeForPetSkill();
	if ( bContrlByPlayer )
	{
		const _PET_SKILL *pPetSkill = Skill_GetSkill( PET_SKILL_INDEX_CONTROL_BY_PLAYER );
		if( pPetSkill->m_nSkillID == INVALID_ID )
			return Skill_RegisterSkill( nID, PET_SKILL_INDEX_CONTROL_BY_PLAYER );
	}
	else
	{
		INT nMaxAISkillNum = Skill_GetMaxCount_CortrolByAI();
		INT nSkillIndex;
		for ( nSkillIndex = PET_SKILL_INDEX_CONTROL_BY_AI0; nSkillIndex < PET_SKILL_INDEX_CONTROL_BY_AI0 + nMaxAISkillNum; nSkillIndex++ )
		{
			const _PET_SKILL *pPetSkill = Skill_GetSkill( nSkillIndex );
			if( pPetSkill->m_nSkillID == INVALID_ID )
			{
				return Skill_RegisterSkill( nID, nSkillIndex );
			}
		}
	}
	return FALSE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL Obj_Pet::Skill_ModifySkill_MenPai(SkillID_t nID)
{
__ENTER_FUNCTION

	SkillTemplateData_T const* pSkillTemplateData = g_SkillTemplateDataMgr.GetInstanceByID(nID);
	if ( pSkillTemplateData == NULL )
	{
		return FALSE;
	}

	const _PET_SKILL *pPetSkill = Skill_GetSkill( PET_SKILL_INDEX_MENPAI );
	if( pPetSkill->m_nSkillID == nID )
	{
		return FALSE;
	}

	return Skill_RegisterSkill( nID, PET_SKILL_INDEX_MENPAI );

__LEAVE_FUNCTION

	return FALSE;
}

BOOL Obj_Pet::Skill_HaveXinFa( SkillID_t const nID ) const
{
	return TRUE;
}
BOOL Obj_Pet::Skill_SetXinFaLevel(SkillID_t const nID, INT const nLevel)
{
	return TRUE;
}
INT Obj_Pet::Skill_GetXinFaLevel(SkillID_t const nID)const
{
	return 1;
}
VOID 	Obj_Pet::Skill_OnEquipItem(VOID)
{
}
//
//VOID	Obj_Pet::Skill_InitSkillList()
//{
//	_SKILL_LIST& rList= m_SkillList;
//	rList.CleanUp();
//}
BOOL 	Obj_Pet::Skill_RegisterSkill(SkillID_t const nID, INT nIndex)
{
	__ENTER_FUNCTION

	if (INVALID_ID == m_OwnerID)	
	{
		return FALSE;
	}

	Obj* pOwner = getScene()->GetObjManager()->GetObj(m_OwnerID);
	if (!pOwner || pOwner->GetObjType() != Obj::OBJ_TYPE_HUMAN)
	{
		return FALSE;
	}

	ItemContainer* pPetContainer = ((Obj_Human*)pOwner)->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	SkillTemplateData_T const* pSkillTemplateData = g_SkillTemplateDataMgr.GetInstanceByID(nID);
	if ( pSkillTemplateData == NULL )
	{
		Assert( FALSE && "Obj_Pet::Skill_RegisterSkill  pSkillTemplateData == NULL" );
		return FALSE;
	}

	if ( nIndex >= PET_MAX_SKILL_COUNT )
	{
		Assert( FALSE && "Obj_Pet::Skill_RegisterSkill  nIndex < PET_MAX_SKILL_COUNT" );
		return FALSE;
	}

	_PET_SKILL skill;
	skill.m_nSkillID = nID;
	g_ItemOperator.SetSkill(pPetContainer, m_nIndex, nIndex, skill);

	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}
BOOL 	Obj_Pet::Skill_UnregisterSkill(SkillID_t const nID, INT nIndex)
{
	__ENTER_FUNCTION
	if (INVALID_ID == m_OwnerID)	
	{
		return FALSE;
	}

	Obj* pOwner = getScene()->GetObjManager()->GetObj(m_OwnerID);
	if (!pOwner || pOwner->GetObjType() != Obj::OBJ_TYPE_HUMAN)
	{
		return FALSE;
	}

	ItemContainer* pPetContainer = ((Obj_Human*)pOwner)->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	SkillTemplateData_T const* pSkillTemplateData = g_SkillTemplateDataMgr.GetInstanceByID(nID);
	if ( pSkillTemplateData != NULL )
	{
		Assert( FALSE && "Obj_Pet::Skill_UnregisterSkill  pSkillTemplateData == NULL" );
		return FALSE;
	}

	if ( nIndex >= PET_MAX_SKILL_COUNT )
	{
		Assert( FALSE && "Obj_Pet::Skill_UnregisterSkill  nIndex < PET_MAX_SKILL_COUNT" );
		return FALSE;
	}

	_PET_SKILL skill;
	g_ItemOperator.SetSkill(pPetContainer, m_nIndex, nIndex, skill);

	return TRUE;

	__LEAVE_FUNCTION
	return FALSE;
}


