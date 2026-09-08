// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "BlueprintDataDefinitions.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Online.h"
#include "Engine/LocalPlayer.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlineUserInterface.h"
#include "Interfaces/OnlineMessageInterface.h"
#include "Interfaces/OnlinePresenceInterface.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "UObject/UObjectIterator.h"

#include "AdvancedFriendsLibrary.generated.h"


//General Advanced Sessions Log
DECLARE_LOG_CATEGORY_EXTERN(AdvancedFriendsLog, Log, All);

UCLASS()
class UAdvancedFriendsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	//********* Friend List Functions *************//

	// Sends an Invite to the current online session to a list of friends
	// 向当前在线会话中的一组好友发送邀请
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedFriends|FriendsList", meta = (DisplayName = "向好友发送会话邀请 (SendSessionInviteToFriends)", ExpandEnumAsExecs = "Result"))
	static void SendSessionInviteToFriends(APlayerController *PlayerController, const TArray<FBPUniqueNetId> &Friends, EBlueprintResultSwitch &Result);

	// Sends an Invite to the current online session to a friend
	// 向当前在线会话中的一位好友发送邀请
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedFriends|FriendsList", meta = (DisplayName = "向好友发送会话邀请 (SendSessionInviteToFriend)", ExpandEnumAsExecs = "Result"))
	static void SendSessionInviteToFriend(APlayerController *PlayerController, const FBPUniqueNetId &FriendUniqueNetId, EBlueprintResultSwitch &Result);

	// Get a friend from the previously read/saved friends list (Must Call GetFriends first for this to return anything)
	// 从先前读取/保存的好友列表中获取一位好友（必须先调用GetFriends才会返回内容）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedFriends|FriendsList", meta = (DisplayName = "获取好友 (GetFriend)"))
	static void GetFriend(APlayerController *PlayerController, const FBPUniqueNetId FriendUniqueNetId, FBPFriendInfo &Friend);

	// Get the previously read/saved friends list (Must Call GetFriends first for this to return anything)
	// 获取先前读取/保存的好友列表（必须先调用GetFriends才会返回内容）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedFriends|FriendsList", meta = (DisplayName = "获取已保存的好友列表 (GetStoredFriendsList)"))
	static void GetStoredFriendsList(APlayerController *PlayerController, TArray<FBPFriendInfo> &FriendsList);

	// Get the previously read/saved recent players list (Must Call GetRecentPlayers first for this to return anything)
	// 获取先前读取/保存的最近玩家列表（必须先调用GetRecentPlayers才会返回内容）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedFriends|RecentPlayersList", meta = (DisplayName = "获取已保存的最近玩家列表 (GetStoredRecentPlayersList)"))
	static void GetStoredRecentPlayersList(FBPUniqueNetId UniqueNetId, TArray<FBPOnlineRecentPlayer> &PlayersList);

	// Check if a UniqueNetId is a friend
	// 检查某个UniqueNetId是否为好友
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedFriends|FriendsList", meta = (DisplayName = "是否为好友 (IsAFriend)"))
	static void IsAFriend(APlayerController *PlayerController, const FBPUniqueNetId UniqueNetId, bool &IsFriend);
};	
