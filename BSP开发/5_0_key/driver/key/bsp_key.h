#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "../utils/bsp_utils.h"
#include "../driver/delay/bsp_delay.h"
//#include "../driver/gpio/bsp_gpio.h"

// 定义按键编码(每一个按键都有自己的编码)
enum keyvalue{
    KEY_NONE   = 0,     // 没有按键按下
    KEY0_VALUE,         // 按键1按下
    KEY1_VALUE,         // 按键2按下
    KEY2_VALUE,         // 按键3按下
};

/* 函数声明 */
extern void key_init(void);
extern int read_key(void);
extern int key_getvalue(void);

#endif // __BSP_KEY_H__
