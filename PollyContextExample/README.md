# Polly 弹性上下文示例

这个项目演示了如何在 Polly 8.x 中使用弹性上下文（ResilienceContext）来在策略和应用程序代码之间共享数据。

## 项目概述

弹性上下文是 Polly 中的一个强大功能，它允许：
- 从应用程序**流入**数据到管道中
- 在不同策略之间**传递**数据
- 将数据从策略**返回**到应用程序

## 主要功能演示

### 1. 类型安全的属性键
```csharp
public static class ContextKeys
{
    public static readonly ResiliencePropertyKey<string> TraceId = new("TraceId");
    public static readonly ResiliencePropertyKey<int> LastAttemptNumber = new("LastAttemptNumber");
}
```

### 2. 在重试策略中读写上下文数据
- **读取**：从上下文中获取追踪ID用于日志记录
- **写入**：将重试次数存储到上下文中供后续使用

### 3. 在操作中访问上下文数据
- 直接从 `ResilienceContext` 参数中读取自定义数据
- 展示数据在整个执行流程中的传递

### 4. 上下文池管理
- 使用 `ResilienceContextPool.Shared.Get()` 获取上下文
- 使用 `ResilienceContextPool.Shared.Return()` 返回上下文到池中

## 运行要求

- .NET 8.0 或更高版本
- Polly NuGet 包 (版本 8.2.0)

## 如何运行

### 方法1：使用 dotnet run
```bash
cd /root/Component-study/PollyContextExample
dotnet run
```

### 方法2：编译后运行 DLL
```bash
cd /root/Component-study/PollyContextExample
dotnet build
dotnet ./bin/Debug/net8.0/PollyContextExample.dll
```

## 预期输出

程序运行时会显示类似以下的输出：

```
=== Polly 弹性上下文示例 ===

生成的追踪ID: b2fcc975

[操作] 正在为TraceId执行: b2fcc975。调用次数: 1
[策略] 正在为TraceId重试: b2fcc975。尝试次数: 0
[操作] 正在为TraceId执行: b2fcc975。调用次数: 2
[策略] 正在为TraceId重试: b2fcc975。尝试次数: 1
[操作] 正在为TraceId执行: b2fcc975。调用次数: 3

[应用] 操作成功完成！返回结果: 123
[应用] 操作完成。应用观察到的总重试次数: 1

=== 弹性上下文数据流演示 ===
这展示了弹性上下文如何作为共享状态机制，允许数据：
• 从应用程序*流入*管道
• *在*策略之间流动
• *返回*到应用程序

=== 示例完成 ===
```

## 代码解释

### 执行流程

1. **初始化**：创建包含重试策略的弹性管道
2. **设置上下文**：生成追踪ID并存储到弹性上下文中
3. **执行操作**：
   - 第1次调用：抛出异常，触发重试
   - 第2次调用：再次抛出异常，触发第二次重试
   - 第3次调用：成功完成，返回结果
4. **清理**：将上下文返回到对象池中

### 关键概念

- **ResiliencePropertyKey<T>**：提供类型安全的方式来存储和检索上下文数据
- **OnRetry 回调**：在重试时执行，可以访问和修改上下文数据
- **上下文传递**：上下文在整个执行流程中保持一致，确保数据的连续性

## 学习要点

1. **类型安全**：使用强类型的属性键避免魔法字符串
2. **资源管理**：正确使用上下文池来提高性能
3. **数据流向**：理解数据如何在应用程序、策略和操作之间流动
4. **实际应用**：可用于分布式追踪、审计日志、性能监控等场景

## 扩展建议

- 添加更多策略（如断路器、超时）来演示跨策略的数据共享
- 集成真实的分布式追踪系统（如 OpenTelemetry）
- 添加更复杂的上下文数据结构
- 演示异步场景下的上下文传递

## 参考资料

- [Polly 官方文档](https://www.pollydocs.org/)
- [弹性上下文文档](https://www.pollydocs.org/strategies/resilience-context.html)
- [.NET 8 文档](https://docs.microsoft.com/en-us/dotnet/core/whats-new/dotnet-8)
