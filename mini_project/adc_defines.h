/*-------------------------------------------------------------------
File    : adc_defines.h
Purpose : Contains ADC related function prototypes, clock definitions,
          bit positions, and channel/macros for LPC21xx ADC module.
-------------------------------------------------------------------*/

//-----------------------------------------------------------
// Function prototype for ADC initialization
//-----------------------------------------------------------
void initadc(void);

//-----------------------------------------------------------
// (Commented) Old ADC read function prototype
// Kept for reference / future use
//-----------------------------------------------------------
// void read_adc(int chno, float *eAR, int *adcDVal);

//-----------------------------------------------------------
// Crystal oscillator frequency (12 MHz)
//-----------------------------------------------------------
#define FOSC 12000000

//-----------------------------------------------------------
// CPU clock frequency (CCLK = 5 * FOSC)
//-----------------------------------------------------------
#define CCLK (5*FOSC)

//-----------------------------------------------------------
// Peripheral clock frequency (PCLK = CCLK / 4)
//-----------------------------------------------------------
#define PCLK (CCLK/4)

//-----------------------------------------------------------
// Desired ADC clock frequency (3 MHz as per datasheet)
//-----------------------------------------------------------
#define ADCCLK 3000000

//-----------------------------------------------------------
// ADC clock divider value
// ADC clock = PCLK / (CLKDIV + 1)
//-----------------------------------------------------------
#define CLKDIV ((PCLK/ADCCLK)-1)

//-----------------------------------------------------------
// ADCR register bit positions
//-----------------------------------------------------------

// Bit position where clock divider starts in ADCR
#define CLKDIV_BITS 8

// Power Down bit for ADC (PDN = 1 enables ADC)
#define PDN 21

// Start conversion bit position
#define START 24

//-----------------------------------------------------------
// ADDR register bit positions
//-----------------------------------------------------------

// DONE bit indicates end of ADC conversion
#define DONE 31

// DIGITAL result start bit position in ADDR
#define DIGITAL 6

//-----------------------------------------------------------
// Analog input pin numbers (P0.27 to P0.30)
//-----------------------------------------------------------
#define AIN0 27
#define AIN1 28
#define AIN2 29
#define AIN3 30

//-----------------------------------------------------------
// ADC channel numbers corresponding to AIN pins
//-----------------------------------------------------------
#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3

