// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "BlueprintDataDefinitions.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Engine/LocalPlayer.h"
#include "LoginUserCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class ULoginUserCallbackProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	// Called when there is a successful destroy
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	// Called when there is an unsuccessful destroy
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	// Logs into the identity interface
	// 登录到身份（Identity）接口
	// [相对4.26] 4.27起新增AuthType参数（认证类型），并归类为AdvancedDisplay高级显示参数
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "登录用户 (LoginUser)", BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject", AdvancedDisplay = "AuthType"), Category = "Online|AdvancedIdentity")
	static ULoginUserCallbackProxy* LoginUser(UObject* WorldContextObject, class APlayerController* PlayerController, FString UserID, FString UserToken, FString AuthType);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// Internal callback when the operation completes, calls out to the public success/failure callbacks
	void OnCompleted(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& ErrorVal);

private:
	// The player controller triggering things
	TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;

	// The user ID
	FString UserID;

	// The user pass / token
	FString UserToken;

	FString AuthType;

	// The delegate executed by the online subsystem
	FOnLoginCompleteDelegate Delegate;

	// Handle to the registered OnDestroySessionComplete delegate
	FDelegateHandle DelegateHandle;

	// The world context object in which this call is taking place
	UObject* WorldContextObject;
};
