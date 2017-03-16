#include "stdafx.h"


#include "WGTeamResult.h"
#include "WGTeamMemberInfo.h"
#include "WGTeamList.h"
#include "WGTeamLeaderAskInvite.h"
#include "WGTeamFollowList.h"
#include "WGTeamError.h"
#include "WGTeamAskInvite.h"
#include "WGTeamAskApply.h"
#include "WGRetUserData.h"
#include "WGRetSceneData.h"
#include "WGRetChangeScene.h"
#include "WGRelation.h"
#include "WGNotifyUser.h"
#include "WGNotifyMail.h"
#include "WGMail.h"
#include "WGGuildReturn.h"
#include "WGGuild.h"
#include "WGGuildError.h"
#include "WGChat.h"
#include "WGChannelResult.h"
#include "WGChannelError.h"
#include "WGWorldTime.h"
#include "WGCallOfHuman.h"
#include "WGFinger.h"

#include "WGCityInitInfo.h"
#include "WGCityApplyNewCity.h"
#include "WGCityAttr.h"
#include "WGCityClose.h"
#include "WGCityCloseSuccess.h"
#include "WGCityError.h"
#include "WGSystemMsg.h"


UINT WGTeamResultHandler::Execute( WGTeamResult* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGTeamMemberInfoHandler::Execute( WGTeamMemberInfo* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

UINT WGTeamListHandler::Execute( WGTeamList* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

UINT WGTeamLeaderAskInviteHandler::Execute( WGTeamLeaderAskInvite* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGTeamFollowListHandler::Execute( WGTeamFollowList* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

UINT WGTeamErrorHandler::Execute( WGTeamError* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGTeamAskInviteHandler::Execute( WGTeamAskInvite* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGTeamAskApplyHandler::Execute( WGTeamAskApply* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGRetUserDataHandler::Execute( WGRetUserData* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGRetSceneDataHandler::Execute( WGRetSceneData* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION


	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGRetChangeSceneHandler::Execute( WGRetChangeScene* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGRelationHandler::Execute( WGRelation* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGNotifyUserHandler::Execute( WGNotifyUser* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGNotifyMailHandler::Execute( WGNotifyMail* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGMailHandler::Execute( WGMail* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGGuildReturnHandler::Execute( WGGuildReturn* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

UINT WGGuildHandler::Execute( WGGuild* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

UINT WGGuildErrorHandler::Execute( WGGuildError* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

UINT WGChatHandler::Execute( WGChat* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGChannelResultHandler::Execute( WGChannelResult* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT WGChannelErrorHandler::Execute( WGChannelError* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

UINT	WGWorldTimeHandler::Execute( WGWorldTime* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

UINT	WGCallOfHumanHandler::Execute( WGCallOfHuman* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

UINT	WGFingerHandler::Execute( WGFinger* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

UINT WGCityApplyNewCityHandler::Execute( WGCityApplyNewCity* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}

UINT WGCityAttrHandler::Execute( WGCityAttr* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

UINT WGCityCloseHandler::Execute( WGCityClose* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

UINT WGCityCloseSuccessHandler::Execute( WGCityCloseSuccess* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

UINT WGCityErrorHandler::Execute( WGCityError* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

UINT WGCityInitInfoHandler::Execute( WGCityInitInfo* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

UINT WGSystemMsgHandler::Execute( WGSystemMsg* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
