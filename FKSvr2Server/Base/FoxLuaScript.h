//---------------------------------------------------------------------------
// Script Engine by FireFox
// Desc:	
//---------------------------------------------------------------------------
#ifndef FoxLuaScript_H
#define FoxLuaScript_H
//---------------------------------------------------------------------------
#include "FoxScript.h"
#include <stdio.h>
#include <direct.h>

#ifndef __linux
	#include "Lua.h"
#else
	#include "Lua.h"
	#include <string.h>
#endif


#define MAINFUNCTIONNAME "main"
#define LUA_CREATE_ERROR 1
#define LUA_SCRIPT_LEN_ERROR 2
#define LUA_SCRIPT_COMPILE_ERROR 3
#define LUA_SCRIPT_EXECUTE_ERROR 4
#define LUA_SCRIPT_NOT_NUMBER_ERROR 10
#define LUA_SCRIPT_NOT_STRING_ERROR 11
#define LUA_SCRIPT_NOT_TABLE_ERROR 12
#define LUA_SCRIPT_STATES_IS_NULL 20

typedef struct  {
	const char *name;
	lua_CFunction func;
	
}TLua_Funcs;

int RemoveOnePointPath(LPSTR str,size_t len);
int RemoveTwoPointPath(LPSTR str,size_t len);
int RemoveAllPointPath(LPSTR str,size_t len);
void SetRootPath(LPSTR rootPath);
void GetRootPath(LPSTR rootPath);
void SetFilePath(LPSTR cPath);
void GetFilePath(LPSTR ret);
LPSTR GetFullPath(LPSTR ret,LPSTR cFileName);

class FoxFile
{
private:
	FILE* fp;
	DWORD ma;
	DWORD m_PosPointor;
	
public:
	FoxFile():fp(0),ma(0),m_PosPointor(0){};
	~FoxFile(){};

	void Close();
	BOOL Create(LPSTR cFileName);
	BOOL Open(LPSTR cFileName);
	int Read(void* pBuf,size_t count);
	int Write(void* pBuf,size_t count);
	int Seek(long Offset,int BeginPos);
	BOOL Append(LPSTR cFileName);
	int Tell();
	int Size();
};

 class FoxPakFile: public FoxFile
 {
 public:
 	FoxPakFile(){};
 	~FoxPakFile(){ FoxFile::Close();};
 
 	BOOL IsFileInPak();
 	BOOL Open(LPTSTR file);
	//static SetPakFileMode(DWORD mode){m_nPakFileMode=mode;}
	//static DWORD m_nPakFileMode;
};
//---------------------------------------------------------------------------
class  FoxLuaScript : public FoxScript//ENGINE_API
{
public:
	FoxLuaScript();
	virtual ~FoxLuaScript();
	FoxLuaScript( int StackSize);/////////////////////////////////////////////////////////////////////////////////////////////
	
	int		Activate();
	virtual BOOL Init();
	virtual void Exit();
 	virtual BOOL Load(char* FileName,char* buf =0, size_t bufSize=0);
	virtual	BOOL Compile(char* FileName);
	virtual	BOOL Execute();
	virtual	BOOL CallFunction(LPSTR cFuncName, int nResults, LPSTR cFormat, ...);
	virtual BOOL RegisterFunction(LPSTR FuncName, void* Func);
	virtual void SetScriptName(LPSTR scpname);

	int	 GetUserTag();
	BOOL RegisterFunctions( TLua_Funcs Funcs[], int n = 0 );////////////////////////////////////////////////////////////////
	BOOL LoadBuffer(PBYTE pBuffer, DWORD dwLen );
	void SafeCallBegin(int * pIndex);//记录当前堆栈栈顶位置，并保存到pIndex指向的数据中
	void SafeCallEnd (int nIndex);//恢复至调用之前栈顶位置。
	BOOL GetValuesFromStack(char * cFormat , ...);
	
	BOOL Stop();
	BOOL Resume();
	DWORD CreateTable();
	DWORD ModifyTable(LPSTR szTableName);
	void SetGlobalName(LPSTR szName);
 	inline void SetTableMember(int nIndex, int Id, const char * szString){Lua_SetTable_StringFromId(m_LuaState,  nIndex, Id, szString);};
 	inline void SetTableMember(int nIndex, int Id, double nNumber){Lua_SetTable_DoubleFromId(m_LuaState,  nIndex, Id, nNumber);};
 	inline void SetTableMember(int nIndex, int Id, int nNumber){Lua_SetTable_IntFromId(m_LuaState,  nIndex, Id, nNumber);};
 	inline void SetTableMember(int nIndex, const char * szMemberName, Lua_CFunction CFun){Lua_SetTable_CFunFromName(m_LuaState,  nIndex, szMemberName, CFun);};
 	inline void SetTableMember(int nIndex, int nId, Lua_CFunction CFun){Lua_SetTable_CFunFromId(m_LuaState,  nIndex, nId, CFun);};
 	inline void SetTableMember(int nIndex, const char * szMemberName, char * szString){Lua_SetTable_StringFromName(m_LuaState,  nIndex, szMemberName, szString);};
 	inline void SetTableMember(int nIndex, const char * szMemberName, int Number){Lua_SetTable_IntFromName(m_LuaState,  nIndex, szMemberName, Number);};
 	inline void SetTableMember(int nIndex, const char * szMemberName, double Number){Lua_SetTable_DoubleFromName(m_LuaState,  nIndex, szMemberName, Number);};
 	void ScriptError(int Error);
	void ScriptError(int a, int b);
 	BOOL ExecuteCode();


	Lua_State * m_LuaState;

private:
	void RegisterStandardFunctions(){
		if(m_LuaState==NULL) return;
		lua_baselibopen(m_LuaState);
		lua_iolibopen(m_LuaState);
		lua_strlibopen(m_LuaState);
		lua_mathlibopen(m_LuaState);
		lua_dblibopen(m_LuaState);
	}
	BOOL m_IsRuning;//是否该脚本有效
	char m_szScriptName[100];
	int	 m_UserTag;
	
private:
	BOOL CallFunction(LPSTR cFuncName, int nResults, LPSTR cFormat, va_list vlist);

};

//---------------------------------------------------------------------------
#endif //FoxLuaScript_H
