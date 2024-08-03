/* 相当于C语言定义宏，注意是一个杠，下面是两个杠 */
.global _start

_start:
/************************中断向量表***************************/
    ldr pc, =Reset_Handler /* 复位中断服务函数 */
    ldr pc, =Undefined_Handler /* 未定义指令中断服务函数 */
    ldr pc, =SVC_Handler /* SVC(Supervisor)中断服务函数 */
    ldr pc, =PrefAbort_Handler /* 预取终止中断服务函数 */
    ldr pc, =DataAbort_Handler /* 数据终止中断服务函数 */
    ldr pc, =NotUsed_Handler /* 未使用中断服务函数 */
    ldr pc, =IRQ_Handler /* IRQ 中断服务函数 */
    ldr pc, =FIQ_Handler /* FIQ(快速中断)未定义中断服务函数 */
/************************end****************************************/

/* 复位中断服务函数实现 */
Reset_Handler:
/************************关闭全局中断********************************/
    cpsid i         // 关闭IRQ
/************************end****************************************/

/************************中断向量表****************************************/
    /* 关闭I,D Cache和MMU   其实内部bootroom已经帮我们完成了 我们自己再实现一遍
     * 修改CP15协处理器的 SCTLR寄存器 采取读-改-写的方式。
     */
    mrc     p15, 0, r0, c1, c0, 0     /* 读取CP15协处理器的C1寄存器到R0中       		        	*/
    bic     r0,  r0, #(0x1 << 12)     /* 清除C1寄存器的bit12位(I位)，关闭I Cache            	*/
    bic     r0,  r0, #(0x1 <<  2)     /* 清除C1寄存器的bit2(C位)，关闭D Cache    				*/
    bic     r0,  r0, #0x2             /* 清除C1寄存器的bit1(A位)，关闭对齐						*/
    bic     r0,  r0, #(0x1 << 11)     /* 清除C1寄存器的bit11(Z位)，关闭分支预测 分支预测对了 提前运行缓存*/
    bic     r0,  r0, #0x1             /* 清除C1寄存器的bit0(M位)，关闭MMU				       	*/
    mcr     p15, 0, r0, c1, c0, 0     /* 将r0寄存器中的值写入到CP15的C1寄存器中	 				*/
/************************end****************************************/

/************************设置中断向量的偏移(在C语言中已经设置)****************************************/
 #if 0
    ldr r0, =0X87800000             //链接首地址
    dsb                             /* 指令、数据同步的指令(确保前面的指令执行完毕) */
    isb
    mcr p15, 0, r0, c12, c0, 0
    dsb
    isb
 #endif
/************************end****************************************/

/************************清除bss段****************************************/
.global _bss_start
_bss_start:
.word __bss_start  /* 相当于C语言里的变量，.word表示在这里放了一个变量，__bss_start就是这个变量的标签，类似变量名 */

.global _bss_end
_bss_end:
.word __bss_end


/* 清除bss段，bss段是定义但是没有初始化的变量，最好全部清零 */
    ldr r0, =_bss_start /* 加载_bss_start的地址到r0 */
    ldr r1, =_bss_end   /* 加载_bss_end的地址到r1 */
    mov r2, #0          /* 将r2置零，用于清除bss段 */
bss_loop:               /* 循环清除bss段 */
    stmia r0!, {r2}     /* 存储指令，将r2的值（0）存储到r0指向的位置，r0自动增加 */
    cmp r0, r1          /* 比较r0和r1 */
    ble bss_loop        /* 如果r0小于等于r1，跳转到bss_loop继续清除bss段 */

/************************end****************************************/

/************************设置工作模式****************************************/
	/* 设置处理器进入IRQ模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1f 	/* 将r0寄存器中的低5位清零，也就是cpsr的M0~M4 	*/
	orr r0, r0, #0x12 	/* r0或上0x13,表示使用IRQ模式					*/
	msr cpsr, r0		/* 将r0 的数据写入到cpsr_c中 					*/
	ldr sp, =0x80600000	/* 设置IRQ模式下的栈（SP）首地址为0X80600000,大小为2MB */

	/* 设置处理器进入SYS模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1f 	/* 将r0寄存器中的低5位清零，也就是cpsr的M0~M4 	*/
	orr r0, r0, #0x1f 	/* r0或上0x13,表示使用SYS模式					*/
	msr cpsr, r0		/* 将r0 的数据写入到cpsr_c中 					*/
	ldr sp, =0x80400000	/* 设置SYS模式下的栈（SP）首地址为0X80400000,大小为2MB */

	/* 设置处理器进入SVC模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1f 	/* 将r0寄存器中的低5位清零，也就是cpsr的M0~M4 	*/
	orr r0, r0, #0x13 	/* r0或上0x13,表示使用SVC模式					*/
	msr cpsr, r0		/* 将r0 的数据写入到cpsr_c中 					*/
	ldr sp, =0X80200000	/* 设置SVC模式下的栈（SP）首地址为0X80200000,大小为2MB */
/************************end****************************************/

/************************打开全局中断********************************/
    cpsie i             // 打开IRQ
/************************end****************************************/

/************************跳转到C语言main函数**************************/
    b main
/************************end****************************************/

/* 未定义指令中断服务函数实现    都写成死循环*/
 Undefined_Handler:
    ldr r0, =Undefined_Handler
    bx r0

/* SVC 中断 */
SVC_Handler:
    ldr r0, =SVC_Handler
    bx r0

/* 预取终止中断 */
PrefAbort_Handler:
    ldr r0, =PrefAbort_Handler
    bx r0

/* 数据终止中断 */
DataAbort_Handler:
    ldr r0, =DataAbort_Handler
    bx r0

/* 未使用的中断 */
NotUsed_Handler:

    ldr r0, =NotUsed_Handler
    bx r0

 /* IRQ 中断！重点！！！！！ 所有外设发生中断，都会触发IRQ_Handler函数*/
IRQ_Handler:
    push {lr}					/* 入栈 保存lr地址 退出的时候要接着被中断的地方接着运行*/
	push {r0-r3, r12}			/* 保存内部r0-r3，r12寄存器 其他的寄存器在中断机制下自动保存了*/

	mrs r0, spsr				/* 读取spsr寄存器到RO */
	push {r0}					/* 压栈保存spsr寄存器 */

	mrc p15, 4, r1, c15, c0, 0 /* 从协处理器CP15的C0寄存器内的值到R1寄存器中
								* 参考文档ARM Cortex-A(armV7)编程手册V4.0.pdf P49
								* Cortex-A7 Technical ReferenceManua.pdf P68 P138
								这个C0寄存器读取CBAR寄存器放到R1寄存器，CBAR寄存器保存了GIC控制器寄存器组首地址*/

	add r1, r1, #0X2000			/* GIC基地址加0X2000，也就是GIC的CPU接口端基地址(查手册) */
	ldr r0, [r1, #0XC]			/* GIC的CPU接口端基地址加0X0C就是GICC_IAR寄存器，将其保存到R0寄存器
								 * GICC_IAR寄存器保存这当前发生中断的中断号，我们要根据
								 * 这个中断号来绝对调用哪个中断服务函数
								   其实还保存了CPU的ID，多核多CPU，这里不用关心*/

	push {r0, r1}				/* 保存r0,r1 */

	cps #0x13					/* 进入SVC模式，后面要运行C程序，其他的中断也可以继续发生了 */

	push {lr}					/* 保存SVC模式的lr寄存器 */
	ldr r2, =system_irqhandler	/* 加载C语言中断处理函数到r2寄存器中 最终目的就是这个 注意不要放到R0和R1里，已经被使用了*/
	blx r2						/* 跳转到R2执行C程序
	                               这是汇编和C混合编程 C语言中断处理函数在bsp_int.c里实现
	                               这个C程序带有一个参数，这个参数保存在R0寄存器中(中断号) */

	pop {lr}					/* 执行完C语言中断服务函数，lr出栈 */
	cps #0x12					/* 重新进入到IRQ模式  前面中断处理函数结束重新返回到IRQ模式*/
	pop {r0, r1}
	str r0, [r1, #0X10]			/* 中断执行完成，将R0保存的中断ID值写到EOIR寄存器里面(手册上要求的) */

	pop {r0}
	msr spsr_cxsf, r0			/* 恢复spsr */

	pop {r0-r3, r12}			/* r0-r3,r12出栈 */
	pop {lr}					/* lr出栈 */
	subs pc, lr, #4				/* 将lr-4赋给pc   三级流水线结构要求减4*/

FIQ_Handler:
    ldr r0, =FIQ_Handler
    bx r0


