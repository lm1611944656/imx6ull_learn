#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__


#include "bsp_utils.h"

#define _BSP_KEY_H

/* GPIO的输入和输出定义 */
typedef enum _gpio_pin_direction
{
    kGPIO_DigitalInput = 0U,  		/* 输入 */
    kGPIO_DigitalOutput = 1U, 		/* 输出 */
} gpio_pin_direction_t;
	

typedef struct _gpio_pin_config
{
    gpio_pin_direction_t direction; /* GPIO方向:输入还是输出 */
    uint8_t outputLogic;            /* 如果是输出的话，默认输出电平 */
} gpio_pin_config_t;


/* 函数声明 */
extern void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config);
extern int gpio_pinread(GPIO_Type *base, int pin);
extern void gpio_pinwrite(GPIO_Type *base, int pin, int value);

#endif
