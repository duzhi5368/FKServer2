#include "stdafx.h"


#include "GCExchangeSynchLock.h"


UINT GCExchangeSynchLockHandler::Execute( GCExchangeSynchLock* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCExchangeSynchII.h"


UINT GCExchangeSynchIIHandler::Execute( GCExchangeSynchII* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCExchangeSynchConfirmII.h"


UINT GCExchangeSynchConfirmIIHandler::Execute( GCExchangeSynchConfirmII* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCExchangeSuccessIII.h"


UINT GCExchangeSuccessIIIHandler::Execute( GCExchangeSuccessIII* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCExchangeEstablishI.h"


UINT GCExchangeEstablishIHandler::Execute( GCExchangeEstablishI* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCExchangeError.h"


UINT GCExchangeErrorHandler::Execute( GCExchangeError* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}


#include "GCExchangeCancel.h"


UINT GCExchangeCancelHandler::Execute( GCExchangeCancel* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCExchangeApplyI.h"


UINT GCExchangeApplyIHandler::Execute( GCExchangeApplyI* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCPlayerShopOpenStall.h"

UINT GCPlayerShopOpenStallHandler::Execute( GCPlayerShopOpenStall* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCPlayerShopOnSale.h"

UINT GCPlayerShopOnSaleHandler::Execute( GCPlayerShopOnSale* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCPlayerShopMoney.h"

UINT GCPlayerShopMoneyHandler::Execute( GCPlayerShopMoney* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCPlayerShopEstablish.h"


UINT GCPlayerShopEstablishHandler::Execute( GCPlayerShopEstablish* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCPlayerShopError.h"

UINT GCPlayerShopErrorHandler::Execute( GCPlayerShopError* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCPlayerShopApply.h"


UINT GCPlayerShopApplyHandler::Execute( GCPlayerShopApply* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCPlayerShopAcquireShopList.h"

UINT GCPlayerShopAcquireShopListHandler::Execute( GCPlayerShopAcquireShopList* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCPackUpPacket.h"

UINT GCPackUpPacketHandler::Execute(GCPackUpPacket* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCItemSynch.h"

UINT GCItemSynchHandler::Execute( GCItemSynch* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCItemList.h"

UINT GCItemListHandler::Execute( GCItemList* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCBBSMessages.h"


UINT GCBBSMessagesHandler::Execute( GCBBSMessages* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCStallRemoveItem.h"


UINT GCStallRemoveItemHandler::Execute( GCStallRemoveItem* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCStallOpen.h"


UINT GCStallOpenHandler::Execute( GCStallOpen* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCStallItemPrice.h"


UINT GCStallItemPriceHandler::Execute( GCStallItemPrice* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCStallEstablish.h"


UINT GCStallEstablishHandler::Execute( GCStallEstablish* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCStallError.h"


UINT GCStallErrorHandler::Execute( GCStallError* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCStallClose.h"


UINT GCStallCloseHandler::Execute( GCStallClose* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCStallBuy.h"


UINT GCStallBuyHandler::Execute( GCStallBuy* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCStallApply.h"


UINT GCStallApplyHandler::Execute( GCStallApply* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCStallAddItem.h"


UINT GCStallAddItemHandler::Execute( GCStallAddItem* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCTeamResult.h"



UINT GCTeamResultHandler::Execute( GCTeamResult* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCTeamMemberInfo.h"

UINT GCTeamMemberInfoHandler::Execute( GCTeamMemberInfo* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCTeamList.h"

UINT GCTeamListHandler::Execute( GCTeamList* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GCTeamLeaderAskInvite.h"
UINT GCTeamLeaderAskInviteHandler::Execute( GCTeamLeaderAskInvite* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCTeamError.h"



UINT GCTeamErrorHandler::Execute( GCTeamError* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCTeamAskInvite.h"



UINT GCTeamAskInviteHandler::Execute( GCTeamAskInvite* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCTeamAskApply.h"



UINT GCTeamAskApplyHandler::Execute( GCTeamAskApply* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNotifyTeamInfo.h"


UINT GCNotifyTeamInfoHandler::Execute( GCNotifyTeamInfo* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION


	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCTeamFollowList.h"

UINT GCTeamFollowListHandler::Execute( GCTeamFollowList* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}
#include "GCTeamFollowErr.h"

UINT GCTeamFollowErrHandler::Execute( GCTeamFollowErr* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GCReturnTeamFollow.h"

UINT GCReturnTeamFollowHandler::Execute( GCReturnTeamFollow* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GCAskTeamFollow.h"

UINT GCAskTeamFollowHandler::Execute( GCAskTeamFollow* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GCXinfaStudyInfo.h"


UINT GCXinfaStudyInfoHandler::Execute( GCXinfaStudyInfo* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION


	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCStudyXinfa.h"


UINT GCStudyXinfaHandler::Execute( GCStudyXinfa* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION


	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCAbilityTeacherInfo.h"


UINT GCAbilityTeacherInfoHandler::Execute( GCAbilityTeacherInfo* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION


	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCUseItemResult.h"


UINT GCUseItemResultHandler::Execute(GCUseItemResult* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return	PACKET_EXE_ERROR;
}
#include "GCUseGemResult.h"


UINT GCUseGemResultHandler::Execute(GCUseGemResult* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}

#include "GCUseEquipSkillResult.h"

UINT GCUseEquipSkillResultHandler::Execute(GCUseEquipSkillResult* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;
	__LEAVE_FUNCTION
		return PACKET_EXE_ERROR;
}

#include "GCUseEquipResult.h"

UINT GCUseEquipResultHandler::Execute(GCUseEquipResult* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCUnEquipResult.h"


UINT GCUnEquipResultHandler::Execute( GCUnEquipResult* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}


#include "GCUICommand.h"



UINT GCUICommandHandler::Execute( GCUICommand* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCTest.h"



UINT GCTestHandler::Execute( GCTest* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCSplitItemResult.h"



UINT GCSplitItemResultHandler::Execute( GCSplitItemResult* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCSpecialObj_FadeOut.h"

UINT GCSpecialObj_FadeOutHandler::Execute( GCSpecialObj_FadeOut* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION
	return PACKET_EXE_CONTINUE ;
__LEAVE_FUNCTION
	return PACKET_EXE_ERROR ;
}

#include "GCSpecialObj_ActNow.h"

UINT GCSpecialObj_ActNowHandler::Execute( GCSpecialObj_ActNow* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION
	return PACKET_EXE_CONTINUE ;
__LEAVE_FUNCTION
	return PACKET_EXE_ERROR ;
}

#include "GCSkillPrepare.h"



UINT GCSkillPrepareHandler::Execute( GCSkillPrepare* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCSkill.h"



UINT GCSkillHandler::Execute( GCSkill* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCShopUpdateMerchandiseList.h"

UINT GCShopUpdateMerchandiseListHandler::Execute( GCShopUpdateMerchandiseList* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCShopSoldList.h"

UINT GCShopSoldListHandler::Execute( GCShopSoldList* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCShopSell.h"

UINT GCShopSellHandler::Execute( GCShopSell* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCShopRepair.h"

UINT GCShopRepairHandler::Execute( GCShopRepair* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCShopMerchandiseList.h"

UINT GCShopMerchandiseListHandler::Execute( GCShopMerchandiseList* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCShopBuy.h"


UINT GCShopBuyHandler::Execute( GCShopBuy* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCScriptCommand.h"


UINT GCScriptCommandHandler::Execute( GCScriptCommand* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCRetSetting.h"

UINT GCRetSettingHandler::Execute( GCRetSetting* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION


	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCRetChangeScene.h"



UINT GCRetChangeSceneHandler::Execute( GCRetChangeScene* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCReqResetAttrResult.h"


UINT GCReqResetAttrResultHandler::Execute(GCReqResetAttrResult* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION
		return	PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION
		return	PACKET_EXE_ERROR;
}

#include "GCRemovePet.h"

UINT GCRemovePetHandler::Execute( GCRemovePet* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCRemoveGemResult.h"


UINT GCRemoveGemResultHandler::Execute(GCRemoveGemResult* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION
		
		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}

#include "GCRemoveCanPickMissionItem.h"

UINT GCRemoveCanPickMissionItemHandler::Execute( GCRemoveCanPickMissionItem* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCRelation.h"


UINT GCRelationHandler::Execute( GCRelation* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCPrescription.h"

UINT GCPrescriptionHandler::Execute( GCPrescription* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCPlayerRelive.h"


UINT GCPlayerReliveHandler::Execute( GCPlayerRelive* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCPlayerRealMove.h"


UINT GCPlayerRealMoveHandler::Execute( GCPlayerRealMove* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCPlayerDie.h"

UINT GCPlayerDieHandler::Execute( GCPlayerDie* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCPlayerCallOf.h"

UINT GCPlayerCallOfHandler::Execute( GCPlayerCallOf* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCPickResult.h"

UINT GCPickResultHandler::Execute(GCPickResult* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCPetPlacardList.h"

UINT GCPetPlacardListHandler::Execute( GCPetPlacardList* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCPackage_SwapItem.h"

UINT GCPackage_SwapItemHandler :: Execute( GCPackage_SwapItem* pPacket, Player* pPlayer ) 
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}



#include "GCOtherSkill.h"



UINT GCOtherSkillHandler::Execute( GCOtherSkill* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCOtherEquip.h"



UINT GCOtherEquipHandler::Execute( GCOtherEquip* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCOtherAttack.h"



UINT GCOtherAttackHandler::Execute( GCOtherAttack* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCOperateResult.h"



UINT GCOperateResultHandler::Execute( GCOperateResult* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCObjTeleport.h"


UINT GCObjTeleportHandler::Execute( GCObjTeleport* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNotifyMail.h"




UINT GCNotifyMailHandler::Execute( GCNotifyMail* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCNotifyEquip.h"


UINT GCNotifyEquipHandler::Execute( GCNotifyEquip* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION



	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNotifyChangeScene.h"



UINT GCNotifyChangeSceneHandler::Execute( GCNotifyChangeScene* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCNewSpecial.h"


UINT GCNewSpecialHandler::Execute( GCNewSpecial* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION


	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCNewSkillObj.h"



UINT GCNewSkillObjHandler::Execute( GCNewSkillObj* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}


#include "GCNewPortal.h"


UINT GCNewPortalHandler::Execute( GCNewPortal* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION


	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNewPlayer.h"


UINT GCNewPlayerHandler::Execute( GCNewPlayer* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNewPlayer_Move.h"




UINT GCNewPlayer_MoveHandler::Execute( GCNewPlayer_Move* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNewPlayer_Death.h"




UINT GCNewPlayer_DeathHandler::Execute( GCNewPlayer_Death* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCNewPlatform.h"


UINT GCNewPlatformHandler::Execute( GCNewPlatform* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION


	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNewMonster.h"


UINT GCNewMonsterHandler::Execute( GCNewMonster* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNewMonster_Move.h"




UINT GCNewMonster_MoveHandler::Execute( GCNewMonster_Move* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNewMonster_Death.h"




UINT GCNewMonster_DeathHandler::Execute( GCNewMonster_Death* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNewPet.h"


UINT GCNewPetHandler::Execute( GCNewPet* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNewPet_Move.h"




UINT GCNewPet_MoveHandler::Execute( GCNewPet_Move* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNewPet_Death.h"




UINT GCNewPet_DeathHandler::Execute( GCNewPet_Death* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCNewItem.h"


UINT GCNewItemHandler::Execute( GCNewItem* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCNewItemBox.h"


UINT GCNewItemBoxHandler::Execute(GCNewItemBox* pPacket, Player* pPlayer )
{

	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;

}

#include "GCMyBagList.h"


UINT GCMyBagListHandler::Execute(GCMyBagList* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION
		return PACKET_EXE_CONTINUE ;
	__LEAVE_FUNCTION
		return PACKET_EXE_ERROR ;
}


#include "GCMonsterSpeak.h"


UINT GCMonsterSpeakHandler::Execute( GCMonsterSpeak* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}


#include "GCMonsterRealMove.h"



UINT GCMonsterRealMoveHandler::Execute( GCMonsterRealMove* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCModifySpeed.h"


UINT GCModifySpeedHandler::Execute( GCModifySpeed* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCMissionResult.h"

UINT GCMissionResultHandler::Execute( GCMissionResult* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCMissionRemove.h"



UINT GCMissionRemoveHandler::Execute( GCMissionRemove* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCMissionModify.h"


UINT GCMissionModifyHandler::Execute( GCMissionModify* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCMissionList.h"


UINT GCMissionListHandler::Execute( GCMissionList* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCMissionAdd.h"


UINT GCMissionAddHandler::Execute( GCMissionAdd* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCMenpaiInfo.h"

UINT GCMenpaiInfoHandler::Execute( GCMenpaiInfo* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCManualAttrResult.h"



UINT GCManualAttrResultHandler::Execute(GCManualAttrResult* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION
		
		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION	

		return PACKET_EXE_ERROR;
}


#include "GCManipulatePetRet.h"

UINT GCManipulatePetRetHandler::Execute( GCManipulatePetRet* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCMail.h"




UINT GCMailHandler::Execute( GCMail* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCLevelUpResult.h"


UINT GCLevelUpResultHandler::Execute(GCLevelUpResult* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return	PACKET_EXE_ERROR;
}

#include "GCLevelUp.h"


UINT GCLevelUpHandler::Execute(GCLevelUp* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}


#include "GCLeaveScene.h"




UINT GCLeaveSceneHandler::Execute( GCLeaveScene* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCJoinMenpai.h"

UINT GCJoinMenpaiHandler::Execute( GCJoinMenpai* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCItemInfo.h"


UINT	GCItemInfoHandler::Execute(GCItemInfo* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCGuildReturn.h"

UINT GCGuildReturnHandler::Execute( GCGuildReturn* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GCGuild.h"

UINT GCGuildHandler::Execute( GCGuild* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}
#include "GCGuildError.h"

UINT GCGuildErrorHandler::Execute( GCGuildError* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}


#include "GCErrorSkill.h"



UINT GCErrorSkillHandler::Execute( GCErrorSkill* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCErrorAttack.h"



UINT GCErrorAttackHandler::Execute( GCErrorAttack* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCEnterScene.h"


UINT GCEnterSceneHandler::Execute( GCEnterScene* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCDiscardItemResult.h"


UINT	GCDiscardItemResultHandler::Execute(GCDiscardItemResult* pPacket, Player* pPlayer )
{

	__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCDiscardEquipResult.h"

UINT	GCDiscardEquipResultHandler::Execute(GCDiscardEquipResult* pPacket, Player* pPlayer )
{

	__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCDie.h"



UINT GCDieHandler::Execute( GCDie* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCDetailXinFaList.h"




UINT GCSkillClassHandler::Execute( GCSkillClass* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCDetailSubEffectList.h"




UINT GCDetailSubEffectListHandler::Execute( GCDetailSubEffectList* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCDetailSkillList.h"




UINT GCDetailSkillListHandler::Execute( GCDetailSkillList* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCDetailImpactListUpdate.h"


UINT GCDetailImpactListUpdateHandler::Execute( GCDetailImpactListUpdate* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCDetailHealsAndDamages.h"

UINT GCDetailHealsAndDamagesHandler::Execute( GCDetailHealsAndDamages* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCDetailEquipList.h"


UINT GCDetailEquipListHandler::Execute(GCDetailEquipList* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCDetailBUFF.h"
UINT GCDetailBuffHandler::Execute( GCDetailBuff* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCDetailAttrib.h"

UINT GCDetailAttribHandler::Execute( GCDetailAttrib* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCDetailAttrib_Pet.h"

UINT GCDetailAttrib_PetHandler::Execute( GCDetailAttrib_Pet* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCDetailAbilityInfo.h"

UINT GCDetailAbilityInfoHandler::Execute( GCDetailAbilityInfo* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCDelObject.h"




UINT GCDelObjectHandler::Execute( GCDelObject* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCCoolDownUpdate.h"




UINT GCCooldownUpdateHandler::Execute( GCCooldownUpdate* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCConnect.h"




UINT GCConnectHandler::Execute( GCConnect* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCChat.h"



UINT GCChatHandler::Execute( GCChat* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCCharSkill_Send.h"


UINT GCCharSkill_SendHandler::Execute( GCCharSkill_Send* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCCharAction.h"

UINT GCCharActionHandler::Execute( GCCharAction* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCCharModifyAction.h"

UINT GCCharModifyActionHandler::Execute( GCCharModifyAction* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCCharStopAction.h"

UINT GCCharStopActionHandler::Execute( GCCharStopAction* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCCharSkill_Missed.h"

UINT GCCharSkill_MissedHandler::Execute( GCCharSkill_Missed* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION
	return PACKET_EXE_CONTINUE ;
__LEAVE_FUNCTION
	return PACKET_EXE_ERROR ;
}


#include "GCCharSkill_Lead.h"

UINT GCCharSkill_LeadHandler::Execute( GCCharSkill_Lead* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCCharSkill_Lead_Modify.h"




UINT GCCharSkill_Lead_ModifyHandler::Execute( GCCharSkill_Lead_Modify* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCCharSkill_Gather.h"




UINT GCCharSkill_GatherHandler::Execute( GCCharSkill_Gather* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCCharSkill_Gather_Modify.h"




UINT GCCharSkill_Gather_ModifyHandler::Execute( GCCharSkill_Gather_Modify* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}


#include "GCCharSkill_CreateBullet.h"




UINT GCCharSkill_CreateBulletHandler::Execute( GCCharSkill_CreateBullet* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCCharMove.h"

UINT GCCharMoveHandler::Execute( GCCharMove* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCCharMoveResult.h"

UINT GCCharMoveResultHandler::Execute( GCCharMoveResult* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCCharJump.h"




UINT GCCharJumpHandler::Execute( GCCharJump* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCCharImpactListUpdate.h"


UINT GCCharImpactListUpdateHandler::Execute( GCCharImpactListUpdate* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION


	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCCharIdle.h"




UINT GCCharIdleHandler::Execute( GCCharIdle* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCCharEquipment.h"




UINT GCCharEquipmentHandler::Execute( GCCharEquipment* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCCharDirectImpact.h"

UINT GCCharDirectImpactHandler::Execute( GCCharDirectImpact* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCCharBUFF.h"


UINT GCCharBuffHandler::Execute( GCCharBuff* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION
		return PACKET_EXE_CONTINUE ;
	__LEAVE_FUNCTION
		return PACKET_EXE_ERROR ;
}


#include "GCCharBaseAttrib.h"


UINT GCCharBaseAttribHandler::Execute( GCCharBaseAttrib* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCCharAllTitles.h"
UINT GCCharAllTitlesHandler::Execute( GCCharAllTitles* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}


#include "GCChannelResult.h"




UINT GCChannelResultHandler::Execute( GCChannelResult* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCChannelError.h"




UINT GCChannelErrorHandler::Execute( GCChannelError* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCCanPickMissionItemList.h"


UINT GCCanPickMissionItemListHandler::Execute( GCCanPickMissionItemList* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCBoxItemList.h"


UINT GCBoxItemListHandler::Execute(GCBoxItemList* pPacket, Player* pPlayer )
{

	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}


#include "GCBankSwapItem.h"


UINT GCBankSwapItemHandler::Execute( GCBankSwapItem* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCBankRemoveItem.h"


UINT GCBankRemoveItemHandler::Execute( GCBankRemoveItem* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCBankMoney.h"


UINT GCBankMoneyHandler::Execute( GCBankMoney* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCBankItemInfo.h"


UINT GCBankItemInfoHandler::Execute(GCBankItemInfo* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCBankBegin.h"


UINT GCBankBeginHandler::Execute( GCBankBegin* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCBankAddItem.h"


UINT GCBankAddItemHandler::Execute( GCBankAddItem* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCBankAcquireList.h"


UINT GCBankAcquireListHandler::Execute( GCBankAcquireList* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCAttack.h"



UINT GCAttackHandler::Execute( GCAttack* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCArrive.h"



UINT GCArriveHandler::Execute( GCArrive* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCAddCanPickMissionItem.h"


UINT GCAddCanPickMissionItemHandler::Execute( GCAddCanPickMissionItem* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCAbilitySucc.h"

UINT GCAbilitySuccHandler::Execute(GCAbilitySucc* pPacket,Player* pPlayer)
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCAbilityResult.h"

UINT GCAbilityResultHandler::Execute( GCAbilityResult* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}
#include "GCAbilityLevel.h"

UINT GCAbilityLevelHandler::Execute( GCAbilityLevel* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCAbilityExp.h"

UINT GCAbilityExpHandler::Execute( GCAbilityExp* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCAbilityAction.h"

UINT GCAbilityActionHandler::Execute( GCAbilityAction* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
#include "GCAbandonAbility.h"

UINT GCAbandonAbilityHandler::Execute( GCAbandonAbility* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCMinorPasswd.h"

UINT GCMinorPasswdHandler::Execute( GCMinorPasswd* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GCCityNotify.h"

UINT GCCityNotifyHandler::Execute( GCCityNotify* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
#include "GCCityAttr.h"

UINT GCCityAttrHandler::Execute( GCCityAttr* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCCityError.h"
UINT GCCityErrorHandler::Execute( GCCityError* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCPlayerShopSaleOut.h"
UINT GCPlayerShopSaleOutHandler::Execute( GCPlayerShopSaleOut* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCPlayerShopBuyShop.h"
UINT GCPlayerShopBuyShopHandler::Execute( GCPlayerShopBuyShop* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCPrivateInfo.h"
UINT GCPrivateInfoHandler::Execute( GCPrivateInfo* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCGuildApply.h"
UINT GCGuildApplyHandler::Execute( GCGuildApply* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCTargetListAndHitFlags.h"

UINT GCTargetListAndHitFlagsHandler::Execute( GCTargetListAndHitFlags* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCWorldTime.h"
UINT GCWorldTimeHandler::Execute(GCWorldTime* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}

#include "GCFinger.h"
UINT GCFingerHandler::Execute(GCFinger* pPacket,Player* pPlayer)
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GCPlayerShopRecordList.h"
UINT GCPlayerShopRecordListHandler::Execute(GCPlayerShopRecordList* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCPlayerShopUpdatePartners.h"
UINT GCPlayerShopUpdatePartnersHandler::Execute(GCPlayerShopUpdatePartners* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCPlayerShopUpdateFavorite.h"
UINT GCPlayerShopUpdateFavoriteHandler::Execute(GCPlayerShopUpdateFavorite* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCPlayerShopType.h"
UINT GCPlayerShopTypeHandler::Execute(GCPlayerShopType* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCPlayerShopStallStatus.h"
UINT GCPlayerShopStallStatusHandler::Execute(GCPlayerShopStallStatus* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCCharDoAction.h"
UINT GCCharDoActionHandler::Execute(GCCharDoAction* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}

#include "GCNotifyGoodBad.h"

UINT GCNotifyRMBMoneyHandler::Execute( GCNotifyRMBMoney* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GCAddLockObj.h"

UINT GCAddLockObjHandler::Execute( GCAddLockObj* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

#include "GCRetMissionDesc.h"

UINT GCRetMissionDescHandler::Execute( GCRetMissionDesc* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}

#include "GCCharFirstLogin.h"

UINT GCCharFirstLoginHandler::Execute( GCCharFirstLogin* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}

#include"GCSystemMsg.h"

UINT GCSystemMsgHandler::Execute( GCSystemMsg* pPacket,Player* pPlayer)
{
	__ENTER_FUNCTION

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;

}
