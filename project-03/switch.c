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
// FOR_ONE_SECOND                       (200)  // for use with 5msec sleep
// SW1                  	        (0x01) // Switch 1
// SW2                  	        (0x02) // Switch 2
// LINE_POS_1                              (0x01) // starting postion on lcd
// LINE_POS_2                              (0x02) // starting postion on lcd
// LINE_POS_3                              (0x03) // starting postion on lcd
//------------------------------------------------------------------------------
//GLOBALS
int menu_count = MENU_ITEM_ONE;
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
//              char posL2
//              char posL3
//              char posL4
//              int menu_count
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  if (!(P4IN & SW1)){
    five_msec_sleep(FOR_TENTH_SECOND); //prevent double detection of switch
    switch(menu_count){
        case MENU_ITEM_ONE:            // First menu item
          five_msec_sleep(FOR_TWOHUNDRED_MSEC);
          display_1 = "";
          posL1 = LINE_POS_1;
          display_2 = "Line";
          posL2 = LINE_POS_3;
          display_3 = "";
          posL3 = LINE_POS_3;
          display_4 = "";
          posL4 = LINE_POS_3;
          menu_count++;
          break;
        case MENU_ITEM_TWO:            // Second menu item  
          five_msec_sleep(FOR_TWOHUNDRED_MSEC);
          display_1 = "";
          posL1 = LINE_POS_1;
          display_2 = "Curve";
          posL2 = LINE_POS_3;
          display_3 = "";
          posL3 = LINE_POS_3;
          display_4 = "";
          posL4 = LINE_POS_3;
          menu_count++;
          break;
        case MENU_ITEM_THREE:             // Third menu item
          five_msec_sleep(FOR_TWOHUNDRED_MSEC);
          display_1 = "";
          posL1 = LINE_POS_1;
          display_2 = "Right";
          posL2 = LINE_POS_2;
          display_3 = "Circle";
          posL3 = LINE_POS_2;
          display_4 = "";
          posL4 = LINE_POS_3;
          menu_count++;
          break;
        case MENU_ITEM_FOUR:             // Third menu item
          five_msec_sleep(FOR_TWOHUNDRED_MSEC);
          display_1 = "";
          posL1 = LINE_POS_1;
          display_2 = "Left";
          posL2 = LINE_POS_3;
          display_3 = "Circle";
          posL3 = LINE_POS_2;
          display_4 = "";
          posL4 = LINE_POS_3;
          menu_count++;
          break;
        case MENU_ITEM_FIVE:             // Fourth menu item
          five_msec_sleep(FOR_TWOHUNDRED_MSEC);
          display_1 = "";
          posL1 = LINE_POS_1;
          display_2 = "Triangle";
          posL2 = LINE_POS_1;
          display_3 = "";
          posL3 = LINE_POS_3;
          display_4 = "";
          posL4 = LINE_POS_3;
          menu_count++;
          break;
        case MENU_ITEM_SIX:  	    // Fifth Menu item
          five_msec_sleep(FOR_TWOHUNDRED_MSEC);
          display_1 = "";
          posL1 = LINE_POS_1;
          display_2 = "Figure-8";
          posL2 = LINE_POS_1;
          display_3 = "";
          posL3 = LINE_POS_3;
          display_4 = "";
          posL4 = LINE_POS_3;
          menu_count = MENU_ITEM_ONE;
          break;                                // 
        default: break; 
      }
  }
  if (!(P4IN & SW2)) {
    five_msec_sleep(FOR_THREETWENTYFIVE_MSEC); //prevent double detection of switch
    switch(menu_count){
        case MENU_PICK_ONE:            // First menu item
          five_msec_sleep(FOR_THREETWENTYFIVE_MSEC );
          straight_line();
          break;
        case MENU_PICK_TWO:            // Second menu item
          five_msec_sleep(FOR_THREETWENTYFIVE_MSEC );
          curved_left180_line();
          break;
        case MENU_PICK_THREE:             // Third menu item
          five_msec_sleep(FOR_THREETWENTYFIVE_MSEC );
          right_circle_routine();
          break;
        case MENU_PICK_FOUR:             // Fourth menu item
          five_msec_sleep(FOR_THREETWENTYFIVE_MSEC );
          left_circle_routine();
          break;
        case MENU_PICK_FIVE:             // Fifth menu item
          five_msec_sleep(FOR_THREETWENTYFIVE_MSEC );
          triangle_routine();
          break;
        case MENU_PICK_SIX:  	    // Sixth Menu item
          five_msec_sleep(FOR_THREETWENTYFIVE_MSEC );
          figure_eight_routine();
          break;                                // 
        default: break; 
      }
  }
//------------------------------------------------------------------------------
}