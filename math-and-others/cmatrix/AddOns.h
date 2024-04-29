#pragma once
/*********************************************************************
:: ADDONS ::

Common functions used in console mode programs

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

HISTORY...

  >> Version 2 - 28-IV-2024
	- pause, pauseAndExit and pauseYesOrNot functions added	

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

