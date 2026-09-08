// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "BlueprintDataDefinitions.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Online.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineUserInterface.h"
#include "Interfaces/OnlinePresenceInterface.h"
#include "Engine/GameInstance.h"
#include "Engine/LocalPlayer.h"

#include "UObject/UObjectIterator.h"

#include "AdvancedIdentityLibrary.generated.h"


//General Advanced Sessions Log
DECLARE_LOG_CATEGORY_EXTERN(AdvancedIdentityLog, Log, All);

UCLASS()
class UAdvancedIdentityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//********* Identity Functions *************//

	// Get the login status of a local player
	// 获取本地玩家的登录状态
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedIdentity", meta = (DisplayName = "获取登录状态 (GetLoginStatus)", ExpandEnumAsExecs = "Result"))
	static void GetLoginStatus(const FBPUniqueNetId & UniqueNetID, EBPLoginStatus & LoginStatus, EBlueprintResultSwitch &Result);

	// Get the auth token for a local player
	// 获取本地玩家的身份验证令牌（AuthToken）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedIdentity", meta = (DisplayName = "获取玩家身份验证令牌 (GetPlayerAuthToken)", ExpandEnumAsExecs = "Result"))
	static void GetPlayerAuthToken(APlayerController * PlayerController, FString & AuthToken, EBlueprintResultSwitch &Result);

	// Get a players nickname
	// 获取玩家的昵称
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedIdentity", meta = (DisplayName = "获取玩家昵称 (GetPlayerNickname)"))
	static void GetPlayerNickname(const FBPUniqueNetId & UniqueNetID, FString & PlayerNickname);

	//********* User Account Functions *************//

	// Get a users account
	// 获取用户账号
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedIdentity|UserAccount", meta = (DisplayName = "获取用户账号 (GetUserAccount)", ExpandEnumAsExecs = "Result"))
	static void GetUserAccount(const FBPUniqueNetId & UniqueNetId, FBPUserOnlineAccount & AccountInfo, EBlueprintResultSwitch &Result);

	// Get all known users accounts
	// 获取所有已知的用户账号
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedIdentity|UserAccount", meta = (DisplayName = "获取所有用户账号 (GetAllUserAccounts)", ExpandEnumAsExecs = "Result"))
	static void GetAllUserAccounts(TArray<FBPUserOnlineAccount> & AccountInfos, EBlueprintResultSwitch &Result);

	// Get a user account access token
	// 获取用户账号的访问令牌（AccessToken）
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedIdentity|UserAccount", meta = (DisplayName = "获取用户账号访问令牌 (GetUserAccountAccessToken)"))
	static void GetUserAccountAccessToken(const FBPUserOnlineAccount & AccountInfo, FString & AccessToken);

	// Get a user account Auth attribute (depends on subsystem)
	// 获取用户账号的Auth属性（取决于子系统）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedIdentity|UserAccount", meta = (DisplayName = "获取用户账号Auth属性 (GetUserAccountAuthAttribute)", ExpandEnumAsExecs = "Result"))
	static void GetUserAccountAuthAttribute(const FBPUserOnlineAccount & AccountInfo, const FString & AttributeName, FString & AuthAttribute, EBlueprintResultSwitch &Result);

	// Set a user account attribute (depends on subsystem)
	// 设置用户账号属性（取决于子系统）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedIdentity|UserAccount", meta = (DisplayName = "设置用户账号属性 (SetUserAccountAttribute)", ExpandEnumAsExecs = "Result"))
	static void SetUserAccountAttribute(const FBPUserOnlineAccount & AccountInfo, const FString & AttributeName, const FString & NewAttributeValue, EBlueprintResultSwitch &Result);

	// Get user ID
	// 获取用户ID
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedIdentity|UserAccount", meta = (DisplayName = "获取用户ID (GetUserID)"))
	static void GetUserID(const FBPUserOnlineAccount & AccountInfo, FBPUniqueNetId & UniqueNetID);

	// Get user accounts real name if possible
	// 尽可能获取用户账号的真实姓名
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedIdentity|UserAccount", meta = (DisplayName = "获取用户账号真实姓名 (GetUserAccountRealName)"))
	static void GetUserAccountRealName(const FBPUserOnlineAccount & AccountInfo, FString & UserName);

	// Get user account display name if possible
	// 尽可能获取用户账号的显示名称
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedIdentity|UserAccount", meta = (DisplayName = "获取用户账号显示名称 (GetUserAccountDisplayName)"))
	static void GetUserAccountDisplayName(const FBPUserOnlineAccount & AccountInfo, FString & DisplayName);

	// Get user account attribute (depends on subsystem)
	// 获取用户账号属性（取决于子系统）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedIdentity|UserAccount", meta = (DisplayName = "获取用户账号属性 (GetUserAccountAttribute)", ExpandEnumAsExecs = "Result"))
	static void GetUserAccountAttribute(const FBPUserOnlineAccount & AccountInfo, const FString & AttributeName, FString & AttributeValue, EBlueprintResultSwitch &Result);


};	
