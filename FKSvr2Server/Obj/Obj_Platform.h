// Obj_Platform.h

#ifndef __OBJ_PLATFORM_H__
#define __OBJ_PLATFORM_H__

#include "Obj_Static.h"

struct _OBJ_PLATFORM_INIT :	public _OBJ_STATIC_INIT
{
	INT					m_Class;			//操作台类型
	INT					m_Type;
	ScriptID_t			m_Script;			//脚本 ID

	_OBJ_PLATFORM_INIT( VOID )
	{
		m_Class		= 0;
		m_Type		= -1;
		m_Script	= INVALID_ID;
	}

	virtual VOID CleanUp( VOID )
	{
		m_Class		= 0;
		m_Type		= -1;
		m_Script	= INVALID_ID;
		_OBJ_STATIC_INIT::CleanUp();
	}
};

class Obj_Platform : public Obj_Static
{
public:
	Obj_Platform()		{ CleanUp(); }

	virtual VOID		CleanUp( );

	virtual ObjType		GetObjType( VOID ) const { return OBJ_TYPE_PLATFORM; }

	virtual BOOL		Init( const _OBJ_INIT *pInit );

	VOID				SetPlatformClass(INT platform)
	{
		m_PlatformClass = platform;
	}

	INT					GetPlatformClass( ) { return m_PlatformClass; }
	BYTE				GetPlatformType( ) { return m_type; }
	virtual VOID		SetScriptID( ScriptID_t idScript ){ m_Script = idScript; }
	virtual ScriptID_t	GetScriptID( VOID )const{ return m_Script; }

public :
	virtual Packet		*CreateNewObjPacket( VOID );
	virtual VOID		DestroyNewObjPacket( Packet *pPacket );

private:
	INT					m_PlatformClass;
	BYTE				m_type;				//操作台的具体样式（配置表中的编号）
	ScriptID_t			m_Script;
};

#endif // __OBJ_PLATFORM_H__
