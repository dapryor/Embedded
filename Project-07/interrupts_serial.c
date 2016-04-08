#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

//GLOBALS---------------------------------------------------------------------//
volatile unsigned int usb_rx_ring_wr0;
volatile unsigned int usb_rx_ring_rd0;
volatile unsigned int usb_tx_ring_wr0;
volatile unsigned int usb_tx_ring_rd0;
volatile unsigned int usb_rx_ring_wr1;
volatile unsigned int usb_rx_ring_rd1;
volatile unsigned int usb_tx_ring_wr1;
volatile unsigned int usb_tx_ring_rd1;
volatile char USB_Char_Rx0[SMALL_RING_SIZE];
volatile char USB_Char_Tx0[LARGE_RING_SIZE];
volatile char USB_Char_Rx1[SMALL_RING_SIZE];
volatile char USB_Char_Tx1[LARGE_RING_SIZE];
extern char *display_1;
extern char adc_char[5];
volatile unsigned int portReady = 0;

//----------------------------------------------------------------------------//

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
    unsigned int temp;
    switch(__even_in_range(UCA0IV,0x08)){
        case 0: // Vector 0 - no interrupt
            break;
        case 2: // Vector 2 - RXIFG
            temp = usb_rx_ring_wr0;
            USB_Char_Rx0[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
            if (++usb_rx_ring_wr0 >= (SMALL_RING_SIZE)){
                usb_rx_ring_wr0 = BEGINNING; // Circular buffer back to beginning
            }
           
            if(!portReady){
              portReady = TRUE;
            }
            
            break;
        case 4: // Vector 4 – TXIFG
            break;
        default: break;
    }
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){ //IOT
    unsigned int temp;
    switch(__even_in_range(UCA1IV,0x08)){
        case 0: // Vector 0 - no interrupt
            break;
        case 2: // Vector 2 - RXIFG
            temp = usb_rx_ring_wr1;
            USB_Char_Rx1[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character
            if (++usb_rx_ring_wr1 >= (SMALL_RING_SIZE)){
                usb_rx_ring_wr1 = BEGINNING; // Circular buffer back to beginning
            }
            
            
            break;
        case 4: // Vector 4 – TXIFG
            //temp = usb_tx_ring_wr1;
            //UCA1TXBUF= USB_Char_Tx1[temp]; // TX -> USB_Char_Tx character
            //if (++usb_tx_ring_wr1 >= (LARGE_RING_SIZE)){
           //     usb_tx_ring_wr1 = BEGINNING; // Circular buffer back to beginning
           // }
            break;
        default: break;
    }
}