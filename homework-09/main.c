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
volatile int passed_value = FALSE;
volatile int pass_flag=FALSE;


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
  display_1 = " David  P";
  display_2 = "  ECE306";  
  display_3 = "   HW08";
  display_4 = "9600  Baud";
  Display_Process();
  Five_msec_Delay(FOR_FIVE_SECONDS);
  display_1 = "";
  display_2 = "";
  display_3 = "";
  display_4 = "";
  Display_Process();


//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                            // Can the Operating system run
    Menu_Process();
    ADC_Process();              // call sampling function
    if(display_count >= FOR_FOURTH_SECOND){    // update screen every 250 msec
      Display_Process();
      display_count = SWITCH_OFF;
    }
    if(menu_items == FALSE){  //start menu
      display_4 = "SW2: Menu";
    }
    if(switch_two_pressed){ //enter selection menu
      menu_items = TRUE;
      switch_two_pressed = SWITCH_OFF;
    }
    if(pass_flag==TRUE){
      Five_msec_Delay(200);
      USB_Char_Tx0[0] = passed_value;
      UCA0TXBUF = USB_Char_Tx0[0];
      pass_flag=FALSE;
    }
    
  }
//------------------------------------------------------------------------------
}


void Menu_Process(void){
  int i;
  //---------------------UNUSED-----------------------------------------
  if(menu_items && ADC_Thumb <= SECTION_SIX_START){
    display_1 = "Option 4";
    display_2 = "";  
    display_3 = "";
    display_4 = "SW1 Select";
    if(switch_one_pressed){
      switch_one_pressed = FALSE;
    } 
  }
  //---------------------UNUSED-----------------------------------------
  else if(menu_items && ADC_Thumb <= SECTION_FIVE_START && ADC_Thumb > SECTION_SIX_START){
    display_1 = "Count";
    display_2 = "";  
    display_3 = "";
    display_4 = "SW1 Select";
    if(switch_one_pressed){
      UCA0TXBUF = 0;
      menu_items = FALSE;
      switch_one_pressed = FALSE;
    }    
  }
  //---------------------UNUSED-------------------------------------------------
  else if(menu_items && ADC_Thumb <= SECTION_FOUR_START && ADC_Thumb > SECTION_FIVE_START){
    HEXtoBCD(right_calibration_black);
    display_1 = "Black";
    display_2 = adc_char;  
    display_3 = "";
    display_4 = "";
  }
  //---------------------9600 BAUD RATE-----------------------------------------
  else if(menu_items && ADC_Thumb <= SECTION_THREE_START && ADC_Thumb > SECTION_FOUR_START){
    display_1 = "";
    display_2 = "9600";  
    display_3 = "";
    display_4 = "";
    if(switch_one_pressed){
      Init_Serial_UCA1(1);                      // BAUD rate 9600
      Init_Serial_UCA0(1);                      // BAUD rate 9600
      
      display_1 = "";
      display_2 = "";
      display_3 = "   9600";
      display_4 = "   Baud";
      Display_Process();
      Five_msec_Delay(FOR_TWO_SECOND);

      
      for(i=0; i<=9; i++){
        UCA0TXBUF = transmission[i];
        UCA1TXBUF = transmission[i];
        Five_msec_Delay(1);
        received0[i] = UCA0RXBUF;
        received1[i] = UCA1RXBUF;
      }
      
      if(received1[0] == '\0'){
        received0[i] = '\0';
        display_1 = received0;
      }
      else{
        received1[i] = '\0';
        display_1 = received1;
      }
      
      
      Display_Process();
      
      Five_msec_Delay(FOR_TWO_SECOND);
      
      switch_one_pressed = FALSE;
    }  
  }
  //---------------------115200 BAUD RATE-----------------------------------------
  else if(menu_items && ADC_Thumb <= SECTION_TWO_START && ADC_Thumb > SECTION_THREE_START){
    display_1 = "";
    display_2 = "115200";  
    display_3 = "";
    display_4 = "";
    if(switch_one_pressed){
      Init_Serial_UCA1(0);                      // BAUD rate 125200
      Init_Serial_UCA0(0);                      // BAUD rate 125200
      
      display_1 = "";
      display_2 = "";
      display_3 = "  115200";
      display_4 = "   Baud";
      Display_Process();
      Five_msec_Delay(FOR_TWO_SECOND);
      

      for(i=0; i<=9; i++){
        UCA0TXBUF = transmission[i];
        UCA1TXBUF = transmission[i];
        Five_msec_Delay(1);
        received0[i] = UCA0RXBUF;
        received1[i] = UCA1RXBUF;
      }
      
      if(received1[0] == '\0'){
        received0[i] = '\0';
        display_1 = received0;
      }
      else{
        received1[i] = '\0';
        display_1 = received1;
      }
      
      Display_Process();
      
      Five_msec_Delay(FOR_TWO_SECOND);
      
      switch_one_pressed = FALSE;
    }  
  }
  //---------------------BAUD RATE TEST-----------------------------------------
  else if(menu_items  && ADC_Thumb > SECTION_TWO_START){
    display_1 = "Test  Baud";
    display_2 = "";  
    display_3 = "";
    display_4 = "SW1 Select";
    if(switch_one_pressed){
      switch_one_pressed = FALSE;
      while(1){
        UCA0TXBUF = 'N';
        UCA1TXBUF = 'N';
        if(switch_one_pressed){
          break;
        }
      }
    switch_one_pressed = FALSE;
    }  
  }
}











