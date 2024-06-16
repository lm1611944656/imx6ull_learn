.global _start

_start:

    /*设置处理器进入SVC模式 */
    mrs r0, cpsr                /* 读取cpsr的值到r0 */
    bic r0, r0, #0x1f           /*清除cpsr的bit4--0 与运算 具体参照相关汇编指令*/
    orr r0, r0, #0x13           /* 使用SVC模式   或运算  这是汇编的与运算*/
    msr cpsr, r0                /* 将r0写入到cpsr中去 */

    /*设置SP指针 */
    /*有的芯片比如三星 还要在设置SP指针之前手动初始化DDR和SDRAM
				    前面分析DCD 数据的时候就已经讲过了，DCD数据包含了DDR配置
				    参数，I.MX6U 内部的Boot ROM 会读取DCD 数据中的DDR 配置参数然后完成DDR 初始化的*/
    ldr sp, =0x80200000
    b main                      /* 跳转到C语言main函数 */