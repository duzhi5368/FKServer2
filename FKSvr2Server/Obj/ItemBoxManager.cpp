#include "stdafx.h"
#include 		"ItemBoxManager.h"
#include 		"WorldManager.h"
#include 		"ServerManager.h"
#include 		"ItemBoxPool.h"
#include 		"Obj_ItemBox.h"
#include 		"Scene.h"
#include		"GCDelObject.h"
#include		"ItemTable.h"
#include		"ItemRuler.h"
#include		"TimeManager.h"



//默认ItemBoxManager 管理的Obj_ItemBox 个数
#define			DEFAULT_ITEMBOX_MANAGER_SIZE			512 
//默认ItemBoxManager HeartBeat 间隔
#define			ITEMBOXMANAGER_LOGIC_INTERVAL			500


ItemBoxManager::ItemBoxManager()
{
__ENTER_FUNCTION

	m_TotalSize = DEFAULT_ITEMBOX_MANAGER_SIZE;

	m_Count		= 0;

	m_pItemBoxObjID = new ObjID_t[DEFAULT_ITEMBOX_MANAGER_SIZE];
	Assert( m_pItemBoxObjID ) ;

	memset(m_pItemBoxObjID,-1,sizeof(ObjID_t)*DEFAULT_ITEMBOX_MANAGER_SIZE);

__LEAVE_FUNCTION
}

ItemBoxManager::~ItemBoxManager()
{
__ENTER_FUNCTION

	m_TotalSize			=	0;
	m_Count				=	0;

	SAFE_DELETE_ARRAY(m_pItemBoxObjID);

__LEAVE_FUNCTION
}

VOID	ItemBoxManager::Init()
{
	__ENTER_FUNCTION
	
	m_TotalSize = DEFAULT_ITEMBOX_MANAGER_SIZE;
	m_Count		= 0;
	Assert( m_pItemBoxObjID ) ;
	memset(m_pItemBoxObjID,-1,sizeof(ObjID_t)*DEFAULT_ITEMBOX_MANAGER_SIZE);

	__LEAVE_FUNCTION
}

Obj_ItemBox*	ItemBoxManager::GenItemBox()
{
__ENTER_FUNCTION

	Obj_ItemBox*	pIB		=	g_pItemBoxPool->NewItemBox();

	pIB->CleanUp();


	return pIB;

__LEAVE_FUNCTION

	return NULL ;
}


Obj_ItemBox*	ItemBoxManager::GetItemBox(ObjID_t ObjID)
{
__ENTER_FUNCTION

	Obj_ItemBox*	pItemBox	=	static_cast<Obj_ItemBox*>(GetScene()->GetObjManager()->GetObj(ObjID)) ;
	Assert( pItemBox ) ;
	return pItemBox;

__LEAVE_FUNCTION

	return NULL ;
}

BOOL			ItemBoxManager::RemoveAllItemBox()
{
	INT iCount = m_Count;

	for(int i = 0;i<iCount;i++)
	{
		Obj_ItemBox* pItemBox = GetItemBox(m_pItemBoxObjID[0]);
		
		if(pItemBox)
		{
			pItemBox->Recycle();
		}
	}

	return TRUE;
}

VOID		ItemBoxManager::RecycleItemBox(ObjID_t ObjID)
{
__ENTER_FUNCTION

	Obj_ItemBox*	pItemBox	=	GetItemBox(ObjID) ;
	Assert( pItemBox ) ;

	//Remove(ObjID);
	
	pItemBox->SetActiveFlag( FALSE );
	pItemBox->CleanUp();

	GetScene()->DeleteObject( pItemBox );

__LEAVE_FUNCTION
}

BOOL	ItemBoxManager::Add(Obj_ItemBox* pItemBox)
{
	__ENTER_FUNCTION

	ObjID_t	objId = pItemBox->GetID();
	m_pItemBoxObjID[m_Count] = objId;
	pItemBox->SetItemBoxID(m_Count);

	m_Count ++ ;
	
	Assert(m_Count<=g_pItemBoxPool->GetItemBoxMaxCount());

	if( m_Count >= m_TotalSize )
	{
		
		BOOL ret = Resize( DEFAULT_ITEMBOX_MANAGER_SIZE ) ;
		if( !ret )
		{
			Assert( FALSE ) ;
			return FALSE ;
		}

		
	}
	return TRUE ;
	__LEAVE_FUNCTION
	return FALSE ;
}

BOOL	ItemBoxManager::Resize(UINT iSize)
{
	__ENTER_FUNCTION

		ObjID_t* pNew = new ObjID_t[m_TotalSize+iSize] ;
	if( !pNew )
	{
		Assert( pNew ) ;
		return FALSE ;
	}

	memcpy( pNew, m_pItemBoxObjID, sizeof(ObjID_t)*m_TotalSize ) ;
	m_TotalSize = m_TotalSize+iSize ;

	SAFE_DELETE_ARRAY( m_pItemBoxObjID ) ;

	m_pItemBoxObjID = pNew ;


	return TRUE ;

	__LEAVE_FUNCTION

		return FALSE ;
}

BOOL	ItemBoxManager::Remove(ObjID_t ObjID)
{	
	__ENTER_FUNCTION

	Obj_ItemBox*	pItemBox	=	GetItemBox(ObjID);
		
	Assert( pItemBox ) ;

	UINT index = (UINT)(pItemBox->GetItemBoxID()) ;
	Assert( index<m_Count ) ;

	Assert( m_Count > 0 ) ;
	Assert( m_pItemBoxObjID[index]==ObjID ) ;

	m_pItemBoxObjID[index] = m_pItemBoxObjID[m_Count-1] ;
	pItemBox->SetItemBoxID( INVALID_ID ) ;

	Obj_ItemBox* pNewItemBox = GetItemBox(m_pItemBoxObjID[index]);
		
	Assert( pNewItemBox ) ;
	pNewItemBox->SetItemBoxID( index ) ;
	m_Count -- ;
	Assert( m_Count>=0 ) ;
	return TRUE ;
	__LEAVE_FUNCTION
	return FALSE ;

}

BOOL	ItemBoxManager::HeartBeat(UINT uTime/* =0  */)
{

	__ENTER_FUNCTION

		if( !m_LogicTimer.IsSetTimer() )
		{
			m_LogicTimer.BeginTimer( ITEMBOXMANAGER_LOGIC_INTERVAL,uTime ) ;
			return TRUE ;
		}

		if( !m_LogicTimer.CountingTimer(uTime ) )
			return TRUE ;


		UINT nCount = m_Count;

		for( UINT i=0; i<nCount; i++ )
		{
			Obj_ItemBox* pItemBox = GetItemBox(m_pItemBoxObjID[i]);
				
			if( pItemBox==NULL )
				continue ;

			_MY_TRY
			{
				pItemBox->HeartBeat(uTime );
			}
			_MY_CATCH
			{
				SaveCodeLog( ) ;
			}
		}

		return TRUE ;

		__LEAVE_FUNCTION

		return FALSE ;
}


ItemBoxContaner	ItemBoxManager::CaculateItemDropFromMonster(  UINT iMonsterLevel,
															   UINT iKillerLevel,
															   INT iMonsterType,
															   FLOAT fWallow)
{
	ItemBoxContaner	IBContaner;
	__ENTER_FUNCTION

	MONSTER_DROPBOX_TB*	pDropBoxs = g_ItemTable.GetMonsterDropTB(iMonsterType);

	if(pDropBoxs)
	{
		ItemBoxRuler ibr;
		IBContaner.m_uDropType	=	pDropBoxs->m_DropType;
		ibr.CreateItemFromMonsterDrop(pDropBoxs->m_MonsterValue,
									  pDropBoxs->m_DropBoxs,
									  iKillerLevel,
									  iMonsterLevel,
									  1.0f,
									  IBContaner,
									  fWallow);	
		if(IBContaner.m_nCount>0)
		{
			for(INT i =0;i<IBContaner.m_nCount;i++)
			{

				ITEM_LOG_PARAM	ItemLogParam;
				ItemLogParam.OpType		= ITEM_CREATE_FROM_MONSTER;
				ItemLogParam.NpcType	=	iMonsterType;
				ItemLogParam.ItemType	=	IBContaner.m_Item[i].m_ItemIndex;
				BOOL bRet	= g_pItemManager->CreateItem( &ItemLogParam,
														  IBContaner.m_Item[i].m_ItemIndex,
														  IBContaner.m_Item[i],
														  IBContaner.m_nQuality[i]);
				if(!bRet)
				{
					CHAR ErrorMsg[255];
					
					sprintf(ErrorMsg,"掉落包中物品创建失败，请检查策划填写的掉落包内容!,\
						    MonsterType = %d,\
							m_ItemIndex = %d ",\
							iMonsterType,IBContaner.m_Item[i].m_ItemIndex);
					AssertEx(bRet,ErrorMsg); 
				}
				SaveItemLog(&ItemLogParam);
			}
		}
	}

	return IBContaner;
	__LEAVE_FUNCTION
	return IBContaner;
}


Obj_ItemBox*	ItemBoxManager::CreateMonsterDropItembox(WORLD_POS* pPos)
{
	__ENTER_FUNCTION
	
	Obj_ItemBox* pItemBox = (Obj_ItemBox*)(GetScene()->NewObject(Obj::OBJ_TYPE_ITEM_BOX));

	_OBJ_ITEMBOX_INIT	initParam;
	initParam.m_uCreateTime		= g_pTimeManager->CurrentTime();
	initParam.m_uRecycleTime	= g_Config.m_ConfigInfo.m_DropBoxRecycleTime;
	initParam.m_Pos	=	*pPos;
	initParam.m_ItemBoxType	=	ITYPE_DROPBOX;
	initParam.m_bRecycle	= TRUE;
	pItemBox->Init(&initParam);
	return pItemBox;

	__LEAVE_FUNCTION

	return NULL;
}

Obj_ItemBox*	ItemBoxManager::CreateGrowPointItemBox(INT IBType)
{
	__ENTER_FUNCTION

	Obj_ItemBox* pIB = GenItemBox();

	Assert(ITYPE_DROPBOX!=IBType);
	_OBJ_ITEMBOX_INIT	initParam;
	initParam.m_uCreateTime		= g_pTimeManager->CurrentTime();
	initParam.m_uRecycleTime	= 3600000000;
	initParam.m_ItemBoxType		= IBType;
	initParam.m_bRecycle		= FALSE;
	pIB->Init(&initParam);
	
	
	return pIB;

	__LEAVE_FUNCTION

	return NULL ;
}






