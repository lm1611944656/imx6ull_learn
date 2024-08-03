#include "main.h"


int main(void)
{
    int i = 0;
    // led的状态
    unsigned char led_state = OFF;

    // 蜂鸣器的状态
    unsigned char beep_state = OFF;

    // 中断初始化
    int_init();

    // 初始化系统时钟
    imx6u_clk_init();

    // 打开所有端口时钟
    clk_enable();

    // led灯初始化
    led_init();

    // 蜂鸣器初始化
    bsp_beep_init();

    // 按键初始化
    // key_init();

    // 按键初始化
    key_interrupt_init();

    while (1) {

//        bsp_led_control(OFF);
//        bsp_beep_control(OFF);
//        delay(100);
//
//        bsp_led_control(ON);
//        bsp_beep_control(ON);
//        delay(100);

        // 判断按键的中断标志位
        if(keyFlag == 1){
            // 清除按键中断标志位
            keyFlag = 0;

            // 执行业务逻辑
            beep_state = !beep_state;
            bsp_beep_control(beep_state);
        }

        // 每500ms led的状态反转一次
        i++;
        if(i == 50){
            i = 0;

            // led的状态反转
            led_state = !led_state;

            bsp_led_control(led_state);
        }
        delay(10);
    }
}
