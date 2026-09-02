/*-------------------------------------------------------------------
File    : rtc_display.c
Purpose : This file contains functions to display RTC time,
          date, and day on LCD, and to check whether one
          minute has elapsed.
-------------------------------------------------------------------*/

#include <lpc21xx.h>          // LPC21xx register definitions
#include "rtc_defines.h"      // RTC function prototypes and macros
#include "lcdtotal.h"         // LCD function declarations

//-----------------------------------------------------------
// Function: rtc
// Purpose : Read RTC time, date, and day of week
//           and display them on the LCD.
//-----------------------------------------------------------
void rtc(void)
{
	// Array holding day names corresponding to DOW value
	char week[][4] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};

	// Variables to store time and date values
	int hour, min = -2, sec, dom, mon, year, dow;

	// Set LCD cursor to first line
	cmdLCD(0x80);

	// Read current RTC time
	readRTCtime(&hour, &min, &sec);

	// Display hour on LCD
	dataLCD((hour / 10) + '0');
	dataLCD((hour % 10) + '0');
	dataLCD(':');

	// Display minutes on LCD
	dataLCD((min / 10) + '0');
	dataLCD((min % 10) + '0');
	dataLCD(':');

	// Display seconds on LCD
	dataLCD((sec / 10) + '0');
	dataLCD((sec % 10) + '0');

	// Move cursor to display day of week
	cmdLCD(0x8a);

	// Read day of week from RTC
	readRTCdow(&dow);

	// Display corresponding weekday string
	writeString(week[dow]);

	// Move cursor to second line
	cmdLCD(0xc0);

	// Read current RTC date
	readRTCdate(&year, &mon, &dom);

	// Display day of month
	dataLCD((dom / 10) + '0');
	dataLCD((dom % 10) + '0');
	dataLCD('/');

	// Display month
	dataLCD((mon / 10) + '0');
	dataLCD((mon % 10) + '0');
	dataLCD('/');

	// Display year
	writeint(year);
}

//-----------------------------------------------------------
// Function: minpassed
// Purpose : Check whether a new minute has elapsed
//           since the last function call.
//-----------------------------------------------------------
int minpassed(void)
{
	int h, m, s;                // Variables to store RTC time

	static int mpassed = -1;    // Stores previously recorded minute

	// Read current RTC time
	readRTCtime(&h, &m, &s);

	// Compare current minute with previous minute
	if (mpassed == m)
		return 0;                // Same minute, return false
	else
	{
		mpassed = m;             // Update stored minute
		return 1;                // New minute detected
	}
}

