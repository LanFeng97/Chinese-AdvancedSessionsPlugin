### How do I use it? ###

**KantanDocGen Automatic Documentation ([KantanDocGen](http://kantandev.com/free/kantan-doc-gen))** 

**[AdvancedSessions](https://vreue4.com/generated-node-documentation?section=advanced-sessions-plugin)**

**[AdvancedSteamSessions](https://vreue4.com/generated-node-documentation?section=advanced-steam-sessions-plugin)**

---
## 中文说明（Chinese Notes）

> 本分支为 UE 5.6 版本的中文化版本。节点显示名均为“中文 (English)”双语，可中英文搜索；英文注释保留并在其下补充中文，歧义以英文为准。

### 版本特点（UE 5.6）
- 基于 UE5.6 适配；AdvancedFriendsGameInstance 新增 bAutoJoinSessionOnAcceptedUserInviteReceived 属性（在悬浮层接受邀请后自动加入会话）。
- bAutoTravelOnAcceptedUserInviteReceived 默认值由 true 改为 false。

### 注意事项
- 标注 STEAM ONLY 的函数仅在 Steam 在线子系统下可用；FilterText / InitTextFiltering 仅 Steam。
- 大部分函数带 WorldContextObject 输入（连 Get Game Instance / Self 等）。
- 上游 .uplugin 版本号仍停留在 5.5 / 5.4（上游未随 5.6 分支更新），不影响使用。
- bAutoTravel / bAutoJoin 两个“邀请后自动处理”属性可能与 Beacon 会话冲突，可按需关闭。

### 相比上一版本（相对 5.5）
- GameInstance 新增“接受邀请后自动加入会话”属性（默认 false）。
- “接受邀请后自动跳转”属性默认值改为 false。
