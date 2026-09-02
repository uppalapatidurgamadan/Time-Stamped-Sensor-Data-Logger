/*-------------------------------------------------------------------
File    : lcd.c
Purpose : LCD interface functions for LPC21xx.
          Provides routines to initialize LCD, send commands,
          display characters, strings, integers, and custom characters.
-------------------------------------------------------------------*/

#include <lpc21xx.h>
#include "delay.h"
#include "defines.h"
#include "lcdtotal.h"

//-----------------------------------------------------------
// LCD control pin definitions
//-----------------------------------------------------------
#define RS   18    // Register Select pin
#define RW   19    // Read/Write pin
#define EN   20    // Enable pin
#define LEDS 0xff  // LCD data lines mask (8-bit mode)

//-----------------------------------------------------------
// Function: initLCDdat
// Purpose : Initialize LCD in 8-bit mode and configure
//           display parameters
//-----------------------------------------------------------
void initLCDdat(void)
{
	// Configure LCD control and data pins as output
	IODIR0 |= (LEDS << 8) | (1 << RS) | (1 << RW) | (1 << EN);

	delay_ms(30);      // LCD power-on delay

	// LCD initialization sequence
	cmdLCD(0x30);
	delay_ms(4);
	cmdLCD(0x30);
	delay_ms(4);
	cmdLCD(0x30);
	delay_ms(4);

	cmdLCD(0x38);      // 8-bit, 2-line, 5x7 font
	cmdLCD(0x10);      // Cursor move
	cmdLCD(0x01);      // Clear display
	cmdLCD(0x06);      // Entry mode set
	cmdLCD(0x0E);      // Display ON, cursor ON
}

//-----------------------------------------------------------
// Function: cmdLCD
// Purpose : Send a command to the LCD
//-----------------------------------------------------------
void cmdLCD(unsigned char val)
{
	IOCLR0 = 1 << RS;   // Select command register
	writeLCD(val);     // Write command to LCD
}

//-----------------------------------------------------------
// Function: writeLCD
// Purpose : Write data/command byte to LCD
//-----------------------------------------------------------
void writeLCD(unsigned char var)
{
	IOCLR0 = 1 << RW;       // Select write mode
	IOCLR0 = LEDS << 8;     // Clear previous data
	WRITEBYTE(IOSET0, 8, var); // Place data on bus

	IOSET0 = 1 << EN;       // Enable pulse
	delay_ms(5);
	IOCLR0 = 1 << EN;
	delay_ms(5);
}

//-----------------------------------------------------------
// Function: dataLCD
// Purpose : Send data (character) to LCD
//-----------------------------------------------------------
void dataLCD(unsigned char var)
{
	IOSET0 = 1 << RS;   // Select data register
	writeLCD(var);     // Write data to LCD
}

//-----------------------------------------------------------
// Function: writeString
// Purpose : Display a string on the LCD
//-----------------------------------------------------------
void writeString(char *p)
{
	while (*p)
	{
		dataLCD(*p);    // Display character
		p++;
	}
}

//-----------------------------------------------------------
// Function: writeint
// Purpose : Display integer value on the LCD
//-----------------------------------------------------------
void writeint(int num)
{
	int rev = 0, temp, cnt1 = 0, cnt2 = 0;

	// Handle zero case
	if (num == 0)
	{
		dataLCD('0');
		return;
	}

	// Reverse number and count digits
	temp = num;
	for (; temp != 0; temp /= 10)
	{
		cnt1++;
		rev = rev * 10 + (temp % 10);
	}

	// Display digits in correct order
	temp = rev;
	for (; temp != 0; temp /= 10)
	{
		cnt2++;
		dataLCD((temp % 10) + '0');
	}

	// Display remaining zeros if any
	cnt1 = cnt1 - cnt2;
	while (cnt1)
	{
		dataLCD('0');
		cnt1--;
	}
}

//-----------------------------------------------------------
// Function: custLCD
// Purpose : Write custom character data to LCD CGRAM
//-----------------------------------------------------------
void custLCD(char *p)
{
	int i;
	for (i = 0; i < 8; i++)
	{
		dataLCD(p[i]);  // Load custom character pattern
	}
}

