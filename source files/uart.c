/*-------------------------------------------------------------------
File    : uart.c
Purpose : Configure UART0 of LPC21xx for serial communication.
          Provides functions for transmitting characters,
          strings, integers, and floating-point values.
-------------------------------------------------------------------*/

#include <lpc21xx.h>   // LPC21xx register definitions
#include "uart.h"      // UART function prototypes

//-----------------------------------------------------------
// System clock definitions
//-----------------------------------------------------------
#define FOSC 12000000        // External oscillator frequency = 12 MHz
#define CCLK (5 * FOSC)     // CPU clock frequency = 60 MHz
#define PCLK (CCLK / 4)     // Peripheral clock = 15 MHz

//-----------------------------------------------------------
// Function: inituart
// Purpose :
//   - Configure UART0 pins
//   - Set UART0 for 8-bit data, no parity, 1 stop bit
//   - Set baud rate to 9600 bps (for PCLK = 15 MHz)
//-----------------------------------------------------------
void inituart(void)
{
	// Configure P0.0 (TXD0) and P0.1 (RXD0) for UART function
	PINSEL0 = (PINSEL0 & (~(0xF << 0))) | (5 << 0);

	// Set word length = 8 bits (DLAB = 0 temporarily)
	U0LCR |= 0x03;

	// Enable access to divisor latches (DLAB = 1)
	U0LCR |= (1 << 7);

	// Set baud rate divisor for 9600 bps
	// DLL = 97, DLM = 0 → 9600 baud @ 15 MHz PCLK
	U0DLL = 97;
	U0DLM = 0;

	// Disable divisor latch access (DLAB = 0)
	U0LCR &= ~(1 << 7);
}

//-----------------------------------------------------------
// Function: Txuart
// Argument:
//   val -> Character to transmit
// Purpose :
//   - Transmits a single character through UART0
//   - Waits until transmitter holding register is empty
//-----------------------------------------------------------
void Txuart(unsigned char val)
{
	// Load data into transmit holding register
	U0THR = val;

	// Wait until transmission is complete
	while (((U0LSR >> 5) & 1) == 0);
}

//-----------------------------------------------------------
// Function: Rxuart
// Return  : Received character
// Purpose :
//   - Waits for data to be received on UART0
//   - Returns received character
//-----------------------------------------------------------
unsigned char Rxuart(void)
{
	// Wait until data is received
	while (((U0LSR >> 0) & 1) == 0);

	// Return received byte
	return U0RBR;
}

//-----------------------------------------------------------
// Function: uartTxstring
// Argument:
//   p -> Pointer to null-terminated string
// Purpose :
//   - Transmits a string character-by-character via UART
//-----------------------------------------------------------
void uartTxstring(char *p)
{
	while (*p)
	{
		Txuart(*p);   // Transmit current character
		p++;          // Move to next character
	}
}

//-----------------------------------------------------------
// Function: Txfloat
// Argument:
//   num -> Floating-point number to transmit
// Purpose :
//   - Transmits a floating-point value through UART
//   - Prints integer part and one digit after decimal point
//-----------------------------------------------------------
void Txfloat(float num)
{
	int n, i;

	// Handle negative numbers
	if (num < 0)
	{
		Txuart('-');
		num = -num;
	}

	// Extract integer part
	n = num;
	Txint(n);

	// Print decimal point
	Txuart('.');

	// Print one digit after decimal point
	for (i = 0; i < 1; i++)
	{
		num = num - n;   // Remove integer part
		num = num * 10;  // Shift decimal
		n = num;
		Txuart(n + '0');
	}
}

//-----------------------------------------------------------
// Function: Txint
// Argument:
//   num -> Integer to transmit
// Purpose :
//   - Converts integer to ASCII characters
//   - Handles negative numbers
//   - Preserves leading zeros if any
//-----------------------------------------------------------
void Txint(int num)
{
	int zeros, rev = 0, temp;
	int num_length = 0, rev_length = 0;

	// Special case: number is zero
	if (num == 0)
	{
		Txuart('0');
		return;
	}

	// Handle negative numbers
	if (num < 0)
	{
		Txuart('-');
		num = -num;
	}

	// Reverse number and count digits
	temp = num;
	while (temp)
	{
		num_length++;
		rev = rev * 10 + (temp % 10);
		temp /= 10;
	}

	// Print reversed number
	temp = rev;
	while (temp)
	{
		rev_length++;
		Txuart((temp % 10) + '0');
		temp /= 10;
	}

	// Print missing zeros (if any)
	zeros = num_length - rev_length;
	while (zeros)
	{
		Txuart('0');
		zeros--;
	}
}

