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
//volatile unsigned int Time_Sequence;
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
volatile unsigned int display_count = 0; //used to write display every 250ms
char adc_char[5];
volatile unsigned int ADC_Left_Detector;
volatile unsigned int ADC_Right_Detector;
volatile unsigned int ADC_Thumb;
unsigned int left_calibration_black;
unsigned int right_calibration_black;
unsigned int left_calibration_white;
unsigned int right_calibration_white;
//unsigned int left_calibration_ambient;
//unsigned int right_calibration_ambient;
extern volatile unsigned int switch_one_pressed;
extern volatile unsigned int switch_two_pressed;
unsigned int menu_items = FALSE;
unsigned int thresholdR;
unsigned int thresholdL;
extern volatile char USB_Char_Rx0[SMALL_RING_SIZE];
extern volatile char USB_Char_Rx1[SMALL_RING_SIZE];
extern unsigned int BaudMenuFG;
extern unsigned int IOTMenuFG;
extern unsigned int MainFG;

volatile char commandBuffer[30];
volatile unsigned int commandIndex=0;
unsigned int writeCommandFG=FALSE;
unsigned int i, j, k; //counter variable
volatile unsigned int transmitFG=TRUE;
volatile unsigned int StartCommandFG=FALSE;
unsigned int macFG=FALSE;
volatile char IOTBufferReceive[100];
volatile unsigned int IOTIndexTransmit = FALSE;
volatile unsigned int IOTIndexReceive = FALSE;
volatile unsigned int newLineFG=FALSE;
char SSIDBuff[11];
char firstipBuff[11] = "";
char secondipBuff[11] = "";
char *macPtr;
char *ipPtr;
char *SSIDPtr;
unsigned int countP = FALSE;
volatile char receiving[100];
volatile unsigned int receivingInd=0;
//project 8
unsigned int start_on_whiteFG = FALSE;
extern volatile unsigned int right_forward_rate;
extern volatile unsigned int right_reverse_rate;
extern volatile unsigned int left_forward_rate;
extern volatile unsigned int left_reverse_rate;
extern unsigned int startBlackLine;
unsigned int black_line_stop=RESET;
unsigned int display_IPFG;
volatile unsigned int reconnectTimer = RESET;
volatile unsigned int pingTimer = RESET;
volatile unsigned int trackTimer = RESET;
unsigned int startTrackFG = FALSE;


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
  Init_Timers();                            // Initialize Timers
  Init_LEDs();                              // Initialize LEDs
  Init_LCD();                               // Initialize LCD
  Init_ADC();                               // Initialize ADC
  Init_Serial_UCA1(0);                      // BAUD rate 115200
  Init_Serial_UCA0(1);                      // BAUD rate 9600
  Five_msec_Delay(1);
  PJOUT |= IOT_STA_MINIAP; //turning on miniap (only works this way)
  IR_LED_OFF();
  lcd_BIG_mid();
  display_1 = "  Waiting  ";
  display_2 = "    for";  
  display_3 = "  Command  ";
  display_4 = "";
  Display_Process();




//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                            // Can the Operating system run
    
    ADC_Process();              // call sampling function
    if(MainFG){
      Menu_Process();
    }
    else if(BaudMenuFG){
      Baud_Menu(); 
    }
    else if(IOTMenuFG){
      IOT_Menu();
    }
    else if(display_IPFG){
      display_1 = "";
      HEXtoBCD(trackTimer*FIVE_MSEC);
      display_2 = adc_char;;
      ipPtr=firstipBuff;
      display_3=ipPtr;
      ipPtr=secondipBuff;
      display_4=ipPtr;
      if(pingTimer > FOR_FIVE_SECONDS){
        pingTimer = RESET;
        uart_puts("AT+S.PING=10.139.64.1\r"); //ping gateway
      }
      if(reconnectTimer >= FOR_THIRTY_SECONDS){ //reset IOT
        reconnectTimer = RESET;
        uart_puts("AT+CFUN=1\r"); 
        IOTHardwareReset();
      }
    }
    
    
    if(startBlackLine){
      blackline(); //run black line detection code  
    }
    
    if(black_line_stop >= 2){ //did i get the command to stop blackline detection?
        startTrackFG = FALSE;
        black_line_stop = 0;
        startBlackLine = FALSE;
        IR_LED_OFF();
        left_wheel_reverse_off();
        right_wheel_forward_off();
        right_wheel_reverse_off();
        left_wheel_forward_off();
    }
    
    if(StartCommandFG){ //StartCommandFG is true once "." has been received
        commandTree();
    }

    clearReceiveBuffer();
    parseIOTData();
  }
//------------------------------------------------------------------------------
}


void clearReceiveBuffer(void){
    if(newLineFG==TRUE){
        newLineFG=FALSE;
        receivingInd=0; //reset index
        for(i=0;i<100;i++){ //clear buffer
            receiving[i]='\0';
        }
    }
}


void parseIOTData(void){
    for(i=0;i<=100-3;i++){ //search through received strings
        if(receiving[i]=='D'){
            if(receiving[i+1]==':'){
                if(receiving[i+2]=='2'){
                    Five_msec_Delay(1);
                    if(receiving[i+3]=='1'){
                        display_4="Scanning";
                        Display_Process();
                    }
                    else if(receiving[i+3]=='4'){
                        countP=0; //initialize period counter
                        Five_msec_Delay(3); //short delay to allow all characters to enter
                        j=0;
                        for(i=17;receiving[i] != '\r';i++){ //go from beginning of address until 2nd period hit (2nd group)
                            if(receiving[i] == '.'){
                                countP++;
                            }
                            if(countP >=2){ //stop copying to buffer if 2nd period has been hit (2nd "group" is copied)
                                break;
                            }
                            firstipBuff[j]=receiving[i];
                            j++;
                        }
                        posL3=(10-j)/2; //center first half of ip address
                        i++; //skip the period
                        for(j=0;receiving[i] != '\r';i++){
                            secondipBuff[j]=receiving[i];
                            j++;
                        }
                        posL4=(10-j)/2; //center second half of ip address
                        ipPtr=firstipBuff;
                        display_3=ipPtr;
                        ipPtr=secondipBuff;
                        display_4=ipPtr;
                        lcd_4line();
                        Display_Process();
                        Five_msec_Delay(600); //display IP for 3 seconds before screen gets cleared by menus
                        
                        display_IPFG = TRUE;
                        MainFG = FALSE;
                        BaudMenuFG = FALSE;
                        IOTMenuFG = FALSE;
                        
                    }
                    else if(receiving[i+3]=='5'){
                        Five_msec_Delay(5);//short delay to allow all characters to enter
                        for(i=32;receiving[i] != '\'' && i<=42 ;i++){ //copy SSID until end of quoted name or until max size for LCD is hit
                            SSIDBuff[i-32]=receiving[i];
                        }
                        SSIDPtr=SSIDBuff;
                        posL1=0;
                        //SSID is displayed in D:24
                    }
                    
                }
                else if(receiving[i+2]=='3'){ //clear display once scanning is complete
                    if(receiving[i+3]=='5'){
                        display_4="          "; 
                        Display_Process();
                    }
                }
                else if(receiving[i+2]=='4'){ //detect disassociation --> reassociate by resetting module
                    if(receiving[i+3]=='1'){
                        uart_puts("AT+CFUN=1\r"); //Get SSID to ncsu
                        PJOUT &= ~IOT_RESET; //reset IOT
                        Five_msec_Delay(10); //wait 50 ms
                        PJOUT |= IOT_RESET; //turn IOT back on (stop reset)
                    }
                }
            }
        }
    }
}

int atoi(char *string){
  int l, converted;
  converted = RESET;
  for(l=RESET; string[l] != '\0'; ++l){
    converted = converted*10 + string[l] - '0';
  }
  return converted;
}








