//	Obj_Human.h
//
//	功能：玩家在SERVER上的实现类
//	修改记录：
//////////////////////////////////////////////////////

#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "Obj_Character.h"
#include "HumanDB.h"
#include "HumanItemContainer.h"
#include "HumanPetContainer.h"
#include "Team.h"
#include "HumanRelation.h"
#include "StallBox.h"
#include "ExchangBox.h"
#include "GameStruct_Team.h"

namespace Packets {
	class GCDetailAttrib_Pet;
};

struct PET_LOG_PARAM;
struct SKILL_LOG_PARAM;
struct XINFA_LOG_PARAM;

//////////////////////////////////////////////////////
// 初始化Obj_Human的结构
//////////////////////////////////////////////////////
struct FULLUSERDATA;
struct _OBJ_HUMAN_INIT :
	public _OBJ_CHARACTER_INIT
{
	const FULLUSERDATA	*m_pUseData;

	_OBJ_HUMAN_INIT( VOID )
	{
		m_pUseData		= NULL;
	}

	virtual VOID CleanUp( VOID )
	{
		m_pUseData		= NULL;
		_OBJ_CHARACTER_INIT::CleanUp();
	}
};

//////////////////////////////////////////////////////
// 与客户端同步队友信息数据
//////////////////////////////////////////////////////
struct _TEAM_MEMBER_INFO
{
	_TEAM_MEMBER_INFO()
	{
		memset(this, 0, sizeof(_TEAM_MEMBER_INFO));
	}

	UINT					m_uFamily;						// 1.门派
	UINT					m_uLevel;						// 2.等级
	WORLD_POS				m_WorldPos;						// 3.位置（坐标）
	INT						m_nHP;							// 4.HP
	UINT					m_uMaxHP;						// 5.HP上限
	INT						m_nMP;							// 6.MP
	UINT					m_uMaxMP;						// 7.MP上限
	INT						m_nAnger;						// 8.怒气
	UINT					m_WeaponID;						// 9.武器
	UINT					m_CapID;						// 10.帽子
	UINT					m_ArmourID;						// 11.衣服
	UINT					m_CuffID;						// 12.护腕
	UINT					m_FootID;						// 13.靴子
	// 14.buff，暂时不考虑
	BOOL					m_bDeadFlag;					// 15.是否死亡
	UINT					m_uFaceMeshID;					// 16.面部模型
	UINT					m_uHairMeshID;					// 17.头发模型
	UINT					m_uHairColor;					// 18.头发颜色
	SimpleImpactList		m_SimpleImpactList;				// Buff 列表
};

//////////////////////////////////////////////////////
// 与客户端同步备份数据
//////////////////////////////////////////////////////
struct _HUMAN_ATTR_BACKUP 
{
public:
	_HUMAN_ATTR_BACKUP(VOID);
	VOID CleanUp(VOID);

public:
	BOOL				m_bNameModified;
	BOOL				m_bTitleModified;
	INT					m_Level;
	UINT				m_Exp;
	INT					m_HP;
	INT					m_MP;
	INT					m_MaxHp;
	INT					m_MaxMp;
	FLOAT       		m_MoveSpeed;
	INT					m_nDataID;
	INT					m_nPortraitID;
	INT					m_nModelID;
	INT					m_nMountID;			//座骑的编号
	UINT				m_uFaceMeshID;		// 面部模型
	UINT				m_uHairMeshID;		// 头发模型
	UINT				m_uHairColor;		// 头发颜色
	INT					m_nStealthLevel;	// 隐身级别
	INT					m_nMoodState;

	//////////////////////////////////////////////////////
	// Detail Infomation
	UINT				m_Money;
	//INT					m_RMBMoney;
	INT					m_nStr;
	INT					m_nSpr;
	INT					m_nCon;
	INT					m_nInt;
	INT					m_nDex;
	INT					m_nPointRemain;

	INT					m_nReHpSpeed;
	INT					m_nReMpSpeed;
	INT					m_nAttPhysics;
	INT					m_nAttMagic;
	INT					m_nDefPhysics;
	INT					m_nDefMagic;
	INT					m_nHit;
	INT					m_nMiss;
	INT					m_nCritic;

	INT					m_nRage;
	INT					m_nStrikePoint;

	INT					m_nAttSpeed;

	INT					m_nAttCold;
	INT					m_nDefCold;
	INT					m_nAttFire;
	INT					m_nDefFire;
	INT					m_nAttLight;
	INT					m_nDefLight;

	INT					m_nAttPoison;
	INT					m_nDefPoison;
	INT					m_nMenpai;
	_CAMP_DATA			m_CampData;
	ObjID_t				m_nOwnerID;
	PET_GUID_t			m_guidCurrentPet;

	INT					m_RMBMoney;//m_Vigor ;
	INT					m_BankRMB;//m_MaxVigor ;
	INT					m_DoubleExpTime_Num;
	INT					m_GmRight;

	BOOL				m_bLimitMove;		//是否限制不能移动
	BOOL				m_bCanActionFlag1;	//技能限制标记1
	BOOL				m_bCanActionFlag2;	//技能限制标记2

	BOOL				m_bMissionHaveDoneFlagsChanged;

	// 装备
	BOOL				m_bWeaponModified;
	BOOL				m_bCapModified;
	BOOL				m_bArmorModified;
	BOOL				m_bCuffModified;
	BOOL				m_bBootModified;
	BOOL				m_bSashModified;

	// 当前是否是摆摊状态
	BOOL				m_bStallIsOpen;
	BOOL				m_bStallNameChanged;

	//帮派刷新数据
	GuildID_t			m_GuildID;		//	玩家所在帮会
};

//////////////////////////////////////////////////////
// 生活技能操作数据
//////////////////////////////////////////////////////
struct AbilityOpera
{
	AbilityID_t			m_AbilityID;
	BYTE				m_SubType;	// 加工包括普通、宝石合成、镶嵌
	PrescriptionID_t	m_PresID;
	ObjID_t				m_Obj;
	INT					m_nMaxTime;
	INT					m_nCurTime;
	INT					m_nRobotTime;
	BYTE				m_BagPos[MAX_ABILITY_ITEM];
	UINT				m_uItemIndex; // 保存合成过程中需要的物品信息（例如宝石合成）

	VOID	CleanUp()
	{
		memset(this,0,sizeof(AbilityOpera));
	}
};


//////////////////////////////////////////////////////
// HUMANLIST
//////////////////////////////////////////////////////
#define MAX_HUMAN_LIST_SIZE 128
#define LEVELDELTA_CALLUP (10)

class Obj_Human;
struct HUMANLIST
{
	Obj_Human*		m_aHuman[MAX_HUMAN_LIST_SIZE];
	BYTE			m_Count;

	HUMANLIST( )
	{
		m_Count = 0;
	}
};


//////////////////////////////////////////////////////
// Obj_Human
//////////////////////////////////////////////////////
class Player;
class AI_Human;
class Obj_Pet;
class AvoidOverlap;
class ItemContainer;
struct _SHOP;
struct _OBJ_LIST_NODE;

class Obj_Human : public Obj_Character
{
//===========================================
// Obj公有接口继承
//===========================================
public:
	Obj_Human( );
	virtual ~Obj_Human( );

	virtual ObjType			GetObjType( VOID )const{ return OBJ_TYPE_HUMAN; }

	virtual VOID OnEnterScene(VOID);
	virtual VOID OnRegisterToZone(VOID);
	virtual VOID OnUnregisterFromZone(VOID);

	virtual VOID CleanUp( VOID );
	virtual BOOL Init( const _OBJ_INIT *pInit, const BYTE age );
	virtual BOOL HeartBeat( UINT uTime=0 );

	virtual BOOL IsEnemy(Obj_Character* pCharacter );
	virtual BOOL IsFriend(Obj_Character* pCharacter);
	virtual BOOL IsPartner(Obj_Character* pCharacter);
	BOOL IsMySpouse(Obj_Human& rHuman);
	virtual VOID Teleport( const WORLD_POS* pos );

//===========================================
// Character公有接口继承
//===========================================
public:
	virtual VOID InitAIObj( );
	virtual VOID OnHumanLogin( ) ;

	virtual VOID OnKillObject( ObjID_t idObj );
	virtual VOID OnItemChanged( UINT uItemDataID );
	virtual VOID OnEnterArea( UINT uAreaID );
	virtual VOID OnPetChanged( UINT uPetDataID ) ;
	virtual VOID OnDie( ObjID_t idKiller );
	virtual VOID OnExecuteScriptTimer(UINT uTime) ;

//===========================================
// 消息/属性刷新
//===========================================
public:
	virtual Packet		*CreateNewObjPacket( VOID );
	virtual VOID		DestroyNewObjPacket( Packet *pPacket );
	virtual VOID 		InitBackupAttr( );
	virtual VOID 		SendMsg_RefeshAttrib( VOID );
	virtual VOID 		SyncTeamMemberInfo( );
	virtual VOID 		AskMsg_BaseAttrib( Obj_Human *pTargetHuman );
	VOID 				AskMsg_DetailAttrib(Obj_Human *pAsker);
	static	VOID		CalculatePetDetailAttrib(Packets::GCDetailAttrib_Pet& rMsg, Item* pPetItem);
	VOID 				RefeshPetDetailAttrib(PET_GUID_t guidPet);

	WORD				GetEquipVer( );
	VOID				SetEquipVer( WORD Ver );
	virtual VOID		UpdateViewCharacter(VOID);

protected:
	_HUMAN_ATTR_BACKUP	m_AttrBackUp;

//===========================================
//  复活点
//===========================================
public:
	// 得到复活信息
	// bSkillRelive		:	是否为技能复活
	virtual const _RELIVE_INFO		*GetReliveInfo( BOOL bSkillRelive )const;

	// 设置复活属性
	// bSkillRelive		:	是否为技能复活
	// pReliveInfo		:	复活信息
	virtual VOID			SetReliveInfo( BOOL bSkillRelive, const _RELIVE_INFO *pReliveInfo );

protected:
	// 复活信息改变的事件(如：玩家对死去的玩家使用复活技能)
	VOID					OnReliveInfoChanged( VOID );

protected:
	_RELIVE_INFO			m_DefaultReliveInfo;		// 缺省复活的信息
	

//===========================================
//  邀请的处理
//===========================================
public:
	// 得到邀请信息
	const _CALLOF_INFO		*GetCallOfInfo(VOID)const;

	VOID					ResetCallOfInfo(VOID);

	// 设置邀请属性
	// pCallOfInfo		:	邀请信息
	VOID					SetCallOfInfo(const _CALLOF_INFO *pCallOfInfo);

	// 拉人
	VOID					CallOfHuman(GUID_t guidTarget, UINT uDuration);

protected:
	// 邀请信息改变的事件
	VOID					OnCallOfInfoChanged( VOID );

protected:
	_CALLOF_INFO			m_CallOfInfo;			// 邀请的信息
	UINT					m_uCallOf_StartTime;	// 邀请信息的起始时间

//===========================================
// AI
//===========================================
public:
	AI_Human*				GetHumanAI( VOID );
	AvoidOverlap*           GetAvoidOverLap()const;
	ObjID_t					GetAssistantID( VOID ) const;
	VOID					SetAssistantID( ObjID_t id );
	VOID					SetCurTarget( ObjID_t idTarget );
	ObjID_t					GetCurTarget( VOID ) const;

protected:
	AvoidOverlap			*m_pAvoidOverlap;	// 
	ObjID_t					m_AssistantID;		//辅助攻击者

//===========================================
// 属性
//===========================================
public:
	virtual UINT			GetUniqueID(VOID) const;
	//DB接口
	HumanDB*				GetDB();
	GUID_t					GetGUID( VOID )const;

	virtual UINT			GetDataID( VOID )const;

	virtual VOID			SetPortraitID( INT nID );
	virtual INT				GetPortraitID( VOID ) const;

	virtual	VOID			SetName( const CHAR *pszName );
	virtual const CHAR		*GetName( VOID )const;

	virtual	VOID			SetTitle( const CHAR *pszTitle );
	virtual const CHAR		*GetTitle( VOID )const;

	virtual	VOID			SetTitleType( BYTE nType );
	virtual const BYTE		GetTitleType( VOID )const;

	virtual VOID			SetHP( INT nHP );
	virtual INT				GetHP( VOID );

	virtual VOID			SetMP( INT nMP );
	virtual INT				GetMP( VOID );

	virtual VOID			SetLevel( INT nLevel );
	virtual INT				GetLevel( VOID )const;

	virtual VOID			SetPKValue( INT nValue );
	virtual INT				GetPKValue( VOID )const;

	virtual VOID			SetCurrentPetGUID( PET_GUID_t guid );
	virtual PET_GUID_t		GetCurrentPetGUID( VOID )const;

	VOID					SetAlterExp( INT AlterExp );	//改变的经验
	VOID					SetMonsterAlterExp( INT AlterExp );	//打怪物改变的经验
	virtual UINT			GetExp( );
	virtual VOID			SetExp(UINT uExp);
	virtual INT				GetStrikePoint(VOID);
	virtual VOID			SetStrikePoint(INT nStrikePoint);

	virtual INT				GetRMB(VOID);
	virtual VOID			SetRMB(INT nMoney);

	virtual INT				GetBankRMB(VOID);
	virtual VOID			SetBankRMB(INT nMoney);

	//virtual	INT				GetVigorRegeneRate(VOID);
	//virtual	VOID			SetVigorRegeneRate(INT nRate);

	virtual INT				GetDoubleExpTime_Num(VOID); //获取双倍经验时间和倍数;
	virtual VOID			SetDoubleExpTime_Num(INT nExpTime_Num);

	virtual INT				GetGmRight(VOID);
	virtual VOID			SetGmRight(INT nRight);

	//virtual	INT				GetEnergyRegeneRate(VOID);
	//virtual	VOID			SetEnergyRegeneRate(INT nRate);

	virtual INT 			GetRage( VOID );
	virtual VOID			SetRage( INT nRage );

	UINT					GetMoney();
	VOID					SetMoney(UINT money);

	_PLAYERSHOP_GUID		GetShopGuid(INT nIndex);
	VOID					SetShopGuid(INT nIndex, _PLAYERSHOP_GUID pGuid);

	_PLAYERSHOP_GUID		GetFavoriteShopGuid(INT nIndex);
	VOID					SetFavoriteShopGuid(INT nIndex, _PLAYERSHOP_GUID pGuid);
	BOOL					IsInFavorite(_PLAYERSHOP_GUID pGuid);
	BOOL					AddFavorite(_PLAYERSHOP_GUID pGuid);
	BOOL					DelFavorite(_PLAYERSHOP_GUID pGuid);
	VOID					UpdateFavorite(_PLAYERSHOP_GUID* pGuidList);

	VOID					SetGuildID(GuildID_t guildID);
	GuildID_t				GetGuildID( );
	BOOL					GetSex();
	INT						GetMenPai( );
	VOID					SetMenPai( INT Menpai );
	INT						Get_RemainPoints();
	VOID					Set_RemainPoints(INT Point);
	VOID					ValidatePlayerID();

	UINT					GetEquipID(HUMAN_EQUIP equipPoint);

	//称号		
	const CHAR*				GetCurTitle();
	VOID					SetCurTitle( const CHAR *pszTitle, BYTE nSize );
	BYTE					GetLevelTitle();
	VOID					SetLevelTitle( BYTE title );
	BYTE					GetLifeTitle();
	VOID					SetLifeTitle( BYTE title );
	BYTE					GetRankTitle();
	VOID					SetRankTitle( BYTE title );
	BYTE					GetStoryTitle();
	VOID					SetStoryTitle( BYTE title );
	BYTE					GetKillBossTitle();
	VOID					SetKillBossTitle( BYTE title );
	BYTE					GetTreasureTitle();
	VOID					SetTreasureTitle( BYTE title );
	SHORT					GetDyTitle(BYTE	iTitleIndex);
	VOID					SetDyTitle(BYTE	iTitleIndex, SHORT TitleData);
	const CHAR*				GetNickName() const;
	const CHAR*				GetSpouseName() const;
	const CHAR*				GetBangPaiName() const;
	const CHAR*				GetJieBaiName() const;
	const CHAR*				GetShiTuName() const;
	const CHAR*				GetShangDianName() const;
	VOID					SetNickName(const CHAR *pszTitle, BYTE nSize );
	VOID					SetSpouseName(const CHAR *pszTitle, BYTE nSize );
	VOID					SetBangPaiName(const CHAR *pszTitle, BYTE nSize );
	VOID					SetJieBaiName(const CHAR *pszTitle, BYTE nSize );
	VOID					SetShiTuName(const CHAR *pszTitle, BYTE nSize );
	VOID					SetShangDianName(const CHAR *pszTitle, BYTE nSize );
	VOID					UpdateTitlesToClient();


	// GM专用
	VOID					SetGod( BYTE bGod );
	BOOL					IsGod(VOID)const;

	VOID					SetChangeSceneFlag( BYTE bChangeSceneFlag );
	BOOL					IsHaveChangeSceneFlag(VOID) const;


	VOID					SetWallow( FLOAT fWallow );
	FLOAT					GetWallow(VOID)const;

protected:
	//存放所有关于Obj_Human的、从数据库里读取的信息
	HumanDB					m_DB;
	BYTE					m_bChangeSceneFlag;
	BYTE					m_bGod;
	FLOAT					m_fWallow; //防沉迷系统标记

//===========================================
// 技能
//===========================================
public:
	virtual INT				SkillCharacter( Obj_Character* pCharacter, SkillID_t SkillID, BOOL bNow=FALSE );

	BOOL					Skill_RefixItemAttr(INT nSlotID, INT nItemType, INT nATTRID, SHORT& nAttrValue);
	BOOL					Skill_DepleteItem(VOID);
	virtual BOOL 			Skill_HaveSkill( SkillID_t const nID, BYTE const nLevel = 1 ) const;
	virtual BOOL 			Skill_ModifySkill(SkillID_t	const nID, BYTE const nLevel, INT const nModifyFlag);
	virtual INT 			Skill_GetSkillLevel(SkillID_t const nID) const;
	virtual BOOL 			Skill_SetSkillLevel(SkillID_t const nID, INT const nLevel);
	virtual INT				Skill_GetCount() const;
	virtual const CHAR*		Skill_GetName( SkillID_t const nID, BYTE const nLevel ) const;
	virtual INT				Skill_GetMaxLevel( SkillID_t const nID ) const;
	virtual INT				Skill_GetClass( SkillID_t const nID ) const;
	virtual INT				Skill_GetClassByUser( SkillID_t const nID ) const;
	virtual	INT				Skill_GetMenpai( SkillID_t const nID ) const;
	//VOID					Skill_AllXinFaLevel(INT const nLevel);
	//virtual BOOL 			Skill_HaveXinFa( SkillID_t const nID ) const;
	//virtual INT 			Skill_GetXinFaLevel(SkillID_t const nID) const;
	//virtual BOOL 			Skill_SetXinFaLevel(SkillID_t const nID, INT const nLevel);
	virtual VOID 			Skill_OnEquipItem(VOID);
	_SKILL_LIST&			Skill_GetSkillList(VOID);
	_XINFA_LIST&	 		Skill_GetXinFaList(VOID);
	WORD					FillSkillList(_OWN_SKILL *paSkill, BYTE *paSkillLevel);

	virtual Time_t			GetCooldownRemained(CooldownID_t const nID) const;
	virtual BOOL			IsCooldowned(CooldownID_t const nID) const;
	virtual VOID			SetCooldown(CooldownID_t const nID, Time_t nCooldown);
	virtual BOOL 			HeartBeat_Cooldown(UINT uTime = 0);
	virtual BOOL			HeartBeat_Recover(UINT uTime = 0);

	VOID					ValidateShareMem(BOOL bForceAll); //HeartBeat 最后更新ShareMemory

private:
	VOID	Skill_InitSkillList();
	VOID	Skill_InitXinFaList();
	BOOL 	Skill_RegisterSkill(SkillID_t const nID, BYTE const nLevel);
	BOOL 	Skill_UnregisterSkill(SkillID_t const nID, BYTE const nLevel);
	//BOOL 	Skill_RegisterXinFa(XinFaID_t const nID);
	//BOOL 	Skill_UnregisterXinFa(SkillID_t const nID);
	//VOID	Skill_CleanMenPaiSkillAndXinFa(SKILL_LOG_PARAM* pSkillLog,XINFA_LOG_PARAM* pXinFaLog,INT Menpai);
	//VOID	Skill_ADDAllMenPaiSkillAndXinFa(SKILL_LOG_PARAM* pSkillLog,XINFA_LOG_PARAM* pXinFaLog,INT Menpai);

private:
	BOOL					m_bCanIncreaseRage; //门派特性专用
	Time_t					m_nCommonCooldown;	//公共冷却时间

//===========================================
// 效果
//===========================================
public:

protected:
	virtual _IMPACT_LIST&	Impact_GetImpactList(VOID);

private:
	VOID 					Impact_InitList(VOID);
	VOID					Impact_ActivateList(VOID);
	VOID					Impact_FadeOutAllOfflineFadeImpact(VOID);

//===========================================
// 道具
//===========================================
public:
	//物品部分外部逻辑接口
	BOOL					IsVisualPart(HUMAN_EQUIP EquipPoint);						//是否其他玩家可见部分
	BOOL					ActivateItem(VOID);											//使用物品
	INT						UseStoreMap(UINT BagIndex);									//使用藏宝图
	INT						UseIdentScroll(UINT BagIndex,UINT TargetBagIndex);			//使用鉴定卷轴
	INT						UseGem(UINT GemBagIndex,UINT EquipBagIndex);				//使用Gem
	INT						RemoveGem(UINT BagIndex,UINT GemIndex);						//移出Gem
	INT						UseEquipSkill(INT iUseEquipSkillOffSet,ObjID_t& Target);	//使用装备上技能
	BOOL					UseItem(ID_t nBagIndex, ObjID_t nTargetObj, const WORLD_POS& posTarget, PET_GUID_t const& guidTargetPet, ID_t nTargetItem);//使用物品的功能
	BOOL 					VerifyItem(VOID); //校验使用中的物品是否存在

	virtual	BOOL			IsCarrayItem(UINT ItemType,UINT ItemCount);
	/*
	*	物品背包容器
	*/
	//杂项物品包
	ItemContainer*	GetBaseContain();
	//任务物品包
	//ItemContainer*	GetTaskContain();
	//材料物品包
	//ItemContainer*	GetMatContain();
	//装备
	ItemContainer*	GetEquipContain();
	//银行
	ItemContainer*	GetBankContain();
	//宠物
	ItemContainer*	GetPetContain();

	//根据身上的装备，计算影响因素
	//如果身上的装备发生变化，则需要调用一次此接口，重新计算特殊效果
	VOID					ItemEffectFlush( );
	VOID					CaculateEffect(_ITEM_ATTR& Attr,INT EquipOffset, INT nItemType=INVALID_ID);
	VOID					CaculateEquipSetEffect();

	//装备的各个影响因素
	_ITEM_EFFECT*		ItemEffect( BYTE AttrType ){//AttrType=enum ITEM_ATTRIBUTE 
		Assert( AttrType<IATTRIBUTE_NUMBER );
		return &m_pItemEffect[AttrType];
	}

	virtual _ITEM_VALUE	ItemValue( BYTE AttrType ){//AttrType=enum ITEM_ATTRIBUTE 
		Assert( AttrType<IATTRIBUTE_NUMBER );
		return m_pItemEffect[AttrType].m_Attr;
	}

private:
	//由物品引起的各种效果
	_ITEM_EFFECT		m_pItemEffect[IATTRIBUTE_NUMBER];
	//由物品引起的特殊技能效果

	_ITEM_SKILL		m_EquipUseSkillEffect[HEQUIP_NUMBER+MAX_ITEM_SET_ATTR];
	_ITEM_SKILL		m_EquipRandSkillEffect[HEQUIP_NUMBER+MAX_ITEM_SET_ATTR];

private:
	//杂项物品包
	HumanItemContainer		m_BaseItem;	
	//任务物品包
	//HumanItemContainer		m_TaskItem;
	//材料物品
	//HumanItemContainer		m_MatItem;
	//角色装备				
	HumanItemContainer		m_EquipItem;
	//角色银行
	HumanItemContainer		m_BankItem;
	//宠物背包
	HumanPetContainer		m_PetItem;

//===========================================
// 生活技能
//===========================================
public:
	const _ABILITY_LIST*	GetAbilityList( ) const;
	AbilityOpera*			GetAbilityOpera( );
	VOID					reset_AbilityOpera( ); 
	VOID					InterruptCurrentAbilityOpera();

	// 获取玩家进入事件区域的时间
	UINT GetAreaTimeStamp()
	{
		return m_uTimeStamp;
	}

	// 重新设置玩家进入事件区域的时间（作为下一次触发事件的时间戳）
	VOID ResetAreaTimeStamp(UINT newTimeStamp)
	{
		m_uTimeStamp = newTimeStamp;
	}

protected:
	virtual	ORESULT			Do_UseAbility( VOID );				//进入UseAbility逻辑
	virtual	BOOL			Obj_Logic_UseAbility( UINT uTime );			//执行UseAbility逻辑
	virtual VOID			OnCharacterLogicStopped(BOOL bAbortive);

private:
	AbilityOpera			m_LastOpera;	

//===========================================
// 任务
//===========================================
public:
	const _MISSION_DB_LOAD *GetMissionList( VOID );
	const _MISSION_DB_LOAD *GetConstMissionList( VOID )const;
	//const UINT *GetMissionHaveDoneFlags( VOID )const;

	// 设置是否已经做过了某个任务
	VOID SetMissionHaveDone( MissionID_t idMission, BOOL bHaveDone );

	// 是否已经做过了某个任务
	BOOL IsMissionHaveDone( MissionID_t idMission )const;

	// 加一个任务入任务列表
	ORESULT AddMission( MissionID_t idMission, ScriptID_t idScript, BOOL bKillObjectEvent = TRUE, BOOL bEnterAreaEvent = TRUE, BOOL bItemChangedEvent = TRUE );
	ORESULT AddMissionEx( MissionID_t idMission, ScriptID_t idScript ) ;
	ORESULT SetMissionEvent( MissionID_t idMission, INT EventID/*TASK_EVENT*/ ) ;
	//ORESULT AddMissionKillObjectNotify( MissionID_t idMission, ScriptID_t idScript,INT killObject0,INT killObject1,INT killObject2,INT killObject3);
	//ORESULT AddMissionEnterAreaNotify( MissionID_t idMission, ScriptID_t idScript,INT areaId0,INT areaId1,INT areaId2,INT areaId3);
	//ORESULT AddMissionItemChangedNotify( MissionID_t idMission, ScriptID_t idScript,INT itemTypeSn0,INT itemTypeSn1,INT itemTypeSn2,INT itemTypeSn3);

	// 从任务列表中删除一个任务
	VOID DelMission( MissionID_t idMission );
	VOID DelMissionByIndex( UINT uIndex );

	// 通过任务ID取该任务在任务表表的索引值， 无该任务时返回UINT_MAX
	UINT GetMissionIndexByID( MissionID_t idMission )const;

	// 检测是否已经有了这个任务
	BOOL IsHaveMission( MissionID_t idMission )const;

	// 设置任务参数
	VOID SetMissionParam( UINT uIndexMission, UINT uIndexParam, INT nValue );

	// 取任务参数
	INT GetMissionParam( UINT uIndexMission, UINT uIndexParam )const;
	const _OWN_MISSION *GetMission( UINT uIndex )const;

	//UINT GetCanPickMissionItemCount( VOID )const;
	//const UINT *GetCanPickMissionItemList( VOID )const;
	//VOID AddCanPickMissionItem( UINT uItemDataID );
	//VOID RemoveCanPickMissionItem( UINT uItemDataID );

	//读取附加任务数据
	INT GetMissionData( INT nIndex );

	//设置当前附加任务数据
	VOID SetMissionData( INT nIndex, INT nData );

	//得到某个任务已经执行总次数
	INT GetMissionTotalTimes( INT nIndex );

	//得到某个任务当天执行的总次数
	INT GetMissionTotalDayTimes( INT nIndex );

	//得到某个任务上次完成的时间
	INT GetMissionLastTime( INT nIndex );

	//得到某个任务上次完成是哪天
	INT GetMissionLastDay( INT nIndex );

	//得到某个任务已经跑了多少环
	INT GetMissionTotalHuan( INT nIndex );
protected:
	virtual VOID OnMissionHaveDoneFlagsChanged( MissionID_t idMission );
	virtual VOID OnMissionParamChanged( UINT uIndexMission, UINT uIndexParam ,INT index =0);
	virtual VOID OnAddMission( UINT uIndex );
	virtual VOID OnRemoveMission( MissionID_t idMission );

	//virtual VOID OnAddCanPickMissionItem( UINT uItemDataID );
	//virtual VOID OnRemoveCanPickMissionItem( UINT uItemDataID );

protected:
	// 这里一定要重点优化（杀死OBJECT的事件，得到和删除物品的事件，以及区域切换的事件）
	//UINT				m_uMissionIndex_KillObjectEvent_Num;
	//UINT				m_uMissionIndex_EnterAreaEvent_Num;
	//UINT				m_uMissionIndex_ItemChangedEvent_Num;
	//UINT				m_aMissionIndex_KillObjectEvent[MAX_CHAR_MISSION_NUM];
	//UINT				m_aMissionIndex_EnterAreaEvent[MAX_CHAR_MISSION_NUM];
	//UINT				m_aMissionIndex_ItemChangedEvent[MAX_CHAR_MISSION_NUM];

	//UINT				m_aMissionIndex_KillObject[MAX_CHAR_MISSION_NUM * MAX_MISSION_NOTIFY_NUM];
	//UINT				m_aMissionIndex_EnterArea[MAX_CHAR_MISSION_NUM * MAX_MISSION_NOTIFY_NUM];
	//UINT				m_aMissionIndex_ItemChanged[MAX_CHAR_MISSION_NUM * MAX_MISSION_NOTIFY_NUM];

	//UINT				m_uCanPickMissionItemIDNum;
	//UINT				m_aCanPickMissionItemList[MAX_CHAR_CAN_PICK_MISSION_ITEM_NUM];

//===========================================
// 队伍/联系人
//===========================================
public:
	TeamInfo*		GetTeamInfo();
	HumanRelation*	GetHumanRelation();

private :
	FLOAT					m_fTeamFollowSpeed;
	BOOL					m_bTeamFollowSpeedUp;
	time_t					m_OutofTeamFollowRangeTime;
	_TEAM_MEMBER_INFO		m_SyncTeamMemberInfo;
	TeamInfo				m_TeamInfo;			//队伍相关数据
	HumanRelation			m_HumanRelation;	//联系人相关数据

//===========================================
// Timer
//===========================================
public:

	VOID					AddTimer(INT sceneTimerIndex);		
	VOID					RemoveTimer(INT sceneTimerIndex);	

	INT						GetUseTimerCount();	
	INT						GetMaxTimerCount();	

	BOOL					HaveTimer(INT sceneTimerIndex);

private:
	INT						m_nUseTimer;
	INT*					m_pUseTimer;

//===========================================
// 摆摊/交易/银行/商店
//===========================================
public:
	//摆摊
	VOID				StallNameChanged()	{m_AttrBackUp.m_bStallNameChanged	=	TRUE;}
	BOOL				GetStallIsOpen() { return m_StallBox.GetStallIsOpen(); }
	ServerStallBox		m_StallBox;

	//银行
	BOOL				IsBankOpen(){return BankIsOpen;}
	VOID				SetBankOpen(BOOL bopen){BankIsOpen = bopen;}

	//商店
	VOID				InitialSoldList();
	VOID				AddToSoldList(INT index, UINT uPrice);
	BOOL				GetCurFromSoldList(_ITEM& itemref, UINT& uPrice, BYTE& nCoinType );
	INT					RecieveOneFromSoldList();
	VOID				DeleteFromSoldList();
	VOID				ClearSoldList();

	//金钱变化时
	VOID				NotifyMoneyChange( UINT uAmount, BOOL bIsReceive);

	//当收到物品...call之
	//VOID				OnItemEnterBag(Item* pItem, UINT uBagIndex);

	//商人买卖用的
	VOID				Shop( _SHOP* pShop){m_pShop = pShop;};
	_SHOP*				Shop( ){return m_pShop;};

public:
	//交易
	ServerExchangeBox	m_ExchangBox;//设为公有，因为需要交易对方的频繁访问。

private:
	//银行
	BOOL				BankIsOpen;

	//商店
	ItemContainer		m_SoldContainer;							//卖出物品的container;
	UINT				m_SoldPrice[MAX_BOOTH_SOLD_NUMBER];			//出售价格;
	_ITEM				m_ItemHasBeenSold[MAX_BOOTH_SOLD_NUMBER]; 
	INT					m_nCurSold;
	ObjID_t				m_CurTargetID;

	//存放与此人发生买卖的当前NPC指针
	_SHOP*				m_pShop;

//===========================================
// Other
//===========================================
public:
	VOID ChangeScene( SceneID_t sSceneID, SceneID_t dSceneID, const WORLD_POS& pos, BYTE uDir, BYTE bFlag = 0 ) ;
	VOID CreateCity( SceneID_t PortSceneID) ;
	VOID DeleteCity( SceneID_t PortSceneID, INT iSceneIndex) ;
	VOID ChangeCityBuilding( SceneID_t SceneID, INT BuildingID, INT BuildingLevel) ;
	// 比较二级密码
	BOOL ComparePasswd( const CHAR* szPasswd );

	PlayerID_t				GetPlayerID( );

	Player*					GetPlayer(){ return m_pPlayer; }
	VOID					SetPlayer( Player* pPlayer ){ m_pPlayer = pPlayer; }
	VOID 					Levelup(VOID); //升级的相关属性操作
	VOID					ChangeMenpaiPoints(VOID); //转换门派时点数从新计算
	VOID 					WashPoints(VOID);//洗点的相关操作
	BOOL 					ManualAttrPoint(CHAR_ATTR_LEVEL1 attrType);//手动加点
	BOOL 					ManualAttrPoint(INT nStr, INT nSpr, INT nCon, INT nInt, INT nDex);//手动加点
	VOID					ChangeMenpai(SKILL_LOG_PARAM* pSkillLog,INT Menpai);
	const _SETTING_DB_LOAD *GetSettingList( VOID );
	const _SETTING_DB_LOAD *GetConstSettingList( VOID )const;

	virtual	VOID			OnArmorAbrasion(VOID);
	virtual	VOID			OnWeaponAbrasion(VOID);
	VOID 					SendOperateResultMsg(INT nCode);

protected:

	BOOL						m_bIsPasswdUnlock;	// 密码解锁标记
	BOOL						m_bUpdateAttr;		//更新非即时信息
	CMyTimer					m_UpdateTimer;

	//CMyTimer					m_VERecoverTimer;	// 活力与精力的恢复心跳
	CMyTimer					m_WallowTimer;
	CMyTimer					m_WallowAwokeTimer;
public:
	CMyTimer                    m_ExpTimer;         //设置多倍经验计时器;


public:
	//////////////////////////////////////////////////////////////////////////
	//人物在地图上的注册节点
	_OBJ_LIST_NODE*			HumanNode(){ return m_pHumanNode; }
	BYTE					getMoveIndex( ){ return m_MoveIndex; }
	VOID					setMoveIndex( BYTE index ){ m_MoveIndex = index; }

	//向自己发送新看到的pObj的信息
	//VOID					SendPacket_NewViewObj( Obj* pObj );

	SceneID_t			GetTransSceneID( );
	VOID				SetTransSceneID( SceneID_t id );

private :
	PlayerID_t			m_PlayerID;
	Player*				m_pPlayer;

	//玩家节点信息，用于注册在Zone的HumanList里的
	_OBJ_LIST_NODE*		m_pHumanNode;

	BYTE				m_MoveIndex;	//客户端的发送移动索引号

	WORD				m_EquipVer;
	SceneID_t			m_TransSceneID;

protected:
	CMyTimer			m_CheckZoneTimer; // 对 Zone 进行检查（Area etc...）的计时器
	UINT				m_uAreaID;
	ScriptID_t			m_uAreaScript;
	UINT				m_uTimeStamp;
	UINT				m_uLastTurnPickTime; //最后一次拾取时间

protected:
	VOID				CheckArea();
	//VOID				RefeshAttrMsg() ;		//刷新角色的自动增长数据

protected:
	//CMyTimer			m_RefeshTimer;

public:
	BOOL				GetPosition(WORLD_POS& Pos, const WORLD_POS* pRefPos, FLOAT fDir);

//===========================================
// 宠物
//===========================================
public:
	ORESULT				TestCallUpPet(const PET_GUID_t guidPet);
	ORESULT				CallUpPet(VOID);
	ORESULT				ReCallPet(VOID);
	ORESULT				FreePetToNature(PET_LOG_PARAM* pPetLogParam,PET_GUID_t guidPet);
	ORESULT				AddPetByDataID(PET_LOG_PARAM* pPetLogParam,const UINT uDataID);

	VOID				BabyToAttack(VOID);
	BOOL				CapturePet(PET_LOG_PARAM* pPetLogParam, ObjID_t PetID );
	Obj_Pet*			GetPet( VOID ) const { return m_pPet; }
	VOID				CleanupPet() { m_pPet = NULL; }
	BOOL				CanReturnToChild(PET_GUID_t guid); // 是否可以还童
	BOOL				ReturnToChild(PET_GUID_t guid); // 还童接口

	VOID				SetGUIDOfCallUpPet(PET_GUID_t guid) { m_GUIDOfCallUpPet = guid; }
	PET_GUID_t			GetGUIDOfCallUpPet(VOID) const { return m_GUIDOfCallUpPet; }

	INT					GetPetCount(VOID)const;
	_PET_DB				*GetPetDB( INT nIndex )const;
	const _PET_DB		*GetConstPetDB( INT nIndex )const;

	Item				*GetPetItem(PET_GUID_t guid);
	INT					GetPetIndexByGUID(PET_GUID_t guid);

	// 临时函数
	PET_GUID_t			GetPetGUIDByIndex(INT nIndex);
	PET_GUID_t			GetPetGUIDByValidIndex(INT nIndex);

public:
	BYTE				GetPetHappiness( PET_GUID_t guid );
	VOID				SetPetHappiness( PET_GUID_t guid, BYTE byHappiness );

	INT					GetPetHP( PET_GUID_t guid );
	VOID				SetPetHP( PET_GUID_t guid, INT nHP );

	INT					GetPetMaxHP( PET_GUID_t guid );

	INT					GetPetLife( PET_GUID_t guid );
	VOID				SetPetLife( PET_GUID_t guid, INT nLife );

protected:
	BOOL				AddPet(const _PET_DB *pPetDB);
	BOOL				RemovePet(PET_LOG_PARAM* pPetLogParam,PET_GUID_t guid);

	ORESULT				CreatePet(VOID);
	BOOL				ReleasePet(VOID);

protected:
	Obj_Pet*			m_pPet;
	PET_GUID_t			m_GUIDOfCallUpPet;

public:
	virtual BOOL		Pet_Skill_Have( PET_GUID_t guidPet, SkillID_t const nID );

	// nIndex	:	ENUM_PET_SKILL_INDEX
	const _PET_SKILL	*Pet_Skill_Get( PET_GUID_t guidPet, INT nIndex ) ;

	INT 				Pet_Skill_GetCount_CortrolByPlayer(PET_GUID_t guidPet);
	INT 				Pet_Skill_GetMaxCount_CortrolByPlayer(PET_GUID_t guidPet);
	INT 				Pet_Skill_GetCount_CortrolByAI(PET_GUID_t guidPet);
	INT 				Pet_Skill_GetMaxCount_CortrolByAI(PET_GUID_t guidPet);

	BOOL 				Pet_Skill_Register(PET_GUID_t guidPet, SkillID_t const nID, INT nIndex);
	BOOL 				Pet_Skill_Unregister(PET_GUID_t guidPet, SkillID_t const nID, INT nIndex);
	BOOL 				Pet_Skill_Modify_Study(PET_GUID_t guidPet, SkillID_t nID, INT *pnOutSkillIndex);
	BOOL 				Pet_Skill_Modify_Realize(PET_GUID_t guidPet, SkillID_t nID);
	BOOL 				Pet_Skill_Modify_MenPai(PET_GUID_t guidPet, SkillID_t nID);
	BOOL 				Pet_Skill_Apperceive(PET_GUID_t guidPet);

//===========================================
// 属性
//===========================================
public:
	//StrikePoint
	INT 						GetMaxStrikePoint(VOID);
	//Rage
	INT   						GetMaxRage(VOID);
	//Attr1: Str
	INT							GetStr(VOID);
	INT							GetBaseStr(VOID);
	VOID 						SetBaseStr(INT const nValue);
	//Attr1: Spr
	INT							GetSpr(VOID);
	INT							GetBaseSpr(VOID);
	VOID						SetBaseSpr(INT const nValue);
	//Attr1: Con
	INT							GetCon(VOID);
	INT							GetBaseCon(VOID);
	VOID						SetBaseCon(INT const nValue);
	//Attr1: Int
	INT							GetInt(VOID);
	INT							GetBaseInt(VOID);
	VOID						SetBaseInt(INT const nValue);
	//Attr1: Dex
	INT							GetDex(VOID);
	INT							GetBaseDex(VOID);
	VOID						SetBaseDex(INT const nValue);
	//HP
	INT							GetMaxHP(VOID) ; 
	INT 						GetBaseMaxHP(VOID);
	VOID 						SetBaseMaxHP(INT const nHp);
	INT							GetHPRegenerate(VOID) ; 
	INT							GetBaseHPRegenerate(VOID);
	VOID 						SetBaseHPRegenerate(INT const nValue);

	//MP
	INT 						GetMaxMP(VOID);
	INT 						GetBaseMaxMP(VOID);
	VOID 						SetBaseMaxMp(INT const nMp);
	INT							GetMPRegenerate(VOID); 
	INT 						GetBaseMPRegenerate(VOID);
	VOID 						SetBaseMPRegenerate(INT const nValue);
	//CampID
	virtual const _CAMP_DATA	*GetBaseCampData(VOID)const;
	virtual VOID				SetBaseCampData(const _CAMP_DATA *pCampData);
	INT 						GetCampID(VOID);
	INT 						GetBaseCampID(VOID) const;
	VOID						SetBaseCampID(INT const nID);
	//modelID
	INT 						GetBaseModelID(VOID) const;
	VOID						SetBaseModelID(INT const nID);
	//mountID
	//Alive flag
	//In Combat flag
	// Can move flag
	// Can Action flag
	// Unbreakable flag
	virtual BOOL				IsUnbreakable(VOID);
	// Attr2: Move Speed
	FLOAT						GetMoveSpeed(VOID);
	INT							GetBaseMoveSpeed(VOID);
	VOID						SetBaseMoveSpeed(INT const nValue);
	// Attr2: Attack Speed
	INT 						GetAttackSpeed(VOID);
	INT 						GetBaseAttackSpeed(VOID);
	VOID						SetBaseAttackSpeed(INT const nValue);
	// Attr2: Miss
	INT 						GetMiss(VOID);
	INT 						GetBaseMiss(VOID);
	VOID						SetBaseMiss(INT const nValue);
	// Attr2 Hit
	INT 						GetHit(VOID);
	INT 						GetBaseHit(VOID);
	VOID						SetBaseHit(INT const nValue);
	// Attr2 Critical
	INT 						GetCritical(VOID);
	INT 						GetBaseCritical(VOID);
	VOID						SetBaseCritical(INT const nValue);
	// Attr2: Attack and Defence power physics
	INT 						GetAttackPhysics(VOID);
	INT 						GetBaseAttackPhysics(VOID);
	VOID						SetBaseAttackPhysics(INT const nValue);
	INT 						GetDefencePhysics(VOID);
	INT 						GetBaseDefencePhysics(VOID);
	VOID						SetBaseDefencePhysics(INT const nValue);
	// Attr2: Attack and Defence power of Magic
	INT 						GetAttackMagic(VOID);
	INT 						GetBaseAttackMagic(VOID);
	VOID						SetBaseAttackMagic(INT const nValue);
	INT 						GetDefenceMagic(VOID);
	INT 						GetBaseDefenceMagic(VOID);
	VOID						SetBaseDefenceMagic(INT const nValue);
	// Attr2: Attack and Defence power of Cold
	INT 						GetAttackCold(VOID);
	INT 						GetBaseAttackCold(VOID);
	VOID						SetBaseAttackCold(INT const nValue);
	INT 						GetDefenceCold(VOID);
	INT 						GetBaseDefenceCold(VOID);
	VOID						SetBaseDefenceCold(INT const nValue);
	// Attr2: Attack and Defence power of Fire
	INT 						GetAttackFire(VOID);
	INT 						GetBaseAttackFire(VOID);
	VOID						SetBaseAttackFire(INT const nValue);
	INT 						GetDefenceFire(VOID);
	INT 						GetBaseDefenceFire(VOID);
	VOID						SetBaseDefenceFire(INT const nValue);
	// Attr2: Attack and Defence power of Light
	INT 						GetAttackLight(VOID);
	INT 						GetBaseAttackLight(VOID);
	VOID						SetBaseAttackLight(INT const nValue);
	INT 						GetDefenceLight(VOID);
	INT 						GetBaseDefenceLight(VOID);
	VOID						SetBaseDefenceLight(INT const nValue);
	// Attr2: Attack and Defence power of Poison
	INT 						GetAttackPoison(VOID);
	INT 						GetBaseAttackPoison(VOID);
	VOID						SetBaseAttackPoison(INT const nValue);
	INT 						GetDefencePoison(VOID);
	INT 						GetBaseDefencePoison(VOID);
	VOID						SetBaseDefencePoison(INT const nValue);
	// Attr2 Reduce Slower Duration
	INT 						GetReduceSlowerDuration(VOID);
	// Attr2 Reduce Weaken Duration
	INT 						GetReduceWeakenDuration(VOID);
	// Attr2 Reduce Faint Duration
	INT 						GetReduceFaintDuration(VOID);
	// Attr2 Reduce Poisoned Duration
	INT 						GetReducePoisonedDuration(VOID);
	// Attr2 VisionRange
	INT 						GetVisionRange(VOID);
	INT 						GetBaseVisionRange(VOID);
	VOID						SetBaseVisionRange(INT const nValue);

//===========================================
// _属性接口
//===========================================
public:
	virtual const INT			__GetSex( ) const ;//性别 human
	virtual VOID				__SetSex( const INT sex ) ;
	virtual const UINT			__GetCreateDate( ) const ;//创建时间 human
	virtual VOID				__SetCreateDate( const UINT createdate ) ;
	virtual const CHAR*			__GetNick( ) const ;//昵称 human
	virtual VOID				__SetNick( const CHAR* nick ) ;
	virtual BOOL				__IsPasswordSetup();
	virtual BOOL				__IsPasswordUnlock();
	virtual VOID				__LockPassword(); // 输入二级密码错误，则调用
	virtual VOID				__UnlockPassword(); // 输入二级密码正确
	virtual const CHAR*			__GetPassword( );//二级密码 human
	virtual BOOL				__SetPassword( const CHAR* password );
	virtual VOID				__DelPassword( ); // 删除二级密码
	virtual UINT				__GetPasswordDeleteTime( ); // 强制解除二级密码的时间
	virtual VOID				__SetPasswordDeleteTime( UINT uTime ); // 设置强制解除二级密码的时间
	virtual UINT				__GetPasswordDeleteRemainTime( ); // 得到强制解除密码的剩余时间
	virtual BOOL				__IsValidToDeletePassword( ); // 是否满足强制解除二级密码条件
	virtual UINT				__GetHairColor( ) const ;//头发颜色 human
	virtual VOID				__SetHairColor( UINT haircolor ) ;
	virtual BYTE				__GetFaceColor( ) const ;//脸颜色 human
	virtual VOID				__SetFaceColor( BYTE facecolor ) ;
	virtual BYTE				__GetHairModel( ) const ;//头发模型 human
	virtual VOID				__SetHairModel( BYTE hairmodel ) ;
	virtual BYTE				__GetFaceModel( ) const ;//脸模型 human
	virtual VOID				__SetFaceModel( BYTE facemodel ) ;
	virtual const UINT			__GetOnlineTime( ) const ;//在线时间 human
	virtual VOID				__SetOnlineTime( const UINT onlinetime ) ;
	virtual const UINT			__GetLastLevelUpTime( ) const ;//上次升级时间 human
	virtual VOID				__SetLastLevelUpTime( const UINT lastleveluptime ) ;
	virtual const UINT			__GetLastLoginTime( ) const ;//上次登录时间 human
	virtual VOID				__SetLastLoginTime( const UINT lastlogintime ) ;
	virtual const UINT			__GetLastLogoutTime( ) const ;//上次登出时间 human
	virtual VOID				__SetLastLogoutTime( const UINT lastlogouttime ) ;
	virtual const INT			__GetBagItemCount( ) const ;//背包中物品数量 human
	virtual VOID				__SetBagItemCount( const INT bagitemcount ) ;
	virtual const _ITEM*		__GetBagItem( const INT bagindex ) const ;//背包中某个位置的物品 human
	virtual VOID				__SetBagItem( const INT bagindex, const _ITEM* item ) ;
	virtual const INT			__GetBankItemCount( ) const ;//银行中物品数量 human
	virtual VOID				__SetBankItemCount( const INT Bankitemcount ) ;
	virtual const _ITEM*		__GetBankItem( const INT bankindex ) const ;//银行中某个位置的物品 human
	virtual VOID				__SetBankItem( const INT bankindex, const _ITEM* item ) ;
	virtual const INT			__GetBankEndIndex( ) const ;//当前银行的大小
	virtual VOID				__SetBankEndIndex( const INT bankindex ) ;
	virtual const INT			__GetBankMoney( ) const ;//当前银行内的钱数
	virtual VOID				__SetBankMoney( const INT money ) ;
	virtual const INT			__GetEquipItemCount( ) const ;//装备数量 human
	virtual VOID				__SetEquipItemCount( const INT equipitemcount ) ;
	virtual const _ITEM*		__GetEquipItem( const INT equipindex ) const ;//身上某个位置的装备 human
	virtual VOID				__SetEquipItem( const INT equipindex, const _ITEM* item ) ;
	virtual const INT			__GetMissionCount( ) const ;//接受的任务数量 human
	virtual VOID				__SetMissionCount( const INT missioncount ) ;
	virtual const _OWN_MISSION* __GetMission( const INT missionindex ) const ;//某个任务数据 human
	virtual VOID				__SetMission( const INT missionindex, _OWN_MISSION* mission ) ;
	virtual const BOOL			__IsMissionHaveDone( MissionID_t missionid ) const ;//判断某个任务是否完成 human
	virtual VOID				__SetMissionDoneFalg( MissionID_t missionid, BOOL flag ) ;
	virtual const BOOL			__IsAbilityHaveLearned(AbilityID_t abilityid) const; // 某种生活技能是否学会
	virtual const INT			__GetAbilityLevel( const AbilityID_t abilityid ) const ;//某种生活技能级别 human
	virtual VOID				__SetAbilityLevel( const AbilityID_t abilityid, INT lvl) ;
	virtual const INT			__GetAbilityExp( const AbilityID_t abilityid ) const ;//某种生活技能熟练度 human
	virtual VOID				__SetAbilityExp( const AbilityID_t abilityid, INT exp) ;
	virtual const BOOL			__IsPrescrHaveLearned( const PrescriptionID_t prescrid ) const;//某个配方是否学会 human
	virtual VOID				__SetPrescrLearnedFlag( const PrescriptionID_t prescrid, BOOL flag ) ;
	virtual const _ITEM_EFFECT* __GetItemEffect( const INT index ) const ;//装备效果 human
	virtual VOID				__SetItemEffect( const INT index, _ITEM_EFFECT* itemeffect ) ;
	virtual const _ITEM_VALUE	__GetItemValue( const INT index ) const ;//装备效果值 human
	virtual VOID				__SetItemValue( const INT index, _ITEM_VALUE value) ;
	virtual const UINT			__GetLastTurnPickTime()	const;
	virtual	VOID				__SetLastTurnPickTime(UINT uTime)	;
	virtual const TeamID_t		__GetTeamID( ) const ;//队伍号 human
	virtual VOID				__SetTeamID( const TeamID_t teamid ) ;
	virtual BOOL				__IsTeamLeader( ) const; // 是否队长
	virtual const INT			__GetTeamMemberCount( ) const ;//队伍中成员数量 human
	virtual const TEAMMEMBER*	__GetTeamMember( const INT memberindex ) const ;//取得队伍中某个成员
	virtual VOID				__AddTeamMember( const TEAMMEMBER* member ) ;
	virtual const INT			__GetTeamSceneMemberCount( ) const ;//队伍中同场景成员数量 human
	virtual const ObjID_t		__GetTeamSceneMember( const INT memberindex ) const ;//取得队伍中某同场景成员的 OBJID
	virtual VOID				__SetTeamFollowFlag( BOOL flag ); // 设置队伍跟随状态
	virtual const BOOL			__GetTeamFollowFlag( ) const; // 获得队伍跟随状态
	virtual VOID				__AddFollowedMember( const _FOLLOWEDMEMBER& FollowedMember ); // 增加一个跟随的队员
	virtual VOID				__DelFollowedMember( GUID_t guid ); // 移出一个跟随队员
	virtual const INT			__GetFollowedMembersCount() const; // 得到跟随状态的队友数量
	virtual const _FOLLOWEDMEMBER*	__GetFollowedMember( INT i ) const; // 得到第 i 个跟随的队友
	virtual VOID				__ClearFollowedMembers(); // 清除所有的跟随队友列表
	virtual const FLOAT			__GetTeamFollowSpeed( ) const; // 得到组队跟随的速度
	virtual VOID				__SetTeamFollowSpeed( FLOAT fSpeed ); // 设置组队跟随的速度
	virtual VOID				__OutOfTeamFollowRange(); // 超出组队跟随范围
	virtual VOID				__InTeamFollowRange(); // 在组队跟随范围内
	virtual const BOOL			__GetTeamFollowSpeedUp( ) const; // 获得组队跟随加速状态
	virtual VOID				__SetTeamFollowSpeedUp( BOOL bSpeedUp); // 设置组队跟随加速状态
	virtual VOID				__StopTeamFollow( BOOL bWorldFlag=TRUE ); // 停止跟随,flag表示是否通知 world
};


#endif
