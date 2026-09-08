// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
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
#include "BlueprintDataDefinitions.h"
#include "UObject/UObjectIterator.h"

// This is taken directly from UE4 - OnlineSubsystemSteamPrivatePCH.h as a fix for the array_count macro
// @todo Steam: Steam headers trigger secure-C-runtime warnings in Visual C++. Rather than mess with _CRT_SECURE_NO_WARNINGS, we'll just
//	disable the warnings locally. Remove when this is fixed in the SDK
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
// #TODO check back on this at some point
#pragma warning(disable:4265) // SteamAPI CCallback< specifically, this warning is off by default but 4.17 turned it on....
#endif

#if (PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX) && STEAM_SDK_INSTALLED

#pragma push_macro("ARRAY_COUNT")
#undef ARRAY_COUNT

#if USING_CODE_ANALYSIS
MSVC_PRAGMA(warning(push))
MSVC_PRAGMA(warning(disable : ALL_CODE_ANALYSIS_WARNINGS))
#endif	// USING_CODE_ANALYSIS

#include <steam/steam_api.h>

#if USING_CODE_ANALYSIS
MSVC_PRAGMA(warning(pop))
#endif	// USING_CODE_ANALYSIS

#include <steam/isteamapps.h>
#include <steam/isteamapplist.h>
//#include <OnlineSubsystemSteamTypes.h>
#pragma pop_macro("ARRAY_COUNT")

// @todo Steam: See above
#ifdef _MSC_VER
#pragma warning(pop)
#endif

// Making a copy of this here since the original is still in a private folder and is screwing with things
/**
* Steam specific implementation of the unique net id
*/
class FUniqueNetIdSteam2 :
	public FUniqueNetId
{
PACKAGE_SCOPE:
	/** Holds the net id for a player */
	uint64 UniqueNetId;

	/** Hidden on purpose */
	FUniqueNetIdSteam2() :
		UniqueNetId(0)
	{
	}

	/**
	* Copy Constructor
	*
	* @param Src the id to copy
	*/
	explicit FUniqueNetIdSteam2(const FUniqueNetIdSteam2& Src) :
		UniqueNetId(Src.UniqueNetId)
	{
	}

public:
	/**
	* Constructs this object with the specified net id
	*
	* @param InUniqueNetId the id to set ours to
	*/
	explicit FUniqueNetIdSteam2(uint64 InUniqueNetId) :
		UniqueNetId(InUniqueNetId)
	{
	}

	/**
	* Constructs this object with the steam id
	*
	* @param InUniqueNetId the id to set ours to
	*/
	explicit FUniqueNetIdSteam2(CSteamID InSteamId) :
		UniqueNetId(InSteamId.ConvertToUint64())
	{
	}

	/**
	* Constructs this object with the specified net id
	*
	* @param String textual representation of an id
	*/
	explicit FUniqueNetIdSteam2(const FString& Str) :
		UniqueNetId(FCString::Atoi64(*Str))
	{
	}


	/**
	* Constructs this object with the specified net id
	*
	* @param InUniqueNetId the id to set ours to (assumed to be FUniqueNetIdSteam in fact)
	*/
	explicit FUniqueNetIdSteam2(const FUniqueNetId& InUniqueNetId) :
		UniqueNetId(*(uint64*)InUniqueNetId.GetBytes())
	{
	}

	virtual FName GetType() const override
	{
		return STEAM_SUBSYSTEM;
	}

	/**
	* Get the raw byte representation of this net id
	* This data is platform dependent and shouldn't be manipulated directly
	*
	* @return byte array of size GetSize()
	*/
	virtual const uint8* GetBytes() const override
	{
		return (uint8*)&UniqueNetId;
	}

	/**
	* Get the size of the id
	*
	* @return size in bytes of the id representation
	*/
	virtual int32 GetSize() const override
	{
		return sizeof(uint64);
	}

	/**
	* Check the validity of the id
	*
	* @return true if this is a well formed ID, false otherwise
	*/
	virtual bool IsValid() const override
	{
		return UniqueNetId != 0 && CSteamID(UniqueNetId).IsValid();
	}

	/**
	* Platform specific conversion to string representation of data
	*
	* @return data in string form
	*/
	virtual FString ToString() const override
	{
		return FString::Printf(TEXT("%llu"), UniqueNetId);
	}

	/**
	* Get a human readable representation of the net id
	* Shouldn't be used for anything other than logging/debugging
	*
	* @return id in string form
	*/
	virtual FString ToDebugString() const override
	{
		CSteamID SteamID(UniqueNetId);
		if (SteamID.IsLobby())
		{
			return FString::Printf(TEXT("Lobby [0x%llX]"), UniqueNetId);
		}
		else if (SteamID.BAnonGameServerAccount())
		{
			return FString::Printf(TEXT("Server [0x%llX]"), UniqueNetId);
		}
		else if (SteamID.IsValid())
		{
			const FString NickName(SteamFriends() ? UTF8_TO_TCHAR(SteamFriends()->GetFriendPersonaName(UniqueNetId)) : TEXT("UNKNOWN"));
			return FString::Printf(TEXT("%s [0x%llX]"), *NickName, UniqueNetId);
		}
		else
		{
			return FString::Printf(TEXT("INVALID [0x%llX]"), UniqueNetId);
		}
	}


	virtual uint32 GetTypeHash() const override
	{
		return ::GetTypeHash(UniqueNetId);
	}

	/** Convenience cast to CSteamID */
	operator CSteamID()
	{
		return UniqueNetId;
	}

	/** Convenience cast to CSteamID */
	operator const CSteamID() const
	{
		return UniqueNetId;
	}

	/** Convenience cast to CSteamID pointer */
	operator CSteamID*()
	{
		return (CSteamID*)&UniqueNetId;
	}

	/** Convenience cast to CSteamID pointer */
	operator const CSteamID*() const
	{
		return (const CSteamID*)&UniqueNetId;
	}

	friend FArchive& operator<<(FArchive& Ar, FUniqueNetIdSteam2& UserId)
	{
		return Ar << UserId.UniqueNetId;
	}
};

#endif

#include "AdvancedSteamFriendsLibrary.generated.h"


//General Advanced Sessions Log
DECLARE_LOG_CATEGORY_EXTERN(AdvancedSteamFriendsLog, Log, All);

UENUM(Blueprintable)
enum class SteamAvatarSize : uint8
{
	SteamAvatar_INVALID = 0,
	SteamAvatar_Small = 1,
	SteamAvatar_Medium = 2,
	SteamAvatar_Large = 3
};

UENUM(Blueprintable)
enum class ESteamUserOverlayType : uint8
{
	/*Opens the overlay web browser to the specified user or groups profile.*/
	steamid,
	/*Opens a chat window to the specified user, or joins the group chat.*/
	chat,
	/*Opens a window to a Steam Trading session that was started with the ISteamEconomy / StartTrade Web API.*/
	jointrade,
	/*Opens the overlay web browser to the specified user's stats.*/
	stats,
	/*Opens the overlay web browser to the specified user's achievements.*/
	achievements,
	/*Opens the overlay in minimal mode prompting the user to add the target user as a friend.*/
	friendadd,
	/*Opens the overlay in minimal mode prompting the user to remove the target friend.*/
	friendremove,
	/*Opens the overlay in minimal mode prompting the user to accept an incoming friend invite.*/
	friendrequestaccept,
	/*Opens the overlay in minimal mode prompting the user to ignore an incoming friend invite.*/
	friendrequestignore,
	/*Opens the invite overlay, invitations sent from this dialog will be for the provided lobby*/
	// 打开邀请悬浮层；从此对话框发出的邀请将针对指定的大厅（Lobby）
	invitetolobby
};

static FString EnumToString(const FString& enumName, uint8 value)
{
	
	const UEnum* EnumPtr = FindFirstObject<UEnum>(*enumName, EFindFirstObjectOptions::None, ELogVerbosity::Warning, TEXT("EumtoString"));

	if (!EnumPtr)
		return FString();

	FString EnumName = EnumPtr->GetNameStringByIndex(value);
	return EnumName;
}


USTRUCT(BlueprintType, Category = "Online|SteamAPI|SteamGroups")
struct FBPSteamGroupInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online|SteamAPI|SteamGroups")
		FBPUniqueNetId GroupID; // Uint64 representation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online|SteamAPI|SteamGroups")
		FString GroupName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online|SteamAPI|SteamGroups")
		FString GroupTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online|SteamAPI|SteamGroups")
		int32 numOnline = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online|SteamAPI|SteamGroups")
		int32 numInGame = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Online|SteamAPI|SteamGroups")
		int32 numChatting = 0;

};

UENUM(Blueprintable)
enum class EBPTextFilteringContext : uint8
{
	/*Unknown context.*/
	// 未知上下文
	FContext_Unknown = 0,
	/*Game content, only legally required filtering is performed.*/
	// 游戏内容，仅执行法律要求的过滤
	FContext_GameContent = 1,
	/*Char from another player.*/
	// 来自其他玩家的聊天内容
	FContext_Chat = 2,
	/*Character or item name.*/
	// 角色或物品名称
	FContext_Name = 3
};

UCLASS()
class UAdvancedSteamFriendsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	//********* Friend List Functions *************//

	// Get a texture of a valid friends avatar, STEAM ONLY, Returns invalid texture if the subsystem hasn't loaded that size of avatar yet
	// 获取有效好友头像的纹理，仅限Steam；若子系统尚未加载该尺寸的头像则返回无效纹理
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedFriends|SteamAPI", meta = (DisplayName = "获取Steam好友头像 (GetSteamFriendAvatar)", ExpandEnumAsExecs = "Result"))
	static UTexture2D * GetSteamFriendAvatar(const FBPUniqueNetId UniqueNetId, EBlueprintAsyncResultSwitch &Result, SteamAvatarSize AvatarSize = SteamAvatarSize::SteamAvatar_Medium);

	// Preloads the avatar and name of a steam friend, return whether it is already available or not, STEAM ONLY, Takes time to actually load everything after this is called.
	// 预加载Steam好友的头像与名称，返回这些信息是否已可用；仅限Steam。调用后实际加载全部内容需要一定时间。
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedFriends|SteamAPI", meta = (DisplayName = "请求Steam好友信息 (RequestSteamFriendInfo)"))
	static bool RequestSteamFriendInfo(const FBPUniqueNetId UniqueNetId, bool bRequireNameOnly = false);

	// Opens the steam overlay to go to the specified user dialog
	// 打开Steam悬浮层（Overlay）以跳转到指定的用户对话框
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedFriends|SteamAPI", meta = (DisplayName = "打开Steam用户悬浮层 (OpenSteamUserOverlay)", WorldContext = "WorldContextObject"))
		static bool OpenSteamUserOverlay(UObject* WorldContextObject, const FBPUniqueNetId UniqueNetId, ESteamUserOverlayType DialogType);
	
	// Returns if the steam overlay is currently active (this can return false during initial overlay hooking)
	// 返回Steam悬浮层当前是否处于活动状态（初始挂接悬浮层期间可能返回false）
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedFriends|SteamAPI", meta = (DisplayName = "Steam悬浮层是否启用 (IsOverlayEnabled)"))
		static bool IsOverlayEnabled();

	// Gets the level of a friends steam account, STEAM ONLY, Returns -1 if the steam level is not known, might need RequestSteamFriendInfo called first.
	// 获取好友Steam账号的等级；仅限Steam。若等级未知则返回-1，可能需要先调用RequestSteamFriendInfo。
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedFriends|SteamAPI", meta = (DisplayName = "获取好友Steam等级 (GetFriendSteamLevel)"))
	static int32 GetFriendSteamLevel(const FBPUniqueNetId UniqueNetId);

	// Gets the persona name of a steam ID, STEAM ONLY, Returns empty if no result, might need RequestSteamFriendInfo called first.
	// 获取Steam ID对应的个人资料名（Persona Name）；仅限Steam。若无结果返回空字符串，可能需要先调用RequestSteamFriendInfo。
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedFriends|SteamAPI", meta = (DisplayName = "获取Steam个人资料名 (GetSteamPersonaName)"))
	static FString GetSteamPersonaName(const FBPUniqueNetId UniqueNetId);

	// Creates a unique steam id directly from a string holding a uint64 value, useful for testing
	// 直接从保存uint64值的字符串创建Steam唯一ID，便于测试
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedFriends|SteamAPI", meta = (DisplayName = "从字符串创建Steam ID (CreateSteamIDFromString)"))
	static FBPUniqueNetId CreateSteamIDFromString(const FString SteamID64);

	// Retreives the local steam ID from steam
	// 从Steam获取本地Steam ID
	UFUNCTION(BlueprintPure, Category = "Online|AdvancedFriends|SteamAPI", meta = (DisplayName = "获取本地Steam ID (GetLocalSteamIDFromSteam)"))
		static FBPUniqueNetId GetLocalSteamIDFromSteam();

	/* Gets the current game played by a friend - AppID is int32 even though steam ids are uint32, can't be helped in blueprint currently
	*  can use the AppID with the WebAPI GetAppList request.
	*/
	// 获取好友当前正在游玩的游戏——AppID为int32（尽管Steam ID是uint32，目前蓝图无法更改）；可将AppID配合WebAPI的GetAppList请求使用
	UFUNCTION(BlueprintCallable, Category = "Online|AdvancedFriends|SteamAPI", meta = (DisplayName = "获取Steam好友正在玩的游戏 (GetSteamFriendGamePlayed)", ExpandEnumAsExecs = "Result"))
	static void GetSteamFriendGamePlayed(const FBPUniqueNetId UniqueNetId, EBlueprintResultSwitch &Result/*, FString & GameName*/, int32 & AppID);

	// Get a full list of steam groups
	// 获取完整的Steam群组列表
	UFUNCTION(BlueprintCallable, Category = "Online|SteamAPI|SteamGroups", meta = (DisplayName = "获取Steam群组列表 (GetSteamGroups)"))
		static void GetSteamGroups(TArray<FBPSteamGroupInfo> & SteamGroups);

	// Initializes text filtering (pre-loading dictonaries)
	// Returns if it succeeded, false if filtering is unavailable for the games language
	// 初始化文本过滤（预加载词典）
	// 返回是否初始化成功；若该游戏语言不支持过滤则返回false
	UFUNCTION(BlueprintCallable, Category = "Online|SteamAPI|TextFiltering", meta = (DisplayName = "初始化文本过滤 (InitTextFiltering)"))
		static bool InitTextFiltering();

	// Attempts to filter a string with the given filtering context
	// Returns true if the text has been filtered, false if it hasn't (no filtering required or operation failed)
	// If false it will still output the original text
	// Textsource is the steam id that is the source of the text (player name / chat)
	// Requires that InitTextFiltering be called first!!
	// 尝试使用给定的过滤上下文（Context）过滤字符串
	// 若文本已被过滤则返回true；若未被过滤（无需过滤或操作失败）则返回false
	// 返回false时仍会输出原始文本
	// TextSource是文本来源的Steam ID（玩家名/聊天）
	// 必须先调用InitTextFiltering！！！
	UFUNCTION(BlueprintCallable, Category = "Online|SteamAPI|TextFiltering", meta = (DisplayName = "过滤文本 (FilterText)"))
		static bool FilterText(FString TextToFilter, EBPTextFilteringContext Context, const FBPUniqueNetId TextSourceID, FString& FilteredText);

	// Returns if steam is running in big picture mode
	// 返回Steam当前是否以“大屏幕模式（Big Picture）”运行
	UFUNCTION(BlueprintPure, Category = "Online|SteamAPI", meta = (DisplayName = "Steam是否处于大屏幕模式 (IsSteamInBigPictureMode)"))
		static bool IsSteamInBigPictureMode();
};	
