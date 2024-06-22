#include "imx6ull_RegisterMap.h"


/* 使能外设时钟 */
void clk_enable(void)
{
    CCM->CCGR0 =0xFFFFFFFF;
    CCM->CCGR1 =0xFFFFFFFF;
    CCM->CCGR2 =0xFFFFFFFF;
    CCM->CCGR3 =0xFFFFFFFF;
    CCM->CCGR4 =0xFFFFFFFF;
    CCM->CCGR5 =0xFFFFFFFF;
    CCM->CCGR6 =0xFFFFFFFF;
}

/*初始化LED灯*/
void led_init(void)
{
    /* 第1步，复用为GPIO1--IO03 */
    IOMUX_SW_MUX->GPIO1_IO03 = 0x5;

    /* 第2步，配置 GPIO1_IO03 的 IO 属性
     *bit 16:0 HYS 关闭
     *bit [15:14]: 00 默认下拉
     *bit [13]: 0 kepper 功能
     *bit [12]: 1 pull/keeper 使能
     *bit [11]: 0 关闭开路输出
     *bit [7:6]: 10 速度 100Mhz
     *bit [5:3]: 110 R0/6 驱动能力
     *bit [0]: 0 低转换率
     */
    IOMUX_SW_PAD->GPIO1_IO03 = 0x10B0;

    /* 第3步，初始化 GPIO */
    GPIO1->GDIR = 0x8;//设置为输出

    /* 第4步，设置 GPIO1_IO03 输出低电平，打开 LED0 */
    GPIO1->DR = 0x0;

}
/*短延时*/
void delay_short(volatile unsigned int n)
{
    while(n--);
}
/*
 * 延时  一次循环大概是1ms 在主频396MHz
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
    GPIO1->DR &= ~(1<<3); //bit3清零

}
/*关闭LED灯*/
void led_off(void )
{
    GPIO1->DR |= (1<<3);  //bit3置1
}
int main()
{
    clk_enable();  //使能外设时钟

    led_init(); //初始化LED

    while(1)
    {
        led_off();
        delay(2000);

        led_on();
        delay(2000);
    }

    return 0;
}
