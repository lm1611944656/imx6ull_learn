#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "../utils/bsp_utils.h"

/*初始化LED灯*/
extern void led_init(void);

/*打开LED灯*/
extern void  led_on(void);

/*关闭LED灯*/
extern void led_off(void);

extern void bsp_led_control(ComponentStatus_T ledStatus_T);
#endif // __BSP_LED_H__
