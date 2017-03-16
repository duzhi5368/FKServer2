//---------------------------------------------------------------------------
// Script Engine by FireFox
// Desc:	脚本引擎接口
//---------------------------------------------------------------------------
#ifndef FoxScript_H
#define FoxScript_H
#include "FoxWin32.h"
//---------------------------------------------------------------------------
class  FoxScript//ENGINE_API
{
public:
	FoxScript(){};
	virtual ~FoxScript(){};
	virtual BOOL Init(){ return TRUE;};
	virtual void Exit(){};
	virtual BOOL Load(char* FileName){ return TRUE;};
	virtual	BOOL Compile(char* FileName){ return TRUE;};
	virtual	BOOL Execute(){ return TRUE;};
	virtual	BOOL CallFunction(LPSTR cFuncName, int nResults, LPSTR cFormat,...){ return TRUE;};
	virtual BOOL RegisterFunction(LPSTR FuncName, void* Func){ return TRUE;};
	
};
//---------------------------------------------------------------------------
#endif  //FoxScript_H
