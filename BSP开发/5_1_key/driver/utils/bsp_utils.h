#ifndef __BSP_UTILS_H__
#define __BSP_UTILS_H__

#include "fsl_iomuxc.h"
#include "fsl_common.h"
#include "MCIMX6Y2.h"
#include "cc.h"

typedef enum{
    OFF = 0,        // 元件的关状态
    ON = 1         // 元件的开状态
} ComponentStatus_T;


#endif // __BSP_UTILS_H__
