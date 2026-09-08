#pragma once

#include "CoreMinimal.h"
#include "BlueprintDataDefinitions.h"
#include "StartSessionCallbackProxyAdvanced.generated.h"

UCLASS(MinimalAPI)
class UStartSessionCallbackProxyAdvanced : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()
	// Called when the session starts successfully
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	// Called when there is an error starting the session
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/**
	 * Starts a session with the default online subsystem. The session needs to be previously created by calling the "CreateAdvancedSession" node.
	 * @param WorldContextObject
	 */
	/**
	 *  使用默认在线子系统开始一个会话。该会话需先通过“创建高级会话（CreateAdvancedSession）”节点创建。
	 *  @param WorldContextObject
	 */
	UFUNCTION(
		BlueprintCallable
		, meta=(DisplayName = "开始高级会话 (StartAdvancedSession)", BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject")
		, Category = "Online|AdvancedSessions"
	)
	static UStartSessionCallbackProxyAdvanced* StartAdvancedSession(const UObject* WorldContextObject);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// Internal callback when session start completes
	void OnStartCompleted(FName SessionName, bool bWasSuccessful);

	// The delegate executed by the online subsystem
	FOnStartSessionCompleteDelegate StartCompleteDelegate;

	// Handles to the registered delegates above
	FDelegateHandle StartCompleteDelegateHandle;

	// The world context object in which this call is taking place
	const UObject* WorldContextObject;
};
