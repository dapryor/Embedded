//------------------------------------------------------------------------------
//  File Name : macros.h
//
//  Description: This file contains the Macros used throughout the C functions
//
//
//  David Pryor
//  Jan 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
// Required defines
//------------------------------------------------------------------------------
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                                  (1)
#define CNTL_STATE_INDEX                        (3) // Control States
#define EMPTY_REGISTER			        (0x00)
#define SET_INPUT				(0x00) // value to set port as input
#define SW1                  	                (0x01) // Switch 1
#define SW2                  	                (0x02) // Switch 2
#define START					(0x00) // First element
#define MAX_SIZE_COUNT			        (0x05)
#define LINE_POS_1                              (0x01) // starting postion on lcd
#define LINE_POS_2                              (0x02) // starting postion on lcd
#define LINE_POS_3                              (0x03) // starting postion on lcd
#define INCREMENT_ONCE                          (0x01) // increment by 1
#define MAX_FIVE_MSEC_COUNT                     (0x03E8) //1000
// SWITCHES
#define SWITCH_OFF				(0x00) 
#define SWITCH_ON				(0x01)
// CASE NUMBERS (THESE ARE TEMPORARY FILLERS!)
#define COUNT_TWOFIDDY_MSEC			(0x32) //50
#define COUNT_FIVEHUNNED_MSEC			(0x64) //100
#define COUNT_SEVENFIDDY_MSEC			(0x96) //150
#define COUNT_ONETHOUSAND_MSEC			(0xC8) //200
#define COUNT_TWELVEFIDDY_MSEC			(0xFA) //250
//------------------------------------------------------------------------------
// LCD
#define LCD_HOME_L1	                        (0x80)
#define LCD_HOME_L2         	                (0xA0)
#define LCD_HOME_L3         	                (0xC0)
#define LCD_HOME_L4         	                (0xE0)
#define LINE_SIZE				(0x0B)
//------------------------------------------------------------------------------
//port 1 configure
#define V_DETECT_R				(0x01) //
#define V_DETECT_L				(0x02) //
#define IR_LED					(0x04) //
#define V_THUMB					(0x08) //
#define SPI_CS_LCD				(0x10) // LCD Chip Select
#define RESET_LCD				(0x20) // LCD Reset
#define SIMO_B					(0x40) // SPI mode - slave in/master out of USCI_B0
#define SOMI_B					(0x80) // SPI mode - slave out/master in of USCI_B0
//------------------------------------------------------------------------------
//Configure Port 2
#define USB_TXD				        (0x01) //
#define USB_RXD				        (0x02) //
#define SPI_SCK				        (0x04) //
#define UNKNOWN1				(0x08) //
#define UNKNOWN2				(0x10) // 
#define CPU_TXD				        (0x20) // 
#define CPU_RXD				        (0x40) // 
#define UNKNOWN3				(0x80) //
//------------------------------------------------------------------------------
//Configure Port 3
#define ACCEL_X				        (0x01) //
#define ACCEL_Y				        (0x02) //
#define ACCEL_Z				        (0x04) //
#define LCD_BACKLITE			        (0x08) //
#define R_FORWARD        	                (0x10) // This was LED 5
#define R_REVERSE        	                (0x20) // This was LED 6
#define L_FORWARD        	                (0x40) // This was LED 7
#define L_REVERSE        	                (0x80) // This was LED 8
//------------------------------------------------------------------------------
//Configure Port 4
#define SW1					(0x01) //
#define SW2					(0x02) //
//------------------------------------------------------------------------------
// Port J Pins
#define IOT_WAKEUP           	                (0x01) // This was LED 1
#define IOT_FACTORY   			        (0x02) // This was LED 2
#define IOT_STA_MINIAP       	                (0x04) // This was LED 3
#define IOT_RESET            	                (0x08) // This was LED 4
#define XINR				        (0x10) // XINR
#define XOUTR				        (0x20) // XOUTR



