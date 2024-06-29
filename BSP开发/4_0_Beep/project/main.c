#include "main.h"


int main(void)
{
    // 打开所有端口时钟
    clk_enable();

    // led灯初始化
    led_init();

    // 蜂鸣器初始化
    bsp_beep_init();

    while (1) {
        bsp_led_control(OFF);
        bsp_beep_control(OFF);
        delay(100);

        bsp_led_control(ON);
        bsp_beep_control(ON);
        delay(100);
    }
}
