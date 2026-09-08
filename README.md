### How do I use it? ###

**[AdvancedSteamSessions](https://vreue4.com/generated-node-documentation?section=advanced-steam-sessions-plugin)**

---
## 中文说明（Chinese Notes）

> 本分支为 UE 5.4 版本的中文化版本。节点显示名均为“中文 (English)”双语，可中英文搜索；英文注释保留并在其下补充中文，歧义以英文为准。

### 版本特点（UE 5.4）
- 基于 UE5.4 适配；.uplugin 版本号已由上游更正为 5.4（5.3 分支遗留的 5.1 已不存在）。
- UpdateSession（更新会话）新增 bAllowJoinViaPresence / bAllowJoinViaPresenceFriendsOnly 参数（是否允许通过 Presence 加入）。
- OpenSteamUserOverlay 增加 WorldContextObject 上下文参数。
- AdvancedFriendsGameInstance 新增 bAutoTravelOnAcceptedUserInviteReceived 属性（收到邀请自动跳转，可能与 Beacon 会话冲突，可关闭）。

### 注意事项
- 标注 STEAM ONLY 的函数仅在 Steam 在线子系统下可用；FilterText / InitTextFiltering 仅 Steam。
- 大部分函数带 WorldContextObject 输入（连 Get Game Instance / Self 等）。
- UpdateSession 自 4.27/5.3/5.4 参数不断调整，请以当前版本节点参数为准。

### 相比上一版本（相对 5.3）
- UpdateSession 新增两个 Presence 相关参数。
- OpenSteamUserOverlay 新增 WorldContextObject。
- GameInstance 新增“收到邀请自动跳转”开关属性 bAutoTravelOnAcceptedUserInviteReceived。
- 上游 .uplugin 版本号更正为 5.4。
