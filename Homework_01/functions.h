// Function prototypes main
void main(void);
void Init_Conditions(void);
void Switches_Process(void);
void Init_Timers(void);
void Init_LEDs(void);

// Function prototypes clocks
void Init_Clocks(void);


// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
__interrupt void Timer0_A0_ISR(void);
void Init_Timer_A0(void);
void Init_Timer_B2(void);
void Timer_code(void);
void usleep10(unsigned int usec);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(void);
