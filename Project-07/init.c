//------------------------------------------------------------------------------
//
//  Description: This file contains the Initialize functions
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
// IOT_WAKEUP           	                (0x01) // This was LED 1
// IOT_FACTORY   			        (0x02) // This was LED 2
// IOT_STA_MINIAP       	                (0x04) // This was LED 3
// R_FORWARD        	                        (0x10) // This was LED 5
// R_REVERSE        	                        (0x20) // This was LED 6
// L_FORWARD        	                        (0x40) // This was LED 7
// L_REVERSE        	                        (0x80) // This was LED 8
//------------------------------------------------------------------------------
// GLOBAL VARIABLES
extern char display_line_1[LINE_SIZE];
extern char display_line_2[LINE_SIZE];
extern char display_line_3[LINE_SIZE];
extern char display_line_4[LINE_SIZE];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern volatile unsigned int usb_rx_ring_wr0;
extern volatile unsigned int usb_rx_ring_rd0;
extern volatile unsigned int usb_tx_ring_wr0;
extern volatile unsigned int usb_tx_ring_rd0;
extern volatile unsigned int usb_rx_ring_wr1;
extern volatile unsigned int usb_rx_ring_rd1;
extern volatile unsigned int usb_tx_ring_wr1;
extern volatile unsigned int usb_tx_ring_rd1;
extern volatile char USB_Char_Rx0[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx0[LARGE_RING_SIZE];
extern volatile char USB_Char_Rx1[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx1[LARGE_RING_SIZE];
//------------------------------------------------------------------------------
void Init_Conditions(void){
//==============================================================================
// Initializations Configurations
// 
// Description: This function intializes display_1 through 4 pointers to start of LCD lines
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:     volatile unsigned int Time_Sequence;
//              volatile char one_time;
//              char* display_1
//              char* display_2
//              char* display_3
//              char* display_4
//              char display_line_1[LINE_SIZE];
//              char display_line_2[LINE_SIZE];
//              char display_line_3[LINE_SIZE];
//              char display_line_4[LINE_SIZE];
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
// Interrupts are disabled by default, enable them. 
  enable_interrupts();
  display_1 = &display_line_1[START];
  display_2 = &display_line_2[START];
  display_3 = &display_line_3[START];
  display_4 = &display_line_4[START];

//------------------------------------------------------------------------------
}

void Init_Timers(void){
//==============================================================================
// Timer Configurations
// 
// Description: This function initializes timers used for the board
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:     NONE
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  Init_Timer_A0(); //
//  Init_Timer_A1(); // 
//  Init_Timer_B0(); // 
  Init_Timer_B1(); //  
  Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
}

void Init_LEDs(void){
//==============================================================================
// LED Configurations
// 
// Description: This function initializes the LED output to 0
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:     NONE
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
//------------------------------------------------------------------------------
// Turns off all 8 LEDs
  PJOUT &= ~IOT_WAKEUP;
  PJOUT &= ~IOT_FACTORY;
  PJOUT &= ~IOT_STA_MINIAP;

//------------------------------------------------------------------------------
}


void Init_Serial_UCA0(int baud_choice){ //1=9600 baud, 0=115200 baud
    int i;
    for(i=0; i<SMALL_RING_SIZE; i++){
        USB_Char_Rx0[i] = 0x00; // USB Rx Buffer
    }
    usb_rx_ring_wr0 = BEGINNING;
    usb_rx_ring_rd0 = BEGINNING;

    for(i=0; i<LARGE_RING_SIZE; i++){ // May not use this
        USB_Char_Tx0[i] = 0x00; // USB Tx Buffer
    }
    usb_tx_ring_wr0 = BEGINNING;
    usb_tx_ring_rd0 = BEGINNING;
    // Configure UART 0
    UCA0CTLW0 = 0; // Use word register
    UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA0CTLW0 |= UCSWRST; // Set Software reset enable bit
    // 9,600 Baud Rate
    // 1. Calculate N = fBRCLK / Baudrate
    // N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
    // if N > 16 continue with step 3, otherwise with step 2
    // 2. OS16 = 0, UCBRx = INT(N)
    // continue with step 4
    // 3. OS16 = 1,
    // UCx = INT(N/16),
    // = INT(N/16) = 833.333/16 => 52
    // UCFx = INT([(N/16) – INT(N/16)] × 16)
    // = ([833.333/16-INT(833.333/16)]*16)
    // = (52.08333333-52)*16
    // = 0.083*16 = 1
    // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
    // Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
    // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
    // TX error (%) RX error (%)
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
    if(baud_choice==1){
        UCA0BRW = 52; // 9,600 Baud
        // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
        // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
        UCA0MCTLW = 0x4911 ;
    }
    else if(baud_choice==0){
        UCA0BRW = 4; // 115,200 Baud
        // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
        // UCA0MCTLW = 0x55 concatenate 5 concatenate 1;
        UCA0MCTLW = 0x5551 ;
    }
    UCA0CTL1 &= ~UCSWRST; // Release from reset
    UCA0IE |= UCRXIE; // Enable RX interrupt
    UCA0IE |= UCTXIE; // Enable RX interrupt

}

void Init_Serial_UCA1(int baud_choice){ //1=9600 baud, 0=115200 baud
    int i;
    for(i=0; i<SMALL_RING_SIZE; i++){
        USB_Char_Rx1[i] = 0x00; // USB Rx Buffer
    }
    usb_rx_ring_wr1 = BEGINNING;
    usb_rx_ring_rd1 = BEGINNING;

    for(i=0; i<LARGE_RING_SIZE; i++){ // May not use this
       USB_Char_Tx1[i] = 0x00; // USB Tx Buffer
    }
    usb_tx_ring_wr1 = BEGINNING;
    usb_tx_ring_rd1 = BEGINNING;
    // Configure UART 0
    UCA1CTLW0 = 0; // Use word register
    UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
    UCA1CTLW0 |= UCSWRST; // Set Software reset enable
    // 9,600 Baud Rate
    // 1. Calculate N = fBRCLK / Baudrate
    // N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
    // if N > 16 continue with step 3, otherwise with step 2
    // 2. OS16 = 0, UCBRx = INT(N)
    // continue with step 4
    // 3. OS16 = 1,
    // UCx = INT(N/16),
    // = INT(N/16) = 833.333/16 => 52
    // UCFx = INT([(N/16) – INT(N/16)] × 16)
    // = ([833.333/16-INT(833.333/16)]*16)
    // = (52.08333333-52)*16
    // = 0.083*16 = 1
    // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
    // Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
    // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
    // TX error (%) RX error (%)
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
    if(baud_choice==1){
        UCA1BRW = 52; // 9,600 Baud
        // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
        // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
        UCA1MCTLW = 0x4911 ;
    }
    else if(baud_choice==0){
        UCA1BRW = 4; // 115,200 Baud
        // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
        // UCA0MCTLW = 0x55 concatenate 5 concatenate 1;
        UCA1MCTLW = 0x5551 ;
    }
    UCA1CTL1 &= ~UCSWRST; // Release from reset
    UCA1IE |= UCRXIE; // Enable RX interrupt
    UCA1IE |= UCTXIE; // Enable RX interrupt

}