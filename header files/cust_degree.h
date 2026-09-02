/*-------------------------------------------------------------------
File    : degree_char.c
Purpose : This file contains function to create and display
          custom degree (°) symbol on LCD using CGRAM.
-------------------------------------------------------------------*/

#include <lpc21xx.h>      // LPC21xx register definitions
#include "lcdtotal.h"     // LCD function declarations

//-----------------------------------------------------------
// Function: degreechar
// Purpose : Create custom degree symbol in LCD CGRAM
//           and display temperature unit (°C) on LCD.
//-----------------------------------------------------------
void degreechar(void)
{
	// Custom character pattern for degree symbol (5x7 format)
	char degree[] = {0X1C, 0X14, 0X1C, 0X00, 0X00, 0X00, 0X00};

	// Set CGRAM address to store custom character
	cmdLCD(0x40);

	// Load custom degree character pattern into CGRAM
	custLCD(degree);

	// Move cursor to desired display position
	cmdLCD(0XCE);

	// Display custom degree character
	dataLCD(0);

	// Display 'C' for Celsius
	dataLCD('C');
}

