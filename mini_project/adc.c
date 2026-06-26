/*-------------------------------------------------------------------
File    : adc.c
Purpose : Initialize ADC module of LPC21xx and read analog values
          from selected ADC channel. Converts raw ADC data into
          corresponding analog voltage.
-------------------------------------------------------------------*/

#include <lpc21xx.h>        // LPC21xx register definitions
#include "defines_adc.h"   // ADC-related macro definitions
#include "delay.h"         // Delay functions

//-----------------------------------------------------------
// Function: init_adc
// Arguments:
//   chno -> ADC channel number to be configured (AIN0–AIN3)
// Purpose :
//   - Configures the selected ADC pin as analog input
//   - Powers up the ADC
//   - Sets ADC clock divider
//-----------------------------------------------------------
void init_adc(int chno)
{
	// Clear the function bits for the selected pin
	// Each pin uses 2 bits in PINSEL1
	PINSEL1 &= ~(3 << ((chno - 16) * 2));

	// Select ADC function for the chosen pin
	PINSEL1 |= (1 << ((chno - 16) * 2));

	// Enable ADC (PDN bit) and set ADC clock divider
	ADCR |= (1 << PDN) | (CLKDIV << CLKDIV_BITS);
}

//-----------------------------------------------------------
// Function: read_adc
// Arguments:
//   chno   -> ADC channel number to read
//   dig    -> Pointer to store raw digital ADC value
//   analog -> Pointer to store calculated analog voltage
// Purpose :
//   - Starts ADC conversion on selected channel
//   - Waits until conversion is complete
//   - Reads digital value
//   - Converts digital value into analog voltage
//-----------------------------------------------------------
void read_adc(int chno, int *dig, float *analog)
{
	// Clear previous channel selection bits
	ADCR &= ~(0xFF);

	// Select required ADC channel
	ADCR |= (1 << chno);

	// Start ADC conversion
	ADCR |= (1 << START);

	// Small delay for ADC sampling stability
	delay_us(5);

	// Wait until ADC conversion is completed
	while (((ADDR >> DONE) & 1) == 0);

	// Extract 10-bit digital ADC result
	*dig = ((ADDR >> RESULT) & 1023);

	// Convert digital value to analog voltage (0–3.3V)
	*analog = (*dig) * (3.3 / 1023);

	// Stop ADC conversion
	ADCR &= ~(7 << START);
}

