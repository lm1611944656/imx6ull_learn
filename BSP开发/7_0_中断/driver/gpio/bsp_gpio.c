#include "bsp_gpio.h"


/*
 * @description		: GPIO初始化。
 * @param - base	: 要初始化的GPIO组。
 * @param - pin		: 要初始化GPIO在组内的具体哪个引脚。
 * @param - config	: GPIO配置结构体。
 * @return 			: 无
 */
void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config){

	if(config->direction == kGPIO_DigitalInput){
        // 如果是输入模式，需要将GPIO的GDIR寄存器写0
		base->GDIR &= ~( 1 << pin);
	}else{
        // 如果需要是输出模式，需要将GPIO的GDIR寄存器写1
		base->GDIR |= 1 << pin;

        /* 设置默认输出电平 */
		gpio_pinwrite(base, pin, config->outputLogic);
	}

    // 中断模式初始化
    gpio_intconfig(base, pin, config->interruptMode);
}

 /*
  * @description	 : 读取指定GPIO的电平值 。
  * @param - base	 : 要读取的GPIO组。
  * @param - pin	 : 要读取的GPIO脚号。
  * @return 		 : 无
  */
int gpio_pinread(GPIO_Type *base, int pin)
 {
	 return (((base->DR) >> pin) & 0x1);
 }

 /*
  * @description	 : 指定GPIO输出高或者低电平 。
  * @param - base	 : 要输出的的GPIO组。
  * @param - pin	 : 要输出的GPIO脚号。
  * @param - value	 : 要输出的电平，1表示输出高电平， 0表示输出低低电平
  * @return 		 : 无
  */
void gpio_pinwrite(GPIO_Type *base, int pin, int value)
{
	 if (value == 0U)
	 {
		 base->DR &= ~(1U << pin); /* 输出低电平 */
	 }
	 else
	 {
		 base->DR |= (1U << pin); /* 输出高电平 */
	 }
}


void gpio_enableint(GPIO_Type* base, unsigned int pin){
    // 使能中断需要使用IMR寄存器, 并且IMR寄存器的每一位表示一个IO
    base->IMR |= (1 << pin);
}

// 关闭GPIO的中断
void gpio_disableint(GPIO_Type* base, unsigned int pin){
    // 将IMR寄存器的某一个位清除
    base->IMR &= ~(1 << pin);
}

// 清除GPIO的中断
void gpio_clearintflags(GPIO_Type* base, unsigned int pin){
    // 清除中断标志位需要使用寄存器ISR
    base->ISR |= (1 << pin);
}


/*GPIO中断初始化函数
 * @description  			: 设置GPIO的中断配置功能
 * @param - base 			: 要配置的IO所在的GPIO组。
 * @param - pin  			: 要配置的GPIO脚号。
 * @param - pinInterruptMode: 中断模式，参考枚举类型gpio_interrupt_mode_t
 * @return		 			: 无
 */
void gpio_intconfig(GPIO_Type* base, unsigned int pin, gpio_interrupt_mode_t pin_int_mode)
{

    // 中断配置需要使用到GPIO中的ICR寄存器
    volatile uint32_t *icr;
    uint32_t icrShift;

    icrShift = pin;

    base->EDGE_SEL &= ~(1U << pin);//EDGE_SEL寄存器要清零，否则ICR寄存器无效(手册上有讲)

    if(pin < 16) 	/* 低16位 */  //不同的引脚使用不同的ICR寄存器
    {
        icr = &(base->ICR1);
    }
    else			/* 高16位 */
    {
        icr = &(base->ICR2);
        icrShift -= 16;  //ICR使用0~15来操作
    }
    switch(pin_int_mode)
    {
        case(kGPIO_IntLowLevel)://低电平触发
            *icr &= ~(3U << (2 * icrShift));//同时操作两个位，我们操作寄存器大部分都是一位一位操作的
            break;
        case(kGPIO_IntHighLevel)://高电平触发
            *icr = (*icr & (~(3U << (2 * icrShift)))) | (1U << (2 * icrShift));
            break;           //清零
        case(kGPIO_IntRisingEdge)://上升沿触发
            *icr = (*icr & (~(3U << (2 * icrShift)))) | (2U << (2 * icrShift));
            break;           //清零
        case(kGPIO_IntFallingEdge)://下降沿触发
            *icr |= (3U << (2 * icrShift));
            break;
        case(kGPIO_IntRisingOrFallingEdge)://跳变沿触发
            base->EDGE_SEL |= (1U << pin);
            break;
        default:
            break;
    }
}
