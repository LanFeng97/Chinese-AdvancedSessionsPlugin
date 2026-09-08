### How do I use it? ###

**KantanDocGen Automatic Documentation ([KantanDocGen](http://kantandev.com/free/kantan-doc-gen))** 

**[AdvancedSessions](https://vreue4.com/generated-node-documentation?section=advanced-sessions-plugin)**

**[AdvancedSteamSessions](https://vreue4.com/generated-node-documentation?section=advanced-steam-sessions-plugin)**

---
## 中文说明（Chinese Notes）

> 本分支为 UE 5.3 版本的中文化版本（注：上游 .uplugin 内 VersionName 仍写 5.1，属上游未更新，功能按 5.3 分支源码为准）。节点显示名均为“中文 (English)”双语，可中英文搜索；英文注释保留并在其下补充中文，歧义以英文为准。

### 版本特点（UE 5.3）
- 在 5.0 基础上适配 UE5.3 的 OnlineSubsystem 接口。
- 新增自动转换节点：唯一网络ID转可复制格式（Conv_BPUniqueIDToUniqueNetIDRepl，带 BlueprintAutocast 自动转型）。
- 外部UI、身份、语音等大部分库函数新增 WorldContextObject（世界上下文）参数与引脚。
- Steam 端代码以 `STEAM_SDK_INSTALLED` 宏保护（未安装 Steam SDK 时相关代码不参与编译）。

### 注意事项
- 大量函数相比旧版多了一个 WorldContextObject 输入（一般连 Get Game Instance / Self 等）。
- 标注 STEAM ONLY 的函数仅在 Steam 在线子系统下可用；FilterText / InitTextFiltering 仅 Steam。
- UpdateSession（更新会话）在 5.3 重新加入 bShouldAdvertise 广播参数（5.0 曾移除）。
- 上游 .uplugin 版本号仍是 5.1，不影响使用。

### 相比上一版本（相对 5.0）
- 几乎所有 ExternalUI / Identity / Voice 节点新增 WorldContextObject 参数。
- 新增唯一网络ID转换节点 Conv_BPUniqueIDToUniqueNetIDRepl。
- UpdateSession 重新加入 bShouldAdvertise；代理类内部 WorldContext 改为 TWeakObjectPtr 持有。
- Steam 相关源码改为在 STEAM_SDK_INSTALLED 时编译。
