//------------------------------------------------------------------------------
//  File Name : motors.c
//
//  Description: This files contains functions for straight lines and turns
//
//
//  David Pryor
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
//
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

// MACROS ----------------------------------------------------------------------
// R_FORWARD        	                (0x10) // This was LED 5
// R_REVERSE        	                (0x20) // This was LED 6
// L_FORWARD        	                (0x40) // This was LED 7
// L_REVERSE        	                (0x80) // This was LED 8
//------------------------------------------------------------------------------

void left_wheel_forward_on(void){
//==============================================================================
// Left Wheel Forward On
// 
// Description: This function turns on the left motor for forward use
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
  if(!(P3IN & L_FORWARD)){ // is the LEFT wheel NOT going forward?
    //left_wheel_reverse_off(); // making sure left wheel is NOT reversing
    P3OUT |= L_FORWARD; // turn ON LEFT wheel forward
  }
}

void left_wheel_forward_off(void){
//==============================================================================
// Left Wheel Forward Off
// 
// Description: This function turns the left motor off
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
  if(P3IN & L_FORWARD){ // is the left wheel going forward?
    P3OUT &= ~L_FORWARD; // turn OFF left wheel forward
  }
}

void right_wheel_forward_on(void){
//==============================================================================
// Right Wheel Forward On
// 
// Description: This function turns on the right motor for forward use
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
  if(!(P3IN & R_FORWARD)){ // is the RIGHT wheel NOT going forward?
    //right_wheel_reverse_off(); // making sure RIGHT wheel is NOT reversing
    P3OUT |= R_FORWARD; // turn ON RIGHT wheel forward
  }
}

void right_wheel_forward_off(void){
//==============================================================================
// Right Wheel Forward Off
// 
// Description: This function turns the right motor off
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
  if(P3IN & R_FORWARD){ // is the RIGHT wheel going forward?
    P3OUT &= ~R_FORWARD; // turn OFF RIGHT wheel forward
  }
}

void left_wheel_reverse_on(void){
  if(!(P3IN & L_REVERSE)){ // is the LEFT wheel going reverse?
    left_wheel_forward_off();
    P3OUT |= L_REVERSE; // turn ON LEFT wheel reverse
  }
}
void left_wheel_reverse_off(void){
  if(P3IN & L_REVERSE){ // is the LEFT wheel going reverse?
    P3OUT &= ~L_REVERSE; // turn OFF RIGHT wheel reverse
  }
}
void right_wheel_reverse_on(void){
  if(!(P3IN & R_REVERSE)){ // is the RIGHT wheel going reverse?
    right_wheel_forward_off();
    P3OUT |= R_REVERSE; // turn ON RIGHT wheel reverse
  }
}
void right_wheel_reverse_off(void){
  if(P3IN & R_REVERSE){ // is the RIGHT wheel going reverse?
    P3OUT &= ~R_REVERSE; // turn OFF RIGHT wheel reverse
  }
}
