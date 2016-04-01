//------------------------------------------------------------------------------
// Macro Configurations

#define ON                   (0x01) // High
#define OFF                  (0x00) // Low
#define DEBUG_PORT_ON        (0x00) // Low

// Port 1 Pins
#define V_DETECT_R           (0x01) //
#define V_DETECT_L           (0x02) //
#define IR_LED               (0x04) //
#define V_THUMB              (0x08) //
#define SPI_CS_LCD           (0x10) // Old NTC - ADC Input
#define GPS_RESET            (0x10) // Old NTC
#define GPS_PWRCHK           (0x20) // GPS Power Check from GPS
#define SIMO_B               (0x40) // SPI mode - slave in/master out of USCI_B0
#define RS_LCD               (0x80) // SPI RS Command / Data selection
// Slave out not used but LCD, pin usec as SPI_RESET
//#define  SOMI_B            (0x80) // SPI mode - slave out/master in of USCI_B0

// Port 2 Pins
#define UCA0TXD              (0x01) // UCA0TXD
#define UCA0RXD              (0x02) // UCA0RXD
#define SPI_SCK_B0           (0x04) // SPI mode - clock output—USCI_B0
#define unused_2_3           (0x08) //
#define TEST_SIG             (0x10) //
#define CPU_RXD              (0x20) //
#define CPU_TXD              (0x40) //
#define PIN_PWR              (0x80) // NTC, ACCEL, LDR Power Source

// Port 3 Pins
#define XOUT                 (0x01) // Accelerometer X axis ADC signal
#define YOUT                 (0x02) // Accelerometer Y axis ADC signal
#define ZOUT                 (0x04) // Accelerometer Z axis ADC signal
#define GPS_PWRCNTL          (0x08) // GPS Power Control to GPS
#define SMCLK_OUT            (0x10) // SMCLK
#define R_FORWARD            (0x10) // 5
#define R_REVERSE            (0x20) // 6
#define L_FORWARD            (0x40) // 7
#define L_REVERSE            (0x80) // 8
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8

// Port 4 Pins
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2

// Port J Pins
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED4                 (0x08) // LED 4

// Control States
#define CNTL_STATE_INDEX        (3)
// control_state[0] Bit definitions
#define GPS_SIMPLE           (0x01)  //
#define GPGGA_filter         (0x02)  //
#define GPRMC_filter         (0x04)  //
#define GPS_ONOFF            (0x08)  //
#define LED_flash            (0x10)  //
#define LEDS5to8             (0x20)  //
#define USE_LED5             (0x40)  //
#define ADC_Conversion       (0x80)  //
#define USE_SMCLK            (0x00)  //

// control_state[1] Bit definitions
#define undefined_1_07       (0x01)  // #define LED1 (0x10) // LED 1
#define undefined_1_06       (0x02)  // #define LED2 (0x10) // LED 2
#define undefined_1_05       (0x04)  // #define LED3 (0x10) // LED 3
#define undefined_1_04       (0x08)  // #define LED4 (0x10) // LED 4
#define undefined_1_03       (0x10)  // #define LED5 (0x10) // LED 5
#define undefined_1_02       (0x20)  // #define LED6 (0x10) // LED 6
#define undefined_1_01       (0x40)  // #define LED7 (0x10) // LED 7
#define undefined_1_00       (0x80)  // #define LED8 (0x10) // LED 8

// control_state[2] Bit definitions
#define BLINK_LED            (0x01)  //
#define DISPLAY_UPDATE       (0x02)  //
#define undefined_2_05       (0x04)  //
#define undefined_2_04       (0x08)  //
#define undefined_2_03       (0x10)  //
#define undefined_2_02       (0x20)  //
#define undefined_2_01       (0x40)  //
#define undefined_2_00       (0x80)  //


// Systems
#define NULL ((void *) 0x0)
#define RESET_STATE          (0x00)  //

typedef _Bool bool;
#define FALSE (0)
#define TRUE  (~FALSE)

// Clocks
#define CSLOCK                  (0x01) // Any incorrect password locks registers
#define MCLK_FREQ           (8000000L)
#define SMCLK_FREQ          (8000000L)
//#define SMCLK_FREQ        (6000000L)
#define SMCLK_DIV                 (64)
#define LED5_SEL                (0x31) // LED5_SEL
#define SMCLK_SEL               (0x30) // SMCLK_SEL

// Timers
// Timer A0 Intervals
#define TA0CCR0_INTERVAL        (4096) // 32768 /  4096 = 1024 Hz  125 msec

// Timer A0[1-2+overflow] Intervals
#define TA0CCR1_INTERVAL        (8192) // 32768 /  8192 =    4 Hz  250 msec
#define TA0CCR2_INTERVAL       (16384) // 32768 / 16384 =    2 Hz  500 msec

// Timer A1 Intervals
#define TA1CCR0_INTERVAL        (4096) // 32768 /  4096 = 1024 Hz  125 msec

// Timer A1[1-2+overflow] Intervals
#define TA1CCR1_INTERVAL        (8192) // 32768 /  8192 =    4 Hz  250 msec
#define TA1CCR2_INTERVAL       (16384) // 32768 / 16384 =    2 Hz  500 msec

// Timer B0
#define TB0CCR0_INTERVAL        (2048) // 32768 /  4096 = 1024 Hz  125 msec

// Timer B0[1-2+overflow] Intervals
#define TB0CCR1_INTERVAL        (8192) // 32768 /  8192 =    4 Hz  250 msec
#define TB0CCR2_INTERVAL       (16384) // 32768 / 16384 =    2 Hz  500 msec

// Timer B1
#define TB1CCR0_INTERVAL        (1250) // 8,000,000 /  4 / 8 / 1250 =    5 msec

// Timer B1[1-2+overflow] Intervals
// SMCLK Source 8 MHz
//#define TB1CCR1_INTERVAL       (16000) // 8,000,000 /  4 / 8 / 16000 =    64 msec
#define TB1CCR1_INTERVAL       (31250) // 8,000,000 /  4 / 8 / 31250 =   125 msec
//#define TB1CCR1_INTERVAL       (32000) // 8,000,000 /  4 / 8 / 32000 =   128 msec
//#define TB1CCR2_INTERVAL       (50000) // 8,000,000 /  4 / 8 / 50000 =   200 msec
#define TB1CCR2_INTERVAL       (62500) // 8,000,000 /  4 / 8 / 50000 =   250 msec

// Timer B2
//#define TB2CCR0_INTERVAL        (4096) // 32768 /  4096 = 1024 Hz  125 msec
#define TB2CCR0_INTERVAL        (1250) // 8,000,000 /  4 / 8 / 1250 =    5 msec

// Timer B2[1-2+overflow] Intervals
#define TB2CCR1_INTERVAL        (8192) //
#define TB2CCR2_INTERVAL       (25060) //

#define ONE_SECOND (SMCLK_FREQ/SMCLK_DIV)
#define DEBOUNCE_PERIOD  (ONE_SECOND/4) //250ms
#define UINT_MAX                (1)
#define ASLEEP                  (1)
#define AWAKE                   (0)
#define S_TO_US          (1000000L)
#define CLK_DIV_4              (4L)
#define CLK_DIV_64            (64L)
#define MAX_DUTY          (0x2000L)
#define SLEEP_TIME             (2) // max 255 value

// With 8MHz SMCLK, this makes the SPI clock 100kHz.
#define SPI_CLK_PRESCALER      (80)

// Serial
#define CONTINUES            (0x01)   // Continue Processing
#define SMALL_RING_SIZE        (32)   // Ring Buffer Size
#define LARGE_RING_SIZE        (78)   // Ring Buffer Size
#define BEGINNING            (0x00)   // Beginning value of the Circualr buffer
#define NO_CHARACTER         (0x00)   // No character available
#define SPACE                (0x20)   // " " character
#define RETURN               (0x0D)   // " " Carraige Return

#define BAUD_4800            (0x00)   // Baud Rate 4800
#define BAUD_9600            (0x01)   // Baud Rate 9600
#define BAUD_19200           (0x02)   // Baud Rate 19200
#define BAUD_38400           (0x03)   // Baud Rate 38400
#define BAUD_57600           (0x04)   // Baud Rate 57600
#define BAUD_115200          (0x05)   // Baud Rate 115200
#define BAUD_230400          (0x06)   // Baud Rate 230400

// GPS
// GPS_SIMPLE           (0x01)  //
// GPGGA_filter         (0x02)  //
// GPRMC_filter         (0x04)  //

#define GARBAGE                0
#define GPS_MASK             (0x07)
#define NO_FILTER            (0x00)
#define GPRMC                (0x01)
#define GPGGA                (0x02)
//#define GPGSA                (0x02)
#define GPS_ON               (0x01)
#define GPS_OFF              (0x00)
//#define GPS_PWRCNTL         p3_4
//#define GPS_RESET           p3_5
//#define GPS_PWRCNTL_DDR    pd3_4
//#define GPS_RESET_DDR      pd3_5
#define VALID                 45
#define GPRMC_INDEX           20
#define GPGGA_INDEX           18

// Switches
// switch_states
// Port 4 uses the same bits for SW1
//#define SW1                (0x01) // Switch 1 [Defined with Port 4]
//#define SW2                (0x02) // Switch 2 [Defined with Port 4]
#define SW1_a                (0x04) //
#define SW2_a                (0x08) //
#define SW1_DEBOUNCE         (0x10) //
#define SW2_DEBOUNCE         (0x20) //
#define SW1_b                (0x40) //
#define SW2_b                (0x80) //
#define SW_DEBOUNCE_COUNT      (75) //

// LEDs
#define LED_BLINK              (10) //

// LCD
#define LINE1                   (0)
#define LINE2                   (1)
// Low - Command  High - Data
#define LCD_COMMAND             (0)
#define LCD_DATA                (1)
// DOG-M162 Instructions See ST7036 reference for details.
#define CLEAR_DISPLAY        (0x01)
#define RETURN_HOME          (0x02)

#define ENTRY_MODE           (0x04)
#define ENTRY_MODE_INCRE     (0x02)
#define ENTRY_MODE_SHIFT     (0x01)

#define DISPLAY_CTL          (0x08)
#define DISPLAY_CTL_ON       (0x04)
#define DISPLAY_CTL_CURSOR   (0x02)
#define DISPLAY_CTL_BLINK    (0x01)

#define FUNCTION_SET         (0x20)
#define FUNCTION_SET_8BIT    (0x10)
#define FUNCTION_SET_2LINE   (0x08)
#define FUNCTION_SET_2HIGH   (0x04)
#define FUNCTION_SET_INST2   (0x02)
#define FUNCTION_SET_INST1   (0x01)
#define FUNCTION_SET_INST0   (0x00)

#define SET_CGRAM(addr)      (0x40 | addr)
#define SET_DDRAM(addr)      (0x80 | addr)
#define BIAS_SET             (0x14)
#define BIAS_SET_FOURTH      (0x08)
#define POWER_SET            (0x50)
#define POWER_SET_ICON       (0x08)
#define POWER_SET_BOOST      (0x04)
#define POWER_SET_C5         (0x02)
#define POWER_SET_C4         (0x01)
#define FOLLOWER_CTL         (0x60)
#define FOLLOWER_CTL_FON     (0x08)
#define FOLLOWER_CTL_GAIN(g)    (g)
#define CONTRAST_SET         (0x70)
#define CONTRAST_SET_C3      (0x08)
#define CONTRAST_SET_C2      (0x04)
#define CONTRAST_SET_C1      (0x02)
#define CONTRAST_SET_C0      (0x01)
#define GAIN                 (0x0D) // Recommended value from DOG-M Reference

// Line 2 begins at this DDRAM address
#define LINE_TWO             (0x40)

#define LCD_LINE_1           (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_LINE_2           (0xC0) // Position Cursor at Character 01 of Line 2

#define LCD_L1_C01           (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_L1_C02           (0x81) // Position Cursor at Character 02 of Line 1
#define LCD_L1_C03           (0x82) // Position Cursor at Character 03 of Line 1
#define LCD_L1_C04           (0x83) // Position Cursor at Character 04 of Line 1
#define LCD_L1_C05           (0x84) // Position Cursor at Character 05 of Line 1
#define LCD_L1_C06           (0x85) // Position Cursor at Character 06 of Line 1
#define LCD_L1_C07           (0x86) // Position Cursor at Character 07 of Line 1
#define LCD_L1_C08           (0x87) // Position Cursor at Character 08 of Line 1
#define LCD_L1_C09           (0x88) // Position Cursor at Character 09 of Line 1
#define LCD_L1_C10           (0x89) // Position Cursor at Character 10 of Line 1
#define LCD_L1_C11           (0x8A) // Position Cursor at Character 11 of Line 1
#define LCD_L1_C12           (0x8B) // Position Cursor at Character 12 of Line 1
#define LCD_L1_C13           (0x8C) // Position Cursor at Character 13 of Line 1
#define LCD_L1_C14           (0x8D) // Position Cursor at Character 14 of Line 1
#define LCD_L1_C15           (0x8E) // Position Cursor at Character 15 of Line 1
#define LCD_L1_C16           (0x8F) // Position Cursor at Character 16 of Line 1
#define LCD_L2_C01           (0xC0) // Position Cursor at Character 01 of Line 2
#define LCD_L2_C02           (0xC1) // Position Cursor at Character 02 of Line 2
#define LCD_L2_C03           (0xC2) // Position Cursor at Character 03 of Line 2
#define LCD_L2_C04           (0xC3) // Position Cursor at Character 04 of Line 2
#define LCD_L2_C05           (0xC4) // Position Cursor at Character 05 of Line 2
#define LCD_L2_C06           (0xC5) // Position Cursor at Character 06 of Line 2
#define LCD_L2_C07           (0xC6) // Position Cursor at Character 07 of Line 2
#define LCD_L2_C08           (0xC7) // Position Cursor at Character 08 of Line 2
#define LCD_L2_C09           (0xC8) // Position Cursor at Character 09 of Line 2
#define LCD_L2_C10           (0xC9) // Position Cursor at Character 10 of Line 2
#define LCD_L2_C11           (0xCA) // Position Cursor at Character 11 of Line 2
#define LCD_L2_C12           (0xCB) // Position Cursor at Character 12 of Line 2
#define LCD_L2_C13           (0xCC) // Position Cursor at Character 13 of Line 2
#define LCD_L2_C14           (0xCD) // Position Cursor at Character 14 of Line 2
#define LCD_L2_C15           (0xCE) // Position Cursor at Character 15 of Line 2
#define LCD_L2_C16           (0xCF) // Position Cursor at Character 16 of Line 2


//