#include "stdafx.h"
// Obj_Pet.cpp

#include "DB_Struct.h"

#include "Scene.h"
#include "ObjManager.h"

#include "AI_Pet.h"
#include "Skill_Core.h"

#include "GCManipulatePetRet.h"
#include "GCLevelUp.h"

#include "Obj_Pet.h"
#include "Obj_Pet.inl"
#include "PetManager.h"
#include "GameTable.h"
#include "TimeManager.h"
#include "HumanPetContainer.h"
#include "ActionDelegator.h"
#include "StdImpact051.h"


using namespace Packets;
using namespace Action_Module;
using namespace Combat_Module::Impact_Module;

_PET_ATTR_BACKUP::_PET_ATTR_BACKUP( VOID )
{
	m_bNameModified			= FALSE;
	m_bTitleModified		= FALSE;
	m_HP					= -1;
	m_MP					= -1;
	m_MaxHp					= -1;
	m_MaxMp					= -1;
	m_MoveSpeed				= 0.f;
	//m_CampData.CleanUp();
	m_nOwnerID				= INVALID_ID;
	//m_SpouseGUID.Reset();
	m_nAIType				= -1;
	m_Level					= -1;

	m_nDataID				= INVALID_ID;
	m_nModelID				= INVALID_ID;
	m_nMountID				= INVALID_ID;

	//m_GUID.Reset();
	m_nLife					= -1;
	m_byGeneration			= 0;
	m_byHappiness			= 0;

	m_nAtt_Physics			= -1;
	m_nAtt_Magic			= -1;
	m_nDef_Physics			= -1;
	m_nDef_Magic			= -1;
	m_nHit					= -1;
	m_nMiss					= -1;

	m_nExp					= -1;

	m_StrPerception			= -1;
	m_ConPerception			= -1;
	m_DexPerception			= -1;
	m_SprPerception			= -1;
	m_IntPerception			= -1;
	m_GenGu					= -1;

	m_Str					= -1;
	m_Con					= -1;
	m_Dex					= -1;
	m_Spr					= -1;
	m_Int					= -1;

	m_nRemainPoint			= -1;
	m_nCampType				= INVALID_CAMP;
}

VOID _PET_ATTR_BACKUP::CleanUp( VOID )
{
	m_bNameModified			= FALSE;
	m_bTitleModified		= FALSE;
	m_HP					= -1;
	m_MP					= -1;
	m_MaxHp					= -1;
	m_MaxMp					= -1;
	m_MoveSpeed				= 0.f;
	m_CampData.CleanUp();
	m_nOwnerID				= INVALID_ID;
	m_SpouseGUID.Reset();
	m_nAIType				= -1;
	m_Level					= -1;

	m_nDataID				= INVALID_ID;
	m_nModelID				= INVALID_ID;
	m_nMountID				= INVALID_ID;

	m_GUID.Reset();
	m_nLife					= -1;
	m_byGeneration			= 0;
	m_byHappiness			= 0;

	m_nAtt_Physics			= -1;
	m_nAtt_Magic			= -1;
	m_nDef_Physics			= -1;
	m_nDef_Magic			= -1;
	m_nHit					= -1;
	m_nMiss					= -1;

	m_nExp					= -1;

	m_StrPerception			= -1;
	m_ConPerception			= -1;
	m_DexPerception			= -1;
	m_SprPerception			= -1;
	m_IntPerception			= -1;
	m_GenGu					= -1;

	m_Str					= -1;
	m_Con					= -1;
	m_Dex					= -1;
	m_Spr					= -1;
	m_Int					= -1;

	m_nRemainPoint			= -1;
	m_nCampType				= INVALID_CAMP;
}

Obj_Pet::Obj_Pet( VOID )
{
__ENTER_FUNCTION

	INT i;

	// 消息/属性刷新
	//m_AttrBackUp.CleanUp();

	// 快乐度变化规则
	//m_HappinessTimer.CleanUp();

	// 寿命变化规则
	//m_LifeTimer.CleanUp();

	// 效果
	//m_ImpactList.CleanUp();

	// Capturer
	m_nCapturerCount	= 0;
	for ( i = 0; i < MAX_CAPTURER_NUM; i++ )
	{
		m_aCapturer[i]	= INVALID_ID;
	}
	// aCacheOfSkill
	for (i = 0; i < HUMAN_PET_MAX_COUNT; ++i)
	{
		m_aCacheOfSkill[i] = INVALID_ID;
	}

	// AI
	m_OwnerID			= INVALID_ID;
	m_TargetID			= INVALID_ID;
	m_RespawnPos		= WORLD_POS( -1.f, -1.f );
	m_RespawnTime		= 0;

	// 一级属性
	m_GUID				= INVALID_GUID;
	m_PetDB.CleanUp();
	m_CreatorID			= INVALID_ID;
	m_pCreator			= NULL;
	m_nIndex			= -1;
	//m_nCampType			= INVALID_CAMP;

	m_pAI_Character		= new AI_Pet;
	Assert( m_pAI_Character ); 

__LEAVE_FUNCTION
}

Obj_Pet::~Obj_Pet( VOID )
{
__ENTER_FUNCTION


__LEAVE_FUNCTION
}

VOID Obj_Pet::CleanUp( )
{
__ENTER_FUNCTION

	INT i;

	// 消息/属性刷新
	m_AttrBackUp.CleanUp();

	// 快乐度变化规则
	m_HappinessTimer.CleanUp();

	// 寿命变化规则
	m_LifeTimer.CleanUp();

	// 效果
	m_ImpactList.CleanUp();

	// Capturer
	m_nCapturerCount	= 0;
	for ( i = 0; i < MAX_CAPTURER_NUM; i++ )
	{
		m_aCapturer[i]	= INVALID_ID;
	}

	// aCacheOfSkill
	for (i = 0; i < HUMAN_PET_MAX_COUNT; ++i)
	{
		m_aCacheOfSkill[i] = INVALID_ID;
	}
	// AI
	m_OwnerID			= INVALID_ID;
	m_TargetID			= INVALID_ID;
	m_RespawnPos		= WORLD_POS( -1.f, -1.f );
	m_RespawnTime		= 0;

	// 一级属性
	m_GUID				= INVALID_GUID;
	m_CreatorID			= INVALID_ID;
	m_pCreator			= NULL;
	m_PetDB.CleanUp();
	m_nIndex			= -1;
	//m_nCampType			= INVALID_CAMP;

	//m_pAI_Character

	Obj_Character::CleanUp();

__LEAVE_FUNCTION
}

BOOL Obj_Pet::Init( const _OBJ_INIT *pInit )
{
__ENTER_FUNCTION

	BOOL bResult = Obj_Character::Init( pInit );
	if ( !bResult )
		return FALSE;

	const _OBJ_PET_INIT *pPetInit  = NULL;
	pPetInit = (const _OBJ_PET_INIT*)pInit;
	if ( pPetInit == NULL )
	{
		Assert( FALSE &&  "Error Obj_Pet::Init, pPetInit = NULL" );
		return FALSE;
	}

	m_GUID				= pPetInit->m_GUID;
	m_CreatorID			= pPetInit->m_CreatorID;
	m_pCreator			= NULL;
	m_nIndex			= pPetInit->m_nIndex;
	m_ScriptID			= pPetInit->m_ScriptID ;
	if ( m_CreatorID != INVALID_ID )
	{
		Obj_Character *pCreator	= (Obj_Character*)(getScene()->GetObjManager()->GetObj(m_CreatorID) );
		if (pCreator != NULL && pCreator->GetObjType() == OBJ_TYPE_HUMAN)
			m_pCreator = (Obj_Human*)pCreator;
	}

	if ( m_pCreator == NULL )
		m_PetDB = pPetInit->m_PetDB;

	m_RespawnTime		= pPetInit->m_RespawnTime;
	m_RespawnPos		= pPetInit->m_Pos;
	m_OwnerID			= pPetInit->m_CreatorID;
	//m_nCampType			= INVALID_CAMP;

	m_HappinessTimer.BeginTimer( g_Config.m_ConfigInfo.m_PetHappinessInterval, g_pTimeManager->CurrentTime() );
	m_LifeTimer.BeginTimer( g_Config.m_ConfigInfo.m_PetLifeInterval, g_pTimeManager->CurrentTime() );

	// 如果招呼者有效则将该宠物所有的技能缓存起来
	if (m_pCreator)
	{
		Item* pPetItem = m_pCreator->GetPetItem(GetPetGUID());
		Assert(pPetItem);
		// 设置AI类型
		SetAIType(pPetItem->GetAIType() );
		for (INT i = 0; i < PET_MAX_SKILL_COUNT; ++i)
		{
			PushSkillToCache(pPetItem->GetSkill(i).m_nSkillID);
		}

		//if( m_pCreator->GetCampData() )
		//{
		//	if( m_pCreator->GetCampData()->m_nCampID == CAMP_1 )
		//		m_nCampType = CAMP1_PET;
		//	else if( m_pCreator->GetCampData()->m_nCampID == CAMP_2 )
		//		m_nCampType = CAMP2_PET;
		//}
	}
	else
	{// 在pet初始化的时候就生成宠物的所有属性(只有没有主人的宠物第一次生成时才构造所有属性)
		getScene()->GetPetManager()->MakeCapturePetAttrib(&m_PetDB);
		SetDataID(m_PetDB.m_nDataID); // 可能产生了变异,模型可能会改变
	}

	// 使AI进入IDLE状态
	GetAIObj()->ChangeState(ESTATE_IDLE);

    InitBackupAttr();
	//附加效果数据
	Impact_InitList();

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

VOID Obj_Pet::InitAIObj( )
{
__ENTER_FUNCTION
	Assert( m_pAI_Character );
	m_pAI_Character->Init( this );
__LEAVE_FUNCTION
}

BOOL Obj_Pet::HeartBeat( UINT uTime/* = 0*/ )
{
__ENTER_FUNCTION

	BOOL bResult = Obj_Character::HeartBeat( uTime );
	if ( !bResult )
		return FALSE;

	HeartBeat_Happiness( uTime );
	HeartBeat_Life(uTime);

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL Obj_Pet::HeartBeat_Happiness( UINT uTime/* = 0*/ )
{
__ENTER_FUNCTION

	if ( m_HappinessTimer.CountingTimer( uTime ) )
	{
		if ( GetHappiness() > 0 )
		{
			SetHappiness( GetHappiness() - 1 );
		}
	}

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL Obj_Pet::HeartBeat_Life( UINT uTime/* = 0*/ )
{
__ENTER_FUNCTION

	if ( m_LifeTimer.CountingTimer( uTime ) )
	{
		if ( GetLife() > 0 )
		{
			SetLife( GetLife() - 1 );
		}
	}

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL Obj_Pet::IsEnemy(Obj_Character* pCharacter )
{
	__ENTER_FUNCTION

	Obj_Character *pOwner = GetOwner();
	if(GetID()==pCharacter->GetID())
	{
		return FALSE;
	}
	if(pOwner != NULL)
	{
		if(pOwner->GetID()==pCharacter->GetID())
		{
			return FALSE;
		}
		return pOwner->IsEnemy(pCharacter);
	}
	else
	{
		SOT_ShadowGuard_T logic;
		OWN_IMPACT* pImp = Impact_GetFirstImpactOfSpecificLogicID(logic.ID);
		if(NULL!=pImp)
		{
			Obj* pObj = (Obj*)( (GetSpecificObjInSameSceneByID(logic.GetSummonerID(*pImp))) );
			if(NULL!=pObj)
			{
				if(TRUE == IsCharacterObj(pObj->GetObjType()))
				{
					Obj_Character& rSummoner = *static_cast<Obj_Character*>(pObj);
					return rSummoner.IsEnemy(pCharacter);
				}
			}
		}
		Assert( pCharacter );
		BOOL bIsEnemy = IsEnemyCamp(*pCharacter);
		return bIsEnemy;
	}
	__LEAVE_FUNCTION

	return FALSE;
}
BOOL Obj_Pet::IsFriend(Obj_Character* pCharacter )
{
__ENTER_FUNCTION
	
	Obj_Character *pOwner = GetOwner();
	if(pOwner != NULL)
	{
		return pOwner->IsFriend(pCharacter);
	}
	else
	{
		Assert( pCharacter );
		return FALSE==IsEnemy(pCharacter);
	}
__LEAVE_FUNCTION

	return FALSE;
}
BOOL Obj_Pet::IsPartner(Obj_Character* pCharacter )
{
__ENTER_FUNCTION
	if(NULL==pCharacter)
	{
		return FALSE;
	}
	if(GetID()==pCharacter->GetID())
	{
		return TRUE;
	}
	Obj_Character *pOwner = GetOwner();
	if(pOwner != NULL)
	{
		return pOwner->IsPartner(pCharacter);
	}
	else
	{
		return FALSE;
	}
	return FALSE;

__LEAVE_FUNCTION

	return FALSE;
}

Obj_Character *Obj_Pet::GetOwner( VOID )
{
	Obj_Character *pCharacter = NULL;
	ObjID_t idOwner = GetOwnerID();
	if ( idOwner != INVALID_ID && getScene() != NULL )
	{
		pCharacter = (Obj_Character*)(getScene()->GetObjManager()->GetObj( idOwner ));
	}

	return pCharacter;
}

VOID Obj_Pet::ToAttack( ObjID_t TargetID )
{
__ENTER_FUNCTION

	if (INVALID_ID != TargetID && m_TargetID == TargetID) {
		return ;
	}

	m_TargetID = TargetID;
	
	AI_Pet* pAIPet = (AI_Pet*)GetAIObj();
	if (pAIPet)
	{
		pAIPet->BabyToAttack();
	}

__LEAVE_FUNCTION
}

BOOL Obj_Pet::PushSkillToCache(INT idSkill)
{
__ENTER_FUNCTION
	INT i;
	for ( i = 0; i < HUMAN_PET_MAX_COUNT; ++i)
	{
		if (INVALID_ID == m_aCacheOfSkill[i])
		{
			m_aCacheOfSkill[i] = idSkill;
			break;
		}
	}

	if (HUMAN_PET_MAX_COUNT == i)
	{
		return FALSE;
	}
	return TRUE;

__LEAVE_FUNCTION
	return FALSE;
}

VOID Obj_Pet::GetRateOfBuffTakeEffect(INT idSkill, INT& rateOfBuffTakeEffect)
{
__ENTER_FUNCTION
	const SkillTemplateData_T* pSkillData_T = g_SkillTemplateDataMgr.GetInstanceByID(idSkill);
	if (!pSkillData_T)
	{
		Assert(NULL && "Obj_Pet::GetRateOfBuffTakeEffect...pSkillData_T=NULL...");
		return ;
	}
	ID_t TypeOfSkill = pSkillData_T->GetTypeOfPetSkill();
	Obj_Human* pCreator = GetCreator();
	if (pCreator) {
		ItemContainer* pItemContainer = pCreator->GetPetContain();
		Assert(pItemContainer);
		Item* pItem = pItemContainer->GetItem(m_nIndex);
		Assert(pItem);
		
		INT nAIType = pItem->GetAIType();

		if (nAIType < 0 || nAIType > PET_AITYPE)
			return ;
		if (TypeOfSkill < 0 || TypeOfSkill > PET_SKILL_TYPE)
			return ;
		FLOAT fLaunchRate = g_PetAIStrategyTble[TypeOfSkill][nAIType];
		rateOfBuffTakeEffect = (INT)(rateOfBuffTakeEffect * fLaunchRate);
	}

__LEAVE_FUNCTION
}

VOID Obj_Pet::LevelUp(VOID)
{
	__ENTER_FUNCTION
	if (INVALID_ID == m_OwnerID)	
	{
		return ;
	}

	Obj* pOwner = getScene()->GetObjManager()->GetObj(m_CreatorID);
	if (!pOwner || pOwner->GetObjType() != Obj::OBJ_TYPE_HUMAN)
	{
		return ;
	}

	ItemContainer* pPetContainer = ((Obj_Human*)pOwner)->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	INT nLevel = GetLevel() + 1;
	if (nLevel == PET_LEVEL_NUM)
	{
		return ;
	}
	SetLevel(nLevel);

	// 设置宠物相关属性

	// 所有一级属性加1
	SetBaseStr(GetBaseStr() + 1);
	SetBaseSpr(GetBaseSpr() + 1);
	SetBaseCon(GetBaseCon() + 1);
	SetBaseInt(GetBaseInt() + 1);
	SetBaseDex(GetBaseDex() + 1);
	SetRemainPoint(pPetItem->GetRemainPoint()+5);

	// 一定要先设置MaxHP:)
	SetHP(GetMaxHP());
	SetHappiness( 100 );

	// 调用宠物的领悟技能函数
	Skill_Apperceive();

	GCLevelUp	msgLevelUp;
	msgLevelUp.setObjId(GetID());
	msgLevelUp.setLevel(GetLevel());

	getScene()->BroadCast(&msgLevelUp, this, TRUE);

	__LEAVE_FUNCTION
}

VOID Obj_Pet::SetReliveInfo( BOOL bSkillRelive, const _RELIVE_INFO *pReliveInfo )
{
	__ENTER_FUNCTION
	if ( pReliveInfo == NULL )
	{
		Assert( pReliveInfo != NULL && "Obj_Pet::SetReliveInfo" );
		return;
	}

	Obj_Character::SetReliveInfo(bSkillRelive, pReliveInfo);
	
	__LEAVE_FUNCTION
}

BOOL Obj_Pet::AddCapturer(ObjID_t idObj)
{
	__ENTER_FUNCTION
	INT i;
	for (i = 0; i < MAX_CAPTURER_NUM; ++i)
	{
		if (m_aCapturer[i] == INVALID_ID)
		{
			m_aCapturer[i] = idObj;
			++m_nCapturerCount;
			return TRUE;
		}
	}
	
	if (i == MAX_CAPTURER_NUM)
		return FALSE;

	return TRUE;
	__LEAVE_FUNCTION
	return TRUE;
}

BOOL Obj_Pet::DelCapturer(ObjID_t idObj)
{
	__ENTER_FUNCTION
	INT i;
	for (i = 0; i < MAX_CAPTURER_NUM; ++i)
	{
		if (m_aCapturer[i] == idObj)
		{
			m_aCapturer[i] = INVALID_ID;
			--m_nCapturerCount;
			if (m_nCapturerCount < 0)
				m_nCapturerCount = 0;
			return TRUE;
		}
	}
	
	if (i == MAX_CAPTURER_NUM)
		return FALSE;

	return TRUE;
	__LEAVE_FUNCTION
	return TRUE;

}

VOID Obj_Pet::SendCaptureFailedToOthers(ObjID_t idObj)
{
	__ENTER_FUNCTION
	GCManipulatePetRet msg;
	for (INT i = 0; i < MAX_CAPTURER_NUM; ++i)
	{
		if (INVALID_ID != m_aCapturer[i] && m_aCapturer[i] != idObj)
		{
			Scene* pScene = getScene();
			if (!pScene)
			{
				m_nCapturerCount = 0;
				return ;
			}
			ObjManager* pObjMgr = pScene->GetObjManager();
			if (!pObjMgr)
				return ;
			Obj* pObj = pObjMgr->GetObj(m_aCapturer[i]);
			if (pObj && pObj->GetObjType() == Obj::OBJ_TYPE_HUMAN)
			{
				Obj_Human* pHuman = (Obj_Human*)pObj;
				if (pHuman)
				{
					GetGlobalActionDelegator().InterruptCurrentAction(*pHuman);
					msg.SetManipulateRet(GCManipulatePetRet::MANIPULATEPET_RET_CAPTUREFALID);

					AI_Character* pAIHuman = pHuman->GetAIObj();
					if (pAIHuman)
					{
						pAIHuman->Stop();
					}

					pHuman->GetPlayer()->SendPacket(&msg);
				}
			}
		}
	}
	__LEAVE_FUNCTION
}

VOID Obj_Pet::OnExecuteScriptTimer(UINT uTime)
{
	__ENTER_FUNCTION

	if( m_ScriptID==INVALID_ID )
		return ;

	Scene* pScene = getScene() ;
	if( pScene == NULL )
		return ;

	SceneID_t SceneID = pScene->SceneID() ;
	ObjID_t ObjID = GetID() ;
	INT DataID = GetDataID() ;

	pScene->GetLuaInterface()->ExeScript_DDDD( 
		m_ScriptID, 
		"OnCharacterTimer", 
		SceneID,
		ObjID,
		DataID,
		uTime ) ;


	__LEAVE_FUNCTION
}
