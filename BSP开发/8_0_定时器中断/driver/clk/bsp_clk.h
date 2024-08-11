#ifndef __BSP_CLK_H__
#define __BSP_CLK_H__

#include "bsp_utils.h"

/* 初始化外设时钟使能 */
void imx6u_clk_init(void);

/* 使能外设时钟 */
extern void clk_enable(void);

#endif // __BSP_CLK_H__
