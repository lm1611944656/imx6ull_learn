#ifndef __BSP_INTERRUPT_H__
#define __BSP_INTERRUPT_H__

#include "bsp_utils.h"

/*
 * @brief 定义中断处理函数(不同外设有不同的中断处理函数)
 * param1 gicciar 中断的ID号
 * param2 param 中断函数的参数*/
typedef void (*system_irq_handler_t)(unsigned int gicciar, void *param);

// 默认的中断处理函数
void default_irqHandler(unsigned int gicciar, void *param);

// 中断处理函数结构体
typedef struct _sys_irq_handle{
    system_irq_handler_t irqHandle;      // 中断处理函数
    void *userParam;                    // 中断处理函数需要的参数
}sys_irq_handle_t;

// 中断初始化
void int_init(void);

// 中断注册表
void system_register_irqtable(IRQn_Type irqNum, system_irq_handler_t handler, void *userParam);


#endif //__BSP_INTERRUPT_H__
