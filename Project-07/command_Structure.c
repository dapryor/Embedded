#include "macros.h"
#include "functions.h"
#include "msp430.h"

//GLOBAL VARIABLES------------------------------------------------------------//
//multi-function globals//
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern volatile unsigned int pressed1;
extern volatile unsigned int pressed2;

//commandTree() globals//
extern volatile unsigned int PCReady;
extern char baudCommand[]; //need to seperately add carriage return
extern char carriageReturn;
extern char saveSettingsCommand[];
extern char resetCommand[];
extern char getmacCommand[];
extern volatile char commandBuffer[30];
extern volatile unsigned int commandIndex;
extern unsigned int writeCommandFG;
extern unsigned int i,j; //counter variable
extern volatile unsigned int transmitReady;
extern volatile unsigned int StartCommandFG;
extern unsigned int macFG;
extern volatile unsigned int IOTIndexReceive; //testing

//calibrate_detector() globals//
extern unsigned int Ambient_right; //Variables for detector calibration
extern unsigned int Ambient_left;
extern unsigned int White_right;
extern unsigned int White_left;
extern unsigned int Black_right;
extern unsigned int Black_left;
extern unsigned int threshhold;
extern volatile unsigned int Left_Detector;
extern volatile unsigned int Right_Detector;
//----------------------------------------------------------------------------//


void commandTree(void){
    commandIndex=0;
    for(i=0;i<30;i++){ //clear command buffer
        commandBuffer[i]='\0';
    }
    i=0;
    writeCommandFG=TRUE; //write to command buffer (in interrupt)
    Five_msec_Delay(10); //short delay to allow for commandBuffer to fill   
    while(commandBuffer[i] != '\r' && commandBuffer[i] != '\n'){ //search through command buffer, and end if carriage return or new line is hit
        if(!(commandBuffer[i+0]=='1' && commandBuffer[i+1]=='2' && commandBuffer[i+2]=='3' && commandBuffer[i+3]=='4')){ //if command contains securuty pin, then enter command tree
            StartCommandFG=FALSE;
            break;
        }
        if(commandBuffer[i+4]=='A'){ //FIRST COMMAND
            if(commandBuffer[i+5]=='\r' || commandBuffer[i+5]=='.' || commandBuffer[i+5]=='\n'){ //make sure it is the end of a command line
                uart_puts("I'm Here\r");
                StartCommandFG=FALSE;
            }
        }
        else if(commandBuffer[i+4]=='F'){ //SECOND COMMAND
            if(commandBuffer[i+5]=='\r' || commandBuffer[i+5]=='.' || commandBuffer[i+5]=='\n'){ //make sure it is the end of a command line
                Init_Serial_UCA1(0); //set IOT baud to 115200
                uart_puts("115,200\n");
                StartCommandFG=FALSE;
            }
        }
        else if(commandBuffer[i+4]=='S'){ //THIRD COMMAND
            if(commandBuffer[i+5]=='\r' || commandBuffer[i+5]=='.' || commandBuffer[i+5]=='\n'){ //make sure it is the end of a command line
                Init_Serial_UCA1(1); //set IOT baud to 9600
                uart_puts("9600\n");
                StartCommandFG=FALSE;
            }
        }
           
        else if(commandBuffer[i+4]=='R'){ //FOURTH COMMAND (HARDWARE RESET)
            if(commandBuffer[i+5]=='\r' || commandBuffer[i+5]=='.' || commandBuffer[i+5]=='\n'){ //make sure it is the end of a command line
                PJOUT &= ~IOT_RESET; //reset IOT
                Five_msec_Delay(10); //wait 50 ms
                PJOUT |= IOT_RESET; //turn IOT back on (stop reset)
                uart_puts("Hardware Reset");
                StartCommandFG=FALSE;
            }
        }
           
        else if(commandBuffer[i+4]=='C'){ //FIFTH COMMAND (Configure)
            if(commandBuffer[i+5]=='\r' || commandBuffer[i+5]=='.' || commandBuffer[i+5]=='\n'){ //make sure it is the end of a command line(termite is set to end each line w/ carriage return)
                Init_Serial_UCA1(0); //Set A1 to 115200. TEMPORARILY SET TO 9600 SO IOT RESPONSE CAN BE SEEN ON TERMINAL
                uart_puts("AT+S.SCFG=console1_speed,9600\r"); //set IOT baud rate to 9600
                Five_msec_Delay(400); //delay 2 seconds to allow change to take effect
                uart_puts("AT&W\r"); //save settings to FRAM
                Five_msec_Delay(200); //delay 1 second to allow change to take effect
                Init_Serial_UCA1(1); //Set A1 to 9600 baud
                uart_puts("AT+CFUN=1\r"); //Send software reset command
                IOTHardwareReset(); //resetting iot using pin

                StartCommandFG=FALSE;
            }
        }
        
        else if(commandBuffer[i+4]=='M'){ //SIXTH COMMAND (Get MAC Address)
            if(commandBuffer[i+5]=='\r' || commandBuffer[i+5]=='.' || commandBuffer[i+5]=='\n'){ //make sure it is the end of a command line(termite is set to end each line w/ carriage return)
                uart_puts("AT+S.GCFG=nv_wifi_macaddr\r");//get MAC address
                //print address to display (code to do this is in main)
                macFG=TRUE;

                StartCommandFG=FALSE;
            }
        }
        

        for(;commandBuffer[i]!='\r' &&  commandBuffer[i]!='\n' && commandBuffer[i]!='.';i++){
            //this for loop is for incrementing i to the next period, or incrementing i to the point where
            //it breaks out of the while loop
        }
        if(commandBuffer[i]=='.'){ //if not breaking out of while loop, increment i to skip the period part of the next command
            i++;
        }
    }
    StartCommandFG=FALSE;
    writeCommandFG=FALSE; //command has been executed.
}

void uart_puts(const char *str){
    if (str != '\0') {
        while (*str != '\0') {
            /* give time for the transmit buffer to be ready */
            Five_msec_Delay(1);
            /* Transmit data */
            UCA1TXBUF = *str; //send to IOT
            UCA0TXBUF = *str; //echo to PC
            str++;
        }
    }
}