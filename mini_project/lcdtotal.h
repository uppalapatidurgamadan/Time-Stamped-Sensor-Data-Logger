/*-------------------------------------------------------------------
File    : lcdtotal.h
Purpose : Function prototypes for interfacing 16x2 LCD with LPC21xx.
          Contains initialization, command, data, and utility
          display functions used across the project.
-------------------------------------------------------------------*/

//-----------------------------------------------------------
// Function: initLCDdat
// Purpose : Initializes LCD in 8-bit mode.
//           Configures data and control pins and sends
//           required initialization command sequence.
//-----------------------------------------------------------
void initLCDdat(void);

//-----------------------------------------------------------
// Function: writeLCD
// Purpose : Low-level function to write either command or
//           data byte to LCD depending on RS value.
//-----------------------------------------------------------
void writeLCD(unsigned char);

//-----------------------------------------------------------
// Function: dataLCD
// Purpose : Sends a single data character to LCD display.
//           RS is set internally for data mode.
//-----------------------------------------------------------
void dataLCD(unsigned char);

//-----------------------------------------------------------
// Function: cmdLCD
// Purpose : Sends a command byte to LCD.
//           RS is cleared internally for command mode.
//-----------------------------------------------------------
void cmdLCD(unsigned char);

//-----------------------------------------------------------
// Function: writeString
// Purpose : Displays a null-terminated string on LCD by
//           repeatedly calling dataLCD().
//-----------------------------------------------------------
void writeString(char *);

//-----------------------------------------------------------
// Function: writeint
// Purpose : Converts an integer into characters and displays
//           it on LCD (used for numeric output).
//-----------------------------------------------------------
void writeint(int);

//-----------------------------------------------------------
// Function: custLCD
// Purpose : Writes 8 bytes of custom character data into
//           LCD CGRAM (used for special symbols).
//-----------------------------------------------------------
void custLCD(char *);

//-----------------------------------------------------------
// Function: degreechar
// Purpose : Creates and displays degree symbol (°C) on LCD
//           using custom character generation.
//-----------------------------------------------------------
void degreechar(void);

