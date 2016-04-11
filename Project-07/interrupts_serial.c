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
extern unsigned int writeCommandFG;
extern volatile char commandBuffer[30];
extern volatile unsigned int commandIndex;
extern volatile unsigned int transmitFG;
extern volatile unsigned int StartCommandFG;
extern unsigned int i; //counter variable
extern volatile char IOTBufferReceive[];
extern volatile unsigned int IOTIndexTransmit;
extern volatile unsigned int IOTIndexReceive;
extern unsigned int macFG;
extern volatile unsigned int newLineFG;
extern volatile char receiving[100];
extern volatile unsigned int receivingInd;

//----------------------------------------------------------------------------//

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
    unsigned int temp,temp2;
    switch(__even_in_range(UCA0IV,0x08)){
        case 0: // Vector 0 - no interrupt
            break;
        case 2: // Vector 2 - RXIFG
            temp = usb_rx_ring_wr0;
            USB_Char_Rx0[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
            
            if(UCA0RXBUF=='.'){
                StartCommandFG=TRUE;
            }
            
            if (++usb_rx_ring_wr0 >= (SMALL_RING_SIZE)){
                usb_rx_ring_wr0 = BEGINNING; // Circular buffer back to beginning
            }
            if(writeCommandFG){
                temp2=commandIndex;
                commandBuffer[temp2]=USB_Char_Rx0[temp];//write newly recieved character to command buffer
                commandIndex++;
            }
            
            
            break;
        case 4: // Vector 4 – TXIFG
          transmitFG=TRUE;   
          break;
        default: break;
    }
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){ //IOT
    unsigned int temp,temp2, temp3;
    switch(__even_in_range(UCA1IV,0x08)){
        case 0: // Vector 0 - no interrupt
            break;
        case 2: // Vector 2 - RXIFG
            temp = usb_rx_ring_wr1;
            USB_Char_Rx1[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character
            if(UCA1RXBUF=='.'){
                StartCommandFG=TRUE;
            }
            if (++usb_rx_ring_wr1 >= (SMALL_RING_SIZE)){
                usb_rx_ring_wr1 = BEGINNING; // Circular buffer back to beginning
            }
            if(UCA1RXBUF== '\n'){ //reset receivingInd if new line hits
                newLineFG=TRUE;
            }
            if(writeCommandFG){
                temp2=commandIndex;
                commandBuffer[temp2]=USB_Char_Rx0[temp];//write newly recieved character to command buffer
                commandIndex++;
            }
            if(macFG){
                temp2=IOTIndexReceive; //takes info from IOT device, and writes it to PC
                IOTBufferReceive[temp2]=USB_Char_Rx1[temp];
                IOTIndexReceive++; 
            }

            //IOT TALKING?  
            temp3=receivingInd;
            receiving[temp3]=USB_Char_Rx1[temp];
            receivingInd++;
            break;
        case 4: // Vector 4 – TXIFG
            transmitFG=TRUE; 
            break;
        default: break;
    }
}