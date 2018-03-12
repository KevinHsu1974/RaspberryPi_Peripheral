//  Read RTC via I2C: Test Program for Raspberry-Pi 3
//  23-Dec-2017
//  Kevin Hsu
// --------------------------------------------------------------------
//
//   Title     :  I2C.c
//             :
//   Library   :
//             :
//   Developers:  Kevin Hsu
//             :
//   Purpose   :  RaspberryPi 3 "B" I2C functions
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

#include "RPI3.h"
#include "I2C.h"
#include "GPIO.h"
 
// Initialize I2C
void i2c_init()
{
    INP_GPIO(0);
    SET_GPIO_ALT(0, 0);
    INP_GPIO(1);
    SET_GPIO_ALT(1, 0);
}  
 
// Function to wait for the I2C transaction to complete
void wait_i2c_done() {
 
        int timeout = 50;
        while((!((BSC0_S) & BSC_S_DONE)) && --timeout) {
            usleep(1000);
        }
        if(timeout == 0)
            printf("Error: wait_i2c_done() timeout.\n");
}
