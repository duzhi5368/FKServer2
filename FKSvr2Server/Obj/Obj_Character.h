// Obj_Character.h
//
////////////////////////////////////////////////////////

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "OResultDef.h"
#include "DB_Struct.h"
#include "Attributes.h"
#include "SkillInfo.h"
#include "GameUtil.h"

#include "Obj_Dynamic.h"
#include "Obj_Special.h"
#include "ActionCallBack.h"
#include "ActionLogic.h"
#include "ActionDelegator.h"
#include "TargetingAndDepletingParams.h"

using namespace Combat_Module;
using namespace Action_Module;
using namespace Combat_Module::Skill_Module;

enum ENUM_CHARACTER_LOGIC
{
	CHARACTER_LOGIC_INVALID	= -1,
	CHARACTER_LOGIC_IDLE,
	CHARACTER_LOGIC_MOVE,
	CHARACTER_LOGIC_USE_SKILL,
	//CHARACTER_LOGIC_DEAD,
	//CHARACTER_LOGIC_SIT,
	CHARACTER_LOGIC_USE_ABILITY,	// 使用生活技能

	CHARACTER_LOGIC_NUMBERS
};

struct _ITEM_EFFECT
{
	BOOL			m_bActive ;
	_ITEM_VALUE		m_Attr ;

	_ITEM_EFFECT( )
	{
		m_bActive = FALSE ;
	};

	BOOL			IsActive( ){ return m_bActive ; }
	VOID			SetActive( BOOL bActive ){ m_bActive = bActive ; }
};

struct _SKILL_EFFECT
{
	BOOL			m_bActive ;

	_SKILL_EFFECT( )
	{
		m_bActive = FALSE ;
	};

	BOOL			IsActive( ){ return m_bActive ; }
	VOID			SetActive( BOOL bActive ){ m_bActive = bActive ; }
};

struct _OBJ_CHARACTER_INIT : public _OBJ_DYNAMIC_INIT
{
	INT							m_ScriptTimer ;
	ENUM_CHARACTER_LOGIC		m_eLogic;

	_OBJ_CHARACTER_INIT( VOID )
	{
		m_ScriptTimer = 0 ;
		m_eLogic	= CHARACTER_LOGIC_INVALID;
	}

	virtual VOID CleanUp( VOID )
	{
		m_ScriptTimer = 0 ;
		m_eLogic	= CHARACTER_LOGIC_INVALID;
		_OBJ_DYNAMIC_INIT::CleanUp();
	}
};

struct _LOGICPARAM_MOVE
{
	//INT			m_nHandleID;
	WORD		m_wNumNode;
	WORD		m_wCurNode;
	WORLD_POS	m_aTargetPos[MAX_CHAR_PATH_NODE_NUMBER];

	_LOGICPARAM_MOVE(VOID)
	{
		//m_nHandleID = 0;
		Reset();
	}

	VOID Reset( VOID )
	{
		m_wNumNode = 0;
		m_wCurNode = 0;
	}

	BOOL IsEmpty( VOID )const
	{
		return (( (m_wNumNode==0) || (m_wNumNode==m_wCurNode) )?(TRUE):(FALSE)) ;
	}

	VOID AddTargetPos( const WORLD_POS *pTargetPos )
	{
		if ( m_wNumNode < MAX_CHAR_PATH_NODE_NUMBER )
			m_aTargetPos[m_wNumNode++] = *pTargetPos;
	}

	const WORLD_POS *GetCurTargetPos( VOID )const
	{
		return &m_aTargetPos[m_wCurNode];
	}
	
	const WORLD_POS* GetFinalTarPos( VOID ) const
	{
		return &m_aTargetPos[m_wNumNode - 1];
	}
	// do ... 
	BOOL NextTargetPos( VOID )
	{
		if ( m_wCurNode < m_wNumNode )
			m_wCurNode++;

		if ( m_wCurNode < m_wNumNode )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
};
enum ENUM_REFESH_ATTR_TYPE
{
	REFESH_ATTR_TYPE_INVALID = -1,
	REFESH_ATTR_TYPE_NONE,
	REFESH_ATTR_TYPE_PUBLIC,
	REFESH_ATTR_TYPE_PUBLIC_AND_LEVEL,
	REFESH_ATTR_TYPE_PROTECTED,

	REFESH_ATTR_TYPE_NUMBERS
};

struct TEAMMEMBER;
class State;
class Scene;
class Obj_Human;
class AI_Character;

class Obj_Character : public Obj_Dynamic
{
public :
	friend class State;
	friend class Action_Module::ActionDelegator_T;
public:
	enum CharacterClass
	{
		CHARACTER_CLASS_INVALID = -1,
		CHARACTER_CLASS_HUMAN,
		CHARACTER_CLASS_PET,
		CHARACTER_CLASS_MONSTER,
	};
	enum
	{
		RECOVER_INTERVAL = 3000,
	};

public :
	Obj_Character( );
	~Obj_Character( );

	virtual VOID OnRegisterToZone(VOID);

	virtual VOID	CleanUp( VOID );
	virtual BOOL	Init( const _OBJ_INIT *pInit );
	virtual VOID	OnEnterScene(VOID);
	virtual ObjType	GetObjType( VOID )const{ return OBJ_TYPE_INVALID; }

	virtual BOOL	HeartBeat( UINT uTime = 0 );
	virtual BOOL	HeartBeat_OutZone( UINT uTime=0 );
	virtual VOID	InitAIObj( );

// Event hanlder
public:
	virtual VOID OnDie( ObjID_t idKiller );
	virtual VOID OnRelive( ObjID_t idKiller );
	virtual VOID OnKillObject( ObjID_t idObj ){}
	virtual VOID OnItemChanged( UINT uItemDataID ){}
	virtual VOID OnEnterArea( UINT uAreaID ){}
	virtual	VOID OnArmorAbrasion(VOID){}
	virtual	VOID OnWeaponAbrasion(VOID){}
	virtual VOID OnStealthLevelChanged(VOID);
	virtual VOID OnDetectLevelChanged(VOID);
	virtual VOID OnLevelChanged(VOID);
	virtual VOID OnExecuteScriptTimer(UINT uTime){}
	VOID OnDamages(INT const* const pDamagelist, ObjID_t nAttackerID, BOOL bCritical=FALSE, SkillID_t nSkillID=INVALID_ID);
	VOID OnDamage(INT nDamage, ObjID_t nAttackerID, BOOL bCritical=FALSE, SkillID_t nSkillID=INVALID_ID);
	VOID OnDamageTarget(INT nDamage, Obj_Character& rTar, SkillID_t nSkillID=INVALID_ID);
	INT  OnFiltrateImpact(OWN_IMPACT& rImpact);
	VOID RefixSkill(SkillInfo_T& rSkill);
	VOID RefixImpact(OWN_IMPACT& rImpactNeedRedix);
	VOID RefixRageRegeneration(INT& rRageRegeneration);
	VOID OnBeSkill(Obj_Character& rAttacker, INT nBehaviorType);
	VOID OnBeHit(Obj_Character& rAttacker);
	VOID OnHitTarget(Obj_Character& rTarget);
	VOID OnCriticalHitTarget(SkillID_t const nSkill, Obj_Character& rTarget);
	VOID OnBeCriticalHit(SkillID_t const nSkill, Obj_Character& rAttacker);
	VOID OnHealTarget(SkillID_t const nSkill, Obj_Character& rTarget, INT nHealedHP);
	VOID OnBeHeal(SkillID_t const nSkill, Obj_Character& rCaster, INT nHealedHP);
	VOID OnBeAttack(Obj_Character& rAttacker);
	VOID OnBeAssisted(Obj_Character& rAssistor);
	VOID OnUseSkillSuccessfully(SkillInfo_T& rSkill);
	VOID OnActionStarted(VOID);
	VOID OnMyTrapActivated(Obj_Special& rTrap);
	VOID OnDepleteStrikePoints(INT nStrikePoints);
	
// 效果层处理
public:
	INT			Impact_GetListSize(VOID)const;
	VOID 		Impact_HeartBeat(VOID);
	BOOL 		Impact_RegisterImpact(OWN_IMPACT& rImpact);
	BOOL 		Impact_UnRegisterImpactBySN(INT const nSn);
	BOOL 		Impact_UnRegisterImpactBySkillIDAndImpactID(SkillID_t const nSkillID, ImpactID_t const nImpactID);
	VOID		Impact_CancelImpactInSpecificCollection(INT nCollectionID);

	BOOL 		Impact_CanViewThisSpecialObj(Obj_Special& rObj);

	BOOL 		Impact_HaveImpactOfSpecificImpactID(INT const nImpactID);
	BOOL 		Impact_HaveImpactOfSpecificLogicID(INT const nLogicID);
	BOOL 		Impact_HaveImpactOfSpecificMutexID(INT const nMutexID);
	BOOL 		Impact_HaveImpactOfSpecificSkillID(INT const nSkillID);
	BOOL 		Impact_HaveImpactInSpecificCollection(INT const nCollectionID);
	INT			Impact_DispelSpecificImpactByDataIndex(INT nDataIndex, INT nNeedDispel=-1);//-1是驱散所有的此类效果
	INT			Impact_DispelImpactOfSpecificImpactID(INT nImpactID, INT nNeedDispel=-1); //-1是驱散所有的此类效果
	INT			Impact_DispelImpactOfSpecificMutexID(INT nMutexID, INT nNeedDispel=-1);//-1是驱散所有的此类效果
	INT			Impact_DispelImpactOfSpecificLogicID(INT nLogicID, INT nNeedDispel=-1);//-1是驱散所有的此类效果
	INT			Impact_DispelImpactOfSpecificSkillID(INT nSkillID, INT nNeedDispel=-1);//-1是驱散所有的此类效果
	INT			Impact_DispelImpactInSpecificCollection(INT nCollectionID, INT nDispelLevel, INT nNeedDispel=-1);//-1是驱散所有的此类效果
	OWN_IMPACT* Impact_GetFirstImpactOfSpecificImpactID(INT nImpactID);
	OWN_IMPACT* Impact_GetFirstImpactOfSpecificLogicID(INT nLogicID);
	OWN_IMPACT* Impact_GetFirstImpactOfSpecificMutexID(INT nMutexID);
	OWN_IMPACT* Impact_GetFirstImpactOfSpecificSkillID(INT nSkillID);
	OWN_IMPACT* Impact_GetFirstImpactInSpecificCollection(INT nCollectionID);
	
	VOID	Impact_OnImpactFadeOut(OWN_IMPACT& rImp);
	VOID	Impact_CleanAllImpactWhenPetDead(ObjID_t idPet);
protected:
	INT 	Impact_OnFiltrateImpact(OWN_IMPACT& rImpact);
	VOID	Impact_OnDamages(INT* const pDamage, Obj_Character* const pAttacker, SkillID_t nSkillID=INVALID_ID);
	VOID 	Impact_OnDamage(INT& nDamage, Obj_Character* const pAttacker, SkillID_t nSkillID=INVALID_ID);
	VOID	Impact_OnDamageTarget(INT& nDamage, Obj_Character& rTar, SkillID_t nSkillID=INVALID_ID);
	VOID 	Impact_RefixSkill(SkillInfo_T& rSkill);
	VOID	Impact_RefixImpact(OWN_IMPACT& rImpactNeedRedix);
	VOID	Impact_RefixRageRegeneration(INT& rRageRegeneration);
	BOOL	Impact_GetIntAttrRefix(CharIntAttrRefixs_T::Index_T nIdx, INT& rIntAttrRefix);
	BOOL	Impact_GetBoolAttrRefix(CharBoolAttrs_T::Index_T nIdx, BOOL& rBoolAttrRefix);
	VOID	Impact_OnDie(VOID);
	VOID 	Impact_OnBeHit(Obj_Character& rAttacker);
	VOID 	Impact_OnHitTarget(Obj_Character& rTarget);
	VOID	Impact_OnCriticalHitTarget(SkillID_t const nSkill, Obj_Character& rTarget);
	VOID 	Impact_OnBeCriticalHit(SkillID_t const nSkill, Obj_Character& rAttacker);
	VOID 	Impact_OnHealTarget(SkillID_t const nSkill, Obj_Character& rTarget, INT& rHealedHP);
	VOID 	Impact_OnBeHeal(SkillID_t const nSkill, Obj_Character& rCaster, INT& rHealedHP);
	VOID	Impact_OnUseSkillSuccessfully(SkillInfo_T& nSkill);
	VOID	Impact_OnActionStarted(VOID);
private:
	VOID	Impact_OnImpactActived(OWN_IMPACT& rImp);
	BOOL 	Impact_RemoveImpactByIndex(INT const nIdx);
	BOOL 	Impact_ReplaceMutuallyExclusiveImpact(OWN_IMPACT& rImpactIn);
	VOID	Impact_ReplaceLastGoodImpact(OWN_IMPACT& rImpactIn);
	BOOL	Impact_AddNewImpact(OWN_IMPACT& rImpactIn);
	VOID	Impact_ReplaceImpact(OWN_IMPACT& rDest, OWN_IMPACT& rSrc);
	VOID	Impact_CleanupAllFadeOutImpacts(VOID);
	
private:
	virtual VOID 	Impact_InitList(VOID);
	UINT 	m_nSNSeedOfImpacts;
//持续性效果
protected:
	UINT					Impact_GetSNSeed(VOID) const{return m_nSNSeedOfImpacts;};
	VOID					Impact_SetSNSeed(INT const nValue) {m_nSNSeedOfImpacts=nValue;};
	VOID					Impact_AddSNSeed(VOID){++m_nSNSeedOfImpacts;};
	virtual _IMPACT_LIST&	Impact_GetImpactList(VOID)=0;
private:
	//_IMPACT_LIST	m_ImpactList;
	
///////////////////////////////////////////////////////////////////////////////////
// 技能层和战斗相关
public:
	Obj* 			GetMyShadowGuard(VOID);
	Obj* 			GetMyPet(VOID);
	Obj* 			GetMyMaster(VOID);
	VOID			GM_killObj(VOID);
	VOID 			GM_ForceDie(Obj_Character* pKiller);
	VOID			HealthIncrement(INT nIncrement, Obj_Character* pCharacter=NULL, BOOL bCritical=FALSE);
	VOID			ManaIncrement(INT nIncrement, Obj_Character* pCharacter=NULL);
	VOID			RageIncrement(INT nIncrement, Obj_Character* pCharacter=NULL);
	VOID			StrikePointIncrement(INT nIncrement, Obj_Character* pCharacter=NULL);

	virtual Time_t	GetCooldownRemained(CooldownID_t const nID) const {return 0;};
	virtual VOID	SetCooldown(CooldownID_t const nID, Time_t nCooldown){};
	virtual BOOL	IsCooldowned(CooldownID_t const nID) const {return FALSE;}
	virtual BOOL 	HeartBeat_Cooldown(UINT uTime = 0){return TRUE;};
	virtual BOOL	HeartBeat_Recover(UINT uTime = 0){return TRUE;};
	BOOL			HeartBeat_Action(UINT uTime = 0);
	BOOL			HeartBeat_AutoRepeatCooldown(UINT uTime = 0);
	ObjID_t 		GetLockedTarget(VOID) const {return m_nLockedTargetID;};
	VOID			SetLockedTarget(ObjID_t const nID){m_nLockedTargetID = nID;};
	BOOL			CanUseSkillNow(VOID);

	Time_t			GetActionTime(VOID) const {return m_nActionTime;};
	VOID			SetActionTime(Time_t nTime) {m_nActionTime=nTime;};
	Time_t			GetAutoRepeatCooldown(VOID) const {return m_nAutoRepeatCooldown;};
	VOID			SetAutoRepeatCooldown(Time_t nCooldown){m_nAutoRepeatCooldown = nCooldown;};
	BOOL			DepletingUsedItem(VOID);
	SkillInfo_T&	GetSkillInfo(VOID) {return m_SkillInfo;};
	TargetingAndDepletingParams_T& GetTargetingAndDepletingParams(VOID) {return m_TargetingAndDepletingParams;};
protected:
	Time_t	m_nElapsedRevocerTick; //已经逝去的恢复时间
private:
	ObjID_t m_nLockedTargetID; //锁定的目标 
	SkillInfo_T m_SkillInfo; //技能实例
	TargetingAndDepletingParams_T m_TargetingAndDepletingParams; //目标和消耗数据
	Time_t	m_nActionTime; //配合客户端作动作演示的时间控制，时间不为零时不要进行下一个动作。相当于身体僵直不能动作.
	Time_t  m_nAutoRepeatCooldown;
//技能层和心法
public:
	VOID			Skill_ExecFromItemScript(SkillID_t const nID);
	VOID			Skill_ExecFromScript(SkillID_t const nID, BYTE nLevel, ObjID_t nTargetID, WORLD_POS& pos, FLOAT fDir, BOOL bPassSkillCheck);
	virtual BOOL 	Skill_HaveSkill( SkillID_t const nID, BYTE const nLevel = 1 ) const{return TRUE;};
	virtual BOOL 	Skill_ModifySkill(SkillID_t	const nID, BYTE const nLevel, INT const nModifyFlag){return TRUE;};
	virtual INT 	Skill_GetSkillLevel(SkillID_t const nID) const { return 1; };
	virtual BOOL 	Skill_SetXinFaLevel(SkillID_t const nID, INT const nLevel) { return TRUE; };
	virtual INT		Skill_GetCount() const { return 0; }
	virtual const CHAR*		Skill_GetName(SkillID_t const nID, BYTE const nLevel ) const { return NULL; }
	virtual INT		Skill_GetMaxLevel( SkillID_t const nID ) const { return 0; }
	//virtual BOOL 	Skill_HaveXinFa( SkillID_t const nID ) const{return TRUE;};
	//virtual INT 	Skill_GetXinFaLevel(SkillID_t const nID) const{return 1;};
	//virtual BOOL 	Skill_SetXinFaLevel(SkillID_t const nID, INT const nLevel){return TRUE;};
	virtual VOID 	Skill_OnEquipItem(VOID){};
	BOOL 			Skill_IsSkillCooldowned(SkillID_t nID);
	BOOL			Skill_CanUseThisSkillInThisStatus(SkillID_t nSkillID);
	Obj* 			Skill_CreateObjSpecial(WORLD_POS const& rPosition, INT nDataID);
	BOOL			Skill_RefixSkill(SkillInfo_T& rSkillInfo);
	Obj_Character*	CreateGuard(UINT uDataID, INT nBaseAI = 0, INT nExtAI = 0);
	Obj_Character*	GetGuard(VOID) const { return m_pGuard; }
	VOID			SetGuard(Obj_Character* pGuard) { m_pGuard = pGuard; }

protected:
private:
	Obj_Character*	m_pGuard; // 分身指针成员

// 动作层
// 动作管理和规则在这里实现
public:
	//动作的处理委托给ActionDelegator_T处理
protected:
	ActionParams_T&	GetActionParams(VOID) {return m_ActionParams;}
	ActionLogic_T const* GetActionLogic(VOID) {return m_pActionLogic;}
	VOID SetActionLogic(ActionLogic_T const* pLogic) {m_pActionLogic = pLogic;}
private:
	ActionParams_T			m_ActionParams;
	ActionLogic_T const* 	m_pActionLogic;
// 门派特性的处理
public:
	VOID MenPai_OnDamage(INT nDamage);
	VOID MenPai_OnDamageTarget(INT nDamage);
	VOID MenPai_OnMyTrapActivated(Obj_Special& rTrap);
	VOID MenPai_OnHealTarget(INT nHealed);
	VOID MenPai_OnDepleteStrikePoints(INT nStrikePoints);
protected:
private:

// 常用属性和标记
public:
	//Obj_Character id 是当前角色在CharacterManager类中的数组下标，其值由
	//CharacterManager统一负责处理
	VOID	SetCharacterID( ObjID_t id ){ m_CharacterID = id ; }
	ObjID_t	GetCharacterID( ){ return m_CharacterID ; }

	// 获取AI数据
	AI_Character*	GetAIObj( VOID ) const {  return m_pAI_Character; }
// Flags
public:
	//camp and stand
	BOOL			IsEnemyCamp(Obj_Character& rTar);
	BOOL			IsFriendCamp(Obj_Character& rTar);
	virtual BOOL	IsEnemy(Obj_Character* pCharacter){ return TRUE;}
	virtual BOOL	IsFriend(Obj_Character* pCharacter){return FALSE;}
	virtual BOOL	IsPartner(Obj_Character* pCharacter){return FALSE;}
	virtual BOOL	IsPrevCanViewMe( const Obj *pObj );
	virtual BOOL	IsCanViewMe( const Obj *pObj );
	BOOL			InStealthMode(VOID);
	virtual BOOL	IsNPC(VOID) { return FALSE; }
// logic
public:
	ENUM_CHARACTER_LOGIC	GetCharacterLogic( VOID )const{ return m_eCharacterLogic; }
	BOOL					IsCharacterLogicStopped( VOID )const{ return m_bCharacterLogicStopped; }
	VOID					StopCharacterLogic(BOOL bAbortive = TRUE);
	BOOL					IsMoving( );
	const WORLD_POS			*GetCurrentTargetPos( VOID )const{ return m_paramLogic_Move.GetCurTargetPos(); }
	const WORLD_POS			*GetFinalTarPos( VOID )const{ return m_paramLogic_Move.GetFinalTarPos(); }

	VOID					DoAction(INT nActionID, ObjID_t nTargetObjID = INVALID_ID);

	//INT						GetMoveHandleID( VOID )const{ return m_paramLogic_Move.m_nHandleID; }

protected:
	// 禁止开放
	VOID					SetCharacterLogic( ENUM_CHARACTER_LOGIC eLogic );

	virtual VOID			OnCharacterLogicStopped(BOOL bAbortive);

public:
	VOID					FaceTo( const WORLD_POS* pPos );
	VOID					FaceTo( const Obj* pObj );
	BOOL					IsLimitMove( VOID );			// 是否限制了移动操作
	VOID					DirectMoveTo(const WORLD_POS* pTar) ;
	/*
	BOOL					IsLimitUseSkill( VOID );		// 是否限制了使用技能的操作
	BOOL					IsLimitAttack( VOID );			// 是否限制了攻击
	BOOL					IsLimitAllHandle( VOID );		// 是否限制了所有操作
	*/

//=========================================================================================
// 以下行为、逻辑只能由Obj自身或AI才能调用(禁止开放!!!) -- 06/03/16
//=========================================================================================
private:
	ORESULT					Do_Idle( VOID );
	ORESULT					Do_Jump( VOID );
	ORESULT					Do_Stop( VOID );
	ORESULT					Do_Move( INT nHandleID, WORD wNumTargetPos, const WORLD_POS *paTargetPos, BOOL bFlag=FALSE );
	ORESULT					Do_UseSkill( SkillID_t idSkill, BYTE nLevel, ObjID_t idTarget, const WORLD_POS *pTargetPos, FLOAT fDir, GUID_t guidTarget);

	VOID					MoveTo( INT nHandleID, WORLD_POS* pTar ) ;
	VOID					MoveTo( INT nHandleID, WORLD_POS* pCur, WORLD_POS* pTar ) ;

private:
	BOOL					Obj_Logic_Idle( UINT uTime );
	BOOL					Obj_Logic_Move( UINT uTime );
	BOOL					Obj_Logic_UseSkill( UINT uTime );

//=========================================================================================
// 以下两个成员函数为生活技能服务，放在这里不太适合，建议与技能系统合并 -- 06/03/16
//=========================================================================================
protected:
	virtual ORESULT			Do_UseAbility( VOID ) { return OR_OK; }
	virtual BOOL			Obj_Logic_UseAbility( UINT uTime ) { return TRUE; }

///////////////////////////////////////////////////////////////////////////////////////////

//Sync
public:
	virtual VOID			SyncTeamMemberInfo( ) {}
	virtual VOID			SendMsg_RefeshAttrib( VOID );
	virtual VOID			AskMsg_BaseAttrib( Obj_Human *pTargetHuman );

//=========================================================================================
// 可见性
//=========================================================================================
public:
	virtual VOID			UpdateViewCharacter(VOID);

	INT						GetPrevLevel(VOID)const{return m_nView_PrevLevel;}
	INT						GetPrevStealthLevel(VOID)const{return m_nView_PrevStealthLevel;}
	INT						GetPrevDetectLevel(VOID)const{return m_nView_PrevDetectLevel;}

protected:
	INT			m_nView_PrevLevel;					// 等级
	INT			m_nView_PrevStealthLevel;			// 隐身等级
	INT			m_nView_PrevDetectLevel;			// 反隐等级
	CMyTimer	m_UpdateViewCharacterTimer;			// 隐身变化的心跳间隔

//=========================================================================================
// 复活点相关
//=========================================================================================
public:

	struct _RELIVE_INFO
	{
		// HP
		BOOL		m_bHPUsePercent;
		union
		{
			INT			m_nHP;
			INT			m_nHPPercent;
		};

		// MP
		BOOL		m_bMPUsePercent;
		union
		{
			INT			m_nMP;
			INT			m_nMPPercent;
		};

		// SP---另一种怒气叫法。。以后再改rage吧。
		BOOL		m_bSPUsePercent;
		union
		{
			INT			m_nSP;
			INT			m_nSPPercent;
		};

		// 复活点
		SceneID_t		m_SceneID;
		WORLD_POS		m_Pos;

		_RELIVE_INFO( VOID )
		{
			m_bHPUsePercent		= FALSE;
			m_nHP				= 0;
			m_bMPUsePercent		= FALSE;
			m_nMP				= 0;
			m_bSPUsePercent		= FALSE;
			m_nSP				= 0;
			m_SceneID			= INVALID_ID;
			m_Pos				= WORLD_POS( -1.f, -1.f );
		}

		VOID Reset( VOID )
		{
			m_bHPUsePercent		= FALSE;
			m_nHP				= 0;
			m_bMPUsePercent		= FALSE;
			m_nMP				= 0;
			m_bSPUsePercent		= FALSE;
			m_nSP				= 0;
			m_SceneID			= INVALID_ID;
			m_Pos				= WORLD_POS( -1.f, -1.f );
		}
	};

public:
	// 是否可以技能使用技能复活
	BOOL					IsCanRelive( VOID )const;

	// 得到复活信息
	// bSkillRelive		:	是否为技能复活
	virtual const _RELIVE_INFO		*GetReliveInfo( BOOL bSkillRelive )const;

	// 设置复活属性
	// bSkillRelive		:	是否为技能复活
	// pReliveInfo		:	复活信息
	virtual VOID			SetReliveInfo( BOOL bSkillRelive, const _RELIVE_INFO *pReliveInfo );

	// 重置复活的信息
	VOID					ResetReliveInfo( VOID );

protected:
	BOOL					m_bCanSkillRelive;			// 是否有技能复活
	_RELIVE_INFO			m_SkillReliveInfo;			// 技能复活的信息


public:
	virtual	VOID			SetName( const CHAR *pszName )=0;
	virtual const CHAR		*GetName( VOID )const=0;

	virtual	VOID			SetTitle( const CHAR *pszTitle )=0;
	virtual const CHAR		*GetTitle( VOID )const=0;

	virtual VOID			SetHP( INT nHP )=0;
	virtual INT				GetHP( VOID )=0;

	virtual VOID			SetMP( INT nMP )=0;
	virtual INT				GetMP( VOID )=0;

	virtual VOID			SetLevel( INT nLevel )=0;
	virtual INT				GetLevel( VOID )const=0;

	virtual UINT			GetExp( VOID ){ return 0; } 
	
	virtual INT				GetStrikePoint(VOID) {return 0;}
	virtual VOID			SetStrikePoint(INT nStrikePoint) {}

	//virtual INT				GetVigor(VOID) {return 0;}
	//virtual VOID			SetVigor(INT nVigor) {}

	//virtual INT				GetMaxVigor(VOID) {return 1;}
	//virtual VOID			SetMaxVigor(INT nMaxVigor) {}

	//virtual	INT				GetVigorRegeneRate(VOID){ return 0; }
	//virtual	VOID			SetVigorRegeneRate(INT nRate){}

	//virtual INT				GetEnergy(VOID) {return 0;}
	//virtual VOID			SetEnergy(INT nVigor) {}

	//virtual INT				GetMaxEnergy(VOID) {return 1;}
	//virtual VOID			SetMaxEnergy(INT nMaxVigor) {}

	//virtual	INT				GetEnergyRegeneRate(VOID){ return 0; }
	//virtual	VOID			SetEnergyRegeneRate(INT nRate){}

	virtual INT 			GetRage( VOID ){ return 0; }
	virtual VOID			SetRage( INT nRage ){ }

	virtual INT				GetMoodState(VOID)const{ return m_nMoodState; }
	virtual VOID			SetMoodState(INT nState){ m_nMoodState = nState; }

	virtual UINT			GetDataID( VOID )const{ return UINT_MAX; }

	virtual FLOAT			GetDropSearchRange() const {return 20.0f;}  //掉落搜索半径
	virtual INT				GetDropTeamCount() const {return 1;}		//掉落有效组数量
	virtual INT				GetMinDamagePercent() const {return 20;};	//最小伤血百分比

protected:
	INT						m_nMoodState;	// 表情状态

public:
//物品部分虚接口
	virtual	BOOL			IsCarrayItem(UINT ItemType,UINT ItemCount)	{ return TRUE;}
	virtual _ITEM_VALUE		ItemValue( BYTE AttrType )
	{//AttrType=enum ITEM_ATTRIBUTE 
		_ITEM_VALUE a ;
		a.CleanUp() ;
		return a ;
	};

///////////////////////////////////////////////////////////////////////////////////////
// 改变速度部分
public:
	enum ENUM_MOVE_MODE{
		MOVE_MODE_HOBBLE = 0,	// 蹒跚
		MOVE_MODE_WALK,			// 走	
		MOVE_MODE_RUN,			// 跑
		MOVE_MODE_SPRINT,		// 疾跑
	};

	VOID SetMoveMode(ENUM_MOVE_MODE eMoveMode) { m_eMoveMode = eMoveMode; }
    ENUM_MOVE_MODE GetMoveMode(VOID) const { return m_eMoveMode; }

private:
	ENUM_MOVE_MODE m_eMoveMode;

///////////////////////////////////////////////////////////////////////////////////////
protected :
	CMyTimer				m_SendMsgTimer ;	// 发送网络消息的计时
	BOOL					m_bSendMsgDirty;	// 是否发送过网络消息

	CMyTimer				m_AttrMsgTimer ;				// 属性刷新消息的计时
	BYTE					m_AttrMsgToTeamIntervalCount;	// 属性刷新消息刷新到队员的间隔次数
	BYTE					m_PublicAttrVersion;			// 公开属性的版本
	BYTE					m_ProtectedAttrVersion;			// 限制属性的版本

protected :
	ObjID_t					m_CharacterID ;		// 角色ID
	CMyTimer				m_RecoverTimer ;	// 回复时间控制器
	INT						m_nScriptTime ;//定时调用脚本的时间，单位（毫秒）
	CMyTimer				m_ScriptTimer ;	//定时调用脚本
	_LOGICPARAM_MOVE		m_paramLogic_Move;
	ENUM_CHARACTER_LOGIC	m_eCharacterLogic;
	BOOL					m_bCharacterLogicStopped;
	INT						m_DieTime;		//定时死亡时间
	INT						m_DriverLevel;	//坐骑等级

	AI_Character*			m_pAI_Character;	//AI数据

public:
	virtual ObjID_t			GetOwnerID( VOID ) const { return INVALID_ID; }
	virtual Obj_Character	*GetOwner( VOID ) { return NULL; }
	VOID					SetScriptTimer( INT nTime ) ;

	VOID					SetDieTime( INT nDieTime ){ m_DieTime = nDieTime; }
	INT						GetDieTime( VOID ){ return m_DieTime; }

	VOID					SetDriverLevel( INT nLevel ){ m_DriverLevel = nLevel; }
	INT						GetDriverLevel( VOID ){ return m_DriverLevel; }

protected :
	_CAMP_DATA				m_CampDataRefix;

//角色属性部分
public:
	//StrikePoint
	virtual INT 	GetMaxStrikePoint(VOID)		=	0;
	INT				GetBaseMaxStrikePoint(VOID) {return BASE_MAX_STRIKE_POINT;};
	INT				GetMaxStrikePointRefix(VOID);
	VOID			SetMaxStrikePointRefix(INT const nValue);
	BOOL			GetMaxStrikePointDirtyFlag(VOID);
	VOID			ClearMaxStrikePointDirtyFlag(VOID);
	VOID			MarkMaxStrikePointDirtyFlag(VOID);
	BOOL			GetMaxStrikePointRefixDirtyFlag(VOID);
	VOID			ClearMaxStrikePointRefixDirtyFlag(VOID);
	VOID			MarkMaxStrikePointRefixDirtyFlag(VOID);
	//Rage
	virtual INT   	GetMaxRage(VOID)=0;
	INT				GetBaseMaxRage(VOID) {return BASE_MAX_RAGE;};
	INT				GetMaxRageRefix(VOID);
	VOID			SetMaxRageRefix(INT const nValue);
	BOOL			GetMaxRageDirtyFlag(VOID);
	VOID			ClearMaxRageDirtyFlag(VOID);
	VOID			MarkMaxRageDirtyFlag(VOID);
	BOOL			GetMaxRageRefixDirtyFlag(VOID);
	VOID			ClearMaxRageRefixDirtyFlag(VOID);
	VOID			MarkMaxRageRefixDirtyFlag(VOID);
	//Attr1: Str
	virtual INT		GetStr(VOID)=0;
	virtual INT		GetBaseStr(VOID)=0;
	virtual VOID 	SetBaseStr(INT const nValue)=0;
	INT				GetStrRefix(VOID);
	VOID			SetStrRefix(INT const nValue);
	BOOL			GetStrDirtyFlag(VOID);
	VOID			ClearStrDirtyFlag(VOID);
	VOID			MarkStrDirtyFlag(VOID);
	BOOL			GetStrRefixDirtyFlag(VOID);
	VOID			ClearStrRefixDirtyFlag(VOID);
	VOID			MarkStrRefixDirtyFlag(VOID);
	//Attr1: Spr
	virtual INT		GetSpr(VOID)=0;
	virtual INT		GetBaseSpr(VOID)=0;
	virtual VOID	SetBaseSpr(INT const nValue)=0;
	INT				GetSprRefix(VOID);
	VOID			SetSprRefix(INT const nValue);
	BOOL			GetSprDirtyFlag(VOID);
	VOID			ClearSprDirtyFlag(VOID);
	VOID			MarkSprDirtyFlag(VOID);
	BOOL			GetSprRefixDirtyFlag(VOID);
	VOID			ClearSprRefixDirtyFlag(VOID);
	VOID			MarkSprRefixDirtyFlag(VOID);
	//Attr1: Con
	virtual INT		GetCon(VOID)=0;
	virtual INT		GetBaseCon(VOID)=0;
	virtual VOID	SetBaseCon(INT const nValue)=0;
	INT				GetConRefix(VOID);
	VOID			SetConRefix(INT const nValue);
	BOOL			GetConDirtyFlag(VOID);
	VOID			ClearConDirtyFlag(VOID);
	VOID			MarkConDirtyFlag(VOID);
	BOOL			GetConRefixDirtyFlag(VOID);
	VOID			ClearConRefixDirtyFlag(VOID);
	VOID			MarkConRefixDirtyFlag(VOID);
	//Attr1: Int
	virtual INT		GetInt(VOID)=0;
	virtual INT		GetBaseInt(VOID)=0;
	virtual VOID	SetBaseInt(INT const nValue)=0;
	INT				GetIntRefix(VOID);
	VOID			SetIntRefix(INT const nValue);
	BOOL			GetIntDirtyFlag(VOID);
	VOID			ClearIntDirtyFlag(VOID);
	VOID			MarkIntDirtyFlag(VOID);
	BOOL			GetIntRefixDirtyFlag(VOID);
	VOID			ClearIntRefixDirtyFlag(VOID);
	VOID			MarkIntRefixDirtyFlag(VOID);
	//Attr1: Dex
	virtual INT		GetDex(VOID)=0;
	virtual INT		GetBaseDex(VOID)=0;
	virtual VOID	SetBaseDex(INT const nValue)=0;
	INT				GetDexRefix(VOID);
	VOID			SetDexRefix(INT const nValue);
	BOOL			GetDexDirtyFlag(VOID);
	VOID			ClearDexDirtyFlag(VOID);
	VOID			MarkDexDirtyFlag(VOID);
	BOOL			GetDexRefixDirtyFlag(VOID);
	VOID			ClearDexRefixDirtyFlag(VOID);
	VOID			MarkDexRefixDirtyFlag(VOID);
	//HP
	virtual INT		GetMaxHP(VOID) =0; 
	virtual INT 	GetBaseMaxHP(VOID)=0;
	virtual VOID 	SetBaseMaxHP(INT const nHp)=0;
	INT 			GetMaxHPRefix(VOID);
	VOID 			SetMaxHPRefix(INT const nHp);
	BOOL			GetMaxHPDirtyFlag(VOID);
	VOID			ClearMaxHPDirtyFlag(VOID);
	VOID			MarkMaxHPDirtyFlag(VOID);
	BOOL			GetMaxHPRefixDirtyFlag(VOID);
	VOID			ClearMaxHPRefixDirtyFlag(VOID);
	VOID			MarkMaxHPRefixDirtyFlag(VOID);
	virtual INT		GetHPRegenerate(VOID) =0; 
	virtual INT 	GetBaseHPRegenerate(VOID)=0;
	virtual VOID 	SetBaseHPRegenerate(INT const nValue)=0;
	INT 			GetHPRegenerateRefix(VOID);
	VOID 			SetHPRegenerateRefix(INT const nValue);
	BOOL			GetHPRegenerateDirtyFlag(VOID);
	VOID			ClearHPRegenerateDirtyFlag(VOID);
	VOID			MarkHPRegenerateDirtyFlag(VOID);
	BOOL			GetHPRegenerateRefixDirtyFlag(VOID);
	VOID			ClearHPRegenerateRefixDirtyFlag(VOID);
	VOID			MarkHPRegenerateRefixDirtyFlag(VOID);

	//MP
	virtual INT 	GetMaxMP(VOID)=0;
	virtual INT 	GetBaseMaxMP(VOID)=0;
	virtual VOID 	SetBaseMaxMp(INT const nMp)=0;
	INT 			GetMaxMPRefix(VOID);
	VOID			SetMaxMPRefix(INT const nMp);
	BOOL			GetMaxMPDirtyFlag(VOID);
	VOID			ClearMaxMPDirtyFlag(VOID);
	VOID			MarkMaxMPDirtyFlag(VOID);
	BOOL			GetMaxMPRefixDirtyFlag(VOID);
	VOID			ClearMaxMPRefixDirtyFlag(VOID);
	VOID			MarkMaxMPRefixDirtyFlag(VOID);
	virtual INT		GetMPRegenerate(VOID)=0; 
	virtual INT 	GetBaseMPRegenerate(VOID)=0;
	virtual VOID 	SetBaseMPRegenerate(INT const nValue)=0;
	INT 			GetMPRegenerateRefix(VOID);
	VOID 			SetMPRegenerateRefix(INT const nValue);
	BOOL			GetMPRegenerateDirtyFlag(VOID);
	VOID			ClearMPRegenerateDirtyFlag(VOID);
	VOID			MarkMPRegenerateDirtyFlag(VOID);
	BOOL			GetMPRegenerateRefixDirtyFlag(VOID);
	VOID			ClearMPRegenerateRefixDirtyFlag(VOID);
	VOID			MarkMPRegenerateRefixDirtyFlag(VOID);
	//CampID
	virtual const _CAMP_DATA	*GetCampData(VOID);
	virtual const _CAMP_DATA	*GetBaseCampData(VOID)const=0;
	virtual VOID				SetBaseCampData(const _CAMP_DATA *pCampData)=0;
	virtual INT 	GetCampID(VOID)=0;
	virtual INT 	GetBaseCampID(VOID) const=0;
	virtual VOID	SetBaseCampID(INT const nID)=0;
	INT				GetCampIDRefix(VOID);
	VOID			SetCampIDRefix(CampID_t const nID);
	BOOL			GetCampIDDirtyFlag(VOID);
	VOID			ClearCampIDDirtyFlag(VOID);
	VOID			MarkCampIDDirtyFlag(VOID);
	BOOL			GetCampIDRefixDirtyFlag(VOID);
	VOID			ClearCampIDRefixDirtyFlag(VOID);
	VOID			MarkCampIDRefixDirtyFlag(VOID);
	//modelID
	virtual INT 	GetModelID(VOID);
	virtual INT 	GetBaseModelID(VOID) const=0;
	virtual VOID	SetBaseModelID(INT const nID)=0;
	INT				GetModelIDRefix(VOID);
	VOID			SetModelIDRefix(ID_t const nID);
	BOOL			GetModelIDDirtyFlag(VOID);
	VOID			ClearModelIDDirtyFlag(VOID);
	VOID			MarkModelIDDirtyFlag(VOID);
	BOOL			GetModelIDRefixDirtyFlag(VOID);
	VOID			ClearModelIDRefixDirtyFlag(VOID);
	VOID			MarkModelIDRefixDirtyFlag(VOID);
	//MountID
	virtual INT 	GetMountID(VOID);
	virtual INT 	GetBaseMountID(VOID) const{return INVALID_ID;};
	virtual VOID	SetBaseMountID(INT const nID){}; //不允许进行修改
	INT				GetMountIDRefix(VOID);
	VOID			SetMountIDRefix(ID_t const nID);
	BOOL			GetMountIDDirtyFlag(VOID);
	VOID			ClearMountIDDirtyFlag(VOID);
	VOID			MarkMountIDDirtyFlag(VOID);
	BOOL			GetMountIDRefixDirtyFlag(VOID);
	VOID			ClearMountIDRefixDirtyFlag(VOID);
	VOID			MarkMountIDRefixDirtyFlag(VOID);
	//Exp Refix
	INT 			GetExpRefix(VOID);
	INT 			GetBaseExpRefix(VOID) const{return 100;};//100%
	VOID			SetBaseExpRefix(INT const nID){}; //不允许进行修改
	INT				GetExpRefixRefix(VOID);
	VOID			SetExpRefixRefix(ID_t const nID);
	BOOL			GetExpRefixDirtyFlag(VOID);
	VOID			ClearExpRefixDirtyFlag(VOID);
	VOID			MarkExpRefixDirtyFlag(VOID);
	BOOL			GetExpRefixRefixDirtyFlag(VOID);
	VOID			ClearExpRefixRefixDirtyFlag(VOID);
	VOID			MarkExpRefixRefixDirtyFlag(VOID);
	//StealthLevel
	virtual INT 	GetStealthLevel(VOID);
	INT				GetStealthLevelRefix(VOID);
	VOID			SetStealthLevelRefix(ID_t const nID);
	BOOL			GetStealthLevelDirtyFlag(VOID);
	VOID			ClearStealthLevelDirtyFlag(VOID);
	VOID			MarkStealthLevelDirtyFlag(VOID);
	BOOL			GetStealthLevelRefixDirtyFlag(VOID);
	VOID			ClearStealthLevelRefixDirtyFlag(VOID);
	VOID			MarkStealthLevelRefixDirtyFlag(VOID);

	//DetectLevel
	virtual INT 	GetDetectLevel(VOID);
	INT				GetDetectLevelRefix(VOID);
	VOID			SetDetectLevelRefix(ID_t const nID);
	BOOL			GetDetectLevelDirtyFlag(VOID);
	VOID			ClearDetectLevelDirtyFlag(VOID);
	VOID			MarkDetectLevelDirtyFlag(VOID);
	BOOL			GetDetectLevelRefixDirtyFlag(VOID);
	VOID			ClearDetectLevelRefixDirtyFlag(VOID);
	VOID			MarkDetectLevelRefixDirtyFlag(VOID);

	//Alive flag
	BOOL			IsAlive(VOID);
	BOOL			IsAliveInDeed(VOID);
	BOOL			IsDie(VOID);
	VOID			ClearAliveFlag(VOID);
	VOID			MarkAliveFlag(VOID);
	BOOL			GetAliveDirtyFlag(VOID);
	VOID			ClearAliveDirtyFlag(VOID);
	VOID			MarkAliveDirtyFlag(VOID);
	//BOOL			GetAliveRefixDirtyFlag(VOID);
	//VOID			ClearAliveRefixDirtyFlag(VOID);
	//VOID			MarkAliveRefixDirtyFlag(VOID);
	//In Combat flag
	BOOL			InCombat(VOID) const;
	VOID			ClearCombatFlag(VOID);
	VOID			MarkCombatFlag(VOID);
	// Can move flag
	BOOL			CanMove(VOID);
	VOID			ClearCanMoveFlag(VOID);
	VOID			MarkCanMoveFlag(VOID);
	BOOL			GetCanMoveDirtyFlag(VOID);
	VOID			ClearCanMoveDirtyFlag(VOID);
	VOID			MarkCanMoveDirtyFlag(VOID);
	//BOOL			GetCanMoveRefixDirtyFlag(VOID);
	//VOID			ClearCanMoveRefixDirtyFlag(VOID);
	//VOID			MarkCanMoveRefixDirtyFlag(VOID);
	// Can Action flag 1
	BOOL			CanActionFlag1(VOID);
	VOID			ClearCanActionFlag1(VOID);
	VOID			MarkCanActionFlag1(VOID);
	BOOL			GetCanAction1DirtyFlag(VOID);
	VOID			ClearCanAction1DirtyFlag(VOID);
	VOID			MarkCanAction1DirtyFlag(VOID);
	//BOOL			GetCanAction1RefixDirtyFlag(VOID);
	//VOID			ClearCanAction1RefixDirtyFlag(VOID);
	//VOID			MarkCanAction1RefixDirtyFlag(VOID);
	// Can Action flag 2
	BOOL			CanActionFlag2(VOID);
	VOID			ClearCanActionFlag2(VOID);
	VOID			MarkCanActionFlag2(VOID);
	BOOL			GetCanAction2DirtyFlag(VOID);
	VOID			ClearCanAction2DirtyFlag(VOID);
	VOID			MarkCanAction2DirtyFlag(VOID);
	//BOOL			GetCanAction2RefixDirtyFlag(VOID);
	//VOID			ClearCanAction2RefixDirtyFlag(VOID);
	//VOID			MarkCanAction2RefixDirtyFlag(VOID);
	// Unbreakable flag
	virtual BOOL	IsUnbreakable(VOID);
	VOID			ClearUnbreakableFlag(VOID);
	VOID			MarkUnbreakableFlag(VOID);
	BOOL			GetUnbreakableDirtyFlag(VOID);
	VOID			ClearUnbreakableDirtyFlag(VOID);
	VOID			MarkUnbreakableDirtyFlag(VOID);
	//BOOL			GetUnbreakableRefixDirtyFlag(VOID);
	//VOID			ClearUnbreakableRefixDirtyFlag(VOID);
	//VOID			MarkUnbreakableRefixDirtyFlag(VOID);
	/*
	// InStealthMode flag
	virtual BOOL	InStealthMode(VOID);
	VOID			ClearInStealthModeFlag(VOID);
	VOID			MarkInStealthModeFlag(VOID);
	BOOL			GetInStealthModeDirtyFlag(VOID);
	VOID			ClearInStealthModeDirtyFlag(VOID);
	VOID			MarkInStealthModeDirtyFlag(VOID);
	//BOOL			GetInStealthModeRefixDirtyFlag(VOID);
	//VOID			ClearInStealthModeRefixDirtyFlag(VOID);
	//VOID			MarkInStealthModeRefixDirtyFlag(VOID);
	// CanDetectStealth flag
	virtual BOOL	CanDetectStealth(VOID);
	VOID			ClearCanDetectStealthFlag(VOID);
	VOID			MarkCanDetectStealthFlag(VOID);
	BOOL			GetCanDetectStealthDirtyFlag(VOID);
	VOID			ClearCanDetectStealthDirtyFlag(VOID);
	VOID			MarkCanDetectStealthDirtyFlag(VOID);
	//BOOL			GetCanDetectStealthRefixDirtyFlag(VOID);
	//VOID			ClearCanDetectStealthRefixDirtyFlag(VOID);
	//VOID			MarkCanDetectStealthRefixDirtyFlag(VOID);
	*/
	// Attr2: Move Speed
	virtual FLOAT	GetMoveSpeed(VOID)=0;
	virtual INT		GetBaseMoveSpeed(VOID)=0;
	virtual VOID	SetBaseMoveSpeed(INT const nValue)=0;
	INT 			GetMoveSpeedRefix(VOID);
	VOID			SetMoveSpeedRefix(INT const nValue);
	BOOL			GetMoveSpeedDirtyFlag(VOID);
	VOID			ClearMoveSpeedDirtyFlag(VOID);
	VOID			MarkMoveSpeedDirtyFlag(VOID);
	BOOL			GetMoveSpeedRefixDirtyFlag(VOID);
	VOID			ClearMoveSpeedRefixDirtyFlag(VOID);
	VOID			MarkMoveSpeedRefixDirtyFlag(VOID);
	// Attr2: Attack Speed
	virtual INT 	GetAttackSpeed(VOID)=0;
	virtual INT 	GetBaseAttackSpeed(VOID)=0;
	virtual VOID	SetBaseAttackSpeed(INT const nValue)=0;
	INT				GetAttackSpeedRefix(VOID);
	VOID			SetAttackSpeedRefix(INT const nValue);
	BOOL			GetAttackSpeedDirtyFlag(VOID);
	VOID			ClearAttackSpeedDirtyFlag(VOID);
	VOID			MarkAttackSpeedDirtyFlag(VOID);
	BOOL			GetAttackSpeedRefixDirtyFlag(VOID);
	VOID			ClearAttackSpeedRefixDirtyFlag(VOID);
	VOID			MarkAttackSpeedRefixDirtyFlag(VOID);
	// Attr2: Miss
	virtual INT 	GetMiss(VOID)=0;
	virtual INT 	GetBaseMiss(VOID)=0;
	virtual VOID	SetBaseMiss(INT const nValue)=0;
	INT				GetMissRefix(VOID);
	VOID			SetMissRefix(INT const nValue);
	BOOL			GetMissDirtyFlag(VOID);
	VOID			ClearMissDirtyFlag(VOID);
	VOID			MarkMissDirtyFlag(VOID);
	BOOL			GetMissRefixDirtyFlag(VOID);
	VOID			ClearMissRefixDirtyFlag(VOID);
	VOID			MarkMissRefixDirtyFlag(VOID);
	// Attr2 Hit
	virtual INT 	GetHit(VOID)=0;
	virtual INT 	GetBaseHit(VOID)=0;
	virtual VOID	SetBaseHit(INT const nValue)=0;
	INT				GetHitRefix(VOID);
	VOID			SetHitRefix(INT const nValue);
	BOOL			GetHitDirtyFlag(VOID);
	VOID			ClearHitDirtyFlag(VOID);
	VOID			MarkHitDirtyFlag(VOID);
	BOOL			GetHitRefixDirtyFlag(VOID);
	VOID			ClearHitRefixDirtyFlag(VOID);
	VOID			MarkHitRefixDirtyFlag(VOID);
	// Attr2 Critical
	virtual INT 	GetCritical(VOID)=0;
	virtual INT 	GetBaseCritical(VOID)=0;
	virtual VOID	SetBaseCritical(INT const nValue)=0;
	INT				GetCriticalRefix(VOID);
	VOID			SetCriticalRefix(INT const nValue);
	BOOL			GetCriticalDirtyFlag(VOID);
	VOID			ClearCriticalDirtyFlag(VOID);
	VOID			MarkCriticalDirtyFlag(VOID);
	BOOL			GetCriticalRefixDirtyFlag(VOID);
	VOID			ClearCriticalRefixDirtyFlag(VOID);
	VOID			MarkCriticalRefixDirtyFlag(VOID);
	// Attr2: Attack and Defence power physics
	virtual INT 	GetAttackPhysics(VOID)=0;
	virtual INT 	GetBaseAttackPhysics(VOID)=0;
	virtual VOID	SetBaseAttackPhysics(INT const nValue)=0;
	INT				GetAttackPhysicsRefix(VOID);
	VOID			SetAttackPhysicsRefix(INT const nValue);
	BOOL			GetAttackPhysicsDirtyFlag(VOID);
	VOID			ClearAttackPhysicsDirtyFlag(VOID);
	VOID			MarkAttackPhysicsDirtyFlag(VOID);
	BOOL			GetAttackPhysicsRefixDirtyFlag(VOID);
	VOID			ClearAttackPhysicsRefixDirtyFlag(VOID);
	VOID			MarkAttackPhysicsRefixDirtyFlag(VOID);
	virtual INT 	GetDefencePhysics(VOID)=0;
	virtual INT 	GetBaseDefencePhysics(VOID)=0;
	virtual VOID	SetBaseDefencePhysics(INT const nValue)=0;
	INT				GetDefencePhysicsRefix(VOID);
	VOID			SetDefencePhysicsRefix(INT const nValue);
	BOOL			GetDefencePhysicsDirtyFlag(VOID);
	VOID			ClearDefencePhysicsDirtyFlag(VOID);
	VOID			MarkDefencePhysicsDirtyFlag(VOID);
	BOOL			GetDefencePhysicsRefixDirtyFlag(VOID);
	VOID			ClearDefencePhysicsRefixDirtyFlag(VOID);
	VOID			MarkDefencePhysicsRefixDirtyFlag(VOID);
	// Attr2: Attack and Defence power of Magic
	virtual INT 	GetAttackMagic(VOID)=0;
	virtual INT 	GetBaseAttackMagic(VOID)=0;
	virtual VOID	SetBaseAttackMagic(INT const nValue)=0;
	INT				GetAttackMagicRefix(VOID);
	VOID			SetAttackMagicRefix(INT const nValue);
	BOOL			GetAttackMagicDirtyFlag(VOID);
	VOID			ClearAttackMagicDirtyFlag(VOID);
	VOID			MarkAttackMagicDirtyFlag(VOID);
	BOOL			GetAttackMagicRefixDirtyFlag(VOID);
	VOID			ClearAttackMagicRefixDirtyFlag(VOID);
	VOID			MarkAttackMagicRefixDirtyFlag(VOID);
	virtual INT 	GetDefenceMagic(VOID)=0;
	virtual INT 	GetBaseDefenceMagic(VOID)=0;
	virtual VOID	SetBaseDefenceMagic(INT const nValue)=0;
	INT				GetDefenceMagicRefix(VOID);
	VOID			SetDefenceMagicRefix(INT const nValue);
	BOOL			GetDefenceMagicDirtyFlag(VOID);
	VOID			ClearDefenceMagicDirtyFlag(VOID);
	VOID			MarkDefenceMagicDirtyFlag(VOID);
	BOOL			GetDefenceMagicRefixDirtyFlag(VOID);
	VOID			ClearDefenceMagicRefixDirtyFlag(VOID);
	VOID			MarkDefenceMagicRefixDirtyFlag(VOID);
	// Attr2: Attack and Defence power of Cold
	virtual INT 	GetAttackCold(VOID)=0;
	virtual INT 	GetBaseAttackCold(VOID)=0;
	virtual VOID	SetBaseAttackCold(INT const nValue)=0;
	INT				GetAttackColdRefix(VOID);
	VOID			SetAttackColdRefix(INT const nValue);
	BOOL			GetAttackColdDirtyFlag(VOID);
	VOID			ClearAttackColdDirtyFlag(VOID);
	VOID			MarkAttackColdDirtyFlag(VOID);
	BOOL			GetAttackColdRefixDirtyFlag(VOID);
	VOID			ClearAttackColdRefixDirtyFlag(VOID);
	VOID			MarkAttackColdRefixDirtyFlag(VOID);
	virtual INT 	GetDefenceCold(VOID)=0;
	virtual INT 	GetBaseDefenceCold(VOID)=0;
	virtual VOID	SetBaseDefenceCold(INT const nValue)=0;
	INT				GetDefenceColdRefix(VOID);
	VOID			SetDefenceColdRefix(INT const nValue);
	BOOL			GetResistColdDirtyFlag(VOID);
	VOID			ClearResistColdDirtyFlag(VOID);
	VOID			MarkResistColdDirtyFlag(VOID);
	BOOL			GetResistColdRefixDirtyFlag(VOID);
	VOID			ClearResistColdRefixDirtyFlag(VOID);
	VOID			MarkResistColdRefixDirtyFlag(VOID);
	// Attr2: Attack and Defence power of Fire
	virtual INT 	GetAttackFire(VOID)=0;
	virtual INT 	GetBaseAttackFire(VOID)=0;
	virtual VOID	SetBaseAttackFire(INT const nValue)=0;
	INT				GetAttackFireRefix(VOID);
	VOID			SetAttackFireRefix(INT const nValue);
	BOOL			GetAttackFireDirtyFlag(VOID);
	VOID			ClearAttackFireDirtyFlag(VOID);
	VOID			MarkAttackFireDirtyFlag(VOID);
	BOOL			GetAttackFireRefixDirtyFlag(VOID);
	VOID			ClearAttackFireRefixDirtyFlag(VOID);
	VOID			MarkAttackFireRefixDirtyFlag(VOID);
	virtual INT 	GetDefenceFire(VOID)=0;
	virtual INT 	GetBaseDefenceFire(VOID)=0;
	virtual VOID	SetBaseDefenceFire(INT const nValue)=0;
	INT				GetDefenceFireRefix(VOID);
	VOID			SetDefenceFireRefix(INT const nValue);
	BOOL			GetResistFireDirtyFlag(VOID);
	VOID			ClearResistFireDirtyFlag(VOID);
	VOID			MarkResistFireDirtyFlag(VOID);
	BOOL			GetResistFireRefixDirtyFlag(VOID);
	VOID			ClearResistFireRefixDirtyFlag(VOID);
	VOID			MarkResistFireRefixDirtyFlag(VOID);
	// Attr2: Attack and Defence power of Light
	virtual INT 	GetAttackLight(VOID)=0;
	virtual INT 	GetBaseAttackLight(VOID)=0;
	virtual VOID	SetBaseAttackLight(INT const nValue)=0;
	INT				GetAttackLightRefix(VOID);
	VOID			SetAttackLightRefix(INT const nValue);
	BOOL			GetAttackLightDirtyFlag(VOID);
	VOID			ClearAttackLightDirtyFlag(VOID);
	VOID			MarkAttackLightDirtyFlag(VOID);
	BOOL			GetAttackLightRefixDirtyFlag(VOID);
	VOID			ClearAttackLightRefixDirtyFlag(VOID);
	VOID			MarkAttackLightRefixDirtyFlag(VOID);
	virtual INT 	GetDefenceLight(VOID)=0;
	virtual INT 	GetBaseDefenceLight(VOID)=0;
	virtual VOID	SetBaseDefenceLight(INT const nValue)=0;
	INT				GetDefenceLightRefix(VOID);
	VOID			SetDefenceLightRefix(INT const nValue);
	BOOL			GetResistLightDirtyFlag(VOID);
	VOID			ClearResistLightDirtyFlag(VOID);
	VOID			MarkResistLightDirtyFlag(VOID);
	BOOL			GetResistLightRefixDirtyFlag(VOID);
	VOID			ClearResistLightRefixDirtyFlag(VOID);
	VOID			MarkResistLightRefixDirtyFlag(VOID);
	// Attr2: Attack and Defence power of Poison
	virtual INT 	GetAttackPoison(VOID)=0;
	virtual INT 	GetBaseAttackPoison(VOID)=0;
	virtual VOID	SetBaseAttackPoison(INT const nValue)=0;
	INT				GetAttackPoisonRefix(VOID);
	VOID			SetAttackPoisonRefix(INT const nValue);
	BOOL			GetAttackPoisonDirtyFlag(VOID);
	VOID			ClearAttackPoisonDirtyFlag(VOID);
	VOID			MarkAttackPoisonDirtyFlag(VOID);
	BOOL			GetAttackPoisonRefixDirtyFlag(VOID);
	VOID			ClearAttackPoisonRefixDirtyFlag(VOID);
	VOID			MarkAttackPoisonRefixDirtyFlag(VOID);
	virtual INT 	GetDefencePoison(VOID)=0;
	virtual INT 	GetBaseDefencePoison(VOID)=0;
	virtual VOID	SetBaseDefencePoison(INT const nValue)=0;
	INT				GetDefencePoisonRefix(VOID);
	VOID			SetDefencePoisonRefix(INT const nValue);
	BOOL			GetResistPoisonDirtyFlag(VOID);
	VOID			ClearResistPoisonDirtyFlag(VOID);
	VOID			MarkResistPoisonDirtyFlag(VOID);
	BOOL			GetResistPoisonRefixDirtyFlag(VOID);
	VOID			ClearResistPoisonRefixDirtyFlag(VOID);
	VOID			MarkResistPoisonRefixDirtyFlag(VOID);
	// Attr2 Reduce Slower Duration
	virtual INT 	GetReduceSlowerDuration(VOID)=0;
	INT				GetReduceSlowerDurationRefix(VOID);
	VOID			SetReduceSlowerDurationRefix(INT const nValue);
	BOOL			GetReduceSlowerDurationDirtyFlag(VOID);
	VOID			ClearReduceSlowerDurationDirtyFlag(VOID);
	VOID			MarkReduceSlowerDurationDirtyFlag(VOID);
	BOOL			GetReduceSlowerDurationRefixDirtyFlag(VOID);
	VOID			ClearReduceSlowerDurationRefixDirtyFlag(VOID);
	VOID			MarkReduceSlowerDurationRefixDirtyFlag(VOID);
	// Attr2 Reduce Weaken Duration
	virtual INT 	GetReduceWeakenDuration(VOID)=0;
	INT				GetReduceWeakenDurationRefix(VOID);
	VOID			SetReduceWeakenDurationRefix(INT const nValue);
	BOOL			GetReduceWeakenDurationDirtyFlag(VOID);
	VOID			ClearReduceWeakenDurationDirtyFlag(VOID);
	VOID			MarkReduceWeakenDurationDirtyFlag(VOID);
	BOOL			GetReduceWeakenDurationRefixDirtyFlag(VOID);
	VOID			ClearReduceWeakenDurationRefixDirtyFlag(VOID);
	VOID			MarkReduceWeakenDurationRefixDirtyFlag(VOID);
	// Attr2 Reduce Faint Duration
	virtual INT 	GetReduceFaintDuration(VOID)=0;
	INT				GetReduceFaintDurationRefix(VOID);
	VOID			SetReduceFaintDurationRefix(INT const nValue);
	BOOL			GetReduceFaintDurationDirtyFlag(VOID);
	VOID			ClearReduceFaintDurationDirtyFlag(VOID);
	VOID			MarkReduceFaintDurationDirtyFlag(VOID);
	BOOL			GetReduceFaintDurationRefixDirtyFlag(VOID);
	VOID			ClearReduceFaintDurationRefixDirtyFlag(VOID);
	VOID			MarkReduceFaintDurationRefixDirtyFlag(VOID);
	// Attr2 Reduce Poisoned Duration
	virtual INT 	GetReducePoisonedDuration(VOID)=0;
	INT				GetReducePoisonedDurationRefix(VOID);
	VOID			SetReducePoisonedDurationRefix(INT const nValue);
	BOOL			GetReducePoisonedDurationDirtyFlag(VOID);
	VOID			ClearReducePoisonedDurationDirtyFlag(VOID);
	VOID			MarkReducePoisonedDurationDirtyFlag(VOID);
	BOOL			GetReducePoisonedDurationRefixDirtyFlag(VOID);
	VOID			ClearReducePoisonedDurationRefixDirtyFlag(VOID);
	VOID			MarkReducePoisonedDurationRefixDirtyFlag(VOID);
	// Attr2 VisionRange
	virtual INT 	GetVisionRange(VOID)=0;
	virtual INT 	GetBaseVisionRange(VOID)=0;
	virtual VOID	SetBaseVisionRange(INT const nValue)=0;
	INT				GetVisionRangeRefix(VOID);
	VOID			SetVisionRangeRefix(INT const nValue);
	BOOL			GetVisionRangeDirtyFlag(VOID);
	VOID			ClearVisionRangeDirtyFlag(VOID);
	VOID			MarkVisionRangeDirtyFlag(VOID);
	BOOL			GetVisionRangeRefixDirtyFlag(VOID);
	VOID			ClearVisionRangeRefixDirtyFlag(VOID);
	VOID			MarkVisionRangeRefixDirtyFlag(VOID);
protected:
	//Here open to sub class to modify those is virtual functions.
	//整数属性
	INT		GetIntAttr(CharIntAttrs_T::Index_T const nIdx) const {return m_IntAttrs.GetAttr(nIdx);};
	VOID 	SetIntAttr(CharIntAttrs_T::Index_T const nIdx, INT const nValue){m_IntAttrs.SetAttr(nIdx, nValue);};
	VOID 	ResetIntAttrs(VOID);
	
	//整数属性修正
	INT		GetIntAttrRefix(CharIntAttrRefixs_T::Index_T const nIdx) const {return m_IntAttrRefixs.GetAttr(nIdx);};
	VOID	SetIntAttrRefix(CharIntAttrRefixs_T::Index_T const nIdx, INT const nValue){m_IntAttrRefixs.SetAttr(nIdx,nValue);};
	VOID 	ResetIntAttrRefixs(VOID);

	//BOOL属性
	BOOL	GetBoolAttr(CharBoolAttrs_T::Index_T const nIdx) const{return m_BoolAttrs.GetAttr(nIdx);};
	VOID	SetBoolAttr(CharBoolAttrs_T::Index_T const nIdx, BOOL const bFlag) {m_BoolAttrs.SetAttr(nIdx, bFlag);};
	VOID	ResetBoolAttr(VOID);

	//设置所有的脏标记
	VOID	MarkAllIntAttrDirtyFlags(VOID) {m_IntAttrDirtyFlags.MarkAllFlags();};
	VOID	MarkAllBoolAttrDirtyFlags(VOID) {m_BoolAttrDirtyFlags.MarkAllFlags();};	
	VOID	MarkAllIntAttrRefixDirtyFlags(VOID) {m_IntAttrRefixDirtyFlags.MarkAllFlags();};

private:
	//整数属性脏标记
	BOOL	GetIntAttrDirtyFlag(CharIntAttrs_T::Index_T const nIdx) const {return m_IntAttrDirtyFlags.GetFlagByIndex(nIdx);};
	VOID	ClearIntAttrDirtyFlag(CharIntAttrs_T::Index_T const nIdx) {m_IntAttrDirtyFlags.ClearFlagByIndex(nIdx);};
	VOID	MarkIntAttrDirtyFlag(CharIntAttrs_T::Index_T const nIdx) {m_IntAttrDirtyFlags.MarkFlagByIndex(nIdx);};


	//BOOL属性脏标记
	BOOL	GetBoolAttrDirtyFlag(CharBoolAttrs_T::Index_T const nIdx) const {m_BoolAttrDirtyFlags.GetFlagByIndex(nIdx);};
	VOID	ClearBoolAttrDirtyFlag(CharBoolAttrs_T::Index_T const nIdx) {m_BoolAttrDirtyFlags.ClearFlagByIndex(nIdx);};
	VOID	MarkBoolAttrDirtyFlag(CharBoolAttrs_T::Index_T const nIdx) {m_BoolAttrDirtyFlags.MarkFlagByIndex(nIdx);};

	//整数属性修正的脏标记
	BOOL	GetIntAttrRefixDirtyFlag(CharIntAttrRefixs_T::Index_T const nIdx) const {return m_IntAttrRefixDirtyFlags.GetFlagByIndex(nIdx);};
	VOID	ClearIntAttrRefixDirtyFlag(CharIntAttrRefixs_T::Index_T const nIdx) {m_IntAttrRefixDirtyFlags.ClearFlagByIndex(nIdx);};
	VOID	MarkIntAttrRefixDirtyFlag(CharIntAttrRefixs_T::Index_T const nIdx) {m_IntAttrRefixDirtyFlags.MarkFlagByIndex(nIdx);};
/*
	//BOOL属性修正的脏标记
	BOOL	GetBoolAttrRefixDirtyFlag(CharBoolAttrs_T::Index_T const nIdx) const {return m_BoolAttrRefixDirtyFlags.GetFlagByIndex(nIdx);};
	VOID	ClearBoolAttrRefixDirtyFlag(CharBoolAttrs_T::Index_T const nIdx) {m_BoolAttrRefixDirtyFlags.ClearFlagByIndex(nIdx);};
	VOID	MarkBoolAttrRefixDirtyFlag(CharBoolAttrs_T::Index_T const nIdx) {m_BoolAttrRefixDirtyFlags.MarkFlagByIndex(nIdx);};
	VOID	MarkAllBoolAttrRefixDirtyFlags(VOID) {m_BoolAttrRefixDirtyFlags.MarkAllFlags();};
*/
private :
	//整数属性
	CharIntAttrs_T m_IntAttrs;
	//整数属性修正
	CharIntAttrRefixs_T m_IntAttrRefixs;
	//整数属性脏标记
	typedef BitFlagSet_T<CharIntAttrs_T::MAX_INDEX> CharIntAttrDirtyFlags_T;
	CharIntAttrDirtyFlags_T m_IntAttrDirtyFlags;
	//BOOL属性
	CharBoolAttrs_T m_BoolAttrs;
	//BOOL属性脏标记
	typedef BitFlagSet_T<CharBoolAttrs_T::MAX_INDEX> CharBoolAttrDirtyFlags_T;
	CharBoolAttrDirtyFlags_T m_BoolAttrDirtyFlags;
	//整数属性修正的脏标记
	typedef BitFlagSet_T<CharIntAttrRefixs_T::MAX_INDEX> CharIntAttrRefixDirtyFlags_T;
	CharIntAttrRefixDirtyFlags_T m_IntAttrRefixDirtyFlags;
/*	//BOOL属性修正的脏标记
	typedef BitFlagSet_T<CharBoolAttrs_T::MAX_INDEX> CharBoolAttrRefixDirtyFlags_T;
	CharBoolAttrRefixDirtyFlags_T m_BoolAttrRefixDirtyFlags;
*/
/////////////////////////////////////////////////////////////////////////////////
//obj 公共属性接口

/////////////////////////////////////////////////////////////////////////////////
//character 公共属性接口
public :
};
#endif
