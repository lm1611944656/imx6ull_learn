/*
    定义伪目标
*/

.global _start

@ 函数入口地址
_start:
    /* 使能所有外设寄存器 */
    LDR R0, =0x020C4068          @ 读取CCGR0寄存器中的数据
    LDR R1, =0xFFFFFFFF          @ 寄存器中需要写入的数据
    STR R1, [R0]                @ 将数据写入到0x020C4068寄存器中

    LDR R0, =0x020C406C          @ 读取CCGR1寄存器中的数据
    STR R1, [R0]                @ 将数据写入到0x020C406C寄存器中

    LDR R0, =0x020C4070          @ 读取CCGR2寄存器中的数据
    STR R1, [R0]                @ 将数据写入到0x020C4070寄存器中

    LDR R0, =0x020C4074          @ 读取CCGR3寄存器中的数据
    STR R1, [R0]                @ 将数据写入到0x020C4074寄存器中

    LDR R0, =0x020C4078          @ 读取CCGR4寄存器中的数据
    STR R1, [R0]                @ 将数据写入到0x020C4078寄存器中

    LDR R0, =0x020C4080          @ 读取CCGR5寄存器中的数据
    STR R1, [R0]                @ 将数据写入到0x020C4080寄存器中


	/* 因为LED0挂载到GPIO1_IO03，所以需要设置GPIO1_IO03。设置复用功能为通用的GPIO模式 */
	LDR R0, =0X020E0068	        /* 将寄存器SW_MUX_GPIO1_IO03_BASE加载到r0中 */
	LDR R1, =0X5		        /* 设置寄存器SW_MUX_GPIO1_IO03_BASE的MUX_MODE为5 */
	STR R1, [R0]

	/* 3、配置GPIO1_IO03的IO电气属性属性
	 *bit 16:0      HYS关闭
	 *bit [15:14]:  00 默认下拉
     *bit [13]:     0 kepper功能
     *bit [12]:     1 pull/keeper使能
     *bit [11]:     0 关闭开路输出
     *bit [7:6]:    10 速度100Mhz
     *bit [5:3]:    110 R0/6驱动能力
     *bit [0]:      0 低转换率
     */
    LDR R0, =0X020E02F4	/*寄存器SW_PAD_GPIO1_IO03_BASE */
    LDR R1, =0X10B0
    STR R1, [R0]

	/* 4、设置GPIO1_IO03为输出模式 */
    LDR R0, =0X0209C004	/*寄存器GPIO1_GDIR */
    LDR R1, =0X0000008
    STR R1, [R0]

	/* 5、打开LED0
	 * 设置GPIO1_IO03输出低电平
	 */
@    LDR R0, =0X0209C000     	/* 寄存器GPIO1_DR的地址 */
@    LDR R1, =0                  @ 寄存器中需要写入的数据为0x0000 0000
@    STR R1, [R0]

/* 描述: loop死循环(不断的在以下两行代码中跳转，达到循环的目的) */
@loop:
@	b loop

loop:
    /* 5、打开LED0
     * 设置GPIO1_IO03输出低电平
     */
    LDR R0, =0X0209C000          /* 寄存器GPIO1_DR的地址 */
    LDR R1, =0X00000000          @ 寄存器中需要写入的数据为0x0000 0000
    STR R1, [R0]

    /* 延时循环 */
    LDR R2, =0x100000            @ 设置延时时间
delay1:
    SUBS R2, R2, #1              @ 递减计数器
    BNE delay1                   @ 如果计数器不为0，继续延时

    /* 关闭LED0
     * 设置GPIO1_IO03输出高电平
     */
    LDR R0, =0X0209C000          /* 寄存器GPIO1_DR的地址 */
    LDR R1, =0X00000008          @ 寄存器中需要写入的数据为0x0000 0008
    STR R1, [R0]

    /* 延时循环 */
    LDR R2, =0x100000            @ 设置延时时间
delay2:
    SUBS R2, R2, #1              @ 递减计数器
    BNE delay2                   @ 如果计数器不为0，继续延时

    B loop                       @ 重复循环

