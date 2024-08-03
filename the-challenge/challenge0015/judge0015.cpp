//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Copyright <<< nyder2000@yahoo.es >>>
//III-2001
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <iostream>
#include <string>
using std::cout;
using std::cin;

#include <iomanip>

#define leap_year(bs)    (!(bs%4)&&(bs%100)||!(bs%400))

int main()
{
	int year, month, day, dw, monthd;

	// Variable containing the months of the year for the calendar.
	std::string monthc[12] = {	"January", "February", "March",
								"April", "May", "June", "July",
								"August", "September", "October", "November",
								"December" };

	// Date Entry
	cout << "\nday= ";
	cin >> day;
	cout << "\nmonth= "; 
	cin >> month;
	cout << "\nyear= ";
	cin >> year;

	// Calculation of the day of the week for the entered date
	// Monday = 0 ... Sunday = 6
	dw = (((1461 * ((year + 4800) + ((month - 14) / 12))) >> 2)			
		+ ((367 * (month - 2 - 12 * ((month - 14) / 12))) / 12)			
		- (3 * (((year + 4800) + ((month - 14) / 12) + 100) / 100) >> 2)
		+ day - 32075L) % 7;				

	// Calculation of the number of days in the month...
	switch (month)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:
	case 12:monthd = 31; break;
	case 4:case 6:case 9:case 11:monthd = 30; break;
	case 2:monthd = 28; if (leap_year(year)) monthd = 29; break;
	}

	cout << "\n\n\t" << monthc[month - 1]; // Printing the Title of the month.
	cout << "\n Mo Tu We Th Fr Sa Su\n";	 // Headings of the days.

	//-----------------------------------------------------
	// Solution:
	//-----------------------------------------------------
	int semana[6][7] = { 0 };	// Array to contain the calendar of the month.
	int i, j, *p;				// Pointer that will handle the calendar array of the month.

	dw = dw - (day % 7 - 1);	// Key point of day 1 location
	if (dw < 0)dw += 7;			// Correction, if necessary ;-)

	p = &semana[0][0]; // Location of the pointer over the month array.

	for (i = 0; i < monthd; i++)	// Location of days in the array
		*(p + dw + i) = i + 1;		// via pointer to first element.

	for (j = 0; j < 6; j++) // Print cycle
	{
		for (i = 0; i < 7; i++)
		{
			if (semana[j][i] == 0)
			{
				cout << "   "; // If it is not a day of the month.
			}
			else
			{
				cout << std::setfill(' ') << std::setw(3) << semana[j][i];	// If it is a day of the month.
				semana[j][i] = 0;
			}
		}
		cout << "\n";
	}	
	//-----------------------------------------------------

	return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//nyder2000@yahoo.es