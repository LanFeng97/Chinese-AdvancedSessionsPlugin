// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintDataDefinitions.h"
#include "Online.h"
#include "OnlineSubsystem.h"
#include "Interfaces/VoiceInterface.h"
//#include "OnlineFriendsInterface.h"
//#include "OnlineUserInterface.h"
//#include "OnlineMessageInterface.h"
//#include "OnlinePresenceInterface.h"
#include "Engine/GameInstance.h"
//#include "OnlineSessionInterface.h"

#include "UObject/UObjectIterator.h"

#include "AdvancedVoiceLibrary.generated.h"


//General Advanced Sessions Log
DECLARE_LOG_CATEGORY_EXTERN(AdvancedVoiceLog, Log, All);


UCLASS()
class UAdvancedVoiceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	//********* Voice Library Functions *************//

	// Get if a headset is present for the specified local user
	// 检查指定本地用户是否佩戴了耳机（头戴设备）
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedVoice|VoiceInfo", meta = (DisplayName = "是否佩戴耳机 (IsHeadsetPresent)"))
	static void IsHeadsetPresent(bool & bHasHeadset, uint8 LocalPlayerNum = 0);

	// Starts networked voice, allows push to talk in coordination with StopNetworkedVoice
	// 开始网络语音；与StopNetworkedVoice配合可实现按键说话（Push to Talk）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedVoice", meta = (DisplayName = "开始网络语音 (StartNetworkedVoice)"))
	static void StartNetworkedVoice(uint8 LocalPlayerNum = 0);

	// Stops networked voice, allows push to talk in coordination with StartNetworkedVoice
	// 停止网络语音；与StartNetworkedVoice配合可实现按键说话（Push to Talk）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedVoice", meta = (DisplayName = "停止网络语音 (StopNetworkedVoice)"))
	static void StopNetworkedVoice(uint8 LocalPlayerNum = 0);

	// Registers a local player as someone interested in voice data
	// 将本地玩家注册为语音数据的感兴趣者（本地讲话者）
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedVoice", meta = (DisplayName = "注册本地讲话者 (RegisterLocalTalker)"))
	static bool RegisterLocalTalker(uint8 LocalPlayerNum = 0);

	// Registers all signed in players as local talkers
	// This is already done automatically, only do it manually if you unregistered someone
	// 将所有已登录玩家注册为本地讲话者
	// 此操作默认已自动完成，仅当你手动注销了某人才需要手动调用
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedVoice", meta = (DisplayName = "注册所有本地讲话者 (RegisterAllLocalTalkers)"))
	static void RegisterAllLocalTalkers();

	// UnRegisters local player as a local talker
	// 将本地玩家注销为本地讲话者
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedVoice", meta = (DisplayName = "注销本地讲话者 (UnRegisterLocalTalker)"))
	static void UnRegisterLocalTalker(uint8 LocalPlayerNum = 0);

	// UnRegisters all signed in players as local talkers
	// 将所有已登录玩家注销为本地讲话者
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedVoice", meta = (DisplayName = "注销所有本地讲话者 (UnRegisterAllLocalTalkers)"))
	static void UnRegisterAllLocalTalkers();

	// Registers a remote player as a talker
	// This is already done automatically, only do it manually if you unregistered someone
	// 将远程玩家注册为讲话者
	// 此操作默认已自动完成，仅当你手动注销了某人才需要手动调用
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedVoice", meta = (DisplayName = "注册远程讲话者 (RegisterRemoteTalker)"))
	static bool RegisterRemoteTalker(const FBPUniqueNetId& UniqueNetId);

	// UnRegisters a remote player as a talker
	// 将远程玩家注销为讲话者
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedVoice", meta = (DisplayName = "注销远程讲话者 (UnRegisterRemoteTalker)"))
	static bool UnRegisterRemoteTalker(const FBPUniqueNetId& UniqueNetId);

	// UnRegisters all remote players as talkers
	// 将所有远程玩家注销为讲话者
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedVoice", meta = (DisplayName = "移除所有远程讲话者 (RemoveAllRemoteTalkers)"))
	static void RemoveAllRemoteTalkers();

	// Returns whether a local player is currently talking
	// 返回本地玩家当前是否正在说话
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedVoice|VoiceInfo", meta = (DisplayName = "本地玩家是否正在说话 (IsLocalPlayerTalking)"))
	static bool IsLocalPlayerTalking(uint8 LocalPlayerNum);

	// Returns whether a remote player is currently talking
	// 返回远程玩家当前是否正在说话
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedVoice|VoiceInfo", meta = (DisplayName = "远程玩家是否正在说话 (IsRemotePlayerTalking)"))
	static bool IsRemotePlayerTalking(const FBPUniqueNetId& UniqueNetId);

	// Returns whether a player is muted for the specified local player
	// 返回某玩家对指定本地玩家是否处于静音状态
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedVoice|VoiceInfo", meta = (DisplayName = "玩家是否被静音 (IsPlayerMuted)"))
	static bool IsPlayerMuted(uint8 LocalUserNumChecking, const FBPUniqueNetId& UniqueNetId);

	// Mutes the player associated with the uniquenetid for the specified local player, if IsSystemWide is true then it will attempt to mute globally for the player
	// 将UniqueNetId对应的玩家对指定本地玩家静音；若IsSystemWide为true则尝试对该玩家全局静音
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedVoice", meta = (DisplayName = "静音远程讲话者 (MuteRemoteTalker)"))
	static bool MuteRemoteTalker(uint8 LocalUserNum, const FBPUniqueNetId& UniqueNetId, bool bIsSystemWide = false);

	// UnMutes the player associated with the uniquenetid for the specified local player, if IsSystemWide is true then it will attempt to unmute globally for the player
	// 取消UniqueNetId对应的玩家对指定本地玩家的静音；若IsSystemWide为true则尝试对该玩家全局取消静音
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedVoice", meta = (DisplayName = "取消静音远程讲话者 (UnMuteRemoteTalker)"))
	static bool UnMuteRemoteTalker(uint8 LocalUserNum, const FBPUniqueNetId& UniqueNetId, bool bIsSystemWide = false);

	// Gets the number of local talkers for this system
	// 获取本系统的本地讲话者数量
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedVoice|VoiceInfo", meta = (DisplayName = "获取本地讲话者数量 (GetNumLocalTalkers)"))
	static void GetNumLocalTalkers(int32 & NumLocalTalkers);
};	
