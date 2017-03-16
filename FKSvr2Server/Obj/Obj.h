// Obj.h
// 
/////////////////////////////////////////////////////////////////////////

#ifndef __OBJ_H__
#define __OBJ_H__

#include "Type.h"
#include "Rand.h"
#include "GameUtil.h"

struct _CAMP_DATA;
struct _OBJ_INIT
{
	WORLD_POS		m_Pos;
	FLOAT			m_Dir;
	_OBJ_INIT( VOID )
	{
		m_Pos.CleanUp();
		m_Dir		= 0.f;
	}

	virtual VOID CleanUp( VOID )
	{
		m_Pos.CleanUp();
		m_Dir		= 0.f;
	}
};

// OBJLIST
//#define MAX_OBJ_LIST_SIZE 255

class Obj;
/*
struct OBJLIST
{
	Obj*		m_aObj[MAX_OBJ_LIST_SIZE];
	BYTE		m_Count;

	OBJLIST( )
	{
		m_Count = 0;
	}
};
*/
typedef struct _OBJLIST
{
	enum
	{
		MAX_OBJ_LIST_SIZE = 255,
	};
	Obj*		m_aObj[MAX_OBJ_LIST_SIZE];
	BYTE		m_Count;
	VOID CleanUp(VOID)
	{
		memset((VOID*)m_aObj, NULL, sizeof(m_aObj));
		m_Count = 0;
	}
	_OBJLIST( )
	{
		CleanUp();
	};
} OBJLIST;
typedef BitFlagSet_T<OBJLIST::MAX_OBJ_LIST_SIZE> HitFlagsForOBJLIST_T;

struct _OBJ_LIST_NODE;
class Scene;
class Packet;
class Obj
{
public:
	enum ObjType
	{
		OBJ_TYPE_INVALID,			// 无效
		OBJ_TYPE_HUMAN,				// 玩家
		OBJ_TYPE_MONSTER,			// 战斗的NPC与怪物
		OBJ_TYPE_PET,				// 宠物
		OBJ_TYPE_ITEM_BOX,			// 掉落包
		OBJ_TYPE_PLATFORM,			// 工作台
		OBJ_TYPE_SPECIAL,			// 特殊（如，陷阱）
		OBJ_TYPE_NUMBERS
	};

public:
	Obj( );
	virtual ~Obj( );

	virtual ObjType		GetObjType( VOID )const{ return OBJ_TYPE_INVALID; }

	virtual VOID		OnEnterScene(VOID);
	virtual VOID		OnLeaveScene(VOID);

	virtual VOID		OnRegisterToZone(VOID){}
	virtual VOID		OnUnregisterFromZone(VOID){}

	virtual VOID		CleanUp( );
	virtual BOOL		Init( const _OBJ_INIT *pInit );

	// 击活了的Obj所执行的逻辑
	virtual BOOL		HeartBeat( UINT uTime=0 );

	// 未被击活的Obj所执行的逻辑
	virtual BOOL		HeartBeat_OutZone( UINT uTime=0 );

public:
	ObjID_t				GetID( )const{ return m_ObjID; }
	VOID				SetID( ObjID_t id ){ m_ObjID = id; }
	virtual UINT		GetUniqueID(VOID) const;
	
	// 在ObjPool中的位置，用以ObjPool的优化
	VOID				SetPoolID( UINT uID ){ m_uPoolID =uID; }
	UINT				GetPoolID( VOID )const{ return m_uPoolID; }

	// 在ObjSingleManager中的位置，用以ObjSingleManager的优化
	VOID				SetSingleMgrIndex( UINT uIndex ){ m_uSingleMgrIndex =uIndex; }
	UINT				GetSingleMgrIndex( VOID )const{ return m_uSingleMgrIndex; }

	//两次调用HeartBeat间的时间差(单位：毫秒，整数)
	UINT				GetLogicTime( )const{ return (m_uNowTime-m_uLastTime); }
	UINT				LastTime( )const{ return m_uLastTime; }
	UINT				NowTime( )const{ return m_uNowTime; }
	UINT				GetCreateTime( )const{ return m_uCreateTime; }

private:
	VOID				UpdateTime(UINT uTime);

public:
	virtual VOID		OnKillObject( ObjID_t idObj ){}
	// 工具函数
	Obj* 				GetSpecificObjInSameSceneByID(ObjID_t nID);
	Obj* 				GetSpecificHumanInSameSceneByGUID(GUID_t nID);
public:
	_OBJ_LIST_NODE*		ObjNode(){ return m_pObjNode; }

	// pObj是否可以看得见我
	virtual BOOL		IsCanViewMe( const Obj *pObj ){ return TRUE; }
	virtual BOOL		IsPrevCanViewMe( const Obj *pObj ){ return IsCanViewMe(pObj); }

	BOOL				IsActiveObj( )const{ return (BOOL)m_bActive; }
	VOID				SetActiveFlag( BOOL bFlag );

	const WORLD_POS*	getWorldPos()const{ return &m_Pos; }
	VOID				setWorldPos( const WORLD_POS* pos ){ m_Pos = *pos; }
	virtual VOID		Teleport( const WORLD_POS* pos );

	VOID				setDir( FLOAT dir ){ m_Dir = dir; }
	FLOAT				getDir( )const{ return m_Dir; }

	VOID				setScene( Scene* pScene ){ m_pScene = pScene; }
	Scene*				getScene( ){ return m_pScene; }

	VOID				setZoneID( ZoneID_t zid ){ m_ZoneID = zid; }
	ZoneID_t			getZoneID( )const{ return m_ZoneID; }

	virtual VOID		SetScriptID( ScriptID_t idScript ){ }
	virtual ScriptID_t	GetScriptID( VOID )const{ return INVALID_ID; }

	BOOL				IsInValidRadius(FLOAT fX1, FLOAT fZ1, FLOAT fX2, FLOAT fZ2, FLOAT fRadius);
	BOOL				IsInValidRadius(const Obj *pOb, FLOAT fRadius);
	BOOL				IsInValidRadius(const WORLD_POS *pPos, FLOAT fRadius);

	virtual const _CAMP_DATA	*GetCampData(VOID){ return NULL; }

public:
	INT					GetLogicCount( VOID )const{ return m_nLogicCount; }
	VOID				AddLogicCount( VOID ){ m_nLogicCount++; }
protected:
	VOID				SetLogicCount( INT nLogicCount ){ m_nLogicCount = nLogicCount; }

public:
	virtual Packet		*CreateNewObjPacket( VOID ) = 0;
	virtual VOID		DestroyNewObjPacket( Packet *pPacket ) = 0;

	virtual Packet		*CreateDeleteObjPacket( VOID );
	virtual VOID		DestroyDeleteObjPacket( Packet *pPacket );


	BOOL				UpdateZone( VOID );

private:
	ObjID_t					m_ObjID;
	UINT					m_uPoolID;
	UINT					m_uSingleMgrIndex;
	_OBJ_LIST_NODE*			m_pObjNode;
	BYTE					m_bActive;

	WORLD_POS				m_Pos;				// 在场景中的精确位置
	FLOAT					m_Dir;				// 场景中的方向
	Scene*					m_pScene;			// 所在场景的指针
	ZoneID_t				m_ZoneID;			// 当前所在场景的Zone位置
	UINT					m_uLastTime;		// 上次逻辑运行完成后的时间
	UINT					m_uNowTime;			// 当前时间
	UINT					m_uCreateTime;		// obj的创建时间

	INT						m_nLogicCount;		// 逻辑的计数

/////////////////////////////////////////////////////////////////////////////////
//obj 公共属性接口
public :
	virtual const SceneID_t		__GetSceneID( ) const;//场景号 obj
	virtual Scene*				__GetScene( );//场景指针
	virtual VOID				__SetScene( Scene* scene );
	virtual const ZoneID_t		__GetZoneID( ) const;//区域号 obj
	virtual VOID				__SetZoneID( const ZoneID_t zoneid );
	virtual const ScriptID_t	__GetScriptID( ) const;//脚本号 obj
	virtual VOID				__SetScriptID( const ScriptID_t scriptid );
	virtual const WORLD_POS*	__GetWorldPos( ) const;//位置 obj
	virtual VOID				__SetWorldPos( const WORLD_POS* worldpos );
	virtual const FLOAT			__GetDir( ) const;//方向 obj
	virtual VOID				__SetDir( const FLOAT dir );
	virtual const ObjID_t		__GetID( ) const;//obj号 obj
	virtual VOID				__SetID( const ObjID_t id );
};

// 是否为有运动的OBJ
inline BOOL IsDynamicObj( Obj::ObjType eType )
{
	switch ( eType )
	{
	case Obj::OBJ_TYPE_HUMAN:
	case Obj::OBJ_TYPE_MONSTER:
	case Obj::OBJ_TYPE_PET:
	case Obj::OBJ_TYPE_SPECIAL:
		return TRUE;
	case Obj::OBJ_TYPE_ITEM_BOX:
	case Obj::OBJ_TYPE_PLATFORM:
	default:
		return FALSE;
	}
}

// 是否静止的OBJ
inline BOOL IsStaticObj( Obj::ObjType eType )
{
	switch ( eType )
	{
	case Obj::OBJ_TYPE_HUMAN:
	case Obj::OBJ_TYPE_MONSTER:
	case Obj::OBJ_TYPE_PET:
	case Obj::OBJ_TYPE_SPECIAL:
		return FALSE;
	case Obj::OBJ_TYPE_ITEM_BOX:
	case Obj::OBJ_TYPE_PLATFORM:
	default:
		return TRUE;
	}
}

// 是否为角色
inline BOOL IsCharacterObj( Obj::ObjType eType )
{
	switch ( eType )
	{
	case Obj::OBJ_TYPE_HUMAN:
	case Obj::OBJ_TYPE_MONSTER:
	case Obj::OBJ_TYPE_PET:
		return TRUE;
	case Obj::OBJ_TYPE_SPECIAL:
	case Obj::OBJ_TYPE_ITEM_BOX:
	case Obj::OBJ_TYPE_PLATFORM:
	default:
		return FALSE;
	}
}

// 是否为特殊对象
inline BOOL IsSpecialObj( Obj::ObjType eType )
{
	switch ( eType )
	{
	case Obj::OBJ_TYPE_SPECIAL:
		return TRUE;
	case Obj::OBJ_TYPE_HUMAN:
	case Obj::OBJ_TYPE_MONSTER:
	case Obj::OBJ_TYPE_PET:
	case Obj::OBJ_TYPE_ITEM_BOX:
	case Obj::OBJ_TYPE_PLATFORM:
	default:
		return FALSE;
	}
}

// 是否为玩家
inline BOOL IsHumanObj( Obj::ObjType eType )
{
	switch ( eType )
	{
	case Obj::OBJ_TYPE_HUMAN:
		return TRUE;
	case Obj::OBJ_TYPE_SPECIAL:
	case Obj::OBJ_TYPE_MONSTER:
	case Obj::OBJ_TYPE_PET:
	case Obj::OBJ_TYPE_ITEM_BOX:
	case Obj::OBJ_TYPE_PLATFORM:
	default:
		return FALSE;
	}
}

// 是否为怪物
inline BOOL IsMonsterObj( Obj::ObjType eType )
{
	switch ( eType )
	{
	case Obj::OBJ_TYPE_MONSTER:
		return TRUE;
	case Obj::OBJ_TYPE_SPECIAL:
	case Obj::OBJ_TYPE_HUMAN:
	case Obj::OBJ_TYPE_PET:
	case Obj::OBJ_TYPE_ITEM_BOX:
	case Obj::OBJ_TYPE_PLATFORM:
	default:
		return FALSE;
	}
}

#endif	// __OBJ_H__
