// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "BlueprintDataDefinitions.h"
#include "UpdateSessionCallbackProxyAdvanced.generated.h"

UCLASS(MinimalAPI)
class UUpdateSessionCallbackProxyAdvanced : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	// Called when the session was updated successfully
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	// Called when there was an error updating the session
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	// Creates a session with the default online subsystem with advanced optional inputs, you MUST fill in all categories or it will pass in values that you didn't want as default values
	// 使用默认在线子系统更新当前会话；你必须填满所有分类参数，否则会传入你不想要的默认值
	// （注意：上方英文原注释疑似从CreateSession复制而来，本函数实际功能是更新会话UpdateSession）
	// [相对5.0] 5.3起重新加入bShouldAdvertise参数（5.0曾移除该参数）
	// [相对5.3] 5.4起新增bAllowJoinViaPresence与bAllowJoinViaPresenceFriendsOnly参数（是否允许通过Presence加入）
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "更新会话 (UpdateSession)", BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject",AutoCreateRefTerm="ExtraSettings"), Category = "Online|AdvancedSessions")
	static UUpdateSessionCallbackProxyAdvanced* UpdateSession(UObject* WorldContextObject, const TArray<FSessionPropertyKeyPair> &ExtraSettings, int32 PublicConnections = 100, int32 PrivateConnections = 0, bool bUseLAN = false, bool bAllowInvites = false, bool bAllowJoinInProgress = false, bool bRefreshOnlineData = true, bool bIsDedicatedServer = false, bool bShouldAdvertise = true, bool bAllowJoinViaPresence = true, bool bAllowJoinViaPresenceFriendsOnly = false);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// Internal callback when session creation completes, calls StartSession
	void OnUpdateCompleted(FName SessionName, bool bWasSuccessful);

	// The delegate executed by the online subsystem
	FOnUpdateSessionCompleteDelegate OnUpdateSessionCompleteDelegate;

	// Handles to the registered delegates above
	FDelegateHandle OnUpdateSessionCompleteDelegateHandle;

	// Number of public connections
	int NumPublicConnections = 100;

	// Number of private connections
	int NumPrivateConnections = 0;

	// Whether or not to search LAN
	bool bUseLAN = false;

	// Whether or not to allow invites
	bool bAllowInvites = true;

	// Store extra settings
	TArray<FSessionPropertyKeyPair> ExtraSettings;

	// Whether to update the online data
	bool bRefreshOnlineData = true;

	// Allow joining in progress
	bool bAllowJoinInProgress = true;

	// Allow joining in progress
	bool bAllowJoinViaPresence = true;

	// Allow joining in progress
	bool bAllowJoinViaPresenceFriendsOnly = false;

	// Update whether this is a dedicated server or not
	bool bDedicatedServer = false;

	bool bShouldAdvertise = true;

	// The world context object in which this call is taking place
	TWeakObjectPtr<UObject> WorldContextObject;
};

