#include "stdafx.h"
// MonsterManager.cpp

#include "Ini.h"
#include "Log.h"
#include "GameTable.h"
#include "Scene.h"
#include "ObjManager.h"
#include "Obj_Monster.h"
#include "Obj_Pet.h"
#include "MonsterPool.h"

#include "PetManager.h"
#include "MonsterManager.h"
#include "SceneManager.h"

extern INT	g_Command_AlwaysLoadMonsterIni ;//每次都读取monster.ini文件


#define SECSIZE 64
#define DIR_STEP (__PI/18.f)

MonsterManager::MonsterManager( VOID )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

MonsterManager::~MonsterManager( VOID )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

Obj_Monster *MonsterManager::GetMonster( ObjID_t idObj )
{
__ENTER_FUNCTION

	Obj_Monster *pMonster = (Obj_Monster*)(GetScene()->GetObjManager()->GetObj( idObj ));
	if ( pMonster == NULL )
	{
		return NULL;
	}

	if ( pMonster->GetObjType() != Obj::OBJ_TYPE_MONSTER )
	{
		Assert( (pMonster->GetObjType() == Obj::OBJ_TYPE_MONSTER) && "MonsterManager::GetMonster" );
		return NULL;
	}
	return pMonster;

__LEAVE_FUNCTION

	return NULL ;
}

BOOL MonsterManager::LoadMonster( const CHAR *pszFileName )
{
__ENTER_FUNCTION

	Scene *pScene;
	_OBJ_MONSTER_INIT init;
	const MONSTER_EXT_ATTR *pExtAttr;
	CHAR szSection[SECSIZE], szReadText[SECSIZE], szDebugString[1024];

	INT i ;
	pScene = GetScene();

	//根据怪物配置ini文件名，查找数据源，如果没有数据则从配置文件里读出来
	MONSTER_FILE* pMonsterFile = g_pSceneManager->FindMonsterFile( pszFileName ) ;
	if( pMonsterFile==NULL || g_Command_AlwaysLoadMonsterIni==TRUE )
	{
		//找出一个空的怪物配置数据源
		pMonsterFile = g_pSceneManager->FindEmptyMonsterFile( ) ;

		Ini f(pszFileName) ;
		///////////////////////////////////////////////////////////////////////////
		//读取怪物调整数据
		///////////////////////////////////////////////////////////////////////////
		INT iOperateCount=0;
		BOOL bRet = f.ReadIntIfExist( "setting", "operatecount", iOperateCount ) ;
		if( bRet )
		{//有需要调整的数据存在
			/////////////////////////////////////////////////////
			//读取定义设置数据
			pMonsterFile->m_OperateCount = iOperateCount ;

			INT iDataCount=0 ;
			bRet = f.ReadIntIfExist( "setting", "datacount", iDataCount ) ;
			Assert(bRet) ;
			pMonsterFile->m_DataCount = iDataCount ;

			pMonsterFile->m_pOperate = new _OBJ_MONSTER_OPT[iOperateCount] ;
			if( pMonsterFile->m_pOperate==NULL )
			{
				Assert(FALSE) ;
				return FALSE ;
			}
			pMonsterFile->m_pData = new _OBJ_MONSTER_DATA[iDataCount] ;
			if( pMonsterFile->m_pData==NULL )
			{
				Assert(FALSE) ;
				return FALSE ;
			}

			//////////////////////////////////////////////////////
			//读取操作数据
			for( i=0; i<iOperateCount; i++ )
			{
				sprintf( szSection, "operate%d", i ) ;
				if( 0==f.ReadText(szSection,"selecttype",szReadText,sizeof(szReadText)))
				{
					Assert(FALSE) ;
					continue ;
				}
				pMonsterFile->m_pOperate[i].m_SelectType = (INT)atoi(szReadText) ;

				if( 0==f.ReadText(szSection,"selectvalue",szReadText,sizeof(szReadText)))
				{
					Assert(FALSE) ;
					continue ;
				}
				switch( pMonsterFile->m_pOperate[i].m_SelectType )
				{
				case MONSTER_VALUE_GUID:
						pMonsterFile->m_pOperate[i].m_Value.m_GUID = (GUID_t)atoi(szReadText) ;
					break ;
				case MONSTER_VALUE_TYPE:
						pMonsterFile->m_pOperate[i].m_Value.m_Type = (INT)atoi(szReadText) ;
					break ;
				case MONSTER_VALUE_NAME:
						strncpy( pMonsterFile->m_pOperate[i].m_Value.m_Name,szReadText, NPC_NAME_LEN ) ;
					break ;
				case MONSTER_VALUE_POS:
						pMonsterFile->m_pOperate[i].m_Value.m_Pos.m_fX = (FLOAT)atof(szReadText) ;
						pMonsterFile->m_pOperate[i].m_Value.m_Pos.m_fZ = (FLOAT)atof(szReadText) ;
					break ;
				case MONSTER_VALUE_SCRIPTID:
						pMonsterFile->m_pOperate[i].m_Value.m_ScriptID = (ScriptID_t)atoi(szReadText) ;
					break ;
				case MONSTER_VALUE_GROUPID:
						pMonsterFile->m_pOperate[i].m_Value.m_GroupID = (GroupID_t)atoi(szReadText) ;
					break ;
				case MONSTER_VALUE_TEAMID:
						pMonsterFile->m_pOperate[i].m_Value.m_TeamID = (TeamID_t)atoi(szReadText) ;
					break ;
				case MONSTER_VALUE_BASEAI:
						pMonsterFile->m_pOperate[i].m_Value.m_BaseAI = (INT)atoi(szReadText) ;
					break ;
				case MONSTER_VALUE_AIFILE:
						pMonsterFile->m_pOperate[i].m_Value.m_AIFile = (INT)atoi(szReadText) ;
					break ;
				case MONSTER_VALUE_PATROLID:
						pMonsterFile->m_pOperate[i].m_Value.m_PatrolID = (INT)atoi(szReadText) ;
					break ;
				default :
					{
						Assert(FALSE) ;
					}
					break ;
				};//end switch
				if( 0==f.ReadText(szSection,"data_def",szReadText,sizeof(szReadText)))
				{
					Assert(FALSE) ;
					continue ;
				}
				pMonsterFile->m_pOperate[i].m_DataDef = (INT)atoi(szReadText) ;

				if( 0==f.ReadText(szSection,"maxleft",szReadText,sizeof(szReadText)))
				{
					Assert(FALSE) ;
					continue ;
				}
				pMonsterFile->m_pOperate[i].m_MaxLeft = (INT)atoi(szReadText) ;
			}//end for

			///////////////////////////////////////////////////
			//读取数据预结构
			for( i=0; i<iDataCount; i++ )
			{
				sprintf( szSection, "data_def%d", i ) ;
				if( 0==f.ReadText(szSection,"datatype",szReadText,sizeof(szReadText)))
				{
					Assert(FALSE) ;
					continue ;
				}
				pMonsterFile->m_pData[i].m_DataType = (INT)atoi(szReadText) ;

				if( 0==f.ReadText(szSection,"count",szReadText,sizeof(szReadText)))
				{
					Assert(FALSE) ;
					continue ;
				}
				pMonsterFile->m_pData[i].m_DataCount = (INT)atoi(szReadText) ;
				pMonsterFile->m_pData[i].m_pDataValue = new MONSTER_ATTR_VALUE[pMonsterFile->m_pData[i].m_DataCount] ;
				if( pMonsterFile->m_pData[i].m_pDataValue==NULL )
				{
					Assert(FALSE) ;
					continue ;
				}
				
				for( INT j=0; j<pMonsterFile->m_pData[i].m_DataCount; j++ )
				{
					CHAR szValue[64] ;
					sprintf( szValue, "value%d", j ) ;
					if( 0==f.ReadText(szSection,szValue,szReadText,sizeof(szReadText)))
					{
						Assert(FALSE) ;
						continue ;
					}
					switch( pMonsterFile->m_pData[i].m_DataType )
					{
					case MONSTER_VALUE_GUID:
						pMonsterFile->m_pData[i].m_pDataValue[j].m_GUID = (GUID_t)atoi(szReadText) ;
						break ;
					case MONSTER_VALUE_TYPE:
							pMonsterFile->m_pData[i].m_pDataValue[j].m_Type = (INT)atoi(szReadText) ;
						break ;
					case MONSTER_VALUE_NAME:
							strncpy( pMonsterFile->m_pData[i].m_pDataValue[j].m_Name,szReadText, NPC_NAME_LEN ) ;
						break ;
					case MONSTER_VALUE_POS:
							pMonsterFile->m_pData[i].m_pDataValue[j].m_Pos.m_fX = (FLOAT)atof(szReadText) ;
							sprintf( szValue, "valueex%d", j ) ;
							if( 0==f.ReadText(szSection,szValue,szReadText,sizeof(szReadText)))
							{
								Assert(FALSE) ;
								break ;
							}
							pMonsterFile->m_pData[i].m_pDataValue[j].m_Pos.m_fZ = (FLOAT)atof(szReadText) ;
						break ;
					case MONSTER_VALUE_SCRIPTID:
							pMonsterFile->m_pData[i].m_pDataValue[j].m_ScriptID = (ScriptID_t)atoi(szReadText) ;
						break ;
					case MONSTER_VALUE_GRAND:
					case MONSTER_VALUE_GROUPID:
							pMonsterFile->m_pData[i].m_pDataValue[j].m_GroupID = (GroupID_t)atoi(szReadText) ;
						break ;
					case MONSTER_VALUE_TRAND:
					case MONSTER_VALUE_TEAMID:
							pMonsterFile->m_pData[i].m_pDataValue[j].m_TeamID = (TeamID_t)atoi(szReadText) ;
						break ;
					case MONSTER_VALUE_BASEAI:
							pMonsterFile->m_pData[i].m_pDataValue[j].m_BaseAI = (INT)atoi(szReadText) ;
						break ;
					case MONSTER_VALUE_AIFILE:
							pMonsterFile->m_pData[i].m_pDataValue[j].m_AIFile = (INT)atoi(szReadText) ;
						break ;
					case MONSTER_VALUE_PATROLID:
							pMonsterFile->m_pData[i].m_pDataValue[j].m_PatrolID = (INT)atoi(szReadText) ;
						break ;
					default :
						{
							Assert(FALSE) ;
						}
						break ;
					};
				}
			}
		}//end if

		///////////////////////////////////////////////////////////////////////////
		//读取怪物数据
		///////////////////////////////////////////////////////////////////////////
		
		//怪物个数
		INT iMonsterCount = f.ReadInt( "info", "monstercount" ) ;
		pMonsterFile->m_Count = iMonsterCount ;
		
		strncpy( pMonsterFile->m_szFileName, pszFileName, _MAX_PATH-1 ) ;
		
		pMonsterFile->m_pMonsterInitData = new _OBJ_MONSTER_INIT[iMonsterCount] ;
		Assert( pMonsterFile->m_pMonsterInitData ) ;
		if( pMonsterFile->m_pMonsterInitData==NULL )
			return FALSE ;

		pMonsterFile->m_pAllocFlag = new BOOL[iMonsterCount] ;
		Assert( pMonsterFile->m_pAllocFlag ) ;
		if( pMonsterFile->m_pAllocFlag==NULL )
			return FALSE ;
		
		pMonsterFile->m_pInitUsing = new _OBJ_MONSTER_INIT[iMonsterCount] ;
		Assert( pMonsterFile->m_pInitUsing ) ;
		if( pMonsterFile->m_pInitUsing==NULL )
			return FALSE ;

		for( i=0; i<iMonsterCount; i++ )
		{
			sprintf( szSection, "monster%d", i ) ;
			if ( 0 == f.ReadText( szSection, "guid", szReadText, sizeof ( szReadText ) ) )
			{
				sprintf( szDebugString, "LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>", pszFileName, szSection, "guid" );
				Log::SaveLog( SERVER_LOGFILE, szDebugString ) ;
				Assert( FALSE );
				continue;
			}

			init.m_GUID = (GUID_t)(atoi(szReadText));

			if ( 0 == f.ReadText( szSection, "type", szReadText, sizeof ( szReadText ) ) )
			{
				sprintf( szDebugString, "LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>", pszFileName, szSection, "type" );
				Log::SaveLog( SERVER_LOGFILE, szDebugString ) ;
				Assert( FALSE );
				continue;
			}

			init.m_uDataID = atoi(szReadText) ;
			pExtAttr = g_MonsterAttrExTbl.GetExtAttr(init.m_uDataID);
			if ( pExtAttr == NULL )
			{
				sprintf( szDebugString, "LoadMonster not find attrib, pszFileName=<%s>,section=<%s>,type=<%s>", pszFileName, szSection, "type" );
				Log::SaveLog( SERVER_LOGFILE, szDebugString ) ;
				Assert( FALSE );
				continue;
			}

			if ( f.ReadTextIfExist( szSection, "name", szReadText, sizeof ( szReadText ) ) )
				strncpy( init.m_szName, szReadText, sizeof( init.m_szName ) - 1 );
			else
				init.m_szName[0]='\0';

			if ( f.ReadTextIfExist( szSection, "title", szReadText, sizeof ( szReadText ) ) )
				strncpy( init.m_szTitle, szReadText, sizeof( init.m_szTitle ) - 1 );
			else
				init.m_szTitle[0]='\0';

			if ( 0 == f.ReadText( szSection, "pos_x", szReadText, sizeof ( szReadText ) ) )
			{
				sprintf( szDebugString, "LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>", pszFileName, szSection, "pos_x" );
				Log::SaveLog( SERVER_LOGFILE, szDebugString ) ;
				Assert( FALSE );
				continue;
			}
			init.m_Pos.m_fX = (FLOAT)atof(szReadText) ;

			if ( 0 == f.ReadText( szSection, "pos_z", szReadText, sizeof ( szReadText ) ) )
			{
				sprintf( szDebugString, "LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>", pszFileName, szSection, "pos_z" );
				Log::SaveLog( SERVER_LOGFILE, szDebugString ) ;
				Assert( FALSE );
				continue;
			}
			init.m_Pos.m_fZ = (FLOAT)atof(szReadText) ;

			if ( 0 == f.ReadText( szSection, "dir", szReadText, sizeof ( szReadText ) ) )
			{
				sprintf( szDebugString, "LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>", pszFileName, szSection, "dir" );
				Log::SaveLog( SERVER_LOGFILE, szDebugString ) ;
				Assert( FALSE );
				continue;
			}
			init.m_Dir = (FLOAT)(atoi(szReadText))*DIR_STEP + __PI/2.f;
			if ( init.m_Dir > 2.f * __PI )
			{
				init.m_Dir -= 2.f * __PI;
			}

			if ( 0 == f.ReadText( szSection, "script_id", szReadText, sizeof ( szReadText ) ) )
			{
				sprintf( szDebugString, "LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>", pszFileName, szSection, "script_id" );
				Log::SaveLog( SERVER_LOGFILE, szDebugString ) ;
				Assert( FALSE );
				continue;
			}
			init.m_idScript = (ScriptID_t)atoi( szReadText );

			if ( 0 == f.ReadText( szSection, "respawn_time", szReadText, sizeof ( szReadText ) ) )
			{
				sprintf( szDebugString, "LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>", pszFileName, szSection, "respawn_time" );
				Log::SaveLog( SERVER_LOGFILE, szDebugString ) ;
				Assert( FALSE );
				continue;
			}
			init.m_RespawnTime = (INT)(atoi(szReadText));

			if ( 0 == f.ReadText( szSection, "group_id", szReadText, sizeof ( szReadText ) ) )
			{
				sprintf( szDebugString, "LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>", pszFileName, szSection, "group_id" );
				Log::SaveLog( SERVER_LOGFILE, szDebugString ) ;
				Assert( FALSE );
				continue;
			}
			init.m_uGroupID = (UINT)(atoi(szReadText) );

			if ( 0 == f.ReadText( szSection, "team_id", szReadText, sizeof ( szReadText ) ) )
			{
				sprintf( szDebugString, "LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>", pszFileName, szSection, "team_id" );
				Log::SaveLog( SERVER_LOGFILE, szDebugString ) ;
				Assert( FALSE );
				continue;
			}
			init.m_uTeamID = (UINT)(atoi(szReadText) );

			if(f.ReadTextIfExist(szSection, "base_ai", szReadText, sizeof ( szReadText ) ))
			{
				init.m_BaseAI	= atoi( szReadText );
				Assert(init.m_BaseAI<g_MonsterAITbl.m_Count) ;
			}
			else
			{
				init.m_BaseAI	=	pExtAttr->m_BaseAI;
				Assert(init.m_BaseAI<g_MonsterAITbl.m_Count) ;
			}

			if ( f.ReadTextIfExist( szSection, "ai_file", szReadText, sizeof ( szReadText ) ) )
			{
				init.m_ExtAIScript	=	atoi(szReadText);
			}
			else
			{
				init.m_ExtAIScript	=	pExtAttr->m_ExtAI;
			}

			if ( 0 == f.ReadText( szSection, "patrol_id", szReadText, sizeof ( szReadText ) ) )
			{
				sprintf( szDebugString, "LoadMonster not find value, pszFileName=<%s>,section=<%s>,value=<%s>", pszFileName, szSection, "patrol_id" );
				Log::SaveLog( SERVER_LOGFILE, szDebugString ) ;
				Assert( FALSE );
				continue;
			}
			init.m_nPatrolID = atoi(szReadText) ;


			if ( 0 != f.ReadTextIfExist( szSection, "shop0", szReadText, sizeof ( szReadText ) ) )
			{
				init.m_nShop[0] = atoi(szReadText);
			}
			else
			{
				init.m_nShop[0] = -1;
			}
			if ( 0 != f.ReadTextIfExist( szSection, "shop1", szReadText, sizeof ( szReadText ) ) )
			{
				init.m_nShop[1] = atoi(szReadText);
			}
			else
			{
				init.m_nShop[1] = -1;
			}
			if ( 0 != f.ReadTextIfExist( szSection, "shop2", szReadText, sizeof ( szReadText ) ) )
			{
				init.m_nShop[2] = atoi(szReadText);
			}
			else
			{
				init.m_nShop[2] = -1;
			}
			if ( 0 != f.ReadTextIfExist( szSection, "shop3", szReadText, sizeof ( szReadText ) ) )
			{
				init.m_nShop[3] = atoi(szReadText);
			}
			else
			{
				init.m_nShop[3] = -1;
			}
			if ( 0 != f.ReadTextIfExist( szSection, "leaderid", szReadText, sizeof ( szReadText ) ) )
			{
				init.m_LeaderID	= atoi(szReadText);
			}
			else
			{
				init.m_LeaderID = -1;
			}

            if ( 0 != f.ReadTextIfExist( szSection, "ispet", szReadText, sizeof ( szReadText ) ) )
			{
				init.m_bPet = atoi(szReadText);
			}
			else
			{
				init.m_bPet = FALSE;
			}		

			if ( 0 != f.ReadTextIfExist( szSection, "level", szReadText, sizeof ( szReadText ) ) )
			{
				init.m_nLevel = atoi(szReadText);
			}
			else
			{
				init.m_nLevel = 0;
			}		

			if ( 0 != f.ReadTextIfExist( szSection, "npc", szReadText, sizeof ( szReadText ) ) )
			{
				init.m_bNPC = atoi(szReadText);
			}
			else
			{
				init.m_bNPC = FALSE;//表中未找到，默认为怪物
			}		

			if ( 0 != f.ReadTextIfExist( szSection, "camp", szReadText, sizeof ( szReadText ) ) )
			{
				init.m_nCamp = atoi(szReadText);
			}
			else
			{
				init.m_nCamp = CAMP3_MONSTER;//表中未找到，默认为友好的怪物
			}
			if ( 0 !=f.ReadTextIfExist( szSection, "scripttimer", szReadText, sizeof (szReadText) ) )
			{
				init.m_ScriptTimer = atoi(szReadText);
			}
			else
			{
				init.m_ScriptTimer = 0;
			}		

			//if( init.m_bNPC )
			//{
			//	if( init.m_nCamp == CAMP_4 )
			//		init.m_nCamp = CAMP4_NPC;
			//	else
			//		init.m_nCamp = CAMP3_NPC;
			//}
			//else
			//{
			//	if( init.m_nCamp == CAMP_4 )
			//		init.m_nCamp = CAMP4_MONSTER;
			//	else
			//		init.m_nCamp = CAMP3_MONSTER;
			//}

			//修正位置
			pScene->GetMap()->VerifyPos( &(init.m_Pos) ) ;

			pMonsterFile->m_pMonsterInitData[i] = init ;
		}//end for

	}//end if

	//构造实际生成怪物数据
	if( pMonsterFile->m_OperateCount>0  )
	{
		if( !pMonsterFile->Do( ) )
		{
			Assert(FALSE) ;
			return FALSE ;
		}
	}
	else
	{
		pMonsterFile->m_CountUsing = pMonsterFile->m_Count ;
		memcpy( pMonsterFile->m_pInitUsing, pMonsterFile->m_pMonsterInitData, sizeof(_OBJ_MONSTER_INIT)*pMonsterFile->m_Count ) ;
	}

	//生成怪物
	for( i=0; i<pMonsterFile->m_CountUsing; i++ )
	{
		if (pMonsterFile->m_pInitUsing[i].m_bPet == TRUE)
		{
			Obj_Pet* pPet = (Obj_Pet*)(pScene->NewObject( Obj::OBJ_TYPE_PET ));
			if ( pPet == NULL )
				break;

			_OBJ_PET_INIT petinit;
			pScene->GetPetManager()->InitPetDB(&(petinit.m_PetDB), pMonsterFile->m_pInitUsing[i].m_uDataID);
			petinit.m_GUID = pMonsterFile->m_pInitUsing[i].m_GUID;
			petinit.m_Pos  = pMonsterFile->m_pInitUsing[i].m_Pos;
			petinit.m_ScriptID = pMonsterFile->m_pInitUsing[i].m_idScript;
			if (pMonsterFile->m_pInitUsing[i].m_szName[0] = '\0')
			{
				strncpy(petinit.m_PetDB.m_szName, pMonsterFile->m_pInitUsing[i].m_szName, sizeof(petinit.m_PetDB.m_szName) - 1 );
			}
			else
			{
				MONSTER_EXT_ATTR* pAttr = g_MonsterAttrExTbl.GetExtAttr(petinit.m_PetDB.m_nDataID);
				if (pAttr)
				{
					strncpy(petinit.m_PetDB.m_szName, pAttr->m_Name, sizeof(petinit.m_PetDB.m_szName) - 1 );
				}
			}

			pPet->Init( &petinit ) ;
			pPet->SetActiveFlag( TRUE );
		}
		else
		{
			Obj_Monster* pMonster = (Obj_Monster*)(pScene->NewObject( Obj::OBJ_TYPE_MONSTER ));
			if ( pMonster == NULL )
				break;

			pMonster->Init( &(pMonsterFile->m_pInitUsing[i]) ) ;
			pMonster->SetActiveFlag( TRUE );
		}
	}

	Log::SaveLog( SERVER_LOGFILE, "Load %s ...OK!", pszFileName ) ;
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL MonsterManager::RemoveAllMonster( VOID )
{
__ENTER_FUNCTION

	Scene *pScene;
	Obj_Monster *pMonster;
	UINT i,uCount,uMaxCount,uLength;

	pScene		= GetScene();
	uCount		= 0;
	uMaxCount	= GetCount();
	uLength	= GetLength();

	for ( i = 0; i <uLength; i++ )
	{
		pMonster = (Obj_Monster*)(GetObjByIndex( 0 ));
		if ( pMonster != NULL )
		{
			pMonster->SetActiveFlag( FALSE );
			pMonster->CleanUp();
			pScene->DeleteObject( pMonster );
			uCount++;
			if (uCount >=uMaxCount )
				break;
		}
	}
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL MonsterManager::HeartBeat( UINT uTime )
{
__ENTER_FUNCTION

	if( !m_LogicTimer.CountingTimer(uTime ) )
		return TRUE;

#define MAX_REMOVE_SIZE 1024
	INT aNeedRemoveMonster[MAX_REMOVE_SIZE] ;
	memset( aNeedRemoveMonster, 0, sizeof(INT)*MAX_REMOVE_SIZE ) ;

	INT nRemoveCount=0 ;

	INT i;
	for ( i = 0; i < (INT)m_uCount; i++ )
	{
		if ( m_papObjs[i] != NULL )
		{
			_MY_TRY
			{
				if ( m_papObjs[i]->IsActiveObj() )
				{
					m_papObjs[i]->HeartBeat(uTime ) ;
				}
				else
				{
					BOOL bRet = m_papObjs[i]->HeartBeat_OutZone(uTime) ;
					if( bRet==FALSE )
					{
						aNeedRemoveMonster[nRemoveCount++] = i ;
					}
				}
			}
			_MY_CATCH
			{
				SaveCodeLog( ) ;
			}
		}
	}

	for( i=nRemoveCount-1; i>=0; i-- )
	{
		_MY_TRY
		{
			Obj_Monster* pMonster = (Obj_Monster*)(m_papObjs[aNeedRemoveMonster[i]]) ;
			if( pMonster != NULL )
			{
				pMonster->SetActiveFlag(FALSE);
				pMonster->CleanUp();
				GetScene()->DeleteObject( pMonster ) ;
			}
		}
		_MY_CATCH
		{
			SaveCodeLog( ) ;
		}
	}


	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

ObjID_t MonsterManager::FindMonsterByGUID( GUID_t guid )
{
__ENTER_FUNCTION

	INT i;
	for ( i = 0; i < (INT)m_uCount; i++ )
	{
		if ( m_papObjs[i] != NULL )
		{
			if ( m_papObjs[i]->IsActiveObj() )
			{
				Obj_Monster* pMonster = (Obj_Monster*)(m_papObjs[i]) ;
				if( pMonster->GetGUID()==guid )
				{
					return pMonster->GetID() ;
				}
			}
		}
	}

__LEAVE_FUNCTION

	return INVALID_ID ;
}

BOOL MonsterManager::InitMonsterData(_MONSTER_INIT *pInit, INT nDataID)
{
__ENTER_FUNCTION

	// 还没有写
	Assert(FALSE && "MonsterManager::InitMonsterData");

	if(pInit == NULL || nDataID == INVALID_ID)
		return FALSE;

	MONSTER_EXT_ATTR *pAttr = g_MonsterAttrExTbl.GetExtAttr(nDataID);
	if(pAttr == NULL)
		return FALSE;

	return TRUE;

__LEAVE_FUNCTION
	return FALSE;
}



