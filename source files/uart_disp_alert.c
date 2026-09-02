/*-------------------------------------------------------------------
File    : alert_uart.c
Purpose : This file contains functions related to temperature
          monitoring, UART logging, and alert indication using LED.
-------------------------------------------------------------------*/

#include <lpc21xx.h>          // LPC21xx register definitions
#include "uart.h"             // UART function declarations
#include "delay.h"            // Delay routines
#include "total_main.h"       // Project-wide function prototypes
#include "rtc_defines.h"      // RTC related definitions
#include "adc.h"              // ADC function declarations

//-----------------------------------------------------------
// Macro definition for LED pin used as alert indicator
//-----------------------------------------------------------
#define LED 25

//-----------------------------------------------------------
// Function: min_alert
// Purpose : This function reads temperature from ADC and
//           sends temperature information to UART once
//           every minute.
//-----------------------------------------------------------
void min_alert(void)
{
	int dval;                  // Variable to store digital ADC value
	float aval;                // Variable to store analog voltage

	PINSEL1 &= ~(3 << 18);     // Configure LED pin as GPIO
	IODIR0  |= (1 << LED);     // Set LED pin direction as output

	read_adc(1, &dval, &aval); // Read ADC channel 1 value
	aval = aval * 100;         // Convert voltage to temperature

	if (minpassed())           // Check if one minute has passed
	{
		uartTxstring("[INFO]"); // Send info tag on UART
		disp_uart(aval);        // Display temperature with timestamp
		uartTxstring("\r\n");   // New line for UART formatting
	}
}

//-----------------------------------------------------------
// Function: alert_temp
// Purpose : This function compares temperature with
//           user-defined threshold and generates alert
//           if temperature exceeds threshold.
//-----------------------------------------------------------
void alert_temp(int temp)
{
	int dval;                  // Variable to store digital ADC value
	float aval;                // Variable to store analog voltage

	read_adc(1, &dval, &aval); // Read ADC channel 1 value
	aval = aval * 100;         // Convert voltage to temperature

	if (aval >= temp)          // Compare temperature with threshold
	{
		uartTxstring("[ALERT]");// Send alert tag on UART
		disp_uart(aval);        // Display temperature with timestamp
		Txuart('-');             // Separator character
		uartTxstring("OVER TEMP!"); // Alert message
		uartTxstring("\r\n");   // New line for UART formatting

		IOSET0 = 1 << LED;      // Turn ON LED to indicate alert
	}
	else
	{
		IOCLR0 = 1 << LED;      // Turn OFF LED if temperature is normal
	}
}

//-----------------------------------------------------------
// Function: disp_uart
// Purpose : This function displays temperature along with
//           current time and date on UART.
//-----------------------------------------------------------
void disp_uart(float aval)
{
	int hour, min, sec;        // Variables to store RTC time
	int dom, mon, year;        // Variables to store RTC date

	readRTCtime(&hour, &min, &sec); // Read RTC time
	readRTCdate(&year, &mon, &dom); // Read RTC date

	uartTxstring("Temp:");     // Send temperature label
	Txfloat(aval);             // Transmit temperature value
	uartTxstring("C @ ");      // Unit and separator

	// Transmit hour
	Txuart((hour / 10) + '0');
	Txuart((hour % 10) + '0');
	Txuart(':');

	// Transmit minutes
	Txuart((min / 10) + '0');
	Txuart((min % 10) + '0');
	Txuart(':');

	// Transmit seconds
	Txuart((sec / 10) + '0');
	Txuart((sec % 10) + '0');
	Txuart(' ');

	// Transmit date (day)
	Txuart((dom / 10) + '0');
	Txuart((dom % 10) + '0');
	Txuart('/');

	// Transmit month
	Txuart((mon / 10) + '0');
	Txuart((mon % 10) + '0');
	Txuart('/');

	// Transmit year
	Txuart((year / 10) + '0');
	Txuart((year % 10) + '0');
}

