// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Online.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlineUserInterface.h"
#include "Interfaces/OnlineMessageInterface.h"
#include "Interfaces/OnlinePresenceInterface.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "UObject/UObjectIterator.h"
#include "BlueprintDataDefinitions.h"
#include "AdvancedFriendsInterface.generated.h"


UINTERFACE(MinimalAPI)
class UAdvancedFriendsInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IAdvancedFriendsInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	
	// Called when the designated LocalUser has accepted a session invite, use JoinSession on result to connect
	// 当指定本地用户（LocalUser）接受会话邀请时调用，可对结果调用JoinSession进行连接
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "收到会话邀请 (OnSessionInviteReceived)"))
	void OnSessionInviteReceived(FBPUniqueNetId PersonInviting, const FBlueprintSessionResult& SearchResult);

	// Called when the designated LocalUser has accepted a session invite, use JoinSession on result to connect
	// 当指定本地用户（LocalUser）接受会话邀请时调用，可对结果调用JoinSession进行连接
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "会话邀请被接受 (OnSessionInviteAccepted)"))
	void OnSessionInviteAccepted(FBPUniqueNetId PersonInvited, const FBlueprintSessionResult& SearchResult);

	// Called when the designated LocalUser has accepted a session invite, use JoinSession on result to connect
	// 当指定本地用户（LocalUser）的语音状态改变时调用（注意：上方英文原注释疑似复制粘贴错误）
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "玩家语音状态改变 (OnPlayerVoiceStateChanged)"))
	void OnPlayerVoiceStateChanged(FBPUniqueNetId PlayerId, bool bIsTalking);

	// Called when the designated LocalUser has changed login state
	// 当指定本地用户（LocalUser）改变登录状态时调用
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "玩家登录状态改变 (OnPlayerLoginChanged)"))
	void OnPlayerLoginChanged(int32 PlayerNum);

	// Called when the designated LocalUser has changed login state
	// 当指定本地用户（LocalUser）的登录状态改变时调用
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "玩家登录状态变更 (OnPlayerLoginStatusChanged)"))
	void OnPlayerLoginStatusChanged(EBPLoginStatus PreviousStatus, EBPLoginStatus NewStatus, FBPUniqueNetId PlayerUniqueNetID);

	// REMOVED BECAUSE IT WAS NEVER BEING CALLED
	// Called when the designated LocalUser has received a session invite, use JoinSession on result to connect
	//UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "OnSessionInviteReceived"))
	//void OnSessionInviteReceived(const FBPUniqueNetId &FriendInviting, const FBlueprintSessionResult &Session);

};	
