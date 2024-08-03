#ifndef __BSP_KEY_INTERRUPT_H__
#define __BSP_KEY_INTERRUPT_H__

#include "bsp_utils.h"
#include "bsp_gpio.h"
#include "bsp_delay.h"
#include "bsp_interrupt.h"

// 按键中断标志位
extern volatile unsigned char keyFlag;

// 按键初始化
extern void key_interrupt_init(void);

// 按键的中断处理函数
void gpio1_io18_irqHandler(unsigned int gicciar, void *param);

#endif //__BSP_KEY_INTERRUPT_H__
