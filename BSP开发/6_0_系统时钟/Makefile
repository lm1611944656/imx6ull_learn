CROSS_COMPILE  ?= arm-linux-gnueabihf-
TARGET 		   ?= clk

CC			:= $(CROSS_COMPILE)gcc
LD			:= $(CROSS_COMPILE)ld
OBJCOPY		:= $(CROSS_COMPILE)objcopy
OBJDUMP		:= $(CROSS_COMPILE)objdump

# 指定头文件路径
INCUDIRS	:=  imx6ull \
				driver/utils \
				driver/clk \
				driver/delay \
				driver/gpio \
				driver/led \
				driver/beep \
				driver/key

# 指定源码路径
SRCDIRS		:=  startup \
				project \
				driver/utils \
				driver/clk \
				driver/delay \
				driver/gpio \
				driver/led \
				driver/beep \
				driver/key

# 指定链接脚本路径
SCRIPTPATH		:= script

# 在文本$(INCUDIRS)中，寻找样式 % 的东西，全部替换为 -I % 的样式
INCLUDE		:= $(patsubst %, -I %, $(INCUDIRS))

# 找到所有源文件和汇编文件，并且包含相对路径
# $(foreach dir, $(SRCDIRS))   表式遍历$(SRCDIRS)，遍历出来的内容放入到dir保存
# $(wildcard $(dir)/*.s)	   表示遍历$(dir)下的所有汇编文件，放置在SFILES中
SFILES		:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
CFILES		:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

# 找到所有源文件和汇编文件，不包含相对路径，只是文件名
SFILENDIR	:= $(notdir $(SFILES))
CFILENDIR	:= $(notdir $(CFILES))

# 将汇编文件和源文件替换为目标文件
# 在$(SFILENDIR)中，将符合%.s的文件全部替换为%.o文件，并且放入到obj文件夹下
SOBJS		:= $(patsubst %.s, obj/%.o, $(SFILENDIR))
COBJS		:= $(patsubst %.c, obj/%.o, $(CFILENDIR))

# 指定交叉编译器需要搜索的文件路径
VPATH		:= $(SRCDIRS)

# 将所有目标文件汇聚在一起
OBJS         := $(SOBJS)$(COBJS)

# 获取链接脚本文件
SCRIPTFILE   := $(wildcard $(SCRIPTPATH)/*.lds)

# 定义伪目标
.PHONY:clean run download

# 开始配置
$(TARGET).bin : $(OBJS)
	@$(LD) -T $(SCRIPTFILE) $^ -o $(TARGET).elf		# 将依赖文件链接上脚本后，输出为可执行文件
	@$(OBJCOPY)	-O binary -S $(TARGET).elf $@		# 将可执行文件转换为二进制文件，并且(-S)去除所有调试信息
	@$(OBJDUMP)	-D -m arm $(TARGET).elf > $(TARGET).dis		# 将可执行文件转换为反汇编文件(-D 表示对整个文件进行反汇编; -m arm 这个选项告诉objdump以ARM指令集的方式进行反汇编)
	@echo "编译成功！"

# 将依赖文件转换为目标文件
$(SOBJS) : obj/%.o : %.s
	@$(CC) -Wall -nostdlib -c -O2 $(INCLUDE)	-o $@ $<

$(COBJS) : obj/%.o : %.c
	@$(CC) -Wall -nostdlib -c -O2 $(INCLUDE)	-o $@ $<

print:
	@echo INCLUDE = $(INCLUDE)
	@echo SFILES = $(SFILES)
	@echo CFILESS = $(CFILES)
	@echo SFILENDIR = $(SFILENDIR)
	@echo CFILENDIR = $(CFILENDIR)
	@echo SOBJS = $(SOBJS)
	@echo COBJS = $(COBJS)
	@echo OBJS = $(OBJS)
	@echo SCRIPTFILE = $(SCRIPTFILE)
	@echo SCRIPTFILE1 = $(SCRIPTFILE1)


clean:
	rm -rf $(TARGET).elf $(TARGET).bin $(TARGET).dis $(OBJS)	.clion.source.upload.marker cmake-build-debug

# 生将正点原子提供的源码文件利用gcc编译成可以将二进制文件下载到SD卡的软件
run:
	@mkdir ./obj
	gcc ./download_app/imxdownload.c  -o  imxdownload

# 利用下载软件将二进制文件下载到SD卡
download:
	./imxdownload $(TARGET).bin /dev/sdb