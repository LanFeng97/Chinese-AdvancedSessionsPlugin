// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "BlueprintDataDefinitions.h"
#include "CreateSessionCallbackProxyAdvanced.generated.h"

UCLASS(MinimalAPI)
class UCreateSessionCallbackProxyAdvanced : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	// Called when the session was created successfully
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;

	/**
	 *    Creates a session with the default online subsystem with advanced optional inputs, for dedicated servers leave UsePresence as false and set IsDedicatedServer to true. Dedicated servers don't use presence.
	 *    @param PublicConnections	When doing a 'listen' server, this must be >=2 (ListenServer itself counts as a connection)
	 *    @param bUseLAN			When you want to play LAN, the level to play on must be loaded with option 'bIsLanMatch'
	 *    @param bUsePresence		Must be true for a 'listen' server (Map must be loaded with option 'listen'), false for a 'dedicated' server.
	 *	  @param bUseLobbiesIfAvailable Used to flag the subsystem to use a lobby api instead of general hosting if the API supports it, generally true on steam for listen servers and false for dedicated
	 *	  @param bShouldAdvertise	Set to true when the OnlineSubsystem should list your server when someone is searching for servers. Otherwise the server is hidden and only join via invite is possible.
	 *	  @param bUseLobbiesVoiceChatIfAvailable Set to true to setup voice chat lobbies if the API supports it
	 * 	  @param bStartAfterCreate Set to true to start the session after it's created. If false you need to manually call StartSession when ready.
	 */
	/**
	*  使用默认在线子系统创建一个带高级可选输入的会话。对于专用服务器，请将UsePresence设为false并把IsDedicatedServer设为true，专用服务器不使用Presence。
	*  @param PublicConnections	做“listen”服务器时该值必须>=2（ListenServer自身也算一个连接）
	*  @param bUseLAN			想进行局域网游戏时，所加载的地图必须带有“bIsLanMatch”选项
	*  @param bUsePresence		对“listen”服务器必须为true（地图需带“listen”选项加载）；对“dedicated”服务器为false
	*  @param bUseLobbiesIfAvailable	若API支持，标记子系统优先使用大厅（Lobby）API而非常规托管；Steam上做listen服务器时通常为true，专用服务器为false
	*  @param bShouldAdvertise	希望在线子系统在别人搜索服务器时列出你的服务器就设为true，否则服务器隐藏、只能通过邀请加入。
	*  @param bUseLobbiesVoiceChatIfAvailable	若API支持，设为true以搭建带语音聊天的大厅
	*  @param bStartAfterCreate	设为true以在会话创建后自动开始该会话；若为false，你需要在准备就绪后手动调用StartSession（开始会话）。
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "创建高级会话 (CreateAdvancedSession)", BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject",AutoCreateRefTerm="ExtraSettings"), Category = "Online|AdvancedSessions")
		static UCreateSessionCallbackProxyAdvanced* CreateAdvancedSession(UObject* WorldContextObject, const TArray<FSessionPropertyKeyPair>& ExtraSettings, class APlayerController* PlayerController = NULL, int32 PublicConnections = 100, int32 PrivateConnections = 0, bool bUseLAN = false, bool bAllowInvites = true, bool bIsDedicatedServer = false, bool bUsePresence = true, bool bUseLobbiesIfAvailable = true, bool bAllowJoinViaPresence = true, bool bAllowJoinViaPresenceFriendsOnly = false, bool bAntiCheatProtected = false, bool bUsesStats = false, bool bShouldAdvertise = true, bool bUseLobbiesVoiceChatIfAvailable = false, bool bStartAfterCreate = true);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;
	// End of UOnlineBlueprintCallProxyBase interface

private:
	// Internal callback when session creation completes, optionally calls StartSession
	void OnCreateCompleted(FName SessionName, bool bWasSuccessful);

	// Internal callback when session start completes
	void OnStartCompleted(FName SessionName, bool bWasSuccessful);

	// The player controller triggering things
	TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;

	// The delegate executed by the online subsystem
	FOnCreateSessionCompleteDelegate CreateCompleteDelegate;

	// The delegate executed by the online subsystem
	FOnStartSessionCompleteDelegate StartCompleteDelegate;

	// Handles to the registered delegates above
	FDelegateHandle CreateCompleteDelegateHandle;
	FDelegateHandle StartCompleteDelegateHandle;

	// Number of public connections
	int NumPublicConnections;

	// Number of private connections
	int NumPrivateConnections;

	// Whether or not to search LAN
	bool bUseLAN;

	// Whether or not to allow invites
	bool bAllowInvites;

	// Whether this is a dedicated server or not
	bool bDedicatedServer;

	// Whether to use the presence option
	bool bUsePresence;

	// Whether to prefer the use of lobbies for hosting if the api supports them
	bool bUseLobbiesIfAvailable;

	// Whether to allow joining via presence
	bool bAllowJoinViaPresence;

	// Allow joining via presence for friends only
	bool bAllowJoinViaPresenceFriendsOnly;

	// Delcare the server to be anti cheat protected
	bool bAntiCheatProtected;

	// Record Stats
	bool bUsesStats;

	// Should advertise server?
	bool bShouldAdvertise;

	// Whether to prefer the use of voice chat lobbies if the api supports them
	bool bUseLobbiesVoiceChatIfAvailable;

	// Whether to start the session automatically after it is created
	bool bStartAfterCreate;

	// Store extra settings
	TArray<FSessionPropertyKeyPair> ExtraSettings;

	// The world context object in which this call is taking place
	TWeakObjectPtr<UObject> WorldContextObject;
};

