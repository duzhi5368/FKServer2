#include "stdafx.h"

#include "GWNotifyUser.h"




UINT GWNotifyUserHandler::Execute( GWNotifyUser* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GWMail.h"




UINT GWMailHandler::Execute( GWMail* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GWLevelUp.h"



UINT GWLevelUpHandler::Execute(GWLevelUp* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}
#include "GWGuild.h"

UINT GWGuildHandler::Execute( GWGuild* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}


#include "GWCommand.h"




UINT GWCommandHandler::Execute( GWCommand* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GWChannelKick.h"




UINT GWChannelKickHandler::Execute( GWChannelKick* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GWChat.h"




UINT GWChatHandler::Execute( GWChat* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWChannelInvite.h"




UINT GWChannelInviteHandler::Execute( GWChannelInvite* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GWChannelDismiss.h"




UINT GWChannelDismissHandler::Execute( GWChannelDismiss* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWChannelCreate.h"




UINT GWChannelCreateHandler::Execute( GWChannelCreate* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GWBatchMail.h"

UINT GWBatchMailHandler::Execute( GWBatchMail* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GWAskUserData.h"




UINT GWAskUserDataHandler::Execute( GWAskUserData* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWAskSceneData.h"




UINT GWAskSceneDataHandler::Execute( GWAskSceneData* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWAskMail.h"




UINT GWAskMailHandler::Execute( GWAskMail* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWAskChangeScene.h"




UINT GWAskChangeSceneHandler::Execute( GWAskChangeScene* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWRelation.h"


UINT GWRelationHandler::Execute( GWRelation* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWTeamRetApply.h"



UINT GWTeamRetApplyHandler::Execute( GWTeamRetApply* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWTeamMemberEnterScene.h"

UINT GWTeamMemberEnterSceneHandler::Execute( GWTeamMemberEnterScene* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GWTeamLeave.h"



UINT GWTeamLeaveHandler::Execute( GWTeamLeave* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWTeamLeaderRetInvite.h"



UINT GWTeamLeaderRetInviteHandler::Execute( GWTeamLeaderRetInvite* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWTeamKick.h"



UINT GWTeamKickHandler::Execute( GWTeamKick* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWTeamInvite.h"



UINT GWTeamInviteHandler::Execute( GWTeamInvite* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWTeamDismiss.h"



UINT GWTeamDismissHandler::Execute( GWTeamDismiss* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWTeamAppoint.h"


UINT GWTeamAppointHandler::Execute( GWTeamAppoint* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION


	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWTeamApply.h"



UINT GWTeamApplyHandler::Execute( GWTeamApply* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWAskTeamMemberInfo.h"

UINT GWAskTeamMemberInfoHandler::Execute( GWAskTeamMemberInfo* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GWTeamRetInvite.h"



UINT GWTeamRetInviteHandler::Execute( GWTeamRetInvite* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWAskTeamInfo.h"

UINT GWAskTeamInfoHandler::Execute( GWAskTeamInfo* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GWEnterTeamFollow.h"

UINT GWEnterTeamFollowHandler::Execute( GWEnterTeamFollow* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GWStopTeamFollow.h"

UINT GWStopTeamFollowHandler::Execute( GWStopTeamFollow* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GWCityApplyNewCity.h"

UINT GWCityApplyNewCityHandler::Execute( GWCityApplyNewCity* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}

#include "GWCityAskInitInfo.h"

UINT GWCityAskInitInfoHandler::Execute( GWCityAskInitInfo* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}

#include "GWCityClose.h"

UINT GWCityCloseHandler::Execute( GWCityClose* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}

#include "GWCityCloseSuccess.h"

UINT GWCityCloseSuccessHandler::Execute( GWCityCloseSuccess* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}

#include "GWCityOpt.h"

UINT GWCityOptHandler::Execute( GWCityOpt* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}

#include "GWUpdateTitle.h"

UINT GWUpdateTitleHandler::Execute( GWUpdateTitle* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GWChangeMenpai.h"

UINT GWChangeMenpaiHandler::Execute( GWChangeMenpai* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GWCallOfHuman.h"

UINT GWCallOfHumanHandler::Execute( GWCallOfHuman* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GWFinger.h"
UINT GWFingerHandler::Execute(GWFinger* pPacket,Player* pPlayer)
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GWHeartBeat.h"
UINT GWHeartBeatHandler::Execute(GWHeartBeat* pPacket,Player* pPlayer)
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GWSystemMsg.h"

UINT GWSystemMsgHandler::Execute(GWSystemMsg* pPacket,Player *pPlayer) 
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}