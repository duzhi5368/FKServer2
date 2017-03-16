#include "stdafx.h"
// Obj_Pet_Calc.cpp

#include "GameTable.h"

#include "Obj_Pet.h"

//驯养费用＝宠物等级参量*（（宠物生命恢复量/宠物生命总量）＋（宠物恢复快乐度/100））
INT CalcPetDomesticationMoney( INT nLevel, INT nHP, INT nHPMax, INT nHappiness )
{
	FLOAT fParam = g_PetDomesticationMoneyTbl.GetDomesticationMoney( nLevel );
	return (INT)(fParam *( (((FLOAT)nHPMax - (FLOAT)nHP)/(FLOAT)nHPMax) + ((100.f - (FLOAT)nHappiness)/100.f) ));
}
