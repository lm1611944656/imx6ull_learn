#include "bsp_timer_epit.h"
#include "bsp_interrupt.h"

volatile unsigned char timer_interrupt_Flag = 0;

void timer_epit1_init(unsigned int frac, unsigned int value){
    // 如果分频值大于4095 将分频值设置在4095
    if(frac > 4095){
        frac = 4095;
    }

    // 配置epit1的控制寄存器
    EPIT1->CR = 0;	/* 先清零CR寄存器 */

     /*
     * CR寄存器:
     * bit25:24 01 时钟源选择Peripheral clock=66MHz
     * bit15:4  frac 分频值
     * bit3:	1  当计数器到0的话从LR重新加载数值
     * bit2:	1  比较中断使能
     * bit1:    1  初始计数值来源于LR寄存器值
     * bit0:    0  先关闭EPIT1
     */
    EPIT1->CR = (1<<24 | frac << 4 | 1<<3 | 1<<2 | 1<<1);

    EPIT1->LR = value;	/* 加载数值 相当于倒计数值 */
    EPIT1->CMPR	= 0;	/* 比较寄存器，当计数器值和此寄存器值相等的话就会产生中断 */

    /* 使能GIC中对应的中断 	*/
    GIC_EnableIRQ(EPIT1_IRQn);//宏定义这个中断号是88

    /* 注册中断服务函数 	*/
    system_register_irqtable(EPIT1_IRQn, (system_irq_handler_t)epit1_irqhandler, NULL);

    EPIT1->CR |= 1<<0;	/* 使能EPIT1 */
}

// 2s的时间到达进入中断函数，中断函数将定时器中断标志位置位的1
void epit1_irqhandler(unsigned int gicciar, void *param){

    // 判断exit的中断标志位
    if(EPIT1->SR & (1 << 0)){

        // 将中断标志位置位为1
        timer_interrupt_Flag = 1;
    }

    // 清楚中断标志位
    EPIT1->SR |= 1 << 0;
}