

#ifndef __IDTABLE_H__
#define __IDTABLE_H__

#include "Type.h"


struct _TABLEITEM
{
	UINT	m_ID ;
	VOID*	m_pPtr ;
	UINT	m_Status ;
};

class IDTable
{
public :
	IDTable( ) ;
	~IDTable( ) ;

	//初始化表
	VOID		InitTable( UINT MaxItem ) ;
	//增加一个表项
	BOOL		Add( UINT id, VOID* pPtr ) ;
	//读取信息
	VOID*		Get( UINT id ) ;
	//删除表项
	VOID		Remove( UINT id ) ;
	//清除所有数据
	VOID		CleanUp( ) ;

protected :
	enum {
		IDTS_EMPTY = 0 ,
		IDTS_SET = 1 ,
		IDTS_USE = 2 ,
	};

	UINT		toIndex( UINT id )
	{
		return (UINT)((id&0xffff)+(id>>6))%m_Count ;
	};

private :

	_TABLEITEM*		m_pTable ;
	UINT			m_Count ;


};

#endif
