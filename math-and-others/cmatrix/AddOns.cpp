#include "AddOns.h"
#include "conio.h"
#include <iostream>


std::chrono::time_point < std::chrono::steady_clock> AddOns::time_start = std::chrono::steady_clock::now();

void AddOns::chronoStart() {

	time_start = std::chrono::steady_clock::now();
}

void AddOns::chronoEnd() {

	const auto time_end{ std::chrono::steady_clock::now() };
	const std::chrono::duration<double> elapsed_seconds{ time_end - time_start };
	std::cout << "\nElapsed time: " << elapsed_seconds.count() << " seconds" << std::endl;
}

char AddOns::pause()
{
	textcolor(LIGHTGRAY);
	std::cout << "Press any key to continue..." << std::endl;
	return cgetch();
}

bool AddOns::pauseAndExit()
{
	textcolor(LIGHTGRAY);
	std::cout << "Press any key to continue or SPACE key to return to menu..." << std::endl;
	return cgetch();

	if (cgetch() == 32) // SPACE key = 32
		return true;

	return false;
}

bool AddOns::pauseYesOrNot(std::string message)
{
	textcolor(WHITE);
	std::cout << message;
	return toupper(cgetch()) == 'Y';
}

