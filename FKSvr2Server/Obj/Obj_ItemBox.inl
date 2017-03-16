#ifndef _OBJ_ITEM_BOX_INL_
#define _OBJ_ITEM_BOX_INL_


VOID				Obj_ItemBox::SetItemBoxID( ObjID_t id )
{
	m_ItemBoxId = id ; 
} 
ObjID_t				Obj_ItemBox::GetItemBoxID( )
{
	return m_ItemBoxId ; 
} 


GUID_t				Obj_ItemBox::GetOwner()
{
	return m_OwnerId;
}
VOID				Obj_ItemBox::SetOwner(GUID_t id)
{
	m_OwnerId = id;
}

/*
void			Obj_ItemBox::SetTeamOwner(TeamID_t	id)
{
	m_OwnerTeam	= id;	
}
TeamID_t		Obj_ItemBox::GetTeamOwner()
{
	return m_OwnerTeam;
}
void			Obj_ItemBox::SetItemPickRuler(IPC	ipc,UCHAR	uIndex)
{
	Assert(uIndex<MAX_BOXITEM_NUMBER);

	m_IPCList[uIndex] = ipc;
}
IPC			Obj_ItemBox::GetItemPickRuler(UCHAR uIndex)
{
	Assert(uIndex<MAX_BOXITEM_NUMBER);

	return m_IPCList[uIndex];
}*/



INT					Obj_ItemBox::GetType()	const
{
	return m_ItemBoxType;
};
VOID				Obj_ItemBox::SetType(INT	Type)
{
	m_ItemBoxType = Type;
};

BOOL				Obj_ItemBox::GetOpenFlag()
{	
	return m_OpenFlag;
}
VOID				Obj_ItemBox::SetOpenFlag(BOOL bFlag)
{ 
	m_OpenFlag = bFlag;
}

INT					Obj_ItemBox::GetRecycleTimes()
{
	return m_RecycleTimes;
}
VOID				Obj_ItemBox::SetRecycleTimes(INT RecycleTimes)
{
	m_RecycleTimes = RecycleTimes;
}


UINT				Obj_ItemBox::GetMaxGrowTime()
{
	return m_MaxGrowTime;
}

inline VOID			Obj_ItemBox::SetPoolPos(UINT	iPos)
{
	m_nPoolPos	= iPos;
}
ItemContainer*		Obj_ItemBox::GetContainer()
{
	return	&m_Container;
}



#endif