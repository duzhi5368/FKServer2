#include "stdafx.h"

#include "Player.h"
#include "GameTable.h"
#include "ItemTable.h"
#include "TimeManager.h"
#include "GCDetailSkillList.h"
#include "GCOperateResult.h"
#include "Obj_Human.h"
#include "Config.h"
#include "LogicManager.h"
#include "HumanItemLogic.h"
#include "Scene.h"


using namespace Combat_Module::Skill_Module;
using namespace MenPai_Module;
using namespace Packets;

VOID Obj_Human::Levelup(VOID)
{
	__ENTER_FUNCTION
	SHORT nMenPai = GetMenPai();
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPai);
	if(NULL==pMenPaiLogic)
	{
		Assert("[Obj_Human::AttrLevel1Levelup]:Can't find MenPai Logic!");
		return;
	}
	if(100<=GetLevel())
	{
		return;
	}
	SetLevel(GetLevel()+1);
	getScene()->OnSceneHumanLevelUp( this ) ;
	SHORT nValue = 0;
	if(DEFAULT_WASHPOINT_LEVEL>GetLevel())
	{
		//自动加点
		//STR
		nValue = pMenPaiLogic->GetStrLevelupRefix(GetLevel());
		SetBaseStr(GetBaseStr()+nValue);
		//SPR
		nValue = pMenPaiLogic->GetSprLevelupRefix(GetLevel());
		SetBaseSpr(GetBaseSpr()+nValue);
		//CON
		nValue = pMenPaiLogic->GetConLevelupRefix(GetLevel());
		SetBaseCon(GetBaseCon()+nValue);
		//INT
		nValue = pMenPaiLogic->GetIntLevelupRefix(GetLevel());
		SetBaseInt(GetBaseInt()+nValue);
		//DEX
		nValue = pMenPaiLogic->GetDexLevelupRefix(GetLevel());
		SetBaseDex(GetBaseDex()+nValue);
	}
	else
	{
		//增加剩余点数
		nValue += Get_RemainPoints(); //原来没使用的剩余点数
		//STR
		nValue += pMenPaiLogic->GetStrLevelupRefix(GetLevel());
		//SPR
		nValue += pMenPaiLogic->GetSprLevelupRefix(GetLevel());
		//CON
		nValue += pMenPaiLogic->GetConLevelupRefix(GetLevel());
		//INT
		nValue += pMenPaiLogic->GetIntLevelupRefix(GetLevel());
		//DEX
		nValue += pMenPaiLogic->GetDexLevelupRefix(GetLevel());
		Set_RemainPoints(nValue);
	}

	MarkAllIntAttrDirtyFlags();

	//SetMaxVigor(GetMaxVigor() + 5);

	//SetMaxEnergy(GetMaxEnergy() + 5);

	SetHP(GetMaxHP());
	SetMP(GetMaxMP());

	__LEAVE_FUNCTION;
}

//转换门派的时候需要进行的点数从新计算
VOID Obj_Human::ChangeMenpaiPoints(VOID)
{
	if(GetLevel() >= DEFAULT_WASHPOINT_LEVEL)
	{
		WashPoints();
		SetMP(GetMaxMP());
		SetHP(GetMaxHP());
		return;
	}

	INT nMenPai		=  GetMenPai();

	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPai);
	if(NULL==pMenPaiLogic)
	{
		Assert("[Obj_Human::ChangeMenpaiPoints]:Can't find MenPai Logic!");
		return;
	}
	SHORT nValue = 0;
	SHORT nStr = 0;
	SHORT nSpr = 0;
	SHORT nCon = 0;
	SHORT nInt = 0;
	SHORT nDex = 0;

	for(INT nLevel =0;nLevel <= GetLevel();nLevel++)
	{
		//Str
		nStr += pMenPaiLogic->GetStrLevelupRefix(nLevel);
		//Spr
		nSpr += pMenPaiLogic->GetSprLevelupRefix(nLevel);
		//Con
		nCon += pMenPaiLogic->GetConLevelupRefix(nLevel);
		//Int
		nInt += pMenPaiLogic->GetIntLevelupRefix(nLevel);
		//Dex
		nDex += pMenPaiLogic->GetDexLevelupRefix(nLevel);
	}
	//set attr1
	SetBaseStr(nStr);
	SetBaseSpr(nSpr);
	SetBaseCon(nCon);
	SetBaseInt(nInt);
	SetBaseDex(nDex);

	// 给玩家加满HP和MP
	SetMP(GetMaxMP());
	SetHP(GetMaxHP());
}

VOID Obj_Human::WashPoints(VOID)
{
	INT nWashLevels = DEFAULT_WASHPOINT_LEVEL;
	INT nMenPai		=  GetMenPai();
	MenPai_T const* pMenPaiLogic = g_MenPaiLogicList.GetLogicById(nMenPai);
	if(NULL==pMenPaiLogic)
	{
		Assert("[Obj_Human::WashPoints]:Can't find MenPai Logic!");
		return;
	}
	SHORT nValue = 0;
	SHORT nStr = 0;
	SHORT nSpr = 0;
	SHORT nCon = 0;
	SHORT nInt = 0;
	SHORT nDex = 0;
	SHORT nRemainPoint = 0;
	SHORT nTotalPoint = 0;
	/// \block calculate total points
	//@{
	for(INT nLevel =0;nLevel<=GetLevel();nLevel++)
	{
		//Str
		nTotalPoint += pMenPaiLogic->GetStrLevelupRefix(nLevel);
		//Spr
		nTotalPoint += pMenPaiLogic->GetSprLevelupRefix(nLevel);
		//Con
		nTotalPoint += pMenPaiLogic->GetConLevelupRefix(nLevel);
		//Int
		nTotalPoint += pMenPaiLogic->GetIntLevelupRefix(nLevel);
		//Dex
		nTotalPoint += pMenPaiLogic->GetDexLevelupRefix(nLevel);
	}
	//@}
	
	for(INT nLevel =0;nLevel<DEFAULT_WASHPOINT_LEVEL;nLevel++)
	{
		//Str
		nStr += pMenPaiLogic->GetStrLevelupRefix(nLevel);
		//Spr
		nSpr += pMenPaiLogic->GetSprLevelupRefix(nLevel);
		//Con
		nCon += pMenPaiLogic->GetConLevelupRefix(nLevel);
		//Int
		nInt += pMenPaiLogic->GetIntLevelupRefix(nLevel);
		//Dex
		nDex += pMenPaiLogic->GetDexLevelupRefix(nLevel);
	}
	//set attr1
	SetBaseStr(nStr);
	SetBaseSpr(nSpr);
	SetBaseCon(nCon);
	SetBaseInt(nInt);
	SetBaseDex(nDex);

	//Remain Points
	nRemainPoint = nTotalPoint-nStr-nSpr-nCon-nInt-nDex;
	Set_RemainPoints(nRemainPoint);	
}

BOOL Obj_Human::ManualAttrPoint(CHAR_ATTR_LEVEL1 attrType)
{
	if(0>Get_RemainPoints())
	{
		AssertEx(FALSE,"[Obj_Human::ManualAttrPoint]: Assert at not enough remain point!");
		return FALSE;
	}
	switch(attrType)
	{
		case CATTR_LEVEL1_STR:
			SetBaseStr(GetBaseStr()+1);
			break;
		case CATTR_LEVEL1_SPR:
			SetBaseSpr(GetBaseSpr()+1);
			break;
		case CATTR_LEVEL1_CON:
			SetBaseCon(GetBaseCon()+1);
			break;
		case CATTR_LEVEL1_INT:
			SetBaseInt(GetBaseInt()+1);
			break;
		case CATTR_LEVEL1_DEX:
			SetBaseDex(GetBaseDex()+1);
			break;
		default:
			return FALSE;
			break;
	}
	Set_RemainPoints(Get_RemainPoints()-1);
	return TRUE;
}

BOOL Obj_Human::ManualAttrPoint(INT nStr, INT nSpr, INT nCon, INT nInt, INT nDex)
{
	if(0>nStr||0>nSpr||0>nCon||0>nInt||0>nDex)
	{
		return FALSE;
	}
	if((nStr+nSpr+nCon+nInt+nDex)>Get_RemainPoints())
	{
		AssertEx(FALSE,"[Obj_Human::ManualAttrPoint]: Assert at not enough remain point!");
		return FALSE;
	}
	//set attrs
	SetBaseStr(GetBaseStr()+nStr);
	SetBaseSpr(GetBaseSpr()+nSpr);
	SetBaseCon(GetBaseCon()+nCon);
	SetBaseInt(GetBaseInt()+nInt);
	SetBaseDex(GetBaseDex()+nDex);
	//update remain point
	Set_RemainPoints(Get_RemainPoints()-(nStr+nSpr+nCon+nInt+nDex));
	SendMsg_RefeshAttrib();
	return TRUE;
}

INT Obj_Human::Get_RemainPoints()
{
	return m_DB.GetRemainPoints();
}

VOID Obj_Human::ItemEffectFlush( )
{
__ENTER_FUNCTION

	//将物品的影响因素值清零；
	memset( m_pItemEffect, 0, sizeof(_ITEM_EFFECT)*IATTRIBUTE_NUMBER );
	memset(m_EquipUseSkillEffect,0,sizeof(_ITEM_SKILL)*(HEQUIP_NUMBER+MAX_ITEM_SET_ATTR));	
	memset(m_EquipRandSkillEffect,0,sizeof(_ITEM_SKILL)*(HEQUIP_NUMBER+MAX_ITEM_SET_ATTR));	

	

	for( INT i=0; i<HEQUIP_NUMBER; i++ )
	{
		
		/*
		if( !m_DB.GetEquipDB()->IsSet( (HUMAN_EQUIP)i ) )//没有装备此物品
			continue ;
		*/
		ItemContainer* pEquipContainer = GetEquipContain();
		if(NULL==pEquipContainer)
		{
			AssertEx(FALSE,"[Obj_Human::ItemEffectFlush]: NULL EquipContainer pointer found!");
			break;
		}
		Item*	pEquipItem = pEquipContainer->GetItem((UINT)i);
		if(NULL==pEquipItem)
		{
			AssertEx(FALSE,"[Obj_Human::ItemEffectFlush]: NULL EquipItem pointer found!");
			continue;
		}
		if(TRUE==pEquipItem->IsEmpty())
		{
			continue;//这个位置是空的
		}
		if(0==pEquipItem->GetDurPoints())
		{
			continue;
		}
		//这个位置装备有物品
		const	_ITEM* pCurItem = m_DB.GetEquipItem((HUMAN_EQUIP)i);
		// 武器类型
		INT nItemClass = pCurItem->ItemClass();
		// 防具类型
		INT nItemType = pCurItem->ItemType();
 		Assert(ICLASS_EQUIP==nItemClass) ; //只能为装备，不能为别的物品
		//取得每个物品的各个属性
		for( INT j=0; j<pCurItem->GetEquipData()->m_AttrCount; j++ )
		{
			
			CaculateEffect(pCurItem->GetEquipData()->m_pAttr[j],(HUMAN_EQUIP)i, nItemType);
				
		}	
		
	}

	CaculateEquipSetEffect();
	MarkAllIntAttrDirtyFlags();//mark the int attributes dirty
__LEAVE_FUNCTION
}

VOID		Obj_Human::CaculateEffect(_ITEM_ATTR& Attr,INT EquipOffset, INT nItemType)
{
	__ENTER_FUNCTION

	SHORT				value;
	ITEM_ATTRIBUTE		type;

	value	=	Attr.m_Value.m_Value;
	type	=	(ITEM_ATTRIBUTE)Attr.m_AttrType;
	// Passive Skill refix
	if(INVALID_ID != nItemType)
	{
		switch(type) 
		{

		case IATTRIBUTE_BASE_ATTACK_P:			//基础物理攻击
		case IATTRIBUTE_BASE_ATTACK_M:			//基础魔法攻击
		case IATTRIBUTE_BASE_DEFENCE_P:			//基础物理防御
		case IATTRIBUTE_BASE_DEFENCE_M:			//基础魔法防御
			{
				//passive skill refixs value here
				Skill_RefixItemAttr(EquipOffset, nItemType, type, value);
			}
			break;
		default:
			break;

		}
	}
	switch(type) 
	{
	
		case IATTRIBUTE_POINT_MAXHP:			//按点数增加HP的上限
		case IATTRIBUTE_RATE_MAXHP:				//按百分比增加HP的上
		case IATTRIBUTE_RESTORE_HP:				//加快HP的回复速度
		case IATTRIBUTE_POINT_MAXMP:			//按点数增加MP的上限
		case IATTRIBUTE_RATE_MAXMP:				//按百分比增加MP的上
		case IATTRIBUTE_RESTORE_MP:				//加快MP的回复速度
		case IATTRIBUTE_COLD_ATTACK:			//冰攻击
		case IATTRIBUTE_COLD_RESIST:			//冰抵抗
		case IATTRIBUTE_COLD_TIME:				//减少冰冻迟缓时间
		case IATTRIBUTE_FIRE_ATTACK:			//火攻击
		case IATTRIBUTE_FIRE_RESIST:			//火抵抗
		case IATTRIBUTE_FIRE_TIME:				//减少火烧持续时间
		case IATTRIBUTE_LIGHT_ATTACK:			//电攻击
		case IATTRIBUTE_LIGHT_RESIST:			//电抵抗
		case IATTRIBUTE_LIGHT_TIME:				//减少电击眩晕时间
		case IATTRIBUTE_POISON_ATTACK:			//毒攻击
		case IATTRIBUTE_POISON_RESIST:			//毒抵抗    
		case IATTRIBUTE_POISON_TIME:			//减少中毒时间
		case IATTRIBUTE_ATTACK_P:				//物理攻击
		case IATTRIBUTE_RATE_ATTACK_P:			//按百分比增加物理攻击
		case IATTRIBUTE_RATE_ATTACK_EP:			//对装备基础物理攻击百分比加成
		case IATTRIBUTE_DEFENCE_P:				//物理防御
		case IATTRIBUTE_RATE_DEFENCE_P:			//按百分比增加物理防御
		case IATTRIBUTE_RATE_DEFENCE_EP:		//对装备基础物理防御百分比加成
		case IATTRIBUTE_IMMUNITY_P:				//按百分比抵消物理伤害
		case IATTRIBUTE_ATTACK_M:				//魔法攻击
		case IATTRIBUTE_RATE_ATTACK_M:			//按百分比增加魔法攻击
		case IATTRIBUTE_RATE_ATTACK_EM:			//对装备基础魔法攻击百分比加成
		case IATTRIBUTE_DEFENCE_M:				//魔法防御
		case IATTRIBUTE_RATE_DEFENCE_M:			//按百分比增加魔法防御
		case IATTRIBUTE_RATE_DEFENCE_EM:		//对装备基础魔法防御百分比加成
		case IATTRIBUTE_IMMUNITY_M:				//按百分比抵消魔法伤害
		case IATTRIBUTE_ATTACK_SPEED:			//攻击速度
		case IATTRIBUTE_SKILL_TIME:				//魔法冷却速度
		case IATTRIBUTE_HIT:					//命中
		case IATTRIBUTE_MISS:					//闪避
		case IATTRIBUTE_2ATTACK_RATE:			//会心一击（双倍攻击）的百分比
		case IATTRIBUTE_NO_DEFENCE_RATE:		//无视对方防御比率
		case IATTRIBUTE_SPEED_RATE:				//移动速度百分比
		case IATTRIBUTE_DAMAGE_RET:				//伤害反射
		case IATTRIBUTE_DAMAGE2MANA:			//伤害由内力抵消
		case IATTRIBUTE_STR:					//增加力量
		case IATTRIBUTE_SPR:					//增加灵气
		case IATTRIBUTE_CON:					//增加体制
		case IATTRIBUTE_INT:					//增加定力
		case IATTRIBUTE_DEX:					//增加身法
		case IATTRIBUTE_LUK:					//增加悟性
		case IATTRIBUTE_HP_THIEVE:				//生命偷取(从伤害里)
		case IATTRIBUTE_MP_THIEVE:				//内力偷取(从伤害里)
		case IATTRIBUTE_BASE_ATTACK_P:			//基础物理攻击
		case IATTRIBUTE_BASE_ATTACK_M:			//基础魔法攻击
		case IATTRIBUTE_BASE_ATTACK_TIME:		//基础攻击速度（只对普通攻击）
		case IATTRIBUTE_BASE_DEFENCE_P:			//基础物理防御
		case IATTRIBUTE_BASE_DEFENCE_M:			//基础魔法防御
		case IATTRIBUTE_BASE_MISS:				//基础闪避
			{

				_ITEM_EFFECT* pEffect = &(m_pItemEffect[type]);

				if(pEffect->IsActive())
					pEffect->m_Attr.m_Value += value;
				else
				{
					pEffect->m_Attr.m_Value = value;
					pEffect->SetActive(TRUE);
				}
				break;
			}
		//特殊属性
		case IATTRIBUTE_RESIST_ALL:				//按百分比抵消所有属性攻击
			{

				_ITEM_EFFECT* pEffect = &(m_pItemEffect[IATTRIBUTE_COLD_RESIST]);
				if(pEffect->IsActive())
					pEffect->m_Attr.m_Value += value;
				else
				{
					pEffect->m_Attr.m_Value = value;
					pEffect->SetActive(TRUE);
				}
				pEffect = &(m_pItemEffect[IATTRIBUTE_FIRE_RESIST]);
				if(pEffect->IsActive())
					pEffect->m_Attr.m_Value += value;
				else
				{
					pEffect->m_Attr.m_Value = value;
					pEffect->SetActive(TRUE);
				}			
				pEffect = &(m_pItemEffect[IATTRIBUTE_LIGHT_RESIST]);
				if(pEffect->IsActive())
					pEffect->m_Attr.m_Value += value;
				else
				{
					pEffect->m_Attr.m_Value = value;
					pEffect->SetActive(TRUE);
				}
				pEffect = &(m_pItemEffect[IATTRIBUTE_POISON_RESIST]);
				if(pEffect->IsActive())
					pEffect->m_Attr.m_Value += value;
				else
				{
					pEffect->m_Attr.m_Value = value;
					pEffect->SetActive(TRUE);
				}			

				break;
			}
		case IATTRIBUTE_ALL:					//增加所有的人物一级属性
			{
				_ITEM_EFFECT* pEffect = &(m_pItemEffect[IATTRIBUTE_STR]);

				if(pEffect->IsActive())
					pEffect->m_Attr.m_Value += value;
				else
				{
					pEffect->m_Attr.m_Value = value;
					pEffect->SetActive(TRUE);
				}

				pEffect = &(m_pItemEffect[IATTRIBUTE_SPR]);
				if(pEffect->IsActive())
					pEffect->m_Attr.m_Value += value;
				else
				{
					pEffect->m_Attr.m_Value = value;
					pEffect->SetActive(TRUE);
				}			
				pEffect = &(m_pItemEffect[IATTRIBUTE_CON]);
				if(pEffect->IsActive())
					pEffect->m_Attr.m_Value += value;
				else
				{
					pEffect->m_Attr.m_Value = value;
					pEffect->SetActive(TRUE);
				}			
				pEffect = &(m_pItemEffect[IATTRIBUTE_INT]);
				if(pEffect->IsActive())
					pEffect->m_Attr.m_Value += value;
				else
				{
					pEffect->m_Attr.m_Value = value;
					pEffect->SetActive(TRUE);
				}			
				pEffect = &(m_pItemEffect[IATTRIBUTE_DEX]);
				if(pEffect->IsActive())
					pEffect->m_Attr.m_Value += value;
				else
				{
					pEffect->m_Attr.m_Value = value;
					pEffect->SetActive(TRUE);
				}			
				pEffect = &(m_pItemEffect[IATTRIBUTE_LUK]);
				if(pEffect->IsActive())
					pEffect->m_Attr.m_Value += value;
				else
				{
					pEffect->m_Attr.m_Value = value;
					pEffect->SetActive(TRUE);
				}			
				break;
			}
		case IATTRIBUTE_USESKILL:				//增加某个使用技能
			{
				
				_ITEM_SKILL*	pSkill = &(m_EquipUseSkillEffect[EquipOffset]);
				
				if(pSkill->IsActive()) 
				{
					Assert(FALSE);				//一件装备不同时存在2个技能
				}
				else
				{
					pSkill->m_SkillID		=	value;
					pSkill->m_SkillRate		=	100;
					pSkill->SetActive(TRUE);
				}
				break;
			}
		case IATTRIBUTE_RAND_SKILL:				//增加某个随机技能
			{
				_ITEM_SKILL*	pSkill = &(m_EquipRandSkillEffect[EquipOffset]);

				if(pSkill->IsActive()) 
				{
					Assert(FALSE);			//一件装备不同时存在2个技能
				}
				else
				{
					pSkill->m_SkillID		=	value;
					pSkill->m_SkillRate		=	100;
					pSkill->SetActive(TRUE);
				}
				break;
			}
		case IATTRIBUTE_SKILL_RATE:
			{
				_ITEM_SKILL*	pSkill = &(m_EquipRandSkillEffect[EquipOffset]);
				pSkill->m_SkillRate		=	value;
				break;
			}
		default:
			{
				Assert(FALSE);
				break;
			}

		}

	__LEAVE_FUNCTION
}

VOID	Obj_Human::CaculateEquipSetEffect()
{
	__ENTER_FUNCTION
		
			
		INT iCapSetNum		=	HumanItemLogic::GetEquip(this,HEQUIP_CAP)->GetSetNum();
		INT	iArmorSetNum	=	HumanItemLogic::GetEquip(this,HEQUIP_ARMOR)->GetSetNum();
		INT	iCuffSetNum		=	HumanItemLogic::GetEquip(this,HEQUIP_CUFF)->GetSetNum();
		INT	iBootSetNum		=	HumanItemLogic::GetEquip(this,HEQUIP_BOOT)->GetSetNum();
		
		if( (iArmorSetNum==iCapSetNum)&&
			(iCapSetNum== iCuffSetNum)&&
			(iCapSetNum== iBootSetNum)
			)
		{
			if((iCapSetNum!=-1)&&(iCapSetNum!=0))
			{
					EQUIP_SET_TB* pGET = g_ItemTable.GetEquipSetTB(iCapSetNum);
					if(pGET)
					{
						for(INT i = 0;i<pGET->m_nAttrCount;i++)
						{
							CaculateEffect(pGET->m_ItemAttr[i],HEQUIP_NUMBER+i);
						}
					}

			}
		}

	__LEAVE_FUNCTION
}

