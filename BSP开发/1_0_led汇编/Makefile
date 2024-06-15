led.bin:start.s
	@arm-linux-gnueabihf-gcc -g -c start.s -o led.o					# 将汇编文件转换为目标文件
	@arm-linux-gnueabihf-ld -Ttext 0X87800000 led.o -o led.elf		# 将目标文件链接到指定位置，并且输出为unix下的可执行文件
	@arm-linux-gnueabihf-objcopy -O binary -S -g led.elf led.bin		# 将可执行文件转换为二进制文件
	@arm-linux-gnueabihf-objdump -D led.elf > led.dis				# 将可执行文件转换为反汇编文件

# 生将正点原子提供的源码文件利用gcc编译成可以将二进制文件下载到SD卡的软件
run:
	gcc imxdownload.c -o  imxdownload

# 利用下载软件将二进制文件下载到SD卡
download:
	./imxdownload led.bin /dev/sdb

# 清理指定文件
clean:
	rm -rf *.o led.bin led.elf led.dis imxdownload load.imx