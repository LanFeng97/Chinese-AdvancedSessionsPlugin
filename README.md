### How do I use it? ###

**KantanDocGen Automatic Documentation ([KantanDocGen](http://kantandev.com/free/kantan-doc-gen))** 

**[AdvancedSessions](https://vreue4.com/generated-node-documentation?section=advanced-sessions-plugin)**

**[AdvancedSteamSessions](https://vreue4.com/generated-node-documentation?section=advanced-steam-sessions-plugin)**

---
## 中文说明（Chinese Notes）

> 本分支为 UE 4.26 版本的中文化版本。所有蓝图节点的显示名均为“中文 (English)”双语格式，用中文或英文函数名均可搜索到节点；所有英文注释均保留，并在其下方补充了中文翻译，出现歧义时请以英文原注释为准。

### 版本特点（UE 4.26）
- 会话（Session）相关高级蓝图节点：创建、查找、加入、更新、销毁、取消查找、会话信息与自定义属性读写等（AdvancedSessionsLibrary / 各 CallbackProxy）。
- 好友与最近玩家、身份与账号（Identity/UserAccount）、语音（Voice）、外部 UI（好友/邀请/排行榜/网页/资料/账号升级）等节点。
- Steam 扩展（AdvancedSteamSessions）：好友头像与信息、群组、文本过滤、创意工坊订阅与详情、Steam 大屏幕模式等节点。

### 注意事项
- 标注 STEAM ONLY 的函数仅在 Steam 在线子系统下可用。
- EndSession（结束会话）已弃用（Deprecated），请改用 Destroy Session（销毁会话）。
- FilterText / InitTextFiltering 仅 Steam 支持；使用 FilterText 前必须先调用 InitTextFiltering。
- 个别上游英文注释疑似复制粘贴笔误（如 UniqueNetIdToString、GetWorkshopItemDetails、UpdateSession 等），中文注释已按函数实际功能说明并在文中标注。
- 依赖 OnlineSubsystem / OnlineSubsystemUtils；AdvancedSteamSessions 另需 OnlineSubsystemSteam。

### 相比上一版本
- 中文翻译支持自本版本（4.26）开始，无更早的支持版本。
