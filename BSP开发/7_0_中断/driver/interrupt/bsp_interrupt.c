#include "bsp_interrupt.h"

// 记录中断嵌套的个数
static unsigned int irqNesting;

// 中断处理函数表(用于存储不同外设的中断函数)
static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS];

// 中断处理函数表的初始化
void system_irqtable_init(void){
    unsigned int i = 0;

    // 中断嵌套计数器清除
    irqNesting = 0;

    for(i = 0; i < NUMBER_OF_INT_VECTORS; i++){
        irqTable[i].irqHandle = default_irqHandler;
        irqTable[i].userParam = NULL;
    }
}

// 中断处理函数表的注册
void system_register_irqtable(IRQn_Type irqNum, system_irq_handler_t handler, void *userParam){
    irqTable[irqNum].irqHandle = handler;
    irqTable[irqNum].userParam = userParam;
}

void int_init(void){
    // 中断控制器初始化(和STM32的NVIC一样)
    GIC_Init();

    // 中断处理函数表的初始化
    system_irqtable_init();

    // 设置中断偏移地址
    __set_VBAR(0x87800000);
}

// 系统的中断处理函数(根据中断号去中断处理函数表中查找)
void system_irqhandler(unsigned int gicciar){
    uint32_t intNum = gicciar & 0x3FF;

    // 中断号有效性判断
    if((gicciar == 1023) || (gicciar >= NUMBER_OF_INT_VECTORS)){
        return;
    }

    // 表示有一个中断正在处理
    irqNesting++;

    // 根据中断ID, 读取中断处理函数
    irqTable[intNum].irqHandle(intNum, irqTable[intNum].userParam);

    // 中断处理完之后，将中断计数器减1
    irqNesting--;
}

void default_irqHandler(unsigned int gicciar, void *param){
    while (1){

    }
}