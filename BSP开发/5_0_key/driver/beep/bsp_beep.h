#ifndef __BSP_BEEP_H__
#define __BSP_BEEP_H__

#include "../utils/bsp_utils.h"

extern void bsp_beep_init(void);

extern void bsp_beep_control(ComponentStatus_T beep_statusT);

#endif // __BSP_BEEP_H__
