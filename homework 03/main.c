//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson
//  Jan 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED4                 (0x048) // LED 3
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define CNTL_STATE_INDEX        (3)
// LCD
#define LCD_HOME_L1	          0x80
#define LCD_HOME_L2         	0xA0
#define LCD_HOME_L3         	0xC0
#define LCD_HOME_L4         	0xE0


// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time;
volatile unsigned int five_msec_count;
extern char display_line_1[11];
extern char display_line_2[11];
extern char display_line_3[11];
extern char display_line_4[11];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char posL1;
char posL2;
char posL3;
char posL4;
char size_count;
char big;

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
  five_msec_sleep(50);                      // 250 msec delay for the clock to settle
  Init_LEDs();                              // Initialize LEDs
  Init_LCD();                               // Initialize LCD
  
//             1234567890
  display_1 = "NCSU";
  posL1 = 3;
  display_2 = "WOLFPACK";
  posL2 = 1;
  display_3 = "ECE306";
  posL3 = 2;
  display_4 = "J Carlson";
  posL4 = 1;
  big = 0;
  Display_Process();
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
      size_count++;
      if(size_count > 5){
        size_count = 0;
        if(big){
          lcd_BIG_mid();
          big = 0;
        }else{
          lcd_4line();
          big = 1;
        }
      }
        Display_Process();
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

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on all 8 LEDs
  PJOUT &= ~LED1;
  PJOUT &= ~LED2;
  PJOUT &= ~LED3;
//  PJOUT &= ~LED4;
  P3OUT &= ~LED5;
  P3OUT &= ~LED6;
  P3OUT &= ~LED7;
  P3OUT &= ~LED8;
//------------------------------------------------------------------------------
}

void Display_Process(void){
  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
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

