#include "stdafx.h"
// Obj_Pet_AttrRefesh.cpp

#include "Scene.h"
#include "Player.h"
#include "Obj_Human.h"

#include "GCCharBaseAttrib.h"
#include "GCDetailAttrib_Pet.h"
#include "GCNewPet.h"
#include "GCNewPet_Move.h"
#include "GCNewPet_Death.h"
#include "GCCharImpactListUpdate.h"
#include "GCDetailImpactListUpdate.h"

#include "Obj_Pet.h"


extern ENUM_REFESH_ATTR_TYPE CalcRefeshAttrType(Obj_Character *pSour, Obj_Character *pTarget );

Packet *Obj_Pet::CreateNewObjPacket( VOID )
{
__ENTER_FUNCTION

	if ( getScene() != NULL )
	{
		if( !IsAlive() )
		{//尸体
			GCNewPet_Death *pPacket = (GCNewPet_Death*)(getScene()->m_pPacket_NewPet_Death);
			pPacket->setObjID( GetID() );
			pPacket->setWorldPos( *(getWorldPos()) );
			pPacket->setDir( getDir() );
			pPacket->setMoveSpeed( GetMoveSpeed() ) ;
			return pPacket;
		}
		else if( IsMoving() )
		{
			GCNewPet_Move *pPacket = (GCNewPet_Move*)(getScene()->m_pPacket_NewPet_Move);
			pPacket->setObjID( GetID() ) ;
			pPacket->setHandleID( GetLogicCount() ) ;
			pPacket->setWorldPos( *getWorldPos() ) ;
			pPacket->setTargetPos( *GetFinalTarPos() ) ;
			pPacket->setMoveSpeed( GetMoveSpeed() ) ;
			return pPacket;
		}
		else
		{
			GCNewPet *pPacket = (GCNewPet*)(getScene()->m_pPacket_NewPet);
			pPacket->setObjID( GetID() ) ;
			pPacket->setWorldPos( *(getWorldPos()) ) ;
			pPacket->setDir( getDir() );
			pPacket->setMoveSpeed( GetMoveSpeed() ) ;
			return pPacket;
		}
	}
	else
	{
		Assert( getScene() != NULL && "Obj_Pet::CreateNewObjPacket" );
		return NULL;
	}

__LEAVE_FUNCTION

	return NULL;
}

VOID Obj_Pet::DestroyNewObjPacket( Packet *pPacket )
{
}

VOID Obj_Pet::InitBackupAttr()
{
__ENTER_FUNCTION
	m_AttrBackUp.m_bNameModified		= FALSE;
	m_AttrBackUp.m_bTitleModified		= FALSE;
	m_AttrBackUp.m_SpouseGUID			= GetSpouseGUID();
	m_AttrBackUp.m_nAIType				= GetAIType();
	m_AttrBackUp.m_Level				= GetLevel();
	m_AttrBackUp.m_nStealthLevel		= GetStealthLevel();
	m_AttrBackUp.m_HP					= GetHP();
	m_AttrBackUp.m_MP					= GetMP();
	const _CAMP_DATA *pCampData = GetCampData();
	if ( pCampData != NULL )
		m_AttrBackUp.m_CampData			= *pCampData;
	m_AttrBackUp.m_nOwnerID				= GetOwnerID();
	m_AttrBackUp.m_MaxHp				= GetMaxHP();
	m_AttrBackUp.m_MaxMp				= GetMaxMP();
	m_AttrBackUp.m_MoveSpeed			= GetMoveSpeed();

	m_AttrBackUp.m_GUID					= GetPetGUID();
	m_AttrBackUp.m_nLife				= GetLife();
	m_AttrBackUp.m_byGeneration			= GetGeneration();
	m_AttrBackUp.m_byHappiness			= GetHappiness();

	m_AttrBackUp.m_nAtt_Physics			= Attr_VerifyGeneralAttack(GetAttackPhysics());
	m_AttrBackUp.m_nAtt_Magic			= Attr_VerifyGeneralAttack(GetAttackMagic());
	m_AttrBackUp.m_nDef_Physics			= Attr_VerifyDefence(GetDefencePhysics());
	m_AttrBackUp.m_nDef_Magic			= Attr_VerifyDefence(GetDefenceMagic());
	m_AttrBackUp.m_nHit					= GetHit();
	m_AttrBackUp.m_nMiss				= GetMiss();

	m_AttrBackUp.m_nExp					= GetExp();

	m_AttrBackUp.m_nDataID				= GetDataID();
	m_AttrBackUp.m_nModelID				= GetModelID();
	m_AttrBackUp.m_nMountID				= GetMountID();
	
	m_AttrBackUp.m_StrPerception		= GetStrPerception();
	m_AttrBackUp.m_ConPerception		= GetConPerception();
	m_AttrBackUp.m_DexPerception		= GetDexPerception();
	m_AttrBackUp.m_SprPerception		= GetSprPerception();
	m_AttrBackUp.m_IntPerception		= GetIntPerception();

	m_AttrBackUp.m_Str					= GetStr();
	m_AttrBackUp.m_Con					= GetCon();
	m_AttrBackUp.m_Dex					= GetDex();
	m_AttrBackUp.m_Spr					= GetSpr();
	m_AttrBackUp.m_Int					= GetInt();

	m_AttrBackUp.m_nRemainPoint			= GetRemainPoint();
	//m_AttrBackUp.m_nCampType			= m_nCampType;
__LEAVE_FUNCTION
}

VOID Obj_Pet::SendMsg_RefeshAttrib( VOID )
{
__ENTER_FUNCTION
	INT nAttr = 0;

	BOOL bPublicAttrModified, bProtectedAttrModified, bLevelModified, bDetailAttrModified;
	bPublicAttrModified		= FALSE;
	bProtectedAttrModified	= FALSE;
	bLevelModified			= FALSE;
	bDetailAttrModified		= FALSE;

	GCCharBaseAttrib msgPublicAttr, msgPublicAttrAndLevel, msgProtectedAttr;
	GCDetailAttrib_Pet msgDetail;

	msgDetail.SetObjID( GetID() );
	msgDetail.SetGUID( GetPetGUID() );
	msgPublicAttr.setObjID( GetID() );
	msgPublicAttrAndLevel.setObjID( GetID() );
	msgProtectedAttr.setObjID( GetID() );
	
	if ( m_AttrBackUp.m_bNameModified )
	{
		bPublicAttrModified = TRUE;

		msgPublicAttr.setName( GetName() );
		msgPublicAttrAndLevel.setName( GetName() );
		msgProtectedAttr.setName( GetName() );
		msgDetail.SetName( GetName() );
		m_AttrBackUp.m_bNameModified = FALSE;
	}

	if ( m_AttrBackUp.m_bTitleModified )
	{
		bPublicAttrModified = TRUE;

		msgPublicAttr.setTitle( GetTitle() );
		msgPublicAttrAndLevel.setTitle( GetTitle() );
		msgProtectedAttr.setTitle( GetTitle() );
		m_AttrBackUp.m_bTitleModified = FALSE;
	}

	if(m_AttrBackUp.m_HP != GetHP())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_HP = GetHP();

		BYTE yHPPercent = (GetMaxHP())?((BYTE)((GetHP()*100 + GetMaxHP() - 1)/GetMaxHP())):(0);
		msgPublicAttr.setHPPercent( yHPPercent );
		msgPublicAttrAndLevel.setHPPercent( yHPPercent );
		msgProtectedAttr.setHPPercent( yHPPercent );
		msgDetail.SetHP( GetHP() );
	}

	if(m_AttrBackUp.m_MaxHp != GetMaxHP())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_MaxHp = GetMaxHP();

		BYTE yHPPercent = (GetMaxHP())?((BYTE)((GetHP()*100 + GetMaxHP() - 1)/GetMaxHP())):(0);
		msgPublicAttr.setHPPercent( yHPPercent );
		msgPublicAttrAndLevel.setHPPercent( yHPPercent );
		msgProtectedAttr.setHPPercent( yHPPercent );
		msgDetail.SetHPMax( GetMaxHP());
	}

	if(fabs(m_AttrBackUp.m_MoveSpeed-GetMoveSpeed()) > 0.001f)
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_MoveSpeed = GetMoveSpeed();

		msgPublicAttr.setMoveSpeed( GetMoveSpeed() );
		msgPublicAttrAndLevel.setMoveSpeed( GetMoveSpeed() );
		msgProtectedAttr.setMoveSpeed( GetMoveSpeed() );
	}

	const _CAMP_DATA *pCampData = GetCampData();
	if ( pCampData != NULL )
	{
		if(m_AttrBackUp.m_CampData != *pCampData)
		{
			m_AttrBackUp.m_CampData = *pCampData;

			Obj_Character* pOwner = GetOwner();
			if( pOwner && pOwner->GetCampData() )
			{
				//if( pOwner->GetCampData()->m_nCampID == CAMP_1 )
				//	m_nCampType = CAMP1_PET;
				//else if( pOwner->GetCampData()->m_nCampID == CAMP_2 )
				//	m_nCampType = CAMP2_PET;

				bPublicAttrModified = TRUE;
				msgPublicAttr.setCampData( pOwner->GetCampData() );
				msgPublicAttrAndLevel.setCampData( pOwner->GetCampData() );
				msgProtectedAttr.setCampData( pOwner->GetCampData() );
			}
		}
	}

	if(m_AttrBackUp.m_nOwnerID != GetOwnerID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nOwnerID = GetOwnerID();

		msgPublicAttr.setOwnerID( GetOwnerID() );
		msgPublicAttrAndLevel.setOwnerID( GetOwnerID() );
		msgProtectedAttr.setOwnerID( GetOwnerID() );
	}

	if(m_AttrBackUp.m_nDataID != GetDataID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nDataID = GetDataID();

		msgPublicAttr.setDataID( GetDataID() );
		msgPublicAttrAndLevel.setDataID( GetDataID() );
		msgProtectedAttr.setDataID( GetDataID() );
		msgDetail.SetDataID(GetDataID());
	}

	if(m_AttrBackUp.m_nModelID != GetModelID())
	{
		bPublicAttrModified = TRUE;

		msgPublicAttr.setModelID( GetModelID() );
		msgPublicAttrAndLevel.setModelID( GetModelID() );
		msgProtectedAttr.setModelID( GetModelID() );
		msgDetail.SetModelID(GetModelID());
	}

	if(m_AttrBackUp.m_nMountID != GetMountID())
	{
		bPublicAttrModified = TRUE;

		msgPublicAttr.setMountID( GetMountID() );
		msgPublicAttrAndLevel.setMountID( GetMountID() );
		msgProtectedAttr.setMountID( GetMountID() );
		msgDetail.SetMountID(GetMountID());
	}

	if(m_AttrBackUp.m_nStealthLevel != GetStealthLevel())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nStealthLevel = GetStealthLevel();

		msgPublicAttr.setStealthLevel( GetStealthLevel() );
		msgPublicAttrAndLevel.setStealthLevel( GetStealthLevel() );
		msgProtectedAttr.setStealthLevel( GetStealthLevel() );
	}

	if(m_AttrBackUp.m_Level != GetLevel())
	{
		bLevelModified = TRUE;
		m_AttrBackUp.m_Level = GetLevel();

		msgPublicAttrAndLevel.setLevel( GetLevel() );
		msgProtectedAttr.setLevel( GetLevel() );
		msgDetail.SetLevel( GetLevel() );
	}

	if( m_AttrBackUp.m_GUID != GetPetGUID() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_GUID= GetPetGUID();
		msgDetail.SetGUID( m_AttrBackUp.m_GUID );
	}

	if( m_AttrBackUp.m_SpouseGUID != GetSpouseGUID() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_SpouseGUID= GetSpouseGUID();
		msgDetail.SetSpouseGUID( GetSpouseGUID() );
	}

	if( m_AttrBackUp.m_nAIType != GetAIType() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nAIType= GetAIType();
		msgDetail.SetAIType( GetAIType() );
	}

	if( m_AttrBackUp.m_nLife != GetLife() )
	{
		//if (GetLife()%30 == 0 || abs(m_AttrBackUp.m_nLife - GetLife()) >= 30)
		{
			bDetailAttrModified = TRUE;
			m_AttrBackUp.m_nLife= GetLife();
			msgDetail.SetLife( m_AttrBackUp.m_nLife );
		}
	}

	if( m_AttrBackUp.m_byGeneration != GetGeneration() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_byGeneration= GetGeneration();
		msgDetail.SetGeneration( m_AttrBackUp.m_byGeneration );
	}

	if( m_AttrBackUp.m_byHappiness != GetHappiness() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_byHappiness= GetHappiness();
		msgDetail.SetHappiness( m_AttrBackUp.m_byHappiness );
	}

	nAttr = Attr_VerifyGeneralAttack(GetAttackPhysics());
	if( m_AttrBackUp.m_nAtt_Physics != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nAtt_Physics= nAttr;
		msgDetail.SetAtt_Physics(nAttr);
	}

	nAttr = Attr_VerifyGeneralAttack(GetAttackMagic());
	if( m_AttrBackUp.m_nAtt_Magic != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nAtt_Magic= nAttr;
		msgDetail.SetAtt_Magic(nAttr);
	}

	nAttr = Attr_VerifyDefence(GetDefencePhysics());
	if( m_AttrBackUp.m_nDef_Physics != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nDef_Physics= nAttr;
		msgDetail.SetDef_Physics(nAttr);
	}

	nAttr = Attr_VerifyDefence(GetDefenceMagic());
	if( m_AttrBackUp.m_nDef_Magic != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nDef_Magic= nAttr;
		msgDetail.SetDef_Magic(nAttr);
	}
	nAttr = Attr_VerifyHitMiss(GetHit());
	if( m_AttrBackUp.m_nHit != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nHit= nAttr;
		msgDetail.SetHit(nAttr);
	}
	nAttr = Attr_VerifyHitMiss(GetMiss());
	if( m_AttrBackUp.m_nMiss !=nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nMiss= nAttr;
		msgDetail.SetMiss(nAttr);
	}
	nAttr = Attr_VerifyCritical(GetCritical());
	if (m_AttrBackUp.m_nCritical != nAttr)
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nCritical = nAttr;
		msgDetail.SetCritical(nAttr);
	}

	if( m_AttrBackUp.m_nExp != GetExp() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nExp= GetExp();
		msgDetail.SetExp( m_AttrBackUp.m_nExp );
	}

	if( m_AttrBackUp.m_StrPerception != GetStrPerception() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_StrPerception= GetStrPerception();
		msgDetail.SetStrPerception( m_AttrBackUp.m_StrPerception );
	}

	if( m_AttrBackUp.m_ConPerception != GetConPerception() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_ConPerception= GetConPerception();
		msgDetail.SetConPerception( m_AttrBackUp.m_ConPerception );
	}

	if( m_AttrBackUp.m_DexPerception != GetDexPerception() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_DexPerception= GetDexPerception();
		msgDetail.SetDexPerception( m_AttrBackUp.m_DexPerception );
	}

	if( m_AttrBackUp.m_SprPerception != GetSprPerception() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_SprPerception= GetSprPerception();
		msgDetail.SetSprPerception( m_AttrBackUp.m_SprPerception );
	}

	if( m_AttrBackUp.m_IntPerception != GetIntPerception() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_IntPerception= GetIntPerception();
		msgDetail.SetIntPerception( m_AttrBackUp.m_IntPerception );
	}

	if( m_AttrBackUp.m_Str != GetStr())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_Str= GetStr();
		msgDetail.SetStr( m_AttrBackUp.m_Str );
	}

	if( m_AttrBackUp.m_Con != GetCon() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_Con= GetCon();
		msgDetail.SetCon( m_AttrBackUp.m_Con );
	}

	if( m_AttrBackUp.m_Dex != GetDex() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_Dex= GetDex();
		msgDetail.SetDex( m_AttrBackUp.m_Dex );
	}

	if( m_AttrBackUp.m_Spr != GetSpr())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_Spr= GetSpr();
		msgDetail.SetSpr( m_AttrBackUp.m_Spr );
	}

	if( m_AttrBackUp.m_Int != GetInt())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_Int= GetInt();
		msgDetail.SetInt( m_AttrBackUp.m_Int );
	}

	if( m_AttrBackUp.m_GenGu != GetGenGu())
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_GenGu= GetGenGu();
		msgDetail.SetGenGu( m_AttrBackUp.m_GenGu );
	}

	if( m_AttrBackUp.m_nRemainPoint != GetRemainPoint() )
	{
		bDetailAttrModified = TRUE;
		m_AttrBackUp.m_nRemainPoint= GetRemainPoint();
		msgDetail.SetRemainPoint( m_AttrBackUp.m_nRemainPoint );
	}

	if ( bPublicAttrModified || bProtectedAttrModified || bLevelModified )
	{
		bDetailAttrModified = TRUE;

		if ( bPublicAttrModified || bLevelModified )
		{
			m_PublicAttrVersion++;
		}

		if ( bPublicAttrModified || bLevelModified || m_ProtectedAttrVersion )
		{
			m_ProtectedAttrVersion++;
		}

		HUMANLIST listHuman;
		getScene()->ScanHuman( getZoneID(), MAX_REFESH_OBJ_ZONE_RADIUS, &(listHuman) );

		BOOL bSendPublicMsg				= bPublicAttrModified;
		BOOL bSendPublicAndLevelMsg		= (BOOL)(bPublicAttrModified || bLevelModified);
		BOOL bSendProtectedMsg			= (BOOL)(bPublicAttrModified || bLevelModified || m_ProtectedAttrVersion);
		BYTE i;
		for ( i = 0; i < listHuman.m_Count; i++ )
		{
			Obj_Human *pTargetHuman = listHuman.m_aHuman[i];
			if ( IsCanViewMe( pTargetHuman ) )
			{
				ENUM_REFESH_ATTR_TYPE eType = CalcRefeshAttrType( this, pTargetHuman );
				switch( eType )
				{
				case REFESH_ATTR_TYPE_NONE:
					break;
				case REFESH_ATTR_TYPE_PUBLIC:
					if ( bSendPublicMsg )
					{
						pTargetHuman->GetPlayer()->SendPacket( &msgPublicAttr );
					}
					break;
				case REFESH_ATTR_TYPE_PUBLIC_AND_LEVEL:
					if ( bSendPublicAndLevelMsg )
					{
						pTargetHuman->GetPlayer()->SendPacket( &msgPublicAttrAndLevel );
					}
					break;
				case REFESH_ATTR_TYPE_PROTECTED:
					if ( bSendProtectedMsg )
					{
						pTargetHuman->GetPlayer()->SendPacket( &msgProtectedAttr );
					}
					break;
				default:
					break;
				}
			}
		}
	}

	bDetailAttrModified |= bPublicAttrModified | bProtectedAttrModified | bLevelModified;
	if ( bDetailAttrModified )
	{
		Obj_Human *pOwner = (Obj_Human*)(GetOwner());
		if (pOwner && pOwner->GetObjType() == Obj::OBJ_TYPE_HUMAN )
			pOwner->GetPlayer()->SendPacket( &msgDetail );
	}

__LEAVE_FUNCTION
}

VOID Obj_Pet::AskMsg_BaseAttrib( Obj_Human *pTargetHuman )
{
__ENTER_FUNCTION

	if ( IsCanViewMe( pTargetHuman ) )
	{
		GCCharBaseAttrib msgAttr;

		BYTE yHPPercent = (GetMaxHP())?((BYTE)((GetHP()*100 + GetMaxHP() - 1)/GetMaxHP())):(0);
		BYTE yMPPercent = (GetMaxMP())?((BYTE)((GetMP()*100 + GetMaxMP() - 1)/GetMaxMP())):(0);
		Obj_Character* pOwner = GetOwner();
		INT nObjectCampType = INVALID_CAMP;

		msgAttr.setObjID( GetID() );
		msgAttr.setDataID( (WORD)GetDataID() );
		msgAttr.setLevel(GetLevel());
		msgAttr.setName( GetName() );
		msgAttr.setHPPercent( yHPPercent );
		msgAttr.setMPPercent( yMPPercent );
		msgAttr.setRage( GetRage() );
		msgAttr.setDataID(GetDataID());
		msgAttr.setStealthLevel( GetStealthLevel() );
		msgAttr.setCampData( GetCampData() );
		msgAttr.setOwnerID( GetOwnerID() );
		msgAttr.setModelID( GetModelID() );
		msgAttr.setMountID(GetMountID());
		msgAttr.setMoveSpeed(GetMoveSpeed());
		msgAttr.setAttackSpeed((FLOAT)GetAttackSpeed());

		ENUM_REFESH_ATTR_TYPE eType = CalcRefeshAttrType( this, pTargetHuman );
		switch( eType )
		{
		case REFESH_ATTR_TYPE_NONE:
			break;
		case REFESH_ATTR_TYPE_PUBLIC:
			{
			}
			break;
		case REFESH_ATTR_TYPE_PUBLIC_AND_LEVEL:
			{
				msgAttr.setLevel( GetLevel() );
			}
			break;
		case REFESH_ATTR_TYPE_PROTECTED:
			{
				msgAttr.setLevel( GetLevel() );
			}
			break;
		default:
			break;
		}
		pTargetHuman->GetPlayer()->SendPacket( &msgAttr );
		//在发送属性数据的同时发送角色的效果列表数据
		GCCharImpactListUpdate ImpactListUpdate;
		ImpactListUpdate.SetOwnerID(GetID());
		ImpactListUpdate.SetImpactList(Impact_GetImpactList());
		pTargetHuman->GetPlayer()->SendPacket(&ImpactListUpdate);
	}

__LEAVE_FUNCTION
}

VOID Obj_Pet::AskMsg_DetailAttrib( Obj_Human *pTargetHuman )
{
__ENTER_FUNCTION

	// 
	if ( pTargetHuman == GetOwner() )
	{
		GCDetailAttrib_Pet msgDetail;

		msgDetail.SetGUID( GetPetGUID() );

		msgDetail.SetObjID( GetID() );
		msgDetail.SetDataID( GetDataID() );
		msgDetail.SetName( GetName() );
		msgDetail.SetHP( GetHP() );
		msgDetail.SetHPMax(GetMaxHP());
		msgDetail.SetAIType( GetAIType() );
		msgDetail.SetSpouseGUID( GetSpouseGUID() );
		msgDetail.SetLevel( GetLevel() );
		msgDetail.SetDataID(GetDataID());
		msgDetail.SetModelID( GetModelID() );
		msgDetail.SetMountID(GetMountID());
		msgDetail.SetLife( GetLife() );
		msgDetail.SetGeneration( GetGeneration() );
		msgDetail.SetHappiness( GetHappiness() );
		msgDetail.SetAtt_Physics(Attr_VerifyGeneralAttack(GetAttackPhysics()));
		msgDetail.SetAtt_Magic(Attr_VerifyGeneralAttack(GetAttackMagic()));
		msgDetail.SetDef_Physics(Attr_VerifyDefence(GetDefencePhysics()));
		msgDetail.SetDef_Magic(Attr_VerifyDefence(GetDefenceMagic()));
		msgDetail.SetHit(GetHit());
		msgDetail.SetMiss(GetMiss());
		msgDetail.SetCritical(GetCritical());
		msgDetail.SetExp(GetExp());
		msgDetail.SetStrPerception(GetStrPerception());
		msgDetail.SetConPerception(GetConPerception());
		msgDetail.SetDexPerception(GetDexPerception());
		msgDetail.SetSprPerception(GetSprPerception());
		msgDetail.SetIntPerception(GetIntPerception());
		msgDetail.SetStr(GetStr());
		msgDetail.SetCon(GetCon());
		msgDetail.SetDex(GetDex());
		msgDetail.SetSpr(GetSpr());
		msgDetail.SetInt(GetInt());
		msgDetail.SetGenGu(GetGenGu());
		msgDetail.SetRemainPoint(GetRemainPoint());
		pTargetHuman->GetPlayer()->SendPacket(&msgDetail);
		//在发送详细属性数据的同时发送角色宠物的效果列表详细数据
		GCDetailImpactListUpdate ImpactListUpdate;
		ImpactListUpdate.SetOwnerID(GetID());
		ImpactListUpdate.SetImpactList(Impact_GetImpactList());
		pTargetHuman->GetPlayer()->SendPacket(&ImpactListUpdate);
	}
__LEAVE_FUNCTION
}
