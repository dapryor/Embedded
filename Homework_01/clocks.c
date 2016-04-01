//------------------------------------------------------------------------------
//  Description: This file contains the Clock Initialization 
//
//  Jim Carlson
//  Aug 2014
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"

#define CSLOCK                  (0x01) // Any incorrect password locks registers
#define MCLK_FREQ           (8000000L)
#define SMCLK_FREQ          (8000000L)
#define SMCLK_DIV                 (64)

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
  WDTCTL = WDTPW | WDTHOLD;            // Disable watchdog
// Clocks:
  CSCTL0 = CSKEY;                      // Unlock register
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;       // Set max. DCO setting [8MHz]
  CSCTL2 = SELA_1 + SELS_3 + SELM_3;   // set ACLK = vlo; SMCLK = DCO; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_0 + DIVM_0;   // set all dividers /1
  CSCTL0_H = CSLOCK;                   // Lock registers
//------------------------------------------------------------------------------
}

