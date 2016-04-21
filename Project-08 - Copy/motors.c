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
extern unsigned int start_on_whiteFG;
extern volatile unsigned int motor_time;
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int right_forward_rate;
extern volatile unsigned int right_reverse_rate;
extern volatile unsigned int left_forward_rate;
extern volatile unsigned int left_reverse_rate;
extern unsigned int thresholdR;
extern unsigned int thresholdL;

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

void IR_LED_ON(void){
  P1OUT   |= IR_LED;     // P1 IR_LED Port Pin toggle
}

void IR_LED_OFF(void){
  P1OUT   &= ~IR_LED;     // P1 IR_LED Port Pin toggle
}

void active_breaking_left(void){
  left_wheel_reverse_on();
  Five_msec_Delay(1);
  left_wheel_reverse_off();
}

void active_breaking_right(void){
  right_wheel_reverse_on();
  Five_msec_Delay(1);
  right_wheel_reverse_off();
}

void blackline(void){
  unsigned int errorR=FALSE;
  unsigned int errorL=FALSE;
  unsigned int motor_time_prev=RESET;
  
  if(start_on_whiteFG){
    start_on_whiteFG = FALSE; //only want this first time
    left_wheel_forward_on(); //go forward
    right_wheel_forward_on();
    while(ADC_Left_Detector < thresholdL && ADC_Right_Detector < thresholdR); //do this until on black line
    left_wheel_forward_off();
    right_wheel_forward_off();
  }
  motor_time = RESET; //clear time counter to zero
        
  while(ADC_Right_Detector < thresholdR){//while loop for pivot correcting back from right sensor leaving
    left_wheel_forward_off();
    right_wheel_forward_on();
    while(ADC_Right_Detector < thresholdR); //do this until right sensor back on line
    right_wheel_forward_off();
    active_breaking_right();
    errorR = TRUE;
  }
  motor_time_prev = motor_time/3;//assign current time/2 count to temp time count for error correcting
  if(errorR){//if statement checking if left spin correction needed from correcting right pivot
    left_wheel_forward_on();
    right_wheel_reverse_on();
    motor_time = RESET; //to count back up to previous time;
    while(motor_time < motor_time_prev && motor_time <= 500); //turn until time reached
    right_wheel_reverse_off();
    left_wheel_forward_off();
  }
        
  motor_time = RESET; //clear time counter to zero
        
  while((ADC_Left_Detector) < thresholdL){//while loop for pivot correcting back from left sensor leaving
    right_wheel_forward_off();
    left_wheel_forward_on();
    while(ADC_Left_Detector < thresholdL); //do this until left sensor back on line
    left_wheel_forward_off();
    active_breaking_left();
    errorL = TRUE;
  }
  motor_time_prev = motor_time/3;//assign current time/2 count to temp time count for error correcting
  if(errorL){//if statement checking if right spin correction needed from correcting left pivot
    right_wheel_forward_on();
    left_wheel_reverse_on();
    motor_time = RESET; //to count back up to previous time;
    while(motor_time < motor_time_prev && motor_time <= 500); //turn until time reached
    left_wheel_reverse_off();
    right_wheel_forward_off();
  }
        
      
  while((ADC_Left_Detector) >= thresholdL && ADC_Right_Detector >= thresholdR){//if both sensors on black then go forward (WHILE)
    left_wheel_forward_on(); //go forward
    right_wheel_forward_on();
  }
}
