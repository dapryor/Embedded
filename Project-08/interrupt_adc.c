//------------------------------------------------------------------------------
//  File Name : interrupts_adc.c
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
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Thumb;
volatile unsigned int channel;
//==============================================================================
// interrupt ADC code
// 
// Description: sets up ISR for ADC
//
// Passed :     no variables passed
// Locals:      no variables declared
// Returned:    no values returned
// Globals:     ADC_Thumb
//              ADC_Left_Detector
//              ADC_Right_Detector
//
// Author: David Pryor
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
// ADC10 interrupt service routine
// ADC_Right_Detector; // A00 ADC10INCH_0 - P1.0
// ADC_Left_Detector; // A01 ADC10INCH_1 - P1.1
// ADC_Thumb; // A03 ADC10INCH_3 - P1.3
// ADC_Temp; // A10 ADC10INCH_10 – Temperature REF module
// ADC_Bat; // A11 ADC10INCH_11 - Internal
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
  switch(__even_in_range(ADC10IV,CASE_ITEM_SEVEN)) {
    case MENU_ITEM_ONE: break; // No interrupt
    case CASE_ITEM_TWO: break; // conversion result overflow
    case CASE_ITEM_THREE: break; // conversion time overflow
    case CASE_ITEM_FOUR: break; // ADC10HI
    case CASE_ITEM_FIVE: break; // ADC10LO
    case CASE_ITEM_SIX: break; // ADC10IN
    case CASE_ITEM_SEVEN:
      // Need this to change the ADC10INCH_x value.
      ADC10CTL0 &= ~ADC10ENC; // Turn off the ENC bit of the ADC10CTL0
      switch (channel){
        case MENU_ITEM_ONE:
          ADC10MCTL0 = ADC10INCH_1; // Next channel A1
          ADC_Left_Detector = ADC10MEM0; // Current Channel result for A0
          channel++;
          break;
        case MENU_ITEM_TWO:
          ADC10MCTL0 = ADC10INCH_3; // Next channel A3
          ADC_Right_Detector = ADC10MEM0; // Current Channel result for A1
          channel++;
          break;
        case MENU_ITEM_THREE:
          ADC10MCTL0 = ADC10INCH_0; // Next channel A0
          ADC_Thumb = ADC10MEM0; // Current Channel result for A3
          channel = SWITCH_OFF;
          break;
        default:
          break;
        }
      ADC10CTL0 |= ADC10ENC; // Turn on the ENC bit of the ADC10CTL0
      ADC10CTL0 |= ADC10SC; // Start next sample.
      break;
    default: break;
  }
}
//------------------------------------------------------------------------------