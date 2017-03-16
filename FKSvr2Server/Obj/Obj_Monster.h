// Obj_Monster.h
//
/////////////////////////////////////////////////////////

#ifndef __OBJ_MONSTER_H__
#define __OBJ_MONSTER_H__

#include "Obj_Character.h"

/////////////////////////////////////////////////////////
//怪物初始化数据
/////////////////////////////////////////////////////////

#define MAX_SHOP_INIT 4
struct _OBJ_MONSTER_INIT :
	public _OBJ_CHARACTER_INIT
{
	GUID_t				m_GUID;
	UINT				m_uDataID;
	CHAR				m_szName[NPC_NAME_LEN];
	CHAR				m_szTitle[NPC_TITLE_LEN];
	ScriptID_t			m_idScript;
	INT					m_RespawnTime;
	UINT				m_uGroupID;
	UINT				m_uTeamID;
	INT					m_BaseAI;
	INT					m_ExtAIScript;
	INT					m_nPatrolID;
	INT					m_nShop[MAX_SHOP_INIT];
	UINT				m_LeaderID;
	BOOL				m_bPet;
	INT					m_nLevel;
	BOOL				m_bNPC;
	INT					m_nCamp;

	_OBJ_MONSTER_INIT( VOID )
	{
		m_GUID			= -1;
		m_uDataID		= -1;
		m_szName[0]		= 0;
		m_szTitle[0]	= 0;
		m_RespawnTime	= 60000;
		m_uGroupID     = -1;
		m_uTeamID		= -1;
		m_BaseAI		= 0;
		m_idScript		= -1;
		m_ExtAIScript	= 0;
		m_nPatrolID		= -1;
		m_LeaderID		= -1;
		m_bPet			= FALSE;
		m_nLevel		= -1;
		m_bNPC			= FALSE;
		m_nCamp			= INVALID_CAMP;
		for( INT i=0; i<MAX_SHOP_INIT; i++ )
		{
			m_nShop[i] = -1 ;
		}
	}

	virtual VOID CleanUp( VOID )
	{
		m_GUID			= -1;
		m_uDataID		= -1;
		m_szName[0]		= 0;
		m_szTitle[0]	= 0;
		m_RespawnTime	= 60000;
		m_uGroupID     = -1;
		m_uTeamID		= -1;
		m_BaseAI		= 0;
		m_ExtAIScript	= -1;
		m_idScript		= -1;
		m_nPatrolID		= -1;
		m_LeaderID		= -1;
		m_bPet			= FALSE;
		m_nLevel		= -1;
		m_bNPC			= FALSE;
		m_nCamp			= INVALID_CAMP;
		for( INT i=0; i<MAX_SHOP_INIT; i++ )
		{
			m_nShop[i] = -1 ;
		}

		_OBJ_CHARACTER_INIT::CleanUp();
	}
};

/////////////////////////////////////////////////////////
// 属性刷新的数据备份
/////////////////////////////////////////////////////////
struct _MONSTER_ATTR_BACKUP
{
	BOOL		m_bNameModified;
	BOOL		m_bTitleModified;
	INT			m_HP;
	INT			m_MaxHp;
	FLOAT       m_MoveSpeed;
	_CAMP_DATA	m_CampData;
	INT			m_nDataID;
	INT			m_nModelID;
	INT			m_nMountID;
	INT			m_nAIType;
	ObjID_t		m_OwnerID;
	GUID_t		m_OccupantGUID;
	INT			m_nStealthLevel;	// 隐身级别
	INT			m_nMoodState;
	INT			m_nCampType;

	_MONSTER_ATTR_BACKUP(VOID)
	{
		m_bNameModified		= FALSE;
		m_bTitleModified	= FALSE;
		m_HP				= 0;
		m_MaxHp				= 1;
		m_MoveSpeed			= 0.f;
		//m_CampData
		m_nDataID			= INVALID_ID;
		m_nModelID			= INVALID_ID;
		m_nMountID			= INVALID_ID;
		m_OwnerID			= INVALID_ID;
		m_OccupantGUID		= INVALID_GUID;
		m_nStealthLevel		= -1;
		m_nMoodState		= INVALID_MOOD_STATE;
		m_nCampType			= INVALID_CAMP;
	}

	VOID CleanUp(VOID)
	{
		m_bNameModified		= FALSE;
		m_bTitleModified	= FALSE;
		m_HP				= 0;
		m_MaxHp				= 1;
		m_MoveSpeed			= 0.f;
		m_CampData.CleanUp();
		m_nDataID			= INVALID_ID;
		m_nModelID			= INVALID_ID;
		m_nMountID			= INVALID_ID;
		m_OwnerID			= INVALID_ID;
		m_OccupantGUID		= INVALID_GUID;
		m_nStealthLevel		= -1;
		m_nMoodState		= INVALID_MOOD_STATE;
		m_nCampType			= INVALID_CAMP;
	}
};

class Obj_Human;
class AI_Monster;
class DynamicShopManager;
class PetPlacardSystem;
class Obj_Monster :
	public Obj_Character
{
//===========================================
// Obj接口继承
//===========================================
public:
    Obj_Monster( VOID );
	virtual ~Obj_Monster( VOID );

	virtual ObjType		GetObjType( VOID )const{ return OBJ_TYPE_MONSTER; }

	virtual VOID		CleanUp( VOID );
	virtual BOOL		Init( const _OBJ_INIT *pInit );
	virtual BOOL		HeartBeat( UINT uTime = 0 );
	virtual BOOL		HeartBeat_OutZone( UINT uTime=0 );

//===========================================
// Character接口继承
//===========================================
public:
	virtual VOID		InitAIObj( );
	virtual VOID		OnDie( ObjID_t idKiller );			//死了
	virtual BOOL		IsEnemy(Obj_Character* pCharacter );
	virtual BOOL		IsFriend(Obj_Character* pCharacter);
	virtual BOOL		IsPartner(Obj_Character* pCharacter);
	virtual VOID		OnExecuteScriptTimer(UINT uTime) ;

public:
	VOID				OnDie_Before( ObjID_t idKiller ) ;	//死亡前处理的逻辑
	VOID				OnDie_After( ObjID_t idKiller );	//死亡后处理的逻辑

//===========================================
// 消息/属性刷新
//===========================================
public:
	virtual Packet			*CreateNewObjPacket( VOID );
	virtual VOID			DestroyNewObjPacket( Packet *pPacket );

	virtual VOID			InitBackupAttr( );
	virtual VOID			SendMsg_RefeshAttrib( VOID );
	virtual VOID			AskMsg_BaseAttrib( Obj_Human *pTargetHuman );

protected:
	_MONSTER_ATTR_BACKUP	m_AttrBackUp;

//===========================================
// 技能/心法
//===========================================
public:
	virtual BOOL 	Skill_HaveSkill( SkillID_t const nID, BYTE const nLevel ) const{return TRUE;}
	virtual BOOL 	Skill_ModifySkill(SkillID_t	const nID, BYTE const nLevel, INT const nModifyFlag){return TRUE;}
	virtual BOOL 	Skill_HaveXinFa( SkillID_t const nID ) const{return TRUE;}
	virtual INT 	Skill_GetXinFaLevel(SkillID_t const nID) const{return 1;}
	virtual BOOL 	Skill_SetXinFaLevel(SkillID_t const nID, INT const nLevel){return TRUE;}
	virtual VOID 	Skill_OnEquipItem(VOID){}

//===========================================
// CoolDown
//===========================================
public:
	virtual BOOL		IsCooldowned(CooldownID_t const nID) const;
	virtual VOID		SetCooldown(CooldownID_t const nID, Time_t nCooldown);
	virtual BOOL 		HeartBeat_Cooldown(UINT uTime = 0);

protected:
	INT					m_nCooldown;

//===========================================
// HP，MP，Rage的变化规则
//===========================================
public:
	virtual BOOL		HeartBeat_Recover(UINT uTime = 0);

//===========================================
// 效果
//===========================================
protected:
	virtual _IMPACT_LIST&	Impact_GetImpactList(VOID){return m_ImpactList;}

private:
	virtual VOID 			Impact_InitList(VOID);

private:
	_IMPACT_LIST			m_ImpactList;

//===========================================
// 重生
//===========================================
public:
	VOID					Enter_Respawn( VOID );
	BOOL					Respawn( VOID );

	INT						GetRespawnTime( VOID )const{ return m_RespawnTime; }

	VOID					SetRespawnPos( const WORLD_POS *pPos ){ m_RespawnPos = *pPos; }
	const WORLD_POS			*GetRespawnPos( VOID )const{ return &m_RespawnPos; }

	VOID					SetRespawnDir( FLOAT fDir ){ m_RespawnDir = fDir; }
	FLOAT					GetRespawnDir( VOID )const{ return m_RespawnDir; }

private:
	INT						m_RespawnTime;
	CMyTimer				m_RespawnTimer;		//尸体消失后到重生的时间间隔
	FLOAT					m_RespawnDir;
	WORLD_POS				m_RespawnPos;

//===========================================
// 伤害列表
//===========================================
public:
	VOID					SetOccupantTeamID( TeamID_t tid ){ m_Own_TeamID = tid ; }
	TeamID_t				GetOccupantTeamID( ){ return m_Own_TeamID ; }

	VOID					SetOccupantGUID( GUID_t guid ){ m_OccupantGUID = guid ; }
	GUID_t					GetOccupantGUID( ){ return m_OccupantGUID ; }

	VOID					UpdateDamageList(INT nDamage, Obj_Character* pCharacter);

	DAMAGE_MEM_LIST			GetKillerRec(UINT	uCount,UINT nPercent);
	MONSTER_OWNER_LIST&		GetOwnerList();
	void					ClearKiller()
	{
							m_DamageMemList.CleanUp();
							m_Own_TeamID = INVALID_ID ;
							m_OccupantGUID = INVALID_ID ;
	}

protected:
	TeamID_t				m_Own_TeamID ;//此npc的归属
	GUID_t					m_OccupantGUID ;//此npc的归属（仅在m_Own_TeamID等于INVALID_ID时有效）
	DAMAGE_MEM_LIST			m_DamageMemList;
	MONSTER_OWNER_LIST		m_OwnerList;

//===========================================
// AI
//===========================================
public:
	AI_Monster				*GetMonsterAI( VOID )const{ return ((AI_Monster*)m_pAI_Character); }
	VOID					SetAIType(INT AIType) { m_AIType = AIType; }
	INT						GetAIType( VOID )const{ return m_AIType; }
	INT						GetMonsterAIType(VOID);
	INT						GetPosRange( VOID )const{ return m_PositionRange; }

	VOID					PaoPao(INT idPaoPaoBase, INT idPaoPaoStep);
	VOID					ProcessPaoPao(VOID);

	VOID					SetLeaderID(ObjID_t LeaderID) { m_LeaderID = LeaderID; 	}
	ObjID_t					GetLeaderID(VOID) const { return m_LeaderID; }

private:
	INT						m_AIType;
	INT						m_AIScript;
	ObjID_t					m_LeaderID;
	INT						m_PositionRange;

//===========================================
// NPC商店
//===========================================
public:
	DynamicShopManager*		GetShopManager(){ return m_pShopManager; }
	INT						BindDynamicShop(INT shopindex);
	VOID					InitDynamicShop();

protected:
	//动态商店管理器
	DynamicShopManager*		m_pShopManager;

//===========================================
// 宠物公告板
//===========================================
public:
	PetPlacardSystem		*GetPetPlacardSystem(VOID){ return m_pPetPlacardSystem; }
	BOOL					CreatePetPlacardSystem(VOID);

protected:
	VOID					ReleasePetPlacardSystem(VOID);

protected:
	PetPlacardSystem		*m_pPetPlacardSystem;

//===========================================
// 其他
//===========================================
public:
	BOOL					isPatrolMonster( VOID ) { return m_nPatrolID != INVALID_ID ? TRUE : FALSE; }
	INT						GetPatrolPathIndex( VOID ) const { return m_nPatrolID; }
	VOID					SetPatrolId( INT PatrolID );
	//VOID					StartPatrol( VOID );
	//VOID					StopPatrol( VOID );

	FLOAT					GetDropSearchRange() const;		//掉落搜索半径
	INT						GetDropTeamCount() const;		//掉落有效组数量

private:
	INT						m_nPatrolID;
	FLOAT					m_DropSearchRange;
	INT						m_DropTeamCount;
	BOOL					m_CreateFlag;

	BOX_DISTRIBUTE_RULER	m_DropRuler ;

public:
	//OnKillObject_begin
	enum
	{
		BEKILL_MISSION_NUM = 16,
	};
	typedef struct SKillObj
	{
		INT m_nMissionId;
		
	}tagKillObj[BEKILL_MISSION_NUM];
	tagKillObj m_sKillObj;
	INT m_nKillCount;
	//OnKillObject_end

//===========================================
// 一级属性
//===========================================
public:
	virtual GUID_t			GetGUID( VOID )const{ return m_GUID; }

	virtual UINT			GetDataID( VOID )const{ return m_uDataID; }

	virtual	VOID			SetName( const CHAR *pszName );
	virtual const CHAR		*GetName( VOID )const{ return m_szName; }

	virtual	VOID			SetTitle( const CHAR *pszTitle );
	virtual const CHAR		*GetTitle( VOID )const{ return m_szTitle; }

	virtual VOID			SetHP( INT nHP );
	virtual INT				GetHP( VOID );

	virtual VOID			SetMP( INT nMP );
	virtual INT				GetMP( VOID ){ return 0; }

	virtual VOID			SetLevel( INT nLevel );
	virtual INT				GetLevel( VOID )const{ return m_Level; }

	virtual BOOL			IsNPC(VOID)const { return m_bNPC; }

	virtual VOID			SetScriptID( ScriptID_t idScript ){ m_idScript = idScript; }
	virtual ScriptID_t		GetScriptID( VOID )const{ return m_idScript; }

	INT						GetBaseExp( VOID )const{ return m_BaseExp; }
	INT						GetMinDamagePercent() const; 	//最小伤血百分比

	UINT					GetGroupID(){ return m_uGroupID ; }
	UINT					GetTeamID(){ return m_uTeamID ; }

	INT						GetAttackAnimTime(){return m_AttackAnimTime;}
	INT						GetAttackCooldownTime(){return m_AttackCooldownTime;}

private:
	GUID_t					m_GUID;
	UINT					m_uDataID;			// 资源ID
	CHAR					m_szName[NPC_NAME_LEN];
	CHAR					m_szTitle[NPC_TITLE_LEN];
	INT						m_HP;
	INT						m_Level;
	INT						m_BaseExp;
	ScriptID_t				m_idScript;
	_CAMP_DATA				m_CampData;
	INT						m_MinDamagePercent;
	UINT					m_uGroupID;
	UINT					m_uTeamID;
	INT						m_AttackAnimTime;
	INT						m_AttackCooldownTime;
	BOOL					m_bNPC;

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
	virtual BOOL				IsUnbreakable(VOID);	
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

#endif
