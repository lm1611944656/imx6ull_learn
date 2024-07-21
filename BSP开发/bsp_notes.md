# 第0章 芯片介绍

[参考笔记][0]

## 0.1 芯片标识

![img](https://raw.githubusercontent.com/lm1611944656/imx6ull_learn/master/imx6ull_learn_notes_img/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3podWd1YW5saW4xMjE=,size_16,color_FFFFFF,t_70.png)

## 0.2 参数名称

imx6ull是一款由NXP公司推出的低功耗高性能嵌入式处理器。imx6ull是一颗Cortex-A7架构的MPU。

![在这里插入图片描述](https://raw.githubusercontent.com/lm1611944656/imx6ull_learn/master/imx6ull_learn_notes_img/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3podWd1YW5saW4xMjE=,size_16,color_FFFFFF,t_70-17184214146822.png)

## 0.3 核心板

![在这里插入图片描述](https://raw.githubusercontent.com/lm1611944656/imx6ull_learn/master/imx6ull_learn_notes_img/aaad291b03204d0796232528ff5e9534.png)

## 0.4 BSP板

![在这里插入图片描述](https://raw.githubusercontent.com/lm1611944656/imx6ull_learn/master/imx6ull_learn_notes_img/ed2d833be3924224a31dfecfd8688a12.png)

# 第1章 MCU与SOC的区别，RTOS与LINUX区别

## 1.1 阐述

MCU就是微控制器，别名叫单片机，具体像STC的51单片机，ST的STM8、STM32、Arduino的AVR、TI的MSP430等等。

## 2.1.在操作系统层面

MCU一般最多只运行实时操作系统(RTOS)，不会上Linux，更多的是”裸机”编程。RTOS像freertos或者UCOS都是只能跑多线程，但是不能跑多进程。

## 2.2 SOC

### 2.2.1 阐述

低端的SOC就是内部集成了MCU+特定功能模块外设。高端的SOC应该是内部集成MPU/CPU+特定功能模块外设。具体像NXP的IMX6ULL等。

### 2.2.2 在操作系统层面

SOC可以跑Linux或者QNX系统，最大的差别就是多核，多进程多线程。QNX也是实时操作系统，但是可以实现多进程的，多线程的功能，Linux的分时系统。

## 2.3 MCU与SOC区别

低端的SOC就是在MCU的基础上加了一些定制化的功能，比如蓝牙协议，Zigbee协议，或者解码功能，和MCU功能上没什么大区别，其他的在差别就是在跑操作系统上。

# 第2章 开发环境搭建

## 2.1 工具介绍

### 2.1.1 SecureCRT工具

串口调试助手

linux下查看串口设备的命令

```shell
cat /proc/tty/drivers
```

linux下查看串口设备版本信息的命令

```shell
sudo cat /proc/tty/driver/serial
```

### 2.1.2 串口调试助手使用

- 设备连接方式一

将开发板上电，USB线连接开发板。

在Windos中，检测串口设备。windos中已经安装好SecureCRT软件，采用该软件连接开发板。

- 设备连接方式二

linux中安装串口调试助手；

```shell
apt-get install cutecom 
```

- 使用串口助手

```shell
sudo cutecom
```

### 2.1.3 交叉编译工具

- 查看Ubuntu是什么架构的系统

```shell
uname -m
```

常见的系统架构有X86和ARM。平时使用的GCC和G++是编译C/C++代码，编译之后的可执行文件是在X86使用。

现在需要再X86平台上使用ARM编译工具，编译出来的可执行文件在ARM上使用。

[ARM编译工具下载地址][1]

![在这里插入图片描述](https://raw.githubusercontent.com/lm1611944656/imx6ull_learn/master/imx6ull_learn_notes_img/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3podWd1YW5saW4xMjE=,size_16,color_FFFFFF,t_70-17184217507144.png)

- 将压缩包解压到指定的目录

```shell
tar -zxvf 压缩包 -C  指定的要解压的目录
```

- 给编译工具添加环境变量

```shell
vim /etc/profile
```

在文件中添加环境变量

```shell
export PATH=$PATH:/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin
```

- 刷新环境变量，

```shell 
source /etc/profile
```

- 查看版本号

```shell
arm-linux-gnueabihf-gcc -v
```

**小知识点：**

**linux下的软件应用图标很大概率在：**

```shell
/usr/share/Applications
```

# 第3章 汇编驱动开发

开发步骤：

- 编写汇编代码
- 将汇编文件转换为可执行文件(*.elf)
- 将可执行文件转换为(*.bin)文件
- 将二进制文件生成镜像文件(目的是烧写到SD卡中)

## 3.1 汇编代码格式

```c
# 汇编代码的入口都是
.global _start
    
start:
	指令集
```



>.global      是一个伪目标
>
>-start	是汇编代码的入口函数
>
>start	真正的函数区域

## 3.2 汇编的读写指令

imx6ull是Cortex-A内核

- 读指令

```c
ldr 目的, 源
ldr R0, =0x40002010   @将外设寄存器的地址读取到内核寄存器
ldr R1, =0x40002014   @将外设寄存器的地址读取到内核寄存器
ldr R2, [R0]		  @读取外设寄存器0x40002010中的数据到R2
```

- 写指令

```shell
ldr R0, =0x40002010   @将外设寄存器的地址读取到内核寄存器
ldr R1, =0x40002014   @将外设寄存器的地址读取到内核寄存器
STR R1, [R0]		  @将R1中的数据写入到R0保存的地址中去
```



# 第4章 Makefile

- 在makefile中引用变量的格式为：

```makefile
# 定义一个变量
变量名1 = 值

# 引用变量的格式
变量名2 = $(变量名)
```

- 在shell中引用变量的格式

```shell 
export PATH=$PATH:/usr/bin/clear
```

>$PATH					取系统中原有的环境变量；
>
>:								将环境变量用英文冒号分割开来；
>
>/usr/bin/clear		新的环境变量		

## 4.1 makefile文件格式

```makefile
糖醋排骨：糖 醋 排骨
	制作糖醋排骨
糖：
	到商店买糖
醋：
	到商店买醋
排骨：
	到商店买排骨
```

- 专业术语

```makefile
# 定义目标
目标: 依赖
	命令集
	
# 定义伪目标
.PYTHON:clean cleanall run buildsys makesys

makesys:
	cd $(BUILD_DIR) && make -j4

buildsys:
	mkdir $(BUILD_DIR) && cd $(BUILD_DIR) && cmake ..

run:
	cd ${DEST_DIR} && ./$(DEST_EXE_NAME)

clean:
	rm -rf $(BUILD_DIR)

cleanall:
	rm  -rf $(BUILD_DIR) $(LIB_DIR) $(DEST_DIR)
```

# 第5章 DDR介绍

我们买手机，通常会告诉你这个手机是4+64 或6+128 配置，说的就是RAM 为4GB 或6GB，ROM 为64G 或128GB。

>**RAM**：随机存储器，可以随时进行读写操作，速度很快，掉电以后数据会丢失。**比如内存条、SRAM、SDRAM、DDR 等都是**。

```c
int a;
a = 10;
```

a 是一个变量，我们需要很方便的对这个变量进行读写操作，方法就是直接“a”进行读写操作，不需要在乎具体的读写过程。我们可以随意的对RAM 中任何地址的数据（ROM需要地址概念，RAM随机就随机在地址上）进行读写操作，非常方便。

> **ROM**：只读存储器

**但是这个ROM 是Flash，比如EMMC 或UFS 存储器，因为历史原因，很多人还是将Flash 叫做ROM。**但是EMMC 和UFS，甚至是NAND Flash，这些都是可以进行写操作的！只是写起来比较麻烦，要先进行擦除，然后再发送要写的地址或扇区，最后才是要写入的数据，学习过STM32，使用过WM25QXX 系列的SPI Flash 的同学应该深有体会。


- 一般Cortex-A 芯片自带的RAM 很小;

- imx6ull 片内有一个256MB的RAM，如果要运行Linux 的话完全不够用的，所以必须要外接一片RAM 芯片；

- imx6ull 片外有一个512MB 的DDR3 内存芯片；
- I.MX6U 支持LPDDR2、LPDDR3/DDR3，I.MX6U-ALPHA开发板上选择的是DDR3。
  

# 第6章 GPIO

[参考地址](https://blog.csdn.net/xiandang8023/article/details/124369632)

## 6.1 IMX6Ull 的IO命名

- IMX6ULL 的 IO 分为两类
  - SNVS 域
  - 通用IO

![示例：pandas 是基于NumPy 的一种工具，该工具是为了解决数据分析任务而创建的。](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5Y-k6LaK572h,size_20,color_FFFFFF,t_70,g_se,x_16.png)

## 6.2 GPIO的配置 

1. 使能 GPIO 对应的时钟；
2. 配置寄存器(IOMUXC_SW_MUX_CTL_PAD_XX_XX)，设置 IO 的复用功能，使其复用为 GPIO 功能；
3. 配置寄存器 IOMUXC_SW_PAD_CTL_PAD_XX_XX，设置 电气特性等等。
4. 第2步已经将 IO 复用为了 GPIO 功能，所以需要配置 GPIO，设置输入/输出、是否使用中断、默认输出电平等。

### 6.2.1 时钟配置

时钟配置通常在时钟控制模块(CCM)进行，CCM 通常指的是 "Clock Control Module"时钟控制模块；

- CCM有7 个寄存器控制着 I.MX6U 的所有外设时钟开关；
  - CCM_CCGR0~CCM_CCGR6
  - 每个寄存器都是32位，

例如 CCM_CCGR0 是个 32 位寄存器，其中每 2 位控制一个外设的时钟，比如 bit31:30 控制着GPIO2 的外设时钟，两个位就有 4 种操作方式

![在这里插入图片描述](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\cde8935d4e3b49cdbf86fe0dde8d7240.png)

CCM_CCGR0 结构体如图：

![在这里插入图片描述](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5Y-k6LaK572h,size_20,color_FFFFFF,t_70,g_se,x_16-17202548894325.png)

**如果我们要打开 GPIO2 的外设时钟，那么只需要设置CCM_CCGR0 的 bit31 和 bit30 都为 1 即可，也就是 CCM_CCGR0=3 << 30。**

### 6.2.2 复用功能配置

**复用功能一般配置IOMUXC_SW_MUX_CTL_PAD_XX_XX**

以寄存器(IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00)这个 IO 为例。

- 寄存器地址为 0X020E005C

- 寄存器是 32 位的，**但是只用到了最低 5 位**。bit0~bit3(MUX_MODE)就是设置 GPIO1_IO00 的复用功能的；
- GPIO1_IO00 一共可以复用为 9种功能 IO；
  - 分别对应 ALT0~ALT8，其中 ALT5 就是作为 GPIO1_IO00；
  - GPIO1_IO00 还可以作为 I2C2_SCL、 GPT1_CAPTURE1、 ANATOP_OTG1_ID 等。

![在这里插入图片描述](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5Y-k6LaK572h,size_20,color_FFFFFF,t_70,g_se,x_16-17202543031962.png)

### 6.2.3 电气特性配置

配置端口的电气属性，使用寄存器(IOMUXC_SW_PAD_CTL_PAD_XX_XX)

例如寄存器：IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00 是用来配置 GPIO1_IO00 的，包括速度设置、驱动能力设置、压摆率设置等等。
下图是IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00数据手册：
![在这里插入图片描述](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5Y-k6LaK572h,size_20,color_FFFFFF,t_70,g_se,x_16-17202562990497.png)

### 6.2.4 GPIO配置

IOMUXC_SW_MUX_CTL_PAD_XX_XX 和 IOMUXC_SW_PAD_CTL_PAD_XX_XX 这两
种寄存器都是配置 IO 的，GPIO 是一个 IO 众多复用功能中的一种。
当 IO 用作 GPIO 的时候需要设置的寄存器，一共有八个：DR、 GDIR、 PSR、 ICR1、 ICR2、 EDGE_SEL、 IMR 和 ISR。

#### 6.2.4.1 DR 寄存器

此寄存器是数据寄存器：
![在这里插入图片描述](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5Y-k6LaK572h,size_20,color_FFFFFF,t_70,g_se,x_16-17202564933529.png)

#### 6.2.4.2 GDIR 寄存器

这是方向寄存器，用来设置某个 GPIO 的工作方向的，即输入/输出:

![在这里插入图片描述](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5Y-k6LaK572h,size_20,color_FFFFFF,t_70,g_se,x_16-172025653935411.png)

#### 6.2.4.3 PSR 寄存器

这是 GPIO 状态寄存器:

![在这里插入图片描述](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5Y-k6LaK572h,size_20,color_FFFFFF,t_70,g_se,x_16-172025657124013.png)

#### 6.2.4.4  ICR1和ICR2寄存器

这两个寄存器，都是中断控制寄存器， ICR1用于配置低16个GPIO，ICR2 用于配置高 16 个 GPIO：【一个寄存器有32个IO,ICR1 用于 IO0~15 的配置， ICR2 用于 IO16~31 的配置，GPIO1_IO15为上升沿触发中断，那么GPIO1.ICR1=2<<30，如果要设置 GPIO1 的 IO16~31 的话就需要设置 ICR2 寄存器了。】
![在这里插入图片描述](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5Y-k6LaK572h,size_20,color_FFFFFF,t_70,g_se,x_16-172025662112215.png)

#### 6.2.4.5 IMR 寄存器

这是中断屏蔽寄存器：

![在这里插入图片描述](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5Y-k6LaK572h,size_20,color_FFFFFF,t_70,g_se,x_16-172025665870217.png)

#### 6.2.4.6 ISR 寄存器

这是中断状态寄存器：

![在这里插入图片描述](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5Y-k6LaK572h,size_20,color_FFFFFF,t_70,g_se,x_16-172025669727819.png)

#### 6.2.4.7 EDGE_SEL 寄存器

这是边沿选择寄存器：

![在这里插入图片描述](E:\Hardware\Imx6ull\Workspace\imx6ull_learn\imx6ull_learn_notes_img\watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5Y-k6LaK572h,size_20,color_FFFFFF,t_70,g_se,x_16-172025672464721.png)

## 6.3 代码实现

```c
A:使能 GPIO1 时钟, CCM_CCGR0 
	/* CMM 有 CCM_CCGR0~CCM_CCGR6 这 7 个寄存器，这 7 个寄存器控制着 I.MX6U 的所有外设时钟开关，
	 * CCM_CCGR0 是个 32 位寄存器，其中每 2 位控制一个外设的时钟，比如 bit31:30 控制着 GPIO2 的外设时钟，两个位就有 4 种操作方式，
	 * 00 所有模式下都关闭外设时钟。01 只有在运行模式下打开外设时钟，等待模式和停止模式下均关闭外设时钟。
	 * 10 未使用(保留)。11 除了停止模式以外，其他所有模式下时钟都打开。
	 
code:
	/* 使能CCM_CCGR0 时钟 */
	CCM_CCGR0 = 0xffffffff;


B:设置 GPIO1_IO03 的 IO 复用功能
	/* 选用 IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00寄存器，根据datasheet，寄存器地址为 0X020E005C，这个寄存器是 32 位的，但是只用到了最低 5 位，
	 * bit0~bit3(MUX_MODE)就是设置 GPIO1_IO00 的复用功能,GPIO1_IO00 一共可以复用为 9种功能 IO，分别对应 ALT0~ALT8，
	 * 其中 ALT5 就是作为 GPIO1_IO00。(选择哪路GPIO，根据代码中定义的地址来选择，复用哪路功能，根据ALT的选择来判断)
	 */	 
code:
	/* 寄存器地址 */
	#define SW_MUX_GPIO1_IO03 	*((volatile unsigned int *)0X020E0068)
	/* 初始化IO复用功能 */
	SW_MUX_GPIO1_IO03 = 0x5;


C:配置 GPIO1_IO03 的 IO 配置
	/* 选用 IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00 寄存器，寄存器地址为 0X020E02E8， 32 位寄存器，但是只用到了其中的低 17 位
	 * 用来配置 GPIO1_IO00 的速度设置、驱动能力设置、压摆率设置等。
code:
	/* 配置GPIO1_IO03的IO属性	
	 * bit 16:0 HYS关闭
	 * bit [15:14]: 00 默认下拉
     * bit [13]: 0 kepper功能
     * bit [12]: 1 pull/keeper使能
     * bit [11]: 0 关闭开路输出
     * bit [7:6]: 10 速度100Mhz
     * bit [5:3]: 110 R0/6驱动能力
     * bit [0]: 0 低转换率
     */
    /* 寄存器地址 */
    #define SW_PAD_GPIO1_IO03 *((volatile unsigned int *)0X020E02F4)
    /* 配置电气属性 */
	SW_PAD_GPIO1_IO03 = 0X10B0;	
	
	
D:设置 GPIO
	/* 当 IO 用作 GPIO 的时候需要设置的寄存器，一共有八个：DR、 GDIR、 PSR、 ICR1、 ICR2、 EDGE_SEL、 IMR 和 ISR。
	 * DR 寄存器，此寄存器是数据寄存器， 当 GPIO 被配置为输出功能以后，向指定的位写入数据那么相应的 IO 就会输出相
	 * 应的高低电平，比如要设置 GPIO1_IO00 输出高电平，那么就应该设置 GPIO1.DR=1。
	 * GDIR 寄存器，这是方向寄存器，用来设置某个 GPIO 的工作方向的，即输入/输出，
	 * PSR 寄存器也是一个 GPIO 对应一个位，读取相应的位即可获取对应的 GPIO 的状态，也就是 GPIO 的高低电平值。
	 * ICR1和ICR2这两个寄存器，都是中断控制寄存器， ICR1用于配置低16个GPIO，ICR2 用于配置高 16 个 GPIO
	 * EDGE_SEL 寄存器用来设置边沿中断
	 * IMR 寄存器，这是中断屏蔽寄存器
	 * ISR 寄存器也是 32 位寄存器，一个 GPIO 对应一个位，只要某个 GPIO 的中断发生，那么 ISR 中相应的位就会被置 1。
code:
	/* 初始化GPIO,GPIO1_IO03设置为输出 */
	GPIO1_GDIR = 0X0000008;	


E:控制 GPIO 的输出电平
code:
	/* 设置GPIO1_IO03输出低电平，打开LED0 */
	GPIO1_DR = 0X0;
```



# 第6章 LED驱动开发

## 6.1 编写汇编文件

- 使能时钟
- 配置电气属性
- 输出控制LED灯的电平

## 6.2 编译和链接文件

- 编译文件，将汇编文件编译成目标文件

```shell

```

- 链接文件，将目标文件链接为可执行文件(*.elf)



- 制作镜像文件，在可执行文件的头部添加以下信息，方便板卡的MCU识别。





# 参考文献

[0]: https://blog.csdn.net/zhuguanlin121/category_11209263.html?spm=1001.2014.3001.5482

[1]:https://releases.linaro.org/components/toolchain/binaries/