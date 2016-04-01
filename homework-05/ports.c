//------------------------------------------------------------------------------
//  File Name : ports.c
//
//  Description: This file contains the Port Initialize function
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

void Init_Ports(void){
// //==============================================================================
// PORT configuration: 
// 
// Description: This function runs the individual port initializes
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
// MACROS
// USE_SMCLK                               (0x01)
// configures all ports	
	Init_Port1();
	Init_Port2();
	Init_Port3();
	Init_Port4();
	Init_PortJ(USE_SMCLK);
}

void Init_Port1(void){
//==============================================================================
// Configure Port 1
// 
// Description: This functions initializes all pins for port 1
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
// V_DETECT_R			(0x01) //
// V_DETECT_L			(0x02) //
// IR_LED			(0x04) //
// V_THUMB			(0x08) //
// SPI_CS_LCD			(0x10) // LCD Chip Select
// RESET_LCD			(0x20) // LCD Reset
// SIMO_B			(0x40) // SPI mode - slave in/master out of USCI_B0
// SOMI_B			(0x80) // SPI mode - slave out/master in of USCI_B0
// EMPTY_REGISTER		(0x00)
// SET_INPUT			(0x00) // value to set port as input
//------------------------------------------------------------------------------
P1SEL0  = EMPTY_REGISTER;// P1 set as I/0
P1SEL1  = EMPTY_REGISTER;// P1 set as I/0
P1DIR   = SET_INPUT;    // Set P1 direction to input

P1SEL0  |= V_DETECT_R;  // V_DETECT_R selected                  (1)
P1SEL1  |= V_DETECT_R;  // V_DETECT_R selected	                (1)

P1SEL0  |= V_DETECT_L;  // V_DETECT_L selected	                (1)
P1SEL1  |= V_DETECT_L;  // V_DETECT_L selected	                (1)

P1SEL0  &= ~IR_LED;     // IR_LED GPI/O selected		(0)
P1SEL1  &= ~IR_LED;     // IR_LED GPI/O selected		(0)
P1OUT   &= ~IR_LED;     // P1 IR_LED Port Pin set low		(0)
P1DIR   |= IR_LED;      // Set P1 IR_LED direction to output	(1)

P1SEL0  |= V_THUMB;     // V_THUMB selected	                (1)
P1SEL1  |= V_THUMB;     // V_THUMB selected	                (1)

P1SEL0  &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected		(0)
P1SEL1  &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected		(0)
P1OUT   |= SPI_CS_LCD;  // P1 SPI_CS_LCD Port Pin set high	(1)
P1DIR   |= SPI_CS_LCD;  // Set SPI_CS_LCD output direction 	(1)

P1SEL0  &= ~RESET_LCD;  // RESET_LCD GPI/O selected		(0)
P1SEL1  &= ~RESET_LCD;  // RESET_LCD GPI/O selected		(0)
P1OUT   &= ~RESET_LCD;  // RESET_LCD Port Pin set low		(0)
P1DIR   |= RESET_LCD;   // Set RESET_LCD output directio        (1)

P1SEL0  &= ~SIMO_B;     // SIMO_B selected		        (0)
P1SEL1  |= SIMO_B;      // SIMO_B selected			(1)
P1DIR   |= SIMO_B;      // SIMO_B set to Output	                (1)

P1SEL0  &= ~SOMI_B;     // SOMI_B is used on the LCD	        (0)	
P1SEL1  |= SOMI_B;      // SOMI_B is used on the LCD	        (1)
P1DIR   &= ~SOMI_B;     // SOMI_B set to Input		        (0)
P1REN   |= SOMI_B;      // Enable pullup resistor		(1)
//------------------------------------------------------------------------------
}

void Init_Port2(void){
//==============================================================================
// Configure Port 2
// 
// Description: This functions initializes all pins for port 2
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
// USB_TXD			(0x01) //
// USB_RXD			(0x02) //
// SPI_SCK			(0x04) //
// UNKNOWN1			(0x08) //
// UNKNOWN2			(0x10) // 
// CPU_TXD			(0x20) // 
// CPU_RXD			(0x40) // 
// UNKNOWN3			(0x80) // 
// EMPTY_REGISTER		(0x00) //
// SET_INPUT			(0x00) // value to set port as input
//------------------------------------------------------------------------------
P2SEL0  = EMPTY_REGISTER;// P1 set as I/0
P2SEL1  = EMPTY_REGISTER;// P1 set as I/0
P2DIR   = SET_INPUT;    // Set P1 direction to input

P2SEL0  &= ~USB_TXD;	// USB_TXD selected 			(0)
P2SEL1  |= USB_TXD;	// USB_TXD selected			(1)
P2DIR   |= USB_TXD;	// USB_TXD set to Output	        (1)

P2SEL0  &= ~USB_RXD;	// USB_RXD selected 		        (0)
P2SEL1  |= USB_RXD;	// USB_RXD selected 		        (1)
P2DIR   &= ~USB_RXD;	// USB_RXD set to Input	                (0)

P2SEL0  &= ~SPI_SCK;	// SPI_SCK selected			(0)
P2SEL1  |= SPI_SCK;	// SPI_SCK selected			(1)
P2OUT   |= SPI_SCK;	// SPI_SCK Port Pin set HIGH		(1)
P2DIR   |= SPI_SCK;	// Set SPI_SCK direction to output	(1)

P2SEL0  &= ~UNKNOWN1;	// UNKNOWN1 selected			(0)
P2SEL1  &= ~UNKNOWN1;	// UNKNOWN1 selected			(0)
P2DIR   &= ~UNKNOWN1;	// UNKNOWN1 SET TO INPUT		(0)
P2REN	&= ~UNKNOWN1;   // UNKNOWN1 disable pullup resistor

P2SEL0  &= ~UNKNOWN2;	// UNKNOWN2 selected			(0)
P2SEL1  &= ~UNKNOWN2;	// UNKNOWN2 selected			(0)
P2DIR   &= ~UNKNOWN2;	// UNKNOWN2 SET TO INPUT		(0)
P2REN	&= ~UNKNOWN2;   // UNKNOWN2 disable pullup resistor

P2SEL0  &= ~CPU_TXD;	// CPU_TXD selected 			(0)
P2SEL1  |= CPU_TXD;	// CPU_TXD selected			(1)
P2DIR   |= CPU_TXD;	// CPU_TXD set to Output	        (1)

P2SEL0  &= ~CPU_RXD;	// CPU_RXD selected 		        (0)
P2SEL1  |= CPU_RXD;	// CPU_RXD selected 		        (1)
P2DIR   &= ~CPU_RXD;	// CPU_RXD set to Input	                (0)

P2SEL0  &= ~UNKNOWN3;	// UNKNOWN3 selected			(0)
P2SEL1  &= ~UNKNOWN3;	// UNKNOWN3 selected			(0)
P2DIR   &= ~UNKNOWN3;	// UNKNOWN3 SET TO INPUT		(0)
P2REN	&= ~UNKNOWN3;   // UNKNOWN3 disable pullup resistor
//------------------------------------------------------------------------------
}

void Init_Port3(void){
//==============================================================================
// Configure Port 3
// 
// Description: This functions initializes all pins for port 3
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
// ACCEL_X		        (0x01) //
// ACCEL_Y		        (0x02) //
// ACCEL_Z		        (0x04) //
// LCD_BACKLITE		        (0x08) //
// R_FORWARD        	        (0x10) // This was LED 5
// R_REVERSE        	        (0x20) // This was LED 6
// L_FORWARD        	        (0x40) // This was LED 7
// L_REVERSE        	        (0x80) // This was LED 8
// EMPTY_REGISTER               (0x00) //
// SET_INPUT		        (0x00) // value to set port as input
//------------------------------------------------------------------------------
P3SEL0 = EMPTY_REGISTER;// P1 set as I/0
P3SEL1 = EMPTY_REGISTER;// P1 set as I/0
P3DIR  = SET_INPUT;     // Set P1 direction to input

P3SEL0  &= ~ACCEL_X;	// ACCEL_X selected 			(0)
P3SEL1  &= ~ACCEL_X;	// ACCEL_X selected			(0)
P3DIR   &= ~ACCEL_X;	// ACCEL_X set to Input		        (0)
P3REN	&= ~ACCEL_X; 	// ACCEL_X disable pullup resistor

P3SEL0  &= ~ACCEL_Y;	// ACCEL_Y selected 			(0)
P3SEL1  &= ~ACCEL_Y;	// ACCEL_Y selected			(0)
P3DIR   &= ~ACCEL_Y;	// ACCEL_Y set to Input		        (0)
P3REN   &= ~ACCEL_Y; 	// ACCEL_Y disable pullup resistor

P3SEL0  &= ~ACCEL_Z;	// ACCEL_Z selected 			(0)
P3SEL1  &= ~ACCEL_Z;	// ACCEL_Z selected			(0)
P3DIR   &= ~ACCEL_Z;	// ACCEL_Z set to Input		        (0)
P3REN   &= ~ACCEL_Z; 	// ACCEL_Z disable pullup resistor

P3SEL0  &= ~LCD_BACKLITE;// LCD_BACKLITE selected	 	(0)
P3SEL1  &= ~LCD_BACKLITE;// LCD_BACKLITE selected		(0)
P3OUT   &= ~LCD_BACKLITE;// LCD_BACKLITE Port Pin set low	(0)
P3DIR   |= LCD_BACKLITE; // LCD_BACKLITE set to Output		(1)

P3SEL0  &= ~R_FORWARD;	// R_FORWARD selected 			(0)
P3SEL1  &= ~R_FORWARD;	// R_FORWARD selected			(0)
P3OUT   &= ~R_FORWARD;	// R_FORWARD Port Pin set low		(0)
P3DIR   |= R_FORWARD;	// R_FORWARD set to Output	        (1)

P3SEL0  &= ~R_REVERSE;	// R_REVERSE selected	 		(0)
P3SEL1  &= ~R_REVERSE;	// R_REVERSE selected			(0)
P3OUT   &= ~R_REVERSE;	// R_REVERSE Port Pin set low		(0)
P3DIR   |= R_REVERSE;	// R_REVERSE set to Output		(1)

P3SEL0  &= ~L_FORWARD;	// L_FORWARD selected 			(0)
P3SEL1  &= ~L_FORWARD;	// L_FORWARD selected			(0)
P3OUT   &= ~L_FORWARD;	// L_FORWARD Port Pin set low		(0)
P3DIR   |= L_FORWARD;	// L_FORWARD set to Output		(1)

P3SEL0  &= ~L_REVERSE;	// L_REVERSE selected 			(0)
P3SEL1  &= ~L_REVERSE;	// L_REVERSE selected			(0)
P3OUT   &= ~L_REVERSE;	// L_REVERSE Port Pin set low		(0)
P3DIR   |= L_REVERSE;	// L_REVERSE set to Output		(1)
//------------------------------------------------------------------------------
}

void Init_Port4(void){
//==============================================================================
// Configure Port 4
// 
// Description: This functions initializes all pins for port 4
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
// SW1			(0x01) //
// SW2			(0x02) //
// EMPTY_REGISTER	(0x00) //
// SET_INPUT		(0x00) // value to set port as input
//------------------------------------------------------------------------------
P4SEL0 = EMPTY_REGISTER;// P1 set as I/0
P4SEL1 = EMPTY_REGISTER;// P1 set as I/0
P4DIR =  SET_INPUT;     // Set P1 direction to input

P4SEL0  &= ~SW1;	// SW1 selected 			(0)
P4SEL1  &= ~SW1;	// SW1 selected			        (0)
P4DIR   &= ~SW1;	// SW1 set to Input		        (0)
P4REN	|= SW1; 	// SW1 enable resistor	                (1)
P4OUT	|= SW1;		// SW1 set to PULLUP resistor	        (1) 

P4SEL0  &= ~SW2;	// SW2 selected 			(0)
P4SEL1  &= ~SW2;	// SW2 selected			        (0)
P4DIR   &= ~SW2;	// SW2 set to Input		        (0)
P4REN   |= SW2; 	// SW2 enable resistor	                (1)
P4OUT	|= SW2;		// SW2 set to PULLUP resistor	        (1)
//------------------------------------------------------------------------------
}

void Init_PortJ(char clock_iot){
//==============================================================================
// Configure Port J
// 
// Description: This functions initializes all pins for port J
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
// USE_IOT_WAKEUP                         (0x00)
// USE_SMCLK                               (0x01)
// IOT_WAKEUP		(0x01) // This was LED 1
// SMCLK                (0x01)
// IOT_FACTORY		(0x02) // This was LED 2
// IOT_STA_MINIAP	(0x04) // This was LED 3
// IOT_RESET		(0x08) // This was LED 4
// XINR			(0x10) // XINR
// XOUTR		(0x20) // XOUTR
// EMPTY_REGISTER	(0x00) //
// SET_INPUT		(0x00) // value to set port as input
//------------------------------------------------------------------------------
PJSEL0 = EMPTY_REGISTER;		// PJ set as I/0
PJSEL1 = EMPTY_REGISTER;		// PJ set as I/0
PJDIR = SET_INPUT;			// Set PJ direction to output

switch(clock_iot){
  case USE_SMCLK:
    PJSEL0 |= SMCLK; 			
    PJSEL1 &= ~SMCLK;  
    PJDIR |= SMCLK;                    // Set PJ Pin 1 direction to output
    break;
  case USE_IOT_WAKEUP:
    PJSEL0 &= ~IOT_WAKEUP; 			
    PJSEL1 &= ~IOT_WAKEUP; 
    PJOUT &= ~IOT_WAKEUP; 
    PJDIR |= IOT_WAKEUP;                    // Set PJ Pin 1 direction to output
    break;
}

PJSEL0 &= ~IOT_FACTORY; 		
PJSEL1 &= ~IOT_FACTORY; 
PJOUT &= ~IOT_FACTORY; 
PJDIR |= IOT_FACTORY;                   // Set PJ Pin 2 direction to output
 
PJSEL0 &= ~IOT_STA_MINIAP; 	        
PJSEL1 &= ~IOT_STA_MINIAP; 
PJOUT &= ~IOT_STA_MINIAP; 
PJDIR |= IOT_STA_MINIAP;                // Set PJ Pin 3 direction to output
//------------------------------------------------------------------------------
//USED TO RESET
//PJSEL0 &= ~IOT_RESET;
//PJSEL1 &= ~IOT_RESET;
//PJDIR |= IOT_RESET;                   // Set P3 Pin 4 direction to output
//PJOUT &= ~IOT_RESET;	
// XT1 Setup
// PJSEL0 |= XINR;
// PJSEL0 |= XOUTR;
//------------------------------------------------------------------------------
}

