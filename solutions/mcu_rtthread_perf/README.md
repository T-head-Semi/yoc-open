# 概述

`mcu_rtthread_perf`   是一个玄铁RTOS SDK中面向mcu领域的perf使用例子。该demo基于rtthread原生接口实现，可运行在QEMU、FPGA环境。

# 基于Linux编译运行

## 编译

```bash
./do_build.sh <cpu> <platform>
```
- cpu: <br />
        c906 c906fd c906fdv c907 c907fd c907fdv c907fdvm <br />
        c907-rv32 c907fd-rv32 c907fdv-rv32 c907fdvm-rv32 <br />
        c908 c908v c908i <br />
        c910v2 c910v3 c910v3-cp <br />
        c920v2 c920v3 c920v3-cp <br />
        r908 r908-cp r908fd r908fd-cp r908fdv r908fdv-cp <br />
        r910
- platform: <br />
        xiaohui

以玄铁`c908v`类型为例，可以使用如下命令编译:
```bash
./do_build.sh c908v xiaohui
```

多核编译：
多核编译时需要将`package.yaml`里面的多核的宏`CONFIG_SMP`和`CONFIG_NR_CPUS`打开。
```yaml
def_config:
  CONFIG_DEBUG: 1
  CLI_CONFIG_STACK_SIZE: 4096
  CONFIG_PERF_BACKTRACE_USE_FP: 1  # use framepoint to get backtrace, need add -fno-omit-frame-pointer in cflag/cxxflag above
  CONFIG_PROFILING_PERF_PER_CORE_BUFFER_SIZE: 262144
  CONFIG_PERF_BACKTRACE_DEBUG_PRINT: 0
  CONFIG_PERF_DATA_GDB_MANUAL_DUMP: 1 # dump data with gdb by manual
  CONFIG_PERF_DATA_SEMIHOST2_DUMP: 0  # dump data with semihost
  # multi-core
  CONFIG_SMP: 1
  CONFIG_NR_CPUS: 2
```

## 程序启动

perf record命令可以基于玄铁QEMU或FPGA平台运行，perf stat命令只能基于FPGA平台运行。

### 基于玄铁QEMU运行

单核运行：
```bash
qemu-system-riscv64 -machine xiaohui -nographic -kernel yoc.elf -cpu c908v -gdb tcp::1234
```

smp多核运行：
```bash
qemu-system-riscv64 -machine xiaohui -nographic -kernel yoc.elf -cpu c908v -smp cpus=2 -gdb tcp::1234
```

#### 终端退出qemu

1. 先Ctrl+a
2. 松开所有按键， 紧接着再按下x键

### 基于FPGA平台运行

如何基于FPGA平台运行请参考《玄铁RTOS SDK用户手册》

## 命令行使用

串口看到以下输出内容时可以输入命令行
```
 \ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Sep 23 2024 10:35:00
 2006 - 2024 Copyright by RT-Thread team
mcu_rtthread_perf start.
```

支持`help`命令、`ps`命令、`perf stat`命令和`perf record`命令。

## help命令
输入`help`可以看到`perf stat`命令和`perf record`命令的使用
```
help
perf record <duration_ms> <frequency>
perf stat -e ev1,ev2,ev3 -C 0,1 -t 0x1e23,0x3f52,0x12345678
```

## ps 命令
输入`ps`命令可以看到当前的所有线程信息
```
ps
current threads:
thread                                           cpu bind pri  status      sp     stack size max used left tick   error  tcb addr
------------------------------------------------ --- ---- ---  ------- ---------- ----------  ------  ---------- ------- ------------------
uart_rx                                            0   0   60  running 0x00000310 0x00001000    27%   0x00000001 OK      0x0000000050032280
thread_1                                         N/A   1   32  suspend 0x000002a0 0x00002000    10%   0x00000005 EINTRPT 0x00000000500300b8
thread_0                                         N/A   0   32  suspend 0x000002a0 0x00002000    09%   0x00000005 EINTRPT 0x000000005002def0
app_task                                         N/A   2   32  suspend 0x000002b0 0x00002000    19%   0x00000009 EINTRPT 0x000000005002b910
sys workq                                        N/A   2   23  suspend 0x00000280 0x00001108    14%   0x0000000a OK      0x000000005002a640
tsystem                                          N/A   2   62  suspend 0x000002e0 0x00001000    17%   0x00000020 EINTRPT 0x0000000050020c28
tidle1                                             1   1   63  running 0x00000250 0x00001000    19%   0x00000019 OK      0x000000005001da90
tidle0                                           N/A   0   63  ready   0x00000210 0x00001000    12%   0x00000020 OK      0x000000005001d8f8
timer                                            N/A   2    4  suspend 0x00000310 0x00001000    19%   0x0000000a EINTRPT 0x00000000500214c8
```

## perf record命令
输入以下命令开始采集：
```cli
perf record <duration> <frequency>
```
结束采集有3种情况：
1. 开始采集之后，会以当前时间为起点，经过<duration>毫秒时间后自动结束采集
2. 采集数据的buffer满了，提前退出采集
3. 串口输入`perf record stop`命令，会即刻停止采集

### 通过GDB手动dump data
#### 单核采集结束时的串口打印如下：
```
\ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Sep 23 2024 10:35:00
 2006 - 2024 Copyright by RT-Thread team
mcu_rtthread_perf start.

perf record 5000 999
cpuid[0] perf record test start.[duration: 5000ms, frequency: 999]
cpuid[0] alloc databuf: 0x5001eeb8
cpuid[0] perf record test func val.[6137500]
cpuid[0] time up.
cpuid[0] stop record, pdata->tick: 4996
cpuid[0] please use riscv64-unknown-elf-gdb to dump data:
cpuid[0] dump memory perf_rtos_0.data 0x5001eeb8 0x5001eeb8+178096 
cpuid[0] when finish dump, please input set g_dump_flag=1 to continue
```

#### 多核采集结束时串口输出如下：
```
\ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Sep 23 2024 11:30:01
 2006 - 2024 Copyright by RT-Thread team
mcu_rtthread_perf start.

perf record 5000 999
cpuid[0] perf record test start.[duration: 5000ms, frequency: 999]
cpuid[0] alloc databuf: 0x5002c0d0
cpuid[1] perf record test start.[duration: 5000ms, frequency: 999]
cpuid[1] alloc databuf: 0x5006e2b0
cpuid[1] perf record test func val.[6137500]
cpuid[0] perf record test func val.[6137500]
cpuid[0] time up.
cpuid[0] stop record, pdata->tick: 4996
cpuid[1] time up.
cpuid[1] stop record, pdata->tick: 4996
cpuid[0] please use riscv64-unknown-elf-gdb to dump data:
cpuid[0] dump memory perf_rtos_0.data 0x5002c0d0 0x5002c0d0+199256 
cpuid[0] dump memory perf_rtos_1.data 0x5006e2b0 0x5006e2b0+120304 
cpuid[0] when finish dump, please input set g_dump_flag=1 to continue
```

当看到 `when finish dump, please input set g_dump_flag=1 to continue`提示信息时

1. 如果是QEMU运行，则需要打开另外一个终端，并输入以下命令：
```bash
riscv64-unknown-elf-gdb yoc.elf -x gdbinit
```
请确保`gdbinit`文件里面的内容是 `target remote localhost:1234`

2. FPGA运行时，直接在之前使用`riscv64-unknown-elf-gdb`加载 yoc.elf 的终端界面按下`Ctrl+C`组合按键。

然后再根据串口提示信输入`dump memory ... `相关的命令进行dump。dump完成之后会在当前目录下生成`perf_rtos_0.data`等文件。
如果是多核就多dump几次，相应的当前目录也会生成多个文件。

### 通过semihost dump data
QEMU不支持使用semihost功能。
使用semihost功能时，需要将`package.yaml`的宏进行更改，如下。
```yaml
def_config:
  ...
  CONFIG_PERF_DATA_GDB_MANUAL_DUMP: 0 # dump data with gdb by manual
  CONFIG_PERF_DATA_SEMIHOST2_DUMP: 1  # dump data with semihost
  ...
```

DebugServer连接FPGA的命令如下：
```
DebugServerConsole -ls -prereset
```
输入以上命令之后，DebugServerConsole的连接界面有如下信息：
```
...
Switch input to Semihosting!
...
```
#### 单核采集结束时的串口打印如下：
```
\ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Sep 23 2024 14:06:49
 2006 - 2024 Copyright by RT-Thread team
mcu_rtthread_perf start.

perf record 5000 999
cpuid[0] perf record test start.[duration: 5000ms, frequency: 999]
cpuid[0] alloc databuf: 0x50020148
cpuid[0] perf record test func val.[6137500]
cpuid[0] time up.
cpuid[0] stop record, pdata->tick: 4996
cpuid[0] start to dump [perf_rtos_0.data] perf data[len: 173320] with semihost.[start: 13647 ms]
cpuid[0] success dump perf_rtos_0.data with semihost.[end: 73403 ms]
cpuid[0] will free databuf[0x50020148]
cpuid[0] free databuf[0x50020148] ok
```

#### 多核采集结束时串口输出如下：
```
\ | /
- RT -     Thread Operating System
 / | \     5.1.0 build Sep 23 2024 14:03:08
 2006 - 2024 Copyright by RT-Thread team
mcu_rtthread_perf start.

perf record 5000 999
cpuid[0] perf record test start.[duration: 5000ms, frequency: 999]
cpuid[0] alloc databuf: 0x5002d2a0
cpuid[1] perf record test start.[duration: 5000ms, frequency: 999]
cpuid[1] alloc databuf: 0x5006f480
cpuid[0] perf record test func val.[6137500]
cpuid[1] perf record test func val.[6137500]
cpuid[0] time up.
cpuid[0] stop record, pdata->tick: 4996
cpuid[1] time up.
cpuid[1] stop record, pdata->tick: 4996
cpuid[0] start to dump [perf_rtos_0.data] perf data[len: 199496] with semihost.[start: 12747 ms]
cpuid[0] success dump perf_rtos_0.data with semihost.[end: 80456 ms]
cpuid[0] start to dump [perf_rtos_1.data] perf data[len: 121328] with semihost.[start: 80462 ms]
cpuid[0] success dump perf_rtos_1.data with semihost.[end: 124364 ms]
cpuid[1] no need dump.
cpuid[0] will free databuf[0x5002d2a0]
cpuid[0] free databuf[0x5002d2a0] ok
cpuid[1] will free databuf[0x5006f480]
cpuid[1] free databuf[0x5006f480] ok
```

数据采集完毕之后，会在连接DebugServer端目录生成`perf_rtos_0.data`等文件。多核会生成多个文件。

### perf.data数据分析
使用realt_perf组件下的`stackcollapse.py`脚本进行解析。
如：
```bash
python3 ../../components/realt_perf/scripts/stackcollapse.py perf_rtos_0.data yoc.elf > 0.txt
```
```bash
python3 ../../components/realt_perf/scripts/stackcollapse.py perf_rtos_1.data yoc.elf > 1.txt
```

得到的结果如下：
```
Samples: 4995; Frequency: 999Hz; Duration: 5000ms, Elapsed: 5001ms
+-----+------------+---------+---------------------------+------------------------------------------------------------------------------+
| CPU | Num Sample | Percent | Symbol                    | Call-Graph                                                                   |
+-----+------------+---------+---------------------------+------------------------------------------------------------------------------+
|  0  |    3780    |  75.68% | csi_uart_getc             | [100.00%] csi_uart_getc                                                      |
+-----+------------+---------+---------------------------+------------------------------------------------------------------------------+
|  0  |    783     |  15.68% | idle_thread_entry         | [100.00%] idle_thread_entry                                                  |
+-----+------------+---------+---------------------------+------------------------------------------------------------------------------+
|  0  |    405     |  8.11%  | rt_thread_defunct_dequeue | [81.23%] rt_thread_defunct_dequeue                                           |
|     |            |         |                           | [18.77%] rt_thread_defunct_dequeue <- idle_thread_entry                      |
+-----+------------+---------+---------------------------+------------------------------------------------------------------------------+
|  0  |     25     |  0.50%  | test_func1                | [100.00%] test_func1                                                         |
+-----+------------+---------+---------------------------+------------------------------------------------------------------------------+
|  0  |     2      |  0.04%  | rt_hw_interrupt_enable    | [50.00%] rt_hw_interrupt_enable <- perf_record_test <- simple_cli_task_entry |
|     |            |         |                           | [50.00%] rt_hw_interrupt_enable <- msleep <- sleep <- main                   |
+-----+------------+---------+---------------------------+------------------------------------------------------------------------------+
```

#### 表头含义:
Samples：总的采样次数

Frequency：采样频率

Duration：期望的采样时间

Elapsed：实际消耗的时间

#### 表格释义:
CPU: 当前采用的CPU，0表示cpu0，1表示cpu1，以此类推

Num Sample: 当前函数的采样次数

Percent: 采样占总采样的百分比

Symbol: 函数名称

Call-Graph: 函数调用关系，调用链前面的百分比表示函数被当前调用链调用的占比

### 制作火焰图
使用realt_perf组件下`stackcollapse.py`完成解析以后，每个.data文件会生成一个对应的.fold文件，继续使用`flamegraph.pl`脚本进行解析。
```bash
../../components/realt_perf/scripts/flamegraph.pl 0.fold > 0.svg
../../components/realt_perf/scripts/flamegraph.pl 1.fold > 1.svg
```
可以得到矢量图文件`0.svg`和`1.svg`，然后用浏览器或者其他软件打开即可。

## perf stat命令
perf stat支持默认计数、自选事件计数(`-e`选项)、按CPU计数(`-C`选项)、按线程计数(`-t`选项)。3个选项可以自由组合，参数用逗号分隔。输入`perf stat`开始计数，输入`perf stat stop`停止计数。
#### 命令行使用示例
```bash
# 按默认事件计数，统计范围是全部CPU
perf stat
perf stat stop

# 自选事件，统计l1-icache-miss、l1-icache-access、l1-dcache-load-access三个事件
perf stat -e l1-icache-miss,l1-icache-access,l1-dcache-load-access
perf stat stop

# 按CPU计数，注意-C大写
perf stat -C 0,1
perf stat stop

# 按线程计数，当线程0x1234或者0x1a23在任何一个CPU上被调度运行，则进行计数，线程ID可以通过ps命令查看
# 线程ID可以是10进制或者16进制。以数字1~9开头则以10进制解析，以0x开头则按16进制解析
perf stat -t 0x1234,0x1a23
perf stat stop

# 按线程计数，当线程0x1234或者0x1a23在CPU0上调度运行，则开始计数
perf stat -C 0 -t 0x1234,0x1a23
perf stat stop

# 按线程和CPU计数，指定事件
perf stat -C 0,1 -t 0x1234,0x1a23 -e l1-icache-miss,l1-icache-access,l1-dcache-load-access
perf stat stop
```

### 默认计数
命令行输入`perf stat`开始计数，输入`perf stat stop`停止计数，运行结果如下:
```
mcu_rtthread_perf start.
perf stat
perf_stat_start()
perf stat stop
perf_stat_stop()

Performance counter stat for system wide

131103778                      cycles                          #1.000                CPUs utilized
9945489                        instructions-retired             3792960.250         /sec
3295809                        branch-instruction               1256938.875         /sec
1899                           branch-mispred                   724.231             /sec

2.622092 seconds time elapsed
```

左边第一列代表PMU计数器的读数，第二列是事件名称，第三列是平均每秒的事件数

### 选择事件
使用`-e`选项`mhpmcounter`对应的事件。`cycles`事件和`instructions-retired`事件不需要通过命令行进行选取，无论选择哪些事件，这两个事件都会被统计和显示，因为它们拥有独立的计数器。
```
perf stat -e l1-icache-miss,l2-miss,l1-dcache-miss
perf_stat_start()
perf stat stop
perf_stat_stop()

Performance counter stat for system wide

1682803111                     cycles                          #4.000                CPUs utilized
51198765                       instructions-retired             6085146.000         /sec
6264                           l1-icache-miss                   744.498             /sec
85                             l2-miss                          10.103              /sec
331178                         l1-dcache-miss                   39361.625           /sec

8.413728 seconds time elapsed
```

### 按CPU计数
在多核运行条件下，使用`-C`选项选择CPU，多个CPU用逗号隔开。在4核运行条件下，选择CPU0，和CPU3，监控它们的`cycles`事件、`instructions-retired`事件、`l1-icache-miss`和`l2-cache-miss`事件。如果不指定`-C`选项，则默认统计所有CPU。
```
perf stat -C 0,3 -e l1-icache-miss,l2-miss
perf_stat_start()
perf stat stop
perf_stat_stop()

Performance counter stat for cpu(s): 0,3,

780441275                      cycles                          #2.000                CPUs utilized
38898106                       instructions-retired             4984236.500         /sec
2011                           l1-icache-miss                   257.681             /sec
63                             l2-miss                          8.073               /sec

7.804225 seconds time elapsed

```

### 按线程计数
首先输入`ps`列出当前的所有线程。在`rt-thread`下，线程控制块的地址`tcb addr`就是线程ID。
```
ps
current threads:
thread          pu bind pri  status      sp     stack size max used left tick   error  tcb addr
------------------ ---- ---  ------- ---------- ----------  ------  ---------- ------- ---------
uart_rx         0     0   60  running 0x000002e0 0x00001000    43%   0x00000009 OK      0x0000000050039aa0
thread_3        N/A   3   32  suspend 0x00000290 0x00002000    10%   0x00000005 EINTRPT 0x00000000500378d8
thread_2        N/A   2   32  suspend 0x00000290 0x00002000    10%   0x00000005 EINTRPT 0x0000000050035710
thread_1        N/A   1   32  suspend 0x00000290 0x00002000    10%   0x00000005 EINTRPT 0x0000000050033548
thread_0        N/A   0   32  suspend 0x00000290 0x00002000    08%   0x00000005 EINTRPT 0x0000000050031380
app_task        N/A   4   32  suspend 0x000002b0 0x00002000    12%   0x00000009 EINTRPT 0x000000005002eda0
sys workq       N/A   4   23  suspend 0x00000280 0x00001108    14%   0x0000000a OK      0x000000005002dad0
tsystem         N/A   4   62  suspend 0x000002c0 0x00001000    19%   0x00000020 EINTRPT 0x000000005001c9b0
tidle3          3     3   63  running 0x00000250 0x00001000    19%   0x00000012 OK      0x0000000050021010
tidle2          2     2   63  running 0x00000250 0x00001000    19%   0x00000010 OK      0x0000000050020e78
tidle1          1     1   63  running 0x00000250 0x00001000    19%   0x0000000f OK      0x0000000050020ce0
tidle0          N/A   0   63  ready   0x00000210 0x00001000    12%   0x00000020 OK      0x0000000050020b48
timer           N/A   4    4  suspend 0x00000310 0x00001000    19%   0x0000000a EINTRPT 0x0000000050022828
```
在单核或者多核条件下，通过-t选项指定线程，多个线程ID用逗号隔开。对于每一个线程ID，如果以`0x`开头，则按照16进制解析，如果以数字`1 ~ 9`开头，则按照10进制解析。如果使用`-t`选项与`-C`选项的组合，则只有选定的线程在选定的CPU上被调度运行，才进行计数。

选择`app_task`，统计默认的四个数据：
```
perf stat -t 0x000000005002eda0
perf_stat_start()
perf stat stop
perf_stat_stop()

Performance counter stat for system wide

55715                          cycles                          #0.000                CPUs utilized
17333                          instructions-retired             2893.290            /sec
3867                           branch-instruction               645.494             /sec
433                            branch-mispred                   72.278              /sec

5.990757 seconds time elapsed

```

# 基于Windows IDE(CDS/CDK)编译运行

如何基于CDS/CDK等IDE编译运行具体请参考《玄铁RTOS SDK用户手册》

# 相关文档和工具

相关文档和工具下载请从玄铁官方站点 https://www.xrvm.cn 搜索下载

1、《玄铁RTOS SDK用户手册》

2、玄铁模拟器QEMU工具


# 注意事项

1、Linux平台下基础环境搭建请参考《玄铁RTOS SDK用户手册》

2、如果出现无法编译情况，请使用`sudo pip install yoctools -U`更新最新版本的yoctools再做尝试。

3、玄铁exx系列cpu仅支持smartl平台，cxx/rxx系列cpu仅支持xiaohui平台。

4、某些示例跟硬件特性相关，QEMU中相关功能可能未模拟，只能在相应FPGA硬件平台上运行。

