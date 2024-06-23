.global _start

/* 相当于C语言定义宏，注意是一个杠，下面是两个杠 */
.global _bss_start
_bss_start:
    .word __bss_start  /* 相当于C语言里的变量，.word表示在这里放了一个变量，__bss_start就是这个变量的标签，类似变量名 */

.global _bss_end
_bss_end:
    .word __bss_end

_start:

    /* 设置处理器进入SVC模式 */
    mrs r0, cpsr      /* 读取cpsr到r0 */
    bic r0, r0, #0x1f /* 清除cpsr的bit4到bit0 */
    orr r0, r0, #0x13 /* 使用SVC模式 */
    msr cpsr, r0      /* 将r0写入到cpsr中 */

    /* 清除bss段，bss段是定义但是没有初始化的变量，最好全部清零 */
    ldr r0, =_bss_start /* 加载_bss_start的地址到r0 */
    ldr r1, =_bss_end   /* 加载_bss_end的地址到r1 */
    mov r2, #0          /* 将r2置零，用于清除bss段 */

bss_loop:               /* 循环清除bss段 */
    stmia r0!, {r2}     /* 存储指令，将r2的值（0）存储到r0指向的位置，r0自动增加 */
    cmp r0, r1          /* 比较r0和r1 */
    ble bss_loop        /* 如果r0小于等于r1，跳转到bss_loop继续清除bss段 */

    /* 设置SP指针 */
    ldr sp, =0x80200000 /* 将SP指针设置为0x80200000 */
    b main              /* 跳转到C语言main函数 */
