#include<lpc21xx.h>
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define ADCCLK 3000000
#define CLKDIV ((PCLK/ADCCLK)-1)
//adcr
#define CLKDIV_BITS 8
#define PDN 21
#define START 24
#define BURST 16
//addr
#define RESULT 6
#define OVERRUN 30
#define DONE 31
//analog
#define AIN0 27
#define AIN1 28
#define AIN2 29
#define AIN3 30
//default to clear
#define AIN_BIT_START 27
#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3

