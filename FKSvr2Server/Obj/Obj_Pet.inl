// Obj_Pet.inl

#ifndef __OBJ_PET_INL__
#define __OBJ_PET_INL__
#include "ItemOperator.h"
#include "GCOperateResult.h"
#include "Obj_Pet.h"

_IMPACT_LIST& Obj_Pet::Impact_GetImpactList(VOID)
{
	return m_ImpactList;
}

INT Obj_Pet::GetCaptureCount(VOID)const
{
	return m_nCapturerCount;
}

VOID Obj_Pet::CleanAllCapturer(VOID)
{
	m_nCapturerCount = 0;
}

AI_Pet* Obj_Pet::GetPetAI( VOID )const
{
	return ((AI_Pet*)m_pAI_Character);
}

VOID Obj_Pet::SetTargetID( ObjID_t TargetID )
{
	m_TargetID = TargetID;
}

ObjID_t Obj_Pet::GetTargetID( VOID )const
{
	return m_TargetID;
}

const WORLD_POS* Obj_Pet::GetRespawnPos( VOID )const
{
	return &m_RespawnPos;
}

Obj_Human *Obj_Pet::GetCreator( VOID )const
{
	return m_pCreator;
}

const Obj_Human *Obj_Pet::GetConstCreator( VOID )const
{
	return m_pCreator;
}

GUID_t Obj_Pet::GetGUID( VOID )const
{
	return m_GUID;
}

VOID Obj_Pet::SetPetGUID(PET_GUID_t guid)
{
	if (!GetConstCreator())	
	{
		m_PetDB.m_GUID = guid;
		return ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);	

	g_ItemOperator.SetPetGUID(pPetContainer, m_nIndex, guid);
}

PET_GUID_t Obj_Pet::GetSpouseGUID( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_SpouseGUID;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);	

	return pPetItem->GetSpouseGUID();
}

VOID Obj_Pet::SetSpouseGUID(PET_GUID_t guid)
{
	if (!GetConstCreator())	
	{
		m_PetDB.m_SpouseGUID = guid;
		return ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);	

	g_ItemOperator.SetSpouseGUID(pPetContainer, m_nIndex, guid);
}

PET_GUID_t Obj_Pet::GetPetGUID(VOID)const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_GUID;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);	

	return pPetItem->GetPetGUID();
}

ObjID_t Obj_Pet::GetOwnerID(VOID)const
{
	return m_OwnerID;
}

//////////////////////////////////////////////////////////////
// 属性访问
//////////////////////////////////////////////////////////////
VOID Obj_Pet::SetDataID(const UINT dataID)
{
	if (!GetConstCreator())	
	{
		m_PetDB.m_nDataID = dataID;
		return;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	g_ItemOperator.SetDataID(pPetContainer, m_nIndex, dataID);
}

UINT Obj_Pet::GetDataID( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nDataID;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetDataID();	
}

VOID Obj_Pet::SetName( const CHAR *pszName )
{
	if (!GetConstCreator())	
	{
		strncpy( m_PetDB.m_szName, pszName, sizeof(m_PetDB.m_szName) );
		m_AttrBackUp.m_bNameModified = TRUE;
		return ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);
	
	g_ItemOperator.SetName(pPetContainer, m_nIndex, const_cast<CHAR*>(pszName));
	m_AttrBackUp.m_bNameModified = TRUE;
	
}

const CHAR *Obj_Pet::GetName( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_szName;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetName();
}

VOID Obj_Pet::SetTitle( const CHAR *pszTitle )
{
	if (!GetConstCreator())	
	{
		strncpy( m_PetDB.m_szNick, pszTitle, sizeof(m_PetDB.m_szNick) );
		m_AttrBackUp.m_bTitleModified = TRUE;
		return ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	g_ItemOperator.SetNick(pPetContainer, m_nIndex, const_cast<CHAR*>(pszTitle));
	m_AttrBackUp.m_bTitleModified = TRUE;
}

const CHAR *Obj_Pet::GetTitle( VOID )const
{
	if (!GetConstCreator())
	{
		return m_PetDB.m_szNick;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetNick();
}

VOID Obj_Pet::SetHP( INT nHP )
{
	if (nHP > GetMaxHP())
	{
		nHP = GetMaxHP();
	}

	if (!GetConstCreator())	
	{
		m_PetDB.m_nHP = nHP;
		return ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);	

	g_ItemOperator.SetHP(pPetContainer, m_nIndex, nHP);

}

INT Obj_Pet::GetHP( VOID )
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nHP;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);	

	return pPetItem->GetHP();
}

VOID Obj_Pet::SetMP( INT nMP )
{// 宠物没有MP
	return;
	/*
	if (m_pdbPet)
		m_pdbPet->m_nMP = nMP;
	*/
}

INT Obj_Pet::GetMP( VOID )
{
	// 宠物没有MP
	//if (m_pdbPet)
	//{
	//	if(m_pdbPet->m_nMP>GetMaxMP())
	//	{
	//		m_pdbPet->m_nMP = GetMaxMP();
	//	}
	//	return m_pdbPet->m_nMP;
	//}
	return 0;
}

INT Obj_Pet::GetAIType( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_AIType;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetAIType();
}

VOID Obj_Pet::SetAIType( INT nAIType )
{
	if (!GetConstCreator())	
	{
		m_PetDB.m_AIType = nAIType;
		return ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	g_ItemOperator.SetAIType(pPetContainer, m_nIndex, nAIType);
}

INT Obj_Pet::GetLevel( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nLevel;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetLevel();
}

VOID Obj_Pet::SetLevel( INT nLevel )
{
	if (!GetConstCreator())	
	{
		if(m_PetDB.m_nLevel != nLevel)
		{
			m_PetDB.m_nLevel = nLevel;
			OnLevelChanged();
		}
		return ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	if(nLevel != pPetItem->GetLevel())
	{
		g_ItemOperator.SetLevel(pPetContainer, m_nIndex, nLevel);
		OnLevelChanged();
	}
}

INT Obj_Pet::GetLife( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nLife;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetLife();
}

VOID Obj_Pet::SetLife( INT nLife )
{
	if (!GetConstCreator())	
	{
		m_PetDB.m_nLife = nLife;
		return ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	g_ItemOperator.SetLife(pPetContainer, m_nIndex, nLife);
}

BYTE Obj_Pet::GetGeneration( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_byGeneration;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetGeneration();
}

VOID Obj_Pet::SetGeneration( BYTE byGeneration )
{
	if (!GetConstCreator())	
	{
		m_PetDB.m_byGeneration = byGeneration;
		return ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	g_ItemOperator.SetGeneration(pPetContainer, m_nIndex, byGeneration);
}

VOID Obj_Pet::IncrementHappyness(INT nIncrement)
{
	INT nHappyness = (INT)(GetHappiness()) + nIncrement;
	if ( nHappyness < 0 )
		nHappyness = 0;
	else if ( nHappyness > 100 )
		nHappyness = 100;

	SetHappiness((BYTE)nHappyness);
}

BYTE Obj_Pet::GetHappiness( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_byHappiness;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetHappiness();
}

VOID Obj_Pet::SetHappiness( BYTE byHappiness )
{
	
	if (!GetConstCreator())	
	{
		m_PetDB.m_byHappiness = byHappiness;
		return ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	g_ItemOperator.SetHappiness(pPetContainer, m_nIndex, byHappiness);

}

INT Obj_Pet::GetGenGu( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nGenGu;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetGenGu();
}

VOID Obj_Pet::SetGenGu( INT nGenGu )
{
	if (!GetConstCreator())	
	{
		m_PetDB.m_nGenGu = nGenGu;
		return ;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	g_ItemOperator.SetGenGu(pPetContainer, m_nIndex, nGenGu);

}

INT Obj_Pet::GetExp( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nExp;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetExp();
}

VOID Obj_Pet::SetExp( INT nExp )
{
	if (!GetConstCreator())	
	{
		m_PetDB.m_nExp = nExp;
		return ;
	}

	if (GetLevel() > (GetCreator()->GetLevel() + LEVELDELTA_GETEXP) )
	{// 当宠物等级高于玩家等级5级时将不能获得经验

		Obj_Human* pHuman = static_cast<Obj_Human*>(GetCreator());
		if(NULL!=pHuman)
		{
			pHuman->SendOperateResultMsg(OR_CANNOT_GETEXP);
		}
        return ;
	}
	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	g_ItemOperator.SetExp(pPetContainer, m_nIndex, nExp);
}

INT Obj_Pet::GetStrPerception( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nStrPerception;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetStrPer();
}

INT Obj_Pet::GetConPerception( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nConPerception;
	}


	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetConPer();

}

INT Obj_Pet::GetDexPerception( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nDexPerception;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetDexPer();
}

INT Obj_Pet::GetSprPerception( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nSprPerception;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetSprPer();
}

INT Obj_Pet::GetIntPerception( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nIntPerception;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetIntPer();
}

INT Obj_Pet::GetRemainPoint( VOID )const
{
	if (!GetConstCreator())	
	{
		return m_PetDB.m_nRemainPoint;
	}

	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	return pPetItem->GetRemainPoint();
}

VOID Obj_Pet::SetRemainPoint( INT nRemainPoint )
{
	if (!GetConstCreator())	
	{
		m_PetDB.m_nRemainPoint = nRemainPoint;
		return ;
	}

  	ItemContainer* pPetContainer = GetCreator()->GetPetContain();
	Item* pPetItem = pPetContainer->GetItem(m_nIndex);
	Assert(pPetItem);

	g_ItemOperator.SetRemainPoint(pPetContainer, m_nIndex, nRemainPoint);

}


#endif // __OBJ_PET_INL__
