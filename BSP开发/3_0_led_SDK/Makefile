CROSS_COMPILE  ?= arm-linux-gnueabihf-
NAME 		   ?= ledc

CC 			   := $(CROSS_COMPILE)gcc		# 交叉编译器
LD			   := $(CROSS_COMPILE)ld		# 链接编译器
OBJCOPY		   := $(CROSS_COMPILE)objcopy
OBJDUMP		   := $(CROSS_COMPILE)objdump

OBJS           := start.o  main.o

$(NAME).bin : $(OBJS)
	$(LD) -Timx6ull_Linker_Script.lds $^ -o $(NAME).elf
	$(OBJCOPY) -O binary -S $(NAME).elf $@					# 将elf文件转换为bin文件
	$(OBJDUMP) -D -m arm $(NAME).elf > $(NAME).dis

%.o : %.c
	$(CC) -Wall -nostdlib -c -O2 -o $@  $<

%.o : %.s
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<

clean:
	rm -rf *.o $(NAME).elf $(NAME).bin $(NAME).dis

# 生将正点原子提供的源码文件利用gcc编译成可以将二进制文件下载到SD卡的软件
run:
	gcc imxdownload.c -o  imxdownload

# 利用下载软件将二进制文件下载到SD卡
download:
	./imxdownload $(NAME).bin /dev/sdb