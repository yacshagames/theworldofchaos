#pragma once
/*********************************************************************
:: ADDONS ::

Common functions used in console mode programs

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

  >> Version 2 - 28-IV-2024
	- pause, pauseAndExit and pauseYesOrNot functions added	
	- Fixed a bug in the pauseAndExit function in the AddOns library,
	  which prevented it from being executed correctly.

  >> Version 1 - 04-IV-2024
	- chronoStart and chronoEnd functions added	

**********************************************************************/

#include <chrono> // chronometers functions
#include <string>

class AddOns
{
public:
	// chronometers functions
	
	// Start the stopwatch
	static void chronoStart();

	// Ends the stopwatch and shows the elapsed time
	static void chronoEnd();

	// Pauses until a key is pressed
	// Display a message to notify the user
	static char pause();

	// returns true if the user presses the space key, and false if the user presses any other key
	static bool pauseAndExit();

	// returns true if Y key is pressed or false if another key is pressed
	static bool pauseYesOrNot(std::string message);

	// chronometers variables
	static std::chrono::time_point<std::chrono::steady_clock> time_start;
};

