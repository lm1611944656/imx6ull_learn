objs := start.o main.o

led.bin:$(objs)
#	arm-linux-gnueabihf-ld -Ttext 0X87800000 $^ -o led.elf
	arm-linux-gnueabihf-ld -Timx6ull_Linker_Script.lds $^ -o led.elf
	arm-linux-gnueabihf-objcopy -O binary -S led.elf $@
	arm-linux-gnueabihf-objdump -D -m arm led.elf > led.dis

%.o:%.s
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

%.o:%.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -O2 -o $@ $<

# 生将正点原子提供的源码文件利用gcc编译成可以将二进制文件下载到SD卡的软件
run:
	gcc imxdownload.c -o  imxdownload

# 利用下载软件将二进制文件下载到SD卡
download:
	./imxdownload led.bin /dev/sdb

clean:
	rm -rf *.o  ledc.bin led.elf ledc.dis led.dis ledc.elf load.imx