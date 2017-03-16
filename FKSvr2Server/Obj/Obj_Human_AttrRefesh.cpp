#include "stdafx.h"
// Obj_Human_AttrRefesh.cpp

#include "Scene.h"

#include "GCCharBaseAttrib.h"
#include "GCCharEquipment.h"
#include "GCDetailAttrib.h"
#include "GCDetailAttrib_Pet.h"
#include "GCNotifyTeamInfo.h"
#include "GCTeamFollowList.h"
#include "GCTeamMemberInfo.h"
#include "GCCharImpactListUpdate.h"
#include "GCCanPickMissionItemList.h"
#include "GCDetailImpactListUpdate.h"
#include "GCCoolDownUpdate.h"
#include "DB_Struct.h"
#include "ItemOperator.h"
#include "GameTable.h"
#include "Obj_Human.h"

using namespace Packets;

extern ENUM_REFESH_ATTR_TYPE CalcRefeshAttrType(Obj_Character *pSour, Obj_Character *pTarget );

UINT GetEquipmentMaxLevelGemID(Item *pEquipment)
{
	UINT uGemID = INVALID_ID;
	if(pEquipment != NULL)
	{
		BYTE byCount = pEquipment->GetEquipGemCount();
		BYTE i;
		INT nMaxLevel = -1;
		_ITEM_GEMINFO stGemInfo;
		if(byCount != 0)
		{
			for(i = 0; i < byCount; i++)
			{
				stGemInfo = pEquipment->GetEquipGemInfo(i);
				INT nGemLevel = GetSerialQual(stGemInfo.m_GemType);
				if(nGemLevel > nMaxLevel)
				{
					nMaxLevel = nGemLevel;
					uGemID = stGemInfo.m_GemType;
				}
			}
		}
	}
	return uGemID;
}

VOID Obj_Human::InitBackupAttr()
{
__ENTER_FUNCTION

//	m_SyncTeamMemberInfo.m_Flags
	m_SyncTeamMemberInfo.m_uFamily		= GetMenPai();
	m_SyncTeamMemberInfo.m_uLevel		= GetLevel();
	m_SyncTeamMemberInfo.m_WorldPos.m_fX= getWorldPos()->m_fX;
	m_SyncTeamMemberInfo.m_WorldPos.m_fZ= getWorldPos()->m_fZ;
	m_SyncTeamMemberInfo.m_nHP			= GetHP();
	m_SyncTeamMemberInfo.m_uMaxHP		= GetMaxHP();
	m_SyncTeamMemberInfo.m_nMP			= GetMP();
	m_SyncTeamMemberInfo.m_uMaxMP		= GetMaxMP();
	m_SyncTeamMemberInfo.m_nAnger		= GetRage();
	m_SyncTeamMemberInfo.m_WeaponID		= GetEquipID( HEQUIP_WEAPON );
	m_SyncTeamMemberInfo.m_CapID		= GetEquipID( HEQUIP_CAP );
	m_SyncTeamMemberInfo.m_ArmourID		= GetEquipID( HEQUIP_ARMOR );
	m_SyncTeamMemberInfo.m_CuffID		= GetEquipID( HEQUIP_CUFF );
	m_SyncTeamMemberInfo.m_FootID		= GetEquipID( HEQUIP_BOOT );
	m_SyncTeamMemberInfo.m_bDeadFlag	= IsDie();



	m_AttrBackUp.m_bNameModified		= FALSE;
	m_AttrBackUp.m_bTitleModified		= FALSE;
	m_AttrBackUp.m_Level				= GetLevel();
	m_AttrBackUp.m_Exp					= GetExp();
	m_AttrBackUp.m_HP					= GetHP();
	m_AttrBackUp.m_MP					= GetMP();
	m_AttrBackUp.m_MaxHp				= GetMaxHP();
	m_AttrBackUp.m_MaxMp				= GetMaxMP();
	m_AttrBackUp.m_nRage				= GetRage();
	m_AttrBackUp.m_MoveSpeed			= GetMoveSpeed();
	m_AttrBackUp.m_nDataID				= GetDataID();
	m_AttrBackUp.m_nPortraitID			= GetPortraitID();
	m_AttrBackUp.m_nMountID				= GetMountID();
	m_AttrBackUp.m_nModelID				= GetModelID();
	m_AttrBackUp.m_uFaceMeshID			= __GetFaceModel();
	m_AttrBackUp.m_uHairMeshID			= __GetHairModel();
	m_AttrBackUp.m_uHairColor			= __GetHairColor();
	m_AttrBackUp.m_nStealthLevel		= GetStealthLevel();
	m_AttrBackUp.m_nMoodState			= GetMoodState();

	m_AttrBackUp.m_Money				= GetMoney();
	//m_AttrBackUp.m_RMBMoney				= GetRMBMoney();
	m_AttrBackUp.m_nStr					= GetStr();
	m_AttrBackUp.m_nSpr					= GetSpr();
	m_AttrBackUp.m_nCon					= GetCon();
	m_AttrBackUp.m_nInt					= GetInt();
	m_AttrBackUp.m_nDex					= GetDex();
	m_AttrBackUp.m_nPointRemain			= Get_RemainPoints();
	m_AttrBackUp.m_nReHpSpeed			= GetHPRegenerate();
	m_AttrBackUp.m_nReMpSpeed			= GetMPRegenerate();
	m_AttrBackUp.m_nAttPhysics			= Attr_VerifyGeneralAttack(GetAttackPhysics());
	m_AttrBackUp.m_nAttMagic			= Attr_VerifyGeneralAttack(GetAttackMagic());
	m_AttrBackUp.m_nDefPhysics			= Attr_VerifyDefence(GetDefencePhysics());
	m_AttrBackUp.m_nDefMagic			= Attr_VerifyDefence(GetDefenceMagic());
	m_AttrBackUp.m_nHit					= Attr_VerifyHitMiss(GetHit());
	m_AttrBackUp.m_nMiss				= Attr_VerifyHitMiss(GetMiss());
	m_AttrBackUp.m_nCritic				= Attr_VerifyCritical(GetCritical());
	m_AttrBackUp.m_nStrikePoint			= GetStrikePoint();
	m_AttrBackUp.m_nAttSpeed			= GetAttackSpeed();
	m_AttrBackUp.m_nAttCold				= Attr_VerifyTraitAttack(GetAttackCold());
	m_AttrBackUp.m_nDefCold				= Attr_VerifyResist(GetDefenceCold());
	m_AttrBackUp.m_nAttFire				= Attr_VerifyTraitAttack(GetAttackFire());
	m_AttrBackUp.m_nDefFire				= Attr_VerifyResist(GetDefenceFire());
	m_AttrBackUp.m_nAttLight			= Attr_VerifyTraitAttack(GetAttackLight());
	m_AttrBackUp.m_nDefLight			= Attr_VerifyResist(GetDefenceLight());
	m_AttrBackUp.m_nAttPoison			= Attr_VerifyTraitAttack(GetAttackPoison());
	m_AttrBackUp.m_nDefPoison			= Attr_VerifyResist(GetDefencePoison());
	m_AttrBackUp.m_nMenpai				= GetMenPai();

	const _CAMP_DATA *pCampData = GetCampData();
	if ( pCampData != NULL )
		m_AttrBackUp.m_CampData			= *pCampData;

	m_AttrBackUp.m_nOwnerID				= GetOwnerID();
	m_AttrBackUp.m_guidCurrentPet		= GetCurrentPetGUID();

	m_AttrBackUp.m_RMBMoney				= GetRMB();
	m_AttrBackUp.m_BankRMB				= GetBankRMB();
	m_AttrBackUp.m_DoubleExpTime_Num				= GetDoubleExpTime_Num();
	m_AttrBackUp.m_GmRight			= GetGmRight();

	m_AttrBackUp.m_bLimitMove			= IsLimitMove();
	m_AttrBackUp.m_bCanActionFlag1		= CanActionFlag1();
	m_AttrBackUp.m_bCanActionFlag2		= CanActionFlag2();
	//m_AttrBackUp.m_bLimitHandle			= IsLimitAllHandle();

	m_AttrBackUp.m_bMissionHaveDoneFlagsChanged	= FALSE;
	m_AttrBackUp.m_bWeaponModified		= FALSE;
	m_AttrBackUp.m_bCapModified			= FALSE;
	m_AttrBackUp.m_bArmorModified		= FALSE;
	m_AttrBackUp.m_bCuffModified		= FALSE;
	m_AttrBackUp.m_bBootModified		= FALSE;
	m_AttrBackUp.m_bSashModified		= FALSE;

	m_AttrBackUp.m_bStallIsOpen			= FALSE;
	m_AttrBackUp.m_bStallNameChanged	= FALSE;

	m_AttrBackUp.m_GuildID				= GetGuildID();

__LEAVE_FUNCTION	
}

VOID Obj_Human::SyncTeamMemberInfo( )
{
__ENTER_FUNCTION

	const TeamInfo* pTeamInfo;

	pTeamInfo = GetTeamInfo();
	if ( pTeamInfo == NULL )
	{ // 出问题了
		Assert(FALSE);
		return;
	}

	if ( pTeamInfo->HasTeam() == FALSE )
	{ // 没有组队
		return;
	}

	if ( pTeamInfo->GetSceneMemberCount() < 1 )
	{ // 没有队友在同场景
		return;
	}

	GCTeamMemberInfo msgTeamMember;

	msgTeamMember.setGUID( GetGUID() );

	if ( m_SyncTeamMemberInfo.m_uFamily != GetMenPai())
	{
		m_SyncTeamMemberInfo.m_uFamily = GetMenPai();
		msgTeamMember.SetFamily( GetMenPai() );
	}

	if ( m_SyncTeamMemberInfo.m_uLevel != GetLevel() )
	{
		m_SyncTeamMemberInfo.m_uLevel = GetLevel();
		msgTeamMember.SetLevel( GetLevel() );
	}

	if ( m_SyncTeamMemberInfo.m_WorldPos.m_fX != getWorldPos()->m_fX
	  || m_SyncTeamMemberInfo.m_WorldPos.m_fZ != getWorldPos()->m_fZ
	  )
	{
		m_SyncTeamMemberInfo.m_WorldPos.m_fX = getWorldPos()->m_fX;
		m_SyncTeamMemberInfo.m_WorldPos.m_fZ = getWorldPos()->m_fZ;

		msgTeamMember.SetWorldPos( &(m_SyncTeamMemberInfo.m_WorldPos) );
	}

	if ( m_SyncTeamMemberInfo.m_uMaxHP != GetMaxHP() )
	{
		m_SyncTeamMemberInfo.m_uMaxHP = GetMaxHP();
		msgTeamMember.SetMaxHP( GetMaxHP() );
	}

	if ( m_SyncTeamMemberInfo.m_nHP != GetHP() )
	{
		m_SyncTeamMemberInfo.m_nHP = GetHP();
		msgTeamMember.SetHP( GetHP() );
	}

	if ( m_SyncTeamMemberInfo.m_uMaxMP != GetMaxMP() )
	{
		m_SyncTeamMemberInfo.m_uMaxMP = GetMaxMP();
		msgTeamMember.SetMaxMP( GetMaxMP() );
	}

	if ( m_SyncTeamMemberInfo.m_nMP != GetMP() )
	{
		m_SyncTeamMemberInfo.m_nMP = GetMP();
		msgTeamMember.SetMP( GetMP() );
	}

	if ( m_SyncTeamMemberInfo.m_nAnger != GetRage() )
	{
		m_SyncTeamMemberInfo.m_nAnger = GetRage();
		msgTeamMember.SetAnger( GetRage() );
	}

	// 装备刷新
	UINT uWeaponID = GetEquipID( HEQUIP_WEAPON );
	if ( m_SyncTeamMemberInfo.m_WeaponID != uWeaponID )
	{
		m_SyncTeamMemberInfo.m_WeaponID = uWeaponID;
		msgTeamMember.SetWeaponID( uWeaponID );
	}

	UINT uCapID = GetEquipID( HEQUIP_CAP );
	if ( m_SyncTeamMemberInfo.m_CapID != uCapID )
	{
		m_SyncTeamMemberInfo.m_CapID = uCapID;
		msgTeamMember.SetCapID( uCapID );
	}

	UINT uArmourID = GetEquipID( HEQUIP_ARMOR );
	if ( m_SyncTeamMemberInfo.m_ArmourID != uArmourID )
	{
		m_SyncTeamMemberInfo.m_ArmourID = uArmourID;
		msgTeamMember.SetArmourID( uArmourID );
	}

	UINT uCuffID = GetEquipID( HEQUIP_CUFF );
	if ( m_SyncTeamMemberInfo.m_CuffID != uCuffID )
	{
		m_SyncTeamMemberInfo.m_CuffID = uCuffID;
		msgTeamMember.SetCuffID( uCuffID );
	}

	UINT uBootID = GetEquipID( HEQUIP_BOOT );
	if ( m_SyncTeamMemberInfo.m_FootID != uBootID )
	{
		m_SyncTeamMemberInfo.m_FootID = uBootID;
		msgTeamMember.SetFootID( GetEquipID( HEQUIP_BOOT ) );
	}

	BOOL bDeadFlag = IsDie();
	if ( m_SyncTeamMemberInfo.m_bDeadFlag != bDeadFlag )
	{
		m_SyncTeamMemberInfo.m_bDeadFlag = bDeadFlag;
		msgTeamMember.SetDead( bDeadFlag );
	}

	if ( m_SyncTeamMemberInfo.m_uFaceMeshID != __GetFaceModel() )
	{
		m_SyncTeamMemberInfo.m_uFaceMeshID = __GetFaceModel();
		msgTeamMember.SetFaceModel( __GetFaceModel() );
	}

	if ( m_SyncTeamMemberInfo.m_uHairMeshID != __GetHairModel() )
	{
		m_SyncTeamMemberInfo.m_uHairMeshID = __GetHairModel();
		msgTeamMember.SetHairModel( __GetHairModel() );
	}

	if ( m_SyncTeamMemberInfo.m_uHairColor != __GetHairColor() )
	{
		m_SyncTeamMemberInfo.m_uHairColor = __GetHairColor();
		msgTeamMember.SetHairColor( __GetHairColor() );
	}

	BOOL bMemberInfo = FALSE;
	BOOL bImpactInfo = FALSE;

	if ( msgTeamMember.GetFlags() != 0 )
	{ // 没有需要更新的信息
		bMemberInfo = TRUE;
	}

	// BUFF
	GCCharImpactListUpdate msgMemberImpactList;
	_IMPACT_LIST& rList = Impact_GetImpactList();

	if ( m_SyncTeamMemberInfo.m_SimpleImpactList != rList )
	{
		bImpactInfo = TRUE;
	}

	if ( bImpactInfo )
	{
		m_SyncTeamMemberInfo.m_SimpleImpactList.SetImpactList( &rList );

		msgMemberImpactList.SetOwnerID( GetID() );
		msgMemberImpactList.SetImpactList( rList );
	}


	if ( !bMemberInfo && !bImpactInfo )
	{ // 没有任何需要更新的信息
		return;
	}

	for( INT i=0; i<pTeamInfo->GetSceneMemberCount(); ++i )
	{
		Obj_Human* pRecvHuman;

		pRecvHuman = getScene()->GetHumanManager()->GetHuman( pTeamInfo->GetSceneMemberObjID(i) );

		if ( pRecvHuman != NULL )
		{
			Player* pRecvPlayer = pRecvHuman->GetPlayer();

			if ( pRecvPlayer != NULL )
			{
				if ( bMemberInfo )
				{
					pRecvPlayer->SendPacket( &msgTeamMember );
				}

				if ( bImpactInfo )
				{
					pRecvPlayer->SendPacket( &msgMemberImpactList );
				}
			}
		}
	}

__LEAVE_FUNCTION
}

VOID Obj_Human::SendMsg_RefeshAttrib( VOID )
{
__ENTER_FUNCTION
	INT nAttr = 0;

	BOOL bPublicAttrModified, bEquipmentModified, bDetailAttrModified;
	bPublicAttrModified		= FALSE;
	bEquipmentModified		= FALSE;
	bDetailAttrModified		= FALSE;

	GCCharBaseAttrib msgPublicAttr;
	GCCharEquipment msgEquipment;
	GCDetailAttrib msgDetail;

	msgPublicAttr.setObjID( GetID() );
	msgDetail.SetObjID( GetID() );

	if ( m_AttrBackUp.m_bNameModified )
	{
		bPublicAttrModified = TRUE;
		msgPublicAttr.setName( GetName() );
		m_AttrBackUp.m_bNameModified = FALSE;
	}

	if ( m_AttrBackUp.m_bTitleModified )
	{
		bPublicAttrModified = TRUE;
		msgPublicAttr.setTitle( GetTitle() );
		msgPublicAttr.setTitleType( GetTitleType() );

		m_AttrBackUp.m_bTitleModified = FALSE;
	}

	if(m_AttrBackUp.m_MaxHp != GetMaxHP())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_MaxHp = GetMaxHP();

		BYTE yHPPercent = (GetMaxHP())?((BYTE)((GetHP()*100 + GetMaxHP() - 1)/GetMaxHP())):(0);
		msgPublicAttr.setHPPercent( yHPPercent );
		msgDetail.SetMAXHP( GetMaxHP() );
	}

	if(m_AttrBackUp.m_HP != GetHP())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_HP = GetHP();

		BYTE yHPPercent = (GetMaxHP())?((BYTE)((GetHP()*100 + GetMaxHP() - 1)/GetMaxHP())):(0);
		msgPublicAttr.setHPPercent( yHPPercent );
		msgDetail.SetHP( GetHP() );
	}


	if(m_AttrBackUp.m_MaxMp != GetMaxMP())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_MaxMp = GetMaxMP();

		BYTE yMPPercent = (GetMaxMP())?((BYTE)((GetMP()*100 + GetMaxMP() - 1)/GetMaxMP())):(0);
		msgPublicAttr.setMPPercent( yMPPercent );
		msgDetail.SetMAXMP( GetMaxMP() );
	}

	if(m_AttrBackUp.m_MP != GetMP())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_MP = GetMP();

		BYTE yMPPercent = (GetMaxMP())?((BYTE)((GetMP()*100 + GetMaxMP() - 1)/GetMaxMP())):(0);
		msgPublicAttr.setMPPercent( yMPPercent );
		msgDetail.SetMP( GetMP() );
	}



	if(m_AttrBackUp.m_nRage != GetRage())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nRage = GetRage();

		msgPublicAttr.setRage( GetRage() );
		msgDetail.SetRage( GetRage() );
	}

	if(fabs(m_AttrBackUp.m_MoveSpeed-GetMoveSpeed()) > 0.001f)
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_MoveSpeed = GetMoveSpeed();

		msgPublicAttr.setMoveSpeed( GetMoveSpeed() );
		msgDetail.SetMoveSpeed( GetMoveSpeed() );
	}

	const _CAMP_DATA *pCampData = GetCampData();
	if ( pCampData != NULL )
	{
		if(m_AttrBackUp.m_CampData != *pCampData)
		{
			bPublicAttrModified = TRUE;
			m_AttrBackUp.m_CampData = *pCampData;

			msgPublicAttr.setCampData( pCampData );
			msgDetail.SetCampData( pCampData );
		}
	}
	//if( m_AttrBackUp.m_nCampType != m_nCampType )
	//{
	//	bPublicAttrModified = TRUE;
	//	m_AttrBackUp.m_nCampType = m_nCampType;
	//	msgPublicAttr.setCampType( m_nCampType );
	//	msgDetail.SetCampType( m_nCampType );
	//}

	if(m_AttrBackUp.m_nOwnerID != GetOwnerID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nOwnerID = GetOwnerID();

		msgPublicAttr.setOwnerID( GetOwnerID() );
		//msgDetail.SetOwnerID( GetOwnerID() );
	}

	if(m_AttrBackUp.m_guidCurrentPet != GetCurrentPetGUID())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_guidCurrentPet = GetCurrentPetGUID();

		msgDetail.SetCurrentPetGUID( GetCurrentPetGUID() );
	}

	if(m_AttrBackUp.m_RMBMoney != GetRMB())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_RMBMoney = GetRMB() ;

		msgDetail.SetRMB( GetRMB() ) ;
	}

	if(m_AttrBackUp.m_BankRMB != GetBankRMB())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_BankRMB = GetBankRMB() ;

		msgDetail.SetBankRMB( GetBankRMB() ) ;
	}

	if(m_AttrBackUp.m_DoubleExpTime_Num != GetDoubleExpTime_Num())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_DoubleExpTime_Num = GetDoubleExpTime_Num() ;

		msgDetail.SetDoubleExpTime_Num( GetDoubleExpTime_Num() ) ;
	}

	/*if(m_AttrBackUp.m_GmRight != GetGmRight())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_GmRight = GetGmRight() ;

		msgDetail.SetGmRight( GetGmRight() ) ;
	}*/

	if(m_AttrBackUp.m_nDataID != GetDataID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nDataID = GetDataID();

		msgPublicAttr.setDataID( GetDataID() );
		msgDetail.SetDataID( GetDataID() );
	}
	
	if(m_AttrBackUp.m_nPortraitID != GetPortraitID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nPortraitID = GetPortraitID();

		msgPublicAttr.setPortraitID( GetPortraitID() );
		msgDetail.SetPortraitID( GetPortraitID() );
	}
	
	if(m_AttrBackUp.m_nModelID != GetModelID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nModelID = GetModelID();

		msgPublicAttr.setModelID( GetModelID() );
		msgDetail.SetModelID( GetModelID() );
	}
	
	if(m_AttrBackUp.m_nMountID != GetMountID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nMountID = GetMountID();

		msgPublicAttr.setMountID( GetMountID() );
		msgDetail.SetMountID( GetMountID() );
	}

	if(m_AttrBackUp.m_uHairMeshID != __GetHairModel()
		|| m_AttrBackUp.m_uHairColor != __GetHairColor()
		|| m_AttrBackUp.m_uFaceMeshID != __GetFaceModel())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_uHairMeshID = __GetHairModel();
		m_AttrBackUp.m_uFaceMeshID = __GetFaceModel();
		m_AttrBackUp.m_uHairColor = __GetHairColor();

		msgPublicAttr.setFaceMeshID( __GetFaceModel() );
		msgPublicAttr.setHairMeshID( __GetHairModel() );
		msgPublicAttr.setHairMatrixID( __GetHairColor() );
	}

	if(m_AttrBackUp.m_nStealthLevel != GetStealthLevel())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nStealthLevel = GetStealthLevel();

		msgPublicAttr.setStealthLevel( GetStealthLevel() );
	}

	if(m_AttrBackUp.m_nMoodState != GetMoodState())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nMoodState = GetMoodState();

		msgPublicAttr.setMoodState( GetMoodState() );
	}

	if(m_AttrBackUp.m_Level != GetLevel())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_Level = GetLevel();

		msgPublicAttr.setLevel( GetLevel() );
		msgDetail.SetLevel( GetLevel() );
	}

	if ( m_AttrBackUp.m_bStallIsOpen != m_StallBox.GetStallIsOpen() )
	{//摊位状态发生变化
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_bStallIsOpen = m_StallBox.GetStallIsOpen();

		msgPublicAttr.setIsOpen(m_AttrBackUp.m_bStallIsOpen);
	}

	if ( m_AttrBackUp.m_bStallNameChanged )
	{//摊位名发生变化
		m_AttrBackUp.m_bStallNameChanged = FALSE;
		if(m_StallBox.GetStallIsOpen())
		{
			bPublicAttrModified = TRUE;
			msgPublicAttr.setStallName( m_StallBox.GetStallName() );
		}
	}

	if(m_AttrBackUp.m_bLimitMove != IsLimitMove())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_bLimitMove = IsLimitMove();

		//msgPublicAttr.SetLimitMove( IsLimitMove() );
		//msgPublicAttrAndLevel.SetLimitMove( IsLimitMove() );
		//msgProtectedAttr.SetLimitMove( IsLimitMove() );
		msgDetail.SetLimitMove( IsLimitMove() );
	}

	if(m_AttrBackUp.m_bCanActionFlag1 != CanActionFlag1())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_bCanActionFlag1 = CanActionFlag1();

		msgDetail.SetCanActionFlag1(CanActionFlag1());
	}
	
	if(m_AttrBackUp.m_bCanActionFlag2 != CanActionFlag2())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_bCanActionFlag2 = CanActionFlag2();

		msgDetail.SetCanActionFlag2(CanActionFlag1());
	}

	if(m_AttrBackUp.m_Exp != GetExp())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_Exp = GetExp();

		msgDetail.SetExp( GetExp() );
	}

	if(m_AttrBackUp.m_Money != GetMoney())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_Money = GetMoney();

		msgDetail.SetMoney( GetMoney() );
	}

	if(m_AttrBackUp.m_RMBMoney != GetRMB())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_RMBMoney = GetRMB();

		msgDetail.SetRMB( GetRMB() );
	}

	if(m_AttrBackUp.m_nMenpai != GetMenPai())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nMenpai = GetMenPai();

		msgDetail.SetMenpai(GetMenPai());
	}

	if(m_AttrBackUp.m_GuildID != GetGuildID())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_GuildID = GetGuildID();

		msgDetail.SetGuild(GetGuildID());
	}

	if(m_AttrBackUp.m_nStr != GetStr())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nStr = GetStr();

		msgDetail.SetStr(GetStr());
	}

	if(m_AttrBackUp.m_nSpr != GetSpr())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nSpr = GetSpr();

		msgDetail.SetSpr(GetSpr());
	}

	if(m_AttrBackUp.m_nCon != GetCon())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nCon = GetCon();

		msgDetail.SetCon(GetCon());
	}

	if(m_AttrBackUp.m_nInt != GetInt())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nInt = GetInt();

		msgDetail.SetInt(GetInt());
	}

	if(m_AttrBackUp.m_nDex != GetDex())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nDex = GetDex();

		msgDetail.SetDex(GetDex());
	}

	if(m_AttrBackUp.m_nPointRemain != Get_RemainPoints())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nPointRemain = Get_RemainPoints();

		msgDetail.SetPoint_Remain( Get_RemainPoints() );
	}

	if(m_AttrBackUp.m_nReHpSpeed != GetHPRegenerate())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nReHpSpeed = GetHPRegenerate();

		msgDetail.SetHP_ReSpeed( GetHPRegenerate() );
	}

	if(m_AttrBackUp.m_nReMpSpeed !=	GetMPRegenerate())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nReMpSpeed = GetMPRegenerate();

		msgDetail.SetMP_ReSpeed( GetMPRegenerate() );
	}

	nAttr = Attr_VerifyGeneralAttack(GetAttackPhysics());
	if(m_AttrBackUp.m_nAttPhysics != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nAttPhysics = nAttr;
		msgDetail.SetAtt_Physics(nAttr);
	}

	nAttr = Attr_VerifyGeneralAttack(GetAttackMagic());
	if(m_AttrBackUp.m_nAttMagic != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nAttMagic = nAttr;
		msgDetail.SetAtt_Magic(nAttr);
	}

	nAttr = Attr_VerifyDefence(GetDefencePhysics());
	if(m_AttrBackUp.m_nDefPhysics != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nDefPhysics = nAttr;
		msgDetail.SetDef_Physics(nAttr);
	}

	nAttr = Attr_VerifyDefence(GetDefenceMagic());
	if(m_AttrBackUp.m_nDefMagic != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nDefMagic = nAttr;
		msgDetail.SetDef_Magic(nAttr);
	}

	nAttr = Attr_VerifyHitMiss(GetHit());
	if(m_AttrBackUp.m_nHit != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nHit = nAttr;

		msgDetail.SetHit(nAttr);
	}

	nAttr = Attr_VerifyHitMiss(GetMiss());
	if(m_AttrBackUp.m_nMiss != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nMiss = nAttr;

		msgDetail.SetMiss(nAttr);
	}

	nAttr = Attr_VerifyCritical(GetCritical());
	if(m_AttrBackUp.m_nCritic != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nCritic = nAttr;

		msgDetail.SetCritic(nAttr);
	}

	if(m_AttrBackUp.m_nStrikePoint != GetStrikePoint())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nStrikePoint = GetStrikePoint();

		msgDetail.SetStrikePoint( GetStrikePoint() );
	}

	if(m_AttrBackUp.m_nAttSpeed != GetAttackSpeed())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nAttSpeed = GetAttackSpeed();

		msgDetail.SetAttSpeed( GetAttackSpeed() );
	}

	nAttr = Attr_VerifyTraitAttack(GetAttackCold());
	if(m_AttrBackUp.m_nAttCold != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nAttCold = nAttr;

		msgDetail.SetAttCold(nAttr);
	}
	
	nAttr = Attr_VerifyResist(GetDefenceCold());
	if(m_AttrBackUp.m_nDefCold != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nDefCold = nAttr;

		msgDetail.SetDefCold(nAttr);
	}	

	nAttr = Attr_VerifyTraitAttack(GetAttackFire());
	if(m_AttrBackUp.m_nAttFire != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nAttFire = nAttr;

		msgDetail.SetAttFire(nAttr);
	}

	nAttr = Attr_VerifyResist(GetDefenceFire());
	if(m_AttrBackUp.m_nDefFire != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nDefFire = nAttr;

		msgDetail.SetDefFire(nAttr);
	}

	nAttr = Attr_VerifyTraitAttack(GetAttackLight());
	if(m_AttrBackUp.m_nAttLight != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nAttLight = nAttr;

		msgDetail.SetAttLight(nAttr);
	}
	
	nAttr = Attr_VerifyResist(GetDefenceLight());
	if(m_AttrBackUp.m_nDefLight != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nDefLight = nAttr;

		msgDetail.SetDefLight(nAttr);
	}

	nAttr = Attr_VerifyTraitAttack(GetAttackPoison());
	if(m_AttrBackUp.m_nAttPoison != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nAttPoison = nAttr;

		msgDetail.SetAttPoison(nAttr);
	}
	nAttr = Attr_VerifyResist(GetDefencePoison());
	if(m_AttrBackUp.m_nDefPoison != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nDefPoison = nAttr;

		msgDetail.SetDefPoison(nAttr);
	}

	// 装备刷新
	if ( m_AttrBackUp.m_bWeaponModified )
	{
		bEquipmentModified = TRUE;
		msgEquipment.setWeaponID( GetEquipID( HEQUIP_WEAPON ) );
		Item *pWeaponItem = GetEquipContain()->GetItem(HEQUIP_WEAPON);
		UINT uGemID = INVALID_ID;
		if(pWeaponItem != NULL)
		{
			uGemID = GetEquipmentMaxLevelGemID(pWeaponItem);
		}
		msgEquipment.setWeaponGemID(uGemID);
		m_AttrBackUp.m_bWeaponModified = FALSE;
	}

	if ( m_AttrBackUp.m_bCapModified )
	{
		bEquipmentModified = TRUE;
		msgEquipment.setCapID( GetEquipID( HEQUIP_CAP ) );
		Item *pCapItem = GetEquipContain()->GetItem(HEQUIP_CAP);
		UINT uGemID = INVALID_ID;
		if(pCapItem != NULL)
		{
			uGemID = GetEquipmentMaxLevelGemID(pCapItem);
		}
		msgEquipment.setCapGemID( uGemID );
		m_AttrBackUp.m_bCapModified = FALSE;
	}

	if ( m_AttrBackUp.m_bArmorModified )
	{
		bEquipmentModified = TRUE;
		msgEquipment.setArmourID( GetEquipID( HEQUIP_ARMOR ) );
		Item *pArmorItem = GetEquipContain()->GetItem(HEQUIP_ARMOR);
		UINT uGemID = INVALID_ID;
		if(pArmorItem != NULL)
		{
			uGemID = GetEquipmentMaxLevelGemID(pArmorItem);
		}
		msgEquipment.setArmourGemID( uGemID );
		m_AttrBackUp.m_bArmorModified = FALSE;
	}

	if ( m_AttrBackUp.m_bCuffModified )
	{
		bEquipmentModified = TRUE;
		msgEquipment.setCuffID( GetEquipID( HEQUIP_CUFF ) );
		Item *pCuffItem = GetEquipContain()->GetItem(HEQUIP_CUFF);
		UINT uGemID = INVALID_ID;
		if(pCuffItem != NULL)
		{
			uGemID = GetEquipmentMaxLevelGemID(pCuffItem);
		}
		msgEquipment.setCuffGemID( uGemID );
		m_AttrBackUp.m_bCuffModified = FALSE;
	}

	if ( m_AttrBackUp.m_bBootModified )
	{
		bEquipmentModified = TRUE;
		msgEquipment.setBootID( GetEquipID( HEQUIP_BOOT ) );
		Item *pBootItem = GetEquipContain()->GetItem(HEQUIP_BOOT);
		UINT uGemID = INVALID_ID;
		if(pBootItem != NULL)
		{
			uGemID = GetEquipmentMaxLevelGemID(pBootItem);
		}
		msgEquipment.setBootGemID( uGemID );
		m_AttrBackUp.m_bBootModified = FALSE;
	}

	if ( m_AttrBackUp.m_bSashModified )
	{
		bEquipmentModified = TRUE;
		//msgEquipment.setSashID( GetEquipID( HEQUIP_SASH ) );
		m_AttrBackUp.m_bSashModified = FALSE;
	}

	if ( bPublicAttrModified )
	{
		if ( bPublicAttrModified )
		{
			m_PublicAttrVersion++;
		}

		if ( bEquipmentModified )
		{
			m_EquipVer++;
		}

		HUMANLIST listHuman;
		getScene()->ScanHuman( getZoneID(), MAX_REFESH_OBJ_ZONE_RADIUS, &(listHuman) );

		BOOL bSendPublicMsg				= bPublicAttrModified;
		BYTE i;
		for ( i = 0; i < listHuman.m_Count; i++ )
		{
			Obj_Human *pTargetHuman = listHuman.m_aHuman[i];
			if ( IsCanViewMe( pTargetHuman ) )
			{
				pTargetHuman->GetPlayer()->SendPacket( &msgPublicAttr );

				if ( bEquipmentModified )
				{
					pTargetHuman->GetPlayer()->SendPacket( &msgEquipment );
				}
			}
		}
	}

	bDetailAttrModified |= bPublicAttrModified;
	if ( bDetailAttrModified )
	{
		GetPlayer()->SendPacket(&msgDetail); //发送给自己的详细消息
	}
__LEAVE_FUNCTION
}
VOID Obj_Human::AskMsg_DetailAttrib(Obj_Human *pAsker)
{
__ENTER_FUNCTION
	if ( pAsker == NULL )
		return;

	Player *pAskPlayer = pAsker->GetPlayer();

	BOOL bMySelfAsk = (pAsker == this)?(TRUE):(FALSE);

	if(NULL==pAskPlayer)
	{
		return;
	}

	GCDetailAttrib	Msg;

	Msg.SetObjID( GetID() );

	Msg.SetLevel(GetLevel());
	Msg.SetMenpai(GetMenPai() ) ;
	Msg.SetModelID(GetModelID());

	if ( bMySelfAsk )
	{
		Msg.SetHP(GetHP());
		Msg.SetMAXHP(GetMaxHP());
		Msg.SetMP(GetMP());
		Msg.SetMAXMP(GetMaxMP());

		Msg.SetExp(GetExp());

		Msg.SetMoney(GetMoney());
		Msg.SetCurrentPetGUID(GetCurrentPetGUID() ) ;

		Msg.SetMoveSpeed(GetMoveSpeed());

		Msg.SetStr(GetStr());
		Msg.SetSpr(GetSpr());
		Msg.SetCon(GetCon());
		Msg.SetInt(GetInt());
		Msg.SetDex(GetDex());
		Msg.SetPoint_Remain(Get_RemainPoints());
		Msg.SetHP_ReSpeed(GetHPRegenerate());
		Msg.SetMP_ReSpeed(GetMPRegenerate());
		Msg.SetAtt_Physics(Attr_VerifyGeneralAttack(GetAttackPhysics()));		
		Msg.SetAtt_Magic(Attr_VerifyGeneralAttack(GetAttackMagic()));		
		Msg.SetDef_Physics(Attr_VerifyDefence(GetDefencePhysics()));
		Msg.SetDef_Magic(Attr_VerifyDefence(GetDefenceMagic()));
		Msg.SetHit(Attr_VerifyHitMiss(GetHit()));
		Msg.SetMiss(Attr_VerifyHitMiss(GetMiss()));
		Msg.SetCritic(Attr_VerifyCritical(GetCritical()));
		Msg.SetRage(GetRage());
		Msg.SetStrikePoint(GetStrikePoint());
		Msg.SetAttSpeed(GetAttackSpeed());
		Msg.SetAttCold(Attr_VerifyTraitAttack(GetAttackCold()));
		Msg.SetDefCold(Attr_VerifyResist(GetDefenceCold()));
		Msg.SetAttFire(Attr_VerifyTraitAttack(GetAttackFire()));
		Msg.SetDefFire(Attr_VerifyResist(GetDefenceFire()));
		Msg.SetAttLight(Attr_VerifyTraitAttack(GetAttackLight()));
		Msg.SetDefLight(Attr_VerifyResist(GetDefenceLight()));
		Msg.SetAttPoison(Attr_VerifyTraitAttack(GetAttackPoison()));
		Msg.SetDefPoison(Attr_VerifyResist(GetDefencePoison()));
		Msg.SetLimitMove(IsLimitMove());
		Msg.SetCanActionFlag1(CanActionFlag1());
		Msg.SetCanActionFlag2(CanActionFlag2());
		Msg.SetGuild(GetGuildID());
		//Msg.SetLimitHandle(IsLimitAllHandle());
		//Msg.SetMissionHaveDoneFlags(pHuman->GetMissionHaveDoneFlags());
		//Msg.SetMissionKillObjectFlags(pHuman->GetMissionKillObjectFlags());
		//Msg.SetMissionEnterAreaFlags(pHuman->GetMissionEnterAreaFlags());
		//Msg.SetMissionItemChangedFlags(pHuman->GetMissionItemChangedFlags());
		Msg.SetDoubleExpTime_Num(GetDoubleExpTime_Num()) ;
	//	Msg.SetMaxEnergy( 1 ) ;
		Msg.SetRMB( GetRMB() ) ;
		Msg.SetBankRMB( GetBankRMB() );
	}
	pAskPlayer->SendPacket( &Msg ) ;

	if ( bMySelfAsk )
	{
		// 可以拾取的任务道具
		//GCCanPickMissionItemList msgCanPick;
		//msgCanPick.SetCanPickMissionItemList( (BYTE)(GetCanPickMissionItemCount()), GetCanPickMissionItemList() );
		//pAskPlayer->SendPacket( &msgCanPick );

		//与此同时，发送角色详细效果列表信息给客户端
		GCDetailImpactListUpdate ImpactListUpdate;
		ImpactListUpdate.SetOwnerID(GetID());
		ImpactListUpdate.SetImpactList(Impact_GetImpactList());
		pAskPlayer->SendPacket(&ImpactListUpdate);
		
		//与此同时，发送角色的冷却列表
		GCCooldownUpdate	Msg;
		CooldownListForHuman_T const* pCooldownList = m_DB.GetCooldownDB();
		Assert(pCooldownList);
		CooldownListForHuman_T const& rCooldownList = *pCooldownList;
		for(INT nIdx=0; rCooldownList.LIST_SIZE>nIdx;++nIdx)
		{
			Cooldown_T const& rCooldownInfo = rCooldownList.GetCooldownInfoByIndex(nIdx);
			if(FALSE == rCooldownInfo.IsCooldowned())
			{
				Msg.CooldownModified(rCooldownInfo);
			}
		}
		pAskPlayer->SendPacket( &Msg ) ;
		// 宠物
		for ( INT i = 0; i < HUMAN_PET_MAX_COUNT; ++i )
		{
			Item* pPetFind = GetPetContain()->GetItem(i);
			PET_GUID_t guidFind = pPetFind->GetPetGUID();
			if ( !guidFind.IsNull() )
			{
				RefeshPetDetailAttrib(guidFind);
			}
		}
	}
	
__LEAVE_FUNCTION
}

//VOID Obj_Human::CalculatePetDetailAttrib(Packets::GCDetailAttrib_Pet& rMsg, PET_GUID_t guidPet)
//{
//__ENTER_FUNCTION
//	if(guidPet.IsNull()) {
//		return;
//	}
//	Item* pPetItem = GetPetItem(guidPet);
//	if(!pPetItem) {
//		return ;
//	}
//	rMsg.SetGUID( guidPet );
//	rMsg.SetDataID( pPetItem->GetDataID() );
//	rMsg.SetName( pPetItem->GetName() );
//	rMsg.SetHP( pPetItem->GetHP() );
//	rMsg.SetAIType(pPetItem->GetAIType());
//	rMsg.SetSpouseGUID(pPetItem->GetSpouseGUID());
//	rMsg.SetLevel(pPetItem->GetLevel());
//	rMsg.SetLife(pPetItem->GetLife());
//	rMsg.SetGeneration(pPetItem->GetGeneration());
//	rMsg.SetHappiness(pPetItem->GetHappiness());
//	rMsg.SetExp(pPetItem->GetExp());
//	rMsg.SetStrPerception(pPetItem->GetStrPer());
//	rMsg.SetConPerception(pPetItem->GetConPer());
//	rMsg.SetDexPerception(pPetItem->GetDexPer());
//	rMsg.SetSprPerception(pPetItem->GetSprPer());
//	rMsg.SetIntPerception(pPetItem->GetIntPer());
//
//	rMsg.SetStr( pPetItem->GetLvl1Attr(CATTR_LEVEL1_STR) );
//	rMsg.SetCon( pPetItem->GetLvl1Attr(CATTR_LEVEL1_CON) );
//	rMsg.SetDex( pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX) );
//	rMsg.SetSpr( pPetItem->GetLvl1Attr(CATTR_LEVEL1_SPR) );
//	rMsg.SetInt( pPetItem->GetLvl1Attr(CATTR_LEVEL1_INT) );
//	rMsg.SetGenGu( pPetItem->GetGenGu() );
//
//	INT nBaseParam = 0;
//	INT nValue = 0;
//	INT nAttribParam = 0;
//	FLOAT fLevelRate = 0;
//	FLOAT fAttribRate = 0.f;
//	
//	INT nLevel = pPetItem->GetLevel();
//	FLOAT fGrowRate = pPetItem->GetGrowRate();
//
//	//HP	初始HP+体质*体质对HP影响系数*体资+等级*等级对HP影响系数*成长
//	nBaseParam = g_TableInit.m_PetConfig.m_BaseHP;
//	fAttribRate = g_TableInit.m_PetConfig.m_Con_HP_Pram;
//	fLevelRate = g_TableInit.m_PetConfig.m_Level_HP_Pram;
//	nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_CON);
//	nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
//	
//	rMsg.SetHPMax(nValue);
//	//魔攻	初始魔攻+灵气*灵气对魔攻攻影响系数*灵资+等级*等级对魔攻影响系数*成长
//	nBaseParam = g_TableInit.m_PetConfig.m_BaseMgcAttack;
//	fAttribRate = g_TableInit.m_PetConfig.m_Spr_MgcAttack_Pram;
//	fLevelRate = g_TableInit.m_PetConfig.m_Level_MgcAttack_Pram;
//	nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_SPR);
//	nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
//
//	rMsg.SetAtt_Magic(nValue);
//	//物攻	初始物攻+力量*力量对物攻影响系数*力资+等级*等级对物攻影响系数*成长
//	nBaseParam = g_TableInit.m_PetConfig.m_BasePhyAttack;
//	fAttribRate = g_TableInit.m_PetConfig.m_Str_PhyAttack_Pram;
//	fLevelRate = g_TableInit.m_PetConfig.m_Level_PhyAttack_Pram;
//	nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_STR);
//	nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
//
//	rMsg.SetAtt_Physics(nValue);
//	//魔防	初始魔防+定力*定力对魔防影响系数*定资+等级*等级对魔防影响系数*成长
//	nBaseParam = g_TableInit.m_PetConfig.m_BaseMgcDefence;
//	fAttribRate = g_TableInit.m_PetConfig.m_Int_MgcDefence_Pram;
//	fLevelRate = g_TableInit.m_PetConfig.m_Level_MgcDefence_Pram;
//	nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_INT);
//	nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
//
//	rMsg.SetDef_Magic(nValue);
//	//物防	初始物攻+体质*体质对物防影响系数*体资+等级*等级对物防影响系数*成长
//	nBaseParam = g_TableInit.m_PetConfig.m_BasePhyDefence;
//	fAttribRate = g_TableInit.m_PetConfig.m_Con_PhyDefence_Pram;
//	fLevelRate = g_TableInit.m_PetConfig.m_Level_PhyDefence_Pram;
//	nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_CON);
//	nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
//
//	rMsg.SetDef_Physics(nValue);
//	//闪避	初始物攻+敏捷*敏捷对闪避影响系数*敏资+等级*等级对闪避影响系数*成长
//	nBaseParam = g_TableInit.m_PetConfig.m_BasePhyAttack;
//	fAttribRate = g_TableInit.m_PetConfig.m_Dex_Miss_Pram;
//	fLevelRate = g_TableInit.m_PetConfig.m_Level_Miss_Pram;
//	nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX);
//	nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
//
//	rMsg.SetMiss(nValue);
//	//命中	初始物攻+敏捷*敏捷对命中影响系数*敏资+等级*等级对命中影响系数*成长
//	nBaseParam = g_TableInit.m_PetConfig.m_BasePhyAttack;
//	fAttribRate = g_TableInit.m_PetConfig.m_Dex_Hit_Pram;
//	fLevelRate = g_TableInit.m_PetConfig.m_Level_Hit_Pram;
//	nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX);
//	nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
//
//	rMsg.SetHit(nValue);
//	//会心	初始物攻+敏捷*敏捷对会心影响系数*敏资+等级*等级对会心影响系数*成长
//	nBaseParam = g_TableInit.m_PetConfig.m_BaseCritical;
//	fAttribRate = g_TableInit.m_PetConfig.m_Dex_Critical_Pram;
//	fLevelRate = g_TableInit.m_PetConfig.m_Level_Critical_Pram;
//	nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX);
//
//	nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
//
//	rMsg.SetCritical(nValue);
//	rMsg.SetRemainPoint( pPetItem->GetRemainPoint() );
//
//	_OWN_SKILL ownSkill;
//	INT i;
//	for(i = 0; i < PET_MAX_SKILL_COUNT; i++)
//	{
//		ownSkill.m_nSkillID	= pPetItem->GetSkill(i).m_nSkillID;
//		rMsg.SetSkill(i, &ownSkill);
//	}
//
//__LEAVE_FUNCTION
//
//}

VOID Obj_Human::CalculatePetDetailAttrib(Packets::GCDetailAttrib_Pet& rMsg, Item* pPetItem)
{
	__ENTER_FUNCTION
		if(!pPetItem)
		{
			return ;
		}
		if(pPetItem->GetPetGUID().IsNull())
		{
			return;
		}
		
		rMsg.SetGUID( pPetItem->GetPetGUID() );
		rMsg.SetDataID( pPetItem->GetDataID() );
		rMsg.SetName( pPetItem->GetName() );
		rMsg.SetHP( pPetItem->GetHP() );
		rMsg.SetAIType(pPetItem->GetAIType());
		rMsg.SetSpouseGUID(pPetItem->GetSpouseGUID());
		rMsg.SetLevel(pPetItem->GetLevel());
		rMsg.SetLife(pPetItem->GetLife());
		rMsg.SetGeneration(pPetItem->GetGeneration());
		rMsg.SetHappiness(pPetItem->GetHappiness());
		rMsg.SetExp(pPetItem->GetExp());
		rMsg.SetStrPerception(pPetItem->GetStrPer());
		rMsg.SetConPerception(pPetItem->GetConPer());
		rMsg.SetDexPerception(pPetItem->GetDexPer());
		rMsg.SetSprPerception(pPetItem->GetSprPer());
		rMsg.SetIntPerception(pPetItem->GetIntPer());

		rMsg.SetStr( pPetItem->GetLvl1Attr(CATTR_LEVEL1_STR) );
		rMsg.SetCon( pPetItem->GetLvl1Attr(CATTR_LEVEL1_CON) );
		rMsg.SetDex( pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX) );
		rMsg.SetSpr( pPetItem->GetLvl1Attr(CATTR_LEVEL1_SPR) );
		rMsg.SetInt( pPetItem->GetLvl1Attr(CATTR_LEVEL1_INT) );
		rMsg.SetGenGu( pPetItem->GetGenGu() );
		rMsg.SetHPMax(pPetItem->GetBaseMaxHP());

		INT nBaseParam = 0;
		INT nValue = 0;
		INT nAttribParam = 0;
		FLOAT fLevelRate = 0;
		FLOAT fAttribRate = 0.f;

		INT nLevel = pPetItem->GetLevel();
		FLOAT fGrowRate = pPetItem->GetGrowRate();

		//魔攻	初始魔攻+灵气*灵气对魔攻攻影响系数*灵资+等级*等级对魔攻影响系数*成长
		nBaseParam = g_TableInit.m_PetConfig.m_BaseMgcAttack;
		fAttribRate = g_TableInit.m_PetConfig.m_Spr_MgcAttack_Pram;
		fLevelRate = g_TableInit.m_PetConfig.m_Level_MgcAttack_Pram;
		nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_SPR);
		nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);

		rMsg.SetAtt_Magic(Attr_VerifyGeneralAttack(nValue));
		//物攻	初始物攻+力量*力量对物攻影响系数*力资+等级*等级对物攻影响系数*成长
		nBaseParam = g_TableInit.m_PetConfig.m_BasePhyAttack;
		fAttribRate = g_TableInit.m_PetConfig.m_Str_PhyAttack_Pram;
		fLevelRate = g_TableInit.m_PetConfig.m_Level_PhyAttack_Pram;
		nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_STR);
		nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);

		rMsg.SetAtt_Physics(Attr_VerifyGeneralAttack(nValue));
		//魔防	初始魔防+定力*定力对魔防影响系数*定资+等级*等级对魔防影响系数*成长
		nBaseParam = g_TableInit.m_PetConfig.m_BaseMgcDefence;
		fAttribRate = g_TableInit.m_PetConfig.m_Int_MgcDefence_Pram;
		fLevelRate = g_TableInit.m_PetConfig.m_Level_MgcDefence_Pram;
		nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_INT);
		nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);

		rMsg.SetDef_Magic(Attr_VerifyDefence(nValue));
		//物防	初始物攻+体质*体质对物防影响系数*体资+等级*等级对物防影响系数*成长
		nBaseParam = g_TableInit.m_PetConfig.m_BasePhyDefence;
		fAttribRate = g_TableInit.m_PetConfig.m_Con_PhyDefence_Pram;
		fLevelRate = g_TableInit.m_PetConfig.m_Level_PhyDefence_Pram;
		nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_CON);
		nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);

		rMsg.SetDef_Physics(Attr_VerifyDefence(nValue));
		//闪避	初始物攻+敏捷*敏捷对闪避影响系数*敏资+等级*等级对闪避影响系数*成长
		nBaseParam = g_TableInit.m_PetConfig.m_BasePhyAttack;
		fAttribRate = g_TableInit.m_PetConfig.m_Dex_Miss_Pram;
		fLevelRate = g_TableInit.m_PetConfig.m_Level_Miss_Pram;
		nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX);
		nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);

		rMsg.SetMiss(Attr_VerifyHitMiss(nValue));
		//命中	初始物攻+敏捷*敏捷对命中影响系数*敏资+等级*等级对命中影响系数*成长
		nBaseParam = g_TableInit.m_PetConfig.m_BasePhyAttack;
		fAttribRate = g_TableInit.m_PetConfig.m_Dex_Hit_Pram;
		fLevelRate = g_TableInit.m_PetConfig.m_Level_Hit_Pram;
		nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX);
		nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);

		rMsg.SetHit(Attr_VerifyHitMiss(nValue));
		//会心	初始物攻+敏捷*敏捷对会心影响系数*敏资+等级*等级对会心影响系数*成长
		nBaseParam = g_TableInit.m_PetConfig.m_BaseCritical;
		fAttribRate = g_TableInit.m_PetConfig.m_Dex_Critical_Pram;
		fLevelRate = g_TableInit.m_PetConfig.m_Level_Critical_Pram;
		nAttribParam = pPetItem->GetLvl1Attr(CATTR_LEVEL1_DEX);

		nValue = (INT)(nBaseParam + nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);

		rMsg.SetCritical(Attr_VerifyCritical(nValue));
		rMsg.SetRemainPoint( pPetItem->GetRemainPoint() );

		_OWN_SKILL ownSkill;
		INT i;
		for(i = 0; i < PET_MAX_SKILL_COUNT; i++)
		{
			ownSkill.m_nSkillID	= pPetItem->GetSkill(i).m_nSkillID;
			rMsg.SetSkill(i, &ownSkill);
		}

		__LEAVE_FUNCTION

}

VOID Obj_Human::RefeshPetDetailAttrib(PET_GUID_t guidPet)
{
__ENTER_FUNCTION

	if(guidPet.IsNull()) 
	{
		return;
	}

	Item* pPetItem = GetPetItem(guidPet);
	
	if(!pPetItem)
	{
		return ;
	}

	GCDetailAttrib_Pet msgDetail;
	CalculatePetDetailAttrib(msgDetail, pPetItem);

	GetPlayer()->SendPacket( &msgDetail );
	//与此同时，发送宠物的冷却列表
	GCCooldownUpdate Msg;
	Msg.SetPetGuid(guidPet);
	CooldownListForHuman_T const* pCooldownList = m_DB.GetCooldownDB();
	Assert(pCooldownList);
	CooldownListForHuman_T const& rCooldownList = *pCooldownList;
	for(INT nIdx=0; rCooldownList.LIST_SIZE>nIdx;++nIdx)
	{
		Cooldown_T const& rCooldownInfo = rCooldownList.GetCooldownInfoByIndex(nIdx);
		if(FALSE == rCooldownInfo.IsCooldowned())
		{
			Msg.CooldownModified(rCooldownInfo);
		}
	}
	GetPlayer()->SendPacket(&Msg); //发送宠物的冷却信息
__LEAVE_FUNCTION
}

VOID Obj_Human::AskMsg_BaseAttrib( Obj_Human *pTargetHuman )
{
__ENTER_FUNCTION

	if ( IsCanViewMe( pTargetHuman ) )
	{
		GCCharBaseAttrib msgAttr;

		BYTE yHPPercent = (GetMaxHP())?((BYTE)((GetHP()*100 + GetMaxHP() - 1)/GetMaxHP())):(0);
		BYTE yMPPercent = (GetMaxMP())?((BYTE)((GetMP()*100 + GetMaxMP() - 1)/GetMaxMP())):(0);

		msgAttr.setObjID( GetID() );
		msgAttr.setDataID( (WORD)(GetDataID()) );
		msgAttr.setPortraitID( GetPortraitID() );
//		msgAttr.setFaceMatrixID( GetDB()->GetHumanDB()->m_FaceColor );
		msgAttr.setFaceMeshID( GetDB()->GetHumanDB()->m_FaceModel );
		msgAttr.setHairMatrixID( GetDB()->GetHumanDB()->m_HairColor );
		msgAttr.setHairMeshID( GetDB()->GetHumanDB()->m_HairModel );
		msgAttr.setName( GetName() );
		msgAttr.setTitle( GetTitle() );
		msgAttr.setTitleType( GetTitleType() );
		msgAttr.setHPPercent( yHPPercent );
		msgAttr.setMPPercent( yMPPercent );
		msgAttr.setRage( GetRage() );
		msgAttr.setStealthLevel( GetStealthLevel() );
		msgAttr.setMoodState( GetMoodState() );
		//msgAttr.setCampType(GetCampType());
		if ( GetCampData() != NULL )
			msgAttr.setCampData( GetCampData() );
		msgAttr.setMoveSpeed(GetMoveSpeed());
		msgAttr.setModelID(GetModelID());
		msgAttr.setMountID(GetMountID());
		msgAttr.setAttackSpeed((FLOAT)GetAttackSpeed());
		msgAttr.setIsOpen(m_StallBox.GetStallIsOpen());
		if(m_StallBox.GetStallIsOpen())
		{
			msgAttr.setStallName(m_StallBox.GetStallName());
		}

		msgAttr.setLevel( GetLevel() );

		pTargetHuman->GetPlayer()->SendPacket( &msgAttr );
		//在发送属性数据的同时发送角色的效果列表数据
		GCCharImpactListUpdate ImpactListUpdate;
		ImpactListUpdate.SetOwnerID(GetID());
		ImpactListUpdate.SetImpactList(Impact_GetImpactList());
		pTargetHuman->GetPlayer()->SendPacket(&ImpactListUpdate);
		//队伍相关
		TeamInfo* pTeamInfo = GetTeamInfo();
		if ( pTeamInfo->HasTeam() )
		{ // 是普通队员
			GCNotifyTeamInfo msgTeamFlag;
			msgTeamFlag.SetObjID( GetID() );
			msgTeamFlag.SetHaveTeamFlag( TRUE );
			msgTeamFlag.SetTeamLeaderFlag( pTeamInfo->IsLeader() );
			msgTeamFlag.SetTeamFullFlag( pTeamInfo->IsFull() );
		//	msgTeamFlag.SetTeamFollowFlag( __GetTeamFollowFlag() );

			pTargetHuman->GetPlayer()->SendPacket( &msgTeamFlag );

			if ( pTeamInfo->IsLeader() && __GetTeamFollowFlag() )
			{ // 是队长，发送跟随列表给所有客户端，以供路线模拟
				GCTeamFollowList msgFollowList;
				msgFollowList.SetObjID( GetID() );

				for( INT i=1; i<__GetFollowedMembersCount(); ++i )
				{
					msgFollowList.AddFollowMember( __GetFollowedMember(i)->m_GUID );
				}

				pTargetHuman->GetPlayer()->SendPacket( &msgFollowList );
			}
		}
	}

__LEAVE_FUNCTION
}

