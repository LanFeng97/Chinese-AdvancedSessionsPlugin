// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "BlueprintDataDefinitions.h"
#include "EndSessionCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UEndSessionCallbackProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	// Called when there is a successful destroy
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	// Called when there is an unsuccessful destroy
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	// Ends the current session
	// 结束当前会话
	// 注意：该函数已弃用。官方说明：发现人们一直在误用此函数，且它在蓝图中用处不大，请仅使用销毁会话（Destroy Session）代替。
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "结束会话 (EndSession)", DeprecatedFunction,DeprecationMessage = "This function is deprecated, I realized that people have been using it wrong and it doesn't have much use in blueprints. Use Destroy Session only instead.",BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category = "Online|AdvancedSessions|Deprecated")
	static UEndSessionCallbackProxy* EndSession(UObject* WorldContextObject, class APlayerController* PlayerController);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// Internal callback when the operation completes, calls out to the public success/failure callbacks
	void OnCompleted(FName SessionName, bool bWasSuccessful);

private:
	// The player controller triggering things
	TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;

	// The delegate executed by the online subsystem
	FOnEndSessionCompleteDelegate Delegate;

	// Handle to the registered OnDestroySessionComplete delegate
	FDelegateHandle DelegateHandle;

	// The world context object in which this call is taking place
	UObject* WorldContextObject;
};
