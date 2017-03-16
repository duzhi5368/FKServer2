#include "stdafx.h"
// Obj_Special.cpp
#include "Scene.h"
#include "GCNewSpecial.h"
#include "Obj_Special.h"
#include "GameStruct.h"
#include "GameTable.h"
#include "SpecialObjLogic.h"
#include "LogicManager.h"

#include "GCSpecialObj_ActNow.h"
#include "GCSpecialObj_FadeOut.h"
using namespace Combat_Module;
using namespace Combat_Module::Special_Obj_Module;
using namespace Packets;

Obj_Special::Obj_Special( VOID )
{
__ENTER_FUNCTION
	CleanUp();
__LEAVE_FUNCTION
}

Obj_Special::~Obj_Special( VOID )
{
__ENTER_FUNCTION
		
__LEAVE_FUNCTION
}
BOOL Obj_Special::Init( const _OBJ_INIT *pInit )
{
	__ENTER_FUNCTION
	if(NULL==pInit)
	{
		return FALSE;
	}
	if(!Obj_Dynamic::Init(pInit))
		return FALSE;
	_OBJ_SPECIAL_INIT const * pIniter = (_OBJ_SPECIAL_INIT const*)pInit;
	m_nDataID = pIniter->m_nDataID;
	m_nOwner = pIniter->m_nOwnerID;
	//Init Obj_Special Start
	if(INVALID_ID == m_nDataID)
	{
		return FALSE;
	}
	return InitFromData();
	__LEAVE_FUNCTION
	return FALSE;
}

VOID Obj_Special::CleanUp( VOID )
{
	__ENTER_FUNCTION

	Obj_Dynamic::CleanUp( ) ;
	m_nContinuance = 0;
	m_nInterval = 0;
	m_nElapsedInterval = 0;
	m_nDelayTime = 0;
	m_nOwner = INVALID_ID;
	m_nPowerRefixByValue = 0;
	m_nPowerRefixByRate = 0;
	m_nDataID = INVALID_ID;
	m_nStealthLevel = 0;
	m_bFadeOut = false;
	m_nActiveTimes = 0;
	m_nClass = INVALID_ID;
	memset((VOID*)m_aParams, 0, sizeof(m_aParams));

	__LEAVE_FUNCTION
}

BOOL Obj_Special::InitFromData()
{
	__ENTER_FUNCTION
	if(INVALID_ID==m_nDataID)
	{
		return FALSE;
	}
	SpecialObjData_T const* pData = g_SpecialObjDataMgr.GetInstanceByID(m_nDataID);
	if(NULL==pData)
	{
		return FALSE;
	}
	SpecialObjLogic_T const* pLogic = ObjSpecial_GetLogic(*this);
	//load data start
	m_nContinuance = pData->GetContinuance();
	m_nInterval = pData->GetInterval();
	m_bFadeOut = false;
	m_nActiveTimes = pData->GetActiveTimes();
	m_nClass = pLogic->GetType();
	m_nStealthLevel = pData->GetStealthLevel();
	//load data end
	return TRUE;
	__LEAVE_FUNCTION
	return FALSE;
}
INT	Obj_Special::GetParamByIndex(INT nIdx) const
{
	__ENTER_FUNCTION
	if(0>nIdx || NUM_OF_PARAMS<=nIdx)
	{
		AssertEx(NULL,"[Obj_Special::GetParamByIndex(INT nIdx)]: nIdx out of range!!");
		return -1;
	}
	return m_aParams[nIdx];
	__LEAVE_FUNCTION
	return -1;
}
VOID Obj_Special::SetParamByIndex(INT nIdx, INT nParam)
{
	__ENTER_FUNCTION
	if(0>nIdx || NUM_OF_PARAMS<=nIdx)
	{
		AssertEx(NULL,"[Obj_Special::GetParamByIndex(INT nIdx)]: nIdx out of range!!");
	}
	else
	{
		m_aParams[nIdx]=nParam;
	}
	__LEAVE_FUNCTION
}

BOOL Obj_Special::HeartBeat( UINT uTime )
{
	__ENTER_FUNCTION
	if(FALSE==Obj_Dynamic::HeartBeat(uTime))
	{
		return FALSE;
	}
	if(TRUE==m_bFadeOut)
	{
		SetActiveFlag(FALSE);
		return TRUE;
	}
	Time_t nDeltaTime = GetLogicTime();

	//Interval process
	if(0 < m_nInterval)
	{
		nDeltaTime>m_nContinuance?nDeltaTime=m_nContinuance:NULL;
		m_nElapsedInterval += nDeltaTime;
		while (m_nElapsedInterval >= m_nInterval)
		{
			// Impact activited
			OnTick();
			m_nElapsedInterval -= m_nInterval;
		}
	}
	if(0<m_nContinuance)
	{
		if(0<m_nContinuance)
		{
			m_nContinuance -= nDeltaTime;
		}
		if(0>=m_nContinuance)
		{
			// disable this obj
			OnTimeOver();
			m_bFadeOut=TRUE;
			m_nContinuance = 0;
		}
	}
	else
	{
		m_bFadeOut=TRUE;
	}

	return TRUE ;

	__LEAVE_FUNCTION

	return FALSE ;
}

// 未被击活的Obj所执行的逻辑
BOOL Obj_Special::HeartBeat_OutZone( UINT uTime )
{
	BOOL bResult = Obj_Dynamic::HeartBeat_OutZone(uTime);
	if(!bResult)
	{
		return bResult;
	}
	if(TRUE==IsFadeOut())
	{
		// 直接返回删除
		return FALSE;
	}
	return TRUE;
}

BOOL Obj_Special::IsCanViewMe( const Obj *pObj )
{
__ENTER_FUNCTION
	if(NULL==pObj)
	{
		return FALSE;
	}
	if(INVALID_ID!=m_nOwner)
	{
		Obj* pOwner = GetSpecificObjInSameSceneByID(m_nOwner);
		if(NULL!=pOwner)
		{
			if(TRUE==IsCharacterObj(pOwner->GetObjType()))
			{
				Obj_Character& rOwner = *(static_cast<Obj_Character*>(pOwner));
				if(TRUE==IsCharacterObj(pObj->GetObjType()))
				{
					Obj_Character* pCharacter = const_cast<Obj_Character*>(static_cast<Obj_Character const*>(pObj));
					if(TRUE==rOwner.IsPartner(pCharacter))
					{
						return TRUE;
					}
				}
			}
		}
	}
	if(Obj::OBJ_TYPE_HUMAN == pObj->GetObjType())
	{
		Obj_Human& rHuman = (Obj_Human&)*pObj;
		return rHuman.Impact_CanViewThisSpecialObj(*this);
	}
	return FALSE;
__LEAVE_FUNCTION
	return FALSE;
}

VOID Obj_Special::OnTick(VOID)
{
__ENTER_FUNCTION
	SpecialObjLogic_T const* pLogic = ObjSpecial_GetLogic(*this);
	if(NULL!=pLogic)
	{
		pLogic->OnTick(*this);
	}
__LEAVE_FUNCTION
}

VOID Obj_Special::OnTimeOver(VOID)
{
__ENTER_FUNCTION
	SpecialObjLogic_T const* pLogic = ObjSpecial_GetLogic(*this);
	if(NULL!=pLogic)
	{
		pLogic->OnTimeOver(*this);
	}
__LEAVE_FUNCTION
}

Packet *Obj_Special::CreateNewObjPacket( VOID )
{
__ENTER_FUNCTION

	if ( getScene() != NULL )
	{
		GCNewSpecial *pPacket = (GCNewSpecial*)(getScene()->m_pPacket_NewSpecial);
		pPacket->setObjID( GetID() );
		pPacket->setDataID( GetDataID() );
		pPacket->setWorldPos( *(getWorldPos()) );
		pPacket->setDir( getDir() );
		return pPacket;
	}
	else
	{
		Assert( getScene() != NULL && "Obj_Special::CreateNewObjPacket" );
		return NULL;
	}

__LEAVE_FUNCTION

	return NULL;
}

VOID Obj_Special::DestroyNewObjPacket( Packet *pPacket )
{
}

VOID Obj_Special::OnTrigger(ObjID_List const& rTargetList)
{
__ENTER_FUNCTION
	if ( getScene() != NULL )
	{
		GCSpecialObj_ActNow msgActNow;
		msgActNow.SetObjID( GetID() );
		msgActNow.SetTargetList(rTargetList);
		msgActNow.SetLogicCount(GetLogicCount());

		getScene()->BroadCast( &msgActNow, getZoneID() ) ;
	}
	else
	{
		AssertEx(FALSE,"[Obj_Special::OnTrigger]: GetScene() return NULL!!");
	}
__LEAVE_FUNCTION
}

VOID Obj_Special::OnFadeOut(VOID)
{
__ENTER_FUNCTION
	if ( getScene() != NULL )
	{
		GCSpecialObj_FadeOut msgFadeOut;
		msgFadeOut.SetObjID( GetID() );
	
		getScene()->BroadCast( &msgFadeOut, getZoneID() ) ;
	}
	else
	{
		AssertEx(FALSE,"[Obj_Special::OnFadeOut]: GetScene() return NULL!!");
	}
__LEAVE_FUNCTION
}
SpecialObjData_T const* Obj_Special::GetDataRecord(VOID) const
{
__ENTER_FUNCTION
	SpecialObjData_T const* pData = g_SpecialObjDataMgr.GetInstanceByID(m_nDataID);
	if(NULL==pData)
	{
		AssertEx(FALSE,"[TrapLogic_T::FadeOutNow]: Can not find data record!");
	}
	return pData;
__LEAVE_FUNCTION
	return NULL;
}
