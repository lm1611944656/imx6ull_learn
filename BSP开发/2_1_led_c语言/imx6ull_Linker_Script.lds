/* 定义各个段的内存布局 */
SECTIONS
{
    /* 设置内存起始地址为 0x87800000 */
    . = 0x87800000;

    /* 定义 .text 段 */
    .text :
    {
        /* 包含 start.o 文件中的 .text 段 */
        start.o (.text)
        /* 包含所有其他目标文件中的 .text 段 */
        *(.text)
    }

    /* 定义 .rodata（只读数据）段，并对齐到 4 字节 */
    .rodata ALIGN(4) :
    {
        /* 包含所有目标文件中的 .rodata* 段 */
        *(.rodata*)
    }

    /* 定义 .data 段，并对齐到 4 字节 */
    .data ALIGN(4) :
    {
        /* 包含所有目标文件中的 .data 段 */
        *(.data)
    }

    /* 定义 .bss 段（未初始化数据）的起始地址 */
    __bss_start = .;

    /* 定义 .bss 段，并对齐到 4 字节 */
    .bss ALIGN(4) :
    {
        /* 包含所有目标文件中的 .bss 段 */
        *(.bss)
        /* 包含所有目标文件中的 COMMON 段 */
        *(COMMON)
    }

    /* 定义 .bss 段的结束地址 */
    __bss_end = .;
}
