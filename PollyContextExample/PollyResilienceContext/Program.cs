using Polly;
using Polly.Retry;

// 1. 定义一个"键"来在上下文中存储我们的自定义数据。
// 这确保了类型安全并避免了魔法字符串。
public static class ContextKeys
{
    public static readonly ResiliencePropertyKey<string> TraceId =
        new("TraceId");

    public static readonly ResiliencePropertyKey<int> LastAttemptNumber =
        new("LastAttemptNumber");
}

class Program
{
    static async Task Main(string[] args)
    {
        Console.WriteLine("=== Polly 弹性上下文示例 ===\n");

        // 准备带有重试策略的弹性管道
        var pipeline = new ResiliencePipelineBuilder()
            .AddRetry(new RetryStrategyOptions
            {
                MaxRetryAttempts = 2,
                Delay = TimeSpan.FromSeconds(0.1),
                OnRetry = args =>
                {
                    // 2. 从上下文中读取'TraceId'
                    var traceId = args.Context.Properties.GetValue(ContextKeys.TraceId, "N/A");
                    Console.WriteLine($"[策略] 正在为TraceId重试: {traceId}。尝试次数: {args.AttemptNumber}");

                    // 3. 将'AttemptNumber'写入上下文供后续使用
                    args.Context.Properties.Set(ContextKeys.LastAttemptNumber, args.AttemptNumber);
                    return default; // 返回一个完成的ValueTask
                }
            })
            .Build();

        // --- 执行我们的操作 ---
        string myTraceId = Guid.NewGuid().ToString()[..8]; // 生成唯一ID
        Console.WriteLine($"生成的追踪ID: {myTraceId}\n");

        // 4. 创建一个新的ResilienceContext并注入我们的自定义TraceId
        var context = ResilienceContextPool.Shared.Get();
        context.Properties.Set(ContextKeys.TraceId, myTraceId);

        int callCount = 0;
        try
        {
            await pipeline.ExecuteAsync(async _ =>
            {
                callCount++;
                // 5. 在操作中直接访问TraceId (通过外部变量)
                Console.WriteLine($"[操作] 正在为TraceId执行: {myTraceId}。调用次数: {callCount}");

                if (callCount < 3)
                {
                    throw new InvalidOperationException("模拟瞬时错误！");
                }
                
                await Task.Delay(10); // 模拟异步操作
            }, context);

            Console.WriteLine($"\n[应用] 操作成功完成！");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"\n[应用] 操作失败: {ex.Message}");
        }
        finally
        {
            // 6. 执行后从上下文中检索'LastAttemptNumber'
            int lastAttempt = context.Properties.GetValue(ContextKeys.LastAttemptNumber, 0);
            Console.WriteLine($"[应用] 操作完成。应用观察到的总重试次数: {lastAttempt}");

            ResilienceContextPool.Shared.Return(context); // 重要：将上下文返回到池中！
        }

        Console.WriteLine("\n=== 示例完成 ===");
        
        // 等待用户按键
        Console.WriteLine("按任意键退出...");
        Console.ReadKey();
    }
}