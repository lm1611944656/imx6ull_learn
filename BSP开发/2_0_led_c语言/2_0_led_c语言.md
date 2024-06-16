# 第1章 开发步骤

## 1.1 编写汇编语言

- **设置处理器进入SVC模式**
  - SVC模式：超级管理员模式，特权模式，访问CPU所有资源，供操作系统使用。
    - 设置SVC模式，具体做法是使用程序状态寄存器(CPSR)来设置；

既然是一个寄存器，那么就是32位的，所以设计bit位就好。将CPSR寄存器的低五位设置为0x13，处理器就是SVC模式；

- **设置堆栈指针(SP)**

值得注意的是，有些处理器在设置SP指针之前需要进行外设初始化。但是在Imx6ull中不需要，因为在imxdownload中已经初始化了。

imxdownload文件主要干3件事；

1. 将bin文件转换为镜像文件；

2. 在镜像文件中设置内容

   1. VIT
   2. bootDATA
   3. DCD
   4. bin文件内容

   4者的顺序不能颠倒

3. 将设置好的镜像文件添加到SD卡中；

- **设置跳转到C语言的指令**

  使用b指令，跳转到C语言函数，比如main函数

```c
.global _start

_start:

    /*设置处理器进入SVC模式 */
    mrs r0,cpsr      /*读取cpsr的值到r0 */
    bic r0,r0,#0x1f  /*清除cpsr的bit4--0 与运算 具体参照相关汇编指令*/
    orr r0,r0,#0x13  /*使用SVC模式   或运算  这是汇编的与运算*/
    msr cpsr,r0      /*将r0写入到cpsr中去 */

    /*设置SP指针 */  /*有的芯片比如三星 还要在设置SP指针之前手动初始化DDR和SDRAM  
				    前面分析DCD 数据的时候就已经讲过了，DCD数据包含了DDR配置
				    参数，I.MX6U 内部的Boot ROM 会读取DCD 数据中的DDR 配置参数然后完成DDR 初始化的*/
    ldr sp,=0x80200000  
    b main /*跳转到C语言main函数*/
```



## 1.2 编写c语言

- 寄存器映射

```c
#ifndef  __MAIN_H
#define  __MAIN_H

/*外设时钟寄存器*/
#define  CCM_CCGR0   *((volatile unsigned int *)0X020C4068)
#define  CCM_CCGR1   *((volatile unsigned int *)0X020C406C)
#define  CCM_CCGR2   *((volatile unsigned int *)0X020C4070)
#define  CCM_CCGR3   *((volatile unsigned int *)0X020C4074)
#define  CCM_CCGR4   *((volatile unsigned int *)0X020C4078)
#define  CCM_CCGR5   *((volatile unsigned int *)0X020C407C)
#define  CCM_CCGR6   *((volatile unsigned int *)0X020C4080)

/*
*  IOMUX 复用相关寄存器 
*/

#define SW_MUX_GPIO1_IO03 *((volatile unsigned int *)0X020E0068)
#define SW_PAD_GPIO1_IO03 *((volatile unsigned int *)0X020E02F4)

/*
* GPIO1相关寄存器           这里实际就用了前面两行定义的寄存器
*/

#define GPIO1_DR 			*((volatile unsigned int *)0X0209C000)
#define GPIO1_GDIR 			*((volatile unsigned int *)0X0209C004)
#define GPIO1_PSR 			*((volatile unsigned int *)0X0209C008)
#define GPIO1_ICR1 			*((volatile unsigned int *)0X0209C00C)
#define GPIO1_ICR2 			*((volatile unsigned int *)0X0209C010)
#define GPIO1_IMR 			*((volatile unsigned int *)0X0209C014)
#define GPIO1_ISR 			*((volatile unsigned int *)0X0209C018)
#define GPIO1_EDGE_SEL 		*((volatile unsigned int *)0X0209C01C)
#endif
```



- 操作寄存器(写点灯程序)

```c
#include "main.h"

/*使能所有外设时钟*/
void clk_enable(void)
{
    CCM_CCGR0 = 0xFFFFFFFF;
    CCM_CCGR1 = 0xFFFFFFFF;
    CCM_CCGR2 = 0xFFFFFFFF;
    CCM_CCGR3 = 0xFFFFFFFF;
    CCM_CCGR4 = 0xFFFFFFFF;
    CCM_CCGR5 = 0xFFFFFFFF;
    CCM_CCGR6 = 0xFFFFFFFF;
}

/*初始化LED灯*/
void led_init(void)
{
    SW_MUX_GPIO1_IO03 = 0x5;     /*复用为GPIO1--IO03 */

    SW_PAD_GPIO1_IO03 = 0x10B0;  /*设置GPIO1__IO03电气属性*/

    GPIO1_GDIR = 0x8;  //设置为输出

    GPIO1_DR = 0x0;    //默认打开LED灯

}
/*短延时*/
void delay_short(volatile unsigned int n)
{
    while(n--){}

}
/*
 * 延时  一次循环大概是1ms 在主频396MHz下测试的
 * n:延时ms数
*/
void delay(volatile unsigned int n)
{
    while (n--)
    {
        delay_short(0x7ff);
    }
    
}
/*打开LED灯*/
void  led_on(void)
{
    GPIO1_DR &= ~(1<<3); //bit3清零

}
/*关闭LED灯*/
void led_off(void )
{
    GPIO1_DR |= (1<<3);  //bit3置1
}

int main() 
{
    clk_enable();  //使能外设时钟

    led_init(); //初始化LED
  //  led_off();  
    
    while(1)
    {
        led_off();  
        delay(500);

        led_on();
        delay(500);
    }

    return 0;
}
```



## 1.3 编写编译代码

```makefile
objs := start.o main.o

ledc.bin:$(objs)
	arm-linux-gnueabihf-ld -Ttext 0X87800000 -o ledc.elf $^
	arm-linux-gnueabihf-objcopy -O binary -S ledc.elf $@
	arm-linux-gnueabihf-objdump -D -m arm ledc.elf > ledc.dis

%.o:%.s
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o $@ $<

%.o:%.S
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o $@ $<

%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o $@ $<

clean:
	rm -rf *.o ledc.bin ledc.elf ledc.dis
```



- 编译代码

```shell
make
```

- 生成镜像文件，并且下载代码

```shell
./imxdownload ledc.bin /dev/sdb
```

