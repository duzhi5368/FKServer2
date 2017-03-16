

#ifndef __OBJLIST_H__
#define __OBJLIST_H__

#include "Type.h"


class Obj;

struct _OBJ_LIST_NODE
{
	Obj* m_pNode ;
	_OBJ_LIST_NODE* m_pNext ;
	_OBJ_LIST_NODE* m_pPrev ;

	_OBJ_LIST_NODE( )
	{
		m_pNode = NULL ;
		m_pNext = NULL ;
		m_pPrev = NULL ;
	}

	_OBJ_LIST_NODE( Obj* pNode )
	{
		m_pNode = pNode ;
		m_pNext = NULL ;
		m_pPrev = NULL ;
	}
};



class ObjList
{
public:
	_OBJ_LIST_NODE m_Head;
	_OBJ_LIST_NODE m_Tail;
	INT m_nSize;

public:
	ObjList()
	{
		m_nSize = 0;
			  	
		m_Head.m_pNext = &m_Tail;
		m_Head.m_pPrev = &m_Head;	
		m_Tail.m_pNext = &m_Tail;
		m_Tail.m_pPrev = &m_Head;
	}

	virtual ~ObjList()
	{
	}

	VOID CleanUp( )
	{
		m_nSize = 0 ;

		m_Head.m_pNext = &m_Tail;
		m_Head.m_pPrev = &m_Head;	
		m_Tail.m_pNext = &m_Tail;
		m_Tail.m_pPrev = &m_Head;
	}
	
	BOOL AddNode(_OBJ_LIST_NODE* pNode)
	{
		__ENTER_FUNCTION

		Assert( pNode->m_pPrev==NULL ) ;
		Assert( pNode->m_pNext==NULL ) ;

		pNode->m_pNext = &m_Tail;
		pNode->m_pPrev = m_Tail.m_pPrev;
		m_Tail.m_pPrev->m_pNext = pNode;
		m_Tail.m_pPrev = pNode;

		m_nSize++;
		
		__LEAVE_FUNCTION

		return TRUE;
	}

	BOOL DeleteNode(_OBJ_LIST_NODE* pNode)
	{
		__ENTER_FUNCTION

		Assert( pNode->m_pPrev!=NULL ) ;
		Assert( pNode->m_pNext!=NULL ) ;

		_OBJ_LIST_NODE* pPoint = m_Head.m_pNext;
		while(pPoint != &m_Tail)
		{
			if(pPoint == pNode)
			{
				pPoint->m_pPrev->m_pNext = pPoint->m_pNext;
				pPoint->m_pNext->m_pPrev = pPoint->m_pPrev;
				pPoint->m_pNext = NULL;
				pPoint->m_pPrev = NULL;

				m_nSize--;
				return TRUE;
			}
			else
				pPoint = pPoint->m_pNext;
		}

		Assert(FALSE) ;

		__LEAVE_FUNCTION

		return FALSE;
	}

	INT GetSize()
	{
		return m_nSize;
	}
};



#endif
