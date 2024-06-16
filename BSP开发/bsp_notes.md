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

# 第1章 开发环境搭建

## 1.1 工具介绍

### 1.1.1 SecureCRT工具

串口调试助手

linux下查看串口设备的命令

```shell
cat /proc/tty/drivers
```

linux下查看串口设备版本信息的命令

```shell
sudo cat /proc/tty/driver/serial
```

### 1.1.2 串口调试助手使用

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

### 1.1.3 交叉编译工具

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

# 第2章 汇编驱动开发

开发步骤：

- 编写汇编代码
- 将汇编文件转换为可执行文件(*.elf)
- 将可执行文件转换为(*.bin)文件
- 将二进制文件生成镜像文件(目的是烧写到SD卡中)

## 2.1 汇编代码格式

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

## 2.2 汇编的读写指令

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



# 第3章 Makefile

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

## 3.1 makefile文件格式

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

# 第3章 DDR介绍

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
  

# 第3章 LED驱动开发

## 3.1 编写汇编文件

- 使能时钟
- 配置电气属性
- 输出控制LED灯的电平

## 3.2 编译和链接文件

- 编译文件，将汇编文件编译成目标文件

```shell

```

- 链接文件，将目标文件链接为可执行文件(*.elf)



- 制作镜像文件，在可执行文件的头部添加以下信息，方便板卡的MCU识别。





# 参考文献

[0]: https://blog.csdn.net/zhuguanlin121/category_11209263.html?spm=1001.2014.3001.5482

[1]:https://releases.linaro.org/components/toolchain/binaries/