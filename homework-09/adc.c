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
extern char adc_char[5];
extern unsigned int threshold;
extern unsigned int left_calibration_black;
extern unsigned int right_calibration_black;
extern unsigned int left_calibration_white;
extern unsigned int right_calibration_white;
extern unsigned int left_calibration_ambient;
extern unsigned int right_calibration_ambient;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int right_forward_rate;
extern volatile unsigned int right_reverse_rate;
extern volatile unsigned int left_forward_rate;
extern volatile unsigned int left_reverse_rate;
volatile unsigned int P5_counter;
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern volatile unsigned int switch_one_pressed;
extern volatile unsigned int switch_two_pressed;
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ADC_Right_Detector;

void ADC_Process(void){
 //==============================================================================
 // ADC Process
 // 
 // Description: sampling and conversion if ready
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
  ADC10CTL0 |= ADC10ON;
  while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
  ADC10CTL0 |= ADC10ENC + ADC10SC; // Sampling and conversion start
  ADC10CTL0 &= ~ADC10ON;
}

void Init_ADC(void){
 //==============================================================================
 // Configure ADC10_B
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
 ADC10CTL0 = SWITCH_OFF; // Clear ADC10CTL0
 ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
 ADC10CTL0 &= ~ADC10MSC; // Single Sequence
 ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled
 ADC10CTL1 = SWITCH_OFF; // Clear ADC10CTL1
 ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
 ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
 ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
 ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by 1.
 ADC10CTL1 |= ADC10SSEL_0; // MODCLK
 ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion
 ADC10CTL2 = SWITCH_OFF; // Clear ADC10CTL2
 ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
 ADC10CTL2 |= ADC10RES; // 10-bit resolution
 ADC10CTL2 &= ~ADC10DF; // Binary unsigned
 ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps
 ADC10MCTL0 = SWITCH_OFF; // Clear ADC10MCTL0
 ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
 ADC10MCTL0 |= ADC10INCH_3; // Channel A3 Thumb Wheel
 ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt
}

void HEXtoBCD(int hex_value){
 //==============================================================================
 // Hex to BCD Conversion
 // 
 // Description: Convert a Hex number to a BCD for display on an LCD or monitor
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
  
  int value;
  adc_char[0] = '0';
  adc_char[1] = '0';
  adc_char[2] = '0';
  adc_char[3] = '0';
  if (hex_value > 1000){
    hex_value = hex_value - 1000;
    adc_char[0] = '1';
  }
  value = 0;
  while (hex_value > 99){
    hex_value = hex_value - 100;
    value = value + 1;
    adc_char[1] = 0x30 + value;
  }
  value = 0;
    while (hex_value > 9){
    hex_value = hex_value - 10;
    value = value + 1;
    adc_char[2] = 0x30 + value;
  }
  adc_char[3] = 0x30 + hex_value;

}
//******************************************************************************
//------------------------------------------------------------------------------

void Project5(void){
 //==============================================================================
 // Project 5
 // 
 // Description: does specified task for project 5
 //
 // Passed :     no variables passed
 // Locals:      int count
 // Returned:    no values returned
 // Globals:     right_forward_rate
 //              left_forward_rate
 //              display_1
 //              display_2
 //              display_3
 //              display_4
 //              P5_counter
 //
 // Author: David Pryor
 // Date: March 2016
 // Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
 //==============================================================================
  int count = SWITCH_OFF;
  toggle_IR_LED();
  Five_msec_Delay(FOR_TWO_SECOND);
  right_forward_rate = FIFTY_PERCENT; // turn ON RIGHT wheel forward
  left_forward_rate = FORTYSEVEN_PERCENT; // turn ON LEFT wheel forward
  right_wheel_forward_on();
  left_wheel_forward_on();
  
  display_1 = "Forward";
  display_2 = "";
  display_3 = "";
  display_4 = "";
  Display_Process();
  
  while(TRUE){
    ADC_Process();
    if(ADC_Right_Detector >= threshold){
      right_wheel_forward_off();
      left_wheel_forward_off();
      break;
    }
  }  
  Five_msec_Delay(FOR_TWO_SECOND);
  P5_counter=SWITCH_OFF;
  
  display_1 = "Reverse";
  display_2 = "";
  display_3 = "";
  display_4 = "";
  Display_Process();
  
  right_reverse_rate = FIFTY_PERCENT;
  left_reverse_rate = FIFTY_PERCENT;
  right_wheel_reverse_on();
  left_wheel_reverse_on();
  Five_msec_Delay(FOR_ONE_SECOND);
  
  while(TRUE){
    ADC_Process();
    if(ADC_Right_Detector >= threshold){
      right_wheel_reverse_off();
      left_wheel_reverse_off();
      break;
    }  
  }
  count = P5_counter / HALF;
  HEXtoBCD(P5_counter*FIVE_MSEC);
  display_1 = "";
  display_2 = "";
  display_3 = "";
  display_4 = adc_char;
  Display_Process();
  Five_msec_Delay(FOR_FIVE_SECONDS);
  
  display_1 = "Forward";
  display_2 = "";
  display_3 = "";
  display_4 = "";
  Display_Process();
  
  right_forward_rate = FIFTY_PERCENT; // turn ON RIGHT wheel forward
  left_forward_rate = FORTYSEVEN_PERCENT; // turn ON LEFT wheel forward
  right_wheel_forward_on();
  left_wheel_forward_on();
  Five_msec_Delay(count);
  right_wheel_forward_off();
  left_wheel_forward_off();
  
  Five_msec_Delay(FOR_TWO_SECOND);
  
  display_1 = "CW";
  display_2 = "";
  display_3 = "";
  display_4 = "";
  Display_Process();
  
  clockwise_spin();
  clockwise_spin();
  Five_msec_Delay(FOR_ONE_SECOND);
  
  display_1 = "CCW";
  display_2 = "";
  display_3 = "";
  display_4 = "";
  Display_Process();
  
  counterclockwise_spin();
  counterclockwise_spin();
  counterclockwise_spin();
  
  
  toggle_IR_LED();
}

void IR_Calibration(void){
  int proceed = 0;
  display_1 = "Ambient Test";
  display_2 = "Press SW2";
  display_3 = "";  
  display_4 = "";
  Display_Process();
  while(proceed == 0){
    if(switch_two_pressed){
      proceed = 1;
      switch_two_pressed = FALSE;
    }
  }

  ADC_Process();              // call sampling function
  right_calibration_ambient = ADC_Right_Detector;
  left_calibration_ambient = ADC_Left_Detector;
  proceed = 0;
  
  toggle_IR_LED();
  Five_msec_Delay(30);
  display_1 = "White Test";
  display_2 = "Press SW2";
  display_3 = "";  
  display_4 = "";
  Display_Process();
  while(proceed == 0){
    if(switch_two_pressed){
      proceed = 1;
      switch_two_pressed = FALSE;
    }
  }
  ADC_Process();              // call sampling function
  right_calibration_white = ADC_Right_Detector;
  left_calibration_white = ADC_Left_Detector;
  proceed = 0;
  
  display_1 = "Black Test";
  display_2 = "Press SW2";
  display_3 = "";  
  display_4 = "";
  Display_Process();
  while(proceed == 0){
    if(switch_two_pressed){
      proceed = 1;
      switch_two_pressed = FALSE;
    }
  }
  ADC_Process();              // call sampling function
  right_calibration_black = ADC_Right_Detector;
  left_calibration_black = ADC_Left_Detector;
    
  toggle_IR_LED();
  threshold = right_calibration_ambient - right_calibration_black + 50;
  
}

