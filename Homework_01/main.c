//------------------------------------------------------------------------------
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"

// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define BLINK_LED            (0x01) // Allow LED to Blink
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED4                 (0x08) // LED 4
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2


// Global Variables
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time;
volatile unsigned int five_msec_count;

//------------------------------------------------------------------------------

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
// 
//------------------------------------------------------------------------------
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System 
  Init_Conditions();
  PJOUT |= LED1;                            // Turn LED 1 on to indicate boot
  Time_Sequence = 0;                        // 
  Init_Timers();                            // Initialize Timers
  Init_LEDs();                              // Initialize LEDs

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 while(ALWAYS) {                            // Can the Operating system run
  switch(Time_Sequence){
    case 250:                               // 1000 msec  
      if(one_time){
        Init_LEDs();                        // Initialize LEDs
        one_time = 0;
      }
      Time_Sequence = 0;                    // 
    case 200:                               // 1000 msec  
      if(one_time){
        PJOUT |= LED4;                      // Change State of LED 4
        P3OUT |= LED5;                      // Change State of LED 5
        one_time = 0;
      }
    case 150:                               // 750 msec  
      if(one_time){
        PJOUT |= LED3;                      // Change State of LED 3
        P3OUT |= LED6;                      // Change State of LED 6
        one_time = 0;
      }
    case 100:                               // 500 msec  
      if(one_time){
        PJOUT |= LED2;                      // Change State of LED 2
        P3OUT |= LED7;                      // Change State of LED 7
        one_time = 0;
      }
    case  50:                               // 250 msec  
      if(one_time){
        PJOUT |= LED1;                      // Change State of LED 1
        P3OUT |= LED8;                      // Change State of LED 8
        one_time = 0;
      }
      break;                                // 
    default: break; 
  }
  Switches_Process();                       // Check for switch state change 
  if(Time_Sequence > 250){
    Time_Sequence = 0;
  }
 }
//------------------------------------------------------------------------------
}

void Init_Conditions(void){
//------------------------------------------------------------------------------
// Initializations Configurations
//------------------------------------------------------------------------------
// Interrupts are disabled by default, enable them. 
  enable_interrupts();

//------------------------------------------------------------------------------
}

void Switches_Process(void){
//------------------------------------------------------------------------------
// Switch Configurations
//------------------------------------------------------------------------------
  if (!(P4IN & SW1)){
    PJOUT |= LED1;                   // Change State of LED 1
    PJOUT |= LED2;                   // Change State of LED 2
    PJOUT |= LED3;                   // Change State of LED 3
    PJOUT |= LED4;                   // Change State of LED 4
  }
  if (!(P4IN & SW2)) {
    P3OUT |= LED5;                   // Change State of LED 5
    P3OUT |= LED6;                   // Change State of LED 6
    P3OUT |= LED7;                   // Change State of LED 7
    P3OUT |= LED8;                   // Change State of LED 8
  }
//------------------------------------------------------------------------------
}

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on all 8 LEDs
  PJOUT &= ~LED1;
  PJOUT &= ~LED2;
  PJOUT &= ~LED3;
  PJOUT &= ~LED4;
  P3OUT &= ~LED5;
  P3OUT &= ~LED6;
  P3OUT &= ~LED7;
  P3OUT &= ~LED8;
//------------------------------------------------------------------------------
}

void Init_Timers(void){
//------------------------------------------------------------------------------
// Timer Configurations
//------------------------------------------------------------------------------
  Init_Timer_A0(); //
//  Init_Timer_A1(); // 
//  Init_Timer_B0(); // 
//  Init_Timer_B1(); //  
//  Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
}

void usleep10(unsigned int usec){
//------------------------------------------------------------------------------
// At the current clock rate this yields about 10usec per value passed
// A value of  0 yields 1.37 uSec
// A value of  1 yields 1.87 uSec
// A value of  2 yields 2.36 uSec
// A value of  3 yields 2.86 uSec
// A value of  4 yields 3.36 uSec
// A value of  5 yields 3.86 uSec
// A value of  6 yields 4.36 uSec
// A value of  7 yields 4.85 uSec
// A value of  8 yields 5.354 uSec
// A value of  9 yields 5.854 uSec
// A value of 10 yields 6.353 uSec
// A value of 11 yields 6.851 uSec
// A value of 12 yields 7.351 uSec
// A value of 13 yields 7.849 uSec
// A value of 14 yields 8.350 uSec
// A value of 15 yields 8.849 uSec
// A value of 16 yields 9.342 uSec
// A value of 17 yields 9.84 uSec
// A value of 18 yields 10.34 uSec
// A value of 19 yields 10.84 uSec
  int i,j;
  for(j=0;j<usec;j++){
    for(i=0;i<14;i++);
  }
//  __delay_cycles(unsigned long __cycles);
//------------------------------------------------------------------------------
}

void five_msec_sleep(unsigned int fivemsec){
//------------------------------------------------------------------------------
//Each count passed is at least x times 5 milliseconds
  five_msec_count = 0;
  while(fivemsec > (five_msec_count+1));
//------------------------------------------------------------------------------
}

void Timer_code(void){
//------------------------------------------------------------------------------
// Timer A0 interrupt code
//------------------------------------------------------------------------------
  Time_Sequence++;
  one_time = 1;
  if (five_msec_count < 1000){
    five_msec_count++;
  }
//------------------------------------------------------------------------------
}



