#include "stdafx.h"
// PlatformManager.cpp

#include "Log.h"
#include "Ini.h"
#include "Scene.h"
#include "ObjManager.h"
#include "Obj_Platform.h"
#include "PlatformPool.h"

#include "PlatformManager.h"
#include "SceneManager.h"


#define SECSIZE 64
#define DIR_STEP (__PI/18.f)

PlatformManager::PlatformManager( VOID )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

PlatformManager::~PlatformManager( VOID )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

Obj_Platform *PlatformManager::GetPlatform( ObjID_t idObj )
{
__ENTER_FUNCTION

	Obj_Platform *pPlatform = (Obj_Platform*)(GetScene()->GetObjManager()->GetObj( idObj ));
	if ( pPlatform == NULL )
	{
		return NULL;
	}

	if ( pPlatform->GetObjType() != Obj::OBJ_TYPE_PLATFORM )
	{
		Assert( (pPlatform->GetObjType() == Obj::OBJ_TYPE_PLATFORM) && "PlatformManager::GetPlatform" );
		return NULL;
	}
	return pPlatform;
__LEAVE_FUNCTION
	return NULL ;
}

BOOL PlatformManager::LoadPlatform( const CHAR *pszFileName )
{
__ENTER_FUNCTION

	Scene	*pScene;
	CHAR	szSection[SECSIZE], szTempData[SECSIZE];
	pScene	= GetScene();

	PLATFORM_FILE* pPlatformFile = g_pSceneManager->FindPlatformFile( pszFileName ) ;
	if( pPlatformFile==NULL )
	{
		//找出一个空的
		pPlatformFile = g_pSceneManager->FindEmptyPlatformFile( ) ;
		if( pPlatformFile==NULL )
		{
			Assert(FALSE) ;
			return FALSE ;
		}

		Ini		f(pszFileName);
		//读取操作台数据
		INT iPlatformCount = f.ReadInt( "info", "platformcount" );
		pPlatformFile->m_Count = iPlatformCount ;
		pPlatformFile->m_pInit = new _OBJ_PLATFORM_INIT[iPlatformCount] ;
		if( pPlatformFile->m_pInit==NULL )
		{
			Assert(FALSE) ;
			return FALSE ;
		}

		for( INT i=0; i<iPlatformCount; i++ )
		{
			_OBJ_PLATFORM_INIT init;

			sprintf( szSection, "platform%d", i );
			init.m_Type = f.ReadInt( szSection, "index" );
			init.m_Class = f.ReadInt( szSection, "class" );

			f.ReadText( szSection, "pos_X", szTempData, SECSIZE );
			init.m_Pos.m_fX = (FLOAT)atof(szTempData);

			f.ReadText( szSection, "pos_Z", szTempData, SECSIZE );
			init.m_Pos.m_fZ = (FLOAT)atof(szTempData);

			INT nDir = f.ReadInt( szSection, "dir" );
			init.m_Dir = (FLOAT)(nDir)*DIR_STEP + __PI/2.f;
			if ( init.m_Dir > 2.f * __PI )
			{
				init.m_Dir -= 2.f * __PI;
			}

			INT nRes;
			if( f.ReadIntIfExist( szSection, "script_id", nRes) == TRUE )
			{
				init.m_Script = (ScriptID_t)nRes;
			}
			else
			{
				init.m_Script = (ScriptID_t)(0xFFFFFFFF);
			}

			pPlatformFile->m_pInit[i] = init ;
		}

		strncpy( pPlatformFile->m_szFileName, pszFileName, _MAX_PATH-1 ) ;
	}

	//生成操作台
	for( INT i=0; i<pPlatformFile->m_Count; i++ )
	{
		Obj_Platform* pPlatform = (Obj_Platform*)(GetScene()->NewObject( Obj::OBJ_TYPE_PLATFORM ));
		if ( pPlatform == NULL )
			break;
		pPlatform->Init( &(pPlatformFile->m_pInit[i]) );

		pPlatform->SetActiveFlag( TRUE );
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL PlatformManager::RemoveAllPlatform( )
{
__ENTER_FUNCTION

	Scene *pScene;
	Obj_Platform *pPlatform;
	UINT i,uCount,uMaxCount,uLength;

	pScene		= GetScene();
	uCount		= 0;
	uMaxCount	= GetCount();
	uLength	= GetLength();

	for ( i = 0; i <uLength; i++ )
	{
		pPlatform = (Obj_Platform*)(GetObjByIndex( 0 ));
		if ( pPlatform != NULL )
		{
			pPlatform->SetActiveFlag( FALSE );
			pPlatform->CleanUp();
			pScene->DeleteObject( pPlatform );
			uCount++;
			if (uCount >=uMaxCount )
				break;
		}
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}
