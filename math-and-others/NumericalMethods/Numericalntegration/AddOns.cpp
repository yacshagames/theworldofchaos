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

	textcolor(LIGHTGRAY);
	std::cout << "Press any key to show solutions..." << std::endl;
	cgetch();
}