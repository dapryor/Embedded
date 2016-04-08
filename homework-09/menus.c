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
char song[] = "We're the Red and White from State And we know we are the best. A hand behind our back, We can take on all the rest. Come over the hill, Carolina. Devils and Deacs stand in line. The Red and White from N.C. State. Go State!";
char lcdBuff[DEBOUNCE_MAX] = "         ";

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
    display_1 = " Resistor ";
    display_2 = "   Menu   ";  
    display_3 = "";
    display_4 = "";
    while(switch_one_pressed){
      switch_two_pressed = FALSE;
      Resistor_Menu(); //Run resistor menu
    }  
  }
  //---------------------SHAPES MENU--------------------------------------------
  else if(menu_items && (BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_SIX || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_FIVE || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_FOUR )){
    display_1 = "  Shapes  ";
    display_2 = "   Menu   ";  
    display_3 = "";
    display_4 = "";
    if(switch_one_pressed){
      
      switch_two_pressed = FALSE;
      Shapes_Menu(); //run shape menu
    }  
  }
  //---------------------SONG MENU----------------------------------------------
  else if(menu_items  && (BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_EIGHT || BITSHIFT_R_SEVEN(ADC_Thumb) == MENU_ITEM_SEVEN)){
    display_1 = "   Song   ";
    display_2 = "   Menu   ";  
    display_3 = "";
    display_4 = "";
    while(switch_one_pressed){
      switch_two_pressed = FALSE;
      Song_Menu(); //run song menu
    }  
    TA0CCTL1 |= CCIE; //Turning on timer
  }
}

void Resistor_Menu(void){
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
  if((BITSHIFT_R_SIX(ADC_Thumb)  == MENU_ITEM_ONE) || (BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_TWO)){
    display_1 = "   Color  ";
    display_2 = "   Black  ";  
    display_3 = "   Value  ";
    display_4 = "    00    ";
  }
  else if((BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_THREE) || (BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_FOUR)){
    display_1 = "   Color  ";
    display_2 = "   Brown  ";  
    display_3 = "   Value  ";
    display_4 = "    01    ";
  }
  else if((BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_FIVE) || (BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_SIX)){
    display_1 = "   Color  ";
    display_2 = "    Red   ";  
    display_3 = "   Value  ";
    display_4 = "    02    ";
  }
  else if((BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_SEVEN) || (BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_EIGHT)){
    display_1 = "   Color  ";
    display_2 = "  Orange  ";  
    display_3 = "   Value  ";
    display_4 = "    03    ";
  }
  else if((BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_NINE) || (BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_TEN)){
    display_1 = "   Color  ";
    display_2 = "  Yellow  ";  
    display_3 = "   Value  ";
    display_4 = "    04    ";
  }
  else if((BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_ELEVEN) || (BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_TWELVE)){
    display_1 = "   Color  ";
    display_2 = "   Green  ";  
    display_3 = "   Value  ";
    display_4 = "    05    ";
  }
  else if((BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_THIRTEEN)){
    display_1 = "   Color  ";
    display_2 = "   Blue   ";  
    display_3 = "   Value  ";
    display_4 = "    06    ";
  }
  else if((BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_FOURTEEN)){
    display_1 = "   Color  ";
    display_2 = "  Violet  ";  
    display_3 = "   Value  ";
    display_4 = "    07    ";
  }
  else if((BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_FIFTEEN)){
    display_1 = "   Color  ";
    display_2 = "   Gray   ";  
    display_3 = "   Value  ";
    display_4 = "    08    ";
  }
  else if((BITSHIFT_R_SIX(ADC_Thumb) == MENU_ITEM_SIXTEEN)){
    display_1 = "   Color  ";
    display_2 = "   White  ";  
    display_3 = "   Value  ";
    display_4 = "    09    ";
  }
  
  if(switch_two_pressed){
    switch_one_pressed = FALSE;
    switch_two_pressed = FALSE;
  }
}

void Shapes_Menu(void){
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
  lcd_BIG_mid();
  
  while(!switch_two_pressed){
    if((ADC_Thumb < SECTION_NINE_START)){
      display_1 = "          ";
      display_2 = "  Circle  ";  
      display_3 = "  Square  ";
      //display_4 = "";
    }
    else if((ADC_Thumb >= SECTION_NINE_START) && (ADC_Thumb < SECTION_EIGHT_START)){
      display_1 = "  Circle  ";
      display_2 = "  Square  ";  
      display_3 = " Triangle ";
      //display_4 = "";
    }
    else if((ADC_Thumb >= SECTION_EIGHT_START) && (ADC_Thumb < SECTION_SEVEN_START)){
      display_1 = "  Square  ";
      display_2 = " Triangle ";  
      display_3 = "  Octagon ";
      //display_4 = "";
    }
    else if((ADC_Thumb >= SECTION_SEVEN_START) && (ADC_Thumb < SECTION_SIX_START)){
      display_1 = " Triangle ";
      display_2 = "  Octagon ";  
      display_3 = " Pentagon ";
      //display_4 = "";
    }
    else if((ADC_Thumb >= SECTION_SIX_START) && (ADC_Thumb < SECTION_FIVE_START)){
      display_1 = "  Octagon ";
      display_2 = " Pentagon ";  
      display_3 = "  Hexagon ";
      //display_4 = "";
    }
    else if((ADC_Thumb >= SECTION_FIVE_START) && (ADC_Thumb < SECTION_FOUR_START)){
      display_1 = " Pentagon ";
      display_2 = "  Hexagon ";  
      display_3 = "   Cube   ";
      //display_4 = "";
    }
    else if((ADC_Thumb >= SECTION_FOUR_START) && (ADC_Thumb < SECTION_THREE_START)){
      display_1 = "  Hexagon ";
      display_2 = "   Cube   ";  
      display_3 = "   Oval   ";
      //display_4 = "";
    }
    else if((ADC_Thumb >= SECTION_THREE_START) && (ADC_Thumb < SECTION_TWO_START)){
      display_1 = "   Cube   ";
      display_2 = "   Oval   ";  
      display_3 = "  Sphere  ";
      //display_4 = "";
    }
    else if((ADC_Thumb >= SECTION_TWO_START) && (ADC_Thumb < SECTION_ONE_START)){
      display_1 = "   Oval   ";
      display_2 = "  Sphere  ";  
      display_3 = " Cylinder ";
      //display_4 = "";
    }
    else if((ADC_Thumb >= SECTION_ONE_START)){
      display_1 = "  Sphere  ";
      display_2 = " Cylinder ";  
      display_3 = "          ";
      //display_4 = "";
    }

  } 
    /*if(switch_two_pressed){
      switch_one_pressed = FALSE;
      switch_two_pressed = FALSE;
    }*/
}

void Song_Menu(void){
// Resistor Menu
// 
// Description: This function creates the menu for the song scroll.
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
//              char song[]
//              char lcdBuff[DEBOUNCE_MAX]
//
// Author: David Pryor
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.4.1)
//==============================================================================
  int i;
  int counter = FALSE;
  int thumbPrev = ADC_Thumb;
  int deltaThumb = FALSE;
  int colorSwitch = FALSE;
  char* stringDisplay = lcdBuff;
  
  TA0CCTL1 &= ~CCIE; //disable timer used to update screen
  lcd_BIG_mid(); //make big mid
  while((song[counter] != '\0') && switch_two_pressed == FALSE){ //until end of song or exit
    deltaThumb = ADC_Thumb - thumbPrev;

    if(deltaThumb < THRESHOLD){ //if moved a certain distance CCW
      thumbPrev = ADC_Thumb; //update thumbprev
      
      if(!colorSwitch){ //used to toggle between red/white and white/red
        display_1 = "   Red    ";
        display_3 = "  White   ";
        colorSwitch = TRUE;
      }
      else
      {
        display_1 = "  White   ";
        display_3 = "   Red    ";
        colorSwitch = FALSE;
      }
      
      lcdBuff[WRITING_INDEX] = song[counter++]; //writing song to a buffer starting on right side
      display_2 = stringDisplay; //display new contents
      Display_Process();
      for(i=1; i<=WRITING_INDEX; i++){ //shift values to left to create scroll
        lcdBuff[i-PREVIOUS] = lcdBuff[i];
      }
      
    }
    if(deltaThumb>POSITIVE){ //allows for one way scroll
        thumbPrev = ADC_Thumb;
    }
  }
  
  if(switch_two_pressed){
    switch_one_pressed = FALSE;
    switch_two_pressed = FALSE;
  }
  counter = FALSE; //reset song counter
}
