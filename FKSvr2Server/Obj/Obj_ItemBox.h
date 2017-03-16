// Obj_ItemBox.h
//
///////////////////////////////////////////////////////

#ifndef _OBJ_ITEM_BOX_H_
#define _OBJ_ITEM_BOX_H_

#include "Obj_Static.h"
#include "ItemContainer.h"

struct ITEM_LOG_PARAM;

struct _OBJ_ITEMBOX_INIT : public _OBJ_STATIC_INIT
{

	UINT		m_uCreateTime;
	UINT		m_uRecycleTime;
	BOOL		m_bRecycle;
	INT			m_ItemBoxType;

	_OBJ_ITEMBOX_INIT( VOID )
	{
		CleanUp();
	}

	virtual VOID CleanUp( VOID )
	{
		_OBJ_STATIC_INIT::CleanUp();
		m_uCreateTime	= 0;
		m_uRecycleTime	= 0;
		m_ItemBoxType	= 0;
		m_bRecycle		= TRUE;
	}
};

class Scene;


class Obj_ItemBox : public Obj_Static
{
private:
	Obj_ItemBox();
	~Obj_ItemBox();
public:

	friend class ItemBoxPool;
public:

	virtual ObjType		GetObjType( VOID )const{ return OBJ_TYPE_ITEM_BOX; }

	virtual VOID		CleanUp( ) ;
	virtual BOOL		Init( const _OBJ_INIT *pInit );		//初始化Obj_ItemBox的生存周期

	virtual BOOL		HeartBeat( UINT uTime=0 ) ;

public:
	virtual Packet		*CreateNewObjPacket( VOID );
	virtual VOID		DestroyNewObjPacket( Packet *pPacket );

public:
	VOID				Recycle();
	UINT				GetPoolPos(){return m_nPoolPos;};	//在ItemBoxPool 中的位置


	_ITEM*				GetItem(BYTE	itemIndex);			//获得itemIndex 位置物品数据，可能为非法
	VOID				EraseItem(BYTE itemIndex);			//删除itemIndex 位置数据
	VOID				SetItemCount(BYTE	itemCount);		//Obj_ItemBox的实际物品个数
	BYTE				GetItemCount();						//获取实际物品个数	
	VOID				SetItemData(_ITEM*	pData);			//设置物品数据
	const	_ITEM*		GetItemData();						//获取物品数据

	INT					AddItem(ItemBoxContaner* pContain,INT nDestIndex);
	BOOL				CreateItem(ITEM_LOG_PARAM* pLogParam,UINT uItemType,UINT uQuality);
	
	inline	VOID		SetItemBoxID( ObjID_t id );
	inline ObjID_t		GetItemBoxID( );
	
	inline GUID_t		GetOwner();										//获得所有者
	inline VOID			SetOwner(GUID_t id);							//设置所有者
	inline VOID			SetDropMonsterID(ObjID_t nID)
	{
		m_MonsterID = nID;
	}

	ObjID_t				GetDropMonsterID()
	{
		return m_MonsterID;
	}

	inline	INT			GetType()	const;
	inline VOID			SetType(INT	Type);
	inline BOOL			GetOpenFlag();
	inline VOID			SetOpenFlag(BOOL bFlag);
	inline	INT			GetRecycleTimes();
	inline VOID			SetRecycleTimes(INT RecycleTimes);
	VOID				SetMaxGrowTime(UINT	uGrowTime);
	inline UINT			GetMaxGrowTime();
	BOOL				CanPickBox(GUID_t	PickerID,ObjID_t HumanID);
	virtual  BOOL		IsCanViewMe( const Obj *pObj );
	VOID				EnablePickOwnerTime();
	VOID				SetPickOwnerTime(UINT	uPickTime);


	inline ItemContainer*		GetContainer();


	virtual ScriptID_t			GetScriptID()	const;

	
private:
	inline VOID			SetPoolPos(UINT	iPos);
private:

	UINT				m_nPoolPos;							//在Pool 中位置
	GUID_t				m_OwnerId;							//所有者Id
	ObjID_t				m_MonsterID;						//从掉落怪物的ID
	TeamID_t			m_OwnerTeam;						//所有Team
	ObjID_t				m_ItemBoxId;						//Obj_ItemBox 的ID 由ItemBoxManager 统一管理
	BYTE				m_ItemCount;						//Obj_ItemBox 包含的物品个数
	_ITEM				m_ItemList[MAX_BOXITEM_NUMBER];		//Obj_ItemBox 中物品数据
	IPC					m_IPCList[MAX_BOXITEM_NUMBER];		//Obj_ItemBox 中物品拾取规则数据
	INT					m_ItemBoxType;						//Obj_ItemBox 类型
	INT					m_RecycleTimes;						//回收次数
private:
	BOOL				m_OpenFlag;							//Obj_ItemBox是否已经打开
	INT					m_MaxGrowTime;						//最大在场景中停留时间														
	CMyTimer			m_LifeTimer;						//状态计数器
	INT					m_PickOwnerTime;					//主人拾取保护时间长度
	INT					m_FinalPickTime;					//主人拾取最后时间
private:

	CMyTimer			m_RecycleTimer ;					//回收计时器
	UINT				m_CreateTime;						//创建时间
	UINT				m_RecycleTime;						//回收时间

private:
	ItemContainer		m_Container;


};

#include	"Obj_ItemBox.inl"

#endif