/********************************************************************
	创建日期:	2005年11月1日
	创建时间:	9:22
	文件名称:	ItemBoxPool.h
	文件路径:	d:\Prj\Server\Server\Item\ItemBoxPool.h
	
	文件功能： ?
	修改纪录：
	
*********************************************************************/



#ifndef		_ITEMBOX_POOL_H_
#define		_ITEMBOX_POOL_H_
#include	"Type.h"
#include	"ItemTypes.h"
#define		ITEM_POOL_INVAILD	-1				//无效Obj_ItemBox编号


class Obj_ItemBox;



 /*
  *		Obj_ItemBox	池类
  */
class ItemBoxPool
{
	//Obj_ItemBox数组
	Obj_ItemBox*		m_pItemBox;
	//空闲Itembox池Id
	INT*			m_pFreeItemID;
	//使用的Obj_ItemBox池Id数组
	INT*			m_pUseItemID;
	//空闲位置标记
	INT				m_nFreePosition;
	//共享锁
	MyLock			m_Lock;

	UINT			m_ItemBoxMaxCount;

public:
	ItemBoxPool();
	~ItemBoxPool();
	/*
	 *	完成ItemBoxPool 初始化,在Server->Init中执行
	 */
	BOOL			Init(UINT ItemBoxMaxCount = MAX_ITEM_BOX_POOL);
	
	/*
	 *	产生一个新的Obj_ItemBox
	 *
	 *	
	 */
	
	Obj_ItemBox*		NewItemBox();
	
	/*	删除一个Itembox
	 *	
	 *	
	 *
	 */
	//根据位置删除
	VOID			DelItemBox(UINT iItemPos);
	//根据指针删除
	VOID			DeleteObj(Obj_ItemBox*	pItem);

	UINT			GetItemBoxMaxCount() 
	{
		return m_ItemBoxMaxCount;
	};
};

extern ItemBoxPool* g_pItemBoxPool;


#endif
