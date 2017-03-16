#include "stdafx.h"
// Obj_Monster_AttrRefesh.cpp

#include "Scene.h"
#include "Obj_Human.h"

#include "GCCharBaseAttrib.h"
#include "GCCharImpactListUpdate.h"
#include "GameTable.h"

#include "Obj_Monster.h"

extern ENUM_REFESH_ATTR_TYPE CalcRefeshAttrType(Obj_Character *pSour, Obj_Character *pTarget );


VOID Obj_Monster::InitBackupAttr()
{
__ENTER_FUNCTION

	m_AttrBackUp.m_bNameModified		= FALSE;
	m_AttrBackUp.m_bTitleModified		= FALSE;
	m_AttrBackUp.m_HP					= GetHP();
	const _CAMP_DATA *pCampData = GetCampData();
	if ( pCampData != NULL )
		m_AttrBackUp.m_CampData			= *pCampData;
	m_AttrBackUp.m_MaxHp				= GetMaxHP();
	m_AttrBackUp.m_MoveSpeed			= GetMoveSpeed();
	m_AttrBackUp.m_nDataID				= GetDataID();
	m_AttrBackUp.m_nModelID				= GetModelID();
	m_AttrBackUp.m_nMountID				= GetMountID();
	m_AttrBackUp.m_nAIType				= GetAIType();
	m_AttrBackUp.m_OwnerID				= GetOwnerID();
	m_AttrBackUp.m_OccupantGUID			= GetOccupantGUID();
	m_AttrBackUp.m_nStealthLevel		= GetStealthLevel();
	m_AttrBackUp.m_nMoodState			= GetMoodState();

__LEAVE_FUNCTION
}

VOID Obj_Monster::SendMsg_RefeshAttrib( VOID )
{
__ENTER_FUNCTION

	BOOL bPublicAttrModified ;
	bPublicAttrModified		= FALSE;

	GCCharBaseAttrib msgPublicAttr, msgProtectedAttr;

	msgPublicAttr.setObjID( GetID() );
	msgProtectedAttr.setObjID( GetID() );

	msgPublicAttr.setIsNPC( IsNPC() );
	msgProtectedAttr.setIsNPC( IsNPC() );

	//msgPublicAttr.setName( GetName() );
	//msgProtectedAttr.setName( GetName() );

	//msgPublicAttr.setTitle( GetTitle() );
	//msgProtectedAttr.setTitle( GetTitle() );

	if(m_AttrBackUp.m_HP != GetHP())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_HP = GetHP();

		BYTE yHPPercent = (GetMaxHP())?((BYTE)((GetHP()*100 + GetMaxHP() - 1)/GetMaxHP())):(0);
		msgPublicAttr.setHPPercent( yHPPercent );
		msgProtectedAttr.setHPPercent( yHPPercent );
	}

	if(m_AttrBackUp.m_MaxHp != GetMaxHP())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_MaxHp = GetMaxHP();

		BYTE yHPPercent = (GetMaxHP())?((BYTE)((GetHP()*100 + GetMaxHP() - 1)/GetMaxHP())):(0);
		msgPublicAttr.setHPPercent( yHPPercent );
		msgProtectedAttr.setHPPercent( yHPPercent );
	}

	if(fabs(m_AttrBackUp.m_MoveSpeed-GetMoveSpeed()) > 0.001f)
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_MoveSpeed = GetMoveSpeed();

		msgPublicAttr.setMoveSpeed( GetMoveSpeed() );
		msgProtectedAttr.setMoveSpeed( GetMoveSpeed() );
	}

	if(m_AttrBackUp.m_nDataID != GetDataID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nDataID = GetDataID();

	}

	const _CAMP_DATA *pCampData = GetCampData();
	if ( pCampData != NULL )
	{
		if(m_AttrBackUp.m_CampData != *pCampData)
		{
			bPublicAttrModified = TRUE;
			m_AttrBackUp.m_CampData = *pCampData;

			msgPublicAttr.setCampData( pCampData );
			msgProtectedAttr.setCampData( pCampData );
		}
	}
	//if( m_AttrBackUp.m_nCampType != m_nCampType )
	//{
	//	bPublicAttrModified = TRUE;
	//	m_AttrBackUp.m_nCampType = m_nCampType;
	//	msgPublicAttr.setCampType( m_nCampType );
	//	msgProtectedAttr.setCampType( m_nCampType );
	//}

	if(m_AttrBackUp.m_OwnerID != GetOwnerID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_OwnerID = GetOwnerID();

		msgPublicAttr.setOwnerID( GetOwnerID() );
		msgProtectedAttr.setOwnerID( GetOwnerID() );
	}

	if(m_AttrBackUp.m_OccupantGUID != GetOccupantGUID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_OccupantGUID = GetOccupantGUID();

		msgPublicAttr.setOccupantGUID( GetOccupantGUID() );
		msgProtectedAttr.setOccupantGUID( GetOccupantGUID() );
	}

	if(m_AttrBackUp.m_nModelID != GetModelID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nModelID = GetModelID();
		msgPublicAttr.setModelID( GetModelID() );
		msgProtectedAttr.setModelID( GetModelID() );
	}

	if(m_AttrBackUp.m_nMountID != GetMountID())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nMountID = GetMountID();
		msgPublicAttr.setMountID( GetMountID() );
		msgProtectedAttr.setMountID( GetMountID() );
	}

	if (m_AttrBackUp.m_nAIType != GetAIType() )
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nAIType = GetAIType();
		INT nRet = GetMonsterAIType();
		msgPublicAttr.setAIType(nRet);
		msgProtectedAttr.setAIType(nRet);
	}

	if(m_AttrBackUp.m_nStealthLevel != GetStealthLevel())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nStealthLevel = GetStealthLevel();

		msgPublicAttr.setStealthLevel( GetStealthLevel() );
		msgProtectedAttr.setStealthLevel( GetStealthLevel() );
	}

	if(m_AttrBackUp.m_nMoodState != GetMoodState())
	{
		bPublicAttrModified = TRUE;
		m_AttrBackUp.m_nMoodState = GetMoodState();

		msgPublicAttr.setMoodState( GetMoodState() );
		msgProtectedAttr.setMoodState( GetMoodState() );
	}

	if ( bPublicAttrModified )
	{
		if ( bPublicAttrModified )
		{
			m_PublicAttrVersion++;
		}

		if ( bPublicAttrModified || m_ProtectedAttrVersion )
		{
			m_ProtectedAttrVersion++;
		}

		HUMANLIST listHuman;
		getScene()->ScanHuman( getZoneID(), MAX_REFESH_OBJ_ZONE_RADIUS, &(listHuman) );

		BOOL bSendPublicMsg				= bPublicAttrModified;
		BOOL bSendProtectedMsg			= (BOOL)(bPublicAttrModified || m_ProtectedAttrVersion);
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
				case REFESH_ATTR_TYPE_PUBLIC_AND_LEVEL:
					if ( bSendPublicMsg )
					{
						pTargetHuman->GetPlayer()->SendPacket( &msgPublicAttr );
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

__LEAVE_FUNCTION
}

VOID Obj_Monster::AskMsg_BaseAttrib( Obj_Human *pTargetHuman )
{
__ENTER_FUNCTION

	if ( IsCanViewMe( pTargetHuman ) )
	{
		GCCharBaseAttrib msgAttr;

		BYTE yHPPercent = (GetMaxHP())?((BYTE)((GetHP()*100 + GetMaxHP() - 1)/GetMaxHP())):(0);
		BYTE yMPPercent = (GetMaxMP())?((BYTE)((GetMP()*100 + GetMaxMP() - 1)/GetMaxMP())):(0);

		msgAttr.setObjID( GetID() );
		msgAttr.setDataID( (WORD)GetDataID() );
		msgAttr.setName( GetName() );
		msgAttr.setTitle( GetTitle() );
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
		msgAttr.setAIType(GetMonsterAIType() );
		msgAttr.setAttackSpeed((FLOAT)GetAttackSpeed());
		msgAttr.setOccupantGUID(GetOccupantGUID()) ;
		msgAttr.setOwnerID(GetOwnerID()) ;
		msgAttr.setIsNPC( IsNPC() );

#if 1
		msgAttr.setLevel( GetLevel() );
#else
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
#endif
		pTargetHuman->GetPlayer()->SendPacket( &msgAttr );
		//在发送属性数据的同时发送角色的效果列表数据
		GCCharImpactListUpdate ImpactListUpdate;
		ImpactListUpdate.SetOwnerID(GetID());
		ImpactListUpdate.SetImpactList(Impact_GetImpactList());
		pTargetHuman->GetPlayer()->SendPacket(&ImpactListUpdate);
	}

__LEAVE_FUNCTION
}
