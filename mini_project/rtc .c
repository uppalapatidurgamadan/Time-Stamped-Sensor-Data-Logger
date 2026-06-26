/*-------------------------------------------------------------------
File    : rtc.c
Purpose : This file contains functions to initialize the RTC,
          set and read time, date, and day of week using
          LPC21xx RTC registers.
-------------------------------------------------------------------*/

#include <lpc21xx.h>          // LPC21xx register definitions
#include "rtc_defines.h"      // RTC-related macros and definitions

//-----------------------------------------------------------
// Function: initRTC
// Purpose : Initialize the Real Time Clock (RTC)
//           by configuring prescalers and enabling RTC.
//-----------------------------------------------------------
void initRTC(void)
{
	// Reset RTC counter and prescaler
	CCR = (1 << CLK_RST);

	#ifdef _LPC2148
	// Enable RTC and select external clock source (for LPC2148)
	CCR = (1 << CLK_EN) | (1 << CLK_SRC);
	#else
	// Load integer prescaler value
	PREINT = PRE_INT;

	// Load fractional prescaler value
	PREFRAC = PRE_FRAC;

	// Enable RTC
	CCR = (1 << CLK_EN);
	#endif
}

//-----------------------------------------------------------
// Function: setRTCtime
// Purpose : Set hour, minute, and second values
//           in RTC time registers.
//-----------------------------------------------------------
void setRTCtime(int hour, int min, int sec)
{
	HOUR = hour;   // Set hour register
	MIN  = min;    // Set minute register
	SEC  = sec;    // Set second register
}

//-----------------------------------------------------------
// Function: setRTCdate
// Purpose : Set date values (day, month, year)
//           in RTC date registers.
//-----------------------------------------------------------
void setRTCdate(int day, int mon, int year)
{
	DOM   = day;          // Set day of month
	MONTH = mon;          // Set month
	YEAR  = (year % 100); // Store last two digits of year
}

//-----------------------------------------------------------
// Function: readRTCtime
// Purpose : Read current time values from RTC registers.
//-----------------------------------------------------------
void readRTCtime(int *hour, int *min, int *sec)
{
	*hour = HOUR;   // Read hour value
	*min  = MIN;    // Read minute value
	*sec  = SEC;    // Read second value
}

//-----------------------------------------------------------
// Function: readRTCdate
// Purpose : Read current date values from RTC registers.
//-----------------------------------------------------------
void readRTCdate(int *year, int *mon, int *dom)
{
	*year = YEAR;    // Read year value
	*mon  = MONTH;   // Read month value
	*dom  = DOM;     // Read day of month value
}

//-----------------------------------------------------------
// Function: readRTCdow
// Purpose : Read day of week from RTC register.
//-----------------------------------------------------------
void readRTCdow(int *dow)
{
	*dow = DOW;     // Read day of week
}

//-----------------------------------------------------------
// Function: setRTCdow
// Purpose : Set day of week value in RTC register.
//-----------------------------------------------------------
void setRTCdow(int p)
{
	DOW = p;        // Set day of week
}

