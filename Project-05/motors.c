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
extern volatile unsigned int right_forward_rate;
extern volatile unsigned int right_reverse_rate;
extern volatile unsigned int left_forward_rate;
extern volatile unsigned int left_reverse_rate;

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
  P3SEL0  |= L_FORWARD;      // L_FORWARD selected	TB		(0)        
  P3SEL1  &= ~L_FORWARD;	// L_FORWARD selected   TB		(1)
     
  if(!(P3SEL0 & L_REVERSE)){ // is the LEFT wheel NOT going forward?
    left_wheel_reverse_off();
    TB2CCR1 = left_forward_rate;
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
  P3SEL0  &= ~L_FORWARD;      // L_FORWARD selected	GPIO		(0)        
  P3SEL1  &= ~L_FORWARD;	// L_FORWARD selected	GPIO		(0)
  //if(P3IN & L_FORWARD){ // is the left wheel going forward?
    TB2CCR1 = SWITCH_OFF;
  //}
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
  P3SEL0  |= R_FORWARD;      // R_FORWARD selected	TB		(0)        
  P3SEL1  &= ~R_FORWARD;	// R_FORWARD selected   TB		(1)

  if(!(P3SEL0 & R_REVERSE)){ // is the RIGHT wheel NOT going forward?
    right_wheel_reverse_off(); // making sure RIGHT wheel is NOT reversing
    TB1CCR1 = right_forward_rate;
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
  P3SEL0  &= ~R_FORWARD;      // R_FORWARD selected	GPIO		(0)        
  P3SEL1  &= ~R_FORWARD;	// R_FORWARD selected	GPIO		(0)
  //if(P3IN & R_FORWARD){         // is the RIGHT wheel going forward?
    TB1CCR1 =SWITCH_OFF;
  //}
}

void left_wheel_reverse_on(void){
  P3SEL0  |= L_REVERSE;      // L_FORWARD selected	TB		(0)        
  P3SEL1  &= ~L_REVERSE;	// L_FORWARD selected   TB		(1)
  if(!(P3SEL0 & L_FORWARD)){ // is the LEFT wheel going reverse?
    left_wheel_forward_off();
    TB2CCR2 = left_reverse_rate;
  }
}

void left_wheel_reverse_off(void){
  P3SEL0  &= ~L_REVERSE;      // L_REVERSE selected	GPIO		(0)        
  P3SEL1  &= ~L_REVERSE;	// L_REVERSE selected	GPIO		(0)
  //if(P3IN & L_REVERSE){ // is the LEFT wheel going reverse?
    TB2CCR2 = SWITCH_OFF;
  //}
}

void right_wheel_reverse_on(void){
  P3SEL0  |= R_REVERSE;         // R_REVERSE selected	TB		(0)        
  P3SEL1  &= ~R_REVERSE;	// R_REVERSE selected   TB		(1)
  if(!(P3SEL0 & R_FORWARD)){      // is the RIGHT wheel going reverse?
    right_wheel_forward_off();
    TB1CCR2 = right_reverse_rate;   // P3.5 Right Reverse PWM duty cycle
  }
}

void right_wheel_reverse_off(void){
  P3SEL0  &= ~R_REVERSE;      // R_REVERSE selected	GPIO		(0)        
  P3SEL1  &= ~R_REVERSE;	// R_REVERSE selected	GPIO		(0)
  //if(P3IN & R_REVERSE){ // is the RIGHT wheel going reverse?
    TB1CCR2 = SWITCH_OFF;
  //}
}

void toggle_IR_LED(void){
  P1OUT   ^= IR_LED;     // P1 IR_LED Port Pin toggle
}
