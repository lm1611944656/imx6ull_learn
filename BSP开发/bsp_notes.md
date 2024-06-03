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



第3章 



# 参考文献

[1]:https://releases.linaro.org/components/toolchain/binaries/