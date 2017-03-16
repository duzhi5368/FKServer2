
#include "../FKSvr2Server/Base/FoxLuaScript.h"

char szRootPath[MAX_PATH];
char szCurrPath[MAX_PATH];

int RemoveOnePointPath(LPSTR str,size_t len){
	char* p;
	int i=len;
	while((p = strstr(str,"/./"))!=0 ) { 
		i-=p+2-str;
		memmove(p,p+2,i+1);
	}
	return i;
}
int RemoveTwoPointPath(LPSTR str,size_t len){
	char* p;
	int i=len;
	while((p=strstr(str,"/../"))!=0) { 

		while(p>str){
			p--;
			if(*p == '\\'|| *p =='/')
				break;
		}
		i-=p+2-str;
		memmove(p,p+2,i+1);
	}
	return i;
}
int RemoveAllPointPath(LPSTR str,size_t len){
	len=RemoveTwoPointPath(str,len);
	return RemoveOnePointPath(str,len);
}
void SetRootPath(LPSTR rootPath){
	if(rootPath ==0){
		getcwd(szRootPath,MAX_PATH)	;
	}
	else{
		strcpy(szRootPath,rootPath);
	}
	register size_t len=strlen(szRootPath);
	if(szRootPath[len] == '\\' && szRootPath[len] =='/')
		szRootPath[len]='\0';
}
void GetRootPath(LPSTR rootPath){
	strcpy(rootPath,szRootPath);
}
void SetFilePath(LPSTR cPath){
	if(cPath[0]=='\\')
		cPath++;
	if(cPath[0]=='/')
		cPath++;
	strcpy(szCurrPath,cPath);
	register size_t len;
	if((len=strlen(szCurrPath))>0 && szCurrPath[len]=='\\' && szCurrPath[len]=='/'){
		szCurrPath[len]='/';
		szCurrPath[len+1]='\0';
	}
	RemoveAllPointPath(szCurrPath,len+1);
	for(int i=0;szCurrPath[i]!='\0';i++){
		if(szCurrPath[i]=='\\')
			szCurrPath[i]='/';
	}
}
void GetFilePath(LPSTR ret){
	strcpy(ret,szCurrPath);
}
LPSTR GetFullPath(LPSTR ret,LPSTR cFileName){
	if(cFileName[1]==':')
		return strcpy(ret,cFileName);

	if(cFileName[0]=='\\')
		strcpy(ret,szRootPath);
	else if(cFileName[0]=='/'){
		strcpy(ret,szRootPath);
		if(szCurrPath[0]!='.' && szCurrPath[0]!='\\')
			strcat(ret,"/");

		strcat(ret,szCurrPath);
		if(cFileName[0]!='.' || cFileName[0]!='/') return strcat(ret,cFileName);
		//		if(cFileName[0]!='\\')cFileName+=2;break;

		cFileName+=2;
	}
	else
		strcpy(ret,szRootPath);

	return strcat(ret,cFileName);
}

void FoxFile::Close()
{
	if(fp)
		fclose(fp);
	fp=0;
	ma=0;
	m_PosPointor=0;
}

BOOL FoxFile::Create(LPSTR cFileName)
{
	CHAR FullPath[MAX_PATH];
	if(fp) Close();
	GetFullPath(FullPath,cFileName);
	if(fp=fopen(FullPath,"wb+"))
		return TRUE;
	return FALSE;
}

BOOL FoxFile::Open(LPSTR cFileName)
{
	CHAR FullPath[MAX_PATH];
	if(fp) Close();
	GetFullPath(FullPath,cFileName);
	if(fp=fopen(FullPath,"rb"))
		return TRUE;
	return FALSE;
}

int FoxFile::Read(void* pBuf,size_t count)
{
	if(fp){
		m_PosPointor += fread(pBuf,1,count,fp);
	}
	return m_PosPointor;
}

int FoxFile::Write(void* pBuf,size_t count)
{
	if(fp){
		m_PosPointor += fwrite(pBuf,1,count,fp);
	}
	return m_PosPointor;
}

int FoxFile::Seek(long Offset,int BeginPos)
{
	if(fp){
		fseek(fp,Offset,BeginPos);
		m_PosPointor=ftell(fp);
		return m_PosPointor;
	}
	return -1;
}

BOOL FoxFile::Append(LPSTR cFileName)
{
	CHAR FullPath[MAX_PATH];
	if(fp) Close();
	GetFullPath(FullPath,cFileName);
	if(!(fp=fopen(FullPath,"ab")))
		return FALSE;
	Seek(0,SEEK_END);
	return TRUE;
}

int FoxFile::Tell()
{ 
	if(fp) 
		return m_PosPointor; 
	return 0;
}

int FoxFile::Size()
{ 
	if(!fp || ma==0) return 0;
	ma=Seek(0,SEEK_END);
	Seek(m_PosPointor,SEEK_SET);
	return ma;
}

//////////////////////////
BOOL FoxPakFile::IsFileInPak(){ return FALSE; }

BOOL FoxPakFile::Open(LPTSTR file)
{
	if(file == 0) return 0;
	FoxFile::Close();
	return FoxFile::Open(file);
}


////////////////////////////////
FoxLuaScript::FoxLuaScript(){
	if(m_LuaState = lua_open(1024)){
		m_IsRuning =TRUE;
		m_szScriptName[0]='\0';
		return;
	}
	m_IsRuning =FALSE;
	ScriptError(LUA_CREATE_ERROR);
}

FoxLuaScript::~FoxLuaScript(){
	Exit();
}

int	FoxLuaScript::Activate(){Execute(); return 1;}

BOOL FoxLuaScript::Init(){
	if(m_LuaState==NULL){
		if((m_LuaState=lua_open(1024)) == NULL){
			ScriptError(LUA_CREATE_ERROR);
			return FALSE;
		}
		m_UserTag=lua_newtag(m_LuaState);
	}
	RegisterStandardFunctions();
	return TRUE;
}

void FoxLuaScript::Exit(){
	if(m_LuaState!=NULL){
		lua_close(m_LuaState);
		m_LuaState=NULL;
		m_IsRuning=FALSE;
	}
}

BOOL FoxLuaScript::Load(char* FileName,char* buf , size_t bufSize)
{
	try{
		FoxPakFile fpk;
		if(fpk.Open(FileName)==FALSE)
			throw "文件打开失败";

		int fileSize=fpk.Size();
		char* pbuf;
		if( (pbuf =buf)==0 || bufSize != fileSize){
			pbuf=new char(fileSize+1);
			if(pbuf ==0) throw "分配内存失败";
			memset(pbuf,0,fileSize+1);
		}
		if(fpk.Read(pbuf,fileSize) != fileSize){
			delete pbuf;
			throw "文件读取失败";
		}
		fpk.Close();
		if(!LoadBuffer((PBYTE)pbuf,fileSize)){
			delete pbuf;
			throw "装载缓存失败";
		}
		if(!ExecuteCode()){
			delete pbuf;
			throw "脚本执行失败";
		}
		if(pbuf!=0)
			delete pbuf;
		return TRUE;
	}catch(char* message){
		FILE *f;
		f=fopen("./Log/luaerror.log","a");
		if(f!=0){			
			fprintf(f,"%s,%s\n",message,FileName);
			fclose(f);
		}
		return FALSE;
	}

}

BOOL FoxLuaScript::Compile(char* FileName){ return TRUE;}

BOOL FoxLuaScript::Execute()
{
	if(m_IsRuning ==FALSE || m_LuaState==NULL)return FALSE;
	return CallFunction(MAINFUNCTIONNAME,0,"");
}

BOOL FoxLuaScript::CallFunction(LPSTR cFuncName, int nResults, LPSTR cFormat, ...)
{
	va_list args; 
	va_start(args, cFormat); 
	return CallFunction(cFuncName,nResults,cFormat,args);
	va_end(args);
}

BOOL FoxLuaScript::RegisterFunction(LPSTR FuncName, void* Func)
{
	if( m_LuaState==0 ) return FALSE; 
	lua_pushcclosure(m_LuaState,(Lua_CFunction) Func, 0);
	lua_setglobal(m_LuaState,FuncName);
	return TRUE;
}

void FoxLuaScript::SetScriptName(LPSTR scpname){strcpy(m_szScriptName, scpname);};

int	 FoxLuaScript::GetUserTag() { return m_UserTag; };

BOOL FoxLuaScript::LoadBuffer(PBYTE pBuffer, DWORD dwLen )
{
	if(lua_compilebuffer(m_LuaState,(const char*)pBuffer,dwLen,NULL) !=0){
		ScriptError(LUA_SCRIPT_COMPILE_ERROR);
		return FALSE;
	}
	return TRUE;
}

void FoxLuaScript::SafeCallBegin(int * pIndex)
{
	if(m_LuaState==NULL)return;
	return lua_gettopindex(m_LuaState,pIndex);
}

void FoxLuaScript::SafeCallEnd (int nIndex)//恢复至调用之前栈顶位置。
{
	if(m_LuaState==NULL)return;
	return lua_settop(m_LuaState,nIndex);
}

BOOL FoxLuaScript::GetValuesFromStack(char * cFormat , ...)
{
	int Count;
	int p=0;

	if(m_LuaState==NULL || (Count=lua_gettop(m_LuaState)) == 0)
		return FALSE;

	while( cFormat[p] ) p++;

	va_list args; 
	va_start(args, cFormat);

	if(p!=0 && Count >= p){
		Count=Count -p+1;
		int i=0;
		for(char c=cFormat[i];c!=0;c=cFormat[++i]){
			if(c=='s'){
				if(va_arg(args, int) == 0 )
					return FALSE;
				if(lua_isstring(m_LuaState,Count) ==0){
					ScriptError(LUA_SCRIPT_NOT_STRING_ERROR);
					break;
				}
				va_arg(args, char*)=(char*)lua_tostring(m_LuaState,Count++);

				args+=4;
			}
			else if(c=='n' || c =='d'){
				if(va_arg(args, int) == 0 )
					break;
				if(lua_isnumber(m_LuaState,Count) ==0){
					ScriptError(LUA_SCRIPT_NOT_NUMBER_ERROR);
					break;
				}
				if(c=='n')
					va_arg(args, int)=(INT)lua_tonumber(m_LuaState,Count++);
				else
					va_arg(args, double)=lua_tonumber(m_LuaState,Count++);

				args+=4;
			}
		}
	}

	va_end(args);
	return FALSE;
}		

BOOL FoxLuaScript::Stop()
{
	if(m_IsRuning==FALSE)return TRUE;
	if( m_LuaState ==0 )
		return FALSE; 
	m_IsRuning=FALSE;
	return TRUE;
}

BOOL FoxLuaScript::Resume()
{
	if(m_IsRuning || m_LuaState == NULL) return FALSE;
	return TRUE;
}

DWORD FoxLuaScript::CreateTable()
{
	int rr;
	int r=lua_gettop(m_LuaState);
	lua_newtable(m_LuaState);
	if(r+1==(rr=lua_gettop(m_LuaState)))
		return -1;
	return rr;
}

DWORD FoxLuaScript::ModifyTable(LPSTR szTableName)
{
	if(szTableName[0]=='\0')
		return -1;
	int rr;
	int r=lua_gettop(m_LuaState);
	lua_getglobal(m_LuaState,szTableName);
	if(r+1==(rr=lua_gettop(m_LuaState)))
		return -1;
	return rr;
}

void FoxLuaScript::SetGlobalName(LPSTR szName)
{
	if(szName == 0) return;
	lua_setglobal(m_LuaState,szName);
}

void FoxLuaScript::ScriptError(int Error)
{
	FILE *f;
	f=fopen("./Log/luaerror.log","a");
	if(f==0)
		return;
	fprintf(f,"ScriptError %d:[%d] (%s) \n",Error,m_szScriptName);
	fclose(f);
}

void FoxLuaScript::ScriptError(int a, int b)
{
	FILE *f;
	f=fopen("./Log/luaerror.log","a");
	if(f==0)
		return;
	fprintf(f,"ScriptError %d:[%d] (%s) \n",b,a,m_szScriptName);
	fclose(f);
}

BOOL FoxLuaScript::ExecuteCode()
{
	if(m_IsRuning ==FALSE || m_LuaState==NULL || lua_execute(m_LuaState)==0){
		ScriptError(LUA_SCRIPT_EXECUTE_ERROR);
		return FALSE;
	}
	return TRUE;
}

BOOL FoxLuaScript::CallFunction(LPSTR cFuncName, int nResults, LPSTR cFormat, va_list vlist)
{
	if (m_IsRuning == FALSE || m_LuaState==NULL )
	{
		ScriptError(LUA_SCRIPT_STATES_IS_NULL);
		return FALSE;
	}
	lua_getglobal(m_LuaState,cFuncName);
	int narg=0;

	for(int v=0;cFormat[v] != 0;v++)
	{
		unsigned char c=cFormat[v]-0x4e;
		if(c < 28)
		{
			switch(c)
			{
			case 0:lua_pushnil(m_LuaState);
			case 24:lua_pushcclosure(m_LuaState,va_arg(vlist,Lua_CFunction),0);break;
			case 22:lua_pushnumber(m_LuaState,(float)va_arg(vlist,float));//4456
			case 32:lua_pushnumber(m_LuaState,va_arg(vlist,double));//442a
			case 34:lua_pushusertag(m_LuaState,va_arg(vlist,void*),m_UserTag);break;
			case 37:lua_pushstring(m_LuaState,va_arg(vlist,char*));break;
			case 40:lua_pushvalue(m_LuaState,(int)va_arg(vlist,float));break;
			}
			narg++;
		}
	}
	if(lua_call(m_LuaState,narg,nResults)== 0) return TRUE;
	ScriptError(LUA_SCRIPT_EXECUTE_ERROR);
	return FALSE;		
}

/*
#include "../FKSvr2Server/Base/FoxLuaScript.h"

// http://tpgame.googlecode.com/svn-history/r31/trunk/GServerEngine/GameAi/GameAi/Script/LuaScript.cpp

#define  LUA_OUTERRMSG(STR ) \
	fprintf( stderr, STR )


	/// 构造函数
	FoxLuaScript::FoxLuaScript()
	{
		m_LuaState  = lua_open( 100 );

		if ( m_LuaState == NULL )
		{
			ScriptError( LUA_CREATE_ERROR );
			m_IsRuning = false;
			return ;
		}

		m_IsRuning = true;
		m_szScriptName[0] = '\0';
	}

	/// 析构函数
	FoxLuaScript::~FoxLuaScript()
	{
		Exit();
	}

	bool FoxLuaScript::LoadBuffer(unsigned char *pBuffer, size_t dwLen)
	{
		if ( dwLen < 0 )
		{
			ScriptError( LUA_SCRIPT_LEN_ERROR );
			return false;
		}

		//prase_buffer()
		if ( luaL_loadbuffer(m_LuaState , (char*)pBuffer , dwLen , 0) != 0 )
		{
			ScriptError( LUA_SCRIPT_COMPILE_ERROR );
			return false;
		}
		return true;
	}

	bool  FoxLuaScript::Load(const char *FileName)
	{
		try
		{
			if( !m_LuaState )
				return false;
			if ( !luaL_loadfile(m_LuaState , FileName))
			{
				ScriptError( LUA_SCRIPT_COMPILE_ERROR );
				return false;
			}
		}
		catch( ... )
		{
			return false;
		}

		//if ( !ExecuteCode() )
		//	return false;
		return true;
	}

	/// 执行
	bool FoxLuaScript::Execute()
	{
		if( m_IsRuning && m_LuaState )
			return CallFunction("main", 0 , "" );
		
		return false;
	}

	/// 执行
	bool FoxLuaScript::ExecuteCode()
	{
		if ( !( m_IsRuning && m_LuaState ))
		{
			ScriptError( LUA_SCRIPT_EXECUTE_ERROR );
			return false;
		}

		int  state ; //lua_execute
		if ( state = lua_pcall (m_LuaState,0,LUA_MULTRET,0) != 0 )
		{
			ScriptError( LUA_SCRIPT_EXECUTE_ERROR , state );
			return false;
		}
		return true;
	}


	// * 函数:	CallFunction
	// * 功能:	调用Lua脚本内的函数
	// * 参数:	char* cFuncName
	// * 参数:	int   nResults
	// * 参数:	char* cFormat  调用时所传参数的类型
	// *			n:数字型(double) d:整形(int) s:字符串型 f:C函数型  
	//            n:Nil v:Value p:Point v形为Lua支持的
	//            参数为整形的数index，指明将index所指堆栈的变量作为该函数的调用参数。	
	// *	注意：由于该函数有不定参数…,对于数字，系统并不确定数是以double还是以int
	// *  存在，两种保存形式是不同的。因此需要注意当传入的数是整形时，格式符应用d
	// *  而不能用n,或者强行改变为double形。否则会出现计算的错误。  

	bool  FoxLuaScript::CallFunction(const char* cFuncName , int nResults ,
									char* cFormat, va_list vlist)
	{

		double nNumber ;
		char*  cString =  NULL;
		void*  pPoint  =  NULL;
		
		lua_CFunction   CFunc;
		
		int    i = 0 , nArgNum = 0 , nIndex = 0 , nRetcode = 0;

		if ( ! (m_IsRuning && m_LuaState) )
		{
			ScriptError( LUA_SCRIPT_STATES_IS_NULL  );
			return false;
		}

		lua_getglobal( m_LuaState , cFuncName );

		while ( cFormat[i] != '\0' )
		{
			switch ( cFormat[i] )
			{
				/// double 
			case 'n':
				{
					nNumber = va_arg( vlist ,double);
					lua_pushnumber( m_LuaState , nNumber );
					nArgNum ++ ;
				}
				break;

				///  int 
			case 'd':
				{
					nNumber = (double)(va_arg(vlist, int));
					lua_pushnumber(m_LuaState, (double) nNumber);
					nArgNum ++;
				}
				break;

				///  string
			case 's':
				{
					cString = va_arg(vlist, char *);
					lua_pushstring(m_LuaState, cString);
					nArgNum ++;							
				}
				break;

				/// Null
			case 'N':
				{
					lua_pushnil(m_LuaState);
					nArgNum ++;
				}
				break;

				/// call function
			case 'f':
				{
					CFunc = va_arg(vlist, lua_CFunction);
					lua_pushcfunction(m_LuaState, CFunc) ;
					nArgNum ++;
				}
				break;
				
				/// 输入的是堆栈中Index为nIndex的数据类型
			case 'v':
				{
					nNumber = va_arg(vlist, int);
					int nIndex1 = (int) nNumber;
					lua_pushvalue(m_LuaState, nIndex1);
					nArgNum ++;
				}
				break;

				/// 输入为一Table类型
			case 't':
				{

				}
				break;

			case 'p':
				{
					pPoint = va_arg(vlist, void *);

					/// Lua_PushUserTag(m_LuaState, pPoint,m_UserTag);
					nArgNum ++;
				}
				break;
			}
			i++;	
		}

		lua_call( m_LuaState , nArgNum , nResults );
		if ( nRetcode != 0 )
		{
			ScriptError( LUA_SCRIPT_EXECUTE_ERROR , nRetcode );
			return false;
		}
		return true;
	}


	bool FoxLuaScript::CallFunction(const char* cFuncName, int nResults, char* cFormat, ...)
	{
		bool    bResult  = false;
		va_list vlist;
		va_start(vlist, cFormat);
		bResult = CallFunction(cFuncName, nResults, cFormat, vlist);
		va_end(vlist);
		return bResult;
	}

	///
	///  CLuaScript::GetValuesFromStack 从堆栈中获得变量
	/// 
	bool FoxLuaScript::GetValuesFromStack(const char * cFormat, ...)	
	{
		va_list vlist;
		double* pNumber = NULL;
		const char **   pString ;
		int * pInt = NULL;
		int i = 0;
		int nTopIndex = 0;
		int nIndex = 0;	  

		/// cFormat的字符长度，表示需要取的参数数量
		int nValueNum = 0;

		if (! m_LuaState)
			return false;

		/// Lua_GetTopIndex
		nTopIndex = lua_gettop(m_LuaState);	
		nValueNum = strlen(cFormat);
		
		/// 当堆栈中无数据或不取参数是返回false
		if (nTopIndex == 0 || nValueNum == 0)
			return false;

		if (nTopIndex < nValueNum)
			return false;

		nIndex = nTopIndex - nValueNum +1;
		{
			va_start(vlist, cFormat);     
			while (cFormat[i] != '\0')
			{
				switch(cFormat[i])
				{					
					/// 返回值为数值形,Number,此时Lua只传递double形的值
				case 'n':
					{
						pNumber = va_arg(vlist, double *);
						if (pNumber == NULL)
							return false;

						if (lua_isnumber(m_LuaState, nIndex ))
						{
							* pNumber = lua_tonumber(m_LuaState, nIndex ++ );
						}
						else
						{
							ScriptError(LUA_SCRIPT_NOT_NUMBER_ERROR);
							return false;
						}
					}
					break;
				case 'd':
					{
						pInt = va_arg(vlist, int *);
						if (pInt == NULL)
							return false;
						if ( lua_isnumber(m_LuaState, nIndex))
						{
							* pInt = (int ) lua_tonumber(m_LuaState, nIndex ++);
						}
						else
						{
							ScriptError(LUA_SCRIPT_NOT_NUMBER_ERROR);
							return false;
						}
					}
					break;
				case 's'://字符串形
					{
						pString = va_arg(vlist, const char **);

						if (pString == NULL)
							return false;

						if (lua_isstring(m_LuaState, nIndex))
						{
							(*pString) = (const char *)lua_tostring(m_LuaState, nIndex++);
						}
						else
						{
							ScriptError(LUA_SCRIPT_NOT_STRING_ERROR);
							return false;
						}
					}
					break;
				}

				i ++;	
			}
			va_end(vlist);

		}
		return	true;
	}

	/// 初始化脚本对象，注册系统标准函数库
	bool FoxLuaScript::Init( lua_State* LuaMain)
	{
		if (! m_LuaState)
		{
			m_LuaState				= lua_newthread( LuaMain );

			if (m_LuaState == NULL)
			{
				ScriptError(LUA_CREATE_ERROR);
				m_IsRuning			= false;
				return false;
			}

			m_IsRuning				= true;
			m_szScriptName[0]		= '\0';
			//m_UserTag = lua_newtag(m_LuaState)	;
		}

		RegisterStandardFunctions();
		return	true;
	}

	//---------------------------------------------------------------------------
	// 函数:	CLuaScript::RegisterFunction
	// 功能:	注册某内部C函数至脚本中
	// 参数:	char* FuncName  在脚本中使用的函数名
	// 参数:	void* Func    实际相应的C函数指针
	// 参数:	int Args = 0 //与KScript接口相容，无用
	// 参数:	int Flag = 0 //与KScript接口相容, 无用
	//---------------------------------------------------------------------------
	bool FoxLuaScript::RegFunction(const char* FuncName , void* Func)
	{
		if (! m_LuaState)
			return false;
		lua_register(m_LuaState, FuncName, (lua_CFunction)Func);
		return true;
	}

	bool FoxLuaScript::Compile(const char *filename)
	{
		Load(filename);
		return true;
	}

	// 功能:	批量注册Lua的内部C函数，各个函数的信息保存在reg_luafun的数据中
	// 参数:	reg_luafun *Funcs 数组的指针
	// 参数:	int n 函数数量。可以为零，由系统计算得到。
	bool FoxLuaScript::RegisterFun(reg_luafun Funcs[], int n)
	{
		if (! m_LuaState)	return false;
		if (n == 0)	n = sizeof(Funcs) / sizeof(Funcs[0]);
		for (int i = 0; i < n; i ++)	lua_register(m_LuaState, Funcs[i].name, Funcs[i].func);
		return true;
	}

	/// 注册Lua系统标准的函数库
	void FoxLuaScript::RegisterStandardFunctions()
	{
		if (! m_LuaState)		return ;
		luaL_openlibs( m_LuaState );  

// 		lua_baselibopen(m_LuaState);//Lua基本库
// 		Lua_OpenIOLib(m_LuaState);//输入输出库
// 		Lua_OpenStrLib(m_LuaState);//字符串处理库
// 		Lua_OpenMathLib(m_LuaState);//数值运算库
// 		//Lua_OpenDBLib(m_LuaState);//调试库
		return;	
	}


	//---------------------------------------------------------------------------
	// 函数:	CLuaScript::ReleaseScript
	// 功能:	释放该脚本资源。
	// 返回:	bool 
	//---------------------------------------------------------------------------
	void FoxLuaScript::Exit()
	{
		if (! m_LuaState)		return ;
		lua_close(m_LuaState);
		m_LuaState = NULL;
		m_IsRuning = false;
	}

	template < typename  type>
	type FoxLuaScript::PopLuaNumber( const char* vPar)
	{
		lua_settop( m_LuaState , 0 );

		lua_getglobal( m_LuaState, vPar);

		if ( !lua_isnumber(m_LuaState ,1) )
		{
			ScriptError(LUA_SCRIPT_NOT_NUMBER_ERROR);
			return 0;
		}

		type val = (type)lua_tonumber(  m_LuaState , 1 );

		lua_pop(m_LuaState , 1 );

		return val;
	}

	std::string FoxLuaScript::PopLuaString( const char* vPar)
	{
		lua_settop( m_LuaState , 0 );

		lua_getglobal( m_LuaState, vPar);

		if ( !lua_isstring(m_LuaState ,1) )
		{
			ScriptError(LUA_SCRIPT_NOT_STRING_ERROR);
			return 0;
		}

		std::string str = lua_tostring(  m_LuaState , 1 );

		lua_pop(m_LuaState , 1 );

		return str;
	}

	bool FoxLuaScript::PopLuaBoolean( const char* vPar)
	{
		lua_settop( m_LuaState , 0 );

		lua_getglobal( m_LuaState, vPar);

		if ( !lua_isboolean(m_LuaState ,1) )
		{
			ScriptError(LUA_SCRIPT_NOT_BOOLEN_ERROR);
			return 0;
		}

		bool val = (bool)lua_toboolean( m_LuaState , 1 );

		lua_pop(m_LuaState , 1 );

		return val;
	}

	void FoxLuaScript::ScriptError(int Error)
	{
		char lszErrMsg[200];
		sprintf(lszErrMsg, "ScriptError %d. (%s) \n", Error, m_szScriptName);
		LUA_OUTERRMSG(lszErrMsg);
		return;
	}

	void FoxLuaScript::ScriptError(int Error1 ,int Error2)
	{
		char lszErrMsg[200];
		sprintf(lszErrMsg, "ScriptError %d:[%d] (%s) \n", Error1, Error2, m_szScriptName);
		LUA_OUTERRMSG(lszErrMsg);
		return;
	}

	bool FoxLuaScript::RunLuaSrcipt(const char* FileName)
	{
		if (int error = luaL_dofile(m_LuaState, FileName) != 0)
		{
			//throw std::runtime_error("ERROR(" + ttos(error) + "): Problem with lua script file " + FileName);
			char lszErrMsg[200];
			sprintf(lszErrMsg, "runtime_error %d (%s) \n", error,  FileName);
			LUA_OUTERRMSG(lszErrMsg);
			return false;
		}
		return true;
	}

	//---------------------------------------------------------------------------
	// 函数:	CLuaScript::SafeCallBegin
	// SafeCallBegin与SafeCallEnd两函数应搭配使用，以防止在调用Lua的外部函数之后，
	// 有多余数据在堆栈中未被清除。达到调用前与调用后堆栈的占用大小不变。
	// 上述情况只需用在调用外部函数时，内部函数不需如此处理。
	void FoxLuaScript::SafeCallBegin(int * pIndex)
	{
		if (! m_LuaState)		return ;
		//lua_gettopindex(m_LuaState, pIndex);
	}

	void FoxLuaScript::SafeCallEnd(int nIndex)
	{
		if (! m_LuaState)	return;
		//Lua_SafeEnd(m_LuaState, nIndex);
	}

	bool FoxLuaScript::Stop(void)
	{
		if (! m_IsRuning)		return true;
		if (! m_LuaState)		return false;
		m_IsRuning =  false;
		return true;
	}

	// 函数:	CLuaScript::ResumeScript
	// 功能:	恢复已中止的脚本
	bool FoxLuaScript::Resume(void)
	{
// 		if ((! m_IsRuning) && (m_LuaState))
// 		{
// 			m_IsRuning = true;
// 			return true;
// 		}
// 		return false;

		return lua_resume( m_LuaState, 0 );
	}


	// 功能:	建立一个Lua的Table，在调用该函数并设置Table各个成员之后，必须调用
	//			SetGlobalName()来给这个Table指定一个名字。
	// 返回:	size_t 
	size_t FoxLuaScript::CreateTable()
	{
		int nIndex = 0;

		nIndex = lua_gettop(m_LuaState) ;
		lua_newtable(m_LuaState);
		if (lua_gettop(m_LuaState) != ++nIndex ) 
			return -1;

		return nIndex;
	}

	void FoxLuaScript::SetGlobalName(const char* szName)
	{
		if (!szName) return ;
		lua_setglobal(m_LuaState, szName);
	}

	size_t FoxLuaScript::ModifyTable(const char* szTableName) 
	{
		if (! szTableName[0])		return -1;

		int nIndex = lua_gettop(m_LuaState);

		lua_gettable(m_LuaState, nIndex);

		if (lua_gettop(m_LuaState) != ++nIndex)		return -1;

		return nIndex;
	}
	*/