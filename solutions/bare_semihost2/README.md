# 概述

`bare_semihost2` 是一个玄铁最小系统RTOS SDK中面向baremetal领域的semihost(半主机) demo。

该示例使用三方semihost库，包含semihost_printf、semihost_write等打印/文件读写接口。

注意：该示例运行依赖玄铁DebugServer调试工具。

# 基于Linux编译运行

## 编译

```bash
./do_build.sh <cpu> <platform>
```
- cpu: <br />
        e902 e902m e902t e902mt e906 e906f e906fd e906p e906fp e906fdp e907 e907f e907fd e907p e907fp e907fdp <br />
        r910 r920 r908 r908fd r908fdv r908-cp r908fd-cp r908fdv-cp <br />
        c906 c906fd c906fdv c908 c908v c908i c910 c910v2 c910v3 c910v3-cp c920 c920v2 c920v3 c920v3-cp <br />
        c907 c907fd c907fdv c907fdvm c907-rv32 c907fd-rv32 c907fdv-rv32 c907fdvm-rv32
- platform: <br />
        smartl xiaohui

以玄铁`e907fdp`类型为例，可以使用如下命令编译:
```bash
./do_build.sh e907fdp smartl
```

## 运行

示例仅支持FPGA平台运行。

### 基于FPGA平台运行

如何基于FPGA平台运行请参考《玄铁最小系统RTOS SDK使用参考手册》

### 运行结果
运行结果可在执行DebugServerConsole命令对应终端中查看, 参考如下
```
output by semihost_printf
output by semihost_printf2
output by semihost_write
```

正常运行串口输出内容参考如下
```
bare_semihost2 demo start!
bare_semihost2 demo runs successfully!
```

# 基于Windows IDE(CDS/CDK)编译运行

如何基于CDS/CDK等IDE编译运行具体请参考《玄铁最小系统RTOS SDK使用参考手册》

# 相关文档和工具

相关文档和工具下载请从玄铁官方站点 https://www.xrvm.cn 搜索下载

1、《玄铁最小系统RTOS SDK快速上手手册》

2、《玄铁最小系统RTOS SDK使用参考手册》

3、玄铁模拟器QEMU工具


# 注意事项

1、Linux平台下基础环境搭建请参考《玄铁最小系统RTOS SDK快速上手手册》

2、如果出现无法运行情况，请使用`sudo pip install yoctools -U`更新最新版本的yoctools再做尝试。

3、玄铁exx系列cpu仅支持smartl平台，cxx/rxx系列cpu仅支持xiaohui平台。

4、玄铁exx系列cpu支持Linux/CDK/CDS环境编译，cxx/rxx系列cpu支持Linux/CDS环境编译

5、某些示例并不是支持所有的玄铁cpu类型，更详细的信息请参考《玄铁最小系统RTOS SDK使用参考手册》

6、某些示例跟硬件特性相关，QEMU中相关功能可能未模拟，只能在相应FPGA硬件平台上运行。

