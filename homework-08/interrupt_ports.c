//------------------------------------------------------------------------------
//  File Name : interrupts_ports.c
//
//  Description: This file contains the interrupts used for switches
//
//
//  David Pryor
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
#include "macros.h"
#include "functions.h"
#include "msp430.h"

 volatile unsigned int switch_one_pressed;
 volatile unsigned int switch_two_pressed;
 volatile unsigned int switch_one_debounce;
 volatile unsigned int switch_two_debounce;
 volatile unsigned int debounce_count_one = SWITCH_OFF;
 volatile unsigned int debounce_count_two = SWITCH_OFF;
 extern volatile unsigned int do_this;


#pragma vector=PORT4_VECTOR
__interrupt void switch_interrupt(void){
  //==============================================================================
  // Creates interrupts for sw1 and sw2
  // 
  // Description: creates the interrupt for the timer sw1 and sw2
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals:     extern volatile unsigned int switch_one_pressed
  //              extern volatile unsigned int switch_two_pressed
  //              extern volatile unsigned int switch_one_debounce
  //              extern volatile unsigned int switch_two_debounce
  //              volatile unsigned int debounce_count_one
  //              volatile unsigned int debounce_count_two
  //
  // Author: David Pryor
  // Date: Feb 2016
  // Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
  //============================================================================
 // Switch 1
 if ((P4IFG & SW1) && !switch_one_debounce) {
 switch_one_pressed = SWITCH_ON;        // Set a variable to identify the switch has been pressed.
 switch_one_debounce = SWITCH_ON;       // Set a variable to identify the switch is being debounced.
 debounce_count_one = SWITCH_OFF;       // Reset the count required of the debounce.
 P4IE &= ~SW1;                         // Disable the Switch Interrupt.
 TA0CCTL0 &= ~CCIFG;                       // Clear any current timer interrupt.
 do_this = TRUE;
 }
 
 // Switch 2
 if ((P4IFG & SW2) && !switch_two_debounce) {
 switch_two_pressed = SWITCH_ON;        // Set a variable to identify the switch has been pressed.
 switch_two_debounce = SWITCH_ON ;      // Set a variable to identify the switch is being debounced.
 debounce_count_two = SWITCH_OFF;       // Reset the count required of the debounce.
 P4IE &= ~SW2;                         // Disable the Switch Interrupt.
 TA0CCTL0 &= ~CCIFG;                       // Clear any current timer interrupt.   
 }
 TA0CCTL0 |= CCIE;  
 
}