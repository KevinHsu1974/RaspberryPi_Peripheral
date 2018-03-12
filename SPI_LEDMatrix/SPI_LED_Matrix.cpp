//  Drive LED Matrix via SPI for Raspberry-Pi 3
//  30-Dec-2017
//  Kevin Hsu
// --------------------------------------------------------------------
//
//   Title     :  SPI_LED_Matrix.c
//             :
//   Library   :
//             :
//   Developers:  Kevin Hsu
//             :
//   Purpose   :  RaspberryPi 3 "B" , 8x8 LED Matrix Display functon
//             :
//   Limitation:
//             :
//   Note      :
//             :
// --------------------------------------------------------------------
//   modification history :
// --------------------------------------------------------------------
//   Version| mod. date: |
//   V1.0   | 15-Dec-2017 | Programming Start

#include <iostream> 
#include <wiringPi.h>
#include "ref.h"

using namespace std;

void Send16bits ( unsigned short output ) { //To send  16 bits data
   unsigned int mask, test;
   mask = 0x8000;                                             // mask to mark highest bit
   while ( mask!=0 ){
      if ( output & mask )                                    // To send one bit each time
         digitalWrite( DATA, 1 );
      else
         digitalWrite( DATA, 0 );
         
      digitalWrite( CLOCK, 1 );                            // Set rising edge to transmit data
      mask >>= 1;                                                // right shift one bit
      test = digitalRead( CLOCK );                    // Read the clock and delay
      digitalWrite( CLOCK, 0 );                           // reset clock
   }           
}

// Send data to register
void MAX7219Send( unsigned char reg_number, unsigned char dataout ) {
   int test;
   digitalWrite( CHIP_SELECT, 0 );                // Toggle chip select 
   Send16bits( ( reg_number << 8 ) + dataout ) ;  // Transmit 16bit(8-bit Register + 8-bit data)
   digitalWrite( CHIP_SELECT, 1 ) ;               // Reset chip select
   test = digitalRead( CHIP_SELECT );        // check and delay
   test = digitalRead( CLOCK );                    // check and delay
}

void Init7219( int digits, int mode, int level ) {    // Initialize MAX7219
   if ( wiringPiSetup () == -1 )
      exit( 1 );

   // Setup mode of SPI pins
   pinMode( DATA, OUTPUT );  
   pinMode( CLOCK, OUTPUT );
   pinMode( CHIP_SELECT, OUTPUT );  

   // Setup initial value of SPI pins
   digitalWrite( CHIP_SELECT, 1 );     
   digitalWrite( CLOCK, 0 );    
   digitalWrite( DATA, 0 );     
   
   MAX7219Send( NO_OP, 0 );                  // Set non-operation
   MAX7219Send( SHUTDOWN, 1 );        // Shutdown 
   MAX7219Send( DISPLAY_TEST, 1 );    // Start self- test
   delay(2000);

   // Setup initial values of registers
   MAX7219Send( SCAN_LIMIT, digits );
   MAX7219Send( DECODE_MODE, mode );   
   MAX7219Send( INTENSITY, level );  
 
   MAX7219Send( DISPLAY_TEST, 0 );    // Stop self-test
   
}

// Display patterns
unsigned char smile[] = { 0x3C, 0x42, 0xAD, 0xA1, 0XAD, 0x91, 0x42, 0x3C };
unsigned char cross[] = { 0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81 };

void pattern_display(unsigned char pattern[]){    // Function to send data to LED to display
	 for ( int i = 1 ; i <= 8 ; i++ ) {                             // Transmit data to D0 ~ D7
     MAX7219Send( i, pattern[i-1] );
     }
}

void flash_display(){                                                 // Function to display LEDs one by one
	 for ( int i = 1; i <= 8; i++ ) {
     unsigned char led_mask = 0x80;
       do{
		 MAX7219Send( i, led_mask );
		 delay(500);
		 led_mask >>= 1; 
       }while( led_mask !=0 );
     }
}
   	
int main ( void ) {
   Init7219( DIGITS, MODE_UNDECODE, INTENSITY_VAL );  // Init MAX 7219
   delay(3000);                      

   pattern_display( cross ); 
   delay(2000);
   
   pattern_display( smile ); 
   delay(2000);
   
   flash_display();
   
   return 1;
}

