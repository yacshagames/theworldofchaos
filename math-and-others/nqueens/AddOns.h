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

