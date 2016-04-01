#include  "macros.h"

void Init_Port1(void){
//------------------------------------------------------------------------------
//Configure Port 1
// V_DETECT_R (0x01) //
// V_DETECT_L (0x02) //
// IR_LED (0x04) //
// V_THUMB (0x08) //
// SPI_CS_LCD (0x10) // LCD Chip Select
// RESET_LCD (0x20) // LCD Reset
// SIMO_B (0x40) // SPI mode - slave in/master out of USCI_B0
// SOMI_B (0x80) // SPI mode - slave out/master in of USCI_B0
//------------------------------------------------------------------------------
 P1SEL0 = 0x00; // P1 set as I/0
 P1SEL1 = 0x00; // P1 set as I/0
 P1DIR = 0x00; // Set P1 direction to input
 P1SEL0 |= V_DETECT_R; // V_DETECT_R selected
 P1SEL1 |= V_DETECT_R; // V_DETECT_R selected
 P1SEL0 |= V_DETECT_L; // V_DETECT_L selected
 P1SEL1 |= V_DETECT_L; // V_DETECT_L selected
 P1SEL0 &= ~IR_LED; // IR_LED GPI/O selected
 P1SEL1 &= ~IR_LED; // IR_LED GPI/O selected
 P1OUT |= IR_LED; // P1 IR_LED Port Pin set low
 P1DIR |= IR_LED; // Set P1 IR_LED direction to output
 P1SEL0 |= V_THUMB; // V_THUMB selected
 P1SEL1 |= V_THUMB; // V_THUMB selected
 P1SEL0 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
 P1SEL1 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
 P1OUT |= SPI_CS_LCD; // P1 SPI_CS_LCD Port Pin set high
 P1DIR |= SPI_CS_LCD; // Set SPI_CS_LCD output direction
 P1SEL0 &= ~RESET_LCD; // RESET_LCD GPI/O selected
 P1SEL1 &= ~ RESET_LCD; // RESET_LCD GPI/O selected
 P1OUT &= ~ RESET_LCD; // RESET_LCD Port Pin set low
 P1DIR |= RESET_LCD; // Set RESET_LCD output direction
 P1SEL0 &= ~SIMO_B; // SIMO_B selected
 P1SEL1 |= SIMO_B; // SIMO_B selected
 P1DIR |= SIMO_B; // SIMO_B set to Output
 P1SEL0 &= ~SOMI_B; // SOMI_B is used on the LCD
 P1SEL1 |= SOMI_B; // SOMI_B is used on the LCD
 P1DIR &= ~SOMI_B; // SOMI_B set to Input
 P1REN |= SOMI_B; // Enable pullup resistor
//------------------------------------------------------------------------------
}


void Init_PortJ(void){
//------------------------------------------------------------------------------
// Port J Pins
// LED1 (0x01) // LED 5
// LED2 (0x02) // LED 6
// LED3 (0x04) // LED 7
// LED4 (0x08) // LED 8
// XINR (0x10) // XINR
// XOUTR (0x20) // XOUTR
//------------------------------------------------------------------------------
 PJSEL0 = 0x00; // PJ set as I/0
 PJSEL1 = 0x00; // PJ set as I/0
 PJDIR = 0x00; // Set PJ direction to output
 PJSEL0 &= ~LED1;
 PJSEL1 &= ~LED1;
 PJOUT &= ~LED1;
 PJDIR |= LED1; // Set PJ Pin 1 direction to output
 PJSEL0 &= ~LED2;
 PJSEL1 &= ~LED2;
 PJOUT &= ~LED2;
 PJDIR |= LED2; // Set PJ Pin 2 direction to output
 PJSEL0 &= ~LED3;
 PJSEL1 &= ~LED3;
 PJOUT &= ~LED3;
 PJDIR |= LED3; // Set PJ Pin 3 direction to output
 PJSEL0 &= ~LED4;
 PJSEL1 &= ~LED4;
 PJDIR |= LED4; // Set P3 Pin 4 direction to output
 PJOUT &= ~LED4;
// XT1 Setup
// PJSEL0 |= XINR;
// PJSEL0 |= XOUTR;
//------------------------------------------------------------------------------
}
