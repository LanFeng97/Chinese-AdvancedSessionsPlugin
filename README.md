### How do I use it? ###

**[AdvancedSteamSessions](https://vreue4.com/generated-node-documentation?section=advanced-steam-sessions-plugin)**

---
## 中文说明（Chinese Notes）

> 本分支为 UE 5.0 版本的中文化版本。所有蓝图节点的显示名均为“中文 (English)”双语格式，用中文或英文函数名均可搜索到节点；所有英文注释均保留，并在其下方补充了中文翻译，出现歧义时请以英文原注释为准。

### 版本特点（UE 5.0）
- 基于 UE5 重构的源码与格式；功能范围与 4.27 基本一致（会话、好友、身份/账号、语音、外部UI、Steam扩展等）。
- 结构体字段（如 FBPFriendPresenceInfo / FBPFriendInfo / FBPSteamGroupInfo 等）新增默认初始化值，避免未初始化告警。

### 注意事项
- 标注 STEAM ONLY 的函数仅在 Steam 在线子系统下可用。
- FilterText / InitTextFiltering 仅 Steam 支持；使用 FilterText 前必须先调用 InitTextFiltering。
- CreateAdvancedSession 的 bStartAfterCreate 若为 false，需要在准备就绪后手动调用 StartSession（开始会话）。
- 个别上游英文注释疑似复制粘贴笔误（如 UniqueNetIdToString、GetWorkshopItemDetails、UpdateSession 等），中文注释已按函数实际功能说明并在文中标注。
- 依赖 OnlineSubsystem / OnlineSubsystemUtils；AdvancedSteamSessions 另需 OnlineSubsystemSteam / SteamShared。

### 相比上一版本（相对 4.27）
- UpdateSession 移除了 4.27 临时加入的 bShouldAdvertise 参数（中文注释已同步说明）。
- CreateAdvancedSession 的 bStartAfterCreate 补充“为 false 时需手动 StartSession”的说明。
- 多个结构体成员增加默认值初始化（见“版本特点”）。
