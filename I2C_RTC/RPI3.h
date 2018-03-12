// --------------------------------------------------------------------
//
//   Title     :  RPI3.h
//             :
//   Library   :
//             :
//   Developers:  Kevin Hsu
//             :
//   Purpose   :  RaspberryPi 3 "B" Address of Register
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 03-Dec-2017 | Programming Start

#ifndef __RPI3_H__
#define __RPI3_H__

#ifdef __cplusplus
extern "C" {
#endif

/* BCM2837 Address of Peripherals*/
#define RAM_TESTBASE             0x30000000                           // Use upper 256MB DRAM for testing */
#define BCM2837_PERI_BASE   0x20000000
#define GPIO_BASE                      (BCM2837_PERI_BASE + 0x200000)  // GPIO controller
#define BSC0_BASE                     (BCM2837_PERI_BASE + 0x205000)  // Serial Controller 0 base addess */


#ifdef _cplusplus 
} 
#endif
#endif  //__RPI3_H___
