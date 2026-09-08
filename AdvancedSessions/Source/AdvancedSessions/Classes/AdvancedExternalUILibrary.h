// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "BlueprintDataDefinitions.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Online.h"
#include "Engine/LocalPlayer.h"
#include "OnlineSubsystem.h"
#include "BlueprintDataDefinitions.h"
//#include "OnlineFriendsInterface.h"
//#include "OnlineUserInterface.h"
//#include "OnlineMessageInterface.h"
//#include "OnlinePresenceInterface.h"
//#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"

//#include "UObjectIterator.h"

#include "AdvancedExternalUILibrary.generated.h"


//General Advanced Sessions Log
DECLARE_LOG_CATEGORY_EXTERN(AdvancedExternalUILog, Log, All);

UCLASS()
class UAdvancedExternalUILibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	//********* External UI Functions *************//

	// Show the UI that handles the Friends list
	// 显示用于处理好友列表的界面
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedExternalUI", meta = (DisplayName = "显示好友列表界面 (ShowFriendsUI)", ExpandEnumAsExecs = "Result", WorldContext = "WorldContextObject"))
	static void ShowFriendsUI(UObject* WorldContextObject, APlayerController *PlayerController, EBlueprintResultSwitch &Result);

	// Show the UI that handles inviting people to your game
	// 显示用于邀请他人加入你游戏的界面
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedExternalUI", meta = (DisplayName = "显示邀请界面 (ShowInviteUI)", ExpandEnumAsExecs = "Result", WorldContext = "WorldContextObject"))
	static void ShowInviteUI(UObject* WorldContextObject, APlayerController *PlayerController, EBlueprintResultSwitch &Result);

	// Show the UI that shows the leaderboard (doesn't work with steam)
	// 显示排行榜界面（Steam平台不可用）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedExternalUI", meta = (DisplayName = "显示排行榜界面 (ShowLeaderBoardUI)", ExpandEnumAsExecs = "Result", WorldContext = "WorldContextObject"))
	static void ShowLeaderBoardUI(UObject* WorldContextObject, FString LeaderboardName, EBlueprintResultSwitch &Result);

	// Show the UI that shows a web URL
	// 显示用于展示网页URL的界面
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedExternalUI", meta = (DisplayName = "显示网页URL界面 (ShowWebURLUI)", ExpandEnumAsExecs = "Result", AutoCreateRefTerm = "AllowedDomains", WorldContext = "WorldContextObject"))
	static void ShowWebURLUI(UObject* WorldContextObject, FString URLToShow, EBlueprintResultSwitch &Result, TArray<FString>& AllowedDomains, bool bEmbedded = false , bool bShowBackground = false, bool bShowCloseButton = false, int32 OffsetX = 0, int32 OffsetY = 0, int32 SizeX = 0, int32 SizeY = 0);

	// Show the UI that shows a web URL
	// 关闭用于展示网页URL的界面
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedExternalUI", meta = (DisplayName = "关闭网页URL界面 (CloseWebURLUI)", WorldContext = "WorldContextObject"))
	static void CloseWebURLUI(UObject* WorldContextObject);


	// Show the UI that shows the profile of a uniquenetid
	// 显示指定唯一网络ID（UniqueNetId）玩家的资料界面
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedExternalUI", meta = (DisplayName = "显示玩家资料界面 (ShowProfileUI)", ExpandEnumAsExecs = "Result", WorldContext = "WorldContextObject"))
	static void ShowProfileUI(UObject* WorldContextObject, const FBPUniqueNetId PlayerViewingProfile, const FBPUniqueNetId PlayerToViewProfileOf, EBlueprintResultSwitch &Result);

	// Show the UI that shows the account upgrade UI (doesn't work with steam)
	// 显示账号升级界面（Steam平台不可用）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedExternalUI", meta = (DisplayName = "显示账号升级界面 (ShowAccountUpgradeUI)", ExpandEnumAsExecs = "Result", WorldContext = "WorldContextObject"))
	static void ShowAccountUpgradeUI(UObject* WorldContextObject, const FBPUniqueNetId PlayerRequestingAccountUpgradeUI, EBlueprintResultSwitch &Result);

};	
