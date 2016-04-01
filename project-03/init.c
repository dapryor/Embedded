//------------------------------------------------------------------------------
//
//  Description: This file contains the Initialize functions
//
//
//  David Pryor
//  Jan 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
#include "macros.h"
#include "functions.h"
#include "msp430.h"
//------------------------------------------------------------------------------
// Required defines
// IOT_WAKEUP           	                (0x01) // This was LED 1
// IOT_FACTORY   			        (0x02) // This was LED 2
// IOT_STA_MINIAP       	                (0x04) // This was LED 3
// R_FORWARD        	                        (0x10) // This was LED 5
// R_REVERSE        	                        (0x20) // This was LED 6
// L_FORWARD        	                        (0x40) // This was LED 7
// L_REVERSE        	                        (0x80) // This was LED 8
//------------------------------------------------------------------------------
// GLOBAL VARIABLES
extern char display_line_1[LINE_SIZE];
extern char display_line_2[LINE_SIZE];
extern char display_line_3[LINE_SIZE];
extern char display_line_4[LINE_SIZE];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
//------------------------------------------------------------------------------
void Init_Conditions(void){
//==============================================================================
// Initializations Configurations
// 
// Description: This function intializes display_1 through 4 pointers to start of LCD lines
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:     volatile unsigned int Time_Sequence;
//              volatile char one_time;
//              char* display_1
//              char* display_2
//              char* display_3
//              char* display_4
//              char display_line_1[LINE_SIZE];
//              char display_line_2[LINE_SIZE];
//              char display_line_3[LINE_SIZE];
//              char display_line_4[LINE_SIZE];
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
// Interrupts are disabled by default, enable them. 
  enable_interrupts();
  display_1 = &display_line_1[START];
  display_2 = &display_line_2[START];
  display_3 = &display_line_3[START];
  display_4 = &display_line_4[START];

//------------------------------------------------------------------------------
}

void Init_Timers(void){
//==============================================================================
// Timer Configurations
// 
// Description: This function initializes timers used for the board
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:     NONE
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  Init_Timer_A0(); //
//  Init_Timer_A1(); // 
//  Init_Timer_B0(); // 
//  Init_Timer_B1(); //  
//  Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
}

void Init_LEDs(void){
//==============================================================================
// LED Configurations
// 
// Description: This function initializes the LED output to 0
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:     NONE
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
//------------------------------------------------------------------------------
// Turns off all 8 LEDs
  PJOUT &= ~IOT_WAKEUP;
  PJOUT &= ~IOT_FACTORY;
  PJOUT &= ~IOT_STA_MINIAP;

//------------------------------------------------------------------------------
}
