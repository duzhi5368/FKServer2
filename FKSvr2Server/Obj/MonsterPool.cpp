#include "stdafx.h"

#include "MonsterPool.h"
//#include "Config.h"


MonsterPool* g_pMonsterPool=NULL ;
//
//MonsterPool::MonsterPool( )
//{
//__ENTER_FUNCTION
//
//	for( INT i=0; i<MAX_MONSTER_COUNT; i++ )
//	{
//		m_pMonster[i] = NULL ;
//		m_Active[i] = FALSE ;
//	}
//	m_Count = 0 ;
//	m_Position = 0 ;
//
//__LEAVE_FUNCTION
//}
//
//MonsterPool::~MonsterPool( )
//{
//__ENTER_FUNCTION
//
//	CleanUp( ) ;
//
//__LEAVE_FUNCTION
//}
//
//VOID MonsterPool::CleanUp( )
//{
//__ENTER_FUNCTION
//
//	for( INT i=0; i<MAX_MONSTER_COUNT; i++ )
//	{
//		SAFE_DELETE(m_pMonster[i]) ;
//		m_Active[i] = FALSE ;
//	}
//	m_Count = 0 ;
//	m_Position = 0 ;
//
//__LEAVE_FUNCTION
//}
//
//BOOL MonsterPool::Init( )
//{
//__ENTER_FUNCTION
//
//	Assert( g_Config.m_ConfigInfo.m_MaxMonster<=MAX_MONSTER_COUNT ) ;
//	for( INT i=0; i<g_Config.m_ConfigInfo.m_MaxMonster; i++ )
//	{
//		Assert( m_pMonster[i]==NULL ) ;
//
//		m_pMonster[i] = new Obj_Monster ;
//		if( m_pMonster[i]==NULL )
//		{
//			Assert( FALSE ) ;
//			break ;
//		}
//	}
//	m_Count = i ;
//	m_Position = 0 ;
//
//	return TRUE ;
//
//__LEAVE_FUNCTION
//
//	return FALSE ;
//}
//
//Obj_Monster* MonsterPool::NewMonster( )
//{
//__ENTER_FUNCTION
//
//	m_Lock.Lock() ;
//
//	for( INT i=0; i<m_Count; i++ )
//	{
//		if( m_Active[m_Position] )
//		{
//			m_Position ++ ;
//			if( m_Position>=m_Count )
//			{
//				m_Position = 0 ;
//			}
//
//			continue ;
//		}
//
//		Obj_Monster* pMonster = m_pMonster[m_Position] ;
//		m_Active[m_Position] = TRUE ;
//
//		m_Lock.Unlock() ;
//		return pMonster ;
//	}
//
//__LEAVE_FUNCTION
//
//	m_Lock.Unlock() ;
//	return NULL ;
//}
//

