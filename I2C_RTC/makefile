PREFIX=/usr/bin
CC=$(PREFIX)/arm-linux-gnueabihf-gcc-6
LD=$(PREFIX)/arm-linux-gnueabihf-ld

CFLAGS= -g -Wall
OBJS= I2C.o RTC.o 2837mmu.o
 
RTC_Read : $(OBJS)
	$(CC) -o $@ $^

.PHONY: clean
clean :
	rm -f *.o
