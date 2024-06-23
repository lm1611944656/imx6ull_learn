#include "bsp_led.h"
#include "../../imx6ull/cc.h"


/*初始化LED灯*/
void led_init(void)
{
    /*复用为GPIO--IO03 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);

    /*设置GPIO__IO03电器属性*/
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0x10B0);

    //设置为输出
    GPIO1->GDIR=0x8;

    //设置为低电平，打开LED灯
    GPIO1->DR=0x0;
}

/*打开LED灯*/
void  led_on(void)
{
    GPIO1->DR &= ~(1<<3); //bit3清零

}

/*关闭LED灯*/
void led_off(void )
{
    GPIO1->DR |= (1<<3);  //bit3置1
}

/* led灯的切换*/
void led_switch(int led, int status){
    switch (status) {
        // led0的判断
        case LED0:
            if(status == ON){
                GPIO1->DR &= ~(1<<3); //bit3清零
            }else if(status == OFF){
                GPIO1->DR |= (1<<3);  //bit3置1
            }
            break;
        default:
            break;
    }

}