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

  >> Version 1 - 04-IV-2024
	- chronoStart and chronoEnd functions added	

**********************************************************************/

#pragma once
#include <chrono> // chronometers functions

class AddOns
{
public:
	// chronometers functions
	static void chronoStart();
	static void chronoEnd();

	// chronometers variables
	static std::chrono::time_point<std::chrono::steady_clock> time_start;
};

