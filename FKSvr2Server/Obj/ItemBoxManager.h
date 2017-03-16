/********************************************************************
	创建日期:	2005年11月1日
	创建时间:	9:30
	文件名称:	ItemBoxManager.h
	文件路径:	d:\Prj\Server\Server\Item\ItemBoxManager.h
	
	文件功能： 实现对Obj_ItemBox的管理
			   每个场景一个管理器
	修改纪录：
	
*********************************************************************/
#ifndef			_ITEMBOX_MANAGER_H_
#define			_ITEMBOX_MANAGER_H_
#include		"Type.h"

class Scene;
class Obj_ItemBox;
struct ItemBoxContaner;
/*
 *	ItemBox 管理器类
 */
class ItemBoxManager
{

public:
	ItemBoxManager();
	~ItemBoxManager();
public:

	VOID				Init();
	//清除数据信息
	VOID				CleanUp( ) ;
	//逻辑接口
	virtual BOOL		HeartBeat( UINT uTime=0 ) ;
	
	//添加ItemBox 到管理器
	BOOL				Add(Obj_ItemBox*	pItemBox);

	//移除ItemBox 到管理器
	BOOL				Remove(ObjID_t ObjID);

	//产生ItemBox
	Obj_ItemBox*		GenItemBox();
	//回收ItemBox
	VOID				RecycleItemBox(ObjID_t ObjID);

	//设置ItemBoxManager 所属场景
	VOID				SetScene( Scene* pScene )
	{Assert( pScene ) ;
	m_pScene = pScene ;} ;
	
	//获得ItemBox 所属场景
	Scene*				GetScene(){ return m_pScene ; } ;

	/*
	 *	改变到指定大小	
	 */
	BOOL				Resize(UINT iSize);
	
	Obj_ItemBox*		GetItemBox(ObjID_t ObjID);

	BOOL				RemoveAllItemBox( VOID );
public:



	//计算部分方法
	/*
	 *	从怪物产生掉落的物品容器
	 *
	 *	UINT	iMonsterLevel			怪物级别
	 *	UINT	iKillerLevel			杀怪角色级别
	 *	INT		iMonsterType			怪物类型
	 *
	 */
	ItemBoxContaner			CaculateItemDropFromMonster( UINT iMonsterLevel,
														 UINT iKillerLevel,
														 INT  iMonsterType,
														 FLOAT fWallow);

	/*
	 *	
	 */
	Obj_ItemBox*			CreateMonsterDropItembox(WORLD_POS* pPos);


	/*
	 *	生长点ItemBox 的创建
	 */
	Obj_ItemBox*			CreateGrowPointItemBox(INT	IBType);
	
	
private:
	/*
	 *	逻辑时间计数
	 */
	CMyTimer			m_LogicTimer;
private:
	// ItemBox id 数组
	ObjID_t*			m_pItemBoxObjID ;
	// ItemBoxManager 最大管理大小
	UINT				m_TotalSize ;
	// 当前管理的ItemBox数量
	UINT				m_Count ;
	// 场景指针
	Scene*				m_pScene;


};	


#endif

