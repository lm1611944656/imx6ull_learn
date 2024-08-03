#include "bsp_beep.h"


void bsp_beep_init(void){
    gpio_pin_config_t beep_config;

    // 指定端口
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);

    // 配置端口电气属性
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0x10b0);

    // GPIO5_IO01设置为输出模式
    beep_config.direction = kGPIO_DigitalOutput;

    // GPIO5_IO01设置为高电平，关闭蜂鸣器
    beep_config.outputLogic = 1;

    gpio_init(GPIO5, 1, &beep_config);
}

void bsp_beep_control(ComponentStatus_T beep_statusT){

    if (beep_statusT == ON) {
        // 设置高电平，关闭蜂鸣器
        gpio_pinwrite(GPIO5, 1, 1);
    } else if (beep_statusT == OFF) {
        // 设置低电平，打开蜂鸣器
        gpio_pinwrite(GPIO5, 1, 0);
    }
}
