
#include "fanni/LLPackets/LLPackets.h"
#include "fanni/LLPackets/LLPacketFactory.h"

namespace Fanni {

LLPacketFactory::LLPacketFactory() {
    PacketList[TestMessage_ID] = new TestMessagePacket();
    PacketList[PacketAck_ID] = new PacketAckPacket();
    PacketList[OpenCircuit_ID] = new OpenCircuitPacket();
    PacketList[CloseCircuit_ID] = new CloseCircuitPacket();
    PacketList[StartPingCheck_ID] = new StartPingCheckPacket();
    PacketList[CompletePingCheck_ID] = new CompletePingCheckPacket();
    PacketList[UseCircuitCode_ID] = new UseCircuitCodePacket();
    PacketList[EconomyDataRequest_ID] = new EconomyDataRequestPacket();
    PacketList[AvatarPickerRequest_ID] = new AvatarPickerRequestPacket();
    PacketList[PlacesQuery_ID] = new PlacesQueryPacket();
    PacketList[DirFindQuery_ID] = new DirFindQueryPacket();
    PacketList[DirPlacesQuery_ID] = new DirPlacesQueryPacket();
    PacketList[DirClassifiedQuery_ID] = new DirClassifiedQueryPacket();
    PacketList[ClassifiedInfoRequest_ID] = new ClassifiedInfoRequestPacket();
    PacketList[ClassifiedInfoUpdate_ID] = new ClassifiedInfoUpdatePacket();
    PacketList[ClassifiedDelete_ID] = new ClassifiedDeletePacket();
    PacketList[ClassifiedGodDelete_ID] = new ClassifiedGodDeletePacket();
    PacketList[DirLandQuery_ID] = new DirLandQueryPacket();
    PacketList[DirPopularQuery_ID] = new DirPopularQueryPacket();
    PacketList[ParcelInfoRequest_ID] = new ParcelInfoRequestPacket();
    PacketList[ParcelObjectOwnersRequest_ID] = new ParcelObjectOwnersRequestPacket();
    PacketList[GroupNoticesListRequest_ID] = new GroupNoticesListRequestPacket();
    PacketList[GroupNoticeRequest_ID] = new GroupNoticeRequestPacket();
    PacketList[TeleportRequest_ID] = new TeleportRequestPacket();
    PacketList[TeleportLocationRequest_ID] = new TeleportLocationRequestPacket();
    PacketList[TeleportLandmarkRequest_ID] = new TeleportLandmarkRequestPacket();
    PacketList[StartLure_ID] = new StartLurePacket();
    PacketList[TeleportLureRequest_ID] = new TeleportLureRequestPacket();
    PacketList[TeleportCancel_ID] = new TeleportCancelPacket();
    PacketList[Undo_ID] = new UndoPacket();
    PacketList[Redo_ID] = new RedoPacket();
    PacketList[UndoLand_ID] = new UndoLandPacket();
    PacketList[AgentPause_ID] = new AgentPausePacket();
    PacketList[AgentResume_ID] = new AgentResumePacket();
    PacketList[AgentUpdate_ID] = new AgentUpdatePacket();
    PacketList[ChatFromViewer_ID] = new ChatFromViewerPacket();
    PacketList[AgentThrottle_ID] = new AgentThrottlePacket();
    PacketList[AgentFOV_ID] = new AgentFOVPacket();
    PacketList[AgentHeightWidth_ID] = new AgentHeightWidthPacket();
    PacketList[AgentSetAppearance_ID] = new AgentSetAppearancePacket();
    PacketList[AgentAnimation_ID] = new AgentAnimationPacket();
    PacketList[AgentRequestSit_ID] = new AgentRequestSitPacket();
    PacketList[AgentSit_ID] = new AgentSitPacket();
    PacketList[AgentQuitCopy_ID] = new AgentQuitCopyPacket();
    PacketList[RequestImage_ID] = new RequestImagePacket();
    PacketList[SetAlwaysRun_ID] = new SetAlwaysRunPacket();
    PacketList[ObjectAdd_ID] = new ObjectAddPacket();
    PacketList[ObjectDelete_ID] = new ObjectDeletePacket();
    PacketList[ObjectDuplicate_ID] = new ObjectDuplicatePacket();
    PacketList[ObjectDuplicateOnRay_ID] = new ObjectDuplicateOnRayPacket();
    PacketList[MultipleObjectUpdate_ID] = new MultipleObjectUpdatePacket();
    PacketList[RequestMultipleObjects_ID] = new RequestMultipleObjectsPacket();
    PacketList[ObjectPosition_ID] = new ObjectPositionPacket();
    PacketList[ObjectScale_ID] = new ObjectScalePacket();
    PacketList[ObjectRotation_ID] = new ObjectRotationPacket();
    PacketList[ObjectFlagUpdate_ID] = new ObjectFlagUpdatePacket();
    PacketList[ObjectClickAction_ID] = new ObjectClickActionPacket();
    PacketList[ObjectImage_ID] = new ObjectImagePacket();
    PacketList[ObjectMaterial_ID] = new ObjectMaterialPacket();
    PacketList[ObjectShape_ID] = new ObjectShapePacket();
    PacketList[ObjectExtraParams_ID] = new ObjectExtraParamsPacket();
    PacketList[ObjectOwner_ID] = new ObjectOwnerPacket();
    PacketList[ObjectGroup_ID] = new ObjectGroupPacket();
    PacketList[ObjectBuy_ID] = new ObjectBuyPacket();
    PacketList[BuyObjectInventory_ID] = new BuyObjectInventoryPacket();
    PacketList[ObjectPermissions_ID] = new ObjectPermissionsPacket();
    PacketList[ObjectSaleInfo_ID] = new ObjectSaleInfoPacket();
    PacketList[ObjectName_ID] = new ObjectNamePacket();
    PacketList[ObjectDescription_ID] = new ObjectDescriptionPacket();
    PacketList[ObjectCategory_ID] = new ObjectCategoryPacket();
    PacketList[ObjectSelect_ID] = new ObjectSelectPacket();
    PacketList[ObjectDeselect_ID] = new ObjectDeselectPacket();
    PacketList[ObjectAttach_ID] = new ObjectAttachPacket();
    PacketList[ObjectDetach_ID] = new ObjectDetachPacket();
    PacketList[ObjectDrop_ID] = new ObjectDropPacket();
    PacketList[ObjectLink_ID] = new ObjectLinkPacket();
    PacketList[ObjectDelink_ID] = new ObjectDelinkPacket();
    PacketList[ObjectGrab_ID] = new ObjectGrabPacket();
    PacketList[ObjectGrabUpdate_ID] = new ObjectGrabUpdatePacket();
    PacketList[ObjectDeGrab_ID] = new ObjectDeGrabPacket();
    PacketList[ObjectSpinStart_ID] = new ObjectSpinStartPacket();
    PacketList[ObjectSpinUpdate_ID] = new ObjectSpinUpdatePacket();
    PacketList[ObjectSpinStop_ID] = new ObjectSpinStopPacket();
    PacketList[ObjectExportSelected_ID] = new ObjectExportSelectedPacket();
    PacketList[ModifyLand_ID] = new ModifyLandPacket();
    PacketList[VelocityInterpolateOn_ID] = new VelocityInterpolateOnPacket();
    PacketList[VelocityInterpolateOff_ID] = new VelocityInterpolateOffPacket();
    PacketList[StateSave_ID] = new StateSavePacket();
    PacketList[ReportAutosaveCrash_ID] = new ReportAutosaveCrashPacket();
    PacketList[SimWideDeletes_ID] = new SimWideDeletesPacket();
    PacketList[RequestObjectPropertiesFamily_ID] = new RequestObjectPropertiesFamilyPacket();
    PacketList[TrackAgent_ID] = new TrackAgentPacket();
    PacketList[ViewerStats_ID] = new ViewerStatsPacket();
    PacketList[ScriptAnswerYes_ID] = new ScriptAnswerYesPacket();
    PacketList[UserReport_ID] = new UserReportPacket();
    PacketList[RequestRegionInfo_ID] = new RequestRegionInfoPacket();
    PacketList[RegionInfo_ID] = new RegionInfoPacket();
    PacketList[GodUpdateRegionInfo_ID] = new GodUpdateRegionInfoPacket();
    PacketList[RegionHandshakeReply_ID] = new RegionHandshakeReplyPacket();
    PacketList[TransferRequest_ID] = new TransferRequestPacket();
    PacketList[TransferInfo_ID] = new TransferInfoPacket();
    PacketList[TransferPacket_ID] = new TransferPacketPacket();
    PacketList[TransferAbort_ID] = new TransferAbortPacket();
    PacketList[RequestXfer_ID] = new RequestXferPacket();
    PacketList[SendXferPacket_ID] = new SendXferPacketPacket();
    PacketList[ConfirmXferPacket_ID] = new ConfirmXferPacketPacket();
    PacketList[AbortXfer_ID] = new AbortXferPacket();
    PacketList[RequestPayPrice_ID] = new RequestPayPricePacket();
    PacketList[GodKickUser_ID] = new GodKickUserPacket();
    PacketList[EjectUser_ID] = new EjectUserPacket();
    PacketList[FreezeUser_ID] = new FreezeUserPacket();
    PacketList[AvatarPropertiesRequest_ID] = new AvatarPropertiesRequestPacket();
    PacketList[AvatarPropertiesUpdate_ID] = new AvatarPropertiesUpdatePacket();
    PacketList[AvatarInterestsUpdate_ID] = new AvatarInterestsUpdatePacket();
    PacketList[AvatarNotesUpdate_ID] = new AvatarNotesUpdatePacket();
    PacketList[EventInfoRequest_ID] = new EventInfoRequestPacket();
    PacketList[EventNotificationAddRequest_ID] = new EventNotificationAddRequestPacket();
    PacketList[EventNotificationRemoveRequest_ID] = new EventNotificationRemoveRequestPacket();
    PacketList[EventGodDelete_ID] = new EventGodDeletePacket();
    PacketList[PickInfoUpdate_ID] = new PickInfoUpdatePacket();
    PacketList[PickDelete_ID] = new PickDeletePacket();
    PacketList[PickGodDelete_ID] = new PickGodDeletePacket();
    PacketList[ScriptDialogReply_ID] = new ScriptDialogReplyPacket();
    PacketList[ForceScriptControlRelease_ID] = new ForceScriptControlReleasePacket();
    PacketList[RevokePermissions_ID] = new RevokePermissionsPacket();
    PacketList[ParcelPropertiesRequest_ID] = new ParcelPropertiesRequestPacket();
    PacketList[ParcelPropertiesRequestByID_ID] = new ParcelPropertiesRequestByIDPacket();
    PacketList[ParcelPropertiesUpdate_ID] = new ParcelPropertiesUpdatePacket();
    PacketList[ParcelReturnObjects_ID] = new ParcelReturnObjectsPacket();
    PacketList[ParcelSetOtherCleanTime_ID] = new ParcelSetOtherCleanTimePacket();
    PacketList[ParcelDisableObjects_ID] = new ParcelDisableObjectsPacket();
    PacketList[ParcelSelectObjects_ID] = new ParcelSelectObjectsPacket();
    PacketList[EstateCovenantRequest_ID] = new EstateCovenantRequestPacket();
    PacketList[ParcelBuyPass_ID] = new ParcelBuyPassPacket();
    PacketList[ParcelDeedToGroup_ID] = new ParcelDeedToGroupPacket();
    PacketList[ParcelReclaim_ID] = new ParcelReclaimPacket();
    PacketList[ParcelClaim_ID] = new ParcelClaimPacket();
    PacketList[ParcelJoin_ID] = new ParcelJoinPacket();
    PacketList[ParcelDivide_ID] = new ParcelDividePacket();
    PacketList[ParcelRelease_ID] = new ParcelReleasePacket();
    PacketList[ParcelBuy_ID] = new ParcelBuyPacket();
    PacketList[ParcelGodForceOwner_ID] = new ParcelGodForceOwnerPacket();
    PacketList[ParcelAccessListRequest_ID] = new ParcelAccessListRequestPacket();
    PacketList[ParcelAccessListUpdate_ID] = new ParcelAccessListUpdatePacket();
    PacketList[ParcelDwellRequest_ID] = new ParcelDwellRequestPacket();
    PacketList[ParcelGodMarkAsContent_ID] = new ParcelGodMarkAsContentPacket();
    PacketList[ViewerStartAuction_ID] = new ViewerStartAuctionPacket();
    PacketList[UUIDNameRequest_ID] = new UUIDNameRequestPacket();
    PacketList[UUIDGroupNameRequest_ID] = new UUIDGroupNameRequestPacket();
    PacketList[GetScriptRunning_ID] = new GetScriptRunningPacket();
    PacketList[ScriptRunningReply_ID] = new ScriptRunningReplyPacket();
    PacketList[SetScriptRunning_ID] = new SetScriptRunningPacket();
    PacketList[ScriptReset_ID] = new ScriptResetPacket();
    PacketList[CompleteAgentMovement_ID] = new CompleteAgentMovementPacket();
    PacketList[AgentMovementComplete_ID] = new AgentMovementCompletePacket();
    PacketList[LogoutRequest_ID] = new LogoutRequestPacket();
    PacketList[ImprovedInstantMessage_ID] = new ImprovedInstantMessagePacket();
    PacketList[RetrieveInstantMessages_ID] = new RetrieveInstantMessagesPacket();
    PacketList[FindAgent_ID] = new FindAgentPacket();
    PacketList[RequestGodlikePowers_ID] = new RequestGodlikePowersPacket();
    PacketList[GodlikeMessage_ID] = new GodlikeMessagePacket();
    PacketList[EstateOwnerMessage_ID] = new EstateOwnerMessagePacket();
    PacketList[GenericMessage_ID] = new GenericMessagePacket();
    PacketList[MuteListRequest_ID] = new MuteListRequestPacket();
    PacketList[UpdateMuteListEntry_ID] = new UpdateMuteListEntryPacket();
    PacketList[RemoveMuteListEntry_ID] = new RemoveMuteListEntryPacket();
    PacketList[CopyInventoryFromNotecard_ID] = new CopyInventoryFromNotecardPacket();
    PacketList[UpdateInventoryItem_ID] = new UpdateInventoryItemPacket();
    PacketList[MoveInventoryItem_ID] = new MoveInventoryItemPacket();
    PacketList[CopyInventoryItem_ID] = new CopyInventoryItemPacket();
    PacketList[RemoveInventoryItem_ID] = new RemoveInventoryItemPacket();
    PacketList[ChangeInventoryItemFlags_ID] = new ChangeInventoryItemFlagsPacket();
    PacketList[CreateInventoryFolder_ID] = new CreateInventoryFolderPacket();
    PacketList[UpdateInventoryFolder_ID] = new UpdateInventoryFolderPacket();
    PacketList[MoveInventoryFolder_ID] = new MoveInventoryFolderPacket();
    PacketList[RemoveInventoryFolder_ID] = new RemoveInventoryFolderPacket();
    PacketList[FetchInventoryDescendents_ID] = new FetchInventoryDescendentsPacket();
    PacketList[FetchInventory_ID] = new FetchInventoryPacket();
    PacketList[RemoveInventoryObjects_ID] = new RemoveInventoryObjectsPacket();
    PacketList[PurgeInventoryDescendents_ID] = new PurgeInventoryDescendentsPacket();
    PacketList[UpdateTaskInventory_ID] = new UpdateTaskInventoryPacket();
    PacketList[RemoveTaskInventory_ID] = new RemoveTaskInventoryPacket();
    PacketList[MoveTaskInventory_ID] = new MoveTaskInventoryPacket();
    PacketList[RequestTaskInventory_ID] = new RequestTaskInventoryPacket();
    PacketList[DeRezObject_ID] = new DeRezObjectPacket();
    PacketList[RezObject_ID] = new RezObjectPacket();
    PacketList[RezObjectFromNotecard_ID] = new RezObjectFromNotecardPacket();
    PacketList[AcceptFriendship_ID] = new AcceptFriendshipPacket();
    PacketList[DeclineFriendship_ID] = new DeclineFriendshipPacket();
    PacketList[TerminateFriendship_ID] = new TerminateFriendshipPacket();
    PacketList[OfferCallingCard_ID] = new OfferCallingCardPacket();
    PacketList[AcceptCallingCard_ID] = new AcceptCallingCardPacket();
    PacketList[DeclineCallingCard_ID] = new DeclineCallingCardPacket();
    PacketList[RezScript_ID] = new RezScriptPacket();
    PacketList[CreateInventoryItem_ID] = new CreateInventoryItemPacket();
    PacketList[CreateLandmarkForEvent_ID] = new CreateLandmarkForEventPacket();
    PacketList[RegionHandleRequest_ID] = new RegionHandleRequestPacket();
    PacketList[MoneyTransferRequest_ID] = new MoneyTransferRequestPacket();
    PacketList[MoneyBalanceRequest_ID] = new MoneyBalanceRequestPacket();
    PacketList[ActivateGestures_ID] = new ActivateGesturesPacket();
    PacketList[DeactivateGestures_ID] = new DeactivateGesturesPacket();
    PacketList[UseCachedMuteList_ID] = new UseCachedMuteListPacket();
    PacketList[GrantUserRights_ID] = new GrantUserRightsPacket();
    PacketList[SetStartLocationRequest_ID] = new SetStartLocationRequestPacket();
    PacketList[NetTest_ID] = new NetTestPacket();
    PacketList[SetCPURatio_ID] = new SetCPURatioPacket();
    PacketList[SimCrashed_ID] = new SimCrashedPacket();
    PacketList[RemoveAttachment_ID] = new RemoveAttachmentPacket();
    PacketList[SoundTrigger_ID] = new SoundTriggerPacket();
    PacketList[AssetUploadRequest_ID] = new AssetUploadRequestPacket();
    PacketList[AssetUploadComplete_ID] = new AssetUploadCompletePacket();
    PacketList[CreateGroupRequest_ID] = new CreateGroupRequestPacket();
    PacketList[UpdateGroupInfo_ID] = new UpdateGroupInfoPacket();
    PacketList[GroupRoleChanges_ID] = new GroupRoleChangesPacket();
    PacketList[JoinGroupRequest_ID] = new JoinGroupRequestPacket();
    PacketList[EjectGroupMemberRequest_ID] = new EjectGroupMemberRequestPacket();
    PacketList[LeaveGroupRequest_ID] = new LeaveGroupRequestPacket();
    PacketList[InviteGroupRequest_ID] = new InviteGroupRequestPacket();
    PacketList[GroupProfileRequest_ID] = new GroupProfileRequestPacket();
    PacketList[GroupAccountSummaryRequest_ID] = new GroupAccountSummaryRequestPacket();
    PacketList[GroupAccountDetailsRequest_ID] = new GroupAccountDetailsRequestPacket();
    PacketList[GroupAccountTransactionsRequest_ID] = new GroupAccountTransactionsRequestPacket();
    PacketList[GroupActiveProposalsRequest_ID] = new GroupActiveProposalsRequestPacket();
    PacketList[GroupVoteHistoryRequest_ID] = new GroupVoteHistoryRequestPacket();
    PacketList[StartGroupProposal_ID] = new StartGroupProposalPacket();
    PacketList[GroupProposalBallot_ID] = new GroupProposalBallotPacket();
    PacketList[GroupMembersRequest_ID] = new GroupMembersRequestPacket();
    PacketList[ActivateGroup_ID] = new ActivateGroupPacket();
    PacketList[SetGroupContribution_ID] = new SetGroupContributionPacket();
    PacketList[SetGroupAcceptNotices_ID] = new SetGroupAcceptNoticesPacket();
    PacketList[GroupRoleDataRequest_ID] = new GroupRoleDataRequestPacket();
    PacketList[GroupRoleMembersRequest_ID] = new GroupRoleMembersRequestPacket();
    PacketList[GroupTitlesRequest_ID] = new GroupTitlesRequestPacket();
    PacketList[GroupTitleUpdate_ID] = new GroupTitleUpdatePacket();
    PacketList[GroupRoleUpdate_ID] = new GroupRoleUpdatePacket();
    PacketList[AgentWearablesRequest_ID] = new AgentWearablesRequestPacket();
    PacketList[AgentIsNowWearing_ID] = new AgentIsNowWearingPacket();
    PacketList[AgentCachedTexture_ID] = new AgentCachedTexturePacket();
    PacketList[AgentDataUpdateRequest_ID] = new AgentDataUpdateRequestPacket();
    PacketList[ViewerEffect_ID] = new ViewerEffectPacket();
    PacketList[CreateTrustedCircuit_ID] = new CreateTrustedCircuitPacket();
    PacketList[DenyTrustedCircuit_ID] = new DenyTrustedCircuitPacket();
    PacketList[RezSingleAttachmentFromInv_ID] = new RezSingleAttachmentFromInvPacket();
    PacketList[RezMultipleAttachmentsFromInv_ID] = new RezMultipleAttachmentsFromInvPacket();
    PacketList[DetachAttachmentIntoInv_ID] = new DetachAttachmentIntoInvPacket();
    PacketList[CreateNewOutfitAttachments_ID] = new CreateNewOutfitAttachmentsPacket();
    PacketList[UserInfoRequest_ID] = new UserInfoRequestPacket();
    PacketList[UserInfoReply_ID] = new UserInfoReplyPacket();
    PacketList[UpdateUserInfo_ID] = new UpdateUserInfoPacket();
    PacketList[InitiateDownload_ID] = new InitiateDownloadPacket();
    PacketList[MapLayerRequest_ID] = new MapLayerRequestPacket();
    PacketList[MapBlockRequest_ID] = new MapBlockRequestPacket();
    PacketList[MapNameRequest_ID] = new MapNameRequestPacket();
    PacketList[MapItemRequest_ID] = new MapItemRequestPacket();
    PacketList[SendPostcard_ID] = new SendPostcardPacket();
    PacketList[RpcScriptRequestInbound_ID] = new RpcScriptRequestInboundPacket();
    PacketList[RpcScriptReplyInbound_ID] = new RpcScriptReplyInboundPacket();
    PacketList[LandStatRequest_ID] = new LandStatRequestPacket();
    PacketList[Error_ID] = new ErrorPacket();
    PacketList[ObjectIncludeInSearch_ID] = new ObjectIncludeInSearchPacket();

}

LLPacketFactory::~LLPacketFactory() {}

PacketSerializer *CreateLLPacketSerializer() {
    return new PacketSerializer(LLPacketFactorySingleton::get());
}

}

