#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "../../imx6ull/fsl_iomuxc.h"
#include "../../imx6ull/fsl_common.h"
#include "../../imx6ull/MCIMX6Y2.h"

#define LED0            0

/*初始化LED灯*/
extern void led_init(void);

/*打开LED灯*/
extern void  led_on(void);

/*关闭LED灯*/
extern void led_off(void);

extern void led_switch(int led, int status);
#endif // __BSP_LED_H__
