/*-------------------------------------------------------------------
File    : keypad_defines.h
Purpose : Definitions and function prototypes for interfacing
          a 4x4 matrix keypad with LPC21xx microcontroller.
-------------------------------------------------------------------*/

#include <LPC21xx.h>   // LPC21xx register definitions
#include "types.h"     // User-defined data types (u8, s8, etc.)
//#define HW
//-----------------------------------------------------------
// Keypad Row Pin Definitions (Port 1)
// These pins are configured as OUTPUTS
//-----------------------------------------------------------
#define R0 16    // Row 0 connected to P1.16
#define R1 17    // Row 1 connected to P1.17
#define R2 18    // Row 2 connected to P1.18
#define R3 19    // Row 3 connected to P1.19

//-----------------------------------------------------------
// Keypad Column Pin Definitions (Port 1)
// These pins are configured as INPUTS
//-----------------------------------------------------------
#define C0 20    // Column 0 connected to P1.20
#define C1 21    // Column 1 connected to P1.21
#define C2 22    // Column 2 connected to P1.22
#define C3 23    // Column 3 connected to P1.23

//-----------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------

//-----------------------------------------------------------
// Function: KeyPdInit
// Purpose : Initializes keypad row pins as outputs and
//           sets initial row state.
//-----------------------------------------------------------
void KeyPdInit(void);

//-----------------------------------------------------------
// Function: ColStat
// Return  : 1 -> No key pressed
//           0 -> Key pressed
// Purpose : Checks the status of column lines.
//-----------------------------------------------------------
unsigned char ColStat(void);

//-----------------------------------------------------------
// Function: KeyVal
// Return  : Key value (0–15) based on pressed key
// Purpose : Scans keypad rows and columns and returns
//           the corresponding key value using LUT.
//-----------------------------------------------------------
unsigned char KeyVal(void);

