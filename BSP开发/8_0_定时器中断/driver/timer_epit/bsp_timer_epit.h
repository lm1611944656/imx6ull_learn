#ifndef __BSP_TIMER_EPIT_H__
#define __BSP_TIMER_EPIT_H__

#include "bsp_utils.h"

// 定时器中断标志位
extern volatile unsigned char timer_interrupt_Flag;

/*
 * @brief 定时器初始化
 * @param frac  定时器的时钟分频值
 * @param value 预重装载值*/
extern void timer_epit1_init(unsigned int frac, unsigned int value);

// 定时器中断函数
extern void epit1_irqhandler(unsigned int gicciar, void *param);

#endif // __BSP_TIMER_EPIT_H__
