// Obj_Human.inl

#ifndef _OBJ_HUMAN_INL_
#define _OBJ_HUMAN_INL_

AI_Human*				Obj_Human::GetHumanAI( VOID )
{
	return ((AI_Human*)m_pAI_Character);
}

AvoidOverlap*           Obj_Human::GetAvoidOverLap()const
{
	return m_pAvoidOverlap;
}

ObjID_t					Obj_Human::GetAssistantID( VOID ) const
{
	return m_AssistantID;
}

VOID					Obj_Human::SetAssistantID( ObjID_t id )
{
	m_AssistantID = id ;
}

HumanDB*				Obj_Human::GetDB()
{
	return &m_DB;
}

GUID_t					Obj_Human::GetGUID( VOID )const
{
	return m_DB.GetGUID();
}

VOID					Obj_Human::SetGuildID(GuildID_t guildID)
{
	m_DB.SetDBGuildID(guildID);
}

GuildID_t				Obj_Human::GetGuildID( )
{
	return m_DB.GetDBGuildID();
}

BOOL					Obj_Human::GetSex()
{
	return m_DB.GetSex();
}

INT						Obj_Human::GetMenPai( )
{
	return m_DB.GetMenPai();
}

VOID					Obj_Human::SetMenPai( INT Menpai )
{
	m_DB.SetMenPai( Menpai );
}

// GM专用
VOID					Obj_Human::SetGod( BYTE bGod )
{
	m_bGod = bGod;
}

BOOL					Obj_Human::IsGod(VOID) const
{
	return (BOOL)m_bGod;
}


VOID					Obj_Human::SetChangeSceneFlag( BYTE bChangeSceneFlag )
{
	m_bChangeSceneFlag = bChangeSceneFlag;
}

BOOL					Obj_Human::IsHaveChangeSceneFlag(VOID) const
{
	return (BOOL)m_bChangeSceneFlag;
}

// 生活技能相关的函数
const _ABILITY_LIST*	Obj_Human::GetAbilityList( ) const
{
	return m_DB.GetAbilityDB();
}

AbilityOpera*			Obj_Human::GetAbilityOpera( )
{
	return &m_LastOpera;
}

VOID					Obj_Human::reset_AbilityOpera( ) 
{
	m_LastOpera.CleanUp();
}

VOID					Obj_Human::Set_RemainPoints(INT Point)
{
	m_DB.SetDBRemainPoints(Point);
}

const CHAR				*Obj_Human::GetName( VOID )const
{
	return m_DB.GetName();
}

const CHAR				*Obj_Human::GetTitle( VOID )const
{
	return m_DB.GetCurTitle();
}

const BYTE				Obj_Human::GetTitleType( VOID )const
{
	return m_DB.GetCurTitleType();
}

INT						Obj_Human::GetLevel( VOID )const
{
	return m_DB.GetHumanDB()->m_Level;
}

INT						Obj_Human::GetPKValue( VOID )const
{
	return m_DB.GetHumanDB()->m_nPKValue;
}

PET_GUID_t				Obj_Human::GetCurrentPetGUID( VOID )const
{
	return m_DB.GetHumanDB()->m_guidCurrentPet;
}

UINT					Obj_Human::GetExp( )
{
	return m_DB.GetExp();
}

UINT					Obj_Human::GetEquipID(HUMAN_EQUIP equipPoint)
{
	return m_DB.GetEquipID(equipPoint);
}

const CHAR*				Obj_Human::GetCurTitle()
{
	return		m_DB.GetCurTitle();
}

VOID					Obj_Human::SetCurTitle( const CHAR *pszTitle, BYTE nSize )
{
	m_DB.SetCurTitle(pszTitle, nSize);
}

BYTE					Obj_Human::GetLevelTitle()
{
	return		m_DB.GetLevelTitle();
}

VOID					Obj_Human::SetLevelTitle( BYTE title )
{
	m_DB.SetLevelTitle(title);
}

BYTE					Obj_Human::GetLifeTitle()
{
	return		m_DB.GetLifeTitle();
}

VOID					Obj_Human::SetLifeTitle( BYTE title )
{
	m_DB.SetLifeTitle(title);
}

BYTE					Obj_Human::GetRankTitle()
{
	return		m_DB.GetRankTitle();
}

VOID					Obj_Human::SetRankTitle( BYTE title )
{
	m_DB.SetRankTitle(title);
}

BYTE					Obj_Human::GetStoryTitle()
{
	return		m_DB.GetStoryTitle();
}

VOID					Obj_Human::SetStoryTitle( BYTE title )
{
	m_DB.SetStoryTitle(title);
}

BYTE					Obj_Human::GetKillBossTitle()
{
	return		m_DB.GetKillBossTitle();
}

VOID					Obj_Human::SetKillBossTitle( BYTE title )
{
	m_DB.SetKillBossTitle(title);
}

BYTE					Obj_Human::GetTreasureTitle()
{
	return		m_DB.GetTreasureTitle();
}

VOID					Obj_Human::SetTreasureTitle( BYTE title )
{
	m_DB.SetTreasureTitle(title);
}

SHORT					Obj_Human::GetDyTitle(BYTE	iTitleIndex)
{
	return	m_DB.GetDyTitle(iTitleIndex);
}

VOID					Obj_Human::SetDyTitle(BYTE	iTitleIndex, SHORT TitleData)
{
	m_DB.SetDyTitle(iTitleIndex, TitleData);
}

const CHAR*				Obj_Human::GetNickName() const
{
	return m_DB.GetNickName();
}

const CHAR*				Obj_Human::GetSpouseName() const
{
	return m_DB.GetSpouseName();
}

const CHAR*				Obj_Human::GetBangPaiName() const
{
	return m_DB.GetBangPaiName();
}

const CHAR*				Obj_Human::GetJieBaiName() const
{
	return m_DB.GetJieBaiName();
}

const CHAR*				Obj_Human::GetShiTuName() const
{
	return m_DB.GetShiTuName();
}

const CHAR*				Obj_Human::GetShangDianName() const
{
	return m_DB.GetShangDianName();
}

VOID					Obj_Human::SetNickName(const CHAR *pszTitle, BYTE nSize )
{
	Assert( pszTitle );

	const CHAR* szCurTitle;
	szCurTitle = GetTitle();

	if(tstricmp(szCurTitle, GetNickName()) == 0 )
	{
		SetTitle(pszTitle);
		if(nSize == 0)
		{
			SetTitleType(_TITLE::NO_TITLE);
		}
		else
		{
			SetTitleType(_TITLE::NICK_TITLE);
		}
	}

	m_DB.SetNickName(pszTitle, nSize);
} 

VOID					Obj_Human::SetSpouseName(const CHAR *pszTitle, BYTE nSize )
{
	Assert( pszTitle );

	const CHAR* szCurTitle;
	szCurTitle = GetTitle();

	if(tstricmp(szCurTitle, GetSpouseName()) == 0 )
	{
		SetTitle(pszTitle);
		if(nSize == 0)
		{
			SetTitleType(_TITLE::NO_TITLE);
		}
		else
		{
			SetTitleType(_TITLE::SPOUSE_TITLE);
		}
	}

	m_DB.SetSpouseName(pszTitle, nSize);
} 

VOID					Obj_Human::SetBangPaiName(const CHAR *pszTitle, BYTE nSize )
{
	Assert( pszTitle );

	const CHAR* szCurTitle;
	szCurTitle = GetTitle();

	if(tstricmp(szCurTitle, GetBangPaiName()) == 0 )
	{
		SetTitle(pszTitle);
		if(nSize == 0)
		{
			SetTitleType(_TITLE::NO_TITLE);
		}
		else
		{
			SetTitleType(_TITLE::BANGPAI_TITLE);
		}
	}

	m_DB.SetBangPaiName(pszTitle, nSize);
} 

VOID					Obj_Human::SetJieBaiName(const CHAR *pszTitle, BYTE nSize )
{
	Assert( pszTitle );

	const CHAR* szCurTitle;
	szCurTitle = GetTitle();

	if(tstricmp(szCurTitle, GetJieBaiName()) == 0)
	{
		SetTitle(pszTitle);
		if(nSize == 0)
		{
			SetTitleType(_TITLE::NO_TITLE);
		}
		else
		{
			SetTitleType(_TITLE::JIEBAI_TITLE);
		}
	}

	m_DB.SetJieBaiName(pszTitle, nSize);
} 

VOID					Obj_Human::SetShiTuName(const CHAR *pszTitle, BYTE nSize )
{
	Assert( pszTitle );

	const CHAR* szCurTitle;
	szCurTitle = GetTitle();

	if(tstricmp(szCurTitle, GetShiTuName()) == 0)
	{
		SetTitle(pszTitle);
		if(nSize == 0)
		{
			SetTitleType(_TITLE::NO_TITLE);
		}
		else
		{
			SetTitleType(_TITLE::SHITU_TITLE);
		}
	}

	m_DB.SetShiTuName(pszTitle, nSize);
}
VOID					Obj_Human::SetShangDianName(const CHAR *pszTitle, BYTE nSize )
{
	Assert( pszTitle );

	const CHAR* szCurTitle;
	szCurTitle = GetTitle();

	if(tstricmp(szCurTitle, GetShangDianName()) == 0 )
	{
		SetTitle(pszTitle);
		if(nSize == 0)
		{
			SetTitleType(_TITLE::NO_TITLE);
		}
		else
		{
			SetTitleType(_TITLE::SHANGDIAN_TITLE);
		}
	}

	m_DB.SetShangDianName(pszTitle, nSize);
}


WORD					Obj_Human::GetEquipVer( )
{
	return m_EquipVer; 
}

VOID					Obj_Human::SetEquipVer( WORD Ver )
{ 
	m_EquipVer = Ver; 
}

SceneID_t				Obj_Human::GetTransSceneID( )
{
	return m_TransSceneID; 
}

VOID					Obj_Human::SetTransSceneID( SceneID_t id )
{ 
	m_TransSceneID = id; 
}


 TeamInfo*		Obj_Human::GetTeamInfo()
{
	return &m_TeamInfo; 
}

 ItemContainer*			Obj_Human::GetBaseContain()
{
	return &m_BaseItem;
}

//ItemContainer*			Obj_Human::GetTaskContain()
//{
//	return &m_TaskItem;
//}
//
//ItemContainer*			Obj_Human::GetMatContain()
//{
//	return &m_MatItem;
//}

 ItemContainer*			Obj_Human::GetEquipContain()
{
	return &m_EquipItem;
}

 ItemContainer*			Obj_Human::GetBankContain()
{
	return &m_BankItem;
}

 ItemContainer*			Obj_Human::GetPetContain()
{
	return &m_PetItem;
}

 HumanRelation*	Obj_Human::GetHumanRelation()
{
	return &m_HumanRelation ;
}

//const UINT *Obj_Human::GetMissionHaveDoneFlags( VOID )const
//{
//	return GetConstMissionList()->m_aMissionHaveDoneFlags;
//}

// 设置是否已经做过了某个任务
VOID Obj_Human::SetMissionHaveDone( MissionID_t idMission, BOOL bHaveDone )
{
__ENTER_FUNCTION
	MissionID_t idIndex = (idMission >> 5);
	Assert( idIndex < MAX_CHAR_MISSION_FLAG_LEN );
	if ( idIndex < MAX_CHAR_MISSION_FLAG_LEN )
	{
		if (bHaveDone)
			m_DB.SetMissionDone(idMission,idIndex);
		else
			m_DB.SetMissionNotDone(idMission,idIndex);
		//((GetMissionList()->m_aMissionHaveDoneFlags[idIndex] |= (0x00000001 << ((UINT)idMission & 0x0000001F))) != 0);
		OnMissionHaveDoneFlagsChanged( idIndex );

		MISSION_LOG_PARAM sParam ;
		sParam.CharGUID = GetGUID();
		sParam.OPType	= MISSION_OP_DONEFLAG ;
		sParam.SceneID	= getScene()->SceneID() ;
		sParam.XPos		= getWorldPos()->m_fX ;
		sParam.ZPos		= getWorldPos()->m_fZ ;
		sParam.idMission= idMission ;
		sParam.nDataIndex = idIndex ;
		sParam.nDataValue = GetConstMissionList()->m_aMissionHaveDoneFlags[idIndex] ;
		SaveMissionLog(&sParam) ;
	}
__LEAVE_FUNCTION
}

// 是否已经做过了某个任务
/*
任务号转换成二进制，如450->111 00010
           前面的111代表任务类型，就是7号类型，共0－127个类型
		   后面的00010代表位移，是否完成这个任务就靠这个标记
		   所以说，一共可以标记128*32＝4096个任务
*/
BOOL Obj_Human::IsMissionHaveDone( MissionID_t idMission )const
{
__ENTER_FUNCTION
	MissionID_t idIndex = (idMission >> 5);
	Assert( idIndex < MAX_CHAR_MISSION_FLAG_LEN );
	if ( idIndex < MAX_CHAR_MISSION_FLAG_LEN )
		return ((GetConstMissionList()->m_aMissionHaveDoneFlags[idIndex] & (0x00000001 << ((UINT)idMission & 0x0000001F))) != 0);
	else
		return FALSE;
__LEAVE_FUNCTION
	return FALSE ;
}

// 检测是否已经有了这个任务
BOOL Obj_Human::IsHaveMission( MissionID_t idMission )const
{
	return (GetMissionIndexByID( idMission ) != UINT_MAX);
}

// 设置任务参数
VOID Obj_Human::SetMissionParam( UINT uIndexMission, UINT uIndexParam, INT nValue )
{
__ENTER_FUNCTION
	Assert(uIndexMission < MAX_CHAR_MISSION_NUM &&uIndexParam < MAX_MISSION_PARAM_NUM );
	if (uIndexMission < MAX_CHAR_MISSION_NUM &&uIndexParam < MAX_MISSION_PARAM_NUM )
	{
		m_DB.SetMissionParam(uIndexMission,uIndexParam,nValue);
		OnMissionParamChanged(uIndexMission,uIndexParam );
	}
__LEAVE_FUNCTION
}

// 取任务参数
INT Obj_Human::GetMissionParam( UINT uIndexMission, UINT uIndexParam )const
{
__ENTER_FUNCTION
	Assert(uIndexMission < MAX_CHAR_MISSION_NUM &&uIndexParam < MAX_MISSION_PARAM_NUM );
	if (uIndexMission < MAX_CHAR_MISSION_NUM &&uIndexParam < MAX_MISSION_PARAM_NUM )
		return GetConstMissionList()->m_aMission[uIndexMission].m_anParam[uIndexParam];
	else
		return FALSE;
__LEAVE_FUNCTION
	return FALSE ;
}

const _OWN_MISSION *Obj_Human::GetMission( UINT uIndex )const
{
	if (uIndex < MAX_CHAR_MISSION_NUM )
		return &GetConstMissionList()->m_aMission[uIndex];
	else
		return NULL;
}

//UINT Obj_Human::GetCanPickMissionItemCount( VOID )const
//{
//	return m_uCanPickMissionItemIDNum;
//}
//
//const UINT *Obj_Human::GetCanPickMissionItemList( VOID )const
//{
//	return &(m_aCanPickMissionItemList[0]);
//}
//
//VOID Obj_Human::AddCanPickMissionItem( UINT uItemDataID )
//{
//	if ( m_uCanPickMissionItemIDNum < MAX_CHAR_CAN_PICK_MISSION_ITEM_NUM )
//	{
//		m_aCanPickMissionItemList[m_uCanPickMissionItemIDNum++] =uItemDataID;
//		OnAddCanPickMissionItem(uItemDataID );
//	}
//}

INT Obj_Human::GetMissionData( INT nIndex )//读取附加任务数据
{
__ENTER_FUNCTION
	if( nIndex<0 || nIndex>=MAX_CHAR_MISSION_DATA_NUM )
	{
		AssertEx( FALSE, "下标超出范围" ) ;
		return 0 ;
	}
	return GetMissionList()->m_aMissionData[nIndex] ;
__LEAVE_FUNCTION
	return 0 ;
}
VOID Obj_Human::SetMissionData( INT nIndex, INT nData )//设置当前附加任务数据
{
__ENTER_FUNCTION
	if( nIndex<0 || nIndex>=MAX_CHAR_MISSION_DATA_NUM )
	{
		AssertEx( FALSE, "下标超出范围" ) ;
	}
	m_DB.SetMissionData(nIndex,nData);
	OnMissionParamChanged(nIndex,nData,1);
__LEAVE_FUNCTION
}
INT Obj_Human::GetMissionTotalTimes( INT nIndex )
{
__ENTER_FUNCTION
	if( nIndex<0 || nIndex>=MAX_CHAR_MISSION_DATA_NUM )
	{
		AssertEx( FALSE, "下标超出范围" ) ;
		return 0 ;
	}
	return GetMissionList()->m_aMissionData[nIndex] / 100000;
__LEAVE_FUNCTION
	return 0 ;
}

INT Obj_Human::GetMissionTotalDayTimes( INT nIndex )
{
__ENTER_FUNCTION
	if( nIndex<0 || (nIndex+1)>=MAX_CHAR_MISSION_DATA_NUM )
	{
		AssertEx( FALSE, "下标超出范围" ) ;
		return 0 ;
	}
	return GetMissionList()->m_aMissionData[nIndex+1] / 10000000;
__LEAVE_FUNCTION
	return 0 ;
}

INT Obj_Human::GetMissionLastTime( INT nIndex )
{
__ENTER_FUNCTION
	if( nIndex<0 || (nIndex+1)>=MAX_CHAR_MISSION_DATA_NUM )
	{
		AssertEx( FALSE, "下标超出范围" ) ;
		return 0 ;
	}
	return GetMissionList()->m_aMissionData[nIndex+1] % 10000;
__LEAVE_FUNCTION
	return 0 ;
}
INT Obj_Human::GetMissionLastDay( INT nIndex )
{
__ENTER_FUNCTION
	if( nIndex<0 || (nIndex)>=MAX_CHAR_MISSION_DATA_NUM )
	{
		AssertEx( FALSE, "下标超出范围" ) ;
		return 0 ;
	}
	return GetMissionList()->m_aMissionData[nIndex] % 100000;
__LEAVE_FUNCTION
	return 0 ;
}

INT Obj_Human::GetMissionTotalHuan( INT nIndex )
{
__ENTER_FUNCTION
	if( nIndex<0 || (nIndex+1)>=MAX_CHAR_MISSION_DATA_NUM )
	{
		AssertEx( FALSE, "下标超出范围" ) ;
		return 0 ;
	}
	return ( GetMissionList()->m_aMissionData[nIndex+1] / 10000 ) % 1000;
__LEAVE_FUNCTION
	return 0 ;
}

VOID Obj_Human::SetCurTarget( ObjID_t idTarget )
{
	m_CurTargetID = idTarget;
}

ObjID_t Obj_Human::GetCurTarget( VOID ) const
{
	return m_CurTargetID;
}

#endif
