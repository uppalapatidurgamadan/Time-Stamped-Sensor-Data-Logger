/*-------------------------------------------------------------------
File    : keypad.c
Purpose : Interface a 4x4 matrix keypad with LPC21xx.
          Detects key press by scanning rows and columns and
          returns corresponding key value using LUT.
-------------------------------------------------------------------*/

#include <LPC21xx.h>          // LPC21xx register definitions
#include "keypad_defines.h"  // Keypad pin definitions and typedefs

//-----------------------------------------------------------
// Look-Up Table (LUT)
// Maps row and column number to key value
// Row 0 -> {0,1,2,3}
// Row 1 -> {4,5,6,7}
// Row 2 -> {8,9,10,11}
// Row 3 -> {12,13,14,15}
//-----------------------------------------------------------
#ifdef HW
u8 LUT[][4] = {
	              {0, 1, 2, 3},
	              {4, 5, 6, 7},
	              {8, 9, 10, 11},
	              {12, 13, 14, 15}
              };
#else
u8 LUT[][4] = {
	              {7, 8, 9, 10},
	              {4, 5, 6, 11},
	              {1, 2, 3, 12},
	              {13, 0, 14, 15}
              };
#endif
//-----------------------------------------------------------
// Function: KeyPdInit
// Purpose :
//   - Configure keypad row pins as output
//   - Initialize all row lines to logic 0
//-----------------------------------------------------------
void KeyPdInit(void)
{
	// Configure row pins (R0–R3) as output
	IODIR1 |= ((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));

	// Clear all row pins initially (drive them low)
	IOCLR1 = ((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));
}

//-----------------------------------------------------------
// Function: ColStat
// Return  : 1 -> No key pressed
//           0 -> Any key pressed
// Purpose :
//   - Reads column lines
//   - Checks if all columns are HIGH (idle state)
//-----------------------------------------------------------
u8 ColStat(void)
{
	// Read column bits C0–C3 (P1.20–P1.23)
	// If all are HIGH (0x0F), no key is pressed
	if ((((IOPIN1 >> 20) & 0x0F) == 0x0F))
		return 1;
	else
		return 0;
}

//-----------------------------------------------------------
// Function: KeyVal
// Return  : Key value (0–15) based on row & column
// Purpose :
//   - Scan keypad rows one by one
//   - Detect active row
//   - Detect active column
//   - Return corresponding value from LUT
//-----------------------------------------------------------
u8 KeyVal(void)
{
	char row_val = 0;   // Stores detected row number
	char col_val = 0;   // Stores detected column number

	//--------------- Scan Row 0 ----------------
	IOCLR1 = (1 << R0);                            // Drive R0 LOW
	IOSET1 = ((1 << R1) | (1 << R2) | (1 << R3));  // Drive other rows HIGH
	if ((((IOPIN1 >> 20) & 0x0F) != 0x0F))         // Check column status
	{
		row_val = 0;
		goto colcheck;
	}

	//--------------- Scan Row 1 ----------------
	IOCLR1 = (1 << R1);
	IOSET1 = ((1 << R0) | (1 << R2) | (1 << R3));
	if ((((IOPIN1 >> 20) & 0x0F) != 0x0F))
	{
		row_val = 1;
		goto colcheck;
	}

	//--------------- Scan Row 2 ----------------
	IOCLR1 = (1 << R2);
	IOSET1 = ((1 << R0) | (1 << R1) | (1 << R3));
	if ((((IOPIN1 >> 20) & 0x0F) != 0x0F))
	{
		row_val = 2;
		goto colcheck;
	}

	//--------------- Scan Row 3 ----------------
	IOCLR1 = (1 << R3);
	IOSET1 = ((1 << R0) | (1 << R1) | (1 << R2));
	if ((((IOPIN1 >> 20) & 0x0F) != 0x0F))
		row_val = 3;

	//-------------------------------------------------------
	// Column detection section
	//-------------------------------------------------------
	colcheck:
	if (((IOPIN1 >> C0) & 1) == 0)
		col_val = 0;
	else if (((IOPIN1 >> C1) & 1) == 0)
		col_val = 1;
	else if (((IOPIN1 >> C2) & 1) == 0)
		col_val = 2;
	else
		col_val = 3;

	// Reset all row pins to LOW after scan
	IOCLR1 = ((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));

	// Return key value using LUT
	return (LUT[row_val][col_val]);
}

