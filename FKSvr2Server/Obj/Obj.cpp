#include "stdafx.h"
// Obj.cpp

#include "Scene.h"
#include "ObjList.h"
#include "GCDelObject.h"
#include "GCObjTeleport.h"
#include "GUIDManager.h"

#include "Obj.h"

Obj::Obj( )
{
__ENTER_FUNCTION

	m_ObjID				= INVALID_ID;
	m_uPoolID			= UINT_MAX;
	m_uSingleMgrIndex	= UINT_MAX;
	m_pObjNode			= new _OBJ_LIST_NODE( this );
	m_bActive			= FALSE;

	m_Pos.CleanUp();
	m_Dir				= 0.f;
	m_pScene			= NULL;
	m_ZoneID			= INVALID_ID;
	m_uLastTime			= 0;
	m_uNowTime			= 0;
	m_uCreateTime		= 0;

	m_nLogicCount		= 0;
__LEAVE_FUNCTION
}

Obj::~Obj( )
{
__ENTER_FUNCTION

	SAFE_DELETE( m_pObjNode );

__LEAVE_FUNCTION
}

VOID Obj::OnEnterScene(VOID)
{
__ENTER_FUNCTION

	m_uLastTime			= 0;
	m_uNowTime			= 0;
	m_uCreateTime		= 0;

__LEAVE_FUNCTION
}

VOID Obj::OnLeaveScene(VOID)
{
__ENTER_FUNCTION

	m_uLastTime			= 0;
	m_uNowTime			= 0;
	m_uCreateTime		= 0;

__LEAVE_FUNCTION
}

VOID Obj::UpdateTime(UINT uTime)
{
__ENTER_FUNCTION
	if(m_uNowTime == 0)
	{
		m_uCreateTime	=uTime;
		m_uLastTime		=uTime;
	}
	else
	{
		m_uLastTime		= m_uNowTime;
	}
	m_uNowTime =uTime;
__LEAVE_FUNCTION
}

VOID Obj::CleanUp( )
{
__ENTER_FUNCTION

	m_bActive	= FALSE;
	Assert( m_pObjNode->m_pNext == NULL );
	Assert( m_pObjNode->m_pPrev == NULL );

	m_Pos.CleanUp();
	m_Dir		= 0.f;
	//m_pScene	= NULL;
	m_ZoneID	= INVALID_ID;

__LEAVE_FUNCTION
}

BOOL Obj::Init( const _OBJ_INIT *pInit )
{
__ENTER_FUNCTION

	if ( pInit == NULL )
		return FALSE;

	m_Pos				= pInit->m_Pos;
	m_Dir				= pInit->m_Dir;
	UpdateZone();
	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL Obj::HeartBeat(UINT uTime)
{
__ENTER_FUNCTION

	UpdateTime(uTime);

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

// 未被击活的Obj所执行的逻辑
BOOL Obj::HeartBeat_OutZone( UINT uTime )
{
__ENTER_FUNCTION

	UpdateTime(uTime);

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL Obj::IsInValidRadius(FLOAT fX1, FLOAT fZ1, FLOAT fX2, FLOAT fZ2, FLOAT fRadius)
{
	FLOAT fDistX, fDistZ;

	fDistX = fX1 - fX2;
	fDistZ = fZ1 - fZ2;

	return ((fRadius*fRadius) > (fDistX*fDistX + fDistZ*fDistZ));
}

BOOL Obj::IsInValidRadius(const Obj *pOb, FLOAT fRadius)
{
__ENTER_FUNCTION

	Assert(pOb != NULL);

	return IsInValidRadius(m_Pos.m_fX, m_Pos.m_fZ, pOb->m_Pos.m_fX, pOb->m_Pos.m_fZ, fRadius);

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Obj::IsInValidRadius(const WORLD_POS *pPos, FLOAT fRadius)
{
__ENTER_FUNCTION

	Assert(pPos != NULL);

	return IsInValidRadius(m_Pos.m_fX, m_Pos.m_fZ, pPos->m_fX, pPos->m_fZ, fRadius);

__LEAVE_FUNCTION

	return FALSE ;
}

VOID Obj::SetActiveFlag( BOOL bFlag )
{
__ENTER_FUNCTION

	BYTE bNewActive = (BYTE)bFlag;
	if ( m_bActive != bNewActive )
	{
		m_bActive = bNewActive;
		// 将对象注册或反注册到相应的Zone中
        if ( m_ZoneID != INVALID_ID )
		{
			if ( m_bActive )
			{
				BOOL bRet = getScene()->ObjZone_Register( this, m_ZoneID );
				if ( !bRet )
				{
					Assert( bRet && "Obj::SetActiveFlag ObjZone_Register return FALSE" );
				}
				OnRegisterToZone();
			}
			else
			{
				BOOL bRet = getScene()->ObjZone_Unregister( this, m_ZoneID );
				if ( !bRet )
				{
					Assert( bRet && "Obj::SetActiveFlag ObjZone_Unregister return FALSE" );
				}
				m_ZoneID = -1;
				OnUnregisterFromZone();
			}
		}
	}

__LEAVE_FUNCTION
}

BOOL Obj::UpdateZone( VOID )
{
__ENTER_FUNCTION

	if ( getScene() == NULL )
		return FALSE;

	ZoneID_t idNew = getScene()->CalcZoneID( getWorldPos() );
	ZoneID_t idOld = m_ZoneID;
	if ( idNew != idOld )
	{
		m_ZoneID = idNew;
		if ( IsActiveObj() )
		{
			if ( idNew != INVALID_ID )
			{
				if ( idOld != INVALID_ID )
				{
					BOOL bRet = getScene()->ObjZone_Changed( this, idNew, idOld );
					if ( !bRet )
					{
						Assert( bRet && "Obj::UpdateZone ObjZone_Changed return FALSE" );
					}
				}
				else
				{
					BOOL bRet = getScene()->ObjZone_Register( this, m_ZoneID );
					if ( !bRet )
					{
						Assert( bRet && "Obj::UpdateZone ObjZone_Register return FALSE" );
					}
					OnRegisterToZone();
				}
			}
		}
	}
	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

VOID Obj::Teleport( const WORLD_POS* pos )
{
__ENTER_FUNCTION

	Scene* pScene = getScene();
	if (pScene)
	{
		if ( !pScene->GetMap()->IsCanGo( *const_cast<WORLD_POS*>(pos),0 ) )
			return ;
	}

	setWorldPos( pos );

	UpdateZone();

	if ( getScene() == NULL )
	{
		Assert( getScene() != NULL && "Obj::Teleport" );
		return ;
	}

	// 同步一个Teleport的MSG到客户端
	// to be continue...
	GCObjTeleport msgTeleport;
	msgTeleport.setObjID( GetID() );
	msgTeleport.setWorldPos( m_Pos );

	HUMANLIST listHuman;
	getScene()->ScanHuman( getZoneID(), MAX_REFESH_OBJ_ZONE_RADIUS, &(listHuman) );

	BYTE i;
	for ( i = 0; i < listHuman.m_Count; i++ )
	{
		Obj_Human *pTargetHuman = listHuman.m_aHuman[i];
		if ( IsCanViewMe( pTargetHuman ) )
		{
			pTargetHuman->GetPlayer()->SendPacket( &msgTeleport );
		}
	}

__LEAVE_FUNCTION
}

Packet *Obj::CreateDeleteObjPacket( VOID )
{
__ENTER_FUNCTION

	if ( getScene() != NULL )
	{
		GCDelObject *pPacket = (GCDelObject*)(getScene()->m_pPacket_DelObject);
		pPacket->setObjID( GetID() );
		pPacket->setSceneID( getScene()->SceneID() );
		return pPacket;
	}
	else
	{
		return NULL;
	}

__LEAVE_FUNCTION

	return NULL;
}

VOID Obj::DestroyDeleteObjPacket( Packet *pPacket )
{
}
Obj* Obj::GetSpecificObjInSameSceneByID(ObjID_t nID)
{
__ENTER_FUNCTION
	if(NULL==m_pScene)
	{
		AssertEx(FALSE,"[Obj::GetSpecificObjInSameSceneByID]: m_pScene is NULL!!!");
		return NULL;
	}
	ObjManager* pObjManager = m_pScene->GetObjManager();
	if(NULL==pObjManager)
	{
		AssertEx(FALSE,"[Obj::GetSpecificObjInSameSceneByID]: m_pObjManager is NULL!!!");
		return NULL;
	}
	return pObjManager->GetObj(nID);
__LEAVE_FUNCTION
	return NULL;
}

Obj* Obj::GetSpecificHumanInSameSceneByGUID(GUID_t nID)
{
__ENTER_FUNCTION
	Obj* pObj = NULL;
	if(NULL!=g_pGUIDManager)
	{
		pObj = static_cast<Obj*>(g_pGUIDManager->Get(nID));
	}
	return pObj;
__LEAVE_FUNCTION
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////
//obj 公共属性调用接口
UINT Obj::GetUniqueID(VOID) const
{
	UINT nValue = __GetSceneID();
	nValue = nValue<<16;
	nValue += GetID()&0x0000FFFF;
	return nValue;
}
const SceneID_t Obj::__GetSceneID( ) const//场景号 obj
{
	if( m_pScene ) return m_pScene->SceneID() ;

	return INVALID_ID ;
}
Scene* Obj::__GetScene( )//场景指针
{
	return m_pScene ;
}
VOID Obj::__SetScene( Scene* scene )
{
	m_pScene = scene ;
}
const ZoneID_t Obj::__GetZoneID( ) const//区域号 obj
{
	return m_ZoneID ;
}
VOID Obj::__SetZoneID( const ZoneID_t zoneid )
{
	m_ZoneID = zoneid ;
}
const ScriptID_t Obj::__GetScriptID( ) const//脚本号 obj
{
	return INVALID_ID ;
}
VOID Obj::__SetScriptID( const ScriptID_t scriptid )
{
}
const WORLD_POS* Obj::__GetWorldPos( ) const//位置 obj
{
	return &m_Pos ;
}
VOID Obj::__SetWorldPos( const WORLD_POS* worldpos )
{
	m_Pos = *worldpos ;
}
const FLOAT Obj::__GetDir( ) const//方向 obj
{
	return m_Dir ;
}
VOID Obj::__SetDir( const FLOAT dir )
{
	m_Dir = dir ;
}
const ObjID_t Obj::__GetID( ) const//obj号 obj
{
	return m_ObjID ;
}
VOID Obj::__SetID( const ObjID_t id )
{
	m_ObjID = id ;
}
