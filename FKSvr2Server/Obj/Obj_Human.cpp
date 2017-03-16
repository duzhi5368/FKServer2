#include "stdafx.h"

#include "AI_Human.h"
#include "AI_Pet.h"
#include "PlayerPool.h"
#include "PacketFactoryManager.h"
#include "ServerManager.h"
#include "GCNewPlayer.h"
#include "GCNewPlayer_Death.h"
#include "GCNewPlayer_Move.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GCOtherAttack.h"
#include "GCErrorAttack.h"
#include "GCOperateResult.h"
#include "Config.h"
#include "Obj_Monster.h"
#include "GCErrorSkill.h"
#include "GCOtherSkill.h"
#include "GameTable.h"
#include "GCSkillPrepare.h"
#include "GCLevelUp.h"
#include "AreaManager.h"
#include "GCDetailEquipList.h"
#include "GCCharStopAction.h"
#include "GCChat.h"

#include "GCMissionAdd.h"
#include "GCMissionRemove.h"
#include "GCMissionModify.h"
//#include "GCAddCanPickMissionItem.h"
//#include "GCRemoveCanPickMissionItem.h"

#include "ItemManager.h"
#include "ItemRuler.h"
#include "GCDiscardItemResult.h"
#include "AbilityManager.h"
#include "Ability.h"
#include "Obj_Platform.h"
#include "Obj_Pet.h"

#include "WGRetUserData.h"
#include "GWCallOfHuman.h"
#include "GCAbilityResult.h"
#include "GCAbilityAction.h"
#include "GCCoolDownUpdate.h"
#include "GCDetailXinFaList.h"
#include "GCDetailSkillList.h"
#include "GWCityOpt.h"
#include "TimeManager.h"
#include "GCNotifyEquip.h"
#include "AvoidOverlap.h"
#include "GCItemInfo.h"
#include "Obj_Character.h"
#include "ScriptDef.h"
#include "HumanItemLogic.h"
#include "ItemOperator.h"
#include "GCDetailAttrib_Pet.h"
#include "GCCharBaseAttrib.h"
#include "GCReturnTeamFollow.h"
#include "GWStopTeamFollow.h"
#include "GCTeamFollowList.h"
#include "Obj_Pet.h"
#include "GCNotifyChangeScene.h"
#include "PetManager.h"
#include "GCManipulatePetRet.h"
#include "GCRemovePet.h"
#include "SkillInfo.h"

#include "HumanDB.h"
#include "AvoidOverlap.h"
#include "ShopManager.h"
#include "Team.h"

#include "ExchangBox.h"			//交易盒
#include "StallBox.h"			//摊位盒
#include "GWCityApplyNewCity.h" //申请建立城市
#include "GWCityClose.h" //申请建立城市
#include "GCCharAllTitles.h"
#include "HumanItemContainer.h"
#include "HumanPetContainer.h"

#include "Attributes.h"
#include "HumanRelation.h"

#include "Obj_Human.h"
#include "Obj_Human.inl"
#include "GWLevelUp.h"
#include "GCLevelUpResult.h"
#include "GWChangeMenpai.h"
#include "ActionDelegator.h"
#include "ScriptLogic.h"
#include "LogDefine.h"
#include "GWUpdateTitle.h"
#include "GameStruct_Pet.h"
#include "GCNotifyGoodBad.h"
#include "GCCharFirstLogin.h"


//////////////////////////////////////////////////////
// 与客户端同步备份数据
//////////////////////////////////////////////////////
_HUMAN_ATTR_BACKUP::_HUMAN_ATTR_BACKUP(VOID)
{
	m_bNameModified		= FALSE;
	m_bTitleModified	= FALSE;
	m_Level				= -1;
	m_Exp				= -1;
	m_HP				= -1;
	m_MP				= -1;
	m_MaxHp				= -1;
	m_MaxMp				= -1;
	m_MoveSpeed			= -1;
	m_nDataID			= INVALID_ID;
	m_nPortraitID		= INVALID_ID;
	m_nModelID			= INVALID_ID;
	m_nMountID			= INVALID_ID;
	m_uFaceMeshID		= INVALID_ID;
	m_uHairMeshID		= INVALID_ID;
	m_uHairColor		= 0xFFFFFFFF;
	m_nStealthLevel		= -1;
	m_nMoodState		= INVALID_MOOD_STATE;

	m_Money				= -1;
	m_nStr				= -1;
	m_nSpr				= -1;
	m_nCon				= -1;
	m_nInt				= -1;
	m_nDex				= -1;
	m_nPointRemain		= -1;

	m_nReHpSpeed		= -1;
	m_nReMpSpeed		= -1;
	m_nAttPhysics		= -1;
	m_nAttMagic			= -1;
	m_nDefPhysics		= -1;
	m_nDefMagic			= -1;
	m_nHit				= -1;
	m_nMiss				= -1;
	m_nCritic			= -1;

	m_nRage				= -1;
	m_nStrikePoint		= -1;

	m_nAttSpeed			= -1;

	m_nAttCold			= -1;
	m_nDefCold			= -1;
	m_nAttFire			= -1;
	m_nDefFire			= -1;
	m_nAttLight			= -1;
	m_nDefLight			= -1;

	m_nAttPoison		= -1;
	m_nDefPoison		= -1;
	m_nMenpai			= -1;
	//m_CampData
	m_nOwnerID			= INVALID_ID;
	//m_guidCurrentPet

	m_RMBMoney			= 0;
	m_BankRMB			= -1;
	m_DoubleExpTime_Num	= 1;
	m_GmRight			= 0;

	m_bLimitMove		= FALSE;
	m_bCanActionFlag1	= FALSE;
	m_bCanActionFlag2	= FALSE;

	m_bMissionHaveDoneFlagsChanged	= FALSE;

	m_bWeaponModified	= FALSE;
	m_bCapModified		= FALSE;
	m_bArmorModified	= FALSE;
	m_bCuffModified		= FALSE;
	m_bBootModified		= FALSE;
	m_bSashModified		= FALSE;

	m_bStallIsOpen		= FALSE;
	m_bStallNameChanged	= FALSE;

	m_GuildID			=	INVALID_ID;

	//m_nCampType			= INVALID_CAMP;
}

VOID _HUMAN_ATTR_BACKUP::CleanUp(VOID)
{
	m_bNameModified		= FALSE;
	m_bTitleModified	= FALSE;
	m_Level				= -1;
	m_Exp				= -1;
	m_HP				= -1;
	m_MP				= -1;
	m_MaxHp				= -1;
	m_MaxMp				= -1;
	m_MoveSpeed			= -1;
	m_nDataID			= INVALID_ID;
	m_nPortraitID		= INVALID_ID;
	m_nModelID			= INVALID_ID;
	m_nMountID			= INVALID_ID;
	m_uFaceMeshID		= INVALID_ID;
	m_uHairMeshID		= INVALID_ID;
	m_uHairColor		= 0xFFFFFFFF;
	m_nStealthLevel		= -1;
	m_nMoodState		= INVALID_MOOD_STATE;

	m_Money				= -1;
	//m_RMBMoney			= -1;
	m_nStr				= -1;
	m_nSpr				= -1;
	m_nCon				= -1;
	m_nInt				= -1;
	m_nDex				= -1;
	m_nPointRemain		= -1;

	m_nReHpSpeed		= -1;
	m_nReMpSpeed		= -1;
	m_nAttPhysics		= -1;
	m_nAttMagic			= -1;
	m_nDefPhysics		= -1;
	m_nDefMagic			= -1;
	m_nHit				= -1;
	m_nMiss				= -1;
	m_nCritic			= -1;

	m_nRage				= -1;
	m_nStrikePoint		= -1;

	m_nAttSpeed			= -1;

	m_nAttCold			= -1;
	m_nDefCold			= -1;
	m_nAttFire			= -1;
	m_nDefFire			= -1;
	m_nAttLight			= -1;
	m_nDefLight			= -1;

	m_nAttPoison		= -1;
	m_nDefPoison		= -1;
	m_nMenpai			= -1;
	m_CampData.CleanUp();
	m_nOwnerID			= INVALID_ID;
	m_guidCurrentPet.Reset();

	m_RMBMoney			= 0;
	m_BankRMB			= -1;
	m_DoubleExpTime_Num	= 1;
	m_GmRight			= 0;

	m_bLimitMove		= FALSE;
	m_bCanActionFlag1	= FALSE;
	m_bCanActionFlag2	= FALSE;

	m_bMissionHaveDoneFlagsChanged	= FALSE;

	m_bWeaponModified	= FALSE;
	m_bCapModified		= FALSE;
	m_bArmorModified	= FALSE;
	m_bCuffModified		= FALSE;
	m_bBootModified		= FALSE;
	m_bSashModified		= FALSE;

	m_bStallIsOpen		= FALSE;
	m_bStallNameChanged	= FALSE;

	m_GuildID			=	INVALID_ID;
	//m_nCampType			= INVALID_CAMP;
}

using namespace Combat_Module;
using namespace Action_Module;
using namespace Script_Module;
using namespace Combat_Module::Skill_Module;

extern ENUM_REFESH_ATTR_TYPE CalcRefeshAttrType(Obj_Character *pSour, Obj_Character *pTarget );

Obj_Human::Obj_Human( )
{
	__ENTER_FUNCTION

		m_pHumanNode = new _OBJ_LIST_NODE(this) ;
	Assert( m_pHumanNode ) ;

	m_bCanSkillRelive = FALSE;
	//m_DefaultReliveInfo.Reset();
	//m_SkillReliveInfo.Reset();

	m_EquipVer	=	0;

	//m_uMissionIndex_KillObjectEvent_Num	= 0;
	//m_uMissionIndex_EnterAreaEvent_Num		= 0;
	//m_uMissionIndex_ItemChangedEvent_Num	= 0;

	//////////////////////////////////////////////////////////////////////////
	//辅助功能开发相关

	//当前商店id
	m_pShop		=	NULL;
	BankIsOpen	=	FALSE;

	//交易盒初始化
	m_ExchangBox.Init(this);

	//摊位盒初始化
	m_StallBox.Init(this);

	//辅助功能开发相关
	//////////////////////////////////////////////////////////////////////////


	m_pAvoidOverlap = NULL;
	m_pAvoidOverlap = new AvoidOverlap;
	Assert( m_pAvoidOverlap );

	CleanUp( ) ;

	m_pUseTimer = new INT[g_Config.m_ConfigInfo.m_nMaxHumanUseTimer];
	memset((VOID*)m_pUseTimer,-1,sizeof(INT) * g_Config.m_ConfigInfo.m_nMaxHumanUseTimer);

	m_uAreaID = UINT_MAX;
	m_uAreaScript = UINT_MAX;



	_HUMAN_ITEMCONTAINER_INIT	containInit;
	containInit.m_nContainerSize	=	m_DB.GetBaseBagSize();
	containInit.m_pHumanDB			=	&m_DB;
	containInit.m_ICTType			=	ICT_BASE_CONTAINER;
	containInit.m_DBOffSet			=	BASE_CONTAINER_OFFSET;

	m_BaseItem.Init(&containInit);

	//杂项物品包
	for(UINT i=0;i<m_DB.GetBaseBagSize();i++)
	{
		_ITEM_INIT	itemInit(m_DB.GetBagItem(BASE_CONTAINER_OFFSET+i));
		m_BaseItem.GetItem(i)->Init(&itemInit);
	}


	////材料物品包
	//containInit.m_nContainerSize	=	m_DB.GetMatBagSize();
	//containInit.m_ICTType			=	ICT_MAT_CONTAINER;
	//containInit.m_DBOffSet			=	MAT_CONTAINER_OFFSET;
	//
	//m_MatItem.Init(&containInit);


	//
	//for(UINT i=0;i<m_DB.GetMatBagSize();i++)
	//{
	//	_ITEM_INIT	itemInit(m_DB.GetBagItem(MAT_CONTAINER_OFFSET+i));
	//	m_MatItem.GetItem(i)->Init(&itemInit);
	//}

	////任务物品包
	//containInit.m_nContainerSize	=	m_DB.GetTaskBagSize();
	//containInit.m_ICTType			=	ICT_TASK_CONTAINER;
	//containInit.m_DBOffSet			=	TASK_CONTAINER_OFFSET;
	//
	//m_TaskItem.Init(&containInit);

	//for(UINT i=0;i<m_DB.GetTaskBagSize();i++)
	//{
	//	_ITEM_INIT	itemInit(m_DB.GetBagItem(TASK_CONTAINER_OFFSET+i));
	//	m_TaskItem.GetItem(i)->Init(&itemInit);
	//}

	containInit.m_nContainerSize	=	HEQUIP_NUMBER;
	containInit.m_ICTType			=	ICT_EQUIP_CONTAINER;
	//装备
	m_EquipItem.Init(&containInit);
	for(UINT i=0;i<HEQUIP_NUMBER;i++)
	{
		_ITEM_INIT	itemInit(m_DB.GetEquipItem((HUMAN_EQUIP)i));
		m_EquipItem.GetItem(i)->Init(&itemInit);
	}

	containInit.m_nContainerSize	=	MAX_BANK_SIZE;
	containInit.m_ICTType			=	ICT_BANK_CONTAINER;
	//银行
	m_BankItem.Init(&containInit);
	for(int i=0;i<MAX_BANK_SIZE;i++)
	{
		_ITEM_INIT	itemInit(m_DB.GetBankItem(i));
		m_BankItem.GetItem(i)->Init(&itemInit);
	}




	_HUMAN_PETCONTAINER_INIT	PetContainInit;
	PetContainInit.m_nContainerSize	=	HUMAN_PET_MAX_COUNT;
	PetContainInit.m_pHumanDB		=	&m_DB;
	PetContainInit.m_ICTType		=	ICT_HUMAN_PET_CONTAINER;

	//宠物
	m_PetItem.Init(&PetContainInit);
	for(UINT i = 0 ;i<HUMAN_PET_MAX_COUNT;i++)
	{
		_ITEM_INIT itemInit(m_DB.GetPet(i));
		m_PetItem.GetItem(i)->Init(&itemInit);
	}

	m_bIsPasswdUnlock = FALSE;
	m_bTeamFollowSpeedUp = FALSE;
	m_OutofTeamFollowRangeTime = 0;

	m_GUIDOfCallUpPet.Reset();
	m_pAI_Character = new AI_Human ;
	Assert( m_pAI_Character ) ;

	__LEAVE_FUNCTION
}

Obj_Human::~Obj_Human( )
{
	__ENTER_FUNCTION

		CleanUp( ) ;

	SAFE_DELETE( m_pHumanNode ) ;

	SAFE_DELETE( m_pAvoidOverlap ) ;

	SAFE_DELETE( m_pUseTimer ) ;

	__LEAVE_FUNCTION
}

PlayerID_t Obj_Human::GetPlayerID( )
{
	return m_pPlayer->PlayerID() ;
}

UINT Obj_Human::GetUniqueID() const
{
	return GetGUID();
}

BOOL Obj_Human::Init( const _OBJ_INIT *pInit, const BYTE age )
{
	__ENTER_FUNCTION


		if ( !Obj_Character::Init( pInit ) )
			return FALSE;


	_OBJ_HUMAN_INIT *pHumanInit = (_OBJ_HUMAN_INIT*)pInit;
	if ( pHumanInit != NULL )
	{
		if ( pHumanInit->m_pUseData != NULL )
		{
			const FULLUSERDATA	*pData = pHumanInit->m_pUseData;

			GetDB()->WriteHumanDB(&pData->m_Human);
			GetDB()->WriteEquipDB(&pData->m_Equip);
			GetDB()->WriteBagDB(&pData->m_Bag);
			GetDB()->WriteBankDB(&pData->m_Bank);
			GetDB()->WriteSkillDB(&pData->m_Skill);
			GetDB()->WriteCooldownDB(&pData->m_Cooldown);	
			GetDB()->WriteAbilityDB(&pData->m_Ability);
			GetDB()->WriteXinFaDB(&pData->m_XinFa);
			GetDB()->WriteImpactDB(&pData->m_Impact);
			GetDB()->WriteMissionDB(&pData->m_Mission);
			memcpy( GetDB()->m_dbPetList, &(pData->m_PetList ), sizeof(_PET_DB_LIST_LOAD) ) ;
			GetDB()->WriteRelationDB(&pData->m_Relation);
			GetDB()->WriteSettingDB(&pData->m_Setting);
			GetDB()->WritePrivateInfo(&pData->m_PrivateInfo);
			if(pData->m_bIsPasswdUnlock) {__UnlockPassword();}
		}
	}

	InitBackupAttr();

	UINT	RefreshIntervalTime		= g_Config.m_ConfigInfo.m_DefaultRefreshRate;
	UINT	CreateTime				= g_pTimeManager->CurrentTime();

	m_TeamInfo.CleanUp();
	m_TeamInfo.SetMyGUID( GetGUID() );

	m_HumanRelation.Init( this ) ;//初始化联系人功能模块

	//m_RefeshTimer.BeginTimer(RefreshIntervalTime,CreateTime);

	UINT	CheckZoneIntervalTime		= g_Config.m_ConfigInfo.m_DefaultCheckZoneRate;
	m_CheckZoneTimer.BeginTimer(CheckZoneIntervalTime,CreateTime);

	m_AttrBackUp.m_bMissionHaveDoneFlagsChanged	= TRUE;

	UINT	AttrUpdateIntervalTime = DB_2_SM_TIME;
	m_UpdateTimer.BeginTimer(AttrUpdateIntervalTime,CreateTime);

	//////////////////////////////////////////////////////////////////////////
	//辅助功能开发相关
	//初始化商品的回购列表
	InitialSoldList();

	if( (GetMoney() + __GetBankMoney())> (UINT)g_LevelMoneyTbl.Get(GetLevel()) )
	{
		//原则是先扣身上的钱
		UINT	iMaxMoney = g_LevelMoneyTbl.Get(GetLevel());
		if(GetMoney()>iMaxMoney)
		{//身上的钱已经大于上限
			SetMoney(iMaxMoney);
		}
		else
		{//清空身上的，再在银行里减
			__SetBankMoney(__GetBankMoney() - (iMaxMoney - GetMoney()) );
			SetMoney(0);
		}
	}

	//辅助功能开发相关
	//////////////////////////////////////////////////////////////////////////

	m_bTeamFollowSpeedUp = FALSE;
	m_OutofTeamFollowRangeTime = 0;
	m_bCanIncreaseRage = TRUE;

	//m_VERecoverTimer.BeginTimer(g_Config.m_ConfigInfo.m_HumanVERecoverInterval, g_pTimeManager->CurrentTime());
	if( age <= g_Config.m_ConfigInfo.m_WallowAge )
	{
		m_WallowTimer.BeginTimer(g_Config.m_ConfigInfo.m_WallowStartTime, g_pTimeManager->CurrentTime());
	}
	//如果有剩余时间和经验倍数就开始计时;
	if(GETHIGH(pHumanInit->m_pUseData->m_Human.m_DoubleExpTime_Num) >0 && GETLOW(pHumanInit->m_pUseData->m_Human.m_DoubleExpTime_Num) >1)
	{
		m_ExpTimer.BeginTimer(GETHIGH(pHumanInit->m_pUseData->m_Human.m_DoubleExpTime_Num)*1000,g_pTimeManager->CurrentTime());

	}
	//第一个角色设为管理所有的gm命令
	if(GetGUID() == g_Config.m_ConfigInfo.m_ThisRegion.m_nRegionIndex*10000000+1)
	{
		SetGmRight(4);

	}

	return TRUE;

	__LEAVE_FUNCTION
		return FALSE;
}
VOID Obj_Human::OnEnterScene(VOID)
{
	__ENTER_FUNCTION

		Obj_Character::OnEnterScene();

	setWorldPos(GetDB()->GetDBPosition());

	Impact_ActivateList();

	//Mark all attr dirty, force all attr re-calculated.
	MarkAllIntAttrDirtyFlags();
	MarkAllBoolAttrDirtyFlags();
	MarkAllIntAttrRefixDirtyFlags();

	//技能数据
	Skill_InitSkillList();
	//心法数据
	Skill_InitXinFaList();
	//物品效果刷新
	ItemEffectFlush( ) ;

	INT iHP = GetHP() ;
	if( iHP > GetMaxHP() )
	{
		SetHP(GetMaxHP() );
	}
	INT iMP = GetMP() ;
	if( iMP > GetMaxMP() )
	{
		SetMP(GetMaxMP() ) ;
	}
	//SetRage(0);
	//SetStrikePoint(0);
	__LEAVE_FUNCTION
}

VOID Obj_Human::ValidatePlayerID()
{

	GetDB()->ValidatePlayerID(GetPlayerID());
}
VOID Obj_Human::InitAIObj( )
{
	Assert( m_pAI_Character );
	m_pAI_Character->Init( this );
}

VOID Obj_Human::CleanUp( VOID )
{
	__ENTER_FUNCTION

		// 复活点相关
		m_bCanSkillRelive = FALSE;
	m_DefaultReliveInfo.Reset();
	m_SkillReliveInfo.Reset();

	m_DB.CleanUp() ;

	if( m_pHumanNode->m_pNext != NULL )
	{
		Assert(FALSE) ;
	}
	if( m_pHumanNode->m_pPrev != NULL )
	{
		Assert(FALSE) ;
	}

	m_PlayerID = INVALID_ID ;
	m_AssistantID = INVALID_ID ;
	m_MoveIndex = 0 ;

	m_TransSceneID = INVALID_ID ;
	m_EquipVer = 0 ;


	reset_AbilityOpera( );
	Obj_Character::CleanUp( ) ;
	m_bChangeSceneFlag = FALSE ;
	m_bGod = FALSE ;
	m_fWallow = WALLOW_NORMAL;
	SetRage(0);

	//m_uMissionIndex_KillObjectEvent_Num	= 0;
	//m_uMissionIndex_EnterAreaEvent_Num		= 0;
	//m_uMissionIndex_ItemChangedEvent_Num	= 0;

	m_bIsPasswdUnlock = FALSE;
	m_TeamInfo.CleanUp();
	m_bTeamFollowSpeedUp = FALSE;
	m_OutofTeamFollowRangeTime = 0;
	m_HumanRelation.CleanUp() ;

	//m_uCanPickMissionItemIDNum				= 0;
	//UINT i;
	//for ( i = 0; i < MAX_CHAR_CAN_PICK_MISSION_ITEM_NUM; i++ )
	//	m_aCanPickMissionItemList[i]		= UINT_MAX;

	m_uAreaID = UINT_MAX;
	m_uAreaScript = UINT_MAX;
	m_nCommonCooldown = 0;
	m_pPet = NULL;
	m_GUIDOfCallUpPet.Reset();

	__LEAVE_FUNCTION
}

BOOL Obj_Human::HeartBeat( UINT uTime )
{
	__ENTER_FUNCTION

		GamePlayer* pGamePlayer = (GamePlayer*)(GetPlayer()) ;
	if( pGamePlayer==NULL || pGamePlayer->GetPlayerStatus()!=PS_SERVER_NORMAL )
	{
		return FALSE ;
	}

	if(FALSE==Obj_Character::HeartBeat(uTime))
	{
		return FALSE;
	}

	if(m_CheckZoneTimer.CountingTimer(uTime))
	{
		CheckArea();
	}

	//if(m_RefeshTimer.CountingTimer(uTime))
	//{
	//	RefeshAttrMsg();
	//}

	if(m_UpdateTimer.CountingTimer(uTime))
	{
		m_bUpdateAttr = TRUE;
	}

	if(GetPet() != NULL)
	{
		if(GetPet()->GetHappiness() < g_Config.m_ConfigInfo.m_PetCallUpHappiness)
		{
			ReCallPet();
			SendOperateResultMsg(OR_PET_HADRECALL_NEEDHAPPINESS);
		}
		else if(GetPet()->GetLife() <= 0)
		{
			ReCallPet();
			SendOperateResultMsg(OR_PET_HADRECALL_NEEDLIFE);

		}
	}	

	ValidateShareMem(FALSE); //最后更新数据到共享内存


	return TRUE;

	__LEAVE_FUNCTION

		return FALSE ;
}

VOID Obj_Human::OnRegisterToZone(VOID)
{
	__ENTER_FUNCTION

		Obj_Character::OnRegisterToZone();

	SetGUIDOfCallUpPet(GetCurrentPetGUID());
	if(!GetGUIDOfCallUpPet().IsNull())
	{
		ORESULT oResult = CreatePet();
		if(OR_FAILED(oResult))
		{
			SendOperateResultMsg(oResult);
		}
	}

	if(IsDie())
	{
		GetAIObj()->Relive(FALSE);
	}

	__LEAVE_FUNCTION
}

VOID Obj_Human::OnUnregisterFromZone( )
{
	__ENTER_FUNCTION

		Obj_Character::OnUnregisterFromZone();

	ReleasePet();

	__LEAVE_FUNCTION
}

// 比较二级密码
BOOL Obj_Human::ComparePasswd( const CHAR* szPasswd )
{
	return ( strcmp(szPasswd, __GetPassword()) == 0 );
}

//VOID Obj_Human::RefeshAttrMsg()
//{
//	INT NowVigor = GetVigor() ;
//	NowVigor += 1 ;
//	SetVigor( NowVigor ) ;
//}

VOID Obj_Human::ValidateShareMem(BOOL bForceAll)
{
	__ENTER_FUNCTION

		GetDB()->ValidateShareMem(bForceAll,m_bUpdateAttr);

	__LEAVE_FUNCTION
}
BOOL Obj_Human::HeartBeat_Recover(UINT uTime)
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
		INT nRegenerate = GetHPRegenerate();
		if(nCur<nMax && 0<nRegenerate)
		{
			nCur += nRegenerate*nCount ;
			nCur<nMax?nCur:nCur=nMax;
			SetHP(nCur) ;
		}	
		/** 进行回兰操作 */
		nCur = GetMP( ); 
		nMax = GetMaxMP();
		nRegenerate = GetMPRegenerate();
		if(nCur<nMax && 0<nRegenerate)
		{
			nCur += nRegenerate*nCount ;
			nCur<nMax?nCur:nCur=nMax;
			SetMP(nCur) ;
		}	
	}

	//if(m_VERecoverTimer.CountingTimer(uTime))
	//{
	//	if(GetVigor() != GetMaxVigor())
	//	{
	//		INT nVigorRecover = (INT)(((FLOAT)(GetMaxVigor()) / 100.f + 2.f) * (1.f + (FLOAT)(GetVigorRegeneRate()) / 100.f));
	//		if(nVigorRecover > 0)
	//		{
	//			SetVigor(GetVigor() + nVigorRecover);
	//		}
	//	}
	//	if(GetEnergy() != GetMaxEnergy())
	//	{
	//		INT nEnergyRecover = (INT)(((FLOAT)(GetMaxEnergy()) / 100.f + 2.f) * (1.f + (FLOAT)(GetEnergyRegeneRate()) / 100.f));
	//		if(nEnergyRecover > 0)
	//		{
	//			SetEnergy(GetEnergy() + nEnergyRecover);
	//		}
	//	}
	//}

	if( m_WallowTimer.CountingTimer(uTime) )
	{
		if( m_WallowTimer.GetTermTime() == g_Config.m_ConfigInfo.m_WallowStartTime )
		{
			//进入半收益状态
			m_WallowTimer.SetTermTime( g_Config.m_ConfigInfo.m_WallowStartTime2 - g_Config.m_ConfigInfo.m_WallowStartTime );

			m_WallowAwokeTimer.BeginTimer(g_Config.m_ConfigInfo.m_WallowAwokeTime, g_pTimeManager->CurrentTime());
			SetWallow( WALLOW_HALF_INCOME );
		}
		else
		{
			//进入无收益状态
			m_WallowTimer.CleanUp();
			SetWallow( WALLOW_NONE );
		}
	}
	if( m_WallowAwokeTimer.CountingTimer(uTime) )
	{
		SetWallow( GetWallow() );
	}
	if(m_ExpTimer.IsSetTimer())
	{
		if(m_ExpTimer.CountingTimer(uTime))//多倍经验到时;
		{
			int nExpTime=GETLOW(GetDoubleExpTime_Num());
			SetDoubleExpTime_Num(1);
			m_ExpTimer.CleanUp();
			GCChat msgChat;
			CHAR szChat[MAX_CHAT_SIZE]={0};
			sprintf(szChat,"你设置的%d倍经验状态已经到时!",nExpTime);
			INT Size = (INT)strlen(szChat) ;
			msgChat.SetChatType( CHAT_TYPE_SELF) ;
			msgChat.SetContexSize( Size ) ;
			msgChat.SetContex( szChat ) ;
			msgChat.SetSourNameSize( (BYTE)strlen(GetName())) ;
			msgChat.SetSourName( GetName()) ;
			msgChat.SetSourID(GetID()) ;
			msgChat.SetSourCamp( INVALID_CAMP );
			GetPlayer()->SendPacket(&msgChat);
		}
		else
		{

			SetDoubleExpTime_Num(((m_ExpTimer.GetLeaveTime(uTime)/1000)<<16)+GETLOW(GetDoubleExpTime_Num()));

		}

	}


	__LEAVE_FUNCTION
		return TRUE;
}


VOID Obj_Human::CheckArea()
{
	__ENTER_FUNCTION

		if ( getZoneID() == INVALID_ID )
			return;

	const Area* pArea;
	UINT uAreaID;

	pArea = getScene()->CheckArea(this);
	if ( pArea != NULL )
	{
		uAreaID = pArea->m_uAreaID;
	}
	else
	{
		uAreaID = UINT_MAX;
	}

	SceneID_t sceneid = getScene()->SceneID() ;
	if ( uAreaID != m_uAreaID )
	{
		LuaInterface* pLuaInterface = getScene()->GetLuaInterface();

		if ( m_uAreaID != UINT_MAX && m_uAreaScript != UINT_MAX )
		{ // OnLeaveZone();
			pLuaInterface->ExeScript_DDD(m_uAreaScript, DEF_ON_LEAVE_AREA_FUNC_NAME, (INT)sceneid, (INT)GetID(), 0);
		}

		m_uAreaID = uAreaID;

		if ( m_uAreaID != UINT_MAX )
		{
			// 设置玩家进入 Area 的时刻
			m_uTimeStamp = NowTime();
			m_uAreaScript = pArea->m_uScriptID;

			OnEnterArea( m_uAreaID );

			// 执行 Area 脚本，这个脚本可能是具有杀死玩家（导致位置变化）或者传送的功能
			// 所以需要在玩家脚本执行结束以后执行
			if ( m_uAreaScript != UINT_MAX )
			{
				pLuaInterface->ExeScript_DDD(m_uAreaScript, DEF_ON_ENTER_AREA_FUNC_NAME, (INT)sceneid, (INT)GetID(), 0);
			}
		}
		else
		{
			m_uAreaScript = UINT_MAX;
		}
	}
	else if ( m_uAreaScript != UINT_MAX )
	{
		// 调用 OnTimer 来执行持续事件，但是需要判断该 Area 是否含有持续事件
		getScene()->GetLuaInterface()->ExeScript_DDD(m_uAreaScript, DEF_EVENT_ON_TIMER, (INT)sceneid, GetID(), 0);
	}

	__LEAVE_FUNCTION
}

/****************************************************************************
*	功能说明：
*				根据前一个队员的方位，为当前队员选择一个合适目标位置
*				只从 6 个备用方位选择，优先顺序如下所示：
*								4—— * ——5
*								    / | \
*								   /  |	 \
*								  2   1   3
*				如果找不到合适的位置，则和前一个队员重合（第 6 个方位）
*	参数说明：
*				Pos
*					用作输出
*				pPrevPos
*					前一个队员的位置
*				fDir
*					前一个队员的朝向
*	输出说明：
*				Pos
*				当前队员应该移动到的位置
*				成功返回 TRUE，失败返回 FALSE
*****************************************************************************/
BOOL Obj_Human::GetPosition(WORLD_POS& Pos, const WORLD_POS* pRefPos, FLOAT fDir)
{
	Pos.m_fX = pRefPos->m_fX - sin( fDir );
	Pos.m_fZ = pRefPos->m_fZ - cos( fDir );
	return TRUE;
}

INT		Obj_Human::GetStrikePoint(VOID)
{
	__ENTER_FUNCTION
		if(m_DB.GetStrikePoint()>GetMaxStrikePoint())
		{
			m_DB.SetStrikePoint(GetMaxStrikePoint());
		}
		return m_DB.GetStrikePoint();
		__LEAVE_FUNCTION
			return 0 ;
}
VOID	Obj_Human::SetStrikePoint(INT nStrikePoint)
{
	__ENTER_FUNCTION
		m_DB.SetStrikePoint(nStrikePoint);
	__LEAVE_FUNCTION
}

INT		Obj_Human::GetRMB(VOID)
{
	__ENTER_FUNCTION
		return m_DB.GetRMB();
	__LEAVE_FUNCTION
		return 0 ;
}
VOID	Obj_Human::SetRMB(INT nMoney)
{
	__ENTER_FUNCTION
		m_DB.SetRMB(nMoney);
	__LEAVE_FUNCTION
}

INT		Obj_Human::GetBankRMB(VOID)
{
	__ENTER_FUNCTION
		return m_DB.GetBankRMB();
	__LEAVE_FUNCTION
		return 0 ;
}
VOID	Obj_Human::SetBankRMB(INT nMoney)
{
	__ENTER_FUNCTION
		m_DB.SetBankRMB(nMoney);
	__LEAVE_FUNCTION
}

//INT		Obj_Human::GetVigorRegeneRate(VOID)
//{
//	__ENTER_FUNCTION
//		return m_DB.GetVigorRegeneRate();
//	__LEAVE_FUNCTION
//		return 0 ;
//}
//VOID	Obj_Human::SetVigorRegeneRate(INT nVigorRegeneRate)
//{
//	__ENTER_FUNCTION
//		m_DB.SetVigorRegeneRate(nVigorRegeneRate);
//	__LEAVE_FUNCTION
//}

INT		Obj_Human::GetDoubleExpTime_Num(VOID)
{
	__ENTER_FUNCTION
		return m_DB.GetDoubleExpTime_Num();
	__LEAVE_FUNCTION
		return 0 ;
}
VOID	Obj_Human::SetDoubleExpTime_Num(INT nExpTime_Num)
{
	__ENTER_FUNCTION

		if(nExpTime_Num <= 0)
		{
			nExpTime_Num = 1;
		}

		m_DB.SetDoubleExpTime_Num(nExpTime_Num);
		__LEAVE_FUNCTION
}

INT		Obj_Human::GetGmRight(VOID)
{
	__ENTER_FUNCTION
		return m_DB.GetGmRight();
	__LEAVE_FUNCTION
		return 0 ;
}
VOID	Obj_Human::SetGmRight(INT nRight)
{
	__ENTER_FUNCTION
		m_DB.SetGmRight(nRight);
	__LEAVE_FUNCTION
}
//
//INT		Obj_Human::GetEnergyRegeneRate(VOID)
//{
//	__ENTER_FUNCTION
//		return m_DB.GetEnergyRegeneRate();
//	__LEAVE_FUNCTION
//		return 0 ;
//}
//VOID	Obj_Human::SetEnergyRegeneRate(INT nEnergyRegeneRate)
//{
//	__ENTER_FUNCTION
//		m_DB.SetEnergyRegeneRate(nEnergyRegeneRate);
//	__LEAVE_FUNCTION
//}

INT 	Obj_Human::GetRage( VOID )
{
	__ENTER_FUNCTION
		if(m_DB.GetRage()>GetMaxRage())
		{
			m_DB.SetRage(GetMaxRage());
		}
		return m_DB.GetRage();
		__LEAVE_FUNCTION
			return 0 ;
}
VOID	Obj_Human::SetRage( INT nRage )
{
	__ENTER_FUNCTION
		if(0>nRage)
		{
			nRage=0;
		}
		if(nRage>GetMaxRage())
		{
			nRage = GetMaxRage();
		}
		m_DB.SetRage(nRage);
		__LEAVE_FUNCTION
}
INT		Obj_Human::GetHP( VOID )
{
	if(m_DB.GetHP() > GetMaxHP())
	{
		m_DB.SetHP(GetMaxHP());
	}
	return m_DB.GetHP(); 
}
INT		Obj_Human::GetMP( VOID )
{
	if(m_DB.GetMP() > GetMaxMP())
	{
		m_DB.SetMP(GetMaxMP());
	}
	return m_DB.GetMP(); 
}

VOID Obj_Human::Teleport( const WORLD_POS* pos )
{
	__ENTER_FUNCTION

		Obj_Character::Teleport( pos );
	if ( m_pPet != NULL )
	{
		m_pPet->Teleport( pos );
	}

	m_DB.SetDBPosition(*getWorldPos());

	__LEAVE_FUNCTION
}

ORESULT Obj_Human::TestCallUpPet(const PET_GUID_t guidPet)
{
	__ENTER_FUNCTION

		if ( guidPet.IsNull() ) 
		{
			return OR_ERROR;
		}

		Item *pPetItem = GetPetItem(guidPet);
		if ( pPetItem == NULL ) 
		{
			return OR_ERROR;
		}

		Scene* pScene = getScene();
		if (!pScene)
		{
			return OR_ERROR;
		}
		// 如果是正在交易(被加锁)的宠物不可以招出
		if (TRUE == pPetItem->IsInExchange())
		{
			return OR_PETINEXCHANGE_CANNOT_GOFIGHT;
		}
		// 正在使用技能时不能再次招出
		if (FALSE == CanUseSkillNow() )
		{
			return OR_BUSY;
		}

		// HP等于0时不能招出
		if (pPetItem->GetHP() <= 0)
		{
			return OR_NOT_ENOUGH_HP;
		}
		// 如果宠物等级高于玩家等级10级则无法招唤出来
		if (pPetItem->GetLevel() > (GetLevel() + LEVELDELTA_CALLUP) )
		{
			return OR_NEED_HIGH_LEVEL;
		}

		// 快乐度小于等于50将招不出来
		if (pPetItem->GetHappiness() < g_Config.m_ConfigInfo.m_PetCallUpHappiness)
			return OR_NEED_HAPPINESS;

		// 寿命
		if (pPetItem->GetLife() <= 0)
			return OR_NEED_LIFE;

		return OR_OK;

		__LEAVE_FUNCTION
			return OR_ERROR;
}

ORESULT Obj_Human::CallUpPet(VOID)
{
	__ENTER_FUNCTION
		Item *pPetItem = GetPetItem(m_GUIDOfCallUpPet);
	if ( pPetItem == NULL ) 
	{
		return OR_ERROR;
	}
	// 如果是正在交易(被加锁)的宠物不可以招出
	if (TRUE == pPetItem->IsInExchange())
	{
		return OR_PETINEXCHANGE_CANNOT_GOFIGHT;
	}

	ReleasePet();

	ORESULT oResult =CreatePet();
	if(OR_FAILED(oResult))
		return oResult;

	SetCurrentPetGUID(m_GUIDOfCallUpPet);

	return OR_OK;

	__LEAVE_FUNCTION

		return OR_ERROR;
}

ORESULT Obj_Human::ReCallPet(VOID)
{
	__ENTER_FUNCTION

		PET_GUID_t guidPet;
	m_GUIDOfCallUpPet = guidPet;
	SetCurrentPetGUID(m_GUIDOfCallUpPet);

	if (m_pPet)
	{// 当收回宠物时将主人身上所有宠物种的BUFF统统清掉
		Impact_CleanAllImpactWhenPetDead(m_pPet->GetID());
		m_pPet->Impact_CleanAllImpactWhenPetDead(m_pPet->GetID());
		// 强行刷新宠物信息
		m_pPet->SendMsg_RefeshAttrib();
	}

	ReleasePet();

	return OR_OK;

	__LEAVE_FUNCTION

		return OR_ERROR;
}

BOOL Obj_Human::AddPet(const _PET_DB *pPetDB)
{
	__ENTER_FUNCTION

		if(pPetDB == NULL)
			return FALSE;

	for ( INT i = 0; i < HUMAN_PET_MAX_COUNT; ++i )
	{
		Item* pPetFind = GetPetContain()->GetItem(i);
		if (pPetFind != NULL && pPetFind->IsLock() == FALSE)
		{// 确保要操作的宠物现在处于非锁定状态
			PET_GUID_t guidFind = pPetFind->GetPetGUID();
			if ( guidFind.IsNull() )
			{
				g_ItemOperator.SetItemValue(GetPetContain(), i, pPetDB);
				RefeshPetDetailAttrib(pPetDB->m_GUID);

				OnPetChanged(pPetDB->m_nDataID) ;

				return TRUE;
			}
		}
	}
	return FALSE;

	__LEAVE_FUNCTION

		return FALSE;
}

BOOL Obj_Human::RemovePet(PET_LOG_PARAM* pPetLogParam,PET_GUID_t guid)
{
	__ENTER_FUNCTION

		Assert(pPetLogParam);
	if(GetCurrentPetGUID() == guid)
	{
		ReCallPet();
	}

	for ( INT i = 0; i < HUMAN_PET_MAX_COUNT; ++i )
	{
		Item* pPetFind = GetPetContain()->GetItem(i);
		if (pPetFind != NULL && pPetFind->IsLock() == FALSE)
		{// 确保要操作的宠物现在处于非锁定状态
			PET_GUID_t guidFind = pPetFind->GetPetGUID();
			if ( guidFind == guid )
			{
				pPetLogParam->PetGUID	=	pPetFind->GetPetGUID();
				pPetLogParam->DataID	=	pPetFind->GetPetType();	

				_PET_DB petDB;
				petDB.CleanUp();
				g_ItemOperator.SetItemValue(GetPetContain(), i, &petDB);

				GCRemovePet msgRemovePet;
				msgRemovePet.SetGUID(guid);
				GetPlayer()->SendPacket(&msgRemovePet);
				return TRUE;
			}
		}
	}
	return FALSE;

	__LEAVE_FUNCTION

		return FALSE;
}

ORESULT Obj_Human::CreatePet(VOID)
{
	__ENTER_FUNCTION

		PET_GUID_t guidPet = GetGUIDOfCallUpPet();
	if ( guidPet.IsNull() ) 
	{
		return OR_ERROR;
	}

	Item *pPetItem = GetPetItem(guidPet);
	if ( pPetItem == NULL ) 
	{
		return OR_ERROR;
	}

	Scene* pScene = getScene();
	if (!pScene)
	{
		return OR_ERROR;
	}
	Obj_Pet *pPet = (Obj_Pet*)(getScene()->NewObject( Obj::OBJ_TYPE_PET ));
	if ( !pPet )
	{
		return OR_ERROR;
	}

	BOOL bResult;
	_OBJ_PET_INIT initPet;
	const WORLD_POS* pPos = getWorldPos();
	initPet.m_Pos.m_fX	= pPos->m_fX - 1.f;
	initPet.m_Pos.m_fZ	= pPos->m_fZ;
	// 对该位置进行校验
	pPos = &initPet.m_Pos;
	pScene->GetMap()->VerifyPos(&initPet.m_Pos);
	if (FALSE == pScene->GetMap()->IsCanGo(*pPos,GetDriverLevel())) {
		initPet.m_Pos = *getWorldPos();
	}
	initPet.m_Dir		= 0.f;

	initPet.m_eLogic	= CHARACTER_LOGIC_IDLE;
	initPet.m_CreatorID	= GetID();
	initPet.m_nIndex	= GetPetIndexByGUID(guidPet);
	bResult = pPet->Init( &initPet );
	if ( !bResult )
	{
		pPet->CleanUp();
		getScene()->DeleteObject( pPet );
		pPet = NULL;
		return OR_ERROR;
	}
	pPet->SetActiveFlag( TRUE );
	m_pPet = pPet;

	return OR_OK;

	__LEAVE_FUNCTION

		return OR_ERROR;
}

BOOL Obj_Human::ReleasePet(VOID)
{
	__ENTER_FUNCTION
		if ( m_pPet != NULL )
		{
			PetManager* pPetMgr = getScene()->GetPetManager();
			if (pPetMgr)
				pPetMgr->RemovePet(m_pPet->GetID());

			m_pPet = NULL;

			return TRUE;
		}
		return FALSE;
		__LEAVE_FUNCTION
			return TRUE;
}

ORESULT Obj_Human::FreePetToNature(PET_LOG_PARAM* pPetLogParam,PET_GUID_t guidPet)
{
	__ENTER_FUNCTION

		Assert(pPetLogParam);
	if(guidPet.IsNull())
	{
		return OR_ERROR;
	}

	if(guidPet == GetCurrentPetGUID())
	{
		ReCallPet();
	}

	RemovePet(pPetLogParam,guidPet);

	return OR_OK;

	__LEAVE_FUNCTION
		return OR_ERROR;
}

ORESULT Obj_Human::AddPetByDataID(PET_LOG_PARAM* pPetLogParam,const UINT uDataID)
{
	__ENTER_FUNCTION

		_PET_DB dbPet;
	Assert(pPetLogParam);
	PET_ATTR* pPetAttr = g_PetAttrTbl.GetAttr(uDataID);
	if (!pPetAttr) {
		return OR_ERROR;
	}

	Scene* pScene = getScene();
	if (!pScene)
	{
		return OR_ERROR;
	}	
	dbPet.m_nDataID = uDataID;
	dbPet.m_GUID.Init(GetGUID(), g_pTimeManager->CurrentTime());
	tsnprintf(dbPet.m_szName, sizeof(dbPet.m_szName), pPetAttr->m_Name);
	dbPet.m_nLevel = pPetAttr->m_TakeLevel;
	dbPet.m_nTakeLevel = pPetAttr->m_TakeLevel;

	pScene->GetPetManager()->MakeCapturePetAttrib(&dbPet);

	AddPet(&dbPet);
	return OR_OK;

	__LEAVE_FUNCTION
		return OR_ERROR;

}

VOID Obj_Human::BabyToAttack(VOID)
{
	__ENTER_FUNCTION
		if ( m_pPet == NULL )
		{
			return ;		
		}
		// 让宠物进入攻击状态
		if (m_pPet->IsAlive())
		{
			ObjID_t TargetID = GetCurTarget();
			m_pPet->SetTargetID(TargetID);
			AI_Pet* pAIPet = ((AI_Pet*)m_pPet->GetAIObj() );
			pAIPet->BabyToAttack();
		}

		__LEAVE_FUNCTION
}

BOOL Obj_Human::CapturePet(PET_LOG_PARAM* pPetLogParam, ObjID_t PetID )
{
	__ENTER_FUNCTION

		Assert(pPetLogParam);
	// 检测有效性
	Obj* pObj = getScene()->GetObjManager()->GetObj( PetID );
	if ( !pObj ||
		pObj->GetObjType() != Obj::OBJ_TYPE_PET ||
		!((Obj_Character*)pObj)->IsAlive() )
	{
		return FALSE;
	}
	Obj_Pet* pPet = (Obj_Pet*)pObj;
	if (!pPet)
	{
		Assert(NULL && "Obj_Human::CapturePet...pPet=NULL...");
		return FALSE;
	}

	if (NULL != pPet->GetOwner())
	{// 说明该宠物已经有主人了则返回
		SendOperateResultMsg(OR_INVALID_TARGET);
		return FALSE;
	}
	// 如果小于宠物的携带等级则返回
	INT nTakeLevel = pPet->GetPetDB()->m_nTakeLevel;
	if (GetLevel() < nTakeLevel)
	{
		SendOperateResultMsg(OR_NEED_HIGH_LEVEL);
		return FALSE;
	}

	// 是否属于自己的规则判断
	INT nCapturerCount = pPet->GetCaptureCount();	
	if (!nCapturerCount)
		return FALSE;

	INT nRet = rand() % nCapturerCount;
	if (0 != nRet)
	{// 如果不在范围之内则捕获失败
		return FALSE;
	}


	_PET_DB* pPetDB = const_cast<_PET_DB*>(pPet->GetPetDB());
	BOOL bResult = getScene()->GetPetManager()->CreateGUIDOfPet(pPetDB, GetID(), PetID);
	if(!bResult)
	{
		return FALSE;
	}

	bResult = AddPet(pPetDB);
	if(!bResult)
	{
		return FALSE;
	}

	pPetLogParam->CharGUID		=	GetGUID();
	pPetLogParam->PetGUID		=	pPetDB->m_GUID;
	pPetLogParam->DataID		=	pPetDB->m_nDataID;
	pPetLogParam->SceneID		=	getScene()->SceneID();
	pPetLogParam->XPos			=	getWorldPos()->m_fX;
	pPetLogParam->ZPos			=	getWorldPos()->m_fZ;


	return TRUE;

	__LEAVE_FUNCTION
		return TRUE;

}

BOOL	Obj_Human::CanReturnToChild(PET_GUID_t guid)
{
	__ENTER_FUNCTION
		Scene* pScene = getScene();	
	if (!pScene)
	{
		Assert(NULL && "Obj_Human::CanReturnToChild...pScene=NULL...");
		return FALSE;
	}

	_PET_DB* pPetDB = NULL;
	INT nIndex = GetPetIndexByGUID(guid);
	pPetDB = GetPetDB(nIndex);
	if (!pPetDB)
	{
		return FALSE;
	}

	if (pPetDB->m_SpouseGUID.IsNull() != TRUE)
	{// 已经有配偶的宠物不能进行还童
		SendOperateResultMsg(OR_HASSPOUSE_CANNOT_RETURNTOCHILD);
		return FALSE;
	}
	if (pPetDB->m_byPetType == _PET_DB_LOAD::PET_TYPE_VARIANCE)
	{// 变异宠不能进行还童
		SendOperateResultMsg(OR_VARIANCEPET_CANNOT_RETURNTOCHILD);
		return FALSE;
	}
	Obj_Pet* pPet = GetPet();
	if (pPet && pPet->GetPetGUID() == guid)
	{// 如果要还童的宠物正在出战状态则提示先收回宠物
		SendOperateResultMsg(OR_COMBAT_CANNOT_RETURNTOCHILD);
		return FALSE;
	}

	return TRUE;
	__LEAVE_FUNCTION
		return FALSE;
}

BOOL	Obj_Human::ReturnToChild(PET_GUID_t guid)
{
	__ENTER_FUNCTION

		Scene* pScene = getScene();	
	if (!pScene)
	{
		Assert(NULL && "Obj_Human::ReturnToChild...pScene=NULL...");
		return FALSE;
	}

	_PET_DB* pPetDB = NULL;
	INT nIndex = GetPetIndexByGUID(guid);
	pPetDB = GetPetDB(nIndex);
	if (!pPetDB)
	{
		return FALSE;
	}
	pScene->GetPetManager()->MakeCapturePetAttrib(pPetDB, FALSE, TRUE);
	RefeshPetDetailAttrib(guid);

	return TRUE;
	__LEAVE_FUNCTION
		return FALSE;
}

INT Obj_Human::GetPetCount(VOID)const
{
	__ENTER_FUNCTION

		INT i, nCount;
	nCount = 0;
	for ( i = 0; i < HUMAN_PET_MAX_COUNT; i++ )
	{
		if ( !m_DB.m_dbPetList->m_aPetDB[i].m_GUID.IsNull() )
		{
			nCount++;
		}
	}
	return nCount;

	__LEAVE_FUNCTION

		return 0;
}

_PET_DB *Obj_Human::GetPetDB( INT nIndex )const
{
	__ENTER_FUNCTION

		for (INT i = 0; i < HUMAN_PET_MAX_COUNT; i++ )
		{
			if ( !m_DB.m_dbPetList->m_aPetDB[i].m_GUID.IsNull() )
			{
				if ( i == nIndex )
				{
					return &(m_DB.m_dbPetList->m_aPetDB[i]);
				}
			}
		}
		return NULL;

		__LEAVE_FUNCTION

			return NULL;
}

const _PET_DB *Obj_Human::GetConstPetDB( INT nIndex )const
{
	return GetPetDB( nIndex );
}

BYTE Obj_Human::GetPetHappiness( PET_GUID_t guid )
{
	__ENTER_FUNCTION

		Item *pPetItem = GetPetItem(guid);
	if(pPetItem != NULL)
	{
		return pPetItem->GetHappiness();
	}
	return 0;

	__LEAVE_FUNCTION

		return 0;
}

VOID Obj_Human::SetPetHappiness( PET_GUID_t guid, BYTE byHappiness )
{
	__ENTER_FUNCTION

		INT nIndex = GetPetIndexByGUID(guid);
	g_ItemOperator.SetHappiness(GetPetContain(), nIndex, byHappiness);

	__LEAVE_FUNCTION
}

INT Obj_Human::GetPetHP( PET_GUID_t guid )
{
	__ENTER_FUNCTION

		Item *pPetItem = GetPetItem(guid);
	if(pPetItem != NULL)
	{
		return pPetItem->GetHP();
	}
	return 0;

	__LEAVE_FUNCTION

		return 0;
}

VOID Obj_Human::SetPetHP( PET_GUID_t guid, INT nHP )
{
	__ENTER_FUNCTION

		INT nIndex = GetPetIndexByGUID(guid);
	g_ItemOperator.SetHP(GetPetContain(), nIndex, nHP);

	__LEAVE_FUNCTION
}

INT Obj_Human::GetPetMaxHP( PET_GUID_t guid )
{
	__ENTER_FUNCTION

		if(guid == m_GUIDOfCallUpPet && m_pPet != NULL)
		{
			return m_pPet->GetMaxHP();
		}
		else
		{
			Item *pPetItem = GetPetItem(guid);
			if(pPetItem != NULL)
			{
				return pPetItem->GetBaseMaxHP();
			}
		}

		return 1;

		__LEAVE_FUNCTION

			return 1;
}

INT Obj_Human::GetPetLife( PET_GUID_t guid )
{
	__ENTER_FUNCTION

		Item *pPetItem = GetPetItem(guid);
	if(pPetItem != NULL)
	{
		return pPetItem->GetLife();
	}
	return 0;

	__LEAVE_FUNCTION

		return 0;
}

VOID Obj_Human::SetPetLife( PET_GUID_t guid, INT nLife )
{
	__ENTER_FUNCTION

		INT nIndex = GetPetIndexByGUID(guid);
	g_ItemOperator.SetLife(GetPetContain(), nIndex, nLife);

	__LEAVE_FUNCTION
}

Item *Obj_Human::GetPetItem(PET_GUID_t guid)
{
	__ENTER_FUNCTION

		Item* pPetItem = NULL;
	for ( INT i = 0; i < HUMAN_PET_MAX_COUNT; ++i )
	{
		Item* pPetFind = GetPetContain()->GetItem(i);
		PET_GUID_t guidFind = pPetFind->GetPetGUID();
		if ( (guidFind == guid) )
		{
			pPetItem = pPetFind;
			break;
		}
	}
	return pPetItem;

	__LEAVE_FUNCTION

		return NULL;
}

INT Obj_Human::GetPetIndexByGUID(PET_GUID_t guid)
{
	__ENTER_FUNCTION

		Item* pPetItem = NULL;
	for ( INT i = 0; i < HUMAN_PET_MAX_COUNT; ++i )
	{
		Item* pPetFind = GetPetContain()->GetItem(i);
		PET_GUID_t guidFind = pPetFind->GetPetGUID();
		if ( (guidFind == guid) )
		{
			return i;
		}
	}
	return -1;

	__LEAVE_FUNCTION

		return -1;
}

// 临时函数
PET_GUID_t Obj_Human::GetPetGUIDByIndex(INT nIndex)
{
	__ENTER_FUNCTION

		if(nIndex >= 0 && nIndex < HUMAN_PET_MAX_COUNT)
		{
			Item* pPetFind = GetPetContain()->GetItem(nIndex);
			return  pPetFind->GetPetGUID();
		}

		PET_GUID_t guidPet;
		guidPet.Reset();
		return guidPet;

		__LEAVE_FUNCTION

			PET_GUID_t guidPet;
		guidPet.Reset();
		return guidPet;
}

// 临时函数
PET_GUID_t Obj_Human::GetPetGUIDByValidIndex(INT nIndex)
{
	__ENTER_FUNCTION

		if(nIndex >= 0 && nIndex < HUMAN_PET_MAX_COUNT)
		{
			INT i, nCount;
			nCount = 0;
			for(i = 0; i < HUMAN_PET_MAX_COUNT; i++)
			{
				Item* pPetFind = GetPetContain()->GetItem(nIndex);
				if(pPetFind != NULL)
				{
					if(nCount == nIndex)
					{
						return pPetFind->GetPetGUID();
					}
					nCount++;
				}
			}
		}

		PET_GUID_t guidPet;
		guidPet.Reset();
		return guidPet;

		__LEAVE_FUNCTION

			PET_GUID_t guidPet;
		guidPet.Reset();
		return guidPet;
}

VOID Obj_Human::SetMoney(UINT money)
{
	__ENTER_FUNCTION

		m_DB.SetMoney(money);

	__LEAVE_FUNCTION
}

_PLAYERSHOP_GUID	Obj_Human::GetShopGuid(INT nIndex)
{
	__ENTER_FUNCTION
		if(nIndex >= 0 && nIndex < MAX_SHOP_NUM_PER_PLAYER)
		{
			return	m_DB.GetShopGuid(nIndex);
		}

		_PLAYERSHOP_GUID guidShop;
		return guidShop;
		__LEAVE_FUNCTION
			_PLAYERSHOP_GUID guidShop;
		return guidShop;
}

VOID	Obj_Human::SetShopGuid(INT nIndex, _PLAYERSHOP_GUID pGuid)
{
	__ENTER_FUNCTION
		if(nIndex >= 0 && nIndex < MAX_SHOP_NUM_PER_PLAYER)
		{
			m_DB.SetShopGuid(nIndex, pGuid);
		}
		__LEAVE_FUNCTION
}

_PLAYERSHOP_GUID	Obj_Human::GetFavoriteShopGuid(INT nIndex)
{
	__ENTER_FUNCTION
		if(nIndex >= 0 && nIndex < MAX_FAVORITE_SHOPS)
		{
			return	m_DB.GetFavoriteShopGuid(nIndex);
		}

		_PLAYERSHOP_GUID guidShop;
		return guidShop;
		__LEAVE_FUNCTION
			_PLAYERSHOP_GUID guidShop;
		return guidShop;

}

VOID	Obj_Human::SetFavoriteShopGuid(INT nIndex, _PLAYERSHOP_GUID pGuid)
{
	__ENTER_FUNCTION
		if(nIndex >= 0 && nIndex < MAX_FAVORITE_SHOPS)
		{
			m_DB.SetFavoriteShopGuid(nIndex, pGuid);
		}
		__LEAVE_FUNCTION
}

BOOL Obj_Human::IsInFavorite(_PLAYERSHOP_GUID pGuid)
{
	__ENTER_FUNCTION
		for(INT i = 0; i<MAX_FAVORITE_SHOPS; i++)
		{
			if(GetFavoriteShopGuid(i) == pGuid)
			{
				return TRUE;
			}
		}
		return FALSE;
		__LEAVE_FUNCTION
			return FALSE;
}

BOOL Obj_Human::AddFavorite(_PLAYERSHOP_GUID pGuid)
{
	__ENTER_FUNCTION
		if(IsInFavorite(pGuid))
		{
			return TRUE;
		}
		for(INT i =0; i<MAX_FAVORITE_SHOPS; i++)
		{
			if(GetFavoriteShopGuid(i).isNull() )
			{
				SetFavoriteShopGuid(i, pGuid);
				return TRUE;
			}
		}
		return FALSE;
		__LEAVE_FUNCTION
			return FALSE;

}

BOOL Obj_Human::DelFavorite(_PLAYERSHOP_GUID pGuid)
{
	__ENTER_FUNCTION
		if(IsInFavorite(pGuid) == FALSE)
		{
			return TRUE;
		}

		for(INT i =0; i<MAX_FAVORITE_SHOPS; i++)
		{
			if( GetFavoriteShopGuid(i) == pGuid )
			{
				_PLAYERSHOP_GUID guidShop;
				SetFavoriteShopGuid(i, guidShop);
				return TRUE;
			}
		}
		return FALSE;
		__LEAVE_FUNCTION
			return FALSE;

}

VOID Obj_Human::UpdateFavorite(_PLAYERSHOP_GUID* pGuidList)
{
	//传入的是确实存在的商店列表
	//根据这个列表刷新自己的收藏家列表,真e心
	__ENTER_FUNCTION
		for(INT i=0; i<MAX_FAVORITE_SHOPS; i++)
		{
			BOOL	bDeleteFlag = TRUE;
			_PLAYERSHOP_GUID OldGuid= GetFavoriteShopGuid(i);
			if(OldGuid.isNull())
				continue;
			for(INT j = 0; j<MAX_FAVORITE_SHOPS; j++)
			{
				if(OldGuid == pGuidList[j])
				{
					bDeleteFlag = FALSE;
					break;				
				}
			}

			if(bDeleteFlag == TRUE)
			{
				DelFavorite(OldGuid);
			}
		}
		__LEAVE_FUNCTION
}


UINT Obj_Human::GetDataID( VOID )const
{
	return  m_DB.GetHumanDB()->m_Sex;
}

///////////////////////////////////////////////////////////
// 复活点相关
///////////////////////////////////////////////////////////
VOID Obj_Human::SetReliveInfo( BOOL bSkillRelive, const _RELIVE_INFO *pReliveInfo )
{
	__ENTER_FUNCTION
		if ( pReliveInfo == NULL )
		{
			Assert( pReliveInfo != NULL && "Obj_Human::SetReliveInfo" );
			return;
		}

		Obj_Character::SetReliveInfo(bSkillRelive, pReliveInfo);

		if ( !bSkillRelive )
		{
			m_DefaultReliveInfo = *pReliveInfo;
		}
		OnReliveInfoChanged();
		__LEAVE_FUNCTION
}

const Obj_Character::_RELIVE_INFO *Obj_Human::GetReliveInfo( BOOL bSkillRelive )const
{
	if ( bSkillRelive && m_bCanSkillRelive )
	{
		return &m_SkillReliveInfo;
	}
	else
	{
		return &m_DefaultReliveInfo;
	}
}

VOID Obj_Human::OnReliveInfoChanged( VOID )
{
	__ENTER_FUNCTION
		if ( m_pAI_Character != NULL )
		{
			((AI_Human*)m_pAI_Character)->OnReliveInfoChanged();
		}
		__LEAVE_FUNCTION
}

///////////////////////////////////////////////////////////
// 复活点相关
///////////////////////////////////////////////////////////
VOID Obj_Human::SetCallOfInfo(const _CALLOF_INFO *pCallOfInfo)
{
	__ENTER_FUNCTION
		if(!IsDie())
		{
			if ( pCallOfInfo == NULL )
			{
				Assert( pCallOfInfo != NULL && "Obj_Human::SetCallOfInfo" );
				return;
			}
			m_CallOfInfo = *pCallOfInfo;
			OnCallOfInfoChanged();
		}
		__LEAVE_FUNCTION
}

VOID Obj_Human::CallOfHuman(GUID_t guidTarget, UINT uDuration)
{
	__ENTER_FUNCTION

		if(guidTarget != INVALID_GUID)
		{
			_CALLOF_INFO infoCallOf;
			infoCallOf.m_guidCaller		= GetGUID();
			infoCallOf.m_Pos			= *getWorldPos();
			infoCallOf.m_SceneID		= getScene()->SceneID();
			infoCallOf.m_uDuration		= uDuration;

			GWCallOfHuman* pMsg = (GWCallOfHuman*)g_pPacketFactoryManager->CreatePacket(PACKET_GW_CALLOFHUMAN);
			pMsg->SetCallOfInfo(&infoCallOf);
			pMsg->SetCallOfTargetGUID(guidTarget);
			g_pServerManager->SendPacket(pMsg, INVALID_ID);
		}

		__LEAVE_FUNCTION
}

const _CALLOF_INFO *Obj_Human::GetCallOfInfo(VOID)const
{
	if(m_CallOfInfo.m_uDuration > 0)
	{
		return &m_CallOfInfo;
	}
	else
	{
		return NULL;
	}
}

VOID Obj_Human::ResetCallOfInfo(VOID)
{
	m_CallOfInfo.Reset();
}

VOID Obj_Human::OnCallOfInfoChanged( VOID )
{
	__ENTER_FUNCTION
		if ( m_pAI_Character != NULL )
		{
			((AI_Human*)m_pAI_Character)->OnCallOfInfoChanged();
		}
		__LEAVE_FUNCTION
}

UINT Obj_Human::GetMoney()
{
	return m_DB.GetMoney();
}


BOOL	Obj_Human::IsVisualPart(HUMAN_EQUIP EquipPoint)
{
	switch(EquipPoint) 
	{
	case HEQUIP_WEAPON:
	case HEQUIP_CAP:
	case HEQUIP_ARMOR:
	case HEQUIP_CUFF:
	case HEQUIP_BOOT:
		{
			return TRUE;
		}
	default:
		return FALSE;
	}
}


INT		Obj_Human::UseStoreMap(UINT BagIndex)
{

	__ENTER_FUNCTION


		Item*		pStoreMapItem = HumanItemLogic::GetItem(this,BagIndex);
	Assert(pStoreMapItem);

	USEITEM_RESULT	Result;
	if(pStoreMapItem->GetItemClass()!=ICLASS_STOREMAP)
	{
		Result	=	USEITEM_TYPE_FAIL;
	}
	else
	{
		// 玩家处于不可行动状态
		if( !IsAlive() )
		{ 
			return USEITEM_SKILL_FAIL;
		}

		STORE_MAP_INFO_TB*	pGET = g_ItemTable.GetStoreMapTB(pStoreMapItem->GetItemTableIndex());
		Assert(pGET);

		if(pGET->m_ScriptID>0)
		{
			Result = (USEITEM_RESULT)getScene()->GetLuaInterface()->ExeScript_DDD(	
				pGET->m_ScriptID,"OnUse",(INT)GetID(),(INT)BagIndex,(INT)getScene()->SceneID() );
		}
		if(Result==USEITEM_SUCCESS)
		{
			ITEM_LOG_PARAM ItemLogParam;
			BOOL bRet=	HumanItemLogic::EraseItem(&ItemLogParam,this,BagIndex);
			if(bRet)
			{
				SaveItemLog(&ItemLogParam);
			}
		}
	}

	return Result;

	__LEAVE_FUNCTION

		return USEITEM_SKILL_FAIL;
}

INT	Obj_Human::UseIdentScroll(UINT BagIndex,UINT TargetBagIndex)
{
	__ENTER_FUNCTION


		Item*		pScrollItem = HumanItemLogic::GetItem(this,BagIndex);
	Assert(pScrollItem);

	Item*		pTargetItem = HumanItemLogic::GetItem(this,TargetBagIndex);
	Assert(pTargetItem);


	USEITEM_RESULT	Result;
	if(pScrollItem->GetItemClass()!=ICLASS_COMITEM
		||pScrollItem->GetItemQual()!=COMITEM_QUAL_MIS
		)
	{
		Result	=	USEITEM_IDENT_TYPE_FAIL;
	}
	else if(pTargetItem->GetItemClass()!=ICLASS_EQUIP||
		pTargetItem->GetItemQual()!=EQUALITY_BLUE)
	{
		Result = USEITEM_IDENT_TARGET_TYPE_FAIL;
	}
	else
	{
		// 玩家处于不可行动状态
		if( !IsAlive() )
		{ 
			return USEITEM_SKILL_FAIL;
		}
		//使3种鉴定卷轴通用 fujia 2008.1.2
		/*switch(pTargetItem->GetEquipPoint()) 
		{
		case HEQUIP_WEAPON	:
		{
		if(pScrollItem->GetItemType() != COMITEM_WPIDENT)
		return USEITEM_IDENT_TARGET_TYPE_FAIL;	
		break;
		}
		case HEQUIP_CAP		:
		case HEQUIP_ARMOR   :	
		case HEQUIP_CUFF	:	
		case HEQUIP_BOOT	:	
		{
		if(pScrollItem->GetItemType() != COMITEM_ARIDENT)
		return USEITEM_IDENT_TARGET_TYPE_FAIL;
		break;
		}
		case HEQUIP_SASH:
		case HEQUIP_RING:		
		case HEQUIP_NECKLACE:
		case HEQUIP_RIDER:
		{
		if(pScrollItem->GetItemType() != COMITEM_NCIDENT)
		return USEITEM_IDENT_TARGET_TYPE_FAIL;
		break;
		}
		default:
		{
		Assert(FALSE);
		}

		}*/

		INT ScrollLevel	=  pScrollItem->GetItemIndex();


		INT	EquipLevel = pTargetItem->GetRequireLevel();

		INT ScrollRequireLevel = pScrollItem->GetItemLevel();


		if(ScrollRequireLevel>GetLevel())
		{
			return USEITEM_LEVEL_FAIL;
		}

#define IDENT_LEVEL_RANGE 9

		if(ScrollLevel+IDENT_LEVEL_RANGE<EquipLevel)
		{
			return USEITEM_IDENT_LEVEL_FAIL;
		}

		if(HumanItemLogic::SetBagItemIdent(this,TargetBagIndex))
		{
			Result = USEITEM_SUCCESS;
		}
		else
		{
			Result = USEITEM_SKILL_FAIL;	
		}
		if(Result==USEITEM_SUCCESS)
		{
			ITEM_LOG_PARAM	ItemLogParam;
			ItemLogParam.OpType	= ITEM_USE_IDENT_LOST;
			ItemLogParam.CharGUID	=	GetGUID();
			ItemLogParam.Count		=	1;
			ItemLogParam.ItemGuid	=	pScrollItem->GetGUID();
			ItemLogParam.ItemType	=	pScrollItem->GetItemTableIndex();
			ItemLogParam.SceneID	=	getScene()->SceneID();
			ItemLogParam.XPos		=	getWorldPos()->m_fX;
			ItemLogParam.ZPos		=	getWorldPos()->m_fZ;

			BOOL bRet	= HumanItemLogic::DecItemLayCount(this,BagIndex);

			if(bRet) SaveItemLog(&ItemLogParam);
		}
	}

	return Result;

	__LEAVE_FUNCTION

		return USEITEM_SKILL_FAIL;
}

BOOL Obj_Human::VerifyItem(VOID)
{
	__ENTER_FUNCTION
		TargetingAndDepletingParams_T& rParams = GetTargetingAndDepletingParams();
	//检查物品是否合法
	INT nBagIndex = rParams.GetBagIndexOfDepletedItem();
	Item*	pBagItem = HumanItemLogic::GetItem(this,nBagIndex);
	INT nItemTableIndex =  rParams.GetItemIndexOfDepletedItem();
	if(pBagItem->IsEmpty() || pBagItem->GetItemTableIndex() != nItemTableIndex)
	{
		if(0<HumanItemLogic::CalcBagItemCount(this, nItemTableIndex))
		{
			nBagIndex=HumanItemLogic::GetItemPosByType(this, nItemTableIndex);
			if(0 <= nBagIndex)
			{
				rParams.SetBagIndexOfDepletedItem(nBagIndex);
				pBagItem = HumanItemLogic::GetItem(this,nBagIndex);
			}
		}
	}
	if(FALSE==pBagItem->IsEmpty())
	{
		if(rParams.GetItemIndexOfDepletedItem()==pBagItem->GetItemTableIndex())
		{
			if(rParams.GetActivatedScript()==pBagItem->GetScriptID())
			{
				if(rParams.GetActivatedSkill()==pBagItem->GetSkillID())
				{
					return TRUE;
				}
			}
		}
	}
	SendOperateResultMsg(OR_CAN_NOT_FIND_SPECIFIC_ITEM);
	return FALSE;
	__LEAVE_FUNCTION
		return FALSE;
}

BOOL Obj_Human::ActivateItem(VOID)
{
	__ENTER_FUNCTION
		SkillInfo_T& rSkillInfo = GetSkillInfo();
	TargetingAndDepletingParams_T& rParams = GetTargetingAndDepletingParams();
	BOOL bRet = FALSE;
	rSkillInfo.Init();
	if(FALSE==g_SkillCore.InstanceSkill(rSkillInfo, *this, rParams.GetActivatedSkill(), rParams.GetSkillLevel()))
	{
		rParams.SetErrCode(OR_INVALID_SKILL);
		rParams.SetErrParam(rParams.GetActivatedSkill());
		return FALSE;
	}
	switch (rSkillInfo.GetSkillType())
	{
	case SKILL_INSTANT_LAUNCHING:
		bRet = g_ScriptLogic.StartLaunching(*this);
		break;
	case SKILL_NEED_CHARGING:
		bRet = g_ScriptLogic.StartCharging(*this);
		break;
	case SKILL_NEED_CHANNELING:
		bRet = g_ScriptLogic.StartChanneling(*this);
		break;
	default:
		bRet = FALSE;
		AssertEx(FALSE,"[Obj_Human::ActiveItem]: Unknow Item script or skill type!!");
		break;
	}
	return bRet;
	__LEAVE_FUNCTION
		return FALSE;
}
BOOL Obj_Human::UseItem(ID_t nBagIndex, ObjID_t nTargetObj, const WORLD_POS& posTarget, 
						PET_GUID_t const& guidTargetPet, ID_t nTargetItem)
{
	__ENTER_FUNCTION

		if(!IsCharacterLogicStopped())
			StopCharacterLogic(TRUE);

	TargetingAndDepletingParams_T& rParams = GetTargetingAndDepletingParams();
	if(FALSE==IsAlive()||FALSE==IsActiveObj())
	{
		rParams.SetErrCode(OR_DIE);
		return FALSE;
	}
	//检查物品是否合法
	Item*	pBagItem = HumanItemLogic::GetItem(this,nBagIndex);
	if(pBagItem->IsEmpty())
	{
		return FALSE;
	}

	AddLogicCount();

	// need add...
	//设置物品使用需要的参数
	rParams.SetTargetBagSlot(nTargetItem);
	rParams.SetBagIndexOfDepletedItem(nBagIndex);
	rParams.SetDepletedItemGuid(pBagItem->GetGUID());
	rParams.SetItemIndexOfDepletedItem(pBagItem->GetItemTableIndex());
	rParams.SetActivatedScript(pBagItem->GetScriptID());
	rParams.SetActivatedSkill(pBagItem->GetSkillID());
	rParams.SetTargetObj(nTargetObj);
	rParams.SetTargetPetGuid(guidTargetPet);
	rParams.SetTargetPosition(posTarget);
	rParams.SetSkillLevel(1);
	//设置结束
	//Activate script and skill
	INT nRet = ActivateItem();
	if (GetCharacterLogic() != CHARACTER_LOGIC_USE_SKILL || TRUE==IsCharacterLogicStopped())
	{
		SetCharacterLogic( CHARACTER_LOGIC_USE_SKILL );
	}
	if (TRUE==GetGlobalActionDelegator().CanDoNextAction(*this))
	{
		if (GetCharacterLogic() == CHARACTER_LOGIC_USE_SKILL || FALSE==IsCharacterLogicStopped())
		{
			StopCharacterLogic();
		}		
	}	
	return nRet;
	__LEAVE_FUNCTION
		return FALSE;

}

INT  Obj_Human::UseGem(UINT GemBagIndex,UINT EquipBagIndex)
{
	__ENTER_FUNCTION

		Assert(GemBagIndex<MAX_BAG_SIZE);
	Assert(EquipBagIndex<MAX_BAG_SIZE);

	Item*		 pGemItem		=	
		HumanItemLogic::GetItem(this,GemBagIndex);

	Assert(pGemItem);

	Item*		pEquipItem		=	
		HumanItemLogic::GetItem(this,EquipBagIndex);

	Assert(pEquipItem);

	USEGEM_RESULT	Result;
	if(pGemItem->GetItemClass()!=ICLASS_GEM)
	{
		Result	= USEGEM_FAIL;	
	}

	if(pEquipItem->GetItemClass()!=ICLASS_EQUIP)
	{
		Result	= USEGEM_FAIL;
	}

	if(pEquipItem->GetGemSlotMax()>0)
	{

		if(pEquipItem->GetEquipGemCount() >= pEquipItem->GetGemSlotMax())
		{
			Result	=	USEGEM_EQUIP_GEM_FULL;
		}
		else
		{
			INT iGemCount, iAttrCount;

			ItemContainer* pContainer = HumanItemLogic::GetContainer(this,EquipBagIndex);
			if(!pContainer)
			{
				return USEGEM_FAIL;
			}

			INT GemIndex;
			g_ItemOperator.AddGemInfo(pContainer,
				pContainer->BagIndex2ConIndex(EquipBagIndex),
				GemIndex,
				pGemItem->GetItemTableIndex());

			iGemCount	= GemIndex;
			iAttrCount	= GemIndex;

			/*
			for( INT i=0; i<pEquipItem->GetGemSlotMax(); ++i )
			{
			if( pEquipItem->GetEquipGemInfo(i).m_GemType == 0 )
			{
			pEquipItem->GetEquipGemInfo(i).m_GemType = pGemItem->GetItemTableIndex();
			iGemCount = iAttrCount = i;
			break;
			}
			}*/



			g_ItemOperator.AddItemAttr(pContainer,
				pContainer->BagIndex2ConIndex(EquipBagIndex),
				pGemItem->GetGemAttr());

			GCDiscardItemResult Msg;
			Msg.setItemTableIndex( pGemItem->GetItemTableIndex());

			ITEM_LOG_PARAM	ItemLogParam;
			ItemLogParam.OpType	=	ITEM_USEGEM_LOST;

			BOOL bRet = HumanItemLogic::EraseItem(&ItemLogParam,this,GemBagIndex); // 删除宝石
			if(bRet)
			{
				SaveItemLog(&ItemLogParam);
			}

			Msg.setResult( DISCARDITEM_SUCCESS );
			Msg.setBagIndex( GemBagIndex );
			((GamePlayer*)GetPlayer())->SendPacket( &Msg );
			Result	=	USEGEM_SUCCESS;

			GCItemInfo equipMsg;
			equipMsg.setIsNull(FALSE);
			equipMsg.setID(EquipBagIndex);
			pEquipItem->SaveValueTo(equipMsg.getItem());
			GetPlayer()->SendPacket(&equipMsg);
			ItemEffectFlush();
		}

	}
	else
	{
		Result	=	USEGEM_CANNT_COMBINE_GEM;
	}

	return Result;

	__LEAVE_FUNCTION

		return USEGEM_FAIL ;
}


INT Obj_Human::UseEquipSkill(INT	iUseEquipSkillOffSet,ObjID_t& Target)
{
	__ENTER_FUNCTION

		Assert(iUseEquipSkillOffSet>=0);
	Assert(iUseEquipSkillOffSet<HEQUIP_NUMBER+MAX_ITEM_SET_ATTR);


	_ITEM_SKILL*	pSkill = &(m_EquipUseSkillEffect[iUseEquipSkillOffSet]);

	if(pSkill->IsActive()) 
	{

		INT iSkillID = pSkill->m_SkillID;


		AI_Character* pAI = GetAIObj();
		if (!pAI) 
		{
			Assert(NULL && "Obj_Human::UseEquipSkill...pAI=NULL...");
			return USEEQUIPSKILL_FAIL;
		}

		ORESULT oResult = pAI->UseSkill(iSkillID, 1, Target, -1.f, -1.f, -1.f, INVALID_ID);

		if( OR_SUCCEEDED( oResult ) )
		{
			return USEEQUIPSKILL_SUCCESS;
		}
	}
	else
	{
		return USEEQUIPSKILL_NO_ACTIVE_EFFECT;
	}

	__LEAVE_FUNCTION
		return USEEQUIPSKILL_FAIL;
}

INT Obj_Human::RemoveGem(UINT BagIndex,UINT GemIndex)
{
	__ENTER_FUNCTION

		Assert(BagIndex<MAX_BAG_SIZE);

	Item* pEquipItem = HumanItemLogic::GetItem(this, BagIndex);
	Assert(pEquipItem);

	if(pEquipItem->IsEmpty())
	{
		return REMOVEGEM_NO_ITEM;
	}

	if(pEquipItem->GetItemClass() != ICLASS_EQUIP)
	{
		return REMOVEGEM_INVALID_EQUIP;
	}

	if(GemIndex >= pEquipItem->GetGemSlotMax())
	{
		return REMOVEGEM_ERROR_GEMINDEX;
	}

	UINT GemType = pEquipItem->GetEquipGemInfo(GemIndex).m_GemType;

	if(GemType == 0)
	{
		return REMOVEGEM_NO_GEM;
	}

	ITEM_LOG_PARAM	ItemLogParam;
	ItemLogParam.OpType		= ITEM_CREATE_REMOVE_GEM;
	ItemLogParam.CharGUID	= GetGUID();
	ItemLogParam.SceneID	= getScene()->SceneID();
	ItemLogParam.XPos		= getWorldPos()->m_fX;
	ItemLogParam.ZPos		= getWorldPos()->m_fZ;

	UINT GemBagIndex;
	if(!HumanItemLogic::CreateItemToBag(&ItemLogParam,this, GemType, GemBagIndex, 0))
	{
		return	REMOVEGEM_BAG_FULL;	
	}

	SaveItemLog(&ItemLogParam);

	GCNotifyEquip Msg;
	Msg.SetBagIndex( GemBagIndex );
	Item* pItem = HumanItemLogic::GetItem(this, GemBagIndex);
	Assert(pItem);
	pItem->SaveValueTo(Msg.GetItem());
	GetPlayer()->SendPacket(&Msg);

	ItemContainer*	pContainer = HumanItemLogic::GetContainer(this,BagIndex);
	if(!pContainer)
	{
		return REMOVEGEM_NO_ITEM;
	}

	g_ItemOperator.DelItemAttr(pContainer,
		pContainer->BagIndex2ConIndex(BagIndex),
		pItem->GetGemAttr());

	g_ItemOperator.DelGemInfo(pContainer,
		pContainer->BagIndex2ConIndex(BagIndex),
		GemIndex);

	ItemEffectFlush();
	return  REMOVEGEM_SUCCESS;

	__LEAVE_FUNCTION

		return REMOVEGEM_UNKNOW_ERROR;
}


VOID	Obj_Human::ChangeMenpai(SKILL_LOG_PARAM* pSkillLog,INT Menpai)
{
	__ENTER_FUNCTION

		if( Menpai<0 || Menpai>=MATTRIBUTE_NUMBER )
		{
			AssertEx( FALSE, "门派取值范围错误！" ) ;
			return ;
		}
		const _XINFA_LIST& rXinFaList = Skill_GetXinFaList();
		const _SKILL_LIST& rSkillList = Skill_GetSkillList();
		m_DB.SetMenPai(Menpai);

		//SkillClass
		_XINFA_DB_LOAD	XinFa;
		INT				nID = 0;
		INT				nScaned = 0;

		XinFa.m_Count = 0;
		while( nID < g_XinFaDataMgr.MAXSIZE && nScaned < g_XinFaDataMgr.Size() )
		{
			Combat_Module::Skill_Module::XinFaData_T const* pXinFaData = g_XinFaDataMgr.GetInstanceByID(nID);
			if( pXinFaData != NULL )
			{
				nScaned ++;
				if( Menpai == pXinFaData->GetMenPai() )
				{
					XinFa.m_aXinFa[XinFa.m_Count].m_nXinFaID	=	nID;
					XinFa.m_aXinFa[XinFa.m_Count].m_nXinFaLevel	=	1;
					XinFa.m_Count ++;
				}
				if( XinFa.m_Count >= 3 )
					break;
			}
			nID++;
		}
		GCSkillClass	XinFaMsg;
		XinFaMsg.setObjID(GetID());
		XinFaMsg.setXinFaList((WORD)XinFa.m_Count, XinFa.m_aXinFa);



		//Skills
		m_DB.SetSkillCount(0);
		pSkillLog->Count	=	0;
		SaveSkillLog(pSkillLog);
		BYTE rCount = rSkillList.m_Count;
		nID = 0;
		nScaned = 0;
		while(nID<g_SkillTemplateDataMgr.MAXSIZE && nScaned<g_SkillTemplateDataMgr.Size())
		{
			Combat_Module::Skill_Module::SkillTemplateData_T const* pSkillTemplateData = g_SkillTemplateDataMgr.GetInstanceByID(nID);
			if(NULL!=pSkillTemplateData)
			{
				++nScaned;
				if( pSkillTemplateData->GetClassByUser() == 0 &&
					/*GetLevel() >= pSkillTemplateData->GetLevelRequirement() &&*/
					( pSkillTemplateData->GetMenPai() == GetMenPai() || pSkillTemplateData->GetMenPai() == INVALID_ID ) )
				{
					m_DB.SetSkillID(nID,rCount);
					Time_t ActiveTime = 0>pSkillTemplateData->GetActiveTime()?-1:0;
					m_DB.SetSkillCount(rCount+1);
					pSkillLog->SkillID = nID;
					pSkillLog->Count	= rCount+1;
					SaveSkillLog(pSkillLog);
					rCount = m_DB.GetSkillCount();
				}
				if(rCount>=MAX_CHAR_SKILL_NUM)
				{
					break;
				}
			}
			++nID;
		}
		for(INT nIdx=rCount;MAX_CHAR_SKILL_NUM>nIdx;++nIdx)
		{
			m_DB.SetSkillID(INVALID_ID,nIdx);
		}
		GCDetailSkillList	SkillMsg;
		SkillMsg.setObjID(GetID());
		WORD nSkillNum = FillSkillList( SkillMsg.getSkillList(), SkillMsg.getLevelList() );
		SkillMsg.setNumSkill( nSkillNum );
		//SkillMsg.setSkillList( (WORD)rSkillList.m_Count, rSkillList.m_aSkill, rXinFaList.m_aXinFa );
		Player* pGamePlayer = GetPlayer();
		ItemEffectFlush();

		SetMP(GetMaxMP());
		SetHP(GetMaxHP());

		SendMsg_RefeshAttrib(); //send detail information to player
		if(NULL!=pGamePlayer)
		{
			pGamePlayer->SendPacket(&XinFaMsg); // send detail XinFa information to player
			pGamePlayer->SendPacket(&SkillMsg); // send detail Skill information to player
		}

		GWChangeMenpai* pMsg = (GWChangeMenpai*)g_pPacketFactoryManager->CreatePacket(PACKET_GW_CHANGEMENPAI);
		pMsg->SetGUID( GetGUID() );
		pMsg->SetMenpai( Menpai );

		g_pServerManager->SendPacket( pMsg, INVALID_ID );

		__LEAVE_FUNCTION
}

WORD Obj_Human::FillSkillList(_OWN_SKILL *paSkill, BYTE *paSkillLevel)
{
	__ENTER_FUNCTION
		Assert( paSkill );
	Assert( paSkillLevel );

	_SKILL_LIST& rSkillList = Skill_GetSkillList();

	WORD index = 0;
	for( BYTE i = 0; i < rSkillList.m_Count; i ++ )
	{
		_OWN_SKILL& skill = rSkillList.m_aSkill[i];
		BYTE level = skill.GetSkillLevel();
		Assert(level<=MAX_SKILL_LEVEL);

		Combat_Module::Skill_Module::SkillTemplateData_T const* pSkillTemplateData = g_SkillTemplateDataMgr.GetInstanceByID(skill.m_nSkillID);
		if( pSkillTemplateData == NULL ) continue;

		if( pSkillTemplateData->GetSkillClass() == INVALID_ID )
		{
			paSkill[index].m_nSkillID = skill.m_nSkillID;
			paSkillLevel[index] = level;
			index++;
		}
		else
		{
			for( BYTE j = 0; j < level; j++ )
			{
				if( pSkillTemplateData->GetSkillInstance(j) == -1 ) break;

				paSkill[index].m_nSkillID = skill.m_nSkillID;
				paSkillLevel[index] = j+1;
				index++;
			}
		}
	}

	return index;

	__LEAVE_FUNCTION

		return 0;
}

INT Obj_Human::SkillCharacter( Obj_Character* pCharacter, SkillID_t SkillID, BOOL bNow )
{
	__ENTER_FUNCTION

		return 0 ;

	__LEAVE_FUNCTION

		return 0 ;
}

VOID Obj_Human::SetAlterExp( INT AlterExp )//改变的经验
{
	__ENTER_FUNCTION

		AlterExp = (INT)(GetWallow()*(FLOAT)AlterExp); //防沉迷经验系数

	UINT CurExp = m_DB.GetExp( ) ;
	SetExp( CurExp+AlterExp ) ;


	//判断是否升级
	//...
	UINT	CurrentExp	=	GetExp();
	UINT	iLevel		=	GetLevel();
	UINT	LevelExp	=	g_LevelExpTbl.Get(iLevel-1);	

	if( CurrentExp>=LevelExp && GetDB()->isSetBit( SETTING_TYPE_GAME, GSF_MANUAL_LEVEL_UP ) == FALSE /*&& iLevel<10*/ )
	{
		CurrentExp-=LevelExp;
		this->SetExp(CurrentExp);
		this->Levelup();

		this->SetHP( this->GetMaxHP() ) ;
		this->SetMP( this->GetMaxMP() ) ;

		GCLevelUpResult ResultMsg;
		ResultMsg.SetRemainExp(CurrentExp);
		ResultMsg.SetLevelUpResult(LEVELUP_SUCCESS);

		GetPlayer()->SendPacket(&ResultMsg);

		GCLevelUp	otherMsg;
		otherMsg.setObjId(this->GetID());
		otherMsg.setLevel(this->GetLevel());

		getScene()->BroadCast(&otherMsg,this,TRUE);

		GWLevelUp* pWorldMsg = (GWLevelUp*)(g_pPacketFactoryManager->CreatePacket(PACKET_GW_LEVEUP));
		pWorldMsg->SetGUID( this->GetGUID() );
		pWorldMsg->SetLevel( this->GetLevel() );

		g_pServerManager->SendPacket( pWorldMsg, INVALID_ID );
	}



	UINT afterExp	= GetExp();
	if( afterExp==CurExp )
	{//经验到达上限后需要客户端提示一下
		SendOperateResultMsg(OR_EXP_FULL);
	}



	__LEAVE_FUNCTION
}
VOID Obj_Human::SetMonsterAlterExp( INT AlterExp )//改变的经验
{
	__ENTER_FUNCTION

		if(GETLOW(GetDoubleExpTime_Num()) <= 0)
		{
			SetDoubleExpTime_Num(1);
		}
		AlterExp =AlterExp * GETLOW(GetDoubleExpTime_Num());
		SetAlterExp(AlterExp);

		__LEAVE_FUNCTION

}
VOID	Obj_Human::SetExp(UINT uExp)
{
#define MAX_EXP_RATE 4
	//限制经验为4倍当前等级升级经验
	UINT	LevelExp =		g_LevelExpTbl.Get(GetLevel()-1);
	if(uExp>LevelExp*MAX_EXP_RATE)
	{
		uExp = LevelExp*MAX_EXP_RATE;
	}
	m_DB.SetExp(uExp);
}

BOOL Obj_Human::IsEnemy(Obj_Character* pCharacter )
{
	__ENTER_FUNCTION

		Assert( pCharacter ) ;
	if(GetID()==pCharacter->GetID())
	{
		return FALSE;
	}
	if(TRUE==IsPartner(pCharacter))
	{
		return FALSE;
	}
	BOOL bIsEnemy = IsEnemyCamp(*pCharacter);

	return bIsEnemy ;

	__LEAVE_FUNCTION

		return FALSE ;
}
BOOL Obj_Human::IsFriend(Obj_Character* pCharacter)
{
	__ENTER_FUNCTION

		Assert( pCharacter ) ;
	return FALSE==IsEnemy(pCharacter);

	__LEAVE_FUNCTION

		return FALSE ;
}
BOOL Obj_Human::IsPartner(Obj_Character* pCharacter)
{
	__ENTER_FUNCTION

		Assert( pCharacter ) ;
	if(NULL==pCharacter)
	{
		return FALSE;
	}
	if(GetID()==pCharacter->GetID())
	{
		return TRUE;
	}
	TeamID_t nTeamIDSelf = __GetTeamID();
	if(INVALID_ID==nTeamIDSelf)
	{
		return FALSE;
	}
	TeamID_t nTeamIDTar = INVALID_ID;
	if(OBJ_TYPE_HUMAN == pCharacter->GetObjType())
	{
		nTeamIDTar = ((Obj_Human*)pCharacter)->__GetTeamID();
	}
	else if(OBJ_TYPE_PET == pCharacter->GetObjType())
	{
		Obj_Character* pOwner=((Obj_Pet*)pCharacter)->GetOwner();

		if(NULL != pOwner&& OBJ_TYPE_HUMAN==pOwner->GetObjType())
		{
			nTeamIDTar = ((Obj_Human*)pOwner)->__GetTeamID();
		}
	}
	if(INVALID_ID==nTeamIDTar)
	{
		return FALSE;
	}
	if(nTeamIDSelf==nTeamIDTar)
	{
		return TRUE;
	}	
	__LEAVE_FUNCTION
		return FALSE ;
}
BOOL Obj_Human::IsMySpouse(Obj_Human& rHuman)
{
	__ENTER_FUNCTION
		// 判断
		if(GetHumanRelation()->GetSpouseGUID() == rHuman.GetGUID())
		{
			return TRUE;
		}
		return FALSE;
		__LEAVE_FUNCTION
			return FALSE;
}

//
//VOID Obj_Human::Relive( )
//{
//__ENTER_FUNCTION
//
//	SetHP(GetMaxHP()/2) ;
//	SetMP(GetMaxMP()/2) ;
//
//
//	//GCNewPlayer Msg ;
//	//Msg.setObjID( GetID() ) ;
//	//Msg.setEquipVer( GetEquipVer() ) ;
//	//Msg.setWorldPos( *getWorldPos() ) ;
//
//	//getScene()->BroadCast( &Msg, this, TRUE ) ;
//	//m_bSendMsgDirty	= TRUE;
//
//	Obj_Character::Relive( ) ;
//
//	SendMsg_RefeshAttrib() ;
//
//__LEAVE_FUNCTION
//}


// 生活技能相关的函数

// 返回背包中 Item 类型的物品数量
/*
INT Obj_Human::HasItemCount(UINT ItemSerial)
{
__ENTER_FUNCTION

Assert(ItemSerial >0);

INT count = 0;

for(UINT i=0; i<MAX_BAG_SIZE; ++i)
{
if( m_DB.GetBagItem(i)->m_ItemIndex == ItemSerial )
{
count += m_DB.GetBagItem(i)->GetItemCount();
}
}

return count;
__LEAVE_FUNCTION
return 0 ;
}*/


//是否携带物品
BOOL Obj_Human::IsCarrayItem(UINT ItemType,UINT ItemCount) 
{
	__ENTER_FUNCTION

		UINT count =0;

	count = HumanItemLogic::CalcEquipItemCount(this,ItemType);

	count += HumanItemLogic::CalcBagItemCount(this,ItemType);

	return count>= ItemCount;

	__LEAVE_FUNCTION
		return 0 ;
}


VOID Obj_Human::InterruptCurrentAbilityOpera()
{
	__ENTER_FUNCTION
		Ability *pAbility = g_pAbilityManager->GetAbility(m_LastOpera.m_AbilityID);
	if (pAbility != NULL)
	{
		pAbility->OnProcInterrupt(this);
	}

	reset_AbilityOpera();

	__LEAVE_FUNCTION
}

ORESULT Obj_Human::Do_UseAbility( VOID )
{
	__ENTER_FUNCTION

		AddLogicCount();

	GCAbilityAction Msg;
	Msg.setObjID( GetID() );
	Msg.setLogicCount( GetLogicCount() );
	Msg.setAction( m_LastOpera.m_AbilityID );
	Msg.setPrescriptionID( m_LastOpera.m_PresID );
	Msg.setTargetID( m_LastOpera.m_Obj );
	Msg.setBeginOrEnd(GCAbilityAction::ABILITY_BEGIN);
	getScene()->BroadCast( &Msg, this, TRUE );

	SetCharacterLogic( CHARACTER_LOGIC_USE_ABILITY );
	m_LastOpera.m_nCurTime = 0;
	return OR_OK;

	__LEAVE_FUNCTION
		return OR_ERROR;
}

BOOL Obj_Human::Obj_Logic_UseAbility( UINT uTime )
{
	__ENTER_FUNCTION

		m_LastOpera.m_nCurTime += (INT)(GetLogicTime());

	if( m_LastOpera.m_nCurTime >= m_LastOpera.m_nMaxTime )
	{
		Ability* pAbility;
		ORESULT res;
		GamePlayer *pGamePlayer = (GamePlayer*)(GetPlayer());

		Assert( pGamePlayer != NULL );

		pAbility = g_pAbilityManager->GetAbility(m_LastOpera.m_AbilityID);
		Assert( pAbility != NULL );
		//GetHumanAI()->PushCommand_Idle();

		//GCAbilityAction StopMsg;
		//StopMsg.setObjID( GetID() );
		//StopMsg.setLogicCount( GetLogicCount() );
		//StopMsg.setAction( m_LastOpera.m_AbilityID );
		//StopMsg.setTargetID( m_LastOpera.m_Obj );
		//StopMsg.setBeginOrEnd( GCAbilityAction::ABILITY_END );
		//getScene()->BroadCast( &StopMsg, this, TRUE );

		//m_bSendMsgDirty	= TRUE;

		// reset_AbilityOpera(); // 这里不重设生活技能数据，以免今后需要批量合成物品，但是在用户指令发出的时候进行重设
		StopCharacterLogic(FALSE);

		res = pAbility->OnProcOver(this);

		// 将 res 形成消息发送出去
		if( res != OR_OK )
		{
			GCAbilityResult Msg;
			Msg.SetAbilityID( m_LastOpera.m_AbilityID );
			Msg.SetPrescriptionID( m_LastOpera.m_PresID );
			Msg.setResult( res );
			pGamePlayer->SendPacket( &Msg );
		}

	}
	else
	{ // 做一些合法性验证
		Ability* pAbility;

		pAbility = g_pAbilityManager->GetAbility(m_LastOpera.m_AbilityID);
		Assert( pAbility != NULL );

		if( pAbility->OperationToolID()!=INVALID_ID
			&& HumanItemLogic::CalcEquipItemCount(this, pAbility->OperationToolID())<1
		 )
		{
			pAbility->OnProcInterrupt(this);
		}
	}

	return TRUE;

	__LEAVE_FUNCTION

		return FALSE;
}

VOID Obj_Human::OnCharacterLogicStopped(BOOL bAbortive)
{
	__ENTER_FUNCTION

		ENUM_CHARACTER_LOGIC eLogic = GetCharacterLogic();
	if(eLogic == CHARACTER_LOGIC_MOVE)
	{
		m_DB.SetDBPosition(*getWorldPos());
	}

	switch(eLogic)
	{
	case CHARACTER_LOGIC_USE_ABILITY:
		{
			if(bAbortive)
			{
				Ability *pAbility = g_pAbilityManager->GetAbility(m_LastOpera.m_AbilityID);
				Assert( pAbility != NULL && "Obj_Human::OnCharacterLogicStopped");
				if(pAbility != NULL)
				{
					pAbility->OnProcInterrupt(this);
				}
			}
			//// 不管是强行的还是自然停的都要求发停止
			//GCAbilityAction StopMsg;
			//StopMsg.setObjID( GetID() );
			//StopMsg.setLogicCount( GetLogicCount() );
			//StopMsg.setAction( m_LastOpera.m_AbilityID );
			//StopMsg.setPrescriptionID( m_LastOpera.m_PresID );
			//StopMsg.setTargetID( m_LastOpera.m_Obj );
			//StopMsg.setBeginOrEnd( GCAbilityAction::ABILITY_END );
			//getScene()->BroadCast( &StopMsg, this, TRUE );

			//if(bAbortive)
			{
				GCCharStopAction	msgStopAction;
				msgStopAction.setObjID( GetID() );
				msgStopAction.setLogicCount( GetLogicCount() );
				msgStopAction.setStopTime( (UINT)(m_LastOpera.m_nCurTime) );

				getScene()->BroadCast( &msgStopAction, this, TRUE ) ;
			}
		}
		break;
	default:
		Obj_Character::OnCharacterLogicStopped(bAbortive);
		break;
	}

	__LEAVE_FUNCTION
}

// 生活技能相关的函数

VOID Obj_Human::OnKillObject( ObjID_t idObj )
{
	__ENTER_FUNCTION
		Obj_Character *pObj = (Obj_Character*)(getScene()->GetObjManager()->GetObj( idObj ));
	if ( pObj == NULL )
		return ;

	if(pObj->GetObjType( ) != Obj::OBJ_TYPE_MONSTER)
		return;

	//if ( !IsCharacterObj( pObj->GetObjType() ) )
	//	return ;
	Obj_Monster* pMonster = (Obj_Monster*)pObj;

	UINT i,uDataID;
	uDataID = pObj->GetDataID();
	for(i=0;i<MAX_CHAR_MISSION_NUM;i++)
	{
		//保证任务脚本只执行一次,以后是否需要挪到更合适的地方?
		const _OWN_MISSION* pMission =	GetMission(i) ;
		if( !pMission->IsActiveMission() || !pMission->IsFlags_KillObject() )
			continue ;

		INT nMission = pMission->m_idMission;

		BOOL bToggle = FALSE;	
		for(INT j=0;j<pMonster->m_nKillCount;j++)
		{
			if(pMonster->m_sKillObj[j].m_nMissionId == nMission)
			{
				bToggle = TRUE;
				break;
			}
		}

		if(!bToggle)
		{
			if(pMonster->m_nKillCount < Obj_Monster::BEKILL_MISSION_NUM)
			{
				pMonster->m_sKillObj[pMonster->m_nKillCount++].m_nMissionId = nMission;
				getScene()->GetLuaInterface()->ExeScript_DDDD( 
					pMission->m_idScript,
					"OnKillObject",
					(INT)getScene()->SceneID(),
					(INT)GetID(),
					(INT)uDataID,
					(INT)idObj );
			}
			else
			{
				AssertEx(pMonster->m_nKillCount<Obj_Monster::BEKILL_MISSION_NUM,"overflow exception");
				pMonster->m_nKillCount--;
				break;
			}	
		}
	}
	__LEAVE_FUNCTION
}

VOID Obj_Human::OnItemChanged( UINT uItemDataID )
{
	__ENTER_FUNCTION

		UINT i;
	for(i=0;i<MAX_CHAR_MISSION_NUM;i++)
	{	
		const _OWN_MISSION* pMission = GetMission(i) ;
		if( !pMission->IsActiveMission() || !pMission->IsFlags_ItemChanged() )
			continue ;

		getScene()->GetLuaInterface()->ExeScript_DDD( 
			pMission->m_idScript, 
			"OnItemChanged",
			(INT)getScene()->SceneID(),
			(INT)GetID(),
			(INT)uItemDataID );
	}

	__LEAVE_FUNCTION
}

VOID Obj_Human::OnPetChanged( UINT uPetDataID )
{
	__ENTER_FUNCTION

		UINT i;
	for(i=0;i<MAX_CHAR_MISSION_NUM;i++)
	{	
		const _OWN_MISSION* pMission = GetMission(i) ;
		if( !pMission->IsActiveMission() || !pMission->IsFlags_PetChanged() )
			continue ;

		getScene()->GetLuaInterface()->ExeScript_DDD( 
			pMission->m_idScript, 
			"OnPetChanged",
			(INT)getScene()->SceneID(),
			(INT)GetID(),
			(INT)uPetDataID );
	}

	__LEAVE_FUNCTION
}

VOID Obj_Human::OnDie( ObjID_t idKiller )
{
	__ENTER_FUNCTION

		ResetCallOfInfo();

	Scene *pScene = getScene();
	if(pScene != NULL)
	{
		pScene->OnSceneHumanDie(this, idKiller);
	}

	Obj_Character::OnDie(idKiller);

	// 如果是被老手带着的新手，则扣除老手的善恶值
	//if( GetLevel() <= g_Config.m_ConfigInfo.m_nMemberLevel )
	//{
	//	if( GetTeamInfo()->HasTeam() && GetTeamInfo()->IsLeader() != TRUE )
	//	{ // 组队非队长
	//		Obj_Human* pTeamLeader = NULL;

	//		if( GetTeamInfo()->Leader()->m_SceneID != getScene()->SceneID() )
	//		{
	//			return;
	//		}

	//		pTeamLeader = getScene()->GetHumanManager()->GetHuman(GetTeamInfo()->Leader()->m_ObjID);
	//		if( pTeamLeader == NULL )
	//		{
	//			Assert(FALSE);
	//			return;
	//		}

	//		if( pTeamLeader->GetLevel() >= g_Config.m_ConfigInfo.m_nLevelNeeded
	//		 && IsInValidRadius( pTeamLeader, g_Config.m_ConfigInfo.m_fGoodBadRadius )
	//		 )
	//		{
	//			INT nPenalty;

	//			nPenalty = g_Config.m_ConfigInfo.m_nPenaltyWhenMemberDie;
	//			nPenalty = pTeamLeader->DecGoodBadValue( nPenalty );
	//			// nPenalty 是实际扣除值
	//			// 发送消息给客户端，以显示信息提示
	//			GCNotifyGoodBad Msg;
	//			Msg.SetNotifyMode( NOTIFY_GOODBAD_NEWBIEDIE );
	//			Msg.SetValue( nPenalty );

	//			pTeamLeader->GetPlayer()->SendPacket( &Msg );
	//		}
	//	}
	//}

	__LEAVE_FUNCTION
}

VOID Obj_Human::OnEnterArea( UINT uAreaID )
{
	__ENTER_FUNCTION

		UINT i;

	//一个区域可被数个任务响应,需要和策划商榷
	for(i=0;i<MAX_CHAR_MISSION_NUM;i++)
	{
		const _OWN_MISSION* pMission = GetMission(i) ;
		if( !pMission->IsActiveMission() || !pMission->IsFlags_EnterArea() )
			continue ;

		getScene()->GetLuaInterface()->ExeScript_DDD( 
			pMission->m_idScript, 
			DEF_ON_ENTER_AREA_FUNC_NAME,
			(INT)getScene()->SceneID(),
			(INT)GetID(),
			(INT)uAreaID );
	}

	__LEAVE_FUNCTION
}

Packet *Obj_Human::CreateNewObjPacket( VOID )
{
	__ENTER_FUNCTION

		if ( getScene() != NULL )
		{
			if( !IsAlive() )
			{//尸体
				GCNewPlayer_Death *pPacket = (GCNewPlayer_Death*)(getScene()->m_pPacket_NewPlayer_Death);
				pPacket->setObjID( GetID() );
				pPacket->setWorldPos( *(getWorldPos()) );
				pPacket->setDir( getDir() );
				pPacket->setEquipVer( GetEquipVer() );
				pPacket->setMoveSpeed( GetMoveSpeed() ) ;
				return pPacket;
			}
			else if( IsMoving() )
			{
				GCNewPlayer_Move *pPacket = (GCNewPlayer_Move*)(getScene()->m_pPacket_NewPlayer_Move);
				pPacket->setObjID( GetID() ) ;
				pPacket->setHandleID( GetLogicCount() ) ;
				pPacket->setWorldPos( *getWorldPos() ) ;
				pPacket->setTargetPos( *GetFinalTarPos() ) ;
				pPacket->setEquipVer( GetEquipVer() ) ;
				pPacket->setMoveSpeed( GetMoveSpeed() ) ;
				return pPacket;
			}
			else
			{
				GCNewPlayer *pPacket = (GCNewPlayer*)(getScene()->m_pPacket_NewPlayer);
				pPacket->setObjID( GetID() ) ;
				pPacket->setWorldPos( *(getWorldPos()) ) ;
				pPacket->setDir( getDir() );
				pPacket->setEquipVer( GetEquipVer() ) ;
				pPacket->setMoveSpeed( GetMoveSpeed() ) ;
				return pPacket;
			}
		}
		else
		{
			Assert( getScene() != NULL && "Obj_Human::CreateNewObjPacket" );
			return NULL;
		}

		__LEAVE_FUNCTION
			return NULL ;
}

VOID Obj_Human::DestroyNewObjPacket( Packet *pPacket )
{
}

VOID Obj_Human::OnMissionHaveDoneFlagsChanged( MissionID_t idMission )
{
	__ENTER_FUNCTION
		m_AttrBackUp.m_bMissionHaveDoneFlagsChanged	= TRUE;
	//GamePlayer *pGamePlayer = (GamePlayer*)(GetPlayer());
	//Assert( pGamePlayer != NULL && "Obj_Human::OnMissionHaveDoneFlagsChanged" );
	//if ( pGamePlayer != NULL )
	//{
	//	GCMissionHaveDoneFlags msgMissionHaveDoneFlags;
	//	msgMissionHaveDoneFlags.SetMissionHaveDoneFlags( &(GetConstMissionList()->m_aMission[uIndexMission]) );
	//	pGamePlayer->SendPacket( &msgMissionHaveDoneFlags );
	//}
	__LEAVE_FUNCTION
}

VOID Obj_Human::OnMissionParamChanged( UINT uIndexMission, UINT uIndexParam ,int index)
{
	__ENTER_FUNCTION
		GamePlayer *pGamePlayer = (GamePlayer*)(GetPlayer());
	Assert( pGamePlayer != NULL && "Obj_Human::OnMissionParamChanged" );
	if ( pGamePlayer != NULL )
	{	
		GCMissionModify msgMissionModify;
		msgMissionModify.SetFlag(index) ;
		switch(index)
		{
		case 0:
			{
				const _OWN_MISSION* pMission = &(GetConstMissionList()->m_aMission[uIndexMission]) ;
				msgMissionModify.SetMission( pMission );
				pGamePlayer->SendPacket( &msgMissionModify );

				MISSION_LOG_PARAM sParam ;
				sParam.CharGUID = GetGUID();
				sParam.OPType	= MISSION_OP_PARAM ;
				sParam.SceneID	= getScene()->SceneID() ;
				sParam.XPos		= getWorldPos()->m_fX ;
				sParam.ZPos		= getWorldPos()->m_fZ ;
				sParam.idMission= pMission->m_idMission ;
				sParam.idScript = pMission->m_idScript ;
				sParam.yFlags	= pMission->m_yFlags ;
				memcpy( sParam.aParam, pMission->m_aParam, sizeof(UINT)*MAX_MISSION_PARAM_NUM ) ;
				SaveMissionLog(&sParam) ;
			}
			break;
		case 1:
			{
				msgMissionModify.SetMissionData( (GetConstMissionList()->m_aMissionData) );
				pGamePlayer->SendPacket( &msgMissionModify );

				MISSION_LOG_PARAM sParam ;
				sParam.CharGUID = GetGUID();
				sParam.OPType	= MISSION_OP_DATA ;
				sParam.SceneID	= getScene()->SceneID() ;
				sParam.XPos		= getWorldPos()->m_fX ;
				sParam.ZPos		= getWorldPos()->m_fZ ;
				sParam.nDataIndex	  = uIndexMission ;
				sParam.nDoneFlagValue = uIndexParam ;
				SaveMissionLog(&sParam) ;
			}
			break;
		}
	}
	__LEAVE_FUNCTION
}

VOID Obj_Human::OnAddMission( UINT uIndex )
{
	__ENTER_FUNCTION
		GamePlayer *pGamePlayer = (GamePlayer*)(GetPlayer());
	Assert( pGamePlayer != NULL && "Obj_Human::OnAddMission" );
	const _OWN_MISSION* pMission = &(GetConstMissionList()->m_aMission[uIndex]) ;
	if ( pGamePlayer != NULL )
	{
		GCMissionAdd msgMissionAdd;
		msgMissionAdd.SetMission( pMission );
		pGamePlayer->SendPacket( &msgMissionAdd );
	}
	MISSION_LOG_PARAM sParam ;
	sParam.CharGUID = GetGUID();
	sParam.OPType	= MISSION_OP_ADDMISSION ;
	sParam.SceneID	= getScene()->SceneID() ;
	sParam.XPos		= getWorldPos()->m_fX ;
	sParam.ZPos		= getWorldPos()->m_fZ ;
	sParam.idMission= pMission->m_idMission ;
	sParam.idScript = pMission->m_idScript ;
	sParam.yFlags	= pMission->m_yFlags ;
	memcpy( sParam.aParam, pMission->m_aParam, sizeof(UINT)*MAX_MISSION_PARAM_NUM ) ;
	SaveMissionLog(&sParam) ;

	__LEAVE_FUNCTION
}

VOID Obj_Human::OnRemoveMission( MissionID_t idMission )
{
	__ENTER_FUNCTION
		GamePlayer *pGamePlayer = (GamePlayer*)(GetPlayer());
	Assert( pGamePlayer != NULL && "Obj_Human::OnRemoveMission" );
	if ( pGamePlayer != NULL )
	{
		GCMissionRemove msgMissionRemove;
		msgMissionRemove.SetMissionID( idMission );
		pGamePlayer->SendPacket( &msgMissionRemove );
	}
	MISSION_LOG_PARAM sParam ;
	sParam.CharGUID = GetGUID();
	sParam.OPType	= MISSION_OP_DELMISSION ;
	sParam.SceneID	= getScene()->SceneID() ;
	sParam.XPos		= getWorldPos()->m_fX ;
	sParam.ZPos		= getWorldPos()->m_fZ ;
	sParam.idMission= idMission ;
	SaveMissionLog(&sParam) ;
	__LEAVE_FUNCTION
}

//VOID Obj_Human::OnAddCanPickMissionItem( UINT uItemDataID )
//{
//__ENTER_FUNCTION
//	GamePlayer *pGamePlayer = (GamePlayer*)(GetPlayer());
//	Assert( pGamePlayer != NULL && "Obj_Human::OnAddCanPickMissionItem" );
//	if ( pGamePlayer != NULL )
//	{
//		GCAddCanPickMissionItem msg;
//		msg.SetItemDataID(uItemDataID );
//		pGamePlayer->SendPacket( &msg );
//	}
//__LEAVE_FUNCTION
//}
//
//VOID Obj_Human::OnRemoveCanPickMissionItem( UINT uItemDataID )
//{
//__ENTER_FUNCTION
//	GamePlayer *pGamePlayer = (GamePlayer*)(GetPlayer());
//	Assert( pGamePlayer != NULL && "Obj_Human::OnRemoveCanPickMissionItem" );
//	if ( pGamePlayer != NULL )
//	{
//		GCRemoveCanPickMissionItem msg;
//		msg.SetItemDataID(uItemDataID );
//		pGamePlayer->SendPacket( &msg );
//	}
//__LEAVE_FUNCTION
//}

const _MISSION_DB_LOAD *Obj_Human::GetMissionList( VOID )
{
	return GetDB()->GetMissionDB();
}

const _SETTING_DB_LOAD *Obj_Human::GetSettingList( VOID )
{
	return GetDB()->GetSettingDB();
}

const _MISSION_DB_LOAD *Obj_Human::GetConstMissionList( VOID )const
{
	return m_DB.GetMissionDB();
}

const _SETTING_DB_LOAD *Obj_Human::GetConstSettingList( VOID )const
{
	return m_DB.GetSettingDB();
}

ORESULT Obj_Human::AddMission( MissionID_t idMission, ScriptID_t idScript, BOOL bKillObjectEvent/* = TRUE*/, BOOL bEnterAreaEvent/* = TRUE*/, BOOL bItemChangedEvent/* = TRUE*/ )
{
	__ENTER_FUNCTION
		if ( GetConstMissionList()->m_Count >= MAX_CHAR_MISSION_NUM )
			return OR_MISSION_LIST_FULL;

	UINT uIndex = GetMissionIndexByID( idMission );
	if (uIndex != UINT_MAX )
		return OR_MISSION_HAVE;

	uIndex = UINT_MAX;
	UINT i;
	for ( i = 0; i < MAX_CHAR_MISSION_NUM; i++ )
	{
		if ( GetConstMissionList()->m_aMission[i].m_idMission == INVALID_ID )
		{
			uIndex = i;
			break;
		}
	}

	if (uIndex == UINT_MAX )
		return OR_ERROR;

	const _OWN_MISSION *pMission=GetMission(uIndex);

	m_DB.SetMission(uIndex,idMission,idScript);

	m_DB.SetFlags_KillObject( uIndex,bKillObjectEvent );
	m_DB.SetFlags_EnterArea( uIndex,bEnterAreaEvent );
	m_DB.SetFlags_ItemChanged( uIndex,bItemChangedEvent );

	m_DB.SetMissionCount(GetMissionList()->m_Count+1);

	OnAddMission(uIndex );

	return OR_OK;

	__LEAVE_FUNCTION

		return OR_ERROR;
}

ORESULT Obj_Human::AddMissionEx( MissionID_t idMission, ScriptID_t idScript )
{
	__ENTER_FUNCTION
		if ( GetConstMissionList()->m_Count >= MAX_CHAR_MISSION_NUM )
			return OR_MISSION_LIST_FULL;

	UINT uIndex = GetMissionIndexByID( idMission );
	if (uIndex != UINT_MAX )
		return OR_MISSION_HAVE;

	uIndex = UINT_MAX;
	UINT i;
	for ( i = 0; i < MAX_CHAR_MISSION_NUM; i++ )
	{
		if ( GetConstMissionList()->m_aMission[i].m_idMission == INVALID_ID )
		{
			uIndex = i;
			break;
		}
	}

	if (uIndex == UINT_MAX )
		return OR_ERROR;

	const _OWN_MISSION *pMission=GetMission(uIndex);

	m_DB.SetMission(uIndex,idMission,idScript);

	m_DB.SetMissionCount(GetMissionList()->m_Count+1);

	OnAddMission(uIndex );

	return OR_OK;

	__LEAVE_FUNCTION

		return OR_ERROR;
}

ORESULT Obj_Human::SetMissionEvent( MissionID_t idMission, INT EventID/*TASK_EVENT*/ )
{
	__ENTER_FUNCTION

		UINT uIndex = GetMissionIndexByID( idMission );
	if (uIndex == UINT_MAX )
		return OR_ERROR;

	const _OWN_MISSION *pMission=GetMission(uIndex);
	if( pMission==NULL )
		return OR_ERROR;

	switch( EventID )
	{
	case TASK_EVENT_KILLOBJ:
		m_DB.SetFlags_KillObject( uIndex, TRUE );
		break ;
	case TASK_EVENT_ENTERAREA:
		m_DB.SetFlags_EnterArea( uIndex, TRUE );
		break ;
	case TASK_EVENT_ITEMCHANGED:
		m_DB.SetFlags_ItemChanged( uIndex, TRUE );
		break ;
	case TASK_EVENT_PETCHANGED:
		m_DB.SetFlags_PetChanged( uIndex, TRUE );
		break ;
	default :
		Assert(FALSE) ;
		break ;
	}

	return OR_OK;

	__LEAVE_FUNCTION

		return OR_ERROR;
}


VOID Obj_Human::DelMission( MissionID_t idMission )
{
	__ENTER_FUNCTION
		UINT uIndex = GetMissionIndexByID( idMission );
	if (uIndex == UINT_MAX )
		return ;

	DelMissionByIndex(uIndex );
	__LEAVE_FUNCTION
}

VOID Obj_Human::DelMissionByIndex( UINT uIndex )
{
	__ENTER_FUNCTION

		if (uIndex < MAX_CHAR_MISSION_NUM && GetConstMissionList()->m_aMission[uIndex].m_idMission != INVALID_ID )
		{
			const _OWN_MISSION *pMission = GetMission(uIndex);

			OnRemoveMission( pMission->m_idMission );

			m_DB.ClearMission(uIndex);

		}

		__LEAVE_FUNCTION
}

UINT Obj_Human::GetMissionIndexByID( MissionID_t idMission )const
{
	__ENTER_FUNCTION
		UINT i;
	for ( i = 0; i < MAX_CHAR_MISSION_NUM; i++ )
	{
		if ( GetConstMissionList()->m_aMission[i].m_idMission == idMission )
		{
			return i;
		}
	}
	return UINT_MAX;
	__LEAVE_FUNCTION
		return UINT_MAX;
}


VOID Obj_Human::AddTimer(INT sceneTimerIndex)		
{
	__ENTER_FUNCTION

		for(INT i=0; i<g_Config.m_ConfigInfo.m_nMaxHumanUseTimer; i++)
		{
			if(m_pUseTimer[i] == -1)
			{
				m_pUseTimer[i] = sceneTimerIndex;	

				m_nUseTimer++; 
				break;
			}	
		}	
		__LEAVE_FUNCTION
}

VOID Obj_Human::RemoveTimer(INT sceneTimerIndex)	
{
	__ENTER_FUNCTION

		for(INT i=0; i<g_Config.m_ConfigInfo.m_nMaxHumanUseTimer; i++)
		{
			if(m_pUseTimer[i] == sceneTimerIndex)
			{
				m_pUseTimer[i] = sceneTimerIndex;	

				m_nUseTimer--;	
			}
		}
		__LEAVE_FUNCTION
}

INT Obj_Human::GetUseTimerCount()	
{
	return m_nUseTimer;		
}

INT Obj_Human::GetMaxTimerCount()	
{		
	return g_Config.m_ConfigInfo.m_nMaxHumanUseTimer;	
}

BOOL Obj_Human::HaveTimer(INT sceneTimerIndex)
{
	__ENTER_FUNCTION

		Assert(sceneTimerIndex>=0 && sceneTimerIndex < g_Config.m_ConfigInfo.m_MaxTimerCount);
	if(sceneTimerIndex>=0 && sceneTimerIndex < g_Config.m_ConfigInfo.m_MaxTimerCount)
	{
		for(INT i=0; i<g_Config.m_ConfigInfo.m_nMaxHumanUseTimer; i++)
		{
			if(m_pUseTimer[i] == sceneTimerIndex)
				return TRUE;
		}

	}

	__LEAVE_FUNCTION

		return FALSE;
}

VOID Obj_Human::SetPortraitID( INT nID )
{
	m_DB.SetPortraitID(nID); 
}

INT Obj_Human::GetPortraitID( VOID ) const
{
	return m_DB.GetPortraitID(); 
}

VOID Obj_Human::SetName( const CHAR *pszName )
{
}

VOID Obj_Human::SetTitle( const CHAR *pszTitle )
{
	__ENTER_FUNCTION

		if(tstricmp(pszTitle, m_DB.GetCurTitle()) != 0)
		{
			m_AttrBackUp.m_bTitleModified = TRUE;
			m_DB.SetCurTitle(pszTitle, (BYTE)strlen(pszTitle)); 
		}

		CHAR szWorldTitle[MAX_CHARACTER_TITLE] = {0};

		if( GetTitleType() == _TITLE::MOOD_TITLE )
		{
			strncpy(szWorldTitle, "", sizeof(szWorldTitle));
		}
		else
		{
			strncpy(szWorldTitle, GetTitle(), sizeof(szWorldTitle));
		}

		GWUpdateTitle* pMsg = (GWUpdateTitle*)g_pPacketFactoryManager->CreatePacket(PACKET_GW_UPDATETITLE);
		pMsg->SetGUID( GetGUID() );
		pMsg->SetTitle( szWorldTitle );

		g_pServerManager->SendPacket( pMsg, INVALID_ID );

		__LEAVE_FUNCTION
}

VOID Obj_Human::SetTitleType( BYTE	nType)
{
	__ENTER_FUNCTION
		m_AttrBackUp.m_bTitleModified = TRUE;
	m_DB.SetCurTitleType(nType); 
	__LEAVE_FUNCTION
}

VOID Obj_Human::SetHP( INT nHP )
{
	INT nMaxHP = GetMaxHP();
	if( nHP > nMaxHP )
	{
		nHP = nMaxHP;
	}
	m_DB.SetHP( nHP );
}

VOID Obj_Human::SetMP( INT nMP )
{
	INT nMaxMP = GetMaxMP();
	if( nMP > nMaxMP )
	{
		nMP = nMaxMP;
	}
	m_DB.SetMP( nMP );
}

VOID Obj_Human::SetLevel( INT nLevel )
{
	if(nLevel != m_DB.GetLevel())
	{
		m_DB.SetLevel( nLevel );
		OnLevelChanged();
	}
}

VOID Obj_Human::SetPKValue( INT nValue )
{
	m_DB.SetPKValue( nValue );
}

VOID Obj_Human::SetCurrentPetGUID( PET_GUID_t guid )
{
	m_DB.SetCurrentPetGUID( guid );
}

VOID	Obj_Human::InitialSoldList()
{
	__ENTER_FUNCTION

		memset(m_ItemHasBeenSold, 0,MAX_BOOTH_SOLD_NUMBER*sizeof(_ITEM));
	memset(m_SoldPrice, 0,MAX_BOOTH_SOLD_NUMBER*sizeof(UINT));

	m_nCurSold = 0;

	//初始化container
	_ITEMCONTAINER_INIT	containInit;
	containInit.m_nContainerSize	=	MAX_BOOTH_SOLD_NUMBER;
	m_SoldContainer.Init(&containInit);

	for(INT i=0;i<MAX_BOOTH_SOLD_NUMBER;i++)
	{
		_ITEM_INIT	itemInit(&m_ItemHasBeenSold[i]);
		m_SoldContainer.GetItem(i)->Init(&itemInit);
	}

	__LEAVE_FUNCTION
}

VOID	Obj_Human::AddToSoldList(INT index, UINT uPrice)
{
	__ENTER_FUNCTION

		//不管什么直接覆盖掉
		m_nCurSold++;
	m_nCurSold = (m_nCurSold<MAX_BOOTH_SOLD_NUMBER)? m_nCurSold:0; 
	g_ItemOperator.EraseItem(&m_SoldContainer, m_nCurSold);//清空当前格子

	INT result = 0;
	ItemContainer*	pBagContainer = HumanItemLogic::GetContainer(this, index);
	//指定格
	result = 
		g_ItemOperator.MoveItem
		(
		pBagContainer,
		pBagContainer->BagIndex2ConIndex(index),
		&m_SoldContainer,
		m_nCurSold
		);

	if(result>=0)
	{
		m_SoldPrice[m_nCurSold] = uPrice;
		GCItemInfo  Msg;
		Msg.setIsNull(TRUE);
		Msg.setID(index);
		m_pPlayer->SendPacket(&Msg);
	}
	else
	{
		Assert(FALSE);
	}

	__LEAVE_FUNCTION
}

BOOL	Obj_Human::GetCurFromSoldList(_ITEM& itemref, UINT& uPrice, BYTE& nCoinType )
{
	__ENTER_FUNCTION

		//次函数获得当前物品的实际数据
		if(ITEMISVALID(m_ItemHasBeenSold[m_nCurSold]))
		{
			itemref	= m_ItemHasBeenSold[m_nCurSold];
			uPrice  = m_SoldPrice[m_nCurSold];
			Item* pItem = m_SoldContainer.GetItem(m_nCurSold);
			if( pItem )
				nCoinType = pItem->GetCoinType();
			else
				nCoinType = 0;
			return	TRUE; 
		}
		else
		{
			INT temp = m_nCurSold--;
			m_nCurSold = (m_nCurSold<0)? (MAX_BOOTH_SOLD_NUMBER-1):m_nCurSold; 
			while(m_nCurSold != temp)
			{
				if(ITEMISVALID(m_ItemHasBeenSold[m_nCurSold]))
					break;
				m_nCurSold--;
				m_nCurSold = (m_nCurSold<0)? (MAX_BOOTH_SOLD_NUMBER-1):m_nCurSold; 
			}
			if(m_nCurSold == temp)
			{//回购表已空
				return FALSE;
			}
			else
			{
				itemref	= m_ItemHasBeenSold[m_nCurSold];
				uPrice  = m_SoldPrice[m_nCurSold];
				Item* pItem = m_SoldContainer.GetItem(m_nCurSold);
				if( pItem )
					nCoinType = pItem->GetCoinType();
				else
					nCoinType = 0;
				return	TRUE; 
			}
		}
		__LEAVE_FUNCTION

			return FALSE ;
}

BOOL	Obj_Human::RecieveOneFromSoldList()
{
	return HumanItemLogic::RecieveItemToBag(this, &m_SoldContainer, m_nCurSold);
}

VOID	Obj_Human::DeleteFromSoldList()
{
	g_ItemOperator.EraseItem(&m_SoldContainer, m_nCurSold--);
	m_nCurSold = (m_nCurSold<0)? (MAX_BOOTH_SOLD_NUMBER-1):m_nCurSold; 
}

VOID	Obj_Human::ClearSoldList()
{
	ZeroMemory(m_ItemHasBeenSold, MAX_BOOTH_SOLD_NUMBER*sizeof(_ITEM));
	m_nCurSold = 0;
}

//金钱变化时
VOID	Obj_Human::NotifyMoneyChange(UINT uAmount, BOOL bIsReceive)
{
	__ENTER_FUNCTION
		/*	if(bIsReceive)
		{
		GCChat msgChat;
		CHAR szChat[128] = {0};
		sprintf(szChat, "@*;SrvMsg;ALL:GMDP_CharacterData_Money_Gain;%u", uAmount);
		INT Size = (INT)strlen(szChat) ;
		msgChat.SetChatType( CHAT_TYPE_SELF) ;
		msgChat.SetContexSize( Size ) ;
		msgChat.SetContex( szChat ) ;
		msgChat.SetSourNameSize( (BYTE)strlen( GetName() )) ;
		msgChat.SetSourName( GetName()) ;
		msgChat.SetSourID( GetID()) ;
		GetPlayer()->SendPacket(&msgChat);
		}
		else
		{
		GCChat msgChat;
		CHAR szChat[128] = {0};
		sprintf(szChat, "@*;SrvMsg;ALL:GMDP_CharacterData_Money_Lost;%u", uAmount);
		INT Size = (INT)strlen(szChat) ;
		msgChat.SetChatType( CHAT_TYPE_SELF) ;
		msgChat.SetContexSize( Size ) ;
		msgChat.SetContex( szChat ) ;
		msgChat.SetSourNameSize( (BYTE)strlen( GetName() )) ;
		msgChat.SetSourName( GetName()) ;
		msgChat.SetSourID( GetID()) ;
		GetPlayer()->SendPacket(&msgChat);
		}
		*/
		__LEAVE_FUNCTION

}


/////////////////////////////////////////////////////////////////////////////////
//obj 公共属性接口


/////////////////////////////////////////////////////////////////////////////////
//character 公共属性接口


/////////////////////////////////////////////////////////////////////////////////
//human 公共属性接口
const INT Obj_Human::__GetSex( ) const//性别 human
{
	return 0 ;
}
VOID Obj_Human::__SetSex( const INT sex )
{
}
const UINT Obj_Human::__GetCreateDate( ) const//创建时间 human
{
	return 0 ;
}
VOID Obj_Human::__SetCreateDate( const UINT createdate )
{
}
const CHAR* Obj_Human::__GetNick( ) const//昵称 human
{
	return NULL ;
}
VOID Obj_Human::__SetNick( const CHAR* nick )
{
}
BOOL Obj_Human::__IsPasswordSetup()
{
	return ( strlen( GetDB()->GetPasswd() ) >= MIN_PWD );
}
BOOL Obj_Human::__IsPasswordUnlock()
{
	return m_bIsPasswdUnlock;
}
VOID Obj_Human::__LockPassword() // 输入二级密码错误，则调用
{
	m_bIsPasswdUnlock = FALSE;
}
VOID Obj_Human::__UnlockPassword() // 输入二级密码正确
{
	m_bIsPasswdUnlock = TRUE;
}
const CHAR* Obj_Human::__GetPassword( ) //二级密码 human
{
	return GetDB()->GetPasswd();
}
BOOL Obj_Human::__SetPassword( const CHAR* password )
{
	if ( password == NULL
		|| strlen(password) < MIN_PWD
		|| strlen(password) >= MAX_PWD
		)
	{
		Assert( password );
		Assert( strlen(password) >= MIN_PWD );
		Assert( strlen(password) < MAX_PWD );
		return FALSE;
	}

	GetDB()->SetPasswd( password );
	return TRUE;
}

VOID Obj_Human::__DelPassword( ) // 删除二级密码
{
	GetDB()->DelPasswd();
}
UINT Obj_Human::__GetPasswordDeleteTime( ) // 强制解除二级密码的时间
{
	return GetDB()->GetPasswdDeleteTime();
}
VOID Obj_Human::__SetPasswordDeleteTime( UINT uTime ) // 设置强制解除二级密码的时间
{
	GetDB()->SetPasswdDeleteTime( uTime );
}

UINT Obj_Human::__GetPasswordDeleteRemainTime( ) // 得到强制解除密码的剩余时间
{
	if( __GetPasswordDeleteTime() > 0 )
	{
		INT nReturnTime;

		UINT	DeltaTime = (UINT)g_pTimeManager->GetANSITime() - __GetPasswordDeleteTime();
		nReturnTime = g_Config.m_ConfigInfo.m_nDeleteDelayTime - DeltaTime;
		if( nReturnTime < 0 )
		{
			return 0;
		}

		return nReturnTime;
	}

	return UINT_MAX;
}

BOOL Obj_Human::__IsValidToDeletePassword( ) // 是否满足强制解除二级密码条件
{
	__ENTER_FUNCTION

		if( __GetPasswordDeleteTime() > 0 )
		{
			INT nTime;

			nTime = INT(g_pTimeManager->GetANSITime() - __GetPasswordDeleteTime());

			if( nTime >= g_Config.m_ConfigInfo.m_nDeleteDelayTime )
			{
				return TRUE;
			}
		}

		__LEAVE_FUNCTION

			return FALSE;
}

UINT Obj_Human::__GetHairColor( ) const//头发颜色 human
{
	return m_DB.GetHairColor() ;
}
VOID Obj_Human::__SetHairColor( UINT haircolor )
{
	m_DB.SetHairColor(haircolor);
	GetDB()->SetHairColor(haircolor);
}

BYTE Obj_Human::__GetFaceColor( ) const//脸颜色 human
{
	return m_DB.GetFaceColor() ;
}
VOID Obj_Human::__SetFaceColor( BYTE facecolor )
{
	m_DB.SetFaceColor(facecolor);
}
BYTE Obj_Human::__GetHairModel( ) const//头发模型 human
{
	return m_DB.GetHairModel() ;
}
VOID Obj_Human::__SetHairModel( BYTE hairmodel )
{
	m_DB.SetHairModel(hairmodel);
}
BYTE Obj_Human::__GetFaceModel( ) const//脸模型 human
{
	return m_DB.GetFaceModel() ;
}
VOID Obj_Human::__SetFaceModel( BYTE facemodel )
{
	m_DB.SetFaceModel(facemodel);
}
const UINT Obj_Human::__GetOnlineTime( ) const//在线时间 human
{
	return 0 ;
}
VOID Obj_Human::__SetOnlineTime( const UINT onlinetime )
{
}
const UINT Obj_Human::__GetLastLevelUpTime( ) const//上次升级时间 human
{
	return 0 ;
}
VOID Obj_Human::__SetLastLevelUpTime( const UINT lastleveluptime )
{
}
const UINT Obj_Human::__GetLastLoginTime( ) const//上次登录时间 human
{
	return 0 ;
}
VOID Obj_Human::__SetLastLoginTime( const UINT lastlogintime )
{
}
const UINT Obj_Human::__GetLastLogoutTime( ) const//上次登出时间 human
{
	return 0 ;
}
VOID Obj_Human::__SetLastLogoutTime( const UINT lastlogouttime )
{
}
const INT Obj_Human::__GetBagItemCount( ) const//背包中物品数量 human
{
	return 0 ;
}
VOID Obj_Human::__SetBagItemCount( const INT bagitemcount )
{
}
const _ITEM* Obj_Human::__GetBagItem( const INT bagindex ) const//背包中某个位置的物品 human
{
	return m_DB.GetBagItem(bagindex);
}
VOID Obj_Human::__SetBagItem( const INT bagindex, const _ITEM* item )
{
	m_DB.PutBagDB(item,bagindex);
}
const INT Obj_Human::__GetBankItemCount( ) const//银行中物品数量 human
{
	return m_DB.GetBankItemCount();
}
VOID Obj_Human::__SetBankItemCount( const INT Bankitemcount )
{
	m_DB.SetBankItemCount(Bankitemcount);
}
const _ITEM* Obj_Human::__GetBankItem( const INT bankindex ) const//银行中某个位置的物品 human
{
	return m_DB.GetBankItem(bankindex);
}
VOID Obj_Human::__SetBankItem( const INT bankindex, const _ITEM* item )
{
	m_DB.SetBankItem(bankindex, item);
}
const INT	Obj_Human::__GetBankEndIndex( ) const//当前银行的大小
{
	return m_DB.GetBankEndIndex();
}
VOID Obj_Human::__SetBankEndIndex( const INT bankindex )
{
	return m_DB.SetBankEndIndex(bankindex);
}
const INT	Obj_Human::__GetBankMoney( ) const//当前银行内的钱数
{
	return m_DB.GetBankMoney();
}
VOID Obj_Human::__SetBankMoney( const INT money )
{
	m_DB.SetBankMoney(money);
}


const INT Obj_Human::__GetEquipItemCount( ) const//装备数量 human
{
	return 0 ;
}
VOID Obj_Human::__SetEquipItemCount( const INT equipitemcount )
{
}
const _ITEM* Obj_Human::__GetEquipItem( const INT equipindex ) const//身上某个位置的装备 human
{
	return NULL ;
}
VOID Obj_Human::__SetEquipItem( const INT equipindex, const _ITEM* item )
{
}
const INT Obj_Human::__GetMissionCount( ) const//接受的任务数量 human
{
	return 0 ;
}
VOID Obj_Human::__SetMissionCount( const INT missioncount )
{
}
const _OWN_MISSION* Obj_Human::__GetMission( const INT missionindex ) const//某个任务数据 human
{
	return NULL ;
}
VOID Obj_Human::__SetMission( const INT missionindex, _OWN_MISSION* mission )
{
}
const BOOL Obj_Human::__IsMissionHaveDone( MissionID_t missionid ) const//判断某个任务是否完成 human
{
	return FALSE ;
}
VOID Obj_Human::__SetMissionDoneFalg( MissionID_t missionid, BOOL flag )
{
}
const BOOL Obj_Human::__IsAbilityHaveLearned(AbilityID_t abilityid) const
{
	__ENTER_FUNCTION

		if( abilityid<1 || abilityid>MAX_CHAR_ABILITY_NUM )
		{
			return FALSE;
		}

		if( GetAbilityList()->Get_Ability(abilityid).m_Level > 0 )
		{
			return TRUE;
		}

		__LEAVE_FUNCTION

			return FALSE;
}
const INT Obj_Human::__GetAbilityLevel( const AbilityID_t abilityid ) const//某个生活技能级别 human
{
	__ENTER_FUNCTION

		if( abilityid<1 || abilityid>MAX_CHAR_ABILITY_NUM )
		{
			return 0;
		}

		return GetAbilityList()->Get_Ability(abilityid).m_Level;

		__LEAVE_FUNCTION

			return 0 ;
}
VOID Obj_Human::__SetAbilityLevel( const AbilityID_t abilityid, INT lvl)
{
	__ENTER_FUNCTION

		m_DB.SetAbilityLevel(abilityid,lvl);

	__LEAVE_FUNCTION
}
const INT Obj_Human::__GetAbilityExp( const AbilityID_t abilityid ) const//某个生活技能熟练度 human
{
	__ENTER_FUNCTION

		if( abilityid<1 || abilityid>MAX_CHAR_ABILITY_NUM )
		{
			return 0;
		}

		return GetAbilityList()->Get_Ability(abilityid).m_Exp;

		__LEAVE_FUNCTION

			return 0 ;
}
VOID Obj_Human::__SetAbilityExp( const AbilityID_t abilityid, INT exp )
{
	__ENTER_FUNCTION
		m_DB.SetAbilityExp(abilityid,exp);
	__LEAVE_FUNCTION
}
const BOOL Obj_Human::__IsPrescrHaveLearned( const PrescriptionID_t prescrid ) const //某个配方是否学会 human
{
	__ENTER_FUNCTION

		INT idx;

	idx = (INT)prescrid;
	if( idx<0 || idx>=MAX_ABILITY_PRESCRIPTION_NUM )
	{
		Assert(FALSE);
		return FALSE;
	}

	CHAR cPrescr;
	cPrescr = GetAbilityList()->m_aPrescr[idx>>3];
	cPrescr >>= idx%8;

	if( cPrescr & 0x01 )
	{
		return TRUE;
	}

	__LEAVE_FUNCTION

		return FALSE;
}
VOID Obj_Human::__SetPrescrLearnedFlag( const PrescriptionID_t prescrid, BOOL flag )
{
	__ENTER_FUNCTION
		m_DB.SetPrescrLearnedFlag(prescrid,flag);
	__LEAVE_FUNCTION
}
const _ITEM_EFFECT* Obj_Human::__GetItemEffect( const INT index ) const//装备效果 human
{
	return &m_pItemEffect[index] ;
}
VOID Obj_Human::__SetItemEffect( const INT index, _ITEM_EFFECT* itemeffect )
{
}
const _ITEM_VALUE Obj_Human::__GetItemValue( const INT index ) const//装备效果值 human
{
	return m_pItemEffect[index].m_Attr ;
}
VOID Obj_Human::__SetItemValue( const INT index, _ITEM_VALUE value)
{
	m_pItemEffect[index].m_Attr = value ;
}

const UINT Obj_Human::__GetLastTurnPickTime() const
{
	return	m_uLastTurnPickTime;
}

VOID Obj_Human::__SetLastTurnPickTime(UINT uTime)
{
	m_uLastTurnPickTime = uTime;
}

const TeamID_t Obj_Human::__GetTeamID( ) const //队伍号 human
{
	return m_TeamInfo.GetTeamID();
}
VOID Obj_Human::__SetTeamID( const TeamID_t teamid )
{
	m_TeamInfo.SetTeamID( teamid );
}
BOOL Obj_Human::__IsTeamLeader( ) const // 是否队长
{
	return m_TeamInfo.IsLeader();
}
const INT Obj_Human::__GetTeamMemberCount( ) const //队伍中成员数量 human
{
	return m_TeamInfo.GetTeamMemberCount();
}
const TEAMMEMBER* Obj_Human::__GetTeamMember( const INT memberindex ) const //取得队伍中某个成员
{
	return m_TeamInfo.GetTeamMember( memberindex );
}
VOID Obj_Human::__AddTeamMember( const TEAMMEMBER* member )
{
	m_TeamInfo.AddMember( member );
}
const INT Obj_Human::__GetTeamSceneMemberCount( ) const //队伍中同场景成员数量 human
{
	return m_TeamInfo.GetSceneMemberCount();
}
const ObjID_t Obj_Human::__GetTeamSceneMember( const INT memberindex ) const //取得队伍中某同场景成员的 OBJID
{
	return m_TeamInfo.GetSceneMemberObjID(memberindex);
}

VOID Obj_Human::__SetTeamFollowFlag( BOOL flag ) // 设置队伍跟随状态
{
	m_TeamInfo.SetTeamFollowFlag(flag);
}

const BOOL Obj_Human::__GetTeamFollowFlag( ) const // 获得队伍跟随状态
{
	return m_TeamInfo.GetTeamFollowFlag();
}

VOID Obj_Human::__AddFollowedMember( const _FOLLOWEDMEMBER& FollowedMember) // 增加一个跟随的队员
{
	m_TeamInfo.AddFollowedMember( FollowedMember );
}

VOID Obj_Human::__DelFollowedMember( GUID_t guid ) // 移出一个跟随队员
{
	m_TeamInfo.DelFollowedMember( guid );
}

const INT Obj_Human::__GetFollowedMembersCount() const // 得到跟随状态的队友数量
{
	return m_TeamInfo.GetFollowedMembersCount();
}

const _FOLLOWEDMEMBER* Obj_Human::__GetFollowedMember( INT i ) const // 得到第 i 个跟随的队友
{
	Assert( i>-1 && i<m_TeamInfo.GetFollowedMembersCount() );
	return m_TeamInfo.GetFollowedMember(i);
}

VOID Obj_Human::__ClearFollowedMembers() // 清除所有的跟随队友列表
{
	m_TeamInfo.ClearFollowedMembers();
}

const FLOAT Obj_Human::__GetTeamFollowSpeed( ) const // 得到组队跟随的速度
{
	return m_fTeamFollowSpeed;
}

VOID Obj_Human::__SetTeamFollowSpeed( FLOAT fSpeed ) // 设置组队跟随的速度
{
	__ENTER_FUNCTION

		m_fTeamFollowSpeed = fSpeed;

	GCCharBaseAttrib Msg;
	Msg.setObjID( GetID() );
	Msg.setMoveSpeed( fSpeed );

	getScene()->BroadCast( &Msg, this, TRUE );

	__LEAVE_FUNCTION
}

VOID Obj_Human::__OutOfTeamFollowRange() // 超出组队跟随范围
{
	if( m_OutofTeamFollowRangeTime == 0 )
	{
		m_OutofTeamFollowRangeTime = g_pTimeManager->GetANSITime();
	}
	else if( g_pTimeManager->GetANSITime() - m_OutofTeamFollowRangeTime > g_Config.m_ConfigInfo.m_nTimeForLoseFollow )
	{
		__StopTeamFollow();
		m_OutofTeamFollowRangeTime = 0;
	}
}

VOID Obj_Human::__InTeamFollowRange() // 在组队跟随范围内
{
	if( m_OutofTeamFollowRangeTime > 0 )
	{
		m_OutofTeamFollowRangeTime = 0;
	}
}

const BOOL Obj_Human::__GetTeamFollowSpeedUp( ) const // 获得组队跟随加速状态
{
	return m_bTeamFollowSpeedUp;
}

VOID Obj_Human::__SetTeamFollowSpeedUp( BOOL bSpeedUp ) // 设置组队跟随加速状态
{
	m_bTeamFollowSpeedUp = bSpeedUp;
}

VOID Obj_Human::__StopTeamFollow( BOOL bWorldFlag ) // 停止跟随
{
	__ENTER_FUNCTION

		TeamInfo* pTeamInfo = GetTeamInfo();
	if( pTeamInfo->HasTeam() == FALSE )
	{
		Assert(FALSE);
		return;
	}

	Obj_Human* pLeader;
	BOOL bLeaderExist = TRUE;

	if ( __GetTeamFollowFlag() )
	{
		if ( pTeamInfo->IsLeader() )
		{ // 队长退出
			for( INT i=__GetFollowedMembersCount()-1; i>=0; --i)
			{ // 每个人都自动退出
				Obj_Human* pMember;

				pMember = __GetFollowedMember(i)->m_pHuman;

				if ( pMember != NULL )
				{
					pMember->__ClearFollowedMembers();
					pMember->GetHumanAI()->PushCommand_StopTeamFollow();
					pMember->__SetTeamFollowFlag( FALSE );

					GCReturnTeamFollow RetMsg;

					RetMsg.SetReturn( TF_RESULT_STOP_FOLLOW );
					RetMsg.SetGUID( pMember->GetGUID() );

					pMember->GetPlayer()->SendPacket( &RetMsg );
				}
			}

			pLeader = this;
		}
		else
		{
			pLeader = __GetFollowedMember(0)->m_pHuman;
			if( pLeader==NULL )
			{ // 没有找到队长
				bLeaderExist = FALSE;
			}

			GUID_t guid = GetGUID();

			__DelFollowedMember( guid ); // 先自己把自己清了
			GetHumanAI()->PushCommand_StopTeamFollow();
			__SetTeamFollowFlag( FALSE );

			for( INT i=__GetFollowedMembersCount()-1; i>=0; --i)
			{ // 其他跟随状态的队友都移出他
				Obj_Human* pMember = __GetFollowedMember(i)->m_pHuman;

				if ( pMember!=NULL )
				{
					pMember->__DelFollowedMember( guid );
				}
			}

			__ClearFollowedMembers(); // 清除整个跟随列表

			GCReturnTeamFollow RetMsg;

			RetMsg.SetReturn( TF_RESULT_STOP_FOLLOW );
			RetMsg.SetGUID( guid );

			GetPlayer()->SendPacket( &RetMsg ); // 发给自己

			if ( bLeaderExist )
			{
				pLeader->GetPlayer()->SendPacket( &RetMsg ); // 发给队长
			}
		}

		if ( bWorldFlag )
		{
			GWStopTeamFollow* pMsg = (GWStopTeamFollow*)g_pPacketFactoryManager->CreatePacket(PACKET_GW_STOP_TEAMFOLLOW);
			pMsg->SetGUID( GetGUID() );
			g_pServerManager->SendPacket( pMsg, INVALID_ID );
		}

		if ( bLeaderExist )
		{
			GCTeamFollowList Msg;
			Msg.SetObjID( pLeader->GetID() );

			for( INT i=0; i<pLeader->__GetFollowedMembersCount(); ++i )
			{
				Msg.AddFollowMember( pLeader->__GetFollowedMember(i)->m_GUID );
			}

			getScene()->BroadCast( &Msg, pLeader, TRUE );
		}
	}

	__LEAVE_FUNCTION
}

VOID Obj_Human::ChangeScene( SceneID_t sSceneID, SceneID_t dSceneID, const WORLD_POS& pos, BYTE uDir, BYTE bFlag )
{
	__ENTER_FUNCTION

		GCNotifyChangeScene Msg ;
	Msg.setCurrentSceneID( sSceneID ) ;
	Msg.setTargetSceneID( dSceneID ) ;
	Msg.setTargetPos( &pos ) ;
	Msg.setTargetDir( uDir ) ;
	Msg.setFlag( bFlag );

	Scene* pDestScene = g_pSceneManager->GetScene(dSceneID) ;
	if( pDestScene )
	{
		if( pDestScene->GetSceneType() != SCENE_TYPE_GAMELOGIC )
		{
			GetDB()->SetDBBakScene( sSceneID ) ;
			GetDB()->SetDBBakPosition( *getWorldPos() ) ;
		}
		if( pDestScene->GetSceneType() == SCENE_TYPE_COPY )
		{
			if( pDestScene->GetSceneStatus() != SCENE_STATUS_RUNNING )
			{//如果目标场景不是运行状态的副本，不能发送传送消息
				return ;
			}

			pDestScene->m_CopyData.AddMemberGUID(GetGUID()) ;
		}
	}

	GetPlayer()->SendPacket( &Msg ) ;

	SetChangeSceneFlag( TRUE );

	__LEAVE_FUNCTION
}

VOID Obj_Human::CreateCity( SceneID_t PortSceneID)
{
	__ENTER_FUNCTION
		//暂时一个场景只能挂一个城市
		Scene* pPortScene = g_pSceneManager->GetScene(PortSceneID);
	for(INT	i = 0; i<MAX_CITY_PORT; i++)
	{
		if(pPortScene->m_CityData.m_ScenePortList[i] != INVALID_ID)
		{
			return;
		}
	}

	GWCityApplyNewCity* pMsgToWorld = (GWCityApplyNewCity*)g_pPacketFactoryManager->CreatePacket(PACKET_GW_CITYAPPLYNEWCITY);
	pMsgToWorld->SetSceneID(PortSceneID);
	pMsgToWorld->SetPlayerGuid(GetGUID());

	g_pServerManager->SendPacket( pMsgToWorld, INVALID_ID );
	__LEAVE_FUNCTION

}
VOID Obj_Human::DeleteCity( SceneID_t PortSceneID, INT iSceneIndex)
{
	__ENTER_FUNCTION
		Scene* pPortScene = g_pSceneManager->GetScene(PortSceneID);
	if(pPortScene->m_CityData.m_ScenePortList[iSceneIndex] != INVALID_ID)
	{//存在此城市
		Scene* pCityScene = g_pSceneManager->GetScene(pPortScene->m_CityData.m_ScenePortList[iSceneIndex]);
		Assert(pCityScene);
		if(!pCityScene->m_SceneInitData.m_CityData.m_Guid.isNull() && pCityScene->m_SceneInitData.m_nDataType == SCENE_TYPE_CIT)
		{//城市ID有效
			_CITY_GUID CityGuid = pCityScene->m_SceneInitData.m_CityData.m_Guid;
			GWCityClose* pMsgToWorld = (GWCityClose*)g_pPacketFactoryManager->CreatePacket(PACKET_GW_CITYCLOSE);
			pMsgToWorld->SetCityGuid(CityGuid);
			pMsgToWorld->SetPlayerGuid(GetGUID());
			g_pServerManager->SendPacket( pMsgToWorld, INVALID_ID );
		}
	}
	__LEAVE_FUNCTION
}

VOID Obj_Human::ChangeCityBuilding( SceneID_t SceneID, INT BuildingID, INT BuildingLevel)
{
	__ENTER_FUNCTION
		Scene* pCityScene = g_pSceneManager->GetScene(SceneID);
	Assert(pCityScene);
	if(!pCityScene->m_SceneInitData.m_CityData.m_Guid.isNull() && pCityScene->m_SceneInitData.m_nDataType == SCENE_TYPE_CIT)
	{
		_CITY_GUID	CityGuid = pCityScene->m_SceneInitData.m_CityData.m_Guid;
		INT			iParam[MAX_IPARAM_NUM] = {0};

		GWCityOpt* pMsgToWorld = (GWCityOpt*)g_pPacketFactoryManager->CreatePacket(PACKET_GW_CITYOPT);
		pMsgToWorld->SetCityGuid(CityGuid);
		pMsgToWorld->SetOpt(GWCityOpt::OPT_CHANGE_BUILDING_DATA);
		iParam[0] = BuildingID;
		iParam[1] = BuildingLevel;
		pMsgToWorld->SetiParam(iParam);
		g_pServerManager->SendPacket( pMsgToWorld, INVALID_ID );
	}
	__LEAVE_FUNCTION
		return;
}

VOID Obj_Human::OnArmorAbrasion(VOID)
{
	__ENTER_FUNCTION
		// 装备耐久度
		GCDetailEquipList msgDetailEquipList;
	msgDetailEquipList.setObjID(GetID());
	msgDetailEquipList.SetAskMode(ASK_EQUIP_SET);
	BOOL bModified = FALSE;
	Item *pEquipItem;
	INT i;
	for(i = 0; i < HEQUIP_NUMBER; i++)
	{
		if(HEQUIP_WEAPON != i)
		{
			pEquipItem = GetEquipContain()->GetItem(i);
			if(pEquipItem != NULL && !pEquipItem->IsEmpty())
			{
				INT nDamagePoint = pEquipItem->GetDamagePoint();
				nDamagePoint++;
				if(nDamagePoint > g_Config.m_ConfigInfo.m_EquipmentDamagePoint)
				{
					nDamagePoint = 0;
					BYTE byDurPoints = pEquipItem->GetDurPoints();
					if(byDurPoints > 0)
					{
						byDurPoints--;
						g_ItemOperator.SetItemDur(GetEquipContain(), i, (INT)byDurPoints);

						_ITEM itemTemp;
						pEquipItem->SaveValueTo( &itemTemp );
						msgDetailEquipList.SetEquipData((HUMAN_EQUIP)i,&itemTemp);
						bModified = TRUE;
					}
				}
				g_ItemOperator.SetItemDamagePoint(GetEquipContain(), i, nDamagePoint);
			}
		}
	}
	if(bModified)
	{
		GetPlayer()->SendPacket(&msgDetailEquipList);
	}
	__LEAVE_FUNCTION
}

VOID Obj_Human::OnWeaponAbrasion(VOID)
{
	__ENTER_FUNCTION
		Item *pEquipItem = GetEquipContain()->GetItem(HEQUIP_WEAPON);
	if(pEquipItem != NULL && !pEquipItem->IsEmpty())
	{
		INT nDamagePoint = pEquipItem->GetDamagePoint();
		nDamagePoint++;
		if(nDamagePoint > g_Config.m_ConfigInfo.m_EquipmentDamagePoint)
		{
			nDamagePoint = 0;
			BYTE byDurPoints = pEquipItem->GetDurPoints();
			if(byDurPoints > 0)
			{
				byDurPoints--;
				g_ItemOperator.SetItemDur(GetEquipContain(), HEQUIP_WEAPON, (INT)byDurPoints);

				GCDetailEquipList msgDetailEquipList;
				msgDetailEquipList.SetAskMode(ASK_EQUIP_SET);
				msgDetailEquipList.setObjID(GetID());
				_ITEM itemTemp;
				pEquipItem->SaveValueTo( &itemTemp );
				msgDetailEquipList.SetEquipData(HEQUIP_WEAPON,&itemTemp);
				GetPlayer()->SendPacket(&msgDetailEquipList);
			}
		}
		g_ItemOperator.SetItemDamagePoint(GetEquipContain(), HEQUIP_WEAPON, nDamagePoint);
	}
	__LEAVE_FUNCTION
}

VOID Obj_Human::UpdateViewCharacter(VOID)
{
	__ENTER_FUNCTION

		Obj_Character::UpdateViewCharacter();

	if(getZoneID() != INVALID_ID)
	{
		// 反隐数据改变
		if(m_nView_PrevLevel != GetLevel()
			|| m_nView_PrevDetectLevel != GetDetectLevel())
		{
			OBJLIST listObj;
			getScene()->ScanObj( getZoneID(), MAX_REFESH_OBJ_ZONE_RADIUS, &(listObj) );

			Obj *pFindObj;
			//BOOL bPrevCanViewTarget;
			BOOL bCurrentCanViewTarget;
			BYTE i;
			for ( i = 0; i < listObj.m_Count; i++ )
			{
				pFindObj				= listObj.m_aObj[i];
				//bPrevCanViewTarget		= pFindObj->IsPrevCanViewMe(this);
				bCurrentCanViewTarget	= pFindObj->IsCanViewMe(this);
				if(/*bPrevCanViewTarget && */!bCurrentCanViewTarget)
				{
					Packet *pPacket = pFindObj->CreateDeleteObjPacket();
					if ( pPacket != NULL )
					{
						GetPlayer()->SendPacket( pPacket );

						pFindObj->DestroyDeleteObjPacket( pPacket );
					}
				}
				else/* if(!bPrevCanViewTarget && bCurrentCanViewTarget)*/
				{
					Packet *pPacket = pFindObj->CreateNewObjPacket();
					if ( pPacket != NULL )
					{
						GetPlayer()->SendPacket( pPacket );

						pFindObj->DestroyNewObjPacket( pPacket );
					}
				}
			}
			// 放在最后
			m_nView_PrevLevel		= GetLevel();
			m_nView_PrevDetectLevel	= GetDetectLevel();
		}
	}

	__LEAVE_FUNCTION
}


VOID Obj_Human::UpdateTitlesToClient()
{
	__ENTER_FUNCTION

		//PACKET_ALL_TITLES_MSG
		GCCharAllTitles::TitleId titlelist[MAX_TITLE_ID_SIZE];
	int num = 0;
	if(GetLevelTitle())
	{
		titlelist[num].m_titleid		=	_TITLE::LEVEL_TITLE;
		titlelist[num++].m_titleData	=	static_cast<SHORT>(GetLevelTitle());
	}
	if(GetLifeTitle())
	{
		titlelist[num].m_titleid		=	_TITLE::LIFE_TITLE;
		titlelist[num++].m_titleData	=	static_cast<SHORT>(GetLifeTitle());
	}
	if(GetRankTitle())
	{
		titlelist[num].m_titleid		=	_TITLE::RANK_TITLE;
		titlelist[num++].m_titleData	=	static_cast<SHORT>(GetRankTitle());
	}
	if(GetStoryTitle())
	{
		titlelist[num].m_titleid		=	_TITLE::STORY_TITLE;
		titlelist[num++].m_titleData	=	static_cast<SHORT>(GetStoryTitle());
	}
	if(GetKillBossTitle())
	{
		titlelist[num].m_titleid		=	_TITLE::KILLBOSS_TITLE;
		titlelist[num++].m_titleData	=	static_cast<SHORT>(GetKillBossTitle());
	}
	if(GetTreasureTitle())
	{
		titlelist[num].m_titleid		=	_TITLE::TREASURE_TITLE;
		titlelist[num++].m_titleData	=	static_cast<SHORT>(GetTreasureTitle());
	}

	for(int i = 0; i<MAX_DYNAMIC_TITLE_SIZE; i++ )
	{
		if(GetDyTitle(i))
		{
			titlelist[num].m_titleid		=	(_TITLE::DY_TITLE0 + i);
			titlelist[num++].m_titleData	=	GetDyTitle(i);
		}
	}

	GCCharAllTitles::TitleString titlestrlist[MAX_STRING_TITLE_SIZE];
	int strnum = 0;
	const CHAR* szTemp = NULL;
	if(strlen(GetNickName())!=0)
	{
		szTemp = GetNickName();
		titlestrlist[strnum].m_titleid	=	_TITLE::NICK_TITLE;
		titlestrlist[strnum].m_strlength = (BYTE)strlen(szTemp);
		memset(titlestrlist[strnum].m_szTitle, 0, MAX_CHARACTER_TITLE);
		memcpy(titlestrlist[strnum].m_szTitle, szTemp, titlestrlist[strnum].m_strlength);
		strnum++;
	}
	if(strlen(GetSpouseName())!=0)
	{
		szTemp = GetSpouseName();
		titlestrlist[strnum].m_titleid	=	_TITLE::SPOUSE_TITLE;
		titlestrlist[strnum].m_strlength = (BYTE)strlen(szTemp);
		memset(titlestrlist[strnum].m_szTitle, 0, MAX_CHARACTER_TITLE);
		memcpy(titlestrlist[strnum].m_szTitle, szTemp, titlestrlist[strnum].m_strlength);
		strnum++;
	}
	if(strlen(GetBangPaiName())!=0)
	{
		szTemp = GetBangPaiName();
		titlestrlist[strnum].m_titleid	=	_TITLE::BANGPAI_TITLE;
		titlestrlist[strnum].m_strlength = (BYTE)strlen(szTemp);
		memset(titlestrlist[strnum].m_szTitle, 0, MAX_CHARACTER_TITLE);
		memcpy(titlestrlist[strnum].m_szTitle, szTemp, titlestrlist[strnum].m_strlength);
		strnum++;
	}
	if(strlen(GetJieBaiName())!=0)
	{
		szTemp = GetJieBaiName();
		titlestrlist[strnum].m_titleid	=	_TITLE::JIEBAI_TITLE;
		titlestrlist[strnum].m_strlength = (BYTE)strlen(szTemp);
		memset(titlestrlist[strnum].m_szTitle, 0, MAX_CHARACTER_TITLE);
		memcpy(titlestrlist[strnum].m_szTitle, szTemp, titlestrlist[strnum].m_strlength);
		strnum++;
	}
	if(strlen(GetShiTuName())!=0)
	{
		szTemp = GetShiTuName();
		titlestrlist[strnum].m_titleid	=	_TITLE::SHITU_TITLE;
		titlestrlist[strnum].m_strlength = (BYTE)strlen(szTemp);
		memset(titlestrlist[strnum].m_szTitle, 0, MAX_CHARACTER_TITLE);
		memcpy(titlestrlist[strnum].m_szTitle, szTemp, titlestrlist[strnum].m_strlength);
		strnum++;
	}
	if(strlen(GetShangDianName())!=0)
	{
		szTemp = GetShangDianName();
		titlestrlist[strnum].m_titleid	=	_TITLE::SHANGDIAN_TITLE;
		titlestrlist[strnum].m_strlength = (BYTE)strlen(szTemp);
		memset(titlestrlist[strnum].m_szTitle, 0, MAX_CHARACTER_TITLE);
		memcpy(titlestrlist[strnum].m_szTitle, szTemp, titlestrlist[strnum].m_strlength);
		strnum++;
	}

	GCCharAllTitles Msg;
	Msg.setTargetID(GetID());
	Msg.SetTitleIdNum(num);
	Msg.SetTitleIdList(titlelist);
	Msg.SetTitleStrNum(strnum);
	Msg.SetTitleStrList(titlestrlist);
	//PACKET_ALL_TITLES_MSG


	GetPlayer()->SendPacket(&Msg);
	__LEAVE_FUNCTION
}

VOID Obj_Human::SendOperateResultMsg(INT nCode)
{
	__ENTER_FUNCTION
		GCOperateResult Msg ;
	Msg.setResult(nCode) ;
	if(NULL!=m_pPlayer)
	{
		m_pPlayer->SendPacket( &Msg ) ;
	}
	__LEAVE_FUNCTION
}

VOID Obj_Human::OnExecuteScriptTimer(UINT uTime)
{
	__ENTER_FUNCTION

		Scene* pScene = getScene() ;
	if( pScene == NULL )
		return ;

	pScene->OnScenePlayerTimer( this, uTime ) ;

	__LEAVE_FUNCTION
}

VOID Obj_Human::OnHumanLogin( )
{
	__ENTER_FUNCTION

		Scene* pScene = getScene() ;
	if( pScene == NULL )
		return ;
	Impact_FadeOutAllOfflineFadeImpact();
	if( GetDB()->GetLogoutTime() == 0 )
	{//新用户第一次登陆游戏，发送提示邮件
		pScene->OnScenePlayerFirstLogin( this ) ;

		GCCharFirstLogin msg;
		msg.SetCharFirstLogin(1);
		GetPlayer()->SendPacket( &msg );
	}

	pScene->OnScenePlayerLogin( this ) ;


	__LEAVE_FUNCTION
}

VOID					Obj_Human::SetWallow( FLOAT fWallow )
{
	m_fWallow = fWallow;

	if( m_fWallow == WALLOW_HALF_INCOME )
	{
		CHAR szContex[256] ;
		sprintf( szContex, "你已进入防沉迷状态，收益减半！" ) ;
		GCChat Msg ;
		Msg.SetChatType( CHAT_TYPE_SYSTEM ) ;
		Msg.SetContex( szContex ) ;
		Msg.SetContexSize( (BYTE)strlen(szContex) ) ;
		Msg.SetSourCamp( INVALID_CAMP );
		GetPlayer()->SendPacket( &Msg ) ;
	}
	else if( m_fWallow == WALLOW_NONE )
	{
		CHAR szContex[256] ;
		sprintf( szContex, "你已进入防沉迷状态，不会获得收益！" ) ;
		GCChat Msg ;
		Msg.SetChatType( CHAT_TYPE_SYSTEM ) ;
		Msg.SetContex( szContex ) ;
		Msg.SetContexSize( (BYTE)strlen(szContex) ) ;
		Msg.SetSourCamp( INVALID_CAMP );
		GetPlayer()->SendPacket( &Msg ) ;
	}
}

FLOAT					Obj_Human::GetWallow(VOID) const
{
	return m_fWallow;
}
