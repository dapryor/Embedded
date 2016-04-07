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

void Menu_Process(void){
  lcd_4line();
  //---------------------9600 BAUD RATE-----------------------------------------
  if(menu_items && ((ADC_Thumb>>7) == 2 || (ADC_Thumb>>7) == 1 || (ADC_Thumb>>7) == 0 )){
    display_1 = " Resistor ";
    display_2 = "   Menu   ";  
    display_3 = "";
    display_4 = "";
    if(switch_one_pressed){
      switch_two_pressed = FALSE;
      Resistor_Menu();
    }  
  }
  //---------------------115200 BAUD RATE-----------------------------------------
  else if(menu_items && ((ADC_Thumb>>7) == 5 || (ADC_Thumb>>7) == 4 || (ADC_Thumb>>7) == 3 )){
    display_1 = "  Shapes  ";
    display_2 = "   Menu   ";  
    display_3 = "";
    display_4 = "";
    if(switch_one_pressed){
      switch_one_pressed = FALSE;
    }  
  }
  //---------------------BAUD RATE TEST-----------------------------------------
  else if(menu_items  && ((ADC_Thumb>>7) == 7 || (ADC_Thumb>>7) == 6)){
    display_1 = "   Song   ";
    display_2 = "   Menu   ";  
    display_3 = "";
    display_4 = "";
    if(switch_one_pressed){
      switch_one_pressed = FALSE;
    }  
  }
}

void Resistor_Menu(void){
  if((ADC_Thumb>>6 == 0) || (ADC_Thumb>>6 == 1)){
    display_1 = "   Color  ";
    display_2 = "   Black  ";  
    display_3 = "   Value  ";
    display_4 = "    00    ";
  }
  else if((ADC_Thumb>>6 == 2) || (ADC_Thumb>>6 == 3)){
    display_1 = "   Color  ";
    display_2 = "   Brown  ";  
    display_3 = "   Value  ";
    display_4 = "    01    ";
  }
  else if((ADC_Thumb>>6 == 4) || (ADC_Thumb>>6 == 5)){
    display_1 = "   Color  ";
    display_2 = "    Red   ";  
    display_3 = "   Value  ";
    display_4 = "    02    ";
  }
  else if((ADC_Thumb>>6 == 6) || (ADC_Thumb>>6 == 7)){
    display_1 = "   Color  ";
    display_2 = "  Orange  ";  
    display_3 = "   Value  ";
    display_4 = "    03    ";
  }
  else if((ADC_Thumb>>6 == 8) || (ADC_Thumb>>6 == 9)){
    display_1 = "   Color  ";
    display_2 = "  Yellow  ";  
    display_3 = "   Value  ";
    display_4 = "    04    ";
  }
  else if((ADC_Thumb>>6 == 10) || (ADC_Thumb>>6 == 11)){
    display_1 = "   Color  ";
    display_2 = "   Green  ";  
    display_3 = "   Value  ";
    display_4 = "    05    ";
  }
  else if((ADC_Thumb>>6 == 12)){
    display_1 = "   Color  ";
    display_2 = "   Blue   ";  
    display_3 = "   Value  ";
    display_4 = "    06    ";
  }
  else if((ADC_Thumb>>6 == 13)){
    display_1 = "   Color  ";
    display_2 = "  Violet  ";  
    display_3 = "   Value  ";
    display_4 = "    07    ";
  }
  else if((ADC_Thumb>>6 == 14)){
    display_1 = "   Color  ";
    display_2 = "   Gray   ";  
    display_3 = "   Value  ";
    display_4 = "    08    ";
  }
  else if((ADC_Thumb>>6 == 15)){
    display_1 = "   Color  ";
    display_2 = "   White  ";  
    display_3 = "   Value  ";
    display_4 = "    09    ";
  }
  Display_Process();
  if(switch_two_pressed){
    switch_one_pressed = FALSE;
    switch_two_pressed = FALSE;
  }
}

void Shapes_Menu(void){
  if((ADC_Thumb>>6 == 0) || (ADC_Thumb>>6 == 1)){
    display_1 = "          ";
    display_2 = "  Circle  ";  
    display_3 = "  Square  ";
    display_4 = "";
  }
  else if((ADC_Thumb>>6 == 2) || (ADC_Thumb>>6 == 3)){
    display_1 = "  Circle  ";
    display_2 = "  Square  ";  
    display_3 = " Triangle ";
    display_4 = "";
  }
  else if((ADC_Thumb>>6 == 4) || (ADC_Thumb>>6 == 5)){
    display_1 = "  Square  ";
    display_2 = " Triangle ";  
    display_3 = "  Octagon ";
    display_4 = "";
  }
  else if((ADC_Thumb>>6 == 6) || (ADC_Thumb>>6 == 7)){
    display_1 = " Triangle ";
    display_2 = "  Octagon ";  
    display_3 = " Pentagon ";
    display_4 = "";
  }
  else if((ADC_Thumb>>6 == 8) || (ADC_Thumb>>6 == 9)){
    display_1 = "  Octagon ";
    display_2 = " Pentagon ";  
    display_3 = "  Hexagon ";
    display_4 = "";
  }
  else if((ADC_Thumb>>6 == 10) || (ADC_Thumb>>6 == 11)){
    display_1 = " Pentagon ";
    display_2 = "  Hexagon ";  
    display_3 = "   Cube   ";
    display_4 = "";
  }
  else if((ADC_Thumb>>6 == 12)){
    display_1 = "  Hexagon ";
    display_2 = "   Cube   ";  
    display_3 = "   Oval   ";
    display_4 = "";
  }
  else if((ADC_Thumb>>6 == 13)){
    display_1 = "   Cube   ";
    display_2 = "   Oval   ";  
    display_3 = "  Sphere  ";
    display_4 = "";
  }
  else if((ADC_Thumb>>6 == 14)){
    display_1 = "   Oval   ";
    display_2 = "  Sphere  ";  
    display_3 = " Cylinder ";
    display_4 = "";
  }
  else if((ADC_Thumb>>6 == 15)){
    display_1 = "  Sphere  ";
    display_2 = " Cylinder ";  
    display_3 = "          ";
    display_4 = "";
  }
  lcd_BIG_mid();
  Display_Process();
  if(switch_two_pressed){
    switch_one_pressed = FALSE;
    switch_two_pressed = FALSE;
  }
}
void Song_Menu(void){}