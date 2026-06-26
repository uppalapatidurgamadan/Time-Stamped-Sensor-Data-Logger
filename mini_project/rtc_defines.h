#include<lpc21xx.h>
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define PRE_INT ((PCLK/32768)-1)
#define PRE_FRAC (PCLK-((PRE_INT+1)*32768))
#define CLK_EN 0
#define CLK_RST 1
#define CLK_SRC 4



//#define _LPC2148
void setRTCtime(int ,int,int );
void setRTCdate(int ,int ,int);
void initRTC(void);
void readRTCtime(int *,int *,int *);
void readRTCdate(int *,int *,int *);
void readRTCdow(int *);
void setRTCdow(int );

