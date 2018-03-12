/* Register reference value for SPI_Matrix
 * Created by Kevin Hsu 25/Dec/2017
 */ 

// GPIO definition
#define DATA   12  // SPI MOSI
#define CLOCK  14  // SPI CLK
#define CHIP_SELECT   10  // SPI CE0 (Enable)

// Define address of MAX7219 registers
#define NO_OP         0x00    // Non Operation
#define DECODE_MODE   0x09    // Decode Mode: 1=Decode, 0=Not Decode 
#define INTENSITY     0x0a    // LED Intesity(Brigthness)
#define SCAN_LIMIT    0x0b    // Row of LEDs to be desplayed(1
#define SHUTDOWN      0x0c    // Turn off all LEDs, MAX7219 in standby mode
#define DISPLAY_TEST  0x0f    // Turn on all LEDs for test purpose

//  Pre-define register values
#define MODE_DECODE   0x01    // Decode Mode; can be used for 7 segments LED
#define MODE_UNDECODE 0x00    // Normal LED mode
#define DIGITS        0x07    // Test pattern and also the value for SCAN_LIMT register (0~7)
#define INTENSITY_VAL 0x01    // Value of Intensity (0-15)
