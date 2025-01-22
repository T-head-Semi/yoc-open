# rv_backtrace
## 简介

rv_backtrace是一个简单小型的栈回溯组件，在RISC-V架构下使用，组件依赖rt-thread，实现了基于FP的栈回溯与非FP的栈回溯方式，通过调用统一函数接口rv_backtrace进行栈回溯，默认采用非FP方，若定义宏`BACKTRACE_USE_FP`，并添加`-fno-omit-frame-pointer`编译选项,此时采用基于FP的栈回溯，rv_backtrace可以在线程、异常处理函数中使用。

## API介绍

```c
//#define BACKTRACE_USE_FP //使用基于FP栈回溯，添加-fno-omit-frame-pointer编译选项

void rvbacktrace(void);
```

在需要栈回溯的代码之前调用该函数。

## 使用示例

```c
int main(int argc, char *argv[])
{
	...
    extern void cxx_system_init(void);
    cxx_system_init();
    board_yoc_init();
    led_init();
    
    extern void rvbacktrace(void);
    rvbacktrace();
    ...
}
```

运行结果：

```scss
---- RV_Backtrace Call Frame Start: ----
###Please consider the value of ra as accurate and the value of sp as only for reference###
[0]Stack interval :[0x00000000405f6b18 - 0x00000000405f6b38]  ra 0x00000000400e1158 pc 0x00000000400e1154
[1]Stack interval :[0x00000000405f6b38 - 0x00000000405f6b48]  ra 0x000000004006ad1a pc 0x000000004006ad16
[2]Stack interval :[0x00000000405f6b48 - 0x0000000000000007]  ra 0x00000000400807ec pc 0x00000000400807e8
---- RV_Backtrace Call Frame End:----

```

## 注意事项

1. 若定义宏`BACKTRACE_USE_FP`,需同步添加`-fno-omit-frame-pointer`编译选项，确保编译器使用fp/s0寄存器保存栈帧。

2. 若系统支持跳转压缩指令，则在进行栈回溯时以`ra`的值为准，`pc`仅作为参考。