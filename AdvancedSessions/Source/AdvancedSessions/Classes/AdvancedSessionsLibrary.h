// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "BlueprintDataDefinitions.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Online.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlineUserInterface.h"
#include "Interfaces/OnlineMessageInterface.h"
#include "Interfaces/OnlinePresenceInterface.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameSession.h"

//#include "UObjectIterator.h"

#include "AdvancedSessionsLibrary.generated.h"


//General Advanced Sessions Log
DECLARE_LOG_CATEGORY_EXTERN(AdvancedSessionsLog, Log, All);


UCLASS()
class UAdvancedSessionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		//********* Session Admin Functions *************//	

		// Kick a player from the currently active game session, only available on the server
		// 将玩家从当前激活的游戏会话中踢出，仅服务器端可用
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions", meta = (DisplayName = "踢出玩家 (KickPlayer)", WorldContext = "WorldContextObject"))
		static bool KickPlayer(UObject* WorldContextObject, APlayerController* PlayerToKick, FText KickReason);

		// Ban a player from the currently active game session, only available on the server
		// Note that the default gamesession class does not implement an actual ban list and just kicks when this is called
		// 封禁当前激活游戏会话中的玩家，仅服务器端可用
		// 注意：默认的GameSession类并未实现真正的封禁列表，调用时只会把玩家踢出
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions", meta = (DisplayName = "封禁玩家 (BanPlayer)", WorldContext = "WorldContextObject"))
		static bool BanPlayer(UObject* WorldContextObject, APlayerController* PlayerToBan, FText BanReason);

		//********* Session Search Functions *************//	

		// Adds or modifies session settings in an existing array depending on if they exist already or not
		// 根据这些设置是否已存在，在现有数组中添加或修改会话设置
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "添加或修改额外会话设置 (AddOrModifyExtraSettings)"))
		static void AddOrModifyExtraSettings(UPARAM(ref)  TArray<FSessionPropertyKeyPair> & SettingsArray, UPARAM(ref)  TArray<FSessionPropertyKeyPair> & NewOrChangedSettings, TArray<FSessionPropertyKeyPair> & ModifiedSettingsArray);

		// Get an array of the session settings from a session search result
		// 从会话搜索结果中获取会话设置数组
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取额外会话设置 (GetExtraSettings)"))
		static void GetExtraSettings(FBlueprintSessionResult SessionResult, TArray<FSessionPropertyKeyPair> & ExtraSettings);

		// Get the current session state
		// 获取当前会话状态
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取会话状态 (GetSessionState)", WorldContext = "WorldContextObject"))
		static void GetSessionState(UObject* WorldContextObject, EBPOnlineSessionState &SessionState);

		// Get the current session settings
		// 获取当前会话设置
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取会话设置 (GetSessionSettings)", ExpandEnumAsExecs = "Result", WorldContext = "WorldContextObject"))
		static void GetSessionSettings(UObject* WorldContextObject, int32 &NumConnections, int32 &NumPrivateConnections, bool &bIsLAN, bool &bIsDedicated, bool &bAllowInvites, bool &bAllowJoinInProgress, bool &bIsAnticheatEnabled, int32 &BuildUniqueID, TArray<FSessionPropertyKeyPair> &ExtraSettings, EBlueprintResultSwitch &Result);

		// Check if someone is in the current session
		// 检查某人是否在当前会话中
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "玩家是否在会话中 (IsPlayerInSession)", WorldContext = "WorldContextObject"))
		static void IsPlayerInSession(UObject* WorldContextObject, const FBPUniqueNetId &PlayerToCheck, bool &bIsInSession);
		
		// Make a literal session search parameter
		// 创建一个会话搜索参数字面量
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|SessionInfo|Literals", meta = (DisplayName = "创建会话搜索属性字面量 (MakeLiteralSessionSearchProperty)"))
		static FSessionsSearchSetting MakeLiteralSessionSearchProperty(FSessionPropertyKeyPair SessionSearchProperty, EOnlineComparisonOpRedux ComparisonOp);


		//********* Session Information Functions ***********//

		// Check if a session result is valid or not
		// 检查会话结果是否有效
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "会话结果是否有效 (IsValidSession)"))
		static bool IsValidSession(const FBlueprintSessionResult & SessionResult);

		// Get a string copy of a session ID
		// 获取会话ID的字符串副本
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取会话ID字符串 (GetSessionID_AsString)"))
		static void GetSessionID_AsString(const FBlueprintSessionResult & SessionResult, FString& SessionID);

		// Get a string copy of the current session ID
		// 获取当前会话ID的字符串副本
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取当前会话ID字符串 (GetCurrentSessionID_AsString)", WorldContext = "WorldContextObject"))
		static void GetCurrentSessionID_AsString(UObject* WorldContextObject, FString& SessionID);

		// Get the Unique Current Build ID
		// 获取当前唯一的构建ID
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取当前唯一构建ID (GetCurrentUniqueBuildID)"))
		static void GetCurrentUniqueBuildID(int32 &UniqueBuildId);
		
		// Get the Unique Build ID from a session search result
		// 从会话搜索结果中获取唯一构建ID
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取唯一构建ID (GetUniqueBuildID)"))
		static void GetUniqueBuildID(FBlueprintSessionResult SessionResult, int32 &UniqueBuildId);
		
		
		// Thanks CriErr for submission


		// Get session property Key Name value
		// 获取会话属性的键名（Key Name）值
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取会话属性键名 (GetSessionPropertyKey)"))
		static FName GetSessionPropertyKey(const FSessionPropertyKeyPair& SessionProperty);
		
		// Find session property by Name
		// 按名称在会话属性数组中查找属性
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "按名称查找会话属性 (FindSessionPropertyByName)", ExpandEnumAsExecs = "Result"))
		static void FindSessionPropertyByName(const TArray<FSessionPropertyKeyPair>& ExtraSettings, FName SettingsName, EBlueprintResultSwitch &Result, FSessionPropertyKeyPair& OutProperty);
		
		// Find session property index by Name
		// 按名称在会话属性数组中查找属性的索引
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "按名称查找会话属性索引 (FindSessionPropertyIndexByName)", ExpandEnumAsExecs = "Result"))
		static void FindSessionPropertyIndexByName(const TArray<FSessionPropertyKeyPair>& ExtraSettings, FName SettingName, EBlueprintResultSwitch &Result, int32& OutIndex);

		/// Removed the Index_None part of the last function, that isn't accessible in blueprint, better to return success/failure
		// End Thanks CriErr :p

		// Get session custom information key/value as Byte (For Enums)
		// 将会话自定义信息键值作为字节（Byte，用于枚举）读取
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取会话属性字节值 (GetSessionPropertyByte)", ExpandEnumAsExecs = "SearchResult"))
		static void GetSessionPropertyByte(const TArray<FSessionPropertyKeyPair> & ExtraSettings, FName SettingName, ESessionSettingSearchResult &SearchResult, uint8 &SettingValue);

		// Get session custom information key/value as Bool
		// Steam only currently supports Int,Float,String,BYTE values for search filtering!!!
		// 将会话自定义信息键值作为布尔值（Bool）读取
		// Steam目前仅支持Int、Float、String、BYTE类型的值用于搜索过滤！！！
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取会话属性布尔值 (GetSessionPropertyBool)", ExpandEnumAsExecs = "SearchResult"))
		static void GetSessionPropertyBool(const TArray<FSessionPropertyKeyPair> & ExtraSettings, FName SettingName, ESessionSettingSearchResult &SearchResult, bool &SettingValue);

		// Get session custom information key/value as String
		// 将会话自定义信息键值作为字符串（String）读取
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取会话属性字符串值 (GetSessionPropertyString)", ExpandEnumAsExecs = "SearchResult"))
		static void GetSessionPropertyString(const TArray<FSessionPropertyKeyPair> & ExtraSettings, FName SettingName, ESessionSettingSearchResult &SearchResult, FString &SettingValue);

		// Get session custom information key/value as Int
		// 将会话自定义信息键值作为整数（Int）读取
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取会话属性整数值 (GetSessionPropertyInt)", ExpandEnumAsExecs = "SearchResult"))
		static void GetSessionPropertyInt(const TArray<FSessionPropertyKeyPair> & ExtraSettings, FName SettingName, ESessionSettingSearchResult &SearchResult, int32 &SettingValue);

		// Get session custom information key/value as Float
		// 将会话自定义信息键值作为浮点数（Float）读取
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|SessionInfo", meta = (DisplayName = "获取会话属性浮点值 (GetSessionPropertyFloat)", ExpandEnumAsExecs = "SearchResult"))
		static void GetSessionPropertyFloat(const TArray<FSessionPropertyKeyPair> & ExtraSettings, FName SettingName, ESessionSettingSearchResult &SearchResult, float &SettingValue);


		// Make a literal session custom information key/value pair from Byte (For Enums)
		// 用字节（Byte，用于枚举）创建会话自定义信息键值对字面量
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|SessionInfo|Literals", meta = (DisplayName = "创建会话属性字节字面量 (MakeLiteralSessionPropertyByte)"))
		static FSessionPropertyKeyPair MakeLiteralSessionPropertyByte(FName Key, uint8 Value);

		// Make a literal session custom information key/value pair from Bool
		// Steam only currently supports Int,Float,String,BYTE values for search filtering!
		// 用布尔值（Bool）创建会话自定义信息键值对字面量
		// Steam目前仅支持Int、Float、String、BYTE类型的值用于搜索过滤！
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|SessionInfo|Literals", meta = (DisplayName = "创建会话属性布尔字面量 (MakeLiteralSessionPropertyBool)"))
		static FSessionPropertyKeyPair MakeLiteralSessionPropertyBool(FName Key, bool Value);

		// Make a literal session custom information key/value pair from String
		// 用字符串（String）创建会话自定义信息键值对字面量
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|SessionInfo|Literals", meta = (DisplayName = "创建会话属性字符串字面量 (MakeLiteralSessionPropertyString)"))
		static FSessionPropertyKeyPair MakeLiteralSessionPropertyString(FName Key, FString Value);

		// Make a literal session custom information key/value pair from Int
		// 用整数（Int）创建会话自定义信息键值对字面量
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|SessionInfo|Literals", meta = (DisplayName = "创建会话属性整数字面量 (MakeLiteralSessionPropertyInt)"))
		static FSessionPropertyKeyPair MakeLiteralSessionPropertyInt(FName Key, int32 Value);

		// Make a literal session custom information key/value pair from Float
		// 用浮点数（Float）创建会话自定义信息键值对字面量
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|SessionInfo|Literals", meta = (DisplayName = "创建会话属性浮点字面量 (MakeLiteralSessionPropertyFloat)"))
		static FSessionPropertyKeyPair MakeLiteralSessionPropertyFloat(FName Key, float Value);


		//******* Player ID functions *********//

		// Get the unique net id of a network player attached to the given controller
		// 获取绑定到指定Controller的网络玩家的唯一网络ID
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|PlayerInfo|PlayerID", meta = (DisplayName = "获取唯一网络ID (GetUniqueNetID)"))
		static void GetUniqueNetID(APlayerController *PlayerController, FBPUniqueNetId &UniqueNetId);

		// Get the unique net id of a network player attached to the given controller
		// 获取指定会话的所有者（Session Owner）的唯一网络ID（注意：上方英文原注释与函数实现不符，疑似复制粘贴笔误）
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|PlayerInfo|PlayerID", meta = (DisplayName = "获取会话所有者的唯一网络ID (GetUniqueNetIdOfSessionOwner)"))
		static void GetUniqueNetIdOfSessionOwner(FBlueprintSessionResult SessionResult, FBPUniqueNetId& UniqueNetId);

		// Get the unique net id of a network player who is assigned the the given player state
		// 获取分配给指定PlayerState的网络玩家的唯一网络ID
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|PlayerInfo|PlayerID", meta = (DisplayName = "从PlayerState获取唯一网络ID (GetUniqueNetIDFromPlayerState)"))
		static void GetUniqueNetIDFromPlayerState(APlayerState *PlayerState, FBPUniqueNetId &UniqueNetId);
		
		// Return True if Unique Net ID is valid
		// 若唯一网络ID有效则返回True
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|PlayerInfo|PlayerID", meta = (DisplayName = "唯一网络ID是否有效 (IsValidUniqueNetID)"))
		static bool IsValidUniqueNetID(const FBPUniqueNetId &UniqueNetId);

		/* Returns true if the values are equal (A == B) */
		// 若两个值相等（A == B）则返回true
		UFUNCTION(BlueprintPure, meta = (DisplayName = "唯一网络ID是否相等 (Equal Unique Net ID)", CompactNodeTitle = "==", Keywords = "== equal"), Category = "Online|AdvancedSessions|PlayerInfo|PlayerID")
		static bool EqualEqual_UNetIDUnetID(const FBPUniqueNetId &A, const FBPUniqueNetId &B);

		// Check if a UniqueNetId is a friend
		// 将UniqueNetId转换为字符串（注意：上方英文原注释与函数实现不符，疑似复制粘贴笔误）
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|UniqueNetId", meta = (DisplayName = "唯一网络ID转字符串 (UniqueNetIdToString)"))
		static void UniqueNetIdToString(const FBPUniqueNetId &UniqueNetId, FString &String);

		//******** Player Name Functions **********//

		// Get the player name of a network player attached to the given controller
		// 获取绑定到指定Controller的网络玩家的玩家名称
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|PlayerInfo|PlayerName", meta = (DisplayName = "获取玩家名称 (GetPlayerName)"))
		static void GetPlayerName(APlayerController *PlayerController, FString &PlayerName);

		// Set the player name of a network player attached to the given controller
		// 设置绑定到指定Controller的网络玩家的玩家名称
		UFUNCTION(BlueprintCallable, Category = "Online|AdvancedSessions|PlayerInfo|PlayerName", meta = (DisplayName = "设置玩家名称 (SetPlayerName)"))
		static void SetPlayerName(APlayerController *PlayerController, FString PlayerName);

		//********** Misc Player Info Functions *********//

		// Get the number of network players
		// 获取网络玩家数量
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|PlayerInfo|Misc", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", DisplayName = "获取网络玩家数量 (GetNumNetworkPlayers)"))
		static void GetNumberOfNetworkPlayers(UObject* WorldContextObject, int32 &NumNetPlayers);

		// Get the network player index of the given controller
		// 获取指定Controller的网络玩家索引
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|PlayerInfo|Misc", meta = (DisplayName = "获取网络玩家索引 (GetNetPlayerIndex)"))
		static void GetNetPlayerIndex(APlayerController *PlayerController, int32 &NetPlayerIndex);

		// Checks if the stated session subsystem is active
		// 检查指定的会话子系统是否处于激活状态
		UFUNCTION(BlueprintPure, Category = "Online|AdvancedSessions|Misc", meta = (DisplayName = "是否存在在线子系统 (HasOnlineSubsystem)"))
		static bool HasOnlineSubsystem(FName SubSystemName);
		
		//**** Seamless travel Functions ****//
		
		//Exposes Server travel to blueprint
		// 向蓝图暴露服务器切换关卡（Server Travel）功能
		UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Online|AdvancedSessions|Seamless", meta = (DisplayName = "服务器切换关卡 (ServerTravel)", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
		static bool ServerTravel(UObject* WorldContextObject, const FString& InURL, bool bAbsolute, bool bShouldSkipGameNotify);

		
};	
