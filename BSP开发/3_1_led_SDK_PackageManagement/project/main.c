#include "main.h"


int main(void)
{
    clk_enable();
    led_init();
    while(1)
    {
        led_off();
        delay(100);

        led_on();
        delay(100);
    }
}
