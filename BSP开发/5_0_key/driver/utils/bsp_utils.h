#ifndef __BSP_UTILS_H__
#define __BSP_UTILS_H__

#include "../../imx6ull/fsl_iomuxc.h"
#include "../../imx6ull/fsl_common.h"
#include "../../imx6ull/MCIMX6Y2.h"
#include "../../imx6ull/cc.h"

typedef enum{
    OFF = 0,        // 元件的关状态
    ON = 1         // 元件的开状态
} ComponentStatus_T;


#endif // __BSP_UTILS_H__
