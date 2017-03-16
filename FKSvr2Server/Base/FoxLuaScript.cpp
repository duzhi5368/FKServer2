#include "stdafx.h"

#include "FoxLuaScript.h"

//struct tagmem{
//	DWORD a;
//	tagmem* pre;
//	tagmem* next;
//	DWORD d;//10h
//	DWORD e;
//};
//tagmem* m_MemList;
//MemAlloc(tagmem* mem){
//	tagmem* k=ma(&(mem->e));
//
//	if(k==0)
//		return 0;
//
//	k->pre=0;
//	k->next=mem;
//	k->d=1234567890;
//	if(m_MemList->pre==0){
//		k->pre=m_MemList->pre;
//		k->next=m_MemList;
//		m_MemList->pre=k;
//		m_MemList->pre->next=k;
//	}
//	else{
//		k->next=0;
//	}
//	return &(k->e);
//
//}
//void MemFree(tagmem* p){
//	if (p==0 || p->d !=1234567890)
//		return;
//	if(p->next == NULL )
//		p->next->pre=p->pre;
//	if(p->pre!=0)
//		p->pre->next=p->next;
//
//	free p;
//}
//void MemCopy(void* dst,void* src,size_t size){memcpy(dst,src,size);}
//void MemCopyMmx()(void* dst,void* src,size_t size){memcpy(dst,src,size);}
//bool MemComp(void* buf1,void* buf2,size_t size){memcmp(buf1,buf2,size);}
//void MemFill(void* dst,int val,size_t size){memset();}
//void MemZero(void* buf,size_t size){memset(buf,0,size);}

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

//
// class FoxMemClass
// {
// public:
// 	FoxMemClass(){
// 		m_pBuf=0;m_Size=0;
// 	}
// 	~FoxMemClass(){Free();}
// 	tagmem* Alloc(DWORD size){
// 		if(m_Size!=p){
// 			if(m_pBuf) Free();
// 			if(m_pBuf=MemAlloc(size))
// 				m_Size=size;
// 		}
// 		return m_pBuf
// 	}
// 	void Free(){
// 		if(m_pBuf!=0)
// 			MemFree(m_pBuf);
// 		m_pBuf=0;
// 		m_Size=0;
// 	}
// 	void Zero(){
// 		if(m_pBuf) MemZero(m_pBuf,m_Size);
// 	}
// 	void Fill(BYTE val){
// 		if(m_pBuf) MemFill(m_pBuf,val,m_Size);
// 	}
// 	tagmem* m_pBuf;
// 	DWORD m_Size;
// };
//
//class FoxNode
//{
//public:
//
//};



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