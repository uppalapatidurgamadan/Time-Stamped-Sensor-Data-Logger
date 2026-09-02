/*-------------------------------------------------------------------
File    : adc.h
Purpose : Header file containing function prototypes
          for ADC initialization and ADC data reading.
-------------------------------------------------------------------*/

//-----------------------------------------------------------
// Function: init_adc
// Purpose : Initialize ADC for the specified channel
//-----------------------------------------------------------
void init_adc(int);

//-----------------------------------------------------------
// Function: read_adc
// Purpose : Read ADC value from specified channel and
//           return digital and analog values
//-----------------------------------------------------------
void read_adc(int, int *, float *);

