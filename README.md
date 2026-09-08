### How do I use it? ###

**KantanDocGen Automatic Documentation ([KantanDocGen](http://kantandev.com/free/kantan-doc-gen))** 

**[AdvancedSessions](https://vreue4.com/generated-node-documentation?section=advanced-sessions-plugin)**

**[AdvancedSteamSessions](https://vreue4.com/generated-node-documentation?section=advanced-steam-sessions-plugin)**


---
## 中文说明（Chinese Notes）

> 本分支为 UE 4.27 版本的中文化版本。所有蓝图节点的显示名均为“中文 (English)”双语格式，用中文或英文函数名均可搜索到节点；所有英文注释均保留，并在其下方补充了中文翻译，出现歧义时请以英文原注释为准。

### 版本特点（UE 4.27）
- 在 4.26 全部功能基础上，新增“自动登录（AutoLoginUser）”与“开始高级会话（StartAdvancedSession）”两个异步节点。
- 新增“获取会话所有者的唯一网络ID（GetUniqueNetIdOfSessionOwner）”。
- CreateAdvancedSession（创建高级会话）增加大厅（Lobby）相关参数：bUseLobbiesIfAvailable、bUseLobbiesVoiceChatIfAvailable、bStartAfterCreate。
- FindSessionsAdvanced（高级查找会话）新增 bSearchLobbies（是否同时搜索大厅）。
- LoginUser（登录用户）新增 AuthType 认证类型参数；UpdateSession（更新会话）新增 bShouldAdvertise 广播参数。
- EndSession（结束会话）在 4.27 起已取消弃用标记（仍建议一般用途使用引擎原生的销毁会话 Destroy Session）。

### 注意事项
- 标注 STEAM ONLY 的函数仅在 Steam 在线子系统下可用。
- FilterText / InitTextFiltering 仅 Steam 支持；使用 FilterText 前必须先调用 InitTextFiltering。
- 个别上游英文注释疑似复制粘贴笔误（如 UniqueNetIdToString、GetWorkshopItemDetails、UpdateSession、GetUniqueNetIdOfSessionOwner 等），中文注释已按函数实际功能说明并在文中标注。
- 依赖 OnlineSubsystem / OnlineSubsystemUtils；AdvancedSteamSessions 另需 OnlineSubsystemSteam。

### 相比上一版本（相对 4.26）
- 新增节点：自动登录 AutoLoginUser、开始高级会话 StartAdvancedSession、获取会话所有者的唯一网络ID GetUniqueNetIdOfSessionOwner。
- CreateAdvancedSession / FindSessionsAdvanced / LoginUser / UpdateSession 增加新参数（详见上方“版本特点”）。
- EndSession 取消弃用（4.26 中标注 Deprecated）。
