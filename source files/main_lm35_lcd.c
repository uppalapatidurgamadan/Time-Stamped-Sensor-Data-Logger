/*-------------------------------------------------------------------
File    : lm35.c
Purpose : This file contains function to read temperature
          from LM35 sensor using ADC and display it on LCD.
-------------------------------------------------------------------*/

#include <lpc21xx.h>          // LPC21xx register definitions
#include "lcdtotal.h"         // LCD function declarations
#include "lm35.h"             // LM35 function prototype
#include "adc.h"              // ADC function declarations
#include "adc_defines.h"      // ADC related definitions

//-----------------------------------------------------------
// Function: lm35
// Purpose : Read temperature from LM35 sensor via ADC,
//           convert it to degree Celsius and display
//           the value on LCD.
//-----------------------------------------------------------
void lm35(void)
{
	int dval, temp;            // dval: digital ADC value, temp: temperature
	float aval;                // aval: analog voltage value

	// Read ADC channel connected to LM35
	read_adc(1, &dval, &aval);

	// Convert analog voltage to temperature value
	temp = aval * 100;

	// Set LCD cursor position for temperature display
	cmdLCD(0XCA);

	// Display temperature label
	writeString("T:");

	// Display temperature value
	dataLCD((temp / 10) + '0');
	dataLCD((temp % 10) + '0');

	// Display degree symbol and 'C'
	degreechar();
}

