//------------------------------------------------------------------------------
//  File Name : main.c
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  David Pryor
//  Jan 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

// Required defines
// In the event the universe no longer exists, this bit will reset
// ALWAYS                                       (1)
// CNTL_STATE_INDEX                             (3) // Control States
// SW1                  	                (0x01) // Switch 1
// SW2                  	                (0x02) // Switch 2
// START				        (0x00)
// MAX_SIZE_COUNT			        (0x05) 
// LINE_POS_1                                   (0x01) // starting postion on lcd
// LINE_POS_2                                   (0x02) // starting postion on lcd
// LINE_POS_3                                   (0x03) // starting postion on lcd
// LCD--------------------------------------------------------------------------
// LCD_HOME_L1	                                (0x80)
// LCD_HOME_L2         	                        (0xA0)
// LCD_HOME_L3         	                        (0xC0)
// LCD_HOME_L4         	                        (0xE0)
// LINE_SIZE				        (0x0B)
// CASE NUMBERS (THESE ARE TEMPORARY FILLERS!)----------------------------------
// COUNT_TWOFIDDY_MSEC			        (0x32) //50
// COUNT_FIVEHUNNED_MSEC			(0x64) //100
// COUNT_SEVENFIDDY_MSEC			(0x96) //150
// COUNT_ONETHOUSAND_MSEC			(0xC8) //200
// COUNT_TWELVEFIDDY_MSEC			(0xFA) //250
// SWITCHES---------------------------------------------------------------------
// SWITCH_OFF				        (0x00)
// SWITCH_ON			                (0x01)
//------------------------------------------------------------------------------



// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time;
volatile unsigned int five_msec_delay;
extern char display_line_1[LINE_SIZE];
extern char display_line_2[LINE_SIZE];
extern char display_line_3[LINE_SIZE];
extern char display_line_4[LINE_SIZE];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char posL1;
char posL2;
char posL3;
char posL4;
char size_count;
char big;
volatile unsigned int do_this = FALSE;
volatile unsigned int display_count = 0; //used to write display every 250ms
char adc_char[5];
volatile unsigned int ADC_Left_Detector;
volatile unsigned int ADC_Right_Detector;
volatile unsigned int ADC_Thumb;
unsigned int left_calibration_black;
unsigned int right_calibration_black;
unsigned int left_calibration_white;
unsigned int right_calibration_white;
unsigned int left_calibration_ambient;
unsigned int right_calibration_ambient;
extern volatile unsigned int switch_one_pressed;
extern volatile unsigned int switch_two_pressed;
unsigned int menu_items = FALSE;
unsigned int threshold;
extern volatile char USB_Char_Rx0[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx0[LARGE_RING_SIZE];
extern volatile char USB_Char_Rx1[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx1[LARGE_RING_SIZE];
char transmission[16] = " NCSU  #1 ";
char received0[16];
char received1[16];

extern volatile unsigned int PCReady;
char response1[]="I'm Here";
char response2[]="115,200";
char response3[]="9600";
char response4[]="Hardware Reset";
volatile char commandBuffer[16];
volatile unsigned int commandIndex=0;
unsigned int writeToCommand=FALSE;
unsigned int i; //counter variable
volatile unsigned int transmitReady=TRUE;
volatile unsigned int commandStart=FALSE;

volatile char IOTBufferTransmit[100];
volatile char IOTBufferReceive[100];
volatile unsigned int IOTIndexTransmit;
volatile unsigned int IOTIndexReceive;
volatile unsigned int commandCheckTimeout;


void main(void){
//==============================================================================
// Main Program
// 
// Description: This function contains the while loop that runs continuously
// to act for the operating system. It also calls all the functions to
// initialize the system.
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
//              slow_input_down
//              control_state[CNTL_STATE_INDEX]
//              char big
//              char size_count;
//              char posL1
//              char posL2
//              char posL3
//              char posL4
//
// Author: David Pryor
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System 
  Init_Conditions();
  Time_Sequence = SWITCH_OFF;               // 
  Init_Timers();                            // Initialize Timers
  Init_LEDs();                              // Initialize LEDs
  Init_LCD();                               // Initialize LCD
  Init_ADC();                               // Initialize ADC
  Init_Serial_UCA1(1);                      // BAUD rate 9600
  Init_Serial_UCA0(1);                      // BAUD rate 9600
  Five_msec_Delay(1);
  PJOUT |= IOT_RESET; //IOT reset is active low, so this turns IOT reset off.
  
  lcd_BIG_mid();
  display_1 = "  David   ";
  display_2 = "Homework 9";  
  display_3 = "  Pryor   ";
  display_4 = "";
  Display_Process();



//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                            // Can the Operating system run
    
    ADC_Process();              // call sampling function
    
    
if(commandStart==TRUE){ //commandStart=TRUE once "." has been received
       
       commandIndex=0;
       writeToCommand=TRUE; //write to command buffer (in interrupt)
       commandCheckTimeout=0;
       for(i=0;i<16;i++){ //clear command buffer
           commandBuffer[i]='\0';
       }
       
       while(ALWAYS){ //search through command buffer
           if(commandBuffer[0]=='@'){ //FIRST COMMAND
               if(commandBuffer[1]==0x000D){ //make sure it is the end of a command line
                   i=0;
                   while(response1[i] != '\0'){
                       if(transmitReady==TRUE){
                           transmitReady=FALSE;
                           UCA0TXBUF=response1[i]; //send transmission message
                           i++;
                       }
                   }
                   Five_msec_Delay(5);
                   commandStart=FALSE; //command done
                   break;
               }
           }
           if(commandBuffer[0]=='F'){ //SECOND COMMAND
               if(commandBuffer[1]==0x000D){ //make sure it is the end of a command line
                   i=0;
                   Init_Serial_UCA1(0); //set IOT baud to 115200
                   while(response2[i] != '\0'){
                       if(transmitReady==TRUE){
                           transmitReady=FALSE;
                           UCA0TXBUF=response2[i]; //send transmission message
                           i++;
                       }
                   }
                   Five_msec_Delay(5);
                   commandStart=FALSE; //command done
                   break;
               }
           }
           if(commandBuffer[0]=='S'){ //THIRD COMMAND
               if(commandBuffer[1]==0x000D){ //make sure it is the end of a command line
                   i=0;
                   Init_Serial_UCA1(1); //set IOT baud to 9600
                   while(response3[i] != '\0'){
                       if(transmitReady==TRUE){
                           transmitReady=FALSE;
                           UCA0TXBUF=response3[i]; //send transmission message
                           i++;
                       }
                   }
                   Five_msec_Delay(5);
                   commandStart=FALSE;
                   break;
               }
           }
           
           if(commandBuffer[0]=='R'){ //THIRD COMMAND
               if(commandBuffer[1]==0x000D){ //make sure it is the end of a command line
                   i=0;
                   PJOUT &= ~IOT_RESET; //reset IOT
                   Five_msec_Delay(10); //wait 50 ms
                   PJOUT |= IOT_RESET; //turn IOT back on (stop reset)
                   while(response4[i] != '\0'){
                       if(transmitReady==TRUE){
                           transmitReady=FALSE;
                           UCA0TXBUF=response4[i]; //send transmission message
                           i++;
                       }
                   }
                   Five_msec_Delay(5);
                   commandStart=FALSE;
                   break;
               }
           }
           
           else if(commandCheckTimeout>=10){
               commandCheckTimeout=0;
               commandStart=FALSE;
               break;
           }
       }
       writeToCommand=FALSE; //command has been executed.
       commandStart=FALSE;
   }
   
   if(PCReady==TRUE){ 
       i=0;
       Five_msec_Delay(6);
       while(IOTBufferTransmit[i] != '\0'){
           if(transmitReady==TRUE){
               transmitReady=FALSE;
               UCA1TXBUF=IOTBufferTransmit[i];
               i++;
           }
       }
       for(i=0;i<100;i++){ //clear IOT buffer
           IOTBufferTransmit[i]='\0';
       }
       
       IOTIndexTransmit=0;
       i=0;
       Five_msec_Delay(5);
       
       while(IOTBufferReceive[i] != '\0'){
           if(transmitReady==TRUE){
               transmitReady=FALSE;
               UCA0TXBUF=IOTBufferReceive[i];
               i++;
           }
       }
       for(i=0;i<100;i++){ //clear IOT buffer
           IOTBufferReceive[i]='\0';
       }
       IOTIndexReceive=0;
       Five_msec_Delay(5);
       PCReady=FALSE;
   }
    /*if(menu_items){  //start menu
      switch_one_pressed = FALSE;
      switch_two_pressed = FALSE;
      Menu_Process();
    }*/
    
  }
//------------------------------------------------------------------------------
}














