// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "BlueprintDataDefinitions.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Engine/LocalPlayer.h"
#include "AutoLoginUserCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UAutoLoginUserCallbackProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	// Called when there is a successful destroy
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	// Called when there is an unsuccessful destroy
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/**
	 * Logs the player into the online service using parameters passed on the
	 * command line. Expects -AUTH_LOGIN=<UserName> -AUTH_PASSWORD=<password>. If either
	 * are missing, the function returns false and doesn't start the login
	 * process
	 *
	 * @param LocalUserNum the controller number of the associated user
	 *
	 */
	/**
	 *  使用命令行传入的参数将玩家登录到在线服务。期望 -AUTH_LOGIN=<用户名> -AUTH_PASSWORD=<密码>。
	 *  若任一参数缺失，本函数返回false且不会启动登录流程。
	 *  @param LocalUserNum 关联用户的控制器编号
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "自动登录用户 (AutoLoginUser)", BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject"), Category = "Online|AdvancedIdentity")
	static UAutoLoginUserCallbackProxy* AutoLoginUser(UObject* WorldContextObject, int32 LocalUserNum);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// Internal callback when the operation completes, calls out to the public success/failure callbacks
	void OnCompleted(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& ErrorVal);

private:
	// The controller number of the associated user
	int32 LocalUserNumber;

	// The delegate executed by the online subsystem
	FOnLoginCompleteDelegate Delegate;

	// Handle to the registered OnDestroySessionComplete delegate
	FDelegateHandle DelegateHandle;

	// The world context object in which this call is taking place
	UObject* WorldContextObject;
};
