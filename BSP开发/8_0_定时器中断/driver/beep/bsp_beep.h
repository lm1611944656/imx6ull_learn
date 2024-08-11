#ifndef __BSP_BEEP_H__
#define __BSP_BEEP_H__

#include "bsp_utils.h"
#include "bsp_gpio.h"

extern void bsp_beep_init(void);

extern void bsp_beep_control(ComponentStatus_T beep_statusT);

#endif // __BSP_BEEP_H__
