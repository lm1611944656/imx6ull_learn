#include "bsp_key.h"

/*
 * 因为底板上的按键接在核心板的UART1_CTS引脚上，
 * 所以在fsl_iomuxc.h文件中寻找到到UART1_CTS的GPIO引脚
 *
 * @description	: 初始化按键
 * @param 		: 无
 * @return 		: 无
 */
void key_init(void)
{
    // gpio_pin_config_t key_config;

    /* 1、初始化IO复用, 复用为GPIO1_IO18 */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);

    /* 2、、配置UART1_CTS_B的IO属性
     *bit 16:0 HYS关闭
     *bit [15:14]: 11 默认22K上拉
     *bit [13]: 1 pull功能
     *bit [12]: 1 pull/keeper使能
     *bit [11]: 0 关闭开路输出
     *bit [7:6]: 10 速度100Mhz
     *bit [5:3]: 000 关闭输出
     *bit [0]: 0 低转换率
     */
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xF080);

    /* 3、初始化GPIO */
    GPIO1->GDIR &= ~(1 << 18);	/* GPIO1_IO18设置为输入 */
    //key_config.direction = kGPIO_DigitalInput;
    //gpio_init(GPIO1,18, &key_config);
}

/*
 * @description	: 获取按键值
 * @param 		: 无
 * @return 		: 0 没有按键按下，其他值:对应的按键值
 */
int read_key(void)
{
    int ret = 0;
    ret = (((GPIO1->DR) >> 18) & 0x01);
    return ret;
}

int key_getvalue(void){
    int ret = 0;
    static unsigned char release = 1;       // 为1表示按键释放

    // 如果按键刚才被释放，并且现在读取按键的值为0，表示按键被释放
    if((release == 1) && (read_key() == 0)){
        delay(10);

        // 更新按键状态
        release = 0;

        // 再次判断
        if(read_key() == 0){
            ret = KEY0_VALUE;
        }
    }else if(read_key() == 1){
        ret = KEY_NONE;
        release = 1;
    }

    return ret;
}