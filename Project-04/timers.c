//------------------------------------------------------------------------------
//  File Name : timers.c
//
//  Description: This file contains the Timing functions (Five_msec_Delay, Timer_code)
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
// LCD_HOME_L1	                        (0x80)
// LCD_HOME_L2         	                (0xA0)
// LCD_HOME_L3         	                (0xC0)
// LCD_HOME_L4         	                (0xE0)
// SWITCH_OFF				(0x00) 
// SWITCH_ON				(0x01)
// INCREMENT_ONCE                       (0x01)   // increment by 1
// MAX_FIVE_MSEC_COUNT                  (0x03E8) //1000
//------------------------------------------------------------------------------
//GLOBALS
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
extern volatile unsigned int five_msec_delay;
extern char display_line_1[LINE_SIZE];
extern char display_line_2[LINE_SIZE];
extern char display_line_3[LINE_SIZE];
extern char display_line_4[LINE_SIZE];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
//------------------------------------------------------------------------------
void Five_msec_Delay(unsigned int fivemsec){
//==============================================================================
// Five msec sleep
// 
// Description: Each count passed is at least x times 5 milliseconds
//
// Passed : unsigned int fivemsec
// Locals: no variables declared
// Returned: no values returned
// Globals:     volatile unsigned int five_msec_count;
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  five_msec_delay = SWITCH_OFF;
  while(five_msec_delay <= fivemsec);
//------------------------------------------------------------------------------
}

void Timer_code(void){
//==============================================================================
// Timer A0 interrupt code
// 
// Description: Not sure yet...
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:     volatile unsigned int Time_Sequence;
//              volatile char one_time;
//              volatile unsigned int five_msec_count;
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  Time_Sequence++;
  one_time = SWITCH_ON;
  if (five_msec_delay < MAX_FIVE_MSEC_COUNT){
    five_msec_delay++;
  }
//------------------------------------------------------------------------------
}

void Display_Process(void){
//==============================================================================
// Display Process interrupt code
// 
// Description: This function ends out text for display
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:     char* display_1
//              char* display_2
//              char* display_3
//              char* display_4
//              char posL1
//              char posL2
//              char posL3
//              char posL4
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
}


void Init_Timer_A0(void){
//==============================================================================
// Timer A0 init code
// 
// Description: initializes values for timer interrupt
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:     none
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
// Timer A0 initialization sets up both A0_0 and A0_1-A0_2
 TA0CTL = TASSEL__SMCLK; // SMCLK source
 TA0CTL |= TACLR; // Resets TA0R, clock divider, count direction
 TA0CTL |= MC__CONTINOUS; // Continuous up
 TA0CTL |= ID__2; // Divide clock by 2
 TA0CTL &= ~TAIE; // Disable Overflow Interrupt
 TA0CTL &= ~TAIFG; // Clear Overflow Interrupt flag

 TA0EX0 = TAIDEX_7; // Divide clock by an additional 8

 TA0CCR0 = TA0CCR0_INTERVAL; // CCR0
 TA0CCTL0 |= CCIE; // CCR0 enable interrupt

 TA0CCR1 = TA0CCR1_INTERVAL; // CCR1
 TA0CCTL1 |= CCIE; // CCR1 enable interrupt

// TA0CCR2 = TA0CCR2_INTERVAL; // CCR2
// TA0CCTL2 |= CCIE; // CCR2 enable interrupt
}
//------------------------------------------------------------------------------ 
