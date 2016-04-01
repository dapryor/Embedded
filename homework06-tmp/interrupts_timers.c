//------------------------------------------------------------------------------
//  File Name : interrupts_timers.c
//
//  Description: This file contains the interrupts used for timers
//
//
//  David Pryor
//  Feb 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
#include "macros.h"
#include "functions.h"
#include "msp430.h"
extern volatile unsigned int switch_one_pressed;
extern volatile unsigned int switch_two_pressed;
extern volatile unsigned int switch_one_debounce;
extern volatile unsigned int switch_two_debounce;
extern volatile unsigned int debounce_count_one;
extern volatile unsigned int debounce_count_two;
volatile unsigned int LCD_Count = 0;
extern char *display_4;


//------------------------------------------------------------------------------
// TimerA0 0 Interrupt handler
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
  //==============================================================================
  // Timer A0 interrupt CCR0
  // 
  // Description: creates the interrupt for the timer CCR0
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals:     extern volatile unsigned int switch_one_pressed;
  //              extern volatile unsigned int switch_two_pressed;
  //              extern volatile unsigned int switch_one_debounce;
  //              extern volatile unsigned int switch_two_debounce;
  //              extern volatile unsigned int debounce_count_one;
  //              extern volatile unsigned int debounce_count_two;
  //
  // Author: David Pryor
  // Date: Feb 2016
  // Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
  //============================================================================

  if(debounce_count_one < DEBOUNCE_MAX){
    debounce_count_one++;       //if # of overflows is less than required increment
  }
  if(debounce_count_two < DEBOUNCE_MAX){
    debounce_count_two++;       //if # of overflows is less than required increment
  }
  if(debounce_count_one >= DEBOUNCE_MAX){
    P4IFG &= ~SW1;              //clear interrupts
    P4IE |= SW1;                //enable switch interrupts
    switch_one_debounce = SWITCH_OFF;
  }
  if(debounce_count_two >= DEBOUNCE_MAX){
    P4IFG &= ~SW2;              //clear interrupts
    P4IE |= SW2;                //enable switch interrupts
    switch_two_debounce = SWITCH_OFF;
  }
  if(!switch_two_debounce && !switch_one_debounce){ //if no debounces
    TA0CCTL0 &= ~CCIE;          //turn off interrupt
    display_4 = "";             //clear display
    Display_Process();          //push display
  }
  else{
    P3OUT &= ~LCD_BACKLITE;
  }
  
  TA0CCR0 += TA0CCR0_INTERVAL;  // Add Offset to TACCR0
}
//----------------------------------------------------------------------------

// TimerA0 1-2, Overflow Interrupt Vector (TAIV) handler
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
  //==============================================================================
  // Timer A0 interrupt CCR1 and 2
  // 
  // Description: creates the interrupt for the timer CCR1 and CCR2
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals:     extern volatile unsigned int switch_one_pressed;
  //              extern volatile unsigned int switch_two_pressed;
  //              extern volatile unsigned int switch_one_debounce;
  //              extern volatile unsigned int switch_two_debounce;
  //              volatile unsigned int LED_Count
  //
  // Author: David Pryor
  // Date: Feb 2016
  // Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
  //============================================================================
 switch(__even_in_range(TA0IV,14)){
 case 0: break;                 // No interrupt
 
 case CCR1:                     // CCR1 not used
 LCD_Count++;                   //increment 
 
 if(LCD_Count == DEBOUNCE_MAX && switch_one_debounce == SWITCH_OFF && switch_two_debounce == SWITCH_OFF){ //Toggle LCD if no debounces happening
  LCD_Count = SWITCH_OFF;       //reset count
  P3OUT ^= LCD_BACKLITE;        //toggle backlite
 }
 
 if(LCD_Count == DEBOUNCE_MAX){ //if the first if isnt hit then reset LCD_Count
  LCD_Count = SWITCH_OFF;
 }
 
 TA0CCR1 += TA0CCR1_INTERVAL;   // Add Offset to TACCR1
 break;
 
 //case CCR2: // CCR2 not used
 //...... Add What you need happen in the interrupt ......
 //TA0CCR2 += TA0CCR2_INTERVAL; // Add Offset to TACCR2
 //break;
 //case OVERFLOW: // overflow
 //...... Add What you need happen in the interrupt ......
 //break;
 default: break;
 }
}
//----------------------------------------------------------------------------