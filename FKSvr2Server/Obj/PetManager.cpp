#include "stdafx.h"
// PetManager.cpp

#include "Ini.h"
#include "Log.h"
#include "GameTable.h"
#include "Scene.h"
#include "Obj_Pet.h"
#include "ObjManager.h"
#include "PetManager.h"
#include "ItemOperator.h"
#include "TimeManager.h"
#define SECSIZE 64

PetManager::PetManager( VOID )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

PetManager::~PetManager( VOID )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

Obj_Pet *PetManager::GetPet( ObjID_t idObj )
{
	Obj_Pet *pPet = (Obj_Pet*)(GetScene()->GetObjManager()->GetObj( idObj ));
	if ( pPet == NULL )
	{
		return NULL;
	}

	if ( pPet->GetObjType() != Obj::OBJ_TYPE_PET )
	{
		Assert( (pPet->GetObjType() == Obj::OBJ_TYPE_PET) && "PetManager::GetPet" );
		return NULL;
	}
	return pPet;
}

BOOL PetManager::RemoveAllPet( VOID )
{
__ENTER_FUNCTION

	Scene *pScene;
	Obj_Pet *pPet;
	UINT i,uCount,uMaxCount,uLength;

	pScene		= GetScene();
	uCount		= 0;
	uMaxCount	= GetCount();
	uLength	= GetLength();

	for ( i = 0; i <uLength; i++ )
	{
		pPet = (Obj_Pet*)(GetObjByIndex( 0 ));
		if ( pPet != NULL )
		{
			pPet->SetActiveFlag( FALSE );
			pPet->CleanUp();
			pScene->DeleteObject( pPet );
			uCount++;
			if (uCount >=uMaxCount )
				break;
		}
	}
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL PetManager::RemovePet( ObjID_t idObj )
{
__ENTER_FUNCTION

	Scene* pScene = GetScene();
	if (pScene)
	{
		Obj* pPet = pScene->GetPetManager()->GetPet(idObj);
		if (pPet && pPet->GetObjType() == Obj::OBJ_TYPE_PET)
		{
			pPet->SetActiveFlag( FALSE );
			pPet->CleanUp();
			pScene->DeleteObject( pPet );
		}
	}

	return TRUE;
__LEAVE_FUNCTION
	return TRUE;
}

BOOL PetManager::CreatePet( INT nDataID, WORLD_POS* pPos, ObjID_t& rPetID )
{
__ENTER_FUNCTION
	// create new OBJ of pet
	Obj_Pet *pPet = (Obj_Pet*)(GetScene()->NewObject( Obj::OBJ_TYPE_PET ));
	if ( !pPet )
	{
		return FALSE;
	}
	// 将新创建宠物的ObjID返回
	rPetID = pPet->GetID();

	PET_ATTR* pPetAttr = g_PetAttrTbl.GetAttr(nDataID);
	if (!pPetAttr)
		return FALSE;

	MONSTER_EXT_ATTR* pMonsterExtAttr = g_MonsterAttrExTbl.GetExtAttr(nDataID);
	if (!pMonsterExtAttr)
		return FALSE;

	_OBJ_PET_INIT initPet;
	initPet.m_Pos		= *pPos;
	initPet.m_Dir		= 0.f;
	initPet.m_eLogic	= CHARACTER_LOGIC_IDLE;
	initPet.m_CreatorID	= INVALID_ID;

	InitPetDB( &initPet.m_PetDB, nDataID );
	initPet.m_GUID		= INVALID_GUID;

	// 初始化Pet
	BOOL bResult = pPet->Init( &initPet );
	if ( !bResult )
	{
		return FALSE;
	}
	
	// 激活该Pet
	pPet->SetActiveFlag( TRUE );

	return TRUE;
__LEAVE_FUNCTION
	return TRUE;
}
// 生成一个捕捉后宠物的GUID
BOOL	PetManager::CreateGUIDOfPet(_PET_DB *pPetDB, ObjID_t idHuman, ObjID_t idPet)
{
	__ENTER_FUNCTION

	Assert(idHuman != INVALID_ID && idPet != INVALID_ID && "PetManager::CreateGUIDOfPet");
	if(idHuman == INVALID_ID || idPet == INVALID_ID)
	{
		return FALSE;
	}

	Obj_Human	*pHuman;
	Obj_Pet		*pPet;

	pHuman	= GetScene()->GetHumanManager()->GetHuman(idHuman);
	pPet	= GetPet(idPet);

	Assert(pHuman != NULL && pPet != NULL && "PetManager::CreateGUIDOfPet");
	if(pHuman == NULL || pPet == NULL)
	{
		return FALSE;
	}

	PET_ATTR* pPetAttr = g_PetAttrTbl.GetAttr(pPet->GetDataID());
	if (!pPetAttr)
		return FALSE;

	PET_GUID_t guidPet, guidSpouse;
	guidPet.Init(pHuman->GetGUID(), g_pTimeManager->CurrentTime());
	guidSpouse.Reset();

	pPetDB->m_GUID					= guidPet;
	pPetDB->m_SpouseGUID			= guidSpouse;

	
	return TRUE;
__LEAVE_FUNCTION
	return FALSE;
}

BOOL PetManager::MakeCapturePetAttrib(_PET_DB *pPetDB, BOOL bNeedLevelFluctuate/*=TRUE*/, BOOL bReturnToChild/*=FALSE*/)
{
__ENTER_FUNCTION
	PET_ATTR* pPetAttr = g_PetAttrTbl.GetAttr(pPetDB->m_nDataID);
	if (!pPetAttr) {
		return FALSE;
	}
	MONSTER_EXT_ATTR *pMonsterAttr = g_MonsterAttrExTbl.GetExtAttr(pPetDB->m_nDataID);
	if (!pMonsterAttr) {
		return FALSE;
	}

	pPetDB->m_nLevel				= pPetDB->m_nLevel;
	pPetDB->m_nTakeLevel			= pPetAttr->m_TakeLevel;
	pPetDB->m_AIType				= pPetAttr->m_AI;
 	pPetDB->m_CampData.CleanUp();
	pPetDB->m_CampData.m_nCampID	= pMonsterAttr->m_Camp;
	pPetDB->m_nLife					= pPetAttr->m_Life;
	pPetDB->m_byGeneration			= 1;
	pPetDB->m_byHappiness			= 100;
	pPetDB->m_nStrPerception		= pPetAttr->m_SprPerception;
	pPetDB->m_nConPerception		= pPetAttr->m_ConPerception;
	pPetDB->m_nDexPerception		= pPetAttr->m_DexPerception;
	pPetDB->m_nSprPerception		= pPetAttr->m_SprPerception;
	pPetDB->m_nIntPerception		= pPetAttr->m_IntPerception;
	pPetDB->m_nGenGu				= 0;
	pPetDB->m_fGrowRate				= 0.f;
	pPetDB->m_nRemainPoint			= 0;
	pPetDB->m_nExp					= 0;

	CreateTypeOfPet(*pPetDB, bNeedLevelFluctuate, bReturnToChild);
	CreateAITypeOfPet(*pPetDB);
	CreateRemainPointOfPet(*pPetDB);
	CreateSkillOfPet(*pPetDB);
	CreateGrowRateOfPet(*pPetDB);
	CreatePerceptionOfPet(*pPetDB);

	FLOAT fGrowRate = 0.f;
	INT nLevel = pPetDB->m_nLevel;
	fGrowRate = pPetDB->m_fGrowRate;

	INT nBaseParam = g_TableInit.m_PetConfig.m_BaseHP;
	FLOAT fAttribRate = g_TableInit.m_PetConfig.m_Con_HP_Pram;
	FLOAT fLevelRate = g_TableInit.m_PetConfig.m_Level_HP_Pram;
	INT nAttribParam = pPetDB->m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_CON];
	INT nHP = nBaseParam + (INT)(nAttribParam*fAttribRate + nLevel*fLevelRate*fGrowRate);
	pPetDB->m_nHP		= nHP;

	return TRUE;

__LEAVE_FUNCTION

	return FALSE ;
}

// 通过DataID去付值一个PET DB
BOOL PetManager::InitPetDB( _PET_DB *pPetDB, INT nDataID )
{
__ENTER_FUNCTION

	if ( pPetDB == NULL )
		return FALSE;

	pPetDB->CleanUp();

	PET_ATTR *pPetAttr = NULL;
	MONSTER_EXT_ATTR *pMonsterAttr = NULL;
	if ( nDataID != INVALID_ID )
	{
		 pPetAttr = g_PetAttrTbl.GetAttr( nDataID );
		 pMonsterAttr = g_MonsterAttrExTbl.GetExtAttr( nDataID );
	}

	if ( pPetAttr != NULL && pMonsterAttr != NULL )
	{
		//pPetDB->m_GUID;
		pPetDB->m_SpouseGUID.Reset();
		pPetDB->m_nDataID				= nDataID;
		strncpy( pPetDB->m_szName, pMonsterAttr->m_Name, sizeof( pPetDB->m_szName ) - 1 );
		strncpy( pPetDB->m_szNick, "", sizeof( pPetDB->m_szNick ) - 1 );
		pPetDB->m_nLevel				= pMonsterAttr->m_Level;
		pPetDB->m_nTakeLevel			= pPetAttr->m_TakeLevel;
		pPetDB->m_nAttackType			= -1;
		pPetDB->m_AIType				= pPetAttr->m_AI;
		pPetDB->m_CampData.CleanUp();
		pPetDB->m_CampData.m_nCampID	= pMonsterAttr->m_Camp;
		pPetDB->m_nHP					= g_MonsterAttrExTbl.Get(nDataID, CATTR_LEVEL2_MAXHP);
		pPetDB->m_nLife					= pPetAttr->m_Life;
		//pPetDB->m_byPetType;
		pPetDB->m_byGeneration			= 0;
		pPetDB->m_byHappiness			= 100;

		pPetDB->m_nStrPerception		= pPetAttr->m_SprPerception;
		pPetDB->m_nConPerception		= pPetAttr->m_ConPerception;
		pPetDB->m_nDexPerception		= pPetAttr->m_DexPerception;
		pPetDB->m_nSprPerception		= pPetAttr->m_SprPerception;
		pPetDB->m_nIntPerception		= pPetAttr->m_IntPerception;
		pPetDB->m_nGenGu				= 0;
		//pPetDB->m_fGrowRate				= 0.f;
		pPetDB->m_nRemainPoint			= 0;
		pPetDB->m_nExp					= 0;

		pPetDB->m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_STR]		= -1;
		pPetDB->m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_SPR]		= -1;
		pPetDB->m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_CON]		= -1;
		pPetDB->m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_INT]		= -1;
		pPetDB->m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_DEX]		= -1;

		pPetDB->m_SkillList[PET_SKILL_INDEX_CONTROL_BY_PLAYER].m_nSkillID	= pPetAttr->m_VoluntarySkill;
		pPetDB->m_SkillList[PET_SKILL_INDEX_CONTROL_BY_AI0].m_nSkillID		= pPetAttr->m_PassiveSkill1;
		pPetDB->m_SkillList[PET_SKILL_INDEX_CONTROL_BY_AI1].m_nSkillID		= pPetAttr->m_PassiveSkill2;
		pPetDB->m_SkillList[PET_SKILL_INDEX_CONTROL_BY_AI2].m_nSkillID		= pPetAttr->m_PassiveSkill3;
		pPetDB->m_SkillList[PET_SKILL_INDEX_CONTROL_BY_AI3].m_nSkillID		= pPetAttr->m_PassiveSkill4;
		pPetDB->m_SkillList[PET_SKILL_INDEX_MENPAI].m_nSkillID				= INVALID_ID;
	}
	return TRUE;

__LEAVE_FUNCTION

	return FALSE ;
}
VOID	PetManager::CreateAITypeOfPet(_PET_DB& rPetDB)
{
__ENTER_FUNCTION
	INT idData = rPetDB.m_nDataID; 
	INT& rAIType = rPetDB.m_AIType;

	PET_ATTR* pAttr = g_PetAttrTbl.GetAttr(idData);
	if (!pAttr)
	{
		Assert(NULL && "PetManager::CreateAITypeOfPet...g_PetAttrTbl.GetAttr(idData) = NULL...");
		return ;
	}
	// (1/1000)
	INT nCowardiceRate	= pAttr->m_CowardiceRate;
	INT nWarinessRate	= nCowardiceRate + pAttr->m_WarinessRate;
	INT nLoyalismRate	= nWarinessRate + pAttr->m_LoyalismRate;
	INT nCanninessRate	= nLoyalismRate + pAttr->m_CanninessRate;
	INT nValourRate		= nCanninessRate + pAttr->m_ValourRate;

	INT nRet = RandGen::GetRand(0, 1000);
	if (nRet < nCowardiceRate) {
		rAIType = _PET_DB_LOAD::PET_AI_COWARDICE;	// 胆小
	}												
	else if (nRet < nWarinessRate) {				
		rAIType = _PET_DB_LOAD::PET_AI_WARINESS;	// 谨慎	
	}												
	else if (nRet < nLoyalismRate) {
		rAIType = _PET_DB_LOAD::PET_AI_LOYALISM;	// 忠诚
	}
	else if (nRet < nCanninessRate) {
		rAIType = _PET_DB_LOAD::PET_AI_CANNINESS;	// 精明
	}
	else{
		rAIType = _PET_DB_LOAD::PET_AI_VALOUR;		// 勇猛
	}


__LEAVE_FUNCTION
}

VOID PetManager::CreateTypeOfPet(_PET_DB& rPetDB, BOOL bNeedLevelFluctuate, BOOL bReturnToChild)
{
__ENTER_FUNCTION

	INT& idData = rPetDB.m_nDataID;
	BYTE &byType = rPetDB.m_byPetType;
	INT &nLevel = rPetDB.m_nLevel;
	INT &nRemainPoint = rPetDB.m_nRemainPoint;	
	// 进行还童处理
	if (TRUE == bReturnToChild)
	{
		nLevel = 1;
		byType = _PET_DB_LOAD::PET_TYPE_BABY; // 设置成纯宝宝
		nRemainPoint = 50 + (nLevel - 1) * 8;
		return;
	}
    // 等级不进行波动处理
	if (FALSE == bNeedLevelFluctuate)
	{
		if (nLevel <= 0)
			nLevel = 1;
		nRemainPoint = 50 + (nLevel - 1) * 8;
		return;
	}
	INT nRet = RandGen::GetRand(0, 1000);
	INT nBabyRate = g_TableInit.m_PetConfig.m_BabyPetRate;
	INT nVarianceRate = g_TableInit.m_PetConfig.m_VariancePetRate;

	//if (nRet < nVarianceRate)
	//{
	//	byType = _PET_DB_LOAD::PET_TYPE_VARIANCE;
	//	nLevel = 1;

	//	UINT uDataID = idData;
	//	INT nRet = RandGen::GetRand(0, 100000);// 单位为10w
	//	for (INT i = 0; i < SPetConfig::VARIANCEPET_LEVEL_NUM; ++i)
	//	{
	//		if (nRet < g_TableInit.m_PetConfig.m_aRateOfLevelVariancePet[i])
	//		{
	//			uDataID += i+1;
	//			break;
	//		}
	//	}
	//	// 一种宠物必然有一种变异类型
	//	PET_ATTR* pPetAttr = g_PetAttrTbl.GetAttr(uDataID);
	//	if (pPetAttr)
	//	{
	//		if (pPetAttr->m_Name[0] != '\0')
	//			idData = uDataID;
	//		else
	//			idData = uDataID + 1;
	//	}
	//	else
	//	{
	//		idData = uDataID + 1;
	//	}
	//}

	if ((UINT)idData > g_PetAttrTbl.m_MaxType)
	{// 类型范围判断
		return;
	}
	if (TRUE == g_PetAttrTbl.m_TableExt[idData].m_bVarPet)
	{// 是变异宠物
		byType = _PET_DB_LOAD::PET_TYPE_VARIANCE;
		nLevel = 1;
	}
	else if (TRUE == g_PetAttrTbl.m_TableExt[idData].m_bBabyPet)
	{// 是宝宝宠物
		byType = _PET_DB_LOAD::PET_TYPE_BABY;
		nLevel = 1;
	}
	else
	{// 是野生宠物
		byType = _PET_DB_LOAD::PET_TYPE_WILENESS;

		INT nTakeLevelRate = g_TableInit.m_PetConfig.m_WilenessPetRate_TakeLevel;
		INT	nLowOneLevelRate = nTakeLevelRate + g_TableInit.m_PetConfig.m_WilenessPetRate_Delta1;
		INT nUpOneLevelRate	= nLowOneLevelRate + g_TableInit.m_PetConfig.m_WilenessPetRate_Delta1;
		INT nLow2LevelRate = nUpOneLevelRate + g_TableInit.m_PetConfig.m_WilenessPetRate_Delta2;
		INT nUp2LevelRate = nLow2LevelRate + g_TableInit.m_PetConfig.m_WilenessPetRate_Delta2;
		INT nLow3LevelRate = nUp2LevelRate + g_TableInit.m_PetConfig.m_WilenessPetRate_Delta3;
		INT nUp3LevelRate = nLow3LevelRate + g_TableInit.m_PetConfig.m_WilenessPetRate_Delta3;

		nRet = RandGen::GetRand(0, 100);
		if (nRet < nTakeLevelRate)
		{
			;
		}
		else if (nRet < nLowOneLevelRate)
		{
			--nLevel;
		}
		else if (nRet < nUpOneLevelRate)
		{
			++nLevel;
		}
		else if (nRet < nLow2LevelRate)
		{
			nLevel -= 2;
		}
		else if (nRet < nUp2LevelRate)
		{
			nLevel += 2;
		}
		else if (nRet < nLow3LevelRate)
		{
			nLevel -= 3;
		}
		else
		{
			nLevel += 3;
		}
	}
	if (nLevel <= 0)
		nLevel = 1;
		
	// 公式50+（lv－1）*8得出宠物初始属性点的总数
	nRemainPoint = 50 + (nLevel - 1) * 8;

__LEAVE_FUNCTION
}

VOID PetManager::CreateRemainPointOfPet(_PET_DB& rPetDB)
{
__ENTER_FUNCTION

	INT &nRemainPoint = rPetDB.m_nRemainPoint;
	_ATTR_LEVEL1 &baseAttrLevel1 = rPetDB.m_BaseAttrLevel1;

	INT nCount = g_PetAttrPointDisTbl.m_Count;
	INT nRet = RandGen::GetRand(0, nCount);

	Assert(nRet < nCount);
	
	INT nStrRate = g_PetAttrPointDisTbl.GetAttrDisRate(CATTR_LEVEL1_STR, nRet);
	INT nConRate = g_PetAttrPointDisTbl.GetAttrDisRate(CATTR_LEVEL1_CON, nRet);
	INT nSprRate = g_PetAttrPointDisTbl.GetAttrDisRate(CATTR_LEVEL1_SPR, nRet);
	INT nDexRate = g_PetAttrPointDisTbl.GetAttrDisRate(CATTR_LEVEL1_DEX, nRet);
	INT nIntRate = 1000 - nStrRate - nConRate - nSprRate - nDexRate;

	baseAttrLevel1.m_pAttr[CATTR_LEVEL1_STR] = (nRemainPoint * nStrRate) / 1000;
	baseAttrLevel1.m_pAttr[CATTR_LEVEL1_SPR] = (nRemainPoint * nConRate) / 1000;
	baseAttrLevel1.m_pAttr[CATTR_LEVEL1_CON] = (nRemainPoint * nSprRate) / 1000;
	baseAttrLevel1.m_pAttr[CATTR_LEVEL1_INT] = (nRemainPoint * nDexRate) / 1000;
	INT nDistributed = baseAttrLevel1.m_pAttr[CATTR_LEVEL1_STR] + baseAttrLevel1.m_pAttr[CATTR_LEVEL1_SPR] + baseAttrLevel1.m_pAttr[CATTR_LEVEL1_CON] + baseAttrLevel1.m_pAttr[CATTR_LEVEL1_INT];
	baseAttrLevel1.m_pAttr[CATTR_LEVEL1_DEX]  = nRemainPoint - nDistributed;

	nRemainPoint = 0;

__LEAVE_FUNCTION
}

VOID PetManager::CreateSkillOfPet(_PET_DB& rPetDB)
{
__ENTER_FUNCTION
#define MAX_RANG_VALUE (1000000)
#define RAND_COUNT (5)
	INT idData = rPetDB.m_nDataID;
	_PET_SKILL *paSkillList = rPetDB.m_SkillList;

	INT nIndex = 0;
	INT n;
	for (n = 0; n < PET_MAX_NUM; ++n)
	{
		if (g_PetSkillDistrTbl[n].m_PetID == idData)
		{
			nIndex = n;
			break;
		}
	}

    if (n == PET_MAX_NUM)
	{
		Assert(FALSE && "idData ... not found!");
		return ;
	}

	INT nRangeA = g_PetSkillDistrTbl[nIndex].m_Table[0].m_nSkillRange;
	INT nRangeB = nRangeA + g_PetSkillDistrTbl[nIndex].m_Table[1].m_nSkillRange;
	INT nRangeC = nRangeB + g_PetSkillDistrTbl[nIndex].m_Table[2].m_nSkillRange;
	INT nRangeD = nRangeC + g_PetSkillDistrTbl[nIndex].m_Table[3].m_nSkillRange;
	INT nRangeE = nRangeD + g_PetSkillDistrTbl[nIndex].m_Table[4].m_nSkillRange;

	
	for (INT i = 0; i < RAND_COUNT; ++i)
	{
		INT nRet = RandGen::GetRand(0, MAX_RANG_VALUE);
		if (nRet <= nRangeA)
		{// 0~a
			INT nSkillIndex = g_PetSkillDistrTbl[nIndex].m_Table[0].m_nSkillIndex;
			AddPetSkill(paSkillList, nSkillIndex);
		}
		else if (nRet <= nRangeB)
		{// a+1~b
			INT nSkillIndex = g_PetSkillDistrTbl[nIndex].m_Table[1].m_nSkillIndex;
			AddPetSkill(paSkillList, nSkillIndex);
		}
		else if (nRet <= nRangeC)
		{// a+b+1~c
			INT nSkillIndex = g_PetSkillDistrTbl[nIndex].m_Table[2].m_nSkillIndex;
			AddPetSkill(paSkillList, nSkillIndex);
		}
		else if (nRet <= nRangeD)
		{// a+b+c+1~d
			INT nSkillIndex = g_PetSkillDistrTbl[nIndex].m_Table[3].m_nSkillIndex;
			AddPetSkill(paSkillList, nSkillIndex);
		}
		else if (nRet <= nRangeE)
		{// a+b+c+d+1~e
			INT nSkillIndex = g_PetSkillDistrTbl[nIndex].m_Table[4].m_nSkillIndex;
			AddPetSkill(paSkillList, nSkillIndex);
		}
		else
		{// a+b+c+d+e~∑
		}
	}
__LEAVE_FUNCTION
}

VOID PetManager::CreateGrowRateOfPet(_PET_DB& rPetDB)
{
__ENTER_FUNCTION

	INT nData = rPetDB.m_nDataID;
	FLOAT &fGrowRate = rPetDB.m_fGrowRate;

	PET_ATTR* pAttr = g_PetAttrTbl.GetAttr(nData);
	
	if (!pAttr)
	{
		Assert(NULL && "PetManager::CreateGrowRateOfPet.. g_PetAttrTbl.GetAttr(idData) = NULL...");
		return ;
	}
	INT nRet = RandGen::GetRand(0, 100);
	INT nGrowRate0 = g_TableInit.m_PetConfig.m_GrowRate0;
	INT	nGrowRate1 = nGrowRate0 + g_TableInit.m_PetConfig.m_GrowRate1;
	INT	nGrowRate2 = nGrowRate1 + g_TableInit.m_PetConfig.m_GrowRate2;
	INT	nGrowRate3 = nGrowRate2 + g_TableInit.m_PetConfig.m_GrowRate3;
	INT	nGrowRate4 = nGrowRate3 + g_TableInit.m_PetConfig.m_GrowRate4;

	if (nRet < nGrowRate0)
	{
		fGrowRate = (pAttr->m_GrowRate0) / 1000.f;
	}
	else if (nRet < nGrowRate1)
	{
		fGrowRate = (pAttr->m_GrowRate1) / 1000.f;
	}
	else if (nRet < nGrowRate2)
	{
		fGrowRate = (pAttr->m_GrowRate2) / 1000.f;
	}
	else if (nRet < nGrowRate3)
	{
		fGrowRate = (pAttr->m_GrowRate3) / 1000.f;
	}
	else
	{
		fGrowRate = (pAttr->m_GrowRate4) / 1000.f;
	}
__LEAVE_FUNCTION
}

VOID PetManager::CreatePerceptionOfPet(_PET_DB& rPetDB)
{
__ENTER_FUNCTION

	INT idData = rPetDB.m_nDataID;
	INT &nStrPerception = rPetDB.m_nStrPerception;
	INT &nConPerception = rPetDB.m_nConPerception;
	INT &nSprPerception = rPetDB.m_nSprPerception;
	INT &nDexPerception = rPetDB.m_nDexPerception;
	INT &nIntPerception = rPetDB.m_nIntPerception;
	INT &nGenGu = rPetDB.m_nGenGu;

	//①可携带的物攻宠的标准资质
	PET_ATTR* pAttr = g_PetAttrTbl.GetAttr(idData);
	if (!pAttr)
	{
		Assert(NULL && "PetManager::CreatePerceptionOfPet...g_PetAttrTbl.GetAttr(idData) = NULL...");
		return ;
	}
	
	nStrPerception = pAttr->m_StrPerception;
	nConPerception = pAttr->m_ConPerception;
	nSprPerception = pAttr->m_SprPerception;
	nDexPerception = pAttr->m_DexPerception;
	nIntPerception = pAttr->m_IntPerception;

	INT nTotalPerception = nStrPerception + nConPerception + 
						nSprPerception + nDexPerception + nIntPerception;

    //②按照在标准资质90％～110％的范围内random出一个临时资质来
	INT nStrDelta = (nStrPerception * 10) / 100;
	INT nConDelta = (nConPerception * 10) / 100;
	INT nSprDelta = (nSprPerception * 10) / 100;
	INT nDexDelta = (nDexPerception * 10) / 100;
	INT nIntDelta = (nIntPerception * 10) / 100;

	nStrPerception = (nStrPerception - nStrDelta) + RandGen::GetRand(0,(2*nStrDelta));
	nConPerception = (nConPerception - nConDelta) + RandGen::GetRand(0,(2*nConDelta));
	nSprPerception = (nSprPerception - nSprDelta) + RandGen::GetRand(0,(2*nSprDelta));
	nDexPerception = (nDexPerception - nDexDelta) + RandGen::GetRand(0,(2*nDexDelta));
	nIntPerception = (nIntPerception - nIntDelta) + RandGen::GetRand(0,(2*nIntDelta));

	INT nTempPerception = nStrPerception + nConPerception + 
						nSprPerception + nDexPerception + nIntPerception;

	//③在总标准资质之和的0～5%范围内random一个奖励资质，
	INT nEncouragePer = RandGen::GetRand( 0, ((nTotalPerception * 5) / 100) );

	//④将奖励资质+（总标准资质－总临时资质）的结果（可能是负数）作为最终奖励资质，
	INT nFinallyEncouragePer = nEncouragePer + (nTotalPerception - nTempPerception);

	//⑤将最终奖励资质随机附加到宠物的某一项资质上，作为最终的奖励资质
	INT nSelectedAttr = RandGen::GetRand(0, CATTR_LEVEL1_NUMBER);
	switch (nSelectedAttr)
	{
	case CATTR_LEVEL1_STR:
		nStrPerception += nFinallyEncouragePer;
		break;
	case CATTR_LEVEL1_CON:
		nConPerception += nFinallyEncouragePer;
		break;
	case CATTR_LEVEL1_SPR:
		nSprPerception += nFinallyEncouragePer;
		break;
	case CATTR_LEVEL1_DEX:
		nDexPerception += nFinallyEncouragePer;
		break;
	case CATTR_LEVEL1_INT:
		nIntPerception += nFinallyEncouragePer;
		break;
	default:
		break;
	}

	//⑥根骨根据以下几率在相应范围段random,random出范围段后再继续在范围段里random出一个具体数值
	INT nGenGuRate0 = g_TableInit.m_PetConfig.m_vGenGu[0].m_Rate;
	INT nGenGuRate1 = nGenGuRate0 + g_TableInit.m_PetConfig.m_vGenGu[1].m_Rate;
	INT nGenGuRate2 = nGenGuRate1 + g_TableInit.m_PetConfig.m_vGenGu[2].m_Rate;
	INT nGenGuRate3 = nGenGuRate2 + g_TableInit.m_PetConfig.m_vGenGu[3].m_Rate;
	INT nGenGuRate4 = nGenGuRate3 + g_TableInit.m_PetConfig.m_vGenGu[4].m_Rate;
	
	INT nRet = RandGen::GetRand(0, 100);
	nGenGu = 0;
	INT nBegin = 0, nEnd = 0;
	if (nRet < nGenGuRate0)
	{
		nBegin = g_TableInit.m_PetConfig.m_vGenGu[0].m_Begin;
		nEnd = g_TableInit.m_PetConfig.m_vGenGu[0].m_End;
	}
	else if (nRet < nGenGuRate1)
	{
		nBegin = g_TableInit.m_PetConfig.m_vGenGu[1].m_Begin;
		nEnd = g_TableInit.m_PetConfig.m_vGenGu[1].m_End;
	}
	else if (nRet < nGenGuRate2)
	{
		nBegin = g_TableInit.m_PetConfig.m_vGenGu[2].m_Begin;
		nEnd = g_TableInit.m_PetConfig.m_vGenGu[2].m_End;
	}
	else if (nRet < nGenGuRate3)
	{
		nBegin = g_TableInit.m_PetConfig.m_vGenGu[3].m_Begin;
		nEnd = g_TableInit.m_PetConfig.m_vGenGu[3].m_End;
	}
	else
	{
		nBegin = g_TableInit.m_PetConfig.m_vGenGu[4].m_Begin;
		nEnd = g_TableInit.m_PetConfig.m_vGenGu[4].m_End;
	}
	nGenGu = RandGen::GetRand(nBegin, nEnd);

__LEAVE_FUNCTION
}

// 向宠物的技能列表中增加新技能
VOID PetManager::AddPetSkill(_PET_SKILL *paSkillList, INT& rSkillIndex)
{
__ENTER_FUNCTION

	if (rSkillIndex > PET_SKILL_NUM)
	{
		Assert(FALSE && "rSkillIndex > PET_SKILL_NUM");
		return ;
	}
	INT nSkillID = -1;
	INT nSkillType = -1;
	for (INT i = 0; i < PET_SKILL_NUM; ++i)
	{// 根据索引查找相应的SkillID
		if (g_PetSkillIndexTbl[i].m_nIndex == rSkillIndex)
		{
			nSkillID = g_PetSkillIndexTbl[i].m_nSkillID;
			// 根据技能ID判断该技能是否是手动技能，如果是手动技能则加入到手动技能槽中
			SkillTemplateData_T const* pSkillTemplateData = g_SkillTemplateDataMgr.GetInstanceByID(nSkillID);
			if (!pSkillTemplateData)
			{
				return ;
			}
			ID_t OperateModeOfPetSkill = pSkillTemplateData->GetOperateModeForPetSkill();
			if (PET_SKILL_OPERATE_NEEDOWNER == OperateModeOfPetSkill)
			{// 是手动技能
				paSkillList[PET_SKILL_INDEX_CONTROL_BY_PLAYER].m_nSkillID = nSkillID;
				return ;
			}
			break;
		}
	}

	for (INT j = PET_SKILL_INDEX_CONTROL_BY_AI0 ; j < PET_MAX_SKILL_COUNT; ++j) 
	{
		// 如果已经拥有该技能则直接返回
		if (paSkillList[j].m_nSkillID == nSkillID)
		{
			return ;
		}
        // 如果有可用的技能槽才加入技能列表
		if (paSkillList[j].m_nSkillID == INVALID_ID) 
		{
			paSkillList[j].m_nSkillID = nSkillID;
			break;
		}
	}
__LEAVE_FUNCTION
}

BOOL PetManager::HeartBeat( UINT uTime )
{
__ENTER_FUNCTION

	if( !m_LogicTimer.CountingTimer(uTime ) )
		return TRUE;

#define MAX_REMOVE_SIZE 256
	INT aNeedRemovePet[MAX_REMOVE_SIZE] ;
	memset( aNeedRemovePet, 0, sizeof(INT)*MAX_REMOVE_SIZE ) ;

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
					BOOL bRet = m_papObjs[i]->HeartBeat_OutZone(uTime ) ;
					if( bRet==FALSE )
					{
						aNeedRemovePet[nRemoveCount++] = i ;
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
			Obj_Pet* pPet = (Obj_Pet*)(m_papObjs[aNeedRemovePet[i]]) ;
			if( pPet != NULL )
			{
				pPet->SetActiveFlag( FALSE );
				pPet->CleanUp();
				GetScene()->DeleteObject( pPet ) ;
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
