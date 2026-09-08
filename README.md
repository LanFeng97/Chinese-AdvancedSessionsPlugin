### How do I use it? ###

**KantanDocGen Automatic Documentation ([KantanDocGen](http://kantandev.com/free/kantan-doc-gen))** 

**[AdvancedSessions](https://vreue4.com/generated-node-documentation?section=advanced-sessions-plugin)**

**[AdvancedSteamSessions](https://vreue4.com/generated-node-documentation?section=advanced-steam-sessions-plugin)**

---
## 中文说明（Chinese Notes）

> 本分支为 UE 5.8 版本的中文化版本，从仓库 master（上游 5.8）切出。节点显示名均为“中文 (English)”双语，可中英文搜索；英文注释保留并在其下补充中文，歧义以英文为准。

### 版本特点（UE 5.8）
- 基于上游 master（即 5.8）分支：上游已完成 UE5.8 OnlineSubsystem API 适配（主要改动在 .cpp），并清理模块依赖（移除重复的 CoreUObject）。
- 头部仅做 include 适配（改用 Net/OnlineBlueprintCallProxyBase.h、引入 FindSessionsCallbackProxy.h 等），无新增/删除蓝图节点。
- 已验证：未翻译的 master 基线与本中文分支均在 UE_5.8（Visual Studio 2022 14.44）下完整编译通过——上游 5.8 适配完整，本分支无需额外代码修正。

### 注意事项
- 标注 STEAM ONLY 的函数仅在 Steam 在线子系统下可用；FilterText / InitTextFiltering 仅 Steam。
- 大部分函数带 WorldContextObject 输入（连 Get Game Instance / Self 等）。
- AdvancedSteamSessions 依赖 Steamworks/OnlineSubsystemSteam，需安装 Steam SDK 才能编译（本机引擎未带 SDK，未做 Steam 扩展的完整编译）。

### 相比上一版本（相对 5.7）
- 无新增/删除蓝图节点；改动集中在 UE5.8 API 适配、头文件包含调整与模块依赖清理。
