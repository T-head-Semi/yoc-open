## 概述

`realt_perf`组件是一个适用于裸核和实时操作系统的性能分析工具，用于收集和分析系统的性能数据。它可以帮助开发者分析CPU使用情况，找到性能瓶颈。该组件的主要功能如下：

#### 事件计数
- 跟踪各类硬件PMU事件，例如CPU周期、指令数、缓存命中、分支预测命中等
- 支持按照CPU计数和按线程计数

#### 函数采样统计
- 统计函数的CPU利用率
- 获取各个函数之间的调用关系

## 接口列表

### 基础API
| 函数 | 说明 |
| :--- | :--- |
| perf_record_start | 开始运行perf record |
| perf_record_stop | 停止运行perf record |
| perf_stat_init | 初始化perf_stat模块 |
| perf_stat_deinit | 销毁perf_stat模块 |
| perf_stat_start | 开始运行perf stat |
| perf_stat_stop | 停止运行perf stat并打印结果 |
| get_event_id | 通过事件名称查询事件ID |

### 可重写API
| 函数 | 说明 |
| :--- | :--- |
| perf_printf | 格式控制打印函数 |
| perf_malloc | 内存分配函数 |
| perf_realloc | 内存重新分配函数 |
| perf_free | 内存释放函数 |
| perf_record_dump | 记录perf record数据 |
| perf_record_alloc_data_buf | perf record数据记录缓冲区申请 |
| perf_record_free_data_buf | perf record数据记录缓冲区释放 |

## 接口详细说明

### perf_record_start
`int perf_record_start(uint32_t duration_ms, uint32_t frequency);`

- 功能描述:
    - 启动`perf record`采样，按照函数调用关系，统计各个函数的CPU使用率

- 参数:
    - `duration_ms`: 记录时长
    - `frequency`: 采样频率

- 返回值:
    - 0: 成功
    - 其他：失败

### perf_record_stop
`int perf_record_stop(void);`

- 功能描述:
    - 停止`perf record`采样

- 参数:
    - 无

- 返回值:
    - 0: 成功
    - 其他: 失败

### perf_record_dump

`int perf_record_dump(void);`

- 功能描述:
    - 输出`perf record`数据，定义为弱符号，用户可以自行实现该功能。

- 参数:
    - 无。

- 返回值:
    - 0：成功。
    - 其他：失败。

### perf_stat_init

`void perf_stat_init(void);`

- 功能描述:
    - 初始化`perf-stat`模块，如果使用裸系统，无需执行该函数。如果使用实时操作系统，需要在系统初始化时调用这个函数，在多核场景下，该函数由`CPU0`在其他`CPU`启动之前执行。

- 参数:
    - 无。

- 返回值:
    - 无。

### perf_stat_deinit

`void perf_stat_deinit(void);`

- 功能描述:
    - 销毁`perf-stat`模块，在裸系统运行条件下无需执行该函数。在使用实时操作系统的条件下在该函数在系统关闭时由`CPU0`执行。

- 参数:
    - 无。

- 返回值:
    - 无。

### perf_stat_start

`void perf_stat_start(perf_stat_args_t* args);`

- 功能描述:
    - 根据指定的参数，启动`perf stat`。在多核运行条件下，每个CPU调用一次。

- 参数:
    - `args`：参数结构体

- 返回值:
    - 无。

### perf_stat_stop

`void perf_stat_stop(void);`

- 功能描述:
    - 停止`perf stat`并打印结果。在多核运行条件下，所有CPU各自调用一次，但是只有`CPU0`调用这个函数的时候会进行结果打印。

- 参数:
    - 无。

- 返回值:
    - 无。

### perf_printf

`int perf_printf(const char *fmt, ...);`

- 功能描述:
    - 为组件提供格式化输出功能，定义为弱符号，用户可以自行实现该功能。

- 参数:
    - `fmt`：格式化字符串。
    - `...`：可变参数列表。

- 返回值:
    - 0：成功。
    - 其他：失败。

### perf_malloc

`void *perf_malloc(size_t size);`

- 功能描述:
    - 为组件分配内存，定义为弱符号，用户可以自行实现该功能。

- 参数:
    - `size`：要分配的内存大小。

- 返回值:
    - 成功：返回分配的内存地址。
    - 失败：返回 `NULL`。

### perf_realloc

`void *perf_realloc(void *ptr, size_t size);`

- 功能描述:
    - 调整已分配的内存块大小，定义为弱符号，用户可以自行实现该功能。

- 参数:
    - `ptr`：指向先前分配的内存块的指针。
    - `size`：新内存块的大小。

- 返回值:
    - 成功：返回新的内存地址。
    - 失败：返回 `NULL`。

### perf_free

`void perf_free(void* ptr);`

- 功能描述:
    - 释放组件分配的内存，定义为弱符号，用户可以自行实现该功能。

- 参数:
    - `ptr`：要释放的内存块的指针。

- 返回值:
    - 无。

### perf_record_alloc_data_buf

`unsigned long *perf_record_alloc_data_buf(void);`

- 功能描述:
    - 为`perf record`的数据记录分配内存地址，定义为弱符号，用户可以自行实现该功能。

- 参数:
    - 无。

- 返回值:
    - 成功：返回数据缓冲区地址。
    - 失败：返回 `NULL`。

### perf_record_free_data_buf

`void perf_record_free_data_buf(unsigned long *buf);`

- 功能描述:
    - 释放`perf record`记录数据的内存地址，定义为弱符号，用户可以自行实现该功能。

- 参数:
    - `buf`：要释放的记录数据缓冲区地址。

- 返回值:
    - 无。

### get_event_id

`uint16_t get_event_id(char* ev_name);`

- 功能描述:
    - 查询PMU事件名称对应的ID。

- 参数:
    - `ev_name`：事件名称字符串

- 返回值:
    - 正整数: 事件ID
    - 0: 失败

## 示例

### 裸核运行perf record
```
int perf_record_test(void)
{
    int ret;
    int duration, frequency;

    duration = 5000;
    frequency = 999;

    perf_printf("perf record test start.[duration: %dms, frequency: %dHz]\n", duration, frequency);
    ret = perf_record_start(duration, frequency);
    if (ret != 0) {
        perf_printf("perf record start failed\n");
        return ret;
    }
    ret = test_func4(20);
    perf_printf("ret:%d\n", ret);
    mdelay(500);
    ret = test_func3(50);
    perf_printf("ret:%d\n", ret);
    mdelay(500);
    ret = test_func2(100);
    perf_printf("ret:%d\n", ret);
    mdelay(3000);
    perf_record_stop();
    perf_printf("perf record test finish.\n");
    return ret;
}
```

### 基于实时操作系统多核运行perf record

```c
static void perf_thread_entry(void *parameter)
{
    struct record_args *args = (struct record_args *)parameter;
    perf_record_test(args->duration, args->frequency);
    while(!g_record_stop) {
        rt_thread_mdelay(10);
    }
    perf_record_stop();
}

static void smp_perf_record_test(struct record_args *args)
{
    for (long i = 0; i < CONFIG_NR_CPUS; i++) {
        char buf[32];
        rt_thread_t tid;
        snprintf(buf, sizeof(buf), "record_%ld", i);
        tid = rt_thread_create(buf, perf_thread_entry, args, 8192, 32, 5);
        rt_thread_control(tid, RT_THREAD_CTRL_BIND_CPU, (void *)i);
        if (tid != RT_NULL) {
            rt_thread_startup(tid);
        }
    }
}
```

### 裸核运行perf stat
```c
void perf_stat_test(void)
{
    uint16_t evs[] = {
        PMU_HPM_L1_icache_Access,
        PMU_HPM_L1_icache_Miss,
        PMU_HPM_iTLB_Miss,
        PMU_HPM_jTLB_Miss,
        PMU_HPM_Condition_Branch_Mispred,
        PMU_HPM_Condition_Branch,
        PMU_HPM_Indirect_Branch_Miss,
        PMU_HPM_Indirect_Branch,
        PMU_HPM_Store_Instruction,
        PMU_HPM_L1_dcache_load_access,
    };
    perf_stat_args_t args = {
        .events = evs,
        .nr_events = sizeof(evs) / sizeof(uint16_t),
    };
    perf_stat_start(&args);  // 启动
    my_function();           // 运行被统计的代码
    perf_stat_stop();        // 停止并打印
}
```

### 基于实时操作系统多核运行perf stat

```c
static void perf_stat_thread_entry(void *parameter)
{
    perf_stat_args_t *args = (perf_stat_args_t *) parameter;

    // 开始运行
    perf_stat_start(args);

    // 当g_stat_stop没有置位，一直休眠
    while (!g_stat_stop)
    {
        rt_thread_mdelay(10);
    }

    // 当g_stat_stop置位，结束休眠并停止
    perf_stat_stop();
}

static void smp_perf_stat_test(perf_stat_args_t *args)
{
    for (long i = 0; i < CONFIG_NR_CPUS; i++)
    {
        char buf[32];
        rt_thread_t tid;
        snprintf(buf, sizeof(buf), "stat_%ld", i);
        
        // 为每个核创建一个线程
        tid = rt_thread_create(buf, perf_stat_thread_entry, args, 8192, 32, 5);
        rt_thread_control(tid, RT_THREAD_CTRL_BIND_CPU, (void *)i);

        // 启动线程
        if (tid != RT_NULL)
        {
            rt_thread_startup(tid);
        }
    }
}
```
