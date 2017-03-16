#include "stdafx.h"

#include "Login.h"
#include "TimeManager.h"
#include "Log.h"
#include "LoginDBManager.h"
#include "Config.h"
#include "ConnectManager.h"
#include "ThreadManager.h"
#include "ProcessManager.h"
#include "ServerManager.h"
#include "PlayerPool.h"
#include "PacketFactoryManager.h"
#include "TurnPlayerQueue.h"
#include "DBThreadManager.h"
#include "CharConfig.h"
//#include "ClientMain.h"

Login	g_Login;


Login::Login() : m_bExited(FALSE)
{

}

Login::~Login()
{
}

BOOL	Login::Init()
{
	__ENTER_FUNCTION

	
	BOOL	bRet = FALSE;

	Log::SaveLog( "./Log/Login.log", "开始进行配置文件读取。" ) ;
	bRet = g_Config.Init( ) ;
	if(!bRet)
	{
		Assert(bRet);
		return FALSE;
	}
	Log::SaveLog( "./Log/Login.log", "配置文件读取完毕。" ) ;

	Log::SaveLog( "./Log/Login.log", "创建Login全部管理器。" ) ;
	bRet  = NewLogin();
	if(!bRet)
	{
		Assert(bRet);
		return FALSE;
	}
	Log::SaveLog( "./Log/Login.log", "创建Login全部管理器完毕。" ) ;

	Log::SaveLog( "./Log/Login.log", "初始化Login全部管理器。" ) ;
	bRet = InitLogin();
	if(!bRet)
	{
		Assert(bRet);
		return FALSE;
	}
	Log::SaveLog( "./Log/Login.log", "初始化Login全部管理器完毕。" ) ;

	m_bExited = FALSE;
	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

BOOL	Login::Loop()
{
	__ENTER_FUNCTION

	BOOL bRet = FALSE ;

	Log::SaveLog( LOGIN_LOGFILE, "开始主逻辑循环。" ) ;
	Log::SaveLog( LOGIN_LOGFILE, "=====================================================" ) ;

	
	//连接客户端线程
	Log::SaveLog( LOGIN_LOGFILE, "客户端线程 ConnectManager 启动" ) ;
	g_pConnectManager->start();

	//连接World 和 BillingSystem 的线程
	Log::SaveLog( LOGIN_LOGFILE, "服务器组内部线程 ThreadManager 启动" ) ;
	bRet = g_pThreadManager->Start( ) ;
	Assert( bRet ) ;
	
	//数据库处理
	Log::SaveLog(LOGIN_LOGFILE,"数据库线程 DBThreadManager 启动");
	g_pDBThreadManager->Start();

	//主线程资源留给 ProcessManager
	Log::SaveLog( LOGIN_LOGFILE, "逻辑主线程 ProcessManager 启动" ) ;
	g_pProcessManager->start();

	//守护线程
	while(TRUE)
	{
		MySleep(100);
	}

	return bRet;

	__LEAVE_FUNCTION

	return FALSE;
}

BOOL	Login::Exit()
{
	__ENTER_FUNCTION

	
	Log::SaveLog( LOGIN_LOGFILE, "Begin delete..." ) ;

	SAFE_DELETE(g_pDataBaseManager);
	Log::SaveLog( LOGIN_LOGFILE, "g_pDataBaseManager delete...OK" ) ;

	SAFE_DELETE(g_pProcessManager);
	Log::SaveLog( LOGIN_LOGFILE, "g_pProcessManager delete...OK" ) ;

	SAFE_DELETE(g_pPlayerPool);
	Log::SaveLog( LOGIN_LOGFILE, "g_pPlayerPool delete...OK" ) ;
	

	SAFE_DELETE(g_pPacketFactoryManager);
	Log::SaveLog( LOGIN_LOGFILE, "g_pPacketFactoryManager delete...OK" ) ;

	SAFE_DELETE(g_pProcessPlayerQueue);
	Log::SaveLog( LOGIN_LOGFILE, "g_pProcessPlayerQueue delete...OK" ) ;
	
	SAFE_DELETE(g_pWorldPlayerQueue);
	Log::SaveLog( LOGIN_LOGFILE, "g_pWorldPlayerQueue delete...OK" ) ;
	
	SAFE_DELETE(g_pThreadManager);
	Log::SaveLog( LOGIN_LOGFILE, "g_pThreadManager delete...OK" ) ;
	
	SAFE_DELETE(g_pServerManager);
	Log::SaveLog( LOGIN_LOGFILE, "g_pServerManager delete...OK" ) ;
	
	SAFE_DELETE(g_pConnectManager);
	Log::SaveLog( LOGIN_LOGFILE, "g_pConnectManager delete...OK" ) ;
	
	SAFE_DELETE(g_pDBThreadManager);
	Log::SaveLog(LOGIN_LOGFILE,"g_pDBThreadManager delete ... OK");

	Log::SaveLog( LOGIN_LOGFILE, "End delete..." ) ;
	
	m_bExited = TRUE;

	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}


/*
*	分配空间相关
*/
BOOL	Login::NewLogin()
{
	__ENTER_FUNCTION

	g_pDataBaseManager	=	 new	LoginDBManager();
	AssertEx(g_pDataBaseManager,"分配数据库管理器失败!");
	Log::SaveLog(LOGIN_LOGFILE,"分配LoginDBManager成功");

	g_pProcessManager	=	 new  ProcessManager();
	AssertEx( g_pProcessManager,"分配g_pProcessManager 失败!");
	Log::SaveLog( LOGIN_LOGFILE, "分配ProcessManager成功" ) ;
	
	g_pPlayerPool		=	new	  PlayerPool ;
	AssertEx( g_pPlayerPool,"分配g_pPlayerPool 失败!");
	Log::SaveLog( LOGIN_LOGFILE, "分配PlayerPool成功" ) ;

	g_pPacketFactoryManager = new PacketFactoryManager ;
	AssertEx( g_pPacketFactoryManager,"分配g_pFacketFactoryManager 失败!") ;
	Log::SaveLog( LOGIN_LOGFILE, "分配PacketFactoryManager成功" ) ;
	
	g_pProcessPlayerQueue	= new TurnPlayerQueue;
	AssertEx(g_pProcessPlayerQueue,"分配排队队列失败!");
	Log::SaveLog(LOGIN_LOGFILE,"分配TurnPlayerQueue成功");

	g_pWorldPlayerQueue	= new WorldPlayerQueue;
	AssertEx(g_pWorldPlayerQueue,"分配排队队列失败!");
	Log::SaveLog(LOGIN_LOGFILE,"分配WorldPlayerQueue成功");

	g_pThreadManager	=	 new ThreadManager();
	AssertEx( g_pThreadManager,"分配g_pThreadManager 失败!");
	Log::SaveLog( LOGIN_LOGFILE, "分配ThreadManager成功" ) ;

	g_pServerManager    =	 new ServerManager ;
	AssertEx( g_pServerManager,"分配g_pServerManager 失败!" ) ;
	Log::SaveLog( LOGIN_LOGFILE, "分配ServerManager成功" ) ;

	g_pConnectManager   =    new ConnectManager ;
	AssertEx( g_pConnectManager,"分配g_pConnectManager 失败!");
	Log::SaveLog( LOGIN_LOGFILE, "分配ConnectManager成功" ) ;

	g_pDBThreadManager	=	new DBThreadManager;
	AssertEx(g_pDBThreadManager,"分配g_pDBThreadManager 失败!");
	Log::SaveLog( LOGIN_LOGFILE, "分配DBThreadManager成功" );

	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

/*
*	数据赋值相关
*/
BOOL	Login::InitLogin()
{
	__ENTER_FUNCTION

	BOOL	bRet = FALSE;
	INT		nTemp = 0;

	//DB 的初始化,连接数据库
	Assert(g_pDataBaseManager);
	bRet = g_pDataBaseManager->Init();
	Assert(bRet);
	Log::SaveLog(LOGIN_LOGFILE,"DataBaseManager 初始化完成");

	if( g_Config.m_ConfigInfo.m_SystemModel == 0 )
	{
		nTemp = 5;
	}
	else
	{
		nTemp = MAX_POOL_SIZE;
	}
	bRet = g_pPlayerPool->Init( nTemp ) ;
	Assert( bRet ) ;
	Log::SaveLog( LOGIN_LOGFILE, "PlayerPool 初始化完成" ) ;

	bRet = g_pPacketFactoryManager->Init( ) ;
	Assert( bRet ) ;
	Log::SaveLog( LOGIN_LOGFILE, "PacketFactoryManager 初始化完成" ) ;
	
	bRet = g_pProcessPlayerQueue->Init();
	Assert(bRet);
	Log::SaveLog(LOGIN_LOGFILE,"DataBaseManager 初始化完成");

	bRet = g_pWorldPlayerQueue->Init();
	Assert(bRet);
	Log::SaveLog(LOGIN_LOGFILE,"WorldPlayerQueue 初始化完成");

	//对客户端网络管理类的初始化
	bRet = g_pConnectManager->Init( ) ;
	Assert( bRet ) ;
	Log::SaveLog( LOGIN_LOGFILE, "ConnectManager 初始化完成" ) ;
	
	// 登录流程管理器
	bRet	= g_pProcessManager->Init();
	Assert(bRet);
	Log::SaveLog( LOGIN_LOGFILE, "ProcessManager 初始化完成" ) ;

	// 线程管理器
	bRet = g_pThreadManager->Init( ) ;
	Assert( bRet ) ;
	Log::SaveLog( LOGIN_LOGFILE, "ThreadManager 初始化完成" ) ;

	bRet = g_pDBThreadManager->Init();
	Assert(bRet);
	Log::SaveLog( LOGIN_LOGFILE, "DBThreadManager 初始化完成" ) ;

	bRet = g_CharConfig.Init();
	Assert(bRet);
	Log::SaveLog( LOGIN_LOGFILE, "CharConfig 初始化完成" ) ;

	//if (g_Config.m_LoginInfo.m_AskAuthType != _LOGIN_INFO::USE_BILLING)
	//{
		//bRet = g_ClientMain.InIt(g_Config.m_LoginInfo.m_ClientMainPath);
		//Assert(bRet);
		//Log::SaveLog( LOGIN_LOGFILE, "g_ClientMain->InIt()...OK" ) ;
	//}


	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

VOID	Login::Stop()
{
	__ENTER_FUNCTION

		if( g_pConnectManager )
		{
			g_pConnectManager->stop( ) ;
		}

	__LEAVE_FUNCTION
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

LoginExceptionHandler::LoginExceptionHandler()
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

LoginExceptionHandler g_LoginExceptionHandler;
