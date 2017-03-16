#include "stdafx.h"
#include "ShareMemory.h"
#include "Log.h"
#include "Config.h"
#include "TimeManager.h"
#include "SMUManager.h"
#include "SMULogicManager.h"
#include "ShareDBManager.h"
#include "ODBCInterface.h"
#include "CommandThread.h"
#include "PlayerShopDefine.h"

#if __LINUX__
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <errno.h>
#elif __WINDOWS__
#include <WinBase.h>
#endif


ShareMemory			g_ShareMemory ;

using namespace PLAYER_SHOP;
INT					g_CmdInput;


BOOL				CheckSaveAllFile();
BOOL				CheckExitFile();

int main(int argc, char* argv[])
{
#if defined(__WINDOWS__)
	_CrtSetDbgFlag(_CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF);
#endif
	g_CmdInput = FALSE;

	if( argc>1 )
	{
		for( int i=1; i<argc; i++ )
		{
			if( strcmp(argv[i],"-clear")==0 )
			{
				g_CmdArgv = CMD_MODE_CLEARALL ;
				printf("Cmd enter clear mode!\r\n");
			}
			if(strcmp(argv[i],"-loaddump")==0)
			{
				g_CmdArgv = CMD_MODE_LOADDUMP;
				printf("Cmd enter loaddump mode!\r\n");
			}
			if(strcmp(argv[i],"-enablecmd")==0)
			{	
				g_CmdInput	= TRUE;

			}
			if( strcmp(argv[i],"-ignoreassert")==0 )
			{
				g_Command_Assert=1 ;
			}
			else if( strcmp(argv[i],"-retryassert")==0 )
			{
				g_Command_Assert=2 ;
			}

			if( strcmp(argv[i],"-ignoremessagebox")==0 )
			{
				g_Command_IgnoreMessageBox=TRUE ;
			}
					
		}
	}

	g_pTimeManager = new TimeManager ;
	Assert( g_pTimeManager ) ;
	if( g_pTimeManager->Init() )
	{
		Log::SaveLog( "./Log/ShareMemory.log", "时间管理器初始化完毕。" ) ;
	}
	else
	{
		Log::SaveLog( "./Log/ShareMemory.log", "时间管理器初始化失败。" ) ;
		return 1;
	}

	Log::SaveLog( "./Log/ShareMemory.log", "=====================================" );
	Log::SaveLog( "./Log/ShareMemory.log", "启动时间： %.10d",g_pTimeManager->Time2DWORD() );
	Log::SaveLog( "./Log/ShareMemory.log", "=====================================" );

	Log::SaveLog( "./Log/ShareMemory.log", "启动ShareMemory服务器。" ) ;

	BOOL bRet ;

	Log::SaveLog( "./Log/ShareMemory.log", "ShareMemory开启。" ) ;

	bRet = g_ShareMemory.Init();
	if( bRet==FALSE )
	{
		Assert(FALSE) ;
		return 1 ;
	}
	else
	{
		Log::SaveLog( "./Log/ShareMemory.log", "ShareMemory初始化完毕。" ) ;
	}
	
	bRet = g_ShareMemory.Loop();
	if( bRet==FALSE )
	{
		Assert(FALSE) ;
		return 1 ;
	}

	bRet = g_ShareMemory.Exit();
	if( bRet==FALSE )
	{
		Assert(FALSE) ;
		return 1 ;
	}
	
	SAFE_DELETE(g_pTimeManager);

	return 0 ;
}

ShareMemory::ShareMemory( ) : m_bExited(FALSE)
{

	
}

ShareMemory::~ShareMemory( )
{
}

BOOL ShareMemory::Init( )
{

	BOOL bRet ;

	Log::SaveLog( "./Log/ShareMemory.log", "开始进行配置文件读取。" ) ;
	bRet = g_Config.Init( ) ;
	Assert( bRet );
	Log::SaveLog( "./Log/ShareMemory.log", "配置文件读取完毕。" ) ;
	
	Log::SaveLog( "./Log/ShareMemory.log", "创建静态管理器。" ) ;
	bRet = NewStaticManager( ) ;
	Assert( bRet ) ;
	Log::SaveLog( "./Log/ShareMemory.log", "创建静态管理器完毕。" ) ;

	Log::SaveLog( "./Log/ShareMemory.log", "初始化静态管理器。" ) ;
	bRet = InitStaticManager( ) ;
	Assert( bRet ) ;
	Log::SaveLog( "./Log/ShareMemory.log", "初始化静态管理器完毕。" ) ;
	return TRUE ;
}

BOOL ShareMemory::Loop( )
{
	if(g_CmdInput)
	{
		g_CommandThread.start();
		Log::SaveLog( "./Log/ShareMemory.log", "命令行监听线程启动。" ) ;
	}

	Log::SaveLog( "./Log/ShareMemory.log", "开始主逻辑循环。" ) ;
	Log::SaveLog( "./Log/ShareMemory.log", "=====================================================" ) ;
	while( TRUE )
	{
		DoWork();
		MySleep(1000);
	}
	Log::SaveLog( "./Log/ShareMemory.log", "主逻辑循环结束。" ) ;

	return TRUE ;
}

BOOL ShareMemory::Exit( )
{
	DelStaticManager();
	m_bExited= FALSE;
	return TRUE ;
}

BOOL ShareMemory::DoWork()
{
	_MY_TRY
	{
		BOOL  bExit = FALSE;

		ODBCInterface* pInterface= 	g_pDBManager->GetInterface(CHARACTER_DATABASE);
		Assert(pInterface);

		if(!pInterface->IsConnected())
		{
			Log::SaveLog("./Log/ShareMemory.log","连接数据库失败");
			BOOL bRet =	pInterface->Connect();
			if(!bRet)
			{
				Log::SaveLog("./Log/ShareMemory.log","重新连接数据库失败");
				MySleep(5000);
				if(g_CommandThread.m_SMConfig.Commands.cmdType==CMD_UNKNOW)
				{
					return FALSE;
				}
			}
			else
			{
				Log::SaveLog("./Log/ShareMemory.log","重新连接数据库成功");
			}
		}

		if(CheckSaveAllFile())
		{
			g_CommandThread.m_SMConfig.Commands.cmdType = CMD_SAVE_ALL;
		}

		if(CheckExitFile())
		{
			g_CommandThread.m_SMConfig.Commands.cmdType = CMD_SAVE_ALL;
			bExit = TRUE;
			Log::SaveLog("./Log/ShareMemory.log","收到退出消息");
		}

		if(g_CommandThread.m_SMConfig.Commands.cmdType!=CMD_UNKNOW)
		{
			g_SMConfig = g_CommandThread.m_SMConfig ;
			g_CommandThread.m_SMConfig.Commands.cmdType=CMD_UNKNOW;
		}

		for(UINT i = 0;i<MAX_SM_OBJ_NUM;i++)
		{
			if(m_SMULogicManager[i].m_SMULogicManager)
			{
				SHAREMEM_TYPE	Type = m_SMULogicManager[i].m_Type;

				switch(Type) 
				{
				case ST_HUMAN_SMU:
					{
						SMULogicManager<HumanSMU>* pHumanSMULogicMgr = static_cast<SMULogicManager<HumanSMU>*>(m_SMULogicManager[i].m_SMULogicManager);
						if(pHumanSMULogicMgr)
							pHumanSMULogicMgr->HeartBeat();
						else
						{
							AssertEx(FALSE,"运行时类型错误" );
						}

						break;
					}
				case ST_GUILD_SMU:
					{
						SMULogicManager<GuildSMU>* pGuildSMULogicMgr = static_cast<SMULogicManager<GuildSMU>*>(m_SMULogicManager[i].m_SMULogicManager);
						if(pGuildSMULogicMgr)
							pGuildSMULogicMgr->HeartBeat();
						else
						{
							AssertEx(FALSE,"运行时类型错误" );
						}

						break;
					}
				case ST_MAIL_SMU:
					{
						SMULogicManager<MailSMU>* pMailSMULogicMgr = static_cast<SMULogicManager<MailSMU>*>(m_SMULogicManager[i].m_SMULogicManager);
						if(pMailSMULogicMgr)
							pMailSMULogicMgr->HeartBeat();
						else
						{
							AssertEx(FALSE,"运行时类型错误" );
						}

						break;	
					}
				case ST_PSHOP_SMU:
					{
						SMULogicManager<PlayerShopSM>* pPShopSMULogicMgr = static_cast<SMULogicManager<PlayerShopSM>*>(m_SMULogicManager[i].m_SMULogicManager);
						if(pPShopSMULogicMgr)
							pPShopSMULogicMgr->HeartBeat();
						else
						{
							AssertEx(FALSE,"运行时类型错误" );
						}
						break;
					}

				case ST_ITEMSERIAL_SMU:
					{
						SMULogicManager<ItemSerialKeySMU>* pItemSerialSMULogicMgr = static_cast<SMULogicManager<ItemSerialKeySMU>*>(m_SMULogicManager[i].m_SMULogicManager);
						if(pItemSerialSMULogicMgr)
							pItemSerialSMULogicMgr->HeartBeat();
						else
						{
							AssertEx(FALSE,"运行时类型错误" );
						}
						break;
					}
				case ST_USERDATA_SMU:
					{
						AssertEx(FALSE,"无法识别的 SMU 类型");
						break;
					}
				case  ST_HUMANEXT_SMU:
					{
						AssertEx(FALSE,"无法识别的 SMU 类型");
						break;
					}
				default:
					{
						AssertEx(FALSE,"无法识别的 SMU 类型");
					}
				}

			}
		}

		if(g_SMConfig.Commands.cmdType == CMD_CLEAR_ALL)
		{
			exit(0);
		}

		
		g_SMConfig.Commands.cmdType = CMD_UNKNOW;

		if(bExit)
		{
			Log::SaveLog( "./Log/ShareMemory.log", "退出共享内存进程");
			exit(0);
		}

		return TRUE;

	}
	_MY_CATCH
	{
		Log::SaveLog( "./Log/ShareMemory.log", "共享内存进程DoWork帧循环出现错误") ;
	
	}

	return FALSE;
}



BOOL ShareMemory::NewStaticManager( )
{
	__ENTER_FUNCTION

	g_pDBManager = new ShareDBManager();

	AssertEx( g_pDBManager,"分配数据库管理器失败!" );

	Log::SaveLog("./Log/ShareMemory.log","创建静态池管理器成功");

	for(UINT i =0;i< g_Config.m_ShareMemInfo.m_SMUObjCount;i++)
	{
		m_SMUPool[i].m_Data = g_Config.m_ShareMemInfo.m_pShareData[i];
		SHAREMEM_TYPE type = g_Config.m_ShareMemInfo.m_pShareData[i].m_Type;
		switch(type) 
		{
		case ST_HUMAN_SMU:
			{
				m_SMUPool[i].m_Pool = new SMUPool<HumanSMU>();
				m_SMULogicManager[i].m_SMULogicManager = new SMULogicManager<HumanSMU>();
				m_SMULogicManager[i].m_Type	=	ST_HUMAN_SMU;
			}
			break;
		case ST_GUILD_SMU:
			{
				m_SMUPool[i].m_Pool = new SMUPool<GuildSMU>();
				m_SMULogicManager[i].m_SMULogicManager = new SMULogicManager<GuildSMU>();
				m_SMULogicManager[i].m_Type	=	ST_GUILD_SMU;
			}
			break;
		case ST_MAIL_SMU:
			{
				m_SMUPool[i].m_Pool = new SMUPool<MailSMU>();
				m_SMULogicManager[i].m_SMULogicManager = new SMULogicManager<MailSMU>();
				m_SMULogicManager[i].m_Type	=	ST_MAIL_SMU;	
			}
			break;
		case ST_PSHOP_SMU:
			{
				m_SMUPool[i].m_Pool = new SMUPool<PlayerShopSM>();
				m_SMULogicManager[i].m_SMULogicManager = new SMULogicManager<PlayerShopSM>();
				m_SMULogicManager[i].m_Type	=	ST_PSHOP_SMU;	
			}
			break;
		case ST_ITEMSERIAL_SMU:
			{
				m_SMUPool[i].m_Pool = new SMUPool<ItemSerialKeySMU>();
				m_SMULogicManager[i].m_SMULogicManager = new SMULogicManager<ItemSerialKeySMU>();
				m_SMULogicManager[i].m_Type	=	ST_ITEMSERIAL_SMU;	

			}
			break;
		case ST_USERDATA_SMU:
			AssertEx(FALSE,"Unimplement Type: ST_USERDATA_SMU");
			break;
		case ST_HUMANEXT_SMU:
			AssertEx(FALSE,"Unimplement Type: ST_HUMANEXT_SMU");
			break;
		default:
			break;
		}
		
	}

	Log::SaveLog( "./Log/ShareMemory.log", "创建静态池管理器成功" ) ;

	return TRUE ;

	__LEAVE_FUNCTION	

	return FALSE;
}

BOOL ShareMemory::InitStaticManager( )
{
	__ENTER_FUNCTION

	BOOL bRet = FALSE;

	//DB 的初始化,连接数据库
	Assert(g_pDBManager);
	bRet = g_pDBManager->Init();
	if(!bRet)
	{
		Log::SaveLog("./Log/ShareMemory.log","初始化DB数据失败");
		return FALSE;
	}
	else
	{
		Log::SaveLog("./Log/ShareMemory.log","初始化DB数据成功");
	}

	for(UINT i =0;i< g_Config.m_ShareMemInfo.m_SMUObjCount;i++)
	{
		SHAREMEM_TYPE type = g_Config.m_ShareMemInfo.m_pShareData[i].m_Type;
		switch(type)
		{
		case ST_HUMAN_SMU:
			{
				
				SMUPool<HumanSMU>* pHumanSMUPool = static_cast<SMUPool<HumanSMU>*>(m_SMUPool[i].m_Pool);
				Assert(pHumanSMUPool);
				SM_KEY	key			=		m_SMUPool[i].m_Data.m_Key;
				bRet = pHumanSMUPool->Init(MAX_POOL_SIZE,key,SMPT_SHAREMEM);
				Assert(bRet);
				SMULogicManager<HumanSMU>* pHumanSMULogicMgr = static_cast<SMULogicManager<HumanSMU>*>(m_SMULogicManager[i].m_SMULogicManager);
				Assert(pHumanSMULogicMgr);
				bRet =	pHumanSMULogicMgr->Init(pHumanSMUPool);
				Assert(bRet);
			}
			break;
		case ST_GUILD_SMU:
			{
				SMUPool<GuildSMU>* pGuildSMUPool = static_cast<SMUPool<GuildSMU>*>(m_SMUPool[i].m_Pool);
				Assert(pGuildSMUPool);
				SM_KEY	key			=		m_SMUPool[i].m_Data.m_Key;
				bRet = pGuildSMUPool->Init(MAX_GUILD_SIZE,key,SMPT_SHAREMEM);
				Assert(bRet);
				SMULogicManager<GuildSMU>* pGuildSMULogicMgr = static_cast<SMULogicManager<GuildSMU>*>(m_SMULogicManager[i].m_SMULogicManager);
				Assert(pGuildSMULogicMgr);
				bRet =	pGuildSMULogicMgr->Init(pGuildSMUPool);
				Assert(bRet);
			}
			break;
		case ST_MAIL_SMU:
			{
				SMUPool<MailSMU>* pMailSMUPool = static_cast<SMUPool<MailSMU>*>(m_SMUPool[i].m_Pool);
				Assert(pMailSMUPool);
				SM_KEY	key			=		m_SMUPool[i].m_Data.m_Key;
				bRet = pMailSMUPool->Init(MAX_MAILNODE_SIZE,key,SMPT_SHAREMEM);
				Assert(bRet);
				SMULogicManager<MailSMU>* pMailSMULogicMgr = static_cast<SMULogicManager<MailSMU>*>(m_SMULogicManager[i].m_SMULogicManager);
				Assert(pMailSMULogicMgr);
				bRet =	pMailSMULogicMgr->Init(pMailSMUPool);
				Assert(bRet);
			}
			break;
		case ST_PSHOP_SMU:
			{
				SMUPool<PlayerShopSM>* pPlayerShopSMUPool = static_cast<SMUPool<PlayerShopSM>*>(m_SMUPool[i].m_Pool);
				Assert(pPlayerShopSMUPool);
				SM_KEY	key			=		m_SMUPool[i].m_Data.m_Key;
				bRet = pPlayerShopSMUPool->Init(MAX_PLAYER_SHOP_POOL_PER_SERVER,key,SMPT_SHAREMEM);
				Assert(bRet);
				SMULogicManager<PlayerShopSM>* pPlayerShopSMULogicMgr = static_cast<SMULogicManager<PlayerShopSM>*>(m_SMULogicManager[i].m_SMULogicManager);
				Assert(pPlayerShopSMULogicMgr);
				bRet =	pPlayerShopSMULogicMgr->Init(pPlayerShopSMUPool);
				Assert(bRet);
			}	
			break;

		case ST_ITEMSERIAL_SMU:
			{
				SMUPool<ItemSerialKeySMU>* pItemSerialSMUPool = static_cast<SMUPool<ItemSerialKeySMU>*>(m_SMUPool[i].m_Pool);
				Assert(pItemSerialSMUPool);
				SM_KEY	key			=		m_SMUPool[i].m_Data.m_Key;
				bRet = pItemSerialSMUPool->Init(1,key,SMPT_SHAREMEM);
				Assert(bRet);
				SMULogicManager<ItemSerialKeySMU>* pItemSerialSMULogicMgr = static_cast<SMULogicManager<ItemSerialKeySMU>*>(m_SMULogicManager[i].m_SMULogicManager);
				Assert(pItemSerialSMULogicMgr);
				bRet =	pItemSerialSMULogicMgr->Init(pItemSerialSMUPool);
				Assert(bRet);

			}
			break;
		case ST_USERDATA_SMU:
			AssertEx(FALSE,"Unimplement Type: ST_USERDATA_SMU");
			break;
		case ST_HUMANEXT_SMU:
			AssertEx(FALSE,"Unimplement Type: ST_HUMANEXT_SMU");
			break;
		default:
			AssertEx(bRet," ShareMemory::InitStaticManager fails");
			break;
		}
	}

	return bRet ;

	__LEAVE_FUNCTION	

	return FALSE;
}

BOOL ShareMemory::DelStaticManager( )
{
	__ENTER_FUNCTION

	Log::SaveLog("./Log/ShareMemory.log","开始删除静态池");

	for(UINT i =0;i< g_Config.m_ShareMemInfo.m_SMUObjCount;i++)
	{

		SHAREMEM_TYPE type = g_Config.m_ShareMemInfo.m_pShareData[i].m_Type;
		switch(type)
		{
		case ST_HUMAN_SMU:
			{

				SMUPool<HumanSMU>* pHumanSMUPool = 
					static_cast<SMUPool<HumanSMU>*>(m_SMUPool[i].m_Pool);
				SMULogicManager<HumanSMU>* pHumanSMULogicMgr = 
					static_cast<SMULogicManager<HumanSMU>*>(m_SMULogicManager[i].m_SMULogicManager);

				SAFE_DELETE(pHumanSMUPool);
				SAFE_DELETE(pHumanSMULogicMgr);
			
			}
			break;
		case ST_GUILD_SMU:
			{
				SMUPool<GuildSMU>* pGuildSMUPool = 
					static_cast<SMUPool<GuildSMU>*>(m_SMUPool[i].m_Pool);
				SMULogicManager<GuildSMU>* pGuildSMULogicMgr = 
					static_cast<SMULogicManager<GuildSMU>*>(m_SMULogicManager[i].m_SMULogicManager);

				SAFE_DELETE(pGuildSMUPool);
				SAFE_DELETE(pGuildSMULogicMgr);

			}
			break;
		case ST_MAIL_SMU:
			{
				SMUPool<MailSMU>* pMailSMUPool = 
					static_cast<SMUPool<MailSMU>*>(m_SMUPool[i].m_Pool);
				SMULogicManager<MailSMU>* pMailSMULogicMgr = 
					static_cast<SMULogicManager<MailSMU>*>(m_SMULogicManager[i].m_SMULogicManager);

				SAFE_DELETE(pMailSMUPool);
				SAFE_DELETE(pMailSMULogicMgr);

			}
			break;
		case ST_ITEMSERIAL_SMU:
			{
				SMUPool<ItemSerialKeySMU>* pSMUPool = 
					static_cast<SMUPool<ItemSerialKeySMU>*>(m_SMUPool[i].m_Pool);
				SMULogicManager<ItemSerialKeySMU>* pSMULogicMgr = 
					static_cast<SMULogicManager<ItemSerialKeySMU>*>(m_SMULogicManager[i].m_SMULogicManager);

				SAFE_DELETE(pSMUPool);
				SAFE_DELETE(pSMULogicMgr);

			}
			break;
		case ST_USERDATA_SMU:
			AssertEx(FALSE,"Unimplement Type: ST_USERDATA_SMU");
			break;
		case ST_HUMANEXT_SMU:
			AssertEx(FALSE,"Unimplement Type: ST_HUMANEXT_SMU");
			break;
		default:
			AssertEx(FALSE," ShareMemory::InitStaticManager fails");
			break;
		}
		
		
	}

	Log::SaveLog("./Log/ShareMemory.log","删除静态池完成");
	return TRUE ;

	__LEAVE_FUNCTION	
	return FALSE;
}

BOOL	CheckSaveAllFile()
{
	__ENTER_FUNCTION
	
	
	if( remove( "saveall.cmd" ) == -1 )
	{
				return FALSE;
	}
			
	return TRUE;


	__LEAVE_FUNCTION

	return FALSE;
}

BOOL	CheckExitFile()
{
	__ENTER_FUNCTION


	if( remove( "exit.cmd" ) == -1 )
	{
			return FALSE;
	}
	extern	BOOL g_LockTimeOutEnable;
	g_LockTimeOutEnable = TRUE;
	return TRUE;


	__LEAVE_FUNCTION

	return FALSE;
}


VOID INTHandler(INT)
{
	DumpStack("INT exception:\r\n");
	exit(0);
}
VOID TERMHandler(INT)
{
	DumpStack("TERM exception:\r\n");
	exit(0);

}
VOID ABORTHandler(INT)
{
	DumpStack("ABORT exception:\r\n");
	exit(0);
}

VOID ILLHandler(INT)
{
	DumpStack("ILL exception:\r\n");
	exit(0);
}

VOID FPEHandler(INT)
{
	DumpStack("FPE exception:\r\n");
	exit(0);
}

VOID SEGHandler(INT)
{
	DumpStack("SEG exception:\r\n");
	exit(0);
}
VOID XFSZHandler(INT)
{
	DumpStack("XFSZ exception:\r\n");
	exit(0);
}

ShmExceptionHandler::ShmExceptionHandler()
{
#ifdef __LINUX__
	signal(SIGSEGV, SEGHandler);
	signal(SIGFPE,  FPEHandler);
	signal(SIGILL,  ILLHandler);
	signal(SIGINT,  INTHandler);  
	signal(SIGTERM, TERMHandler); 
	signal(SIGABRT, ABORTHandler);
	signal(SIGXFSZ, XFSZHandler);
#endif
}

ShmExceptionHandler g_ShmExceptionHandler;
