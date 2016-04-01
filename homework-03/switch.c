//------------------------------------------------------------------------------
//  File Name : switch.c
//
//  Description: This file contains the Switches_Process function
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
// SW1                  	        (0x01) // Switch 1
// SW2                  	        (0x02) // Switch 2
// LINE_POS_1                              (0x01) // starting postion on lcd
// LINE_POS_2                              (0x02) // starting postion on lcd
// LINE_POS_3                              (0x03) // starting postion on lcd
//------------------------------------------------------------------------------
//GLOBALS
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
//------------------------------------------------------------------------------

void Switches_Process(void){
//==============================================================================
// Switch Process
// 
// Description: This function takes an input from the push button and switches which lines
//  are display on the LCD
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:     char *display_1
//              char *display_2
//              char *display_3
//              char *display_4
//              char posL1
//              posL2
//              posL3
//              posL4
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  if (!(P4IN & SW1)){
    display_1 = "NCSU";
    posL1 = LINE_POS_3;
    display_2 = "WOLFPACK";
    posL2 = LINE_POS_1;
    display_3 = "ECE306";
    posL3 = LINE_POS_2;
    display_4 = "D Pryor";
    posL4 = LINE_POS_1;
  }
  if (!(P4IN & SW2)) {
    display_1 = "Embedded";
    posL1 = LINE_POS_1;
    display_2 = "Systems";
    posL2 = LINE_POS_2;
    display_3 = "Rock!";
    posL3 = LINE_POS_3;
    display_4 = "Go Pack!";
    posL4 = LINE_POS_1;
  }
//------------------------------------------------------------------------------
}