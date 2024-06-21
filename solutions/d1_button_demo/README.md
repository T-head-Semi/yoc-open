# 概述
d1_button_demo是基于d1开发板的LRADC模块进行的按键示例。LRADC模块属于输入设备，一般包括各种按键的实现。当用户按下按键的时候会触发中断，可以在中断子程序里面进行判断当前的按键属于哪种行为，可以支持多种按键模式的触发。更详细操作内容可参考[【D1 Dock Pro开发板】YoC RTOS 实战：Lichee D1 Dock 开发板 Button按键》](https://www.xrvm.cn/community/post/detail?spm=a2cl5.26076654.0.0.1f16180fvSWZAJ&id=4037166129649618944)。

# CDK
在CDK的首页，通过搜索d1，可以找到d1_button_demo，然后创建工程。

CDK的使用可以参考YoCBook [《CDK开发快速上手》](https://www.xrvm.cn/document?temp=use-cdk-to-get-started-quickly&slug=yocbook) 章节

# 烧录
通过CDK编译完成之后会在out目录下生成yoc_rtos_8M.img文件，此文件即为最终的镜像文件。
使用全志烧写工具进行烧录。如何安装及烧写请参考[全志官方网站](https://d1.docs.aw-ol.com/study/study_4compile/#phoenixsuit)。

# 启动
烧录完成之后系统会自动启动，串口会有打印输出。
当按下对应的按键(HDMI接口边上的KEY按键)之后会有相应的打印信息输出:

```cli
user key is pressed one times
```
