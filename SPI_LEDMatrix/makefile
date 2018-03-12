INCLUDE_PATH=./header/

PREFIX=/usr/bin
CC=$(PREFIX)/arm-linux-gnueabihf-g++-6
LD=$(PREFIX)/arm-linux-gnueabihf-ld

CFLAGS= -g -I$(INCLUDE_PATH)
LIBS =-lwiringPi
 
SPI_LED_Matrix_Test : SPI_LED_Matrix.o
	$(CC) -o SPI_LED_Matrix_Test SPI_LED_Matrix.o $(LIBS)

SPI_LED_Matrix.o : SPI_LED_Matrix.cpp
	$(CC) -o SPI_LED_Matrix.o -c SPI_LED_Matrix.cpp

.PHONY: clean
clean :
	rm -f *.o
