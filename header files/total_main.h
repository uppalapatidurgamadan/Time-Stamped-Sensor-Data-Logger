/*-------------------------------------------------------------------
File    : total_main.h
Purpose : Header file containing function prototypes, macro
          definitions, and declarations used across the project.
-------------------------------------------------------------------*/

//-----------------------------------------------------------
// Function prototypes for temperature sensing and display
//-----------------------------------------------------------

// Reads temperature from LM35 sensor and displays it on LCD
void lm35(void);

// Reads RTC time/date and displays it on LCD
void rtc(void);

// Checks whether one minute has elapsed
int minpassed(void);

// Sends temperature information to UART once every minute
void min_alert(void);

// Displays temperature with timestamp on UART
void disp_uart(float);

//-----------------------------------------------------------
// Menu and user input related function prototypes
//-----------------------------------------------------------

// Displays menu and allows editing of RTC and threshold values
void menu(int *, int *, int *, int *, int *, int *, int *, int *);

// Reads numeric input from keypad until termination key is pressed
int ip_keypad(void);

//-----------------------------------------------------------
// GPIO switch related definitions
//-----------------------------------------------------------

// Switch pin number definition
#define SW 25

// Reads switch status (pressed or not)
char switch_stat(void);

//-----------------------------------------------------------
// Alert and threshold related function prototypes
//-----------------------------------------------------------

// Generates alert if temperature exceeds threshold
void alert_temp(int temp);

