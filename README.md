### How do I use it? ###

**[AdvancedSteamSessions](https://vreue4.com/generated-node-documentation?section=advanced-steam-sessions-plugin)**

---
## 中文说明（Chinese Notes）

> 本分支为 UE 5.7 版本的中文化版本。节点显示名均为“中文 (English)”双语，可中英文搜索；英文注释保留并在其下补充中文，歧义以英文为准。

### 版本特点（UE 5.7）
- 基于 UE5.7 适配；功能与 5.6 基本一致，主要为上游的小幅整理（如注释掉未使用的 steam 头文件引用）。
- .uplugin 版本号已正确标注 5.7。

### 注意事项
- 标注 STEAM ONLY 的函数仅在 Steam 在线子系统下可用；FilterText / InitTextFiltering 仅 Steam。
- 大部分函数带 WorldContextObject 输入（连 Get Game Instance / Self 等）。

### 相比上一版本（相对 5.6）
- 无新增/删除蓝图节点；仅内部整理与 .uplugin 版本号更新。
