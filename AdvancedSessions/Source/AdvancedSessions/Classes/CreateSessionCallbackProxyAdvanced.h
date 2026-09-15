// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
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
	 *	  @param bUseLobbiesIfAvailable Used to flag the subsystem to use a lobby api instead of general hosting if the API supports it, generally true on steam for listen servers and false for dedicated
	 *	Must be true for a 'listen' server (Map must be loaded with option 'listen'), false for a 'dedicated' server.
	 *	  @param bShouldAdvertise	Set to true when the OnlineSubsystem should list your server when someone is searching for servers. Otherwise the server is hidden and only join via invite is possible.
	 *	  @param bUseLobbiesVoiceChatIfAvailable Set to true to setup voice chat lobbies if the API supports it
	 * 	  @param bStartAfterCreate Set to true to start the session after it's created. If false you need to manually call StartSession when ready.
	 */
	/**
	 *  已停用参数（上游原注释）：bool bUsePresence = true,
	 *  使用默认在线子系统创建一个带高级可选输入的会话。对于专用服务器，请将UsePresence设为false并把IsDedicatedServer设为true，专用服务器不使用Presence。
	 *  [相对5.4] 5.5起上游已注释停用bUsePresence参数（蓝图中不再显示该输入，行为按旧默认true处理）
	 *  @param PublicConnections 做“listen”服务器时该值必须>=2（ListenServer自身也算一个连接）
	 *  @param bUseLAN 是否使用局域网(LAN)。勾选后只在局域网内创建房间；联机测试或同网段直连时使用，走公网在线子系统时请取消勾选。
	 *  @param bUseLobbiesIfAvailable 是否优先使用大厅(Lobby)API来托管房间（在支持的子系统上，如Steam）。Steam的Listen Server通常勾选；专用服务器一般取消。
	 *  @param bShouldAdvertise 是否把房间广播到服务器列表供他人搜索；取消勾选后搜索不到，只能通过邀请加入。
	 *  @param bUseLobbiesVoiceChatIfAvailable 是否在支持时启用大厅语音聊天(Lobby Voice Chat)。
	 *  @param bStartAfterCreate 创建会话后是否自动开始会话。取消勾选后需要在准备就绪时手动调用StartAdvancedSession(开始高级会话)，否则房间不会进入可加入的进行中状态。
	 *  @param bAllowInvites 是否允许通过平台邀请好友加入该房间；取消后玩家只能通过搜索或直接加入进入。
	 *  @param bIsDedicatedServer 是否为专用服务器(Dedicated Server)。专用服务器不渲染画面、不使用Presence；勾选后请不要依赖邀请/Presence相关功能。
	 *  @param bAllowJoinViaPresence 是否允许好友通过在线状态(Presence)直接加入房间；取消后只能通过搜索或邀请加入。
	 *  @param bAllowJoinViaPresenceFriendsOnly 是否仅允许好友通过Presence加入（勾选后非好友即使开启Presence也无法进入）。
	 *  @param bAntiCheatProtected 是否把房间标记为“反作弊保护”；是否真正生效取决于所用的在线子系统。
	 *  @param bUsesStats 是否为该会话启用统计数据(Stats)上报。
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "创建高级会话 (CreateAdvancedSession)", BlueprintInternalUseOnly = "true", WorldContext="WorldContextObject",AutoCreateRefTerm="ExtraSettings"), Category = "Online|AdvancedSessions")
		static UCreateSessionCallbackProxyAdvanced* CreateAdvancedSession(UObject* WorldContextObject, const TArray<FSessionPropertyKeyPair>& ExtraSettings, class APlayerController* PlayerController = NULL, int32 PublicConnections = 100, int32 PrivateConnections = 0, bool bUseLAN = false, bool bAllowInvites = true, bool bIsDedicatedServer = false, bool bUseLobbiesIfAvailable = true, bool bAllowJoinViaPresence = true, bool bAllowJoinViaPresenceFriendsOnly = false, bool bAntiCheatProtected = false, bool bUsesStats = false, bool bShouldAdvertise = true, bool bUseLobbiesVoiceChatIfAvailable = false, bool bStartAfterCreate = true);

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

