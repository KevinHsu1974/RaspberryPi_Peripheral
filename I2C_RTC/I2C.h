// --------------------------------------------------------------------
//
//   Title     :  I2C.h
//             :
//   Library   :
//             :
//   Developers:  Kevin Hsu
//             :
//   Purpose   :  RaspberryPi 3 "B" Serial Controller Initization for I2C
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

#include "2837mmu.h"

extern struct bcm2837_peripheral bsc0;	

/* BSC register address */
#define BSC0_C                            *(bsc0.addr + 0x00)
#define BSC0_S                            *(bsc0.addr + 0x04)
#define BSC0_DLEN                     *(bsc0.addr + 0x08)
#define BSC0_A                            *(bsc0.addr + 0x0c)
#define BSC0_FIFO                      *(bsc0.addr + 0x10)
 
/* BSC control register bits*/
#define BSC_C_I2CEN     (1 << 15)
#define BSC_C_INTR       (1 << 10)
#define BSC_C_INTT       (1 << 9)
#define BSC_C_INTD       (1 << 8)
#define BSC_C_ST           (1 << 7)
#define BSC_C_CLEAR    (1 << 4)
#define BSC_C_READ      1
 
#define START_READ      BSC_C_I2CEN|BSC_C_ST|BSC_C_CLEAR|BSC_C_READ
#define START_WRITE     BSC_C_I2CEN|BSC_C_ST
 
/* BSC control register bits */
#define BSC_S_CLKT     (1 << 9)
#define BSC_S_ERR       (1 << 8)
#define BSC_S_RXF       (1 << 7)
#define BSC_S_TXE       (1 << 6)
#define BSC_S_RXD      (1 << 5)
#define BSC_S_TXD       (1 << 4)
#define BSC_S_RXR      (1 << 3)
#define BSC_S_TXW      (1 << 2)
#define BSC_S_DONE    (1 << 1)
#define BSC_S_TA      1
 
#define CLEAR_STATUS    BSC_S_CLKT|BSC_S_ERR|BSC_S_DONE
 
// I2C Function Prototypes
void i2c_init();
void wait_i2c_done();
