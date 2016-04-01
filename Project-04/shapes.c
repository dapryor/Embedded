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
  for(i=INCREMENT_START;i<TEN_ITERATIONS; i++){
    left_wheel_forward_on(); //left wheel on
    Five_msec_Delay(FOR_THIRTY_MSEC);
    left_wheel_forward_off(); //left wheel off
    Five_msec_Delay(FOR_TEN_MSEC);
  }
  right_wheel_forward_off(); //right wheel off
}

void straight_line_reverse(void){
//==============================================================================
// Straight Line Reverse
// 
// Description: This function turns on the motors and travels Reverse for a short distance
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
  right_wheel_reverse_on(); //right wheel on
  for(i=INCREMENT_START;i<TWENTY_ITERATIONS; i++){
    left_wheel_reverse_on(); //left wheel on
    Five_msec_Delay(FOR_THIRTY_MSEC);
    left_wheel_reverse_off(); //left wheel off
    Five_msec_Delay(FOR_TEN_MSEC);
  }
  right_wheel_reverse_off(); //right wheel off
}

void clockwise_spin(void){
//==============================================================================
// Clockwise Spin
// 
// Description: This function turns on the motors and travels clockwise for a short distance
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
  left_wheel_forward_on(); //left wheel on
  right_wheel_reverse_on(); //right wheel on
  Five_msec_Delay(FOR_ONE_SECOND);
  left_wheel_forward_off(); //left wheel off
  right_wheel_reverse_off(); //right wheel off
}

void counterclockwise_spin(void){
//==============================================================================
// Counter Clockwise Spin
// 
// Description: This function turns on the motors and travels counter clockwise for a short distance
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
  left_wheel_reverse_on(); //left wheel on
  right_wheel_forward_on(); //right wheel on
  Five_msec_Delay(FOR_ONE_SECOND);
  left_wheel_reverse_off(); //left wheel off
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
    Five_msec_Delay(FOR_TEN_MSEC);
    right_wheel_forward_off(); //right wheel off
    Five_msec_Delay(FOR_FORTY_MSEC);
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
    Five_msec_Delay(FOR_FIFTEEN_MSEC);
    right_wheel_forward_off(); //right wheel off
    Five_msec_Delay(FOR_FORTYFIVE_MSEC);
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
    Five_msec_Delay(FOR_TEN_MSEC);
    left_wheel_forward_off(); //left wheel off
    Five_msec_Delay(FOR_FIFTY_MSEC);
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
  Five_msec_Delay(FOR_150_MSEC);
  curved_right180_line();
  Five_msec_Delay(FOR_150_MSEC);
  curved_right180_line(); //second circle
  Five_msec_Delay(FOR_150_MSEC);
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
  Five_msec_Delay(FOR_100_MSEC);
  curved_left180_line();
  Five_msec_Delay(FOR_100_MSEC);
  curved_left180_line(); //second circle
  Five_msec_Delay(FOR_100_MSEC);
  curved_left180_line();
}
