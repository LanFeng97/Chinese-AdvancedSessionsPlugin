### How do I use it? ###

**[AdvancedSteamSessions](https://vreue4.com/generated-node-documentation?section=advanced-steam-sessions-plugin)**

---
## 中文说明（Chinese Notes）

> 本分支为 UE 5.5 版本的中文化版本。节点显示名均为“中文 (English)”双语，可中英文搜索；英文注释保留并在其下补充中文，歧义以英文为准。

### 版本特点（UE 5.5）
- 基于 UE5.5 适配；AdvancedSteamSessions 模块 LoadingPhase 改为 PostDefault。
- CreateAdvancedSession 的 bUsePresence 参数被上游注释停用（蓝图中不再显示该输入）。
- FindSessionsAdvanced 的 bSearchLobbies 参数被上游注释停用（不再搜索大厅）。

### 注意事项
- 标注 STEAM ONLY 的函数仅在 Steam 在线子系统下可用；FilterText / InitTextFiltering 仅 Steam。
- 大部分函数带 WorldContextObject 输入（连 Get Game Instance / Self 等）。
- 5.5 起 CreateAdvancedSession / FindSessionsAdvanced 个别“默认开”参数被上游临时注释，如需要请留意后续版本恢复情况。

### 相比上一版本（相对 5.4）
- CreateAdvancedSession：bUsePresence 参数注释停用。
- FindSessionsAdvanced：bSearchLobbies 参数注释停用。
- AdvancedSteamSessions 模块加载阶段改为 PostDefault。
