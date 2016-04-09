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
volatile unsigned int PCReady = 0;

extern volatile unsigned int PCReady;
extern volatile char commandBuffer[];
extern volatile unsigned int commandIndex;
extern unsigned int writeToCommand;
extern volatile unsigned int transmitReady;
extern volatile unsigned int commandStart;

extern volatile char IOTBufferTransmit[];
extern volatile char IOTBufferReceive[];
extern volatile unsigned int IOTIndexTransmit;
extern volatile unsigned int IOTIndexReceive;
//----------------------------------------------------------------------------//

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
    unsigned int temp,temp2,temp3,i;
    switch(__even_in_range(UCA0IV,0x08)){
        case 0: // Vector 0 - no interrupt
            break;
        case 2: // Vector 2 - RXIFG
            temp = usb_rx_ring_wr0;
            for(i=0;i<SMALL_RING_SIZE;i++){ //clear command buffer
              USB_Char_Rx0[i]='\0';
            }
            USB_Char_Rx0[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
            
            if(UCA0RXBUF=='@'){
                commandStart=TRUE;
            }
            
            if (++usb_rx_ring_wr0 >= (SMALL_RING_SIZE)){
                usb_rx_ring_wr0 = BEGINNING; // Circular buffer back to beginning
            }
            if(writeToCommand==TRUE){
                temp2=commandIndex;
                commandBuffer[temp2]=USB_Char_Rx0[temp];//write newly recieved character to command buffer
                commandIndex++;
            }
            if(commandStart==FALSE){
                temp3=IOTIndexTransmit;
                IOTBufferTransmit[temp3]=USB_Char_Rx0[temp];
                IOTIndexTransmit++;
            }
            if(!PCReady){
              PCReady = TRUE;
            }
            
            break;
        case 4: // Vector 4 – TXIFG
          transmitReady=TRUE;   
          break;
        default: break;
    }
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){ //IOT
    unsigned int temp,temp2;
    switch(__even_in_range(UCA1IV,0x08)){
        case 0: // Vector 0 - no interrupt
            break;
        case 2: // Vector 2 - RXIFG
            temp = usb_rx_ring_wr1;
            USB_Char_Rx1[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character
            if (++usb_rx_ring_wr1 >= (SMALL_RING_SIZE)){
                usb_rx_ring_wr1 = BEGINNING; // Circular buffer back to beginning
            }
            if(commandStart==FALSE){
                temp2=IOTIndexReceive;
                IOTBufferReceive[temp2]=USB_Char_Rx1[temp];
                IOTIndexReceive++;
            }
            if(!PCReady){
              PCReady = TRUE;
            }
            break;
        case 4: // Vector 4 – TXIFG
            transmitReady=TRUE; 
            break;
        default: break;
    }
}