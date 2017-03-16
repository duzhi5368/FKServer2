// Obj_Pet.h
//
// 功能：宠物在SERVER的实现
// 
///////////////////////////////////////////////////////

#ifndef __PET_H__
#define __PET_H__

#include "Obj_Character.h"

//////////////////////////////////////////////////////
// 初始化Obj_Pet的结构
//////////////////////////////////////////////////////
struct _OBJ_PET_INIT :
	public _OBJ_CHARACTER_INIT
{
	GUID_t			m_GUID;			// 角色在场景中的GUID，与PetGUID是两回事
	_PET_DB			m_PetDB;
	ObjID_t			m_CreatorID;	// 所有者的ID，即宠物的主人
	INT				m_nIndex;		// 在主人宠物槽中的索引
	INT				m_RespawnTime;
	ScriptID_t		m_ScriptID ;	// 绑定的脚本

	_OBJ_PET_INIT( VOID )
	{
		m_GUID			= INVALID_GUID;
		m_PetDB.CleanUp();
		m_CreatorID		= INVALID_ID;
		m_nIndex		= -1;
		m_RespawnTime	= -1;
		m_ScriptID		= INVALID_ID;
	}

	virtual VOID CleanUp( VOID )
	{
		m_GUID			= INVALID_GUID;
		m_PetDB.CleanUp();
		m_CreatorID		= INVALID_ID;
		m_nIndex		= -1;
		m_RespawnTime	= -1;
		m_ScriptID		= INVALID_ID;

		_OBJ_CHARACTER_INIT::CleanUp();
	}
};

//////////////////////////////////////////////////////
// 属性刷新的上一次属性的保存结构
//////////////////////////////////////////////////////
struct _PET_ATTR_BACKUP
{
public:
	BOOL		m_bNameModified;
	BOOL		m_bTitleModified;
	INT			m_HP;
	INT			m_MP;
	INT			m_MaxHp;
	INT			m_MaxMp;
	FLOAT       m_MoveSpeed;
	_CAMP_DATA	m_CampData;
	ObjID_t		m_nOwnerID;
	PET_GUID_t	m_SpouseGUID;					// 配偶GUID
	INT			m_nAIType;						// 性格
	INT			m_Level;
	INT			m_nStealthLevel;				// 隐身级别

	INT			m_nDataID;						// 数据ID
	INT			m_nModelID;						// 外形
	INT			m_nMountID;						// 座骑ID

	PET_GUID_t	m_GUID;							// ID
	INT			m_nLife;						// 当前寿命
	BYTE		m_byGeneration;					// 几代宠
	BYTE		m_byHappiness;					// 快乐度

	INT			m_nAtt_Physics;					// 物理攻击力
	INT			m_nAtt_Magic;					// 魔法攻击力
	INT			m_nDef_Physics;					// 物理防御力
	INT			m_nDef_Magic;					// 魔法防御力
	INT			m_nHit;							// 命中率
	INT			m_nMiss;						// 闪避率
	INT			m_nCritical;					// 会心率

	INT			m_nExp;							// 经验

	INT			m_StrPerception;				// 力量资质
	INT			m_ConPerception;				// 体力资质
	INT 		m_DexPerception;				// 身法资质
	INT			m_SprPerception;				// 灵气资质
	INT 		m_IntPerception;				// 定力资质
	INT			m_GenGu;						// 根骨9

	INT			m_Str;							// 力量
	INT			m_Con;							// 体力
	INT 		m_Dex;							// 身法
	INT			m_Spr;							// 灵气
	INT 		m_Int;							// 定力

	INT			m_nRemainPoint;					// 潜能点
	INT			m_nCampType;

public:
	_PET_ATTR_BACKUP( VOID );

	VOID CleanUp( VOID );
};



//////////////////////////////////////////////////////
// 宠物
//////////////////////////////////////////////////////

#define MAX_CAPTURER_NUM (6)
#define LEVELDELTA_GETEXP (5)
#define SEND_LIFE_INTERVAL (30)

class AI_Pet;
class Obj_Pet :
	public Obj_Character
{
public:
	friend class AI_Pet;

//===========================================
// Obj公有接口继承
//===========================================
public:
	Obj_Pet( VOID );
	virtual ~Obj_Pet( VOID );

	virtual ObjType		GetObjType( VOID )const{ return OBJ_TYPE_PET; }
	virtual VOID 		CleanUp( );
	virtual BOOL 		Init( const _OBJ_INIT *pInit );
	virtual BOOL 		HeartBeat( UINT uTime = 0 );

	virtual VOID		InitAIObj( );
	virtual VOID		OnExecuteScriptTimer(UINT uTime) ;

	const _PET_DB*		GetPetDB(VOID) const { return &m_PetDB; }

//===========================================
// 宠物基本数据
//===========================================
public:
	ScriptID_t			m_ScriptID ;//宠物绑定的脚本

//===========================================
// 阵营相关
//===========================================
public:
	virtual BOOL	IsEnemy(Obj_Character* pCharacter);
	virtual BOOL	IsFriend(Obj_Character* pCharacter);
	virtual BOOL	IsPartner(Obj_Character* pCharacter);

//===========================================
// 消息/属性刷新
//===========================================
public:
	virtual Packet		*CreateNewObjPacket( VOID );
	virtual VOID		DestroyNewObjPacket( Packet *pPacket );

	virtual VOID 		InitBackupAttr( );
	virtual VOID 		SendMsg_RefeshAttrib( VOID );
	virtual VOID 		AskMsg_BaseAttrib( Obj_Human *pTargetHuman );
	virtual VOID 		AskMsg_DetailAttrib( Obj_Human *pTargetHuman );

protected:
	_PET_ATTR_BACKUP	m_AttrBackUp;

//===========================================
// 快乐度变化规则
//===========================================
public:
	virtual BOOL		HeartBeat_Happiness( UINT uTime = 0 );

protected:
	CMyTimer			m_HappinessTimer;		// 快乐度每隔多少时间减1

//===========================================
// 寿命变化规则
//===========================================
public:
	virtual BOOL		HeartBeat_Life( UINT uTime = 0 );

protected:
	CMyTimer			m_LifeTimer;		// 快乐度每隔多少时间减1

//===========================================
// 其他规则
//===========================================
public:
	VOID				LevelUp(VOID);
	virtual VOID		SetReliveInfo( BOOL bSkillRelive, const _RELIVE_INFO *pReliveInfo );

//===========================================
// 技能/心法
//===========================================
public:
	virtual BOOL		Skill_HaveSkill( SkillID_t const nID, BYTE const nLevel ) const;

	// nIndex	:	ENUM_PET_SKILL_INDEX
	const _PET_SKILL	*Skill_GetSkill( INT nIndex ) const;

	INT 				Skill_GetCount_CortrolByPlayer(VOID);
	INT 				Skill_GetMaxCount_CortrolByPlayer(VOID);
	INT 				Skill_GetCount_CortrolByAI(VOID);
	INT 				Skill_GetMaxCount_CortrolByAI(VOID);

	BOOL 				Skill_RegisterSkill(SkillID_t const nID, INT nIndex);
	BOOL 				Skill_UnregisterSkill(SkillID_t const nID, INT nIndex);
	BOOL 				Skill_ModifySkill_Study(SkillID_t nID);
	BOOL 				Skill_ModifySkill_Realize(SkillID_t nID);
	BOOL 				Skill_ModifySkill_MenPai(SkillID_t nID);
	BOOL 				Skill_Apperceive(VOID);

	virtual INT			Skill_GetXinFaLevel(SkillID_t const nID) const;
	virtual BOOL 		Skill_HaveXinFa( SkillID_t const nID ) const;
	virtual BOOL 		Skill_SetXinFaLevel(SkillID_t const nID, INT const nLevel);
	virtual VOID 		Skill_OnEquipItem(VOID);
//===========================================
// 效果
//===========================================
protected:
	virtual _IMPACT_LIST&	Impact_GetImpactList(VOID);

private:
	virtual VOID 			Impact_InitList(VOID);

private:
	_IMPACT_LIST			m_ImpactList;

//===========================================
// CoolDown
//===========================================
public:
	virtual Time_t		GetCooldownRemained(CooldownID_t const nID) const;
	virtual BOOL		IsCooldowned(CooldownID_t const nID) const;
	virtual VOID 		SetCooldown(CooldownID_t const nID, Time_t nCooldown);
	virtual BOOL 		HeartBeat_Cooldown(UINT uTime = 0);
	virtual BOOL 		HeartBeat_Recover(UINT uTime = 0);

protected:

//===========================================
// Capturer
//===========================================
public:
	INT					GetCaptureCount(VOID)const;

	BOOL 				AddCapturer(ObjID_t idObj); 
	BOOL 				DelCapturer(ObjID_t idObj);
	VOID 				CleanAllCapturer(VOID);
	VOID 				SendCaptureFailedToOthers(ObjID_t idObj);

protected:
	INT					m_nCapturerCount;	// 当前正在捕获自己的玩家数
	ObjID_t				m_aCapturer[MAX_CAPTURER_NUM];

//===========================================
// AI
//===========================================
public:
	virtual ObjID_t			GetOwnerID(VOID)const;
	virtual Obj_Character	*GetOwner( VOID );

	AI_Pet*					GetPetAI( VOID )const;
	VOID					SetTargetID( ObjID_t TargetID );
	ObjID_t					GetTargetID( VOID )const;
	const WORLD_POS*		GetRespawnPos( VOID )const;

	VOID					ToAttack( ObjID_t TargetID );
	BOOL					PushSkillToCache(INT idSkill);
	VOID					GetRateOfBuffTakeEffect(INT idSkill, INT& rateOfBuffTakeEffect);

protected:
	ObjID_t					m_OwnerID;			// 当前所有者的ObjID
	ObjID_t					m_TargetID;			// 目标ID
	WORLD_POS				m_RespawnPos;
	INT						m_RespawnTime;
	// 只用来缓存被动技能和护主型技能(即起持续性效果的技能)
	INT						m_aCacheOfSkill[HUMAN_PET_MAX_COUNT]; 
	INT						m_AIType;


//===========================================
// 一级属性
//===========================================
public:
	virtual GUID_t			GetGUID( VOID )const;

	Obj_Human				*GetCreator( VOID )const;
	const Obj_Human			*GetConstCreator( VOID )const;

	VOID					SetPetGUID(PET_GUID_t guid);
	PET_GUID_t				GetPetGUID(VOID)const;

	VOID					SetSpouseGUID(PET_GUID_t guid);
	PET_GUID_t				GetSpouseGUID(VOID)const;

	VOID					SetDataID(const UINT dataID);
	virtual UINT			GetDataID( VOID )const; 

	virtual	VOID			SetName( const CHAR *pszName );
	virtual const CHAR		*GetName( VOID )const;

	virtual	VOID			SetTitle( const CHAR *pszTitle );
	virtual const CHAR		*GetTitle( VOID )const;

	VOID					IncrementExp(INT nIncrement);
	virtual INT				GetExp( VOID )const;
	virtual VOID			SetExp( INT nExp );

	virtual VOID			SetHP( INT nHP );
	virtual INT				GetHP( VOID );

    virtual VOID			SetMP( INT nMP );
	virtual INT				GetMP( VOID );

	virtual INT				GetAIType( VOID )const;
	virtual VOID			SetAIType( INT nAIType );

	virtual INT				GetLevel( VOID )const;
	virtual VOID			SetLevel( INT nLevel );

	virtual INT				GetLife( VOID )const;
	virtual VOID			SetLife( INT nLife );

	virtual BYTE			GetGeneration( VOID )const;
	virtual VOID			SetGeneration( BYTE byGeneration );

	VOID 					IncrementHappyness(INT nIncrement);
	BYTE 					GetHappiness( VOID )const;
	VOID 					SetHappiness( BYTE byHappiness );

	INT						GetGenGu( VOID )const;
	VOID					SetGenGu( INT nGenGu );

	virtual INT 			GetStrPerception( VOID )const;
	virtual INT 			GetConPerception( VOID )const;
	virtual INT 			GetDexPerception( VOID )const;
	virtual INT 			GetSprPerception( VOID )const;
	virtual INT 			GetIntPerception( VOID )const;

	virtual INT				GetRemainPoint( VOID )const;
	virtual VOID			SetRemainPoint( INT nRemainPoint );

protected:
	GUID_t					m_GUID;				// 角色在场景中的GUID，与PetGUID是两回事
	ObjID_t					m_CreatorID;		// 创建者的ObjID
	Obj_Human*				m_pCreator;			// 宠物的创建者
	INT						m_nIndex;			// 标识该宠物是玩家宠物槽中的第几个
	_PET_DB					m_PetDB;


//===========================================
// 二级属性
//===========================================
public:
	//StrikePoint
	virtual INT 				GetMaxStrikePoint(VOID);
	//Rage
	virtual INT   				GetMaxRage(VOID);
	//Attr1: Str
	virtual INT					GetStr(VOID);
	virtual INT					GetBaseStr(VOID);
	virtual VOID 				SetBaseStr(INT const nValue);
	//Attr1: Spr
	virtual INT					GetSpr(VOID);
	virtual INT					GetBaseSpr(VOID);
	virtual VOID				SetBaseSpr(INT const nValue);
	//Attr1: Con
	virtual INT					GetCon(VOID);
	virtual INT					GetBaseCon(VOID);
	virtual VOID				SetBaseCon(INT const nValue);
	//Attr1: Int
	virtual INT					GetInt(VOID);
	virtual INT					GetBaseInt(VOID);
	virtual VOID				SetBaseInt(INT const nValue);
	//Attr1: Dex
	virtual INT					GetDex(VOID);
	virtual INT					GetBaseDex(VOID);
	virtual VOID				SetBaseDex(INT const nValue);
	//HP
	virtual INT					GetMaxHP(VOID) ; 
	virtual INT 				GetBaseMaxHP(VOID);
	virtual VOID 				SetBaseMaxHP(INT const nHp);
	virtual INT					GetHPRegenerate(VOID) ; 
	virtual INT 				GetBaseHPRegenerate(VOID);
	virtual VOID 				SetBaseHPRegenerate(INT const nValue);

	//MP
	virtual INT 				GetMaxMP(VOID);
	virtual INT 				GetBaseMaxMP(VOID);
	virtual VOID 				SetBaseMaxMp(INT const nMp);
	virtual INT					GetMPRegenerate(VOID); 
	virtual INT 				GetBaseMPRegenerate(VOID);
	virtual VOID 				SetBaseMPRegenerate(INT const nValue);
	//CampID
	virtual const _CAMP_DATA	*GetCampData(VOID);
	virtual const _CAMP_DATA	*GetBaseCampData(VOID)const;
	virtual VOID				SetBaseCampData(const _CAMP_DATA *pCampData);
	virtual INT 				GetCampID(VOID);
	virtual INT 				GetBaseCampID(VOID) const;
	virtual VOID				SetBaseCampID(INT const nID);
	//modelID
	virtual INT 				GetModelID(VOID);
	virtual INT 				GetBaseModelID(VOID) const;
	virtual VOID				SetBaseModelID(INT const nID);
	//Alive flag
	//In Combat flag
	// Can move flag
	// Can Action flag
	// Unbreakable flag
	// Attr2: Move Speed
	virtual FLOAT				GetMoveSpeed(VOID);
	virtual INT					GetBaseMoveSpeed(VOID);
	virtual VOID				SetBaseMoveSpeed(INT const nValue);
	// Attr2: Attack Speed
	virtual INT 				GetAttackSpeed(VOID);
	virtual INT 				GetBaseAttackSpeed(VOID);
	virtual VOID				SetBaseAttackSpeed(INT const nValue);
	// Attr2: Miss
	virtual INT 				GetMiss(VOID);
	virtual INT 				GetBaseMiss(VOID);
	virtual VOID				SetBaseMiss(INT const nValue);
	// Attr2 Hit
	virtual INT 				GetHit(VOID);
	virtual INT 				GetBaseHit(VOID);
	virtual VOID				SetBaseHit(INT const nValue);
	// Attr2 Critical
	virtual INT 				GetCritical(VOID);
	virtual INT 				GetBaseCritical(VOID);
	virtual VOID				SetBaseCritical(INT const nValue);
	// Attr2: Attack and Defence power physics
	virtual INT 				GetAttackPhysics(VOID);
	virtual INT 				GetBaseAttackPhysics(VOID);
	virtual VOID				SetBaseAttackPhysics(INT const nValue);
	virtual INT 				GetDefencePhysics(VOID);
	virtual INT 				GetBaseDefencePhysics(VOID);
	virtual VOID				SetBaseDefencePhysics(INT const nValue);
	// Attr2: Attack and Defence power of Magic
	virtual INT 				GetAttackMagic(VOID);
	virtual INT 				GetBaseAttackMagic(VOID);
	virtual VOID				SetBaseAttackMagic(INT const nValue);
	virtual INT 				GetDefenceMagic(VOID);
	virtual INT 				GetBaseDefenceMagic(VOID);
	virtual VOID				SetBaseDefenceMagic(INT const nValue);
	// Attr2: Attack and Defence power of Cold
	virtual INT 				GetAttackCold(VOID);
	virtual INT 				GetBaseAttackCold(VOID);
	virtual VOID				SetBaseAttackCold(INT const nValue);
	virtual INT 				GetDefenceCold(VOID);
	virtual INT 				GetBaseDefenceCold(VOID);
	virtual VOID				SetBaseDefenceCold(INT const nValue);
	// Attr2: Attack and Defence power of Fire
	virtual INT 				GetAttackFire(VOID);
	virtual INT 				GetBaseAttackFire(VOID);
	virtual VOID				SetBaseAttackFire(INT const nValue);
	virtual INT 				GetDefenceFire(VOID);
	virtual INT 				GetBaseDefenceFire(VOID);
	virtual VOID				SetBaseDefenceFire(INT const nValue);
	// Attr2: Attack and Defence power of Light
	virtual INT 				GetAttackLight(VOID);
	virtual INT 				GetBaseAttackLight(VOID);
	virtual VOID				SetBaseAttackLight(INT const nValue);
	virtual INT 				GetDefenceLight(VOID);
	virtual INT 				GetBaseDefenceLight(VOID);
	virtual VOID				SetBaseDefenceLight(INT const nValue);
	// Attr2: Attack and Defence power of Poison
	virtual INT 				GetAttackPoison(VOID);
	virtual INT 				GetBaseAttackPoison(VOID);
	virtual VOID				SetBaseAttackPoison(INT const nValue);
	virtual INT 				GetDefencePoison(VOID);
	virtual INT 				GetBaseDefencePoison(VOID);
	virtual VOID				SetBaseDefencePoison(INT const nValue);
	// Attr2 Reduce Slower Duration
	virtual INT 				GetReduceSlowerDuration(VOID);
	// Attr2 Reduce Weaken Duration
	virtual INT 				GetReduceWeakenDuration(VOID);
	// Attr2 Reduce Faint Duration
	virtual INT 				GetReduceFaintDuration(VOID);
	// Attr2 Reduce Poisoned Duration
	virtual INT 				GetReducePoisonedDuration(VOID);
	// Attr2 VisionRange
	virtual INT 				GetVisionRange(VOID);
	virtual INT 				GetBaseVisionRange(VOID);
	virtual VOID				SetBaseVisionRange(INT const nValue);
};

#endif	// __PET_H__
