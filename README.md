# Advanced Sessions Plugin 中文汉化版（Chinese-AdvancedSessionsPlugin）

> 本仓库是 [AdvancedSessionsPlugin](https://github.com/mordentral/AdvancedSessionsPlugin)（原作者 **mordentral**）的 **Fork + 中文汉化** 版本，许可协议见 `LICENSE.txt`（与上游一致）。

## 一、仓库说明

这个插件为 Unreal Engine 提供了一整套“更高级的会话（Session）操作”蓝图节点，包含两个插件：

- **AdvancedSessions**：会话创建/查找/更新/销毁、好友、身份与账号、语音、外部 UI 等（核心，UE4.26 起全版本可用）。
- **AdvancedSteamSessions**：Steam 专属扩展（好友头像与资料、群组、创意工坊、文本过滤、Steam 悬浮层等），需要 Steam 在线子系统。

### 我们做了什么（汉化说明）
- **蓝图节点显示名改为“中文 (English)”双语**：例如 `创建高级会话 (CreateAdvancedSession)`。在蓝图里用**中文或英文函数名都能搜索到**对应节点。
- **所有英文注释保留**，并在其下方补充中文翻译；出现歧义时以英文原注释为准。
- 对上游个别“复制粘贴笔误”的英文注释，按函数实际行为翻译并在中文注释中标注。
- **C++ 函数名 / 参数类型 / 返回值类型保持英文**（不影响编译、存档与既有蓝图）。
- 各版本中被修改过功能的函数，均带有 `[相对上一版本]` 的中文差异说明。

> 注意：代码主体与上游一致。**master 分支保持上游 5.8 原样（未翻译）**，中文版 5.8 在 `5.8-Locked` 分支。

## 二、版本与分支引导

上游按 UE 版本维护了多个分支，本仓库为每个版本都做了中文翻译。**请切换到与你 UE 版本对应的分支查看**，每个分支的 README 都写有该版本的特点、注意事项和相比上一版本的更新。

| UE 版本 | 分支（Git Branch） | 说明 |
|---|---|---|
| UE 4.26 | `4.26-Locked` | 中文翻译起始版本 |
| UE 4.27 | `4.27-Locked` | |
| UE 5.0 | `5.0-Locked` | |
| UE 5.3 | `5.3-Locked` | |
| UE 5.4 | `5.4-Locked` | |
| UE 5.5 | `5.5-Locked` | |
| UE 5.6 | `5.6-Locked` | |
| UE 5.7 | `5.7-Locked` | |
| UE 5.8 | `5.8-Locked` | 自 master（上游 5.8）切出的中文分支 |
| （总览） | `master` | 上游 5.8 原样基线；本页即总说明 |

切换方式（任选其一）：

```bash
# 命令行：先下载全部分支
git clone -b master https://github.com/Smartre97/Chinese-AdvancedSessionsPlugin.git
cd Chinese-AdvancedSessionsPlugin
git fetch origin
git checkout 5.4-Locked        # 把 5.4-Locked 换成你需要的版本
```

或者在 GitHub 网页上点击分支下拉框（Branch）选择对应版本。

**如何安装到项目**：进入对应版本分支后，把 `AdvancedSessions`（及需要的 `AdvancedSteamSessions`）文件夹复制到项目的 `Plugins/` 目录，启用插件即可；也可直接放到引擎的 `Engine/Plugins/`。

## 三、中文使用文档（主要常用节点）

以下以 UE 5.x 常见写法为例；节点名采用“中文 (English)”双名，你在蓝图中直接搜中文或英文都能找到。UE4 分支同名节点同样可用（个别差异见对应分支 README）。

### 1. 会话（Session）基本流程 —— 最常用

多人联机最典型的两条流程：

**主机（Listen Server，可带玩家开房）**
1. `创建高级会话 (CreateAdvancedSession)` → 成功回调 `On Success` 后，其他玩家即可搜到你的房间。
   - `bUseLAN=true`：局域网；否则走在线子系统（Steam 等）。
   - `bUsePresence=true`：做 Listen Server 时通常为 true（地图需以 `listen` 选项加载）。
   - `PublicConnections`：主机人数上限（Listen Server 自身也算 1 个连接，因此想再进 N 人应填 ≥ N+1）。
   - `bShouldAdvertise=true`：让服务器能被搜索到；false 则只能靠邀请加入。
   - 5.4+ 另有 `bAllowJoinViaPresence` 等参数；5.5 起上游暂时注释停用了 `bUsePresence` 输入，请以你所用分支为准。
2.（可选）`开始高级会话 (StartAdvancedSession)`：若创建时 `bStartAfterCreate=false`，需要你在准备就绪后手动开始会话。

**客户端（加入别人的房间）**
1. `高级查找会话 (FindSessionsAdvanced)` → 得到会话结果列表。
   - 可传 `FSessionsSearchSetting` 过滤器数组；`bUseLAN` 要与主机一致。
2. 对选中的结果调用**引擎自带**的 `Join Session` 节点（蓝图右键搜索 “Join Session”）加入。
3. 想退出/结束：使用**引擎自带**的 `Destroy Session`（销毁会话）；插件的 `结束会话 (EndSession)` 是旧接口（4.27 起已取消弃用标记，但官方仍建议用 Destroy Session）。

其他会话节点：
- `取消查找会话 (CancelFindSessions)`：中止正在进行的搜索。
- `更新会话 (UpdateSession)`：修改房间人数上限/广播等设置。**注意：参数较多，需要传的值请显式填满**，避免把默认值当成你想要的数值（上游注释也强调这一点）。
- 会话信息查询（见下）。

### 2. 会话信息与玩家信息（AdvancedSessionsLibrary）

- `获取会话状态 (GetSessionState)` / `获取会话设置 (GetSessionSettings)`：查询当前房间状态（无会话/创建中/进行中/结束等）与连接数、是否 LAN、是否专用服务器等。
- `获取会话ID字符串 (GetSessionID_AsString)` / `获取当前会话ID字符串 (GetCurrentSessionID_AsString)`：拿房间 ID。
- `玩家是否在会话中 (IsPlayerInSession)`：判断某个玩家是否在当前房间。
- `获取唯一网络ID (GetUniqueNetID)`：由 PlayerController 取玩家唯一网络 ID；`唯一网络ID是否有效 (IsValidUniqueNetID)`、`唯一网络ID是否相等 (Equal Unique Net ID)`（节点上显示 `==`）用于比较。
- `获取玩家名称 (GetPlayerName)` / `设置玩家名称 (SetPlayerName)`。
- `服务器切换关卡 (ServerTravel)`：服务器端切图。

### 3. 好友 / 最近玩家 / 邀请（Advanced Friends）

- `获取并存储好友列表 (GetAndStoreFriendsList)`（异步）：成功回调返回好友列表（`FBPFriendInfo` 数组）；之后可用 `获取已保存的好友列表 (GetStoredFriendsList)` 再次读取。
- `向好友发送会话邀请 (SendSessionInviteToFriend / ...ToFriends)`：把当前房间邀请给指定好友。
- `是否为好友 (IsAFriend)`、`获取好友 (GetFriend)`。
- `获取并存储最近玩家列表 (GetAndStoreRecentPlayersList)` / `获取已保存的最近玩家列表 (GetStoredRecentPlayersList)`。
- 想“好友在哪个房间、一键加入”：可用 `查找好友会话 (FindFriendSession)`（异步，返回好友所在会话结果）再配合 Join Session。

### 4. 登录 / 身份 / 账号（Advanced Identity）

- `自动登录用户 (AutoLoginUser)`：用命令行参数（`-AUTH_LOGIN=`/`-AUTH_PASSWORD=`）自动登录，常用于专用服务器/自动化。
- `登录用户 (LoginUser)` / `登出用户 (LogoutUser)`：手动登录/登出（4.27+ 的 LoginUser 有 `AuthType` 参数）。
- `获取登录状态 (GetLoginStatus)`、`获取玩家昵称 (GetPlayerNickname)`。
- 账号相关：`获取用户账号 (GetUserAccount)`、`获取所有用户账号 (GetAllUserAccounts)`、`获取用户账号真实姓名/显示名称/属性 (GetUserAccountRealName / DisplayName / Attribute)` 等。

### 5. 语音（Advanced Voice）

- `是否佩戴耳机 (IsHeadsetPresent)`。
- `开始网络语音 (StartNetworkedVoice)` / `停止网络语音 (StopNetworkedVoice)`：配合实现“按键说话（Push-to-Talk）”。
- `注册本地讲话者 (RegisterLocalTalker)` / `注册所有本地讲话者 (RegisterAllLocalTalkers)`、远程玩家同理（`RegisterRemoteTalker` 等）。注意：引擎通常会自动注册，只有手动注销过才需要再注册。
- `本地/远程玩家是否正在说话 (IsLocalPlayerTalking / IsRemotePlayerTalking)`。
- `静音远程讲话者 (MuteRemoteTalker)` / `取消静音 (UnMuteRemoteTalker)` / `玩家是否被静音 (IsPlayerMuted)`：`bIsSystemWide=true` 时尝试对该玩家全局静音（跨房间）。

### 6. 外部 UI（Advanced External UI）—— 显示平台自带界面

- `显示好友列表界面 (ShowFriendsUI)`、`显示邀请界面 (ShowInviteUI)`、`显示玩家资料界面 (ShowProfileUI)`、`显示网页URL界面 (ShowWebURLUI)` / `关闭网页URL界面 (CloseWebURLUI)`。
- 注意：`显示排行榜界面 (ShowLeaderBoardUI)` 与 `显示账号升级界面 (ShowAccountUpgradeUI)` 在 Steam 上不可用（上游注明）。
- 5.3+ 这些函数普遍带 `WorldContextObject` 输入，一般连 `Get Game Instance` / `Self` 即可。

### 7. Steam 扩展（Advanced Steam Sessions）—— 仅 Steam 在线子系统

- 好友头像/资料：`获取Steam好友头像 (GetSteamFriendAvatar)`（头像需要先 `请求Steam好友信息 (RequestSteamFriendInfo)` 预加载）、`获取Steam个人资料名 (GetSteamPersonaName)`、`获取好友Steam等级 (GetFriendSteamLevel)`、`获取本地Steam ID (GetLocalSteamIDFromSteam)`。
- 群组：`获取Steam群组列表 (GetSteamGroups)`、`获取Steam群组管理员列表 (GetSteamGroupOfficerList)`。
- 创意工坊：`获取已订阅创意工坊物品 (GetSubscribedWorkshopItems)`、`获取创意工坊物品详情 (GetWorkshopItemDetails)`。
- 文本过滤：先 `初始化文本过滤 (InitTextFiltering)`，再 `过滤文本 (FilterText)`。
- 其他：`Steam是否处于大屏幕模式 (IsSteamInBigPictureMode)`、`打开Steam用户悬浮层 (OpenSteamUserOverlay)`、`Steam悬浮层是否启用 (IsOverlayEnabled)` 等。

### 通用注意事项

1. **标注 “STEAM ONLY” 的函数仅在 Steam 在线子系统下可用**；其余函数也依赖你在项目里配置了在线子系统（默认 `Steam` 需要 AppID，见 `DefaultPlatformService` / OnlineSubsystem 配置）。
2. 5.x 版本里大量节点带 `WorldContextObject`（世界上下文）输入，一般连 `Get Game Instance` 或 `Self`。
3. **邀请加入**：主机的 `bShouldAdvertise=false` 时房间不会被搜到，只能通过 `SendSessionInvite*` 邀请。
4. **专用服务器（Dedicated Server）**：创建时 `bUsePresence=false`、`bIsDedicatedServer=true`；专用服务器不使用 Presence。
5. 返回值/枚举仍为英文（如 `FBlueprintSessionResult`、`EBlueprintResultSwitch` 的 Success/Failure 分支），配合本页“双语节点名 + 中文注释”使用即可。
6. **跨版本差异**：不同 UE 版本分支间个别参数有增删（例如 4.27/5.3/5.4 对 `bShouldAdvertise`、`bAllowJoinViaPresence` 的反复调整，5.5 停用 `bUsePresence`/`bSearchLobbies` 等），请以**你所用分支**的 README 和节点为准。

## 四、官方文档（英文）

上游提供的自动生成节点文档（英文，内容最全）：

### How do I use it? ###

**KantanDocGen Automatic Documentation ([KantanDocGen](http://kantandev.com/free/kantan-doc-gen))** 

**[AdvancedSessions](https://vreue4.com/generated-node-documentation?section=advanced-sessions-plugin)**

**[AdvancedSteamSessions](https://vreue4.com/generated-node-documentation?section=advanced-steam-sessions-plugin)**

## 五、致谢

- 上游插件作者 **mordentral**：[AdvancedSessionsPlugin](https://github.com/mordentral/AdvancedSessionsPlugin)（本仓库为其 Fork，代码许可随上游 `LICENSE.txt`）。
- 中文翻译与说明由本仓库维护者基于各版本分支整理，译文仅供学习交流；请以英文原注释/官方文档为最终依据。