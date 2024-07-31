//Solución de Antonio González Cruz
// III-2001

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
	std::string monthc[12] = { "January", "February", "March",
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
	// Solution: ( Failure for the date of November 13, 2013 )
	//-----------------------------------------------------
	int i;
	dw = (dw - ((day % 7) - 1)) % 7;	// We assign ds the 1st day of each
										// month based on the requested day...

	for (i = 0; i < dw; i++)   // Should work for all cases
		cout << "   ";        // create the empty spaces

	for (i = 1; i <= monthd; i++) {
		cout << std::setfill(' ') << std::setw(3) << i ;	// print the day number using 3 spaces
		if (((i + dw) % 7) == 0)
			cout << "\n";	// line break if we reach Sunday
	}

	//-----------------------------------------------------

	return 0;
}

