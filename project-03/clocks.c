//------------------------------------------------------------------------------
//  File Name : clocks.c
//
//  Description: This file contains the Clock Initialization 
//
//  Jim Carlson
//  Jan 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"

//MACROS========================================================================
#define FLLN_BITS          (0x03ffu)
#define FLLN_255           (0x00ffu)
#define CSLOCK                  (0x01) // Any incorrect password locks registers

// Port J Pins
#define XINR                 (0x10) // XINR
#define XOUTR                (0x20) // XOUTR
#define CLEAR_REGISTER     (0X0000)

void Init_Clocks(void);

void Init_Clocks(void){
//------------------------------------------------------------------------------
// Clock Configurtaions
// This is the clock initialization for the program.
//
// Initial clock configuration, runs immediately after boot.
// Disables 1ms watchdog timer, 
//      configure MCLK to 8MHz
//      configure SMCLK to 8MHz.  
// Since the X1 oscillator is not currently connected, 
// X1CLK is an unknown speed (probably ~10kHz).
//------------------------------------------------------------------------------
  WDTCTL = WDTPW | WDTHOLD;  // Disable watchdog
//  PJSEL0 |= XINR;
//  PJSEL0 |= XOUTR;
  
// Clocks:
// Clock System Control 0 Register
  CSCTL0 = CSKEY;            // Unlock register
  
// Clock System Control 1 Register
  CSCTL1 = CLEAR_REGISTER;   // Clear register
  CSCTL1 &= ~DCORSEL;        // DCO range select. For high-speed devices,
                             // this bit can be written by the user.
                             // For low-speed devices, it is always reset.
//  CSCTL1 |= DCOFSEL_0;     // Set 5.33MHz DCO or 16MHz  
//  CSCTL1 |= DCOFSEL_1;     // Set 6.67MHz DCO or 20MHz 
//  CSCTL1 |= DCOFSEL_2;     // Set 5.33MHz DCO or 16MHz
  CSCTL1 |= DCOFSEL_3;       // Set 8MHz DCO or 24MHz
  
// Clock System Control 2 Register
  CSCTL2 = CLEAR_REGISTER;   // Clear register
//  CSCTL2 |= SELA_0;        // set ACLK = XT1; 
  CSCTL2 = SELA_1;           // set ACLK = vlo;
  CSCTL2 |= SELS_3;          // set SMCLK = DCO;
  CSCTL2 |= SELM_3;          // set MCLK = DCO
  
// Clock System Control 3 Register
  CSCTL3 = CLEAR_REGISTER;   // Clear register
  CSCTL3 |= DIVA_0;          // set ACLK clock divider /1
  CSCTL3 |= DIVS_0;          // set SMCLK clock divider /1
  CSCTL3 |= DIVM_0;          // set MCLK clock divider /1
  
// Clock System Control 4 Register
  CSCTL4 = CLEAR_REGISTER;   // Clear register
  CSCTL4 &= ~XT1OFF;         // XT1 is on if XT1 is selected by the port selection and XT1 is not in bypass 
  CSCTL4 &= ~SMCLKOFF;       // SMCLK is not Off 
  CSCTL4 &= ~XT1BYPASS;      // XT1 sourced from external crystal 
  CSCTL4 &= ~XTS;            // Low-frequency mode
  CSCTL4 |= XT1DRIVE_0;      // Lowest current consumption for XT1 LF mode. 
                             // XT1 oscillator operating range in HF mode is 4 MHz to 8 MHz.
  CSCTL4 |= XT2OFF;          // High Frequency Oscillator 2 (XT2) disable 
  
  CSCTL0_H = CSLOCK;         // Lock registers
//------------------------------------------------------------------------------
}


