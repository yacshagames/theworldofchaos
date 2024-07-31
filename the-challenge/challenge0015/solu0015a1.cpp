/********************************************
SOLUTION #1 TO CHALLENGE0015:
   by:
   Jose Luis De la Cruz Lazaro - 29/VII/2024
   contact@theworldofchaos.com
   https://www.theworldofchaos.com
********************************************/
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
	int i, ini_pos, calendar_day = 0;
	
	// get the position of the current day in the calendar
	ini_pos = ((day / 7)+1) * 7 + dw;	
	
	// get the position of the first day of the month in the calendar
	int fdm = (ini_pos + 1 - day) % 7;

	// Print the calculated calendar
	cout << ' ';

	for (i = 0; calendar_day < monthd; i++) {
		
		calendar_day = i - fdm + 1;
		
		// A line break is inserted every week
		if (i > 0 && i % 7 == 0)
			cout << std::endl << ' ';
		
		// The calendar days are inserted with a format
		// of up to 2 spaces in front
		if ( calendar_day >= 1 )
			cout << std::setfill(' ') << std::setw(2) << calendar_day << ' ';
		else
			cout << "   ";
	}
	
	//-----------------------------------------------------

	return 0;
}