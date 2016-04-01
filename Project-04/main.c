//------------------------------------------------------------------------------
//  File Name : main.c
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  David Pryor
//  Jan 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

// Required defines
// In the event the universe no longer exists, this bit will reset
// ALWAYS                                       (1)
// CNTL_STATE_INDEX                             (3) // Control States
// SW1                  	                (0x01) // Switch 1
// SW2                  	                (0x02) // Switch 2
// START				        (0x00)
// MAX_SIZE_COUNT			        (0x05) 
// LINE_POS_1                                   (0x01) // starting postion on lcd
// LINE_POS_2                                   (0x02) // starting postion on lcd
// LINE_POS_3                                   (0x03) // starting postion on lcd
// LCD--------------------------------------------------------------------------
// LCD_HOME_L1	                                (0x80)
// LCD_HOME_L2         	                        (0xA0)
// LCD_HOME_L3         	                        (0xC0)
// LCD_HOME_L4         	                        (0xE0)
// LINE_SIZE				        (0x0B)
// CASE NUMBERS (THESE ARE TEMPORARY FILLERS!)----------------------------------
// COUNT_TWOFIDDY_MSEC			        (0x32) //50
// COUNT_FIVEHUNNED_MSEC			(0x64) //100
// COUNT_SEVENFIDDY_MSEC			(0x96) //150
// COUNT_ONETHOUSAND_MSEC			(0xC8) //200
// COUNT_TWELVEFIDDY_MSEC			(0xFA) //250
// SWITCHES---------------------------------------------------------------------
// SWITCH_OFF				        (0x00)
// SWITCH_ON			                (0x01)
//------------------------------------------------------------------------------



// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time;
volatile unsigned int five_msec_delay;
extern char display_line_1[LINE_SIZE];
extern char display_line_2[LINE_SIZE];
extern char display_line_3[LINE_SIZE];
extern char display_line_4[LINE_SIZE];
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
volatile unsigned int do_this = FALSE;

void main(void){
//==============================================================================
// Main Program
// 
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
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
//              slow_input_down
//              control_state[CNTL_STATE_INDEX]
//              char big
//              char size_count;
//              char posL1
//              char posL2
//              char posL3
//              char posL4
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System 
  Init_Conditions();
  Time_Sequence = SWITCH_OFF;               // 
  Init_Timers();                            // Initialize Timers
  Init_LEDs();                              // Initialize LEDs
  Init_LCD();                               // Initialize LCD
  

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 while(ALWAYS) {                            // Can the Operating system run
   if(do_this == TRUE){
      Five_msec_Delay(FOR_ONE_SECOND);                     //pause
      display_2 = "FORWARD";                    //change display
      posL2 = LINE_POS_1;
      Display_Process();                        //push display
      straight_line();                          //forward
      
      Five_msec_Delay(FOR_ONE_SECOND);                     //pause
      display_2 = "REVERSE";                    //change display
      posL2 = LINE_POS_1;
      Display_Process();                        //push display
      straight_line_reverse();                  //reverse
      
      Five_msec_Delay(FOR_ONE_SECOND);
      display_2 = "FORWARD";                    //change display
      posL2 = LINE_POS_1;
      Display_Process();                        //push display
      straight_line();                          //forward
      
      Five_msec_Delay(FOR_ONE_SECOND);
      display_2 = "CW-SPIN";                   //change display
      posL2 = LINE_POS_1;
      Display_Process();                         //push display
      clockwise_spin();                          //forward
      
      Five_msec_Delay(FOR_ONE_SECOND);
      display_2 = "CCW-SPIN";                   //change display
      posL2 = LINE_POS_1;
      Display_Process();                         //push display
      counterclockwise_spin();                          //forward
      
      Five_msec_Delay(FOR_ONE_SECOND);                     //pause
      display_2 = "";                           //clear display
      posL2 = LINE_POS_1;
      Display_Process();                        //push display
      do_this = FALSE;
   }
 }
//------------------------------------------------------------------------------
}













