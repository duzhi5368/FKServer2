#include "stdafx.h"
#include "Obj_ItemBox.h"
#include "Scene.h"
#include "Log.h"
#include "Config.h"
#include "GCNewItemBox.h"
#include "TimeManager.h"
#include "GameTable.h"
#include "Item.h"
#include "ItemOperator.h"
#include "LogDefine.h"

Obj_ItemBox::Obj_ItemBox()
{
__ENTER_FUNCTION
		
		Item	itemIterator;

		_ITEMCONTAINER_INIT	containInit;
		containInit.m_nContainerSize	=	MAX_BOXITEM_NUMBER;
		m_Container.Init(&containInit);
		
		for(int i=0;i<MAX_BOXITEM_NUMBER;i++)
		{
			_ITEM_INIT	itemInit(&m_ItemList[i]);
			m_Container.GetItem(i)->Init(&itemInit);
		}

__LEAVE_FUNCTION
}

Obj_ItemBox::~Obj_ItemBox()
{

}

BOOL Obj_ItemBox::Init( const _OBJ_INIT *pInit )
{
__ENTER_FUNCTION

	CleanUp();

	BOOL bResult = Obj_Static::Init( pInit );


	if ( !bResult )
		return FALSE;

	

	_OBJ_ITEMBOX_INIT *pItemBoxInit = (_OBJ_ITEMBOX_INIT*)pInit;
	if ( pItemBoxInit == NULL )
		return FALSE;

	m_CreateTime	=	pItemBoxInit->m_uCreateTime;
	m_RecycleTime	=	pItemBoxInit->m_uRecycleTime;
	m_ItemBoxType	=	pItemBoxInit->m_ItemBoxType;
	if(pItemBoxInit->m_bRecycle)
	{
		m_RecycleTimer.BeginTimer( m_RecycleTime, m_CreateTime );
	}
	else
	{
		m_RecycleTimer.CleanUp();
	}

__LEAVE_FUNCTION

	return TRUE;
}

BOOL	Obj_ItemBox::HeartBeat(UINT uTime/* =0  */)
{
	__ENTER_FUNCTION

	BOOL bResult = Obj_Static::HeartBeat( uTime );
	if ( !bResult )
		return FALSE;
	
	// temp code {
	UpdateZone();
	// }

	if( m_RecycleTimer.CountingTimer(uTime) )
	{
		//回收操作
		//
		Recycle();
		return TRUE;
	}
	
	if(m_LifeTimer.CountingTimer(uTime))
	{
		INT ItemBoxType		=	 GetType();
		
		_GROW_POINT_INFO*	pGET = g_GrowPointInfoTbl.Get(ItemBoxType);

			Assert(pGET);

		if(pGET->m_ScriptID>0)
		{
			_MY_TRY
			{
				if(getScene() && getScene()->GetGrowPointManager()->CallScriptRecycleFunc(pGET->m_ScriptID,GetOwner(),GetID(),getScene()->SceneID()))
				{	
					//可以Recycle
					Recycle();
				}
			}
			_MY_CATCH
			{
				//可以Recycle
				SaveCodeLog( ) ;
				Recycle();
			}
		}
		else
            Recycle();
	}
	
	return	TRUE;

	__LEAVE_FUNCTION

	return	FALSE;

}

Packet *Obj_ItemBox::CreateNewObjPacket( VOID )
{
__ENTER_FUNCTION

	if ( getScene() != NULL )
	{
		GCNewItemBox *pPacket = (GCNewItemBox*)(getScene()->m_pPacket_NewItemBox);
		pPacket->setObjType(GetType());
		pPacket->setObjID(GetID());
		pPacket->setOwner(GetOwner());
		pPacket->setWorldPos(*(getWorldPos()));
		pPacket->setMonsterID(GetDropMonsterID());
		return pPacket;
	}
	else
	{
		Assert( getScene() != NULL && "Obj_ItemBox::CreateNewObjPacket" );
		return NULL;
	}

__LEAVE_FUNCTION

	return NULL;
}

VOID Obj_ItemBox::DestroyNewObjPacket( Packet *pPacket )
{
}


BOOL	Obj_ItemBox::CanPickBox(GUID_t	PickerID,ObjID_t HumanID)
{
__ENTER_FUNCTION

	if(m_OwnerId==INVALID_ID)
		return TRUE;

	Obj_Human*	pHuman = getScene()->GetHumanManager()->GetHuman(HumanID);
	Assert(pHuman);

	if(GetType()==ITYPE_DROPBOX)
	{
		return PickerID==m_OwnerId;
		
	}
	else
	{
		if(PickerID==m_OwnerId)
			return TRUE;
		else
		{
			return g_pTimeManager->CurrentTime()>(UINT)m_FinalPickTime;
		}

	}

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL				Obj_ItemBox::IsCanViewMe(const Obj *pObj )
{
__ENTER_FUNCTION

	if(!pObj)
		return FALSE;

	if(GetType()==ITYPE_DROPBOX)
	{
		if(pObj->GetObjType() == OBJ_TYPE_HUMAN)
		{
			Obj_Human* pHuman = (Obj_Human*)pObj;
			if(!pHuman)
				return FALSE;

			return	m_OwnerId == pHuman->GetGUID()||m_OwnerId==INVALID_ID;
		}
	}

	return TRUE;

__LEAVE_FUNCTION

	return FALSE ;
}



VOID Obj_ItemBox::EnablePickOwnerTime()
{
__ENTER_FUNCTION

	m_FinalPickTime	=	g_pTimeManager->CurrentTime()+m_PickOwnerTime;

__LEAVE_FUNCTION
}

VOID Obj_ItemBox::SetPickOwnerTime(UINT uPickTime)
{
	m_PickOwnerTime	=	uPickTime;
}


VOID	Obj_ItemBox::SetMaxGrowTime(UINT uGrowTime)
{
__ENTER_FUNCTION

	m_MaxGrowTime	=	uGrowTime;

	m_LifeTimer.BeginTimer(m_MaxGrowTime,g_pTimeManager->CurrentTime());

__LEAVE_FUNCTION
}


VOID	Obj_ItemBox::Recycle()
{
	__ENTER_FUNCTION
	//回收日志
	ITEM_LOG_PARAM	ItemLogParam;
	ItemLogParam.OpType	=	ITEM_BOX_RECYCLE;
	ItemLogParam.SceneID	=	getScene()->SceneID();
	ItemLogParam.XPos		=	getWorldPos()->m_fX;
	ItemLogParam.ZPos		=	getWorldPos()->m_fZ;
	for(INT i=0;i<MAX_BOXITEM_NUMBER;i++)
	{
		if(m_ItemList[i].IsNullType() == FALSE)
		{
			ItemLogParam.ItemGuid	=	m_ItemList[i].m_ItemGUID;
			ItemLogParam.ItemType	=	m_ItemList[i].m_ItemIndex;
			
			SaveItemLog(&ItemLogParam);
		}
	}


	if(m_ItemBoxType != ITYPE_DROPBOX) //非DropBox 都应该由生长点管理器释放
	{
			BOOL bRet =
				getScene()->GetGrowPointManager()->DecGrowPointTypeCount(m_ItemBoxType,getWorldPos()->m_fX,getWorldPos()->m_fZ);

			Assert(bRet);
	}
	SetActiveFlag(FALSE);
	getScene()->DeleteObject(this);
	
	
	__LEAVE_FUNCTION
}


VOID	Obj_ItemBox::CleanUp()
{
__ENTER_FUNCTION

	m_ItemCount			=	0;
	m_CreateTime		=	0;
	m_RecycleTime		=	0;
	m_MaxGrowTime		=	0;
	m_ItemBoxType		=	-1;
	m_RecycleTimes		=	0;
	m_OpenFlag			=	FALSE;

	memset(m_ItemList,0,sizeof(_ITEM)*MAX_BOXITEM_NUMBER);
	for(int i =0;i<MAX_BOXITEM_NUMBER;i++)
	{
		m_IPCList[i].CleanUp();
	}

	m_LifeTimer.CleanUp();
	
	m_PickOwnerTime		=	0;

	m_FinalPickTime		=	0;
	m_OwnerId			=	INVALID_ID;
	m_OwnerTeam			=	INVALID_ID;
	m_MonsterID			=   INVALID_ID;

__LEAVE_FUNCTION
}

_ITEM*	Obj_ItemBox::GetItem(BYTE itemIndex)
{
	__ENTER_FUNCTION
	
	return &m_ItemList[itemIndex];

	__LEAVE_FUNCTION

	return NULL ;
}

VOID	Obj_ItemBox::EraseItem(BYTE itemIndex)
{
	__ENTER_FUNCTION
		
		Assert(itemIndex<=m_ItemCount);
		memcpy(m_ItemList+itemIndex,m_ItemList+m_ItemCount-1,sizeof(_ITEM));
		memset(m_ItemList+m_ItemCount-1,0,sizeof(_ITEM));
		m_ItemCount--;

	__LEAVE_FUNCTION
}



VOID	Obj_ItemBox::SetItemCount(BYTE itemCount)
{
	__ENTER_FUNCTION

		Assert(itemCount<=MAX_BOXITEM_NUMBER);

		m_ItemCount = itemCount;

	__LEAVE_FUNCTION
}

BYTE	Obj_ItemBox::GetItemCount()
{
		return m_ItemCount;
}


VOID	Obj_ItemBox::SetItemData(_ITEM* pData)
{
	__ENTER_FUNCTION
		Assert(m_ItemCount>0&&m_ItemCount<=MAX_BOXITEM_NUMBER);
		memcpy(m_ItemList,pData,sizeof(_ITEM)*m_ItemCount);
	__LEAVE_FUNCTION
}

const	_ITEM*	Obj_ItemBox::GetItemData()
{
	__ENTER_FUNCTION

		return	m_ItemList;
	__LEAVE_FUNCTION
}

INT	Obj_ItemBox::AddItem(ItemBoxContaner* pContain,INT nDestIndex)
{
	__ENTER_FUNCTION

		Assert(pContain);
		
		BOOL	bNewPos	=	FALSE;
		INT nIndex = g_ItemOperator.CopyItem(pContain,nDestIndex,bNewPos,GetContainer());
		
		if(bNewPos)	m_ItemCount++;

		return nIndex;
		
	__LEAVE_FUNCTION

		return INVALID_INDEX;
}

BOOL Obj_ItemBox::CreateItem(ITEM_LOG_PARAM* pLogParam,UINT uItemType,UINT uQuality)
{
	__ENTER_FUNCTION
		
		Assert(pLogParam);

		BOOL	bNewPos	=	FALSE;
		UINT	uContainerPos;
		BOOL	bCreate = g_ItemOperator.CreateItem(pLogParam,
			uItemType,uQuality,GetContainer(),bNewPos,uContainerPos,0);
		
		if(bNewPos)
		{
			m_ItemCount++;
		}

		return bCreate;

	__LEAVE_FUNCTION

		return FALSE;
}


ScriptID_t	Obj_ItemBox::GetScriptID() const
{
	__ENTER_FUNCTION

	if(m_ItemBoxType == ITYPE_DROPBOX)
	{
		return INVALID_ID;
	}

	_GROW_POINT_INFO*	pGET = g_GrowPointInfoTbl.Get(m_ItemBoxType);
	Assert(pGET);
	if(pGET->m_ScriptID>0)
	{
		return pGET->m_ScriptID;
	}

	return INVALID_ID;
		
	__LEAVE_FUNCTION

	return INVALID_ID;
}
