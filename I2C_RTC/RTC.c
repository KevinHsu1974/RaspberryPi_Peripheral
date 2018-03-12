//  Read RTC via I2C: Test Program for Raspberry-Pi 3
//  23-Dec-2017
//  Kevin Hsu
// --------------------------------------------------------------------
//
//   Title     :  RTC.c
//             :
//   Library   :
//             :
//   Developers:  Kevin Hsu
//             :
//   Purpose   :  RaspberryPi 3 "B" RTC/I2C testing
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 13-Dec-2017 | Programming Start


#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include "RPI3.h"
#include "2837mmu.h"
#include "I2C.h"
 
struct bcm2837_peripheral gpio = {GPIO_BASE};             //Declare GPIO mmap structure
struct bcm2837_peripheral bsc0 = {BSC0_BASE};            //Declare BSC0 mmap structure for I2C
struct tm t;                                                                        // Declare time structure to store time infomation

unsigned int bcd_to_decimal(unsigned int bcd) {             // Function to convert BCD to decimal value
    return ((bcd & 0xf0) >> 4) * 10 + (bcd & 0x0f);
}
unsigned int decimal_to_bcd(unsigned int d) {                 // Function to convert decimal to BCD value
    return ((d / 10) << 4) + (d % 10);
}
 
int main(int argc, char *argv[]) {
 
    setup_io(&gpio);                                                                // Mmap and get virtual address of GPIO 
    setup_io(&bsc0);                                                               // Mmap and get virtual address of BSC0 
 
    i2c_init();                                                                            //Initialize I2C interface by configuring GPIO and enable I2C function
 
    BSC0_A = 0xa2;                                                                // RTC-8564 slave address: Read=>0xa3, Write=>0xa2
 
    /* Write operation to restart the RTC-8564, configuring register at index 2 ('secs' field) */
    BSC0_DLEN = 1;                                                               // write one byte at one time
    BSC0_FIFO = 2;                                                                // value of data: 2
    BSC0_S = CLEAR_STATUS;                                            // Reset status bits 
    BSC0_C = START_WRITE;                                               // Start Write 
 
    wait_i2c_done();

    BSC0_A = 0xa3;                                                                // RTC-8564 slave address: Read=>0xa3, Write=>0xa2
 
    /* Start Read of RTC chip's time */
    BSC0_DLEN = 7;
    BSC0_S = CLEAR_STATUS;                                            // Reset status bits 
    BSC0_C = START_READ;                                                 // Start Read after clearing FIFO
 
    wait_i2c_done();
 
    /* Store values in struct */
    t.tm_sec = bcd_to_decimal(BSC0_FIFO & 0x7f);
    t.tm_min = bcd_to_decimal(BSC0_FIFO & 0x7f);
    t.tm_hour = bcd_to_decimal(BSC0_FIFO & 0x3f);
    t.tm_mday = bcd_to_decimal(BSC0_FIFO & 0x3f);
    t.tm_wday = bcd_to_decimal(BSC0_FIFO & 0x07);
    t.tm_mon = bcd_to_decimal(BSC0_FIFO & 0x1f) - 1; // Convert from 1~12 to 0~11
    t.tm_year = bcd_to_decimal(BSC0_FIFO) + 100;
 
    printf("%02d:%02d:%02d %02d/%02d/%02d (UTC on RTC-8564)\n",
        t.tm_hour,t.tm_min,t.tm_sec,
        t.tm_mday,t.tm_mon + 1,t.tm_year - 100);
 
    /* Unmap the peripheral */
    release_io(&bsc0);
    release_io(&gpio);
}
