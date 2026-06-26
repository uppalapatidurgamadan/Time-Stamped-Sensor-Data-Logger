/*-------------------------------------------------------------------
File    : menu.c
Purpose : Handles user interaction using switch and keypad.
          Provides menu navigation for:
          1) Editing RTC parameters
          2) Setting temperature threshold
          3) Exiting menu mode
-------------------------------------------------------------------*/

#include <lpc21xx.h>          // LPC21xx microcontroller register definitions
#include "lcdtotal.h"         // LCD control and display functions
#include "keypad_defines.h"   // Keypad scanning and key value functions
#include "total_main.h"       // Global project function prototypes
#include "uart.h"             // UART transmit functions for logging
#include "rtc_defines.h"      // RTC register access and control functions
#include "delay.h"            // Delay routines (ms level)

/*-------------------------------------------------------------------
Function : switch_stat
Purpose  : Reads the status of the external switch connected to Port1.
Returns  : 1 -> switch pressed (logic LOW)
           0 -> switch not pressed (logic HIGH)
-------------------------------------------------------------------*/
/*char switch_stat(void)
{
	// Read the switch pin from IOPIN1 register
	// Right shift by SW position and mask LSB
	if (((IOPIN1 >> SW) & 1) == 0)
	{
		// Switch line is LOW, meaning switch is pressed
		return 1;
	}
	else
	{
		// Switch line is HIGH, meaning switch is released
		return 0;
	}
}*/

/*-------------------------------------------------------------------
Function : menu
Purpose  : Displays menu on LCD and allows user to:
           - Edit RTC time/date values
           - Set temperature threshold
           - Exit menu mode
Arguments:
 temp  -> pointer to temperature threshold variable
 hour  -> pointer to hour variable
 min   -> pointer to minute variable
 sec   -> pointer to second variable
 day   -> pointer to date variable
 mon   -> pointer to month variable
 year  -> pointer to year variable
 dow   -> pointer to day-of-week variable
-------------------------------------------------------------------*/
void menu(int *temp, int *hour, int *min, int *sec,
          int *day, int *mon, int *year, int *dow)
{
	// ch     : stores main menu choice
	// tmenu  : stores RTC sub-menu choice
	int ch, tmenu,dtemp,itemp;

	// Stay inside menu until EXIT option is selected
	uartTxstring("****editing mode activated****\r\n");
	while (1)
	{
		// Clear LCD display
		cmdLCD(0x01);

		// Display main menu first line
		cmdLCD(0x80);
		writeString("1.ERI  2.TEMP");

		// Display main menu second line
		cmdLCD(0xc0);
		writeString("3.DTEMP  4.EXIT");

		// Wait until any key is pressed
		while (ColStat());

		// Read keypad value
		ch = KeyVal();

		/*-----------------------------------------------------------
		  OPTION 1: RTC EDITING MODE
		-----------------------------------------------------------*/
		if (ch == 1)
		{
			// Inform through UART that RTC edit mode has started
			uartTxstring("****time editing mode activated****\r\n");

			// Wait until key is released
			while (!ColStat());

			// Stay in RTC edit submenu
			while (1)
			{
				// Clear LCD
				cmdLCD(0x01);

				// Display RTC edit options (line 1)
				cmdLCD(0x80);
				writeString("1.H 2.M 3.S 4.D");

				// Display RTC edit options (line 2)
				cmdLCD(0xc0);
				writeString("5.M6.Y 7.DAY 8.E");

				// Wait for submenu key press
				while (ColStat());

				// Read submenu choice
				tmenu = KeyVal();

				/*------------------ EDIT HOUR ------------------*/
				if (tmenu == 1)
				{
					// Wait for key release
					while (!ColStat());

					// Prompt user
					cmdLCD(0x01);
					cmdLCD(0x80);
					writeString("enter hour");

					// Read hour from keypad
					*hour = ip_keypad();

					// Validate hour range
					if (*hour > 23)
					{
						// Display error message
						cmdLCD(0x01);
						cmdLCD(0x80);
						writeString("out of range");
						cmdLCD(0xc0);
						writeString("range is (0-23)");

						// Small delay to allow user to read message
						delay_ms(300);
					}
					else if((*hour)!=-1)
					{
						// Update RTC hour register
						setRTCtime(*hour, *min, *sec);
					}
				}

				/*------------------ EDIT MINUTE ------------------*/
				else if (tmenu == 2)
				{
					while (!ColStat());

					cmdLCD(0x01);
					cmdLCD(0x80);
					writeString("enter min");

					*min = ip_keypad();

					if (*min > 59)
					{
						cmdLCD(0x01);
						cmdLCD(0x80);
						writeString("out of range");
						cmdLCD(0xc0);
						writeString("range is (0-59)");
						delay_ms(300);
					}
					else if((*min)!=-1)
					{
						setRTCtime(*hour, *min, *sec);
					}
				}

				/*------------------ EDIT SECOND ------------------*/
				else if (tmenu == 3)
				{
					while (!ColStat());

					cmdLCD(0x01);
					cmdLCD(0x80);
					writeString("enter seconds");

					*sec = ip_keypad();

					if (*sec > 59)
					{
						cmdLCD(0x01);
						cmdLCD(0x80);
						writeString("out of range");
						cmdLCD(0xc0);
						writeString("range is (0-59)");
						delay_ms(300);
					}
					else if((*sec)!=-1)
					{
						setRTCtime(*hour, *min, *sec);
					}
				}

				/*------------------ EDIT DAY ------------------*/
				else if (tmenu == 4)
				{
					while (!ColStat());

					cmdLCD(0x01);
					cmdLCD(0x80);
					writeString("enter day");

					*day = ip_keypad();

					if (*day > 31)
					{
						cmdLCD(0x01);
						cmdLCD(0x80);
						writeString("out of range");
						cmdLCD(0xc0);
						writeString("range is (1-31)");
						delay_ms(300);
					}
					else if((*day)!=-1)
					{
						setRTCdate(*day, *mon, *year);
					}
				}

				/*------------------ EDIT MONTH ------------------*/
				else if (tmenu == 5)
				{
					while (!ColStat());

					cmdLCD(0x01);
					cmdLCD(0x80);
					writeString("enter month");

					*mon = ip_keypad();

					if (*mon > 12)
					{
						cmdLCD(0x01);
						cmdLCD(0x80);
						writeString("out of range");
						cmdLCD(0xc0);
						writeString("range is (1-12)");
						delay_ms(300);
					}
					else if((*mon)!=-1)
					{
						setRTCdate(*day, *mon, *year);
					}
				}

				/*------------------ EDIT YEAR ------------------*/
				else if (tmenu == 6)
				{
					while (!ColStat());

					cmdLCD(0x01);
					cmdLCD(0x80);
					writeString("enter year");

					*year = ip_keypad();

					// Year is stored directly (no range enforced)
					setRTCdate(*day, *mon, *year);
				}

				/*------------------ EDIT DAY OF WEEK ------------------*/
				else if (tmenu == 7)
				{
					while (!ColStat());

					cmdLCD(0x01);
					cmdLCD(0x80);
					writeString("enter week(0-6)");

					*dow = ip_keypad();

					if (*dow > 6)
					{
						cmdLCD(0x01);
						cmdLCD(0x80);
						writeString("out of range");
						cmdLCD(0xc0);
						writeString("range is (0-6)");
						delay_ms(300);
					}
					else if((*dow)!=-1)
					{
						setRTCdow(*dow);
					}
				}

				/*------------------ EXIT RTC EDIT MODE ------------------*/
				if (tmenu == 8)
				{
					uartTxstring("****time editing mode ended****\r\n");
					break;
				}
			}
		}

		/*-----------------------------------------------------------
		  OPTION 2: TEMPERATURE THRESHOLD SETTING
		-----------------------------------------------------------*/
		else if (ch == 2)
		{
			while (!ColStat());

			cmdLCD(0x01);
			cmdLCD(0x80);
			writeString("enter temp");

			// Read temperature threshold from keypad
			itemp = ip_keypad();
			if(itemp==-1)
				continue;
			else if(itemp>150)
			{
				cmdLCD(0x01);
				cmdLCD(0x80);
				writeString("out of range");
				cmdLCD(0xc0);
				writeString("range is (0-150)");
				delay_ms(300);
			}
			else
				*temp=itemp;
		}

		/*-----------------------------------------------------------
		  OPTION 3: EXIT MENU
		-----------------------------------------------------------*/
		else if (ch == 3)
		{
			// Wait for key release before exiting
			while (!ColStat());
			cmdLCD(0x01);
			while(1)
			{
				while(!ColStat());
				cmdLCD(0x80);
				writeString("Threshold:");
				writeint((*temp));
				//degreechar();
				dataLCD(0);
				dataLCD('C');
				cmdLCD(0xc0);
				writeString("14.EXIT");
				while(ColStat());
				dtemp=KeyVal();
				while(!ColStat());
				if(dtemp==14)
					break;
			}
		}
		else if (ch == 4)
		{
			// Wait for key release before exitingu
			while (!ColStat());
			uartTxstring("****editing mode ended****\r\n");
			break;
		}
	}
}

/*-------------------------------------------------------------------
Function : ip_keypad
Purpose  : Reads a multi-digit number from keypad.
           Digits are accumulated until termination key (14) is pressed.
Returns  : Final integer value entered by user
-------------------------------------------------------------------*/
int ip_keypad(void)
{
	int val = 0;   // Stores accumulated numeric value
	int stop;      // Stores key value from keypad
	int typed=0;

	// Move cursor to second LCD line
	cmdLCD(0xc0);

	while (1)
	{
		// Wait for key press
		while (ColStat());

		// Read key value
		stop = KeyVal();

		// Wait for key release
		while (!ColStat());

		// Termination key detected
		if (stop == 14)
			break;
		if(stop==15)
		{
			val=val/10;
			cmdLCD(0xc0);
			writeString("                ");
			cmdLCD(0xc0);
			writeint(val);
			if(typed>0)
				typed--;
			continue;
		}
		// Append digit to number
		val = val * 10 + stop;

		// Clear previous display
		cmdLCD(0xc0);
		writeString("                ");

		// Display updated number
		cmdLCD(0xc0);
		writeint(val);
		typed++;
	}

	// Return final value entered
	if(typed==0)
		return -1;
	else
		return val;
}

