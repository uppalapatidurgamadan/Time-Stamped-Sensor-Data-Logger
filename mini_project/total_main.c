/*-------------------------------------------------------------------
File    : main.c
Purpose : Main application file for Time-Stamped Sensor Data Logger.
          Handles system initialization, normal operation mode,
          and edit/menu mode using switch and keypad.
-------------------------------------------------------------------*/

#include <lpc21xx.h>
#include "total_main.h"
#include "lcdtotal.h"
#include "adc.h"
#include "adc_defines.h"
#include "rtc_defines.h"
#include "keypad_defines.h"
#include "uart.h"

//-----------------------------------------------------------
// Function: main
// Purpose : Entry point of the application
//           Initializes all peripherals and controls
//           switching between normal mode and edit mode
//-----------------------------------------------------------
int main()
{
	/* RTC time and date variables */
	int hour = 16, min = 30, sec = 0;
	int day = 31, mon = 12, year = 25, dow;

	/* Temperature threshold and edit mode flag */
	int thre = 30, edit_flag = 0;

	//-------------------------------------------------------
	// GPIO configuration for switch
	//-------------------------------------------------------
	PINSEL1 = PINSEL1 & (~(3 << 18));   // Configure switch pin as GPIO
	IODIR1  &= ~(1 << SW);              // Set switch pin as input

	//-------------------------------------------------------
	// Peripheral initialization
	//-------------------------------------------------------
	inituart();        // Initialize UART for serial communication
	initLCDdat();      // Initialize LCD
	initRTC();         // Initialize RTC
	init_adc(AIN1);    // Initialize ADC for LM35 temperature sensor
	KeyPdInit();       // Initialize keypad

	//-------------------------------------------------------
	// Set initial RTC time and date
	//-------------------------------------------------------
	setRTCtime(hour, min, sec);
	setRTCdate(day, mon, year);
	setRTCdow(0);

	//-------------------------------------------------------
	// Main application loop
	//-------------------------------------------------------
	while (1)
	{
		// Check if edit switch is pressed
		if (((IOPIN1 >> SW) & 1) == 0)
		{
			edit_flag = 1;   // Set edit mode flag
		}

		//---------------------------------------------------
		// Edit mode
		//---------------------------------------------------
		if (edit_flag == 1)
		{
			// Call menu to edit RTC parameters and threshold
			menu(&thre, &hour, &min, &sec, &day, &mon, &year, &dow);

			// Wait for switch release
			while (((IOPIN1 >> SW) & 1) == 0);

			cmdLCD(0x01);    // Clear LCD after exiting menu
			edit_flag = 0;   // Clear edit mode flag
		}
		//---------------------------------------------------
		// Normal operation mode
		//---------------------------------------------------
		else
		{
			rtc();            // Display RTC time and date on LCD
			lm35();           // Display temperature on LCD
			min_alert();      // Log temperature once per minute
			alert_temp(thre); // Trigger alert if threshold is exceeded
		}
	}
}

