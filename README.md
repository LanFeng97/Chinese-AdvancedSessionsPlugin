### How do I use it? ###

**KantanDocGen Automatic Documentation ([KantanDocGen](http://kantandev.com/free/kantan-doc-gen))** 

**[AdvancedSessions](https://vreue4.com/generated-node-documentation?section=advanced-sessions-plugin)**

**[AdvancedSteamSessions](https://vreue4.com/generated-node-documentation?section=advanced-steam-sessions-plugin)**

---
## 中文说明（Chinese Notes）

> 本分支为 UE 5.9 版本的中文化版本。节点显示名均为“中文 (English)”双语，可中英文搜索；英文注释保留并在其下补充中文，歧义以英文为准。

### 版本特点（UE 5.9）
- 上游目前没有官方 5.9 分支；本分支基于上游 `master`（5.8 代码 + 最新修复 `fixed unreachable breaks`）创建，并完成 UE5.9 兼容性验证。
- 已在 UE5.9 下完整编译通过（AdvancedSessions 核心模块）。
- 包含截至 5.8 的全部中文翻译，以及蓝图引脚的中文悬停说明（`@param` 文档块，覆盖 11 个函数 / 34 个输入型 bool 参数）。
- `.uplugin` 版本号已更新为 5.9。

### 注意事项
- 标注 STEAM ONLY 的函数仅在 Steam 在线子系统下可用；FilterText / InitTextFiltering 仅 Steam。
- AdvancedSteamSessions 依赖 Steamworks/OnlineSubsystemSteam，需要安装 Steam SDK 才能编译（本机未对该扩展做完整编译）。
- 大部分函数带 WorldContextObject 输入（连 Get Game Instance / Self 等）。
- 5.5+ 中 CreateAdvancedSession 的 bUsePresence、FindSessionsAdvanced 的 bSearchLobbies 为上游注释停用参数；中文文档块中保留了停用说明。

### 相比上一版本（相对 5.8）
- 无新增/删除蓝图节点；主要变化为 UE5.9 兼容性实测与 `.uplugin` 版本号更新，并包含上游最新提交 `fixed unreachable breaks`。
- 中文翻译与引脚悬停说明与 5.8 的 `UE5.8_v2` 内容对齐。
