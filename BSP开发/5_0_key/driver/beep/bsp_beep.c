#include "bsp_beep.h"


void bsp_beep_init(void){

    // 指定端口
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);

    // 配置端口电气属性
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0x10b0);

    // GPIO5_IO01设置为输出模式
    GPIO5->GDIR |= (1<<1);

    // GPIO5_IO01设置为高电平，关闭蜂鸣器
    GPIO5->DR |= (1<<1);
}

void bsp_beep_control(ComponentStatus_T beep_statusT){

    if (beep_statusT == ON) {
        // 设置高电平，关闭蜂鸣器
        GPIO5->DR |= (1 << 1);
    } else if (beep_statusT == OFF) {
        // 设置低电平，打开蜂鸣器
        GPIO5->DR &= ~(1 << 1);
    }
}
