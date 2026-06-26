/*-------------------------------------------------------------------
File    : delay.c
Purpose : This file contains software delay functions for
          generating delays in microseconds, milliseconds,
          and seconds using simple loop-based timing.
-------------------------------------------------------------------*/

//-----------------------------------------------------------
// Function: delay_us
// Purpose : Generate delay in microseconds
//-----------------------------------------------------------
void delay_us(unsigned int tdly)
{
	// Multiply delay count to match approximate microsecond timing
	tdly *= 12;

	// Loop until delay count reaches zero
	while (tdly--);
}

//-----------------------------------------------------------
// Function: delay_ms
// Purpose : Generate delay in milliseconds
//-----------------------------------------------------------
void delay_ms(unsigned int tdly)
{
	// Multiply delay count to match approximate millisecond timing
	tdly *= 12000;

	// Loop until delay count reaches zero
	while (tdly--);
}

//-----------------------------------------------------------
// Function: delay_s
// Purpose : Generate delay in seconds
//-----------------------------------------------------------
void delay_s(unsigned int tdly)
{
	// Multiply delay count to match approximate second timing
	tdly *= 12000000;

	// Loop until delay count reaches zero
	while (tdly--);
}

