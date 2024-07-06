#ifndef __BSP_DELAY_H__
#define __BSP_DELAY_H__

/*短延时*/
extern void delay_short(volatile unsigned int n);

/*
 * 延时  一次循环大概是1ms 在主频396MHz
 * n:延时ms数
*/
extern void delay(volatile unsigned int n);

#endif // __BSP_DELAY_H__
