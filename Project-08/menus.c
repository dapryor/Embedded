//------------------------------------------------------------------------------
//  File Name : menus.c
//
//  Description: This file contains the menus Routines 
//
//  David Pryor
//  April 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

extern unsigned int menu_items;
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern volatile unsigned int switch_one_pressed;
extern volatile unsigned int switch_two_pressed;
extern volatile unsigned int ADC_Thumb;
char lcdBuff[10] = "         ";
unsigned int BaudMenuFG = FALSE;
unsigned int IOTMenuFG = FALSE;
unsigned int MainFG = TRUE;

//testing black line
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int right_forward_rate;
extern volatile unsigned int right_reverse_rate;
extern volatile unsigned int left_forward_rate;
extern volatile unsigned int left_reverse_rate;
extern unsigned int thresholdR;
extern unsigned int thresholdL;
unsigned int start_on_whiteFG = FALSE;
unsigned int errorR=FALSE;
unsigned int errorL=FALSE;
extern volatile unsigned int motor_time;
unsigned int white_val;
unsigned int black_val;

void Menu_Process(void){
// Menu Process
// 
// Description: This function creates the main menu.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:    
//              char* display_1
//              char* display_2
//              char* display_3
//              char* display_4
//              unsigned int menu_items;
//              volatile unsigned int ADC_Thumb;
//              volatile unsigned int switch_one_pressed;
//              volatile unsigned int switch_two_pressed;
//
// Author: David Pryor
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  unsigned int motor_time_prev=RESET;
  
  lcd_4line();// going to default lcd screen size
  //---------------------RESISTOR MENU------------------------------------------
  if(menu_items && (BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_THREE || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_TWO || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_ONE )){
    display_1 = " A1  Baud ";
    display_2 = "   Menu   ";  
    display_3 = "";
    display_4 = "";
    while(switch_one_pressed){
      switch_two_pressed = FALSE;
      BaudMenuFG = TRUE;
      MainFG = FALSE;
      switch_one_pressed = FALSE;
    }  
  }
  //---------------------SHAPES MENU--------------------------------------------
  else if(menu_items && (BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_SIX || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_FIVE || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_FOUR )){
    display_1 = "   IOT    ";
    display_2 = "   Menu   ";  
    display_3 = "";
    display_4 = "";
    if(switch_one_pressed){
      switch_two_pressed = FALSE;
      IOTMenuFG = TRUE;
      MainFG = FALSE;
      switch_one_pressed = FALSE;

    }  
  }
  //---------------------SONG MENU----------------------------------------------
  else if(menu_items  && (BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_EIGHT || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_SEVEN)){
    display_1 = "   black   ";
    display_2 = "    test   ";  
    display_3 = "";
    display_4 = "";
    if(switch_one_pressed){
      switch_two_pressed = FALSE;
      switch_one_pressed = FALSE;
      //some declarations (wheel rate, IR ON, etc)
      IR_LED_ON();
      Five_msec_Delay(FOR_TENTH_SECOND);
      left_forward_rate = 1800;
      right_forward_rate = 1800;
      left_reverse_rate = 2500;
      right_reverse_rate = 2500;
      start_on_whiteFG = FALSE;
      int errorR=FALSE;
      int errorL=FALSE;

      //check if starting on white
      if((ADC_Left_Detector) < thresholdL && ADC_Right_Detector < thresholdR){
        start_on_whiteFG = TRUE;
      }
      
      while(ALWAYS){ //doing black line detection until done with the black line
        if(start_on_whiteFG){
          start_on_whiteFG = FALSE; //only want this first time
          left_wheel_forward_on(); //go forward
          right_wheel_forward_on();
          while(ADC_Left_Detector < thresholdL && ADC_Right_Detector < thresholdR); //do this until on black line
          left_wheel_forward_off();
          right_wheel_forward_off();
        }
        motor_time = RESET; //clear time counter to zero
        
        while(ADC_Right_Detector < thresholdR){//while loop for pivot correcting back from right sensor leaving
          left_wheel_forward_off();
          right_wheel_forward_on();
          while(ADC_Right_Detector < thresholdR); //do this until right sensor back on line
          right_wheel_forward_off();
          active_breaking_right();
          errorR = TRUE;
        }
        motor_time_prev = motor_time/3;//assign current time/2 count to temp time count for error correcting
        if(errorR){//if statement checking if left spin correction needed from correcting right pivot
          
          left_wheel_forward_on();
          right_wheel_reverse_on();
          motor_time = RESET; //to count back up to previous time;
          while(motor_time < motor_time_prev && motor_time <= 500); //turn until time reached
          right_wheel_reverse_off();
          left_wheel_forward_off();
        }
        
        motor_time = RESET; //clear time counter to zero
        
        while((ADC_Left_Detector) < thresholdL){//while loop for pivot correcting back from left sensor leaving
          right_wheel_forward_off();
          left_wheel_forward_on();
          while(ADC_Left_Detector < thresholdL); //do this until left sensor back on line
          left_wheel_forward_off();
          active_breaking_left();
          errorL = TRUE;
        }
        motor_time_prev = motor_time/3;//assign current time/2 count to temp time count for error correcting
        if(errorL){//if statement checking if right spin correction needed from correcting left pivot
          
          right_wheel_forward_on();
          left_wheel_reverse_on();
          motor_time = RESET; //to count back up to previous time;
          while(motor_time < motor_time_prev && motor_time <= 500); //turn until time reached
          left_wheel_reverse_off();
          right_wheel_forward_off();
        }
        
      
        while((ADC_Left_Detector) >= thresholdL && ADC_Right_Detector >= thresholdR){//if both sensors on black then go forward (WHILE)
          left_wheel_forward_on(); //go forward
          right_wheel_forward_on();
        }
        //if statement checking if wheel have left to right (work in progress)
      }
      IR_LED_OFF();
    }  
  }
}

void Baud_Menu(void){
  // Resistor Menu
// 
// Description: This function creates the menu for the resistor values and colors.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:    
//              char* display_1
//              char* display_2
//              char* display_3
//              char* display_4
//              volatile unsigned int ADC_Thumb;
//              volatile unsigned int switch_one_pressed;
//              volatile unsigned int switch_two_pressed;
//
// Author: David Pryor
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
    lcd_4line();// going to default lcd screen size
  //---------------------RESISTOR MENU------------------------------------------
    if(menu_items && (BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_ONE || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_TWO || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_THREE || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_FOUR )){
        display_1=" A1 Baud  ";
        display_2="   9600   ";
        if(switch_one_pressed){
            Init_Serial_UCA1(1);
            uart_puts("A1 Baud Rate at 9600\n");
            switch_one_pressed=FALSE;
        }
  }
  //---------------------SHAPES MENU--------------------------------------------
    else if(menu_items && (BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_FIVE  || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_SIX)){
        display_1=" A1 Baud  ";
        display_2="  115200  ";
        if(switch_one_pressed){
            uart_puts("A1 Baud Rate at 115200\n");
            Init_Serial_UCA1(0);
            switch_one_pressed=FALSE;
        } 
    }
    else if(menu_items && BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_SEVEN || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_EIGHT ){
        display_1=" calibrate";
        display_2="";
        if(switch_one_pressed){
            IR_Calibration();
            switch_one_pressed=FALSE;
        } 
    }
    if(switch_two_pressed){
        switch_one_pressed = FALSE;
        switch_two_pressed = FALSE;
        BaudMenuFG=FALSE;
        MainFG=TRUE;
    }
}

void IOT_Menu(void){
// Shape Menu
// 
// Description: This function creates the menu for the shapes.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals:    
//              char* display_1
//              char* display_2
//              char* display_3
//              volatile unsigned int ADC_Thumb;
//              volatile unsigned int switch_one_pressed;
//              volatile unsigned int switch_two_pressed;
//
// Author: David Pryor
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  
    if((ADC_Thumb < SECTION_NINE_START)){
        display_1=" Set SSID ";
        display_2="          ";
        display_3="          ";
        display_4="          ";
        if(switch_one_pressed==TRUE){
            uart_puts("AT+S.SSIDTXT=ncsu\r"); //Set SSID to ncsu
            switch_one_pressed=FALSE;
        }
    }
    else if((ADC_Thumb >= SECTION_NINE_START) && (ADC_Thumb < SECTION_EIGHT_START)){
        display_1=" Get SSID ";
        display_2="          ";
        display_3="          ";
        display_4="          ";
        if(switch_one_pressed==TRUE){
            uart_puts("AT+S.SSIDTXT\r"); //Get SSID to ncsu
            switch_one_pressed=FALSE;
        }
    }
    else if((ADC_Thumb >= SECTION_EIGHT_START) && (ADC_Thumb < SECTION_SEVEN_START)){
        display_1=" Set Host ";
        display_2="   Name   ";
        display_3="          ";
        display_4="          ";
        if(switch_one_pressed==TRUE){
            uart_puts("AT+S.SCFG=ip_hostname,ECE-306_08_C\r"); //Get SSID to ncsu
            switch_one_pressed=FALSE;
        }
    }
    else if((ADC_Thumb >= SECTION_SEVEN_START) && (ADC_Thumb < SECTION_SIX_START)){
        display_1=" Get Host ";
        display_2="   Name   ";
        display_3="          ";
        display_4="          ";
        if(switch_one_pressed==TRUE){
            uart_puts("AT+S.GCFG=ip_hostname\r"); //Get SSID to ncsu
            switch_one_pressed=FALSE;
        }
    }
    else if((ADC_Thumb >= SECTION_SIX_START) && (ADC_Thumb < SECTION_FIVE_START)){
        display_1=" Set Net. ";
        display_2=" Privacy  ";
        display_3=" Mode     ";
        display_4="          ";
        if(switch_one_pressed==TRUE){
            uart_puts("AT+S.SCFG=wifi_priv_mode,0\r"); //Get SSID to ncsu
            switch_one_pressed=FALSE;
        }
    }
    else if((ADC_Thumb >= SECTION_FIVE_START) && (ADC_Thumb < SECTION_FOUR_START)){
        display_1=" Get Net. ";
        display_2=" Privacy  ";
        display_3=" Mode     ";
        display_4="          ";
        if(switch_one_pressed==TRUE){
            uart_puts("AT+S.GCFG=wifi_priv_mode\r"); //Get SSID to ncsu
            switch_one_pressed=FALSE;
        }
    }
    else if((ADC_Thumb >= SECTION_FOUR_START) && (ADC_Thumb < SECTION_THREE_START)){
      display_1=" Set Net. ";
        display_2="   Mode   ";
        display_3="          ";
        display_4="          ";
        if(switch_one_pressed==TRUE){
            uart_puts("AT+S.SCFG=wifi_mode,1\r"); //Get SSID to ncsu
            switch_one_pressed=FALSE;
        }
    }
    else if((ADC_Thumb >= SECTION_THREE_START) && (ADC_Thumb < SECTION_TWO_START)){
        display_1=" Get Net. ";
        display_2="   Mode   ";
        display_3="          ";
        display_4="          ";
        if(switch_one_pressed==TRUE){
            uart_puts("AT+S.GCFG=wifi_mode\r"); //Get SSID to ncsu
            switch_one_pressed=FALSE;
        }
    }
    else if((ADC_Thumb >= SECTION_TWO_START) && (ADC_Thumb < SECTION_ONE_START)){
        display_1="   Save   ";
        display_2=" Settings ";
        display_3=" On Flash ";
        display_4="          ";
        if(switch_one_pressed==TRUE){
            uart_puts("AT&W\r"); //Get SSID to ncsu
            Five_msec_Delay(200); //delay to allow changed to take effect
            switch_one_pressed=FALSE;
        }
    }
    else if((ADC_Thumb >= SECTION_ONE_START)){
        display_1="  Reset   ";
        display_2="  Module  ";
        display_3="          ";
        display_4="          ";
        if(switch_one_pressed==TRUE){
            uart_puts("AT+CFUN=1\r"); //Get SSID to ncsu
            IOTHardwareReset();
            switch_one_pressed=FALSE;
        }
    } 
    if(switch_two_pressed){
      switch_one_pressed = FALSE;
      switch_two_pressed = FALSE;
    }
}

