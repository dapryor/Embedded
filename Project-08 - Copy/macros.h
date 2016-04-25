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
#define START					(0x00) // First element
#define MAX_SIZE_COUNT			        (0x05)
#define LINE_POS_0                              (0x00) // starting postion on lcd
#define LINE_POS_1                              (0x01) // starting postion on lcd
#define LINE_POS_2                              (0x02) // starting postion on lcd
#define LINE_POS_3                              (0x03) // starting postion on lcd
#define INCREMENT_ONCE                          (0x01) // increment by 1
#define MAX_FIVE_MSEC_COUNT                     (0x03E8) //1000
#define USE_IOT_WAKEUP                         (0x00)
#define USE_SMCLK                               (0x01)
#define TRUE                                    (1)
#define FALSE                                   (0)
#define POSITIVE                                (0) 
#define RESET                                   (0)
#define PREVIOUS                                (1)
#define WRITING_INDEX                           (9)
#define THRESHOLD                               (-30)
#define THRESHOLD_SENSITIVITY                   (250)
#define LCD_LINE_SIZE                           (10)
// SWITCHES --------------------------------------------------------------------
#define SWITCH_OFF				(0x00) 
#define SWITCH_ON				(0x01)
// CASE NUMBERS (THESE ARE TEMPORARY FILLERS!) ---------------------------------
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
#define SMCLK                                   (0x01)
#define IOT_FACTORY   			        (0x02) // This was LED 2
#define IOT_STA_MINIAP       	                (0x04) // This was LED 3
#define IOT_RESET            	                (0x08) // This was LED 4
#define XINR                                    (0x10) // XINR
#define XOUTR                                   (0x20) // XOUTR
#define CLEAR_REGISTER                          (0X0000)
// Timing Macros ---------------------------------------------------------------

#define FOR_ONE_SECOND                          (200)  // for use with 5msec sleep
#define FOR_TWO_SECOND                          (400)
#define FOR_150_MSEC                            (30)   
#define FOR_100_MSEC                            (20)
#define FOR_HALF_SECOND                         (100)
#define FOR_FOURTH_SECOND                       (50)
#define FOR_EIGHTH_SECOND                       (25)
#define FOR_TENTH_SECOND                        (20)
#define FOR_TEN_MSEC                            (2)
#define FOR_FIFTY_MSEC                          (10)
#define FOR_FORTY_MSEC                          (8)
#define FOR_THREEFIFTY_MSEC                     (70)
#define FOR_THREETWENTYFIVE_MSEC                (65)
#define FOR_FIFTEEN_MSEC                        (3)
#define FOR_FORTYFIVE_MSEC                      (9)
#define FOR_THIRTY_MSEC                         (6)
#define FOR_TWOHUNDRED_MSEC                     (40)
#define FOR_FIVE_SECONDS                        (1000)
#define FOR_THIRTY_SECONDS                      (6000)
#define FIVE_MSEC                               (5)
#define HALF                                    (2)

//DUTY CYCLES ------------------------------------------------------------------
#define TWENTYTWO_PERCENT                       (1800)
#define TWENTY_PERCENT                          (2000)
#define TWENTYEIGHT_PERCENT                     (2200)
#define THIRTYEIGHT_PERCENT                     (3000)
#define FORTYFOUR_PERCENT                       (3500)
#define FORTYSEVEN_PERCENT                      (3750)
#define FIFTY_PERCENT                           (4000)
#define SIXTYTWO_PERCENT                        (5000)
#define SEVENTYFIVE_PERCENT                     (6000)

//LOOP MACROS ------------------------------------------------------------------
#define INCREMENT_START                         (0)
#define THREE_ITERATIONS                        (3)
#define FOUR_ITERATIONS                         (4)
#define EIGHT_ITERATIONS                        (8)
#define TEN_ITERATIONS                          (10)
#define TWENTY_ITERATIONS                       (20)
//MENU -------------------------------------------------------------------------
#define MENU_ITEM_ONE                           (0)
#define MENU_ITEM_TWO                           (1)
#define MENU_ITEM_THREE                         (2)
#define MENU_ITEM_FOUR                          (3)     
#define MENU_ITEM_FIVE                          (4)
#define MENU_ITEM_SIX                           (5)
#define MENU_ITEM_SEVEN                         (6)
#define MENU_ITEM_EIGHT                         (7)
#define MENU_ITEM_NINE                          (8)
#define MENU_ITEM_TEN                           (9)     
#define MENU_ITEM_ELEVEN                        (10)
#define MENU_ITEM_TWELVE                        (11)
#define MENU_ITEM_THIRTEEN                      (12)
#define MENU_ITEM_FOURTEEN                      (13)     
#define MENU_ITEM_FIFTEEN                       (14)
#define MENU_ITEM_SIXTEEN                       (15)

#define BITSHIFT_R_SIX(X)                       ((X)>>(6))
#define BITSHIFT_R_SEVEN(X)                       ((X)>>(7))

#define SECTION_ONE_START                       (918)
#define SECTION_TWO_START                       (816)
#define SECTION_THREE_START                     (714)
#define SECTION_FOUR_START                      (612)
#define SECTION_FIVE_START                      (510)
#define SECTION_SIX_START                       (408)
#define SECTION_SEVEN_START                      (306)
#define SECTION_EIGHT_START                      (204)
#define SECTION_NINE_START                       (102)


#define CASE_ITEM_TWO                           (2)
#define CASE_ITEM_THREE                         (4)
#define CASE_ITEM_FOUR                          (6)
#define CASE_ITEM_FIVE                          (8)
#define CASE_ITEM_SIX                           (10)
#define CASE_ITEM_SEVEN                         (12)

#define MENU_PICK_ONE                           (1)
#define MENU_PICK_TWO                           (2)
#define MENU_PICK_THREE                         (3)
#define MENU_PICK_FOUR                          (4)     
#define MENU_PICK_FIVE                          (5)
#define MENU_PICK_SIX                           (0)
//CLOCK MACROS -----------------------------------------------------------------
#define FLLN_BITS                               (0x03ffu)
#define FLLN_255                                (0x00ffu)
#define CSLOCK                                  (0x01) // Any incorrect password locks registers
#define TA0CCR0_INTERVAL                        (25000) //50ms
#define TA0CCR1_INTERVAL                        (2500) //5ms
#define TA0CCR2_INTERVAL                        (250) // ~1msec
#define DEBOUNCE_MAX                            (10)
#define CCR1                                    (2)
#define CCR2                                    (4)
#define OVERFLOW                                (14)
//PWM --------------------------------------------------------------------------
#define WHEEL_PERIOD                            (8000) // wheel period of 8000 counts
//Serial------------------------------------------------------------------------
#define SMALL_RING_SIZE                         (16)
#define LARGE_RING_SIZE                         (16)
#define BEGINNING                               (0)
#define IOT_9600                                (1)
#define IOT_115200                                (0)
#define TX                                      (4)
#define RX                                      (2)
#define NONE                                    (0)
//BLACKLINE --------------------------------------------------------------------
#define MAX_CORRECTION_TIME                     (500) //max correction time for black line
#define TIME_RATIO                              (3) //time ratio for correcting movement
#define DEGREE_RATIO                            (0.638888) // ratio for accepting degree input
#define MAX_NUMBERBUF_SIZE                      (5)
#define MAX_ADCCHAR_SIZE                      (5)
#define MAX_COMMANDBUF_SIZE                     (30)
#define MAX_RECEIVE_SIZE                     (100)

#define FIRST_ELEMENT                           (0)
#define SECOND_ELEMENT                          (1)
#define THIRD_ELEMENT                           (2)        
#define FOURTH_ELEMENT                          (3)
#define FIFTH_ELEMENT                           (4)
#define SIXTH_ELEMENT                           (5)
#define SEVENTH_ELEMENT                         (6)

#define TENS                                    (10)
#define HUNDREDS                                (100)
#define THOUSANDS                               (1000)

#define IP_START_ADDR                           (17)
#define SSID_START_INDEX                        (32)