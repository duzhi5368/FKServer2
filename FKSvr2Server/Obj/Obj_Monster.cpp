#include "stdafx.h"
// Obj_Monster.cpp

#include "Scene.h"
#include "Log.h"
#include "Config.h"
#include "GCCharBaseAttrib.h"
#include "GCErrorAttack.h"
#include "GCNewMonster.h"
#include "GCNewMonster_Move.h"
#include "GCNewMonster_Death.h"
#include "GCChat.h"

#include "Scene.h"
#include "TimeManager.h"
#include "GameTable.h"
//物品相关
#include "Obj_ItemBox.h"
#include "ItemTypes.h"
#include "ItemRuler.h"

#include "Obj_Pet.h"
#include "Obj_Monster.h"
#include "ItemOperator.h"
#include "ItemContainer.h"

#include "AI_Monster.h"
#include "ShopManager.h"
#include "PetPlacard.h"
#include "StdImpact033.h"
#include "StdImpact051.h"
#include "Patrol.h"
#include "GCNotifyGoodBad.h"

using namespace Packets;
using namespace Combat_Module::Impact_Module;

Obj_Monster::Obj_Monster( VOID )
{
__ENTER_FUNCTION

	// 消息/属性刷新
	//m_AttrBackUp;

	// CoolDown
	m_nCooldown				= 0;

	// 效果
	//m_ImpactList;

	// 重生
	m_RespawnTime			= -1;
	//m_RespawnTimer;
	m_RespawnDir			= -1.f;
	m_RespawnPos			= WORLD_POS(-1.f, -1.f);

	// 伤害列表
	m_Own_TeamID			= INVALID_ID;
	m_OccupantGUID			= INVALID_GUID;
	//m_DamageMemList;
	//m_OwnerList;

	// AI
	m_AIType				= -1;
	m_AIScript				= -1;
	m_PositionRange			= 0;

	// NPC商店
	m_pShopManager			= NULL;

	// 宠物公告板
	m_pPetPlacardSystem		= NULL;

	// 其他
	m_nPatrolID				= INVALID_ID;
	m_DropSearchRange		= 0.f;
	m_DropTeamCount			= 0;
	m_CreateFlag			= FALSE;

	//m_DropRuler ;

	//m_sKillObj;
	m_nKillCount			= 0;

	// 一级属性
	m_GUID					= INVALID_GUID;
	m_uDataID				= INVALID_ID;
	memset(m_szName, 0, sizeof(m_szName));
	memset(m_szTitle, 0, sizeof(m_szTitle));
	m_HP					= 0;
	m_Level					= -1;
	m_BaseExp				= 0;
	m_idScript				= 0;
	m_CampData.m_nCampID	= INVALID_CAMP;
	m_MinDamagePercent		= 0;
	m_uGroupID				= INVALID_ID;
	m_uTeamID				= INVALID_ID;
	m_bNPC					= FALSE;

	m_pAI_Character = new AI_Monster;
	Assert( m_pAI_Character ) ;

__LEAVE_FUNCTION
}

Obj_Monster::~Obj_Monster( VOID )
{
__ENTER_FUNCTION

	SAFE_DELETE( m_pAI_Character );
	SAFE_DELETE( m_pShopManager );
	if(m_pPetPlacardSystem != NULL)
	{
		m_pPetPlacardSystem->CleanUp();
		SAFE_DELETE(m_pPetPlacardSystem);
	}

__LEAVE_FUNCTION
}

VOID Obj_Monster::CleanUp( VOID )
{
__ENTER_FUNCTION

	// 消息/属性刷新
	m_AttrBackUp.CleanUp();

	// CoolDown
	m_nCooldown				= 0;

	// 效果
	m_ImpactList.CleanUp();

	// 重生
	m_RespawnTime			= -1;
	m_RespawnTimer.CleanUp();
	m_RespawnDir			= -1.f;
	m_RespawnPos			= WORLD_POS(-1.f, -1.f);

	// 伤害列表
	m_Own_TeamID			= INVALID_ID;
	m_OccupantGUID			= INVALID_GUID;
	m_DamageMemList.CleanUp();
	m_OwnerList.CleanUp();

	// AI
	m_AIType				= -1;
	m_AIScript				= -1;
	m_LeaderID				= -1;
	m_PositionRange			= 0;

	// NPC商店
	SAFE_DELETE( m_pShopManager );

	// 宠物公告板
	ReleasePetPlacardSystem();

	// 其他
	m_nPatrolID				= INVALID_ID;
	m_DropSearchRange		= 0.f;
	m_DropTeamCount			= 0;
	m_CreateFlag			= FALSE;

	//m_DropRuler;

	//m_sKillObj;
	m_nKillCount			= 0;

	// 一级属性
	m_GUID					= INVALID_GUID;
	m_uDataID				= INVALID_ID;
	memset(m_szName, 0, sizeof(m_szName));
	memset(m_szTitle, 0, sizeof(m_szTitle));
	m_HP					= 0;
	m_Level					= -1;
	m_BaseExp				= 0;
	m_idScript				= 0;
	m_CampData.m_nCampID	= INVALID_CAMP;
	m_MinDamagePercent		= 0;
	m_uGroupID				= INVALID_ID;
	m_uTeamID				= INVALID_ID;
	m_bNPC					= FALSE;

	Obj_Character::CleanUp();

__LEAVE_FUNCTION
}

BOOL Obj_Monster::Init( const _OBJ_INIT *pInit )
{
__ENTER_FUNCTION

	if ( !Obj_Character::Init( pInit ) )
		return FALSE;

	_OBJ_MONSTER_INIT *pMonsterInit = (_OBJ_MONSTER_INIT*)pInit;
	MONSTER_EXT_ATTR *pAttr = g_MonsterAttrExTbl.GetExtAttr( pMonsterInit->m_uDataID );
	if ( pAttr == NULL )
		return FALSE;

	m_GUID				= pMonsterInit->m_GUID;
	m_uDataID			= pMonsterInit->m_uDataID;		//怪物类型
	if ( pMonsterInit->m_szName[0] == '\0' )
		strncpy( m_szName, pAttr->m_Name, sizeof( m_szName ) - 1 );
	else
		strncpy( m_szName, pMonsterInit->m_szName, sizeof( m_szName ) - 1 );

	strncpy( m_szTitle, pMonsterInit->m_szTitle, sizeof( m_szTitle ) - 1 );
	m_RespawnTime		= pMonsterInit->m_RespawnTime;	//怪物生成间隔时间
	SetRespawnDir( pMonsterInit->m_Dir );			//怪物方向
	SetRespawnPos( &pMonsterInit->m_Pos );			//怪物位置
	m_RespawnTimer.BeginTimer( m_RespawnTime, 0 );		//初始化重生计时器
	m_nPatrolID			= pMonsterInit->m_nPatrolID;
	m_uGroupID			= pMonsterInit->m_uGroupID;
	m_uTeamID			= pMonsterInit->m_uTeamID;
	m_AIType			= pMonsterInit->m_BaseAI;
	m_AIScript          = pMonsterInit->m_ExtAIScript;
	m_LeaderID			= pMonsterInit->m_LeaderID;
	m_idScript			= pMonsterInit->m_idScript;
	//m_nCampType			= pMonsterInit->m_nCamp;

	m_PositionRange		= g_Config.m_ConfigInfo.m_PositionRange;
	if( pMonsterInit->m_nLevel == -1 )
		m_Level				= pAttr->m_Level;
	else
		m_Level				= pMonsterInit->m_nLevel;
	m_BaseExp			= (INT)(pAttr->m_BaseExp * g_Config.m_ConfigInfo.m_ExpParam);
	//if( pMonsterInit->m_nCamp == INVALID_CAMP )
	//	m_CampData.m_nCampID	= pAttr->m_Camp;
	//else
		m_CampData.m_nCampID	= pMonsterInit->m_nCamp;
	m_bNPC				= pMonsterInit->m_bNPC;
	m_DropSearchRange	= pAttr->m_DropSearchRange;
	m_DropTeamCount		= pAttr->m_SearchTeamCount;
	m_MinDamagePercent	= pAttr->m_MinDamagePercent;
	m_AttackAnimTime	= pAttr->m_AttackAnimTime;
	m_AttackCooldownTime = pAttr->m_AttackCooldownTime;
	m_nCooldown			= 0;

	GetMonsterAI()->GetScriptFile(m_AIScript);

	//附加效果数据
	Impact_InitList();

	Respawn( );

	InitBackupAttr();

	//初始化商店
	BOOL hasShop = FALSE ;
	INT i ;
	for( i=0; i<MAX_SHOP_INIT; i++)
	{
		if( pMonsterInit->m_nShop[i] >= 0 )
		{
			hasShop = TRUE ;
			break ;
		}
	}
	if(hasShop)
	{
		this->InitDynamicShop();
		for(i = 0; i<MAX_SHOP_INIT; i++)
		{
			if(pMonsterInit->m_nShop[i] >= 0)
				this->BindDynamicShop(pMonsterInit->m_nShop[i]);
		}

	}
	//pMonster->BindDynamicShop(1);



	return TRUE;

__LEAVE_FUNCTION
	return FALSE;
}

VOID Obj_Monster::InitAIObj( )
{
__ENTER_FUNCTION

	Assert( m_pAI_Character );
	m_pAI_Character->Init( this );

__LEAVE_FUNCTION
}


BOOL Obj_Monster::HeartBeat( UINT uTime )
{
__ENTER_FUNCTION

	static INT nSceneID = 21;
	static INT nObjID = 46;
	if(getScene()->SceneID() == nSceneID && GetID() == nObjID)
	{
		INT i;
		i = 0;
		i++;
	}

	BOOL bResult = Obj_Character::HeartBeat(uTime );
	if ( !bResult )
		return bResult;

	//有商店就跑商店逻辑
    if(m_pShopManager)	m_pShopManager->Tick(uTime );

    if(m_pPetPlacardSystem != NULL)
	{
		m_pPetPlacardSystem->HeartBeat( uTime );
	}

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL Obj_Monster::HeartBeat_OutZone( UINT uTime )
{
__ENTER_FUNCTION

	BOOL bResult = Obj_Character::HeartBeat_OutZone(uTime );
	if ( !bResult )
		return bResult;

	if( m_RespawnTime<0 )
		return FALSE ;

	if( m_RespawnTimer.CountingTimer(uTime) )
	{//尸体已经消失，重生时间到
		m_RespawnTimer.CleanUp();
		Respawn( );
	}

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

Packet *Obj_Monster::CreateNewObjPacket( VOID )
{
__ENTER_FUNCTION

	if ( getScene() != NULL )
	{
		if( !IsAlive() )
		{//尸体
			GCNewMonster_Death *pPacket = (GCNewMonster_Death*)(getScene()->m_pPacket_NewMonster_Death);
			pPacket->setObjID( GetID() );
			pPacket->setWorldPos( *(getWorldPos()) );
			pPacket->setDir( getDir() );
			pPacket->setMoveSpeed( GetMoveSpeed() ) ;
			pPacket->setIsNPC( IsNPC() );
			return pPacket;
		}
		else if( IsMoving() )
		{
			GCNewMonster_Move *pPacket = (GCNewMonster_Move*)(getScene()->m_pPacket_NewMonster_Move);
			pPacket->setObjID( GetID() ) ;
			pPacket->setHandleID( GetLogicCount() ) ;
			pPacket->setWorldPos( *getWorldPos() ) ;
			pPacket->setTargetPos( *GetFinalTarPos() ) ;
			pPacket->setMoveSpeed( GetMoveSpeed() ) ;
			pPacket->setIsNPC( IsNPC() );
			return pPacket;
		}
		else
		{
			GCNewMonster *pPacket = (GCNewMonster*)(getScene()->m_pPacket_NewMonster);
			pPacket->setObjID( GetID() ) ;
			pPacket->setWorldPos( *(getWorldPos()) ) ;
			pPacket->setDir( getDir() );
			pPacket->setMoveSpeed( GetMoveSpeed() ) ;
			pPacket->setIsNPC( IsNPC() );
			return pPacket;
		}
	}
	else
	{
		Assert( getScene() != NULL && "Obj_Monster::CreateNewObjPacket" );
		return NULL;
	}

__LEAVE_FUNCTION

	return NULL;
}

VOID Obj_Monster::DestroyNewObjPacket( Packet *pPacket )
{
}

VOID Obj_Monster::OnDie_Before( ObjID_t idKiller )
{
	//计算怪物掉落情况（即：谁拥有掉落物品）
	m_DropRuler = MonsterDropRuler::GetMonsterDropRuler(this);
	switch(m_DropRuler) 
	{
	case BDR_UNKNOW:
	case BDR_COMMON:
	case BDR_BOSS:
		{
			MonsterDropRuler::CaculateBossOwnerList(this);
		}
		break;
		//{	
		//	MonsterDropRuler::CaculateCommOwnerList(this);
		//}
		//break;
		//{
		//	MonsterDropRuler::CaculateCommOwnerList(this);
		//}
		//break;
	default:
		Assert(FALSE);
		break;
	}	
}

VOID Obj_Monster::OnDie( ObjID_t idKiller )
{
__ENTER_FUNCTION

	OnDie_Before( idKiller ) ;
	
	Obj_Character::OnDie( idKiller );

	OnDie_After( idKiller ) ;

__LEAVE_FUNCTION
}

VOID Obj_Monster::OnDie_After( ObjID_t idKiller )
{
__ENTER_FUNCTION

	// 确定有多少个队友可以分配到经验
	INT nOwnerCount = GetOwnerList().OwnerCount;
	INT nValidMemberCount = 0;
	Obj_Human *apValidMember[MAX_TEAM_MEMBER];

	// 是否需要进行善恶值分配
	Obj_Human* pTeamLeader = NULL;
	INT nValidNewbieMemberCount = 0;						// 有效范围内符合级别条件的玩家数量

	for( INT i=0; i<nOwnerCount; i++ )
	{
		Obj_Human *pMember = (Obj_Human*)(getScene()->GetObjManager()->GetObj( GetOwnerList().OwnerDropList[i].HumanID ));
		if( pMember==NULL )
		{
			Assert(FALSE);
			break;
		}
		if( !pMember->IsAlive() )//活的人才能得到经验
			continue ;

		apValidMember[nValidMemberCount++] = pMember;

		// 判断是否队长，For 善恶值
		if( pMember->GetTeamInfo()->IsLeader()
		 && pMember->GetLevel() >= g_Config.m_ConfigInfo.m_nLevelNeeded
		 )
		{
			pTeamLeader = pMember;
		}

		if( nValidMemberCount>MAX_TEAM_MEMBER )
		{
			break;
		}
	}
	
	MonsterExpCaculateRuler CaculateExp;

	// 多个玩家都可以得到经验
	if ( nValidMemberCount > 1 )
	{
		INT nExp = (m_BaseExp + (m_BaseExp*(nValidMemberCount-1))/10) / nValidMemberCount;
		UINT auExp[MAX_TEAM_MEMBER];
		INT i;

		for ( i = 0; i < nValidMemberCount; i++ )
		{ // 计算每个人应得的经验值
			auExp[i] = CaculateExp.CaculateBaseExp(GetLevel(),apValidMember[i]->GetLevel(),nExp);

			// 判断是否符合条件的队员，For 善恶值
			if( pTeamLeader != NULL
			 && nExp == auExp[i]
			 && apValidMember[i]->GetLevel() <= g_Config.m_ConfigInfo.m_nMemberLevel
			 && apValidMember[i]->IsInValidRadius( pTeamLeader, g_Config.m_ConfigInfo.m_fGoodBadRadius )
			 )
			{
				++nValidNewbieMemberCount;
			}
		}

		// 增加善恶值
		//if( pTeamLeader != NULL )
		//{
		//	INT nBonus;

		//	nBonus = nValidNewbieMemberCount * g_Config.m_ConfigInfo.m_nBonusPerMember;
		//	if( nBonus > g_Config.m_ConfigInfo.m_nMaxBonus )
		//	{
		//		nBonus = g_Config.m_ConfigInfo.m_nMaxBonus;
		//	}

		//	if( nBonus > 0 )
		//	{
		//		nBonus = pTeamLeader->IncGoodBadValue( nBonus );
		//		// nBonus 是实际增加值
		//		// 发送消息给客户端，以显示信息提示
		//		GCNotifyGoodBad Msg;
		//		Msg.SetNotifyMode( NOTIFY_GOODBAD_HELPNEWBIE );
		//		Msg.SetValue( nBonus );

		//		pTeamLeader->GetPlayer()->SendPacket( &Msg );
		//	}
		//}

		for ( i = 0; i < nValidMemberCount; i++ )
		{ // 增加经验值
			if(auExp[i]>0)
			{
				apValidMember[i]->SetMonsterAlterExp(auExp[i]);
			}
			apValidMember[i]->OnKillObject( GetID() );

			// 在此加入玩家的宠物增加经验的Section
			Obj_Pet* pPet = apValidMember[i]->GetPet();
			if (pPet)
			{
				UINT iAddExp = CaculateExp.CaculateBaseExp(GetLevel(), pPet->GetLevel(), nExp);
				if (iAddExp > 0)
					pPet->IncrementExp(iAddExp);
			}

			UINT uExpPoint = (g_Config.m_ConfigInfo.m_nExpPoint >= 0) ? g_Config.m_ConfigInfo.m_nExpPoint : 0;
			GUID_t MyGUID = apValidMember[i]->GetGUID();
			HumanRelation* pRelation = apValidMember[i]->GetHumanRelation();
			if( pRelation == NULL ) continue;
			//Assert( pRelation );

			// 增加友好度
			for ( INT j = i+1; j < nValidMemberCount; ++j )
			{
				GUID_t FriendGUID;
				HumanRelation* pFriendRelation;

				FriendGUID = apValidMember[j]->GetGUID();
				pFriendRelation = apValidMember[j]->GetHumanRelation();
				//Assert(pFriendRelation);

				if ( pFriendRelation && pRelation->IsFriend( FriendGUID ) && pFriendRelation->IsFriend( MyGUID ) )
				{ // 如果是好友
					if ( auExp[i] >= uExpPoint || auExp[j] >= uExpPoint )
					{ // 符合条件
						pRelation->IncFriendPoint( FriendGUID );
						pFriendRelation->IncFriendPoint( MyGUID );
					}
				}
			}
		}
	}
	// 单个玩家得到经验
	else if( nValidMemberCount==1 )
	{
		UINT iAddExp = CaculateExp.CaculateBaseExp(GetLevel(),apValidMember[0]->GetLevel(),m_BaseExp);
		if(iAddExp>0)
		{
			apValidMember[0]->SetMonsterAlterExp(iAddExp);
		}
		apValidMember[0]->OnKillObject( GetID() ) ;

		// 在此加入玩家的宠物增加经验的Section
		Obj_Pet* pPet = apValidMember[0]->GetPet();
		if (pPet)
		{
			iAddExp = CaculateExp.CaculateBaseExp(GetLevel(), pPet->GetLevel(), m_BaseExp);
			if (iAddExp > 0)
				pPet->IncrementExp(iAddExp);
		}

	}	

	//根据掉落规则，计算掉落包掉落处理
	switch(m_DropRuler) 
	{
	case BDR_COMMON:
	case BDR_BOSS:
	case BDR_UNKNOW:
		{
			MonsterDropRuler::CaculateBossDropRuler(this,m_DropRuler);
		}
		break;
		//{	
		//	MonsterDropRuler::CaculateCommDropRuler(this);
		//}
		//break;
		//break;
		//{
		//	MonsterDropRuler::CaculateCommDropRuler(this);
		//}
	default:
		Assert(FALSE);
		break;
	}

__LEAVE_FUNCTION
}

VOID Obj_Monster::Enter_Respawn( VOID )
{
__ENTER_FUNCTION
	m_DamageMemList.CleanUp();
	m_Own_TeamID = INVALID_ID ;
	m_OccupantGUID = INVALID_ID ;

	if( m_RespawnTime>=0 )
	{
		m_RespawnTimer.BeginTimer( (UINT)(m_RespawnTime*g_Config.m_ConfigInfo.m_fRespawnParam), NowTime() );
	}
	else
	{
		m_RespawnTimer.BeginTimer( m_RespawnTime, NowTime() );
	}

	SetActiveFlag( FALSE );

__LEAVE_FUNCTION
}

BOOL Obj_Monster::Respawn( VOID )
{
__ENTER_FUNCTION

	
	Assert( !IsActiveObj() );//死亡的怪物才需要复活

	FLOAT fDir;
	WORLD_POS Pos;
	Pos = *GetRespawnPos();
	fDir = GetRespawnDir();
	getScene()->GetMap()->VerifyPos( &Pos );
	getScene()->GetMap()->IsCanGo(Pos,0) ? Pos : Pos = *GetRespawnPos();
	setWorldPos( &Pos );
	UpdateZone();

	//设置数据
	SetHP( GetMaxHP() );
	m_nKillCount = 0;
	memset(m_sKillObj,-1,sizeof(m_sKillObj));
	SetDieTime(-1) ;

	GetMonsterAI()->CleanUp();

	AI_Monster* pAI = (AI_Monster*)GetAIObj();
	if (pAI) 
	{
		if ( isPatrolMonster( ) ) 
		{
			pAI->StartPatrol( ) ;
		}
		else if (INVALID_ID != m_LeaderID)
		{
			pAI->StartTeamFollow();
		}
		else
		{
			pAI->ChangeState(ESTATE_IDLE);
		}
	}
    
	SetActiveFlag(TRUE);

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}


BOOL Obj_Monster::IsEnemy(Obj_Character* pCharacter )
{
__ENTER_FUNCTION
	OWN_IMPACT* pImp = NULL;
	Assert( pCharacter );
	ObjID_t oId = pCharacter->GetID();
	if(GetID()==oId)
	{
		return FALSE;
	}
	//if( oId == 15000 )
	//{
	//	oId = 0;
	//}

	{ //分身专用
		SOT_ShadowGuard_T logic;
		pImp = Impact_GetFirstImpactOfSpecificLogicID(logic.ID);
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
	} while(0);
	{ //策划专用
		SOT_XingXiu011_T logic;
		pImp = Impact_GetFirstImpactOfSpecificLogicID(logic.ID);
		if(NULL!=pImp)
		{
			Obj* pObj = Impact_GetCaster(*this, *pImp);
			if(NULL!=pObj)
			{
				if(TRUE == IsCharacterObj(pObj->GetObjType()))
				{
					Obj_Character& rFascinator = *static_cast<Obj_Character*>(pObj);
					return rFascinator.IsEnemy(pCharacter);
				}
			}
		}
	} while(0);
	BOOL bIsEnemy = IsEnemyCamp(*pCharacter);
	return bIsEnemy;

__LEAVE_FUNCTION

	return FALSE;
}
BOOL Obj_Monster::IsFriend(Obj_Character* pCharacter )
{
__ENTER_FUNCTION
	
	Assert( pCharacter );
	return FALSE==IsEnemy(pCharacter);

__LEAVE_FUNCTION

	return FALSE;
}
BOOL Obj_Monster::IsPartner(Obj_Character* pCharacter )
{
__ENTER_FUNCTION
	
	Assert( pCharacter );
	if( pCharacter->GetObjType() == Obj::OBJ_TYPE_MONSTER)
		return TRUE;

	return FALSE;

__LEAVE_FUNCTION

	return FALSE;
}

VOID Obj_Monster::SetName( const CHAR *pszName )
{
	strncpy( m_szName, pszName, sizeof( m_szName ) - 1 );
	m_AttrBackUp.m_bNameModified = TRUE;
}

VOID Obj_Monster::SetTitle( const CHAR *pszTitle )
{
	strncpy( m_szTitle, pszTitle, sizeof( m_szTitle ) - 1 );
	m_AttrBackUp.m_bTitleModified = TRUE;
}
INT	Obj_Monster::GetHP( VOID )
{
	if(m_HP>GetMaxHP())
	{
		m_HP=GetMaxHP();
	}
	return m_HP;
}

VOID Obj_Monster::SetHP( INT nHP )
{
	INT nMaxHP = GetMaxHP();
	if( nHP > nMaxHP )
	{
		nHP = nMaxHP;
	}
	m_HP = nHP;
}

VOID Obj_Monster::SetMP( INT nMP )
{
	//INT nMaxMP = GetMaxMP();
	//if( nMP > nMaxMP )
	//{
	//	nMP = nMaxMP;.BeginTimer( CHECK_SENDMSG_TIME, CreateTime ) ;
	//}
	//m_MP = nMP;
}

VOID Obj_Monster::SetLevel( INT nLevel )
{
	if(m_Level != nLevel)
	{
		m_Level = nLevel;
		OnLevelChanged();
	}
}

VOID Obj_Monster::InitDynamicShop()
{
__ENTER_FUNCTION

	SAFE_DELETE(m_pShopManager);
	m_pShopManager = new DynamicShopManager(this);
	Assert(m_pShopManager);

	m_pShopManager->Init();

__LEAVE_FUNCTION
}

INT	Obj_Monster::BindDynamicShop(INT shopindex)
{
__ENTER_FUNCTION

	return m_pShopManager->AddDynamicShop(g_pStaticShopManager->GetShopByID(shopindex));

__LEAVE_FUNCTION

	return 0 ;
}

BOOL Obj_Monster::CreatePetPlacardSystem(VOID)
{
	if(m_pPetPlacardSystem == NULL)
	{
		m_pPetPlacardSystem = new PetPlacardSystem;
		BOOL bResult = m_pPetPlacardSystem->Init();
		if(!bResult)
			return FALSE;
	}
	return TRUE;
}

VOID Obj_Monster::ReleasePetPlacardSystem(VOID)
{
	if(m_pPetPlacardSystem != NULL)
	{
		m_pPetPlacardSystem->CleanUp();
		SAFE_DELETE(m_pPetPlacardSystem);
	}
}

DAMAGE_MEM_LIST	Obj_Monster::GetKillerRec(UINT uCount,UINT nPercent)
{
	DAMAGE_MEM_LIST		DML_Record;
	__ENTER_FUNCTION

	UINT	uLessDamage	=	Float2Int(GetMaxHP()*((FLOAT)nPercent/100)); 
	
	for(UINT i=0;
		i<m_DamageMemList.m_uCount
		&& DML_Record.m_uCount<uCount;
		i++)
	{
		if(m_DamageMemList.m_DamageRec[i].m_uDamage>uLessDamage)
			DML_Record.AddMember(m_DamageMemList.m_DamageRec[i]);
	}
	
	
	return DML_Record;

	__LEAVE_FUNCTION

	return DML_Record;

}
VOID Obj_Monster::UpdateDamageList(INT nDamage, Obj_Character* pAttacker)
{
	__ENTER_FUNCTION
	if(nDamage >= 1 && pAttacker )
	{
		Obj_Human *pHuman = NULL;

		Obj::ObjType nType = pAttacker->GetObjType();
		switch(nType) 
		{
		case Obj::OBJ_TYPE_HUMAN:
			pHuman = (Obj_Human*)(pAttacker);
			break;
		case Obj::OBJ_TYPE_PET:
			{
				Obj_Character* pOwner = ((Obj_Pet*)(pAttacker))->GetOwner();

				if (pOwner->GetObjType() == Obj::OBJ_TYPE_HUMAN )
				{
					pHuman = (Obj_Human*)pOwner;
				}
			}
			break;
		default:
			break;
		}

		if ( pHuman != NULL )
		{
			ObjID_t	nHumanID = pHuman->GetID();
			DAMAGE_RECORD*	pDamageRec	= m_DamageMemList.FindMember(nHumanID,pHuman->__GetTeamID());

			UINT TotalDamage = 0 ;
			if(pDamageRec)
			{
				pDamageRec->m_uDamage += nDamage ;
				TotalDamage = pDamageRec->m_uDamage ;
			}
			else
			{
				m_DamageMemList.AddMember(nHumanID,pHuman->__GetTeamID(),nDamage);
				TotalDamage = nDamage ;
			}
			if( GetOccupantTeamID()==INVALID_ID && GetOccupantGUID()==INVALID_ID )
			{
				if( (TotalDamage*100/(GetMaxHP()+1))>10 )
				{//第一个将怪物血打掉10％的人
					if( pHuman->__GetTeamID()!=INVALID_ID )
					{
						SetOccupantTeamID( pHuman->__GetTeamID() ) ;
					}
					SetOccupantGUID( pHuman->GetGUID() ) ;
				}
			}
		}
	}
	__LEAVE_FUNCTION
}

MONSTER_OWNER_LIST&	Obj_Monster::GetOwnerList() 	
{
	return m_OwnerList;
}

FLOAT		Obj_Monster::GetDropSearchRange() const
{
	return m_DropSearchRange;
}
INT			Obj_Monster::GetDropTeamCount() const
{
	return  m_DropTeamCount;	
}

INT			Obj_Monster::GetMinDamagePercent() const
{
	return m_MinDamagePercent;
}

VOID		Obj_Monster::SetPatrolId(INT PatrolID)
{
__ENTER_FUNCTION
	PatrolPathMgr* pPatrolPathMgr = getScene()->GetPatrolPathMgr();
	if (!pPatrolPathMgr)
	{
		return;
	}
	if (TRUE == pPatrolPathMgr->FindPatrolID(PatrolID))
	{
		m_nPatrolID = PatrolID;
	}
__LEAVE_FUNCTION
}
//VOID Obj_Monster::StartPatrol( VOID )
//{
//	GetMonsterAI()->StartPatrol();
//}
//
//VOID Obj_Monster::StopPatrol( VOID )
//{
//	GetMonsterAI()->StopPatrol();
//}



INT	 Obj_Monster::GetMonsterAIType(VOID)
	{
	//INT nAIType = GetAIType();
	//INT nRet = GCCharBaseAttrib::CHAR_AI_TYPE_INVALID;
	//if (g_MonsterAITbl.Get(nAIType, AIPARAM_SCANTIME) > 0)
	//{// 主动进攻NPC
	//	nRet = GCCharBaseAttrib::CHAR_AI_TYPE_SCANNPC;
	//}
	//else if (TRUE == IsUnbreakable())
	//{// 不可以攻击NPC
	//	nRet = GCCharBaseAttrib::CHAR_AI_TYPE_CANNOTATTACK;
	//}
	//else if (g_MonsterAITbl.Get(nAIType, AIPARAM_SCANTIME) <= 0)
	//{// 非主动进攻NPC
	//	nRet = GCCharBaseAttrib::CHAR_AI_TYPE_NOTSCANNPC;
	//}
	//else
	//{
	//}
	return GetAIType();
	//return nRet;
}

//VOID	Obj_Monster::Betray(const Obj_Character* pCharacter)
//{
//#define SCANMONSTER (0)
//	__ENTER_FUNCTION
//		
//	if (!pCharacter) {
//		return ;
//	}
//
//	// 设置成主动扫描怪
//	SetAIType(SCANMONSTER);
//	// 将怪物的阵营设置成pCharacter的阵营
//	SetBaseCampID(pCharacter->GetBaseCampID() );
//
//	__LEAVE_FUNCTION
//}

VOID	Obj_Monster::ProcessPaoPao(VOID)
{
__ENTER_FUNCTION
	
	AI_Monster* pAIMonster = (AI_Monster*)GetAIObj();
	if (pAIMonster)
	{
		pAIMonster->ProcessPaoPao();
	}

__LEAVE_FUNCTION
}

VOID	Obj_Monster::PaoPao(INT idPaoPaoBase, INT idPaoPaoStep)
{
	__ENTER_FUNCTION
	if (idPaoPaoBase < 0 || idPaoPaoStep < 0) {
		return ;
	}
	Scene* pScene = getScene();
	if (!pScene) {
		return ;
	}

	if (idPaoPaoStep == 0) {
		return ;
	}
	INT idPaoPao = rand() % idPaoPaoStep + idPaoPaoBase;
	// 通过聊天通道向周围的human广播
	// 发送的格式如下
	/* @*;npcpaopao;idObj;idPaoPao */
	CHAR szContex[64];
	memset(szContex, 0, 64);
	sprintf(szContex, "@*;npcpaopao;%d;%d", GetID(), idPaoPao);

	GCChat msg;
	msg.SetChatType( CHAT_TYPE_SELF );
	msg.SetContex( szContex );
	msg.SetContexSize( (BYTE)strlen(szContex) );

	pScene->BroadCast(&msg, getZoneID() );

	__LEAVE_FUNCTION

}

VOID Obj_Monster::OnExecuteScriptTimer(UINT uTime)
{
	__ENTER_FUNCTION

		if( GetScriptID()==INVALID_ID )
			return ;

	Scene* pScene = getScene() ;
	if( pScene == NULL )
		return ;

	SceneID_t SceneID = pScene->SceneID() ;
	ObjID_t ObjID = GetID() ;
	INT DataID = GetDataID() ;

	pScene->GetLuaInterface()->ExeScript_DDDD(
		GetScriptID(),
		"OnCharacterTimer",
		SceneID,
		ObjID,
		DataID,
		uTime ) ;


	__LEAVE_FUNCTION
}
