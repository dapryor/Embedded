//#include <stdlib.h>
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
extern volatile char commandBuffer[30];
extern volatile unsigned int commandIndex;
extern unsigned int writeCommandFG;
extern unsigned int i,j, k; //counter variable
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
char numberBuff[5];
unsigned int time=0;
extern volatile unsigned int right_forward_rate;
extern volatile unsigned int right_reverse_rate;
extern volatile unsigned int left_forward_rate;
extern volatile unsigned int left_reverse_rate;
extern unsigned int thresholdR;
extern unsigned int thresholdL;
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ADC_Right_Detector;
extern unsigned int start_on_whiteFG;
unsigned int startBlackLine = FALSE;
extern unsigned int startTrackFG;
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
        for(k=0;k<5;k++){
            numberBuff[k] = '\0'; //clearing number buffer
        }
        if(!(commandBuffer[i+0]=='4' && commandBuffer[i+1]=='3' && commandBuffer[i+2]=='2' && commandBuffer[i+3]=='1')){ //if command contains securuty pin, then enter command tree
            StartCommandFG=FALSE;
            break;
        }
        if(commandBuffer[i+4]=='A'){ //checking for .A
            if(commandBuffer[i+5]=='\r' || commandBuffer[i+5]=='.' || commandBuffer[i+5]=='\n'){ //check for end of a command line
                uart_puts("I'm Here\r");
                StartCommandFG=FALSE;
            }
        }
        else if(commandBuffer[i+4]=='B'){ //Check for baud rate command or reverse command
          k=0;
          j=i+5;
          for(;commandBuffer[j]!='\r' &&  commandBuffer[j]!='\n' && commandBuffer[j]!='.';j++){
            if(commandBuffer[j] == '0' || commandBuffer[j] == '1'|| commandBuffer[j] == '2'|| commandBuffer[j] == '3'|| commandBuffer[j] == '4'|| commandBuffer[j] == '5'|| commandBuffer[j] == '6'|| commandBuffer[j] == '7'|| commandBuffer[j] == '8'|| commandBuffer[j] == '9'){
              numberBuff[k] = commandBuffer[j]; // grabbing numbers from command
              k++;
            }
          }
          if(commandBuffer[i+5]=='F'){ //checking for .BF
              if(commandBuffer[i+6]=='\r' || commandBuffer[i+6]=='.' || commandBuffer[i+6]=='\n'){ //check for end of a command line
                Init_Serial_UCA1(0); //set IOT baud to 115200
                display_1 = "  115200  ";
                uart_puts("115,200\n");
                StartCommandFG=FALSE;
            }
          }
          else if(commandBuffer[i+5]=='S'){ //checking for .BS
            if(commandBuffer[i+6]=='\r' || commandBuffer[i+6]=='.' || commandBuffer[i+6]=='\n'){ //check for end of a command line
                display_1 = "   9600   ";
                Init_Serial_UCA1(1); //set IOT baud to 9600
                uart_puts("9600\n");
                StartCommandFG=FALSE;
            }
          }  
          else if(numberBuff[0] != '\0'){ //checking for .B(number)
              display_1 = "  Reverse ";
              time = atoi(numberBuff);
              time /= 5;
              left_reverse_rate = 7000;
              right_reverse_rate = 7000;
              left_wheel_reverse_on();
              right_wheel_reverse_on();
              Five_msec_Delay(time);
              left_wheel_reverse_off();
              right_wheel_reverse_off();
              Five_msec_Delay(1);
            }
        }   
        else if(commandBuffer[i+4]=='F'){ //Wheel forward command check
          k=0;
          j=i+5;
          for(;commandBuffer[j]!='\r' &&  commandBuffer[j]!='\n' && commandBuffer[j]!='.';j++){
            if(commandBuffer[j] == '0' || commandBuffer[j] == '1'|| commandBuffer[j] == '2'|| commandBuffer[j] == '3'|| commandBuffer[j] == '4'|| commandBuffer[j] == '5'|| commandBuffer[j] == '6'|| commandBuffer[j] == '7'|| commandBuffer[j] == '8'|| commandBuffer[j] == '9'){
              numberBuff[k] = commandBuffer[j]; // grabbing numbers from command
              k++;
            }
          }
          if(numberBuff[0] != '\0'){ //checking for .F(number)
            display_1 = "  Forward ";  
            time = atoi(numberBuff);
              startTrackFG = TRUE;
              time /= 5;
              left_forward_rate = 7000;
              right_forward_rate = 7000;
              left_wheel_forward_on();
              right_wheel_forward_on();
              Five_msec_Delay(time);
              left_wheel_forward_off();
              right_wheel_forward_off();
              Five_msec_Delay(1);
            }
        }   
        else if(commandBuffer[i+4]=='R'){ // HARDWARE RESET or turn right command
            k=0;
            j=i+5;
            for(;commandBuffer[j]!='\r' &&  commandBuffer[j]!='\n' && commandBuffer[j]!='.';j++){
                if(commandBuffer[j] == '0' || commandBuffer[j] == '1'|| commandBuffer[j] == '2'|| commandBuffer[j] == '3'|| commandBuffer[j] == '4'|| commandBuffer[j] == '5'|| commandBuffer[j] == '6'|| commandBuffer[j] == '7'|| commandBuffer[j] == '8'|| commandBuffer[j] == '9'){
                    numberBuff[k] = commandBuffer[j]; // grabbing numbers from command
                    k++;
                }
            }
            if(commandBuffer[i+5]=='\r' || commandBuffer[i+5]=='.' || commandBuffer[i+5]=='\n'){ //check for end of a command line
                display_1 = "  Reset   ";
                IOTHardwareReset(); //resetting iot using pin
                uart_puts("Hardware Reset");
                StartCommandFG=FALSE;
            }
            else if(numberBuff[0] != '\0'){
              display_1 = "  Right   ";
              time = atoi(numberBuff); //string to number
              time *= 0.638888; //multiplying to enable degrees to be entered 
              left_forward_rate = 7000;
              left_wheel_forward_on();
              Five_msec_Delay(time);
              left_wheel_forward_off();
              Five_msec_Delay(1);
            }
        }
        else if(commandBuffer[i+4]=='L'){ // (HARDWARE RESET) or turn left command
            k=0;
            j=i+5;
            for(;commandBuffer[j]!='\r' &&  commandBuffer[j]!='\n' && commandBuffer[j]!='.';j++){
                if(commandBuffer[j] == '0' || commandBuffer[j] == '1'|| commandBuffer[j] == '2'|| commandBuffer[j] == '3'|| commandBuffer[j] == '4'|| commandBuffer[j] == '5'|| commandBuffer[j] == '6'|| commandBuffer[j] == '7'|| commandBuffer[j] == '8'|| commandBuffer[j] == '9'){
                    numberBuff[k] = commandBuffer[j]; // grabbing numbers from command
                    k++;
                }
            }
            if(numberBuff[0] != '\0'){
              display_1 = "   Left   ";
              time = atoi(numberBuff); //string to number
              time *= 0.638888; 
              right_forward_rate = 7000;
              right_wheel_forward_on();
              Five_msec_Delay(time);
              right_wheel_forward_off();
              Five_msec_Delay(1);
            }
        }   
        else if(commandBuffer[i+4]=='C'){ //Configure IOT
            if(commandBuffer[i+5]=='\r' || commandBuffer[i+5]=='.' || commandBuffer[i+5]=='\n'){ //check for end of a command line
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
        
        
        else if(commandBuffer[i+4]=='G'){ //blackline dection GO
            if(commandBuffer[i+5]=='\r' || commandBuffer[i+5]=='.' || commandBuffer[i+5]=='\n'){ //check for end of a command line
                display_1 = " Blk Line ";
                IR_LED_ON(); //IR on
                Five_msec_Delay(FOR_TENTH_SECOND); //let IR "warm up"
                startBlackLine = TRUE; // set flag for detection true
                if((ADC_Left_Detector) < thresholdL && ADC_Right_Detector < thresholdR){ //does my car start on white or black
                  start_on_whiteFG = TRUE;
                }
                
                StartCommandFG=FALSE;
            }
        }
        
        

        for(;commandBuffer[i]!='\r' &&  commandBuffer[i]!='\n' && commandBuffer[i]!='.';i++){
            //this for loop is for incrementing i to the next period
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