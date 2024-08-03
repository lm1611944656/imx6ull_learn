#include "bsp_key_interrupt.h"

volatile unsigned char keyFlag = 0;

void key_interrupt_init(void){
    gpio_pin_config_t key_config;

    /* 1、初始化IO复用, 复用为GPIO1_IO18 */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);

    /* 2、配置UART1_CTS_B的IO属性 */
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    /* 3、初始化GPIO */
    key_config.direction = kGPIO_DigitalInput;          // GPIO的输入输出方向初始化
    key_config.interruptMode = kGPIO_IntFallingEdge;    // GPIO的中断触发方式
    gpio_init(GPIO1, 18, &key_config);

    /* 4、中断控制器(GIC)的使能 */
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);           // 由于按键接在GPIO1的18号引脚

    /* 5、中断注册表注册中断函数 */
    system_register_irqtable(GPIO1_Combined_16_31_IRQn, gpio1_io18_irqHandler, NULL);

    /* 6、GPIO1的中断使能 */
    gpio_enableint(GPIO1, 18);
}

void gpio1_io18_irqHandler(unsigned int gicciar, void *param){
    /* 1、禁用当前引脚的中断，避免中断嵌套或重复触发 */
    gpio_disableint(GPIO1, 18);

    /* 2、中断消抖 */
    delay(10);

    /* 3、再次判断引脚状态 */
    if(gpio_pinread(GPIO1, 18) == 0){
        keyFlag = 1;  // 设置按键中断标志位
    }

    /* 4、清除中断标志位 */
    gpio_clearintflags(GPIO1, 18);

    /* 5、重新使能当前引脚的中断 */
    gpio_enableint(GPIO1, 18);
}
