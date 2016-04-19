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
      switch_two_pressed = FALSE;
      Baud_Menu(); //Run resistor menu
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
      switch_two_pressed = FALSE;
      //IOT_Menu(); //run shape menu
    }  
  }
  //---------------------SONG MENU----------------------------------------------
  else if(menu_items  && (BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_EIGHT || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_SEVEN)){
    display_1 = "   blank   ";
    display_2 = "   Menu   ";  
    display_3 = "";
    display_4 = "";
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
    else if(menu_items && (BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_FIVE  || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_SIX || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_SEVEN || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_EIGHT )){
        display_1=" A1 Baud  ";
        display_2="  115200  ";
        if(switch_one_pressed){
            uart_puts("A1 Baud Rate at 115200\n");
            Init_Serial_UCA1(0);
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

