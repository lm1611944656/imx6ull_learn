#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "bsp_utils.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"

// 定义按键编码(每一个按键都有自己的编码)
enum keyvalue{
    KEY_NONE = 0,     // 没有按键按下
    KEY0_VALUE,         // 按键1按下
    KEY1_VALUE,         // 按键2按下
    KEY2_VALUE,         // 按键3按下
};

/* 按键初始化 */
extern void key_init(void);

// 查询方式判断按键按键的状态
extern int key_getvalue(void);

#endif // __BSP_KEY_H__
