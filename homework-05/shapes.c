//------------------------------------------------------------------------------
//  File Name : shapes.c
//
//  Description: This file contains the routines required for project 3
//
//
//  David Pryor
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
#include "macros.h"
#include "functions.h"
#include "msp430.h"


void straight_line(void){
//==============================================================================
// Straight Line
// 
// Description: This function turns on the motors and travels forward for a short distance
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:  no global variables
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  int i;
  right_wheel_forward_on(); //right wheel on
  for(i=INCREMENT_START;i<THREE_ITERATIONS; i++){
    left_wheel_forward_on(); //left wheel on
    five_msec_sleep(FOR_THIRTY_MSEC);
    left_wheel_forward_off(); //left wheel off
    five_msec_sleep(FOR_TEN_MSEC);
  }
  right_wheel_forward_off(); //right wheel off
}

void curved_right180_line(void){
//==============================================================================
// Right Curve 180 degrees
// 
// Description: This function turns on the motors and travels a 180degree curve to the right
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:  no global variables
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  int i;
  left_wheel_forward_on(); //left wheel on
  for(i=INCREMENT_START;i<EIGHT_ITERATIONS; i++){
    right_wheel_forward_on(); //right wheel on
    five_msec_sleep(FOR_TEN_MSEC);
    right_wheel_forward_off(); //right wheel off
    five_msec_sleep(FOR_FORTY_MSEC);
  }
  left_wheel_forward_off(); //left wheel off
}

void curved_right120_line(void){
//==============================================================================
// Right Curve 120 degrees
// 
// Description: This function turns on the motors and travels a 120degree curve to the right
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:  no global variables
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================  
  int i;
  left_wheel_forward_on(); //left wheel on
  for(i=INCREMENT_START;i<FOUR_ITERATIONS; i++){
    right_wheel_forward_on(); //right wheel on
    five_msec_sleep(FOR_FIFTEEN_MSEC);
    right_wheel_forward_off(); //right wheel off
    five_msec_sleep(FOR_FORTYFIVE_MSEC);
  }
  left_wheel_forward_off(); //left wheel off
}

void curved_left180_line(void){
//==============================================================================
// Left Curve 180 degrees
// 
// Description: This function turns on the motors and travels a 180degree curve to the left
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:  no global variables
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================  
  int i;
  right_wheel_forward_on(); //right wheel on
  for(i=INCREMENT_START;i<EIGHT_ITERATIONS; i++){
    left_wheel_forward_on(); //left wheel on
    five_msec_sleep(FOR_TEN_MSEC);
    left_wheel_forward_off(); //left wheel off
    five_msec_sleep(FOR_FIFTY_MSEC);
  }
  right_wheel_forward_off(); //right wheel off
}

void right_circle_routine(void){
//==============================================================================
// Right Circle
// 
// Description: This function turns on the motors and travels a 360degree circle to the right twice
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:  no global variables
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  curved_right180_line(); // first circle
  five_msec_sleep(FOR_150_MSEC);
  curved_right180_line();
  five_msec_sleep(FOR_150_MSEC);
  curved_right180_line(); //second circle
  five_msec_sleep(FOR_150_MSEC);
  curved_right180_line();
}

void left_circle_routine(void){
//==============================================================================
// Left Circle
// 
// Description: This function turns on the motors and travels a 360degree circle to the left twice
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:  no global variables
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  curved_left180_line(); //first circle
  five_msec_sleep(FOR_100_MSEC);
  curved_left180_line();
  five_msec_sleep(FOR_100_MSEC);
  curved_left180_line(); //second circle
  five_msec_sleep(FOR_100_MSEC);
  curved_left180_line();
}

void triangle_routine(void){
//==============================================================================
// Triangle
// 
// Description: This function turns on the motors and travels in the shape of a triangle twice
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:  no global variables
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================  
  straight_line(); // First
  five_msec_sleep(FOR_THREEFIFTY_MSEC);
  curved_right120_line();
  five_msec_sleep(FOR_THREEFIFTY_MSEC);
  straight_line();
  five_msec_sleep(FOR_THREEFIFTY_MSEC);
  curved_right120_line();
  five_msec_sleep(FOR_THREEFIFTY_MSEC);
  straight_line();
  five_msec_sleep(FOR_THREEFIFTY_MSEC);
  curved_right120_line();
  five_msec_sleep(FOR_THREETWENTYFIVE_MSEC);
  straight_line(); // Second
  five_msec_sleep(FOR_THREEFIFTY_MSEC);
  curved_right120_line();
  five_msec_sleep(FOR_THREEFIFTY_MSEC);
  straight_line();
  five_msec_sleep(FOR_THREEFIFTY_MSEC);
  curved_right120_line();
  five_msec_sleep(FOR_THREEFIFTY_MSEC);
  straight_line();
  five_msec_sleep(FOR_THREEFIFTY_MSEC);
  curved_right120_line();
}

void figure_eight_routine(void){
//==============================================================================
// Figure Eight
// 
// Description: This function turns on the motors and travels in a right circle then in a left circle twice
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:  no global variables
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  curved_right180_line(); //first 
  five_msec_sleep(FOR_EIGHTH_SECOND);
  curved_right180_line();
  five_msec_sleep(FOR_FOURTH_SECOND);
  curved_left180_line();
  five_msec_sleep(FOR_TENTH_SECOND);
  curved_left180_line();
  five_msec_sleep(FOR_HALF_SECOND);
  curved_right180_line();  //second
  five_msec_sleep(FOR_EIGHTH_SECOND);
  curved_right180_line();
  five_msec_sleep(FOR_FOURTH_SECOND);
  curved_left180_line();
  five_msec_sleep(FOR_EIGHTH_SECOND);
  curved_left180_line();

}