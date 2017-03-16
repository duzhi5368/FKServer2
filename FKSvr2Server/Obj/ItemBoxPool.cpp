#include "stdafx.h"
#include "ItemBoxPool.h"
#include "Obj_ItemBox.h"
#include "ItemTypes.h"
#include "Ini.h"






ItemBoxPool*	g_pItemBoxPool = NULL;


ItemBoxPool::ItemBoxPool():
m_nFreePosition(0)
{
	m_pItemBox = NULL ;
	m_pFreeItemID = NULL ;
	m_ItemBoxMaxCount = 0;
}


ItemBoxPool::~ItemBoxPool()
{
	SAFE_DELETE_ARRAY( m_pItemBox ) ;
	SAFE_DELETE_ARRAY( m_pFreeItemID ) ;
}

BOOL	ItemBoxPool::Init(UINT ItemBoxMaxCount)
{
	__ENTER_FUNCTION

	m_ItemBoxMaxCount = ItemBoxMaxCount;

	m_pItemBox	=	new	Obj_ItemBox[m_ItemBoxMaxCount];
	Assert(m_pItemBox);
	for(UINT i = 0;i<m_ItemBoxMaxCount;i++)	m_pItemBox[i].SetPoolPos(i);

	m_pFreeItemID	= new INT[m_ItemBoxMaxCount];
	Assert(m_pFreeItemID);

	for(UINT i = 0;i<m_ItemBoxMaxCount;i++)	m_pFreeItemID[i]	=	i;



	return TRUE;

	__LEAVE_FUNCTION

		return FALSE;
}



Obj_ItemBox*	ItemBoxPool::NewItemBox()
{
	__ENTER_FUNCTION

		m_Lock.Lock();

	Assert(m_nFreePosition<=(INT)m_ItemBoxMaxCount);
	Obj_ItemBox& ib = m_pItemBox[m_pFreeItemID[m_nFreePosition]];

	m_nFreePosition++;

	m_Lock.Unlock();

	return &ib;

	__LEAVE_FUNCTION

		m_Lock.Unlock();
		return NULL ;
}

VOID	ItemBoxPool::DelItemBox(UINT iItemPos)
{
	__ENTER_FUNCTION

		m_Lock.Lock();

	Assert(	iItemPos>= 0 && iItemPos < m_ItemBoxMaxCount);

	m_nFreePosition--;
	Assert(m_nFreePosition>=0);

	m_pFreeItemID[m_nFreePosition]	=	iItemPos;

	m_Lock.Unlock();
	return ;
	__LEAVE_FUNCTION
	m_Lock.Unlock();
}

VOID	ItemBoxPool::DeleteObj(Obj_ItemBox* pItem)
{
	__ENTER_FUNCTION

	m_Lock.Lock();
	UINT iPoolPos = pItem->GetPoolPos();
	Assert(	iPoolPos>= 0 && iPoolPos < m_ItemBoxMaxCount);
	m_nFreePosition--;
	Assert(m_nFreePosition>=0);
	m_pFreeItemID[m_nFreePosition]	= pItem->GetPoolPos();
	m_Lock.Unlock();
	return ;

	__LEAVE_FUNCTION
	m_Lock.Unlock();
}




