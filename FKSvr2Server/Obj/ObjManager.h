// ObjManage.h
//
// 作用：ObjManager类为处理ObjID_t和Obj指针的对应关系模块
//		对于已经在内存中的Obj对象实例，通过调用ObjManager
//		的AddObj接口后，将会赋予Obj对象实例一个ObjID_t数值
//		此后就可以从ObjManager中通过ObjID_t查询到Obj的实例
//		的指针。
//
//////////////////////////////////////////////////////////

#ifndef __OBJMANAGER_H__
#define __OBJMANAGER_H__

#include "Type.h"

enum ENUM_OBJ_ID_TYPE
{
	OBJ_ID_TYPE_INVALID	= -1,
	OBJ_ID_TYPE_NORMAL,
	OBJ_ID_TYPE_HUMAN,
	OBJ_ID_TYPE_NUMBERS
};

struct _OBJMAGAGER_INIT
{
	UINT		m_aInitCount[OBJ_ID_TYPE_NUMBERS];
	_OBJMAGAGER_INIT( VOID )
	{
		memset( m_aInitCount, 0, sizeof( m_aInitCount ) );
	}

	VOID Cleanup( VOID )
	{
		memset( m_aInitCount, 0, sizeof( m_aInitCount ) );
	}
};

class Obj;
class ObjManager
{
private:
	static ObjID_t		m_aidBegin[OBJ_ID_TYPE_NUMBERS];

public:
	ENUM_OBJ_ID_TYPE GetObjIDType( ObjID_t idObj )const
	{
		INT i;
		for ( i = OBJ_ID_TYPE_NUMBERS - 1; i >= 0; i-- )
		{
			if ( idObj >= m_aidBegin[i] )
			{
				return (ENUM_OBJ_ID_TYPE)(i);
			}
		}
		return OBJ_ID_TYPE_INVALID;
	}

public:
	ObjManager( VOID );
	~ObjManager( VOID );

	BOOL Init( const _OBJMAGAGER_INIT *pInit );
	VOID Term( VOID );

	BOOL AddObj( Obj *pObj, ENUM_OBJ_ID_TYPE eIDType = OBJ_ID_TYPE_NORMAL );
	BOOL RemoveObj( ObjID_t idObj );

	Obj *GetObj( ObjID_t idObj )
	{
		if( idObj == INVALID_ID )
			return NULL;

		ENUM_OBJ_ID_TYPE eIDType = GetObjIDType( idObj );
		if ( idObj > m_aidBegin[eIDType] + (ObjID_t)(m_aLength[eIDType]) )
		{
			Assert( idObj > m_aidBegin[eIDType] + (ObjID_t)(m_aLength[eIDType]) && "ObjManager::GetObj not find object" );
			return NULL;
		}
		return m_appObjs[eIDType][idObj - m_aidBegin[eIDType]];
	}

private:
	BOOL Resize( ENUM_OBJ_ID_TYPE eIDType, UINT uNewSize );

private:
	Obj				**m_appObjs[OBJ_ID_TYPE_NUMBERS];
	UINT			m_aCount[OBJ_ID_TYPE_NUMBERS];
	UINT			m_aPosition[OBJ_ID_TYPE_NUMBERS];
	UINT			m_aLength[OBJ_ID_TYPE_NUMBERS];
};

#endif	// __OBJMANAGER_H__
