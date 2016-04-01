//------------------------------------------------------------------------------
//  File Name : functions.h
//
//  Description: This file contains the Macros used throughout the C functions
//
//
//  David Pryor
//  Jan 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
// Function prototypes main
void main(void);

// Function prototypes clocks
void Init_Clocks(void);

// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
 __interrupt void TIMER2_B1_ISR(void);
void Init_Timer_A0(void);
void Init_Timer_B2(void);
void measure_delay(void);
void usleep10(unsigned int usec);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(void);

// LCD
void Init_LCD(void);
void WriteIns(char instruction);
void WriteData(char data);
void ClrDisplay(void);
void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);

void grab_a_character(void);
int wait_for_character(void);
void menu(void);

// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);

// Init
void Init_Conditions(void);
void Init_Timers(void);
void Init_LEDs(void);

// Timers
void five_msec_sleep(unsigned int fivemsec);
void Timer_code(void);
void Display_Process(void); //UNSURE OF CORRECT FILE.  PUTTING THIS HERE FOR SAFE KEEPING.
