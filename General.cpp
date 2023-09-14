/*
 * general.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: Adrian
 */

#include "General.h"

int support::prompt(std::string txt, std::vector<std::string> opts) {
	// Prepare Variables
	std::string userInput;

	if (opts.size() == 0)
		return -1;

	// Loop until a valid selection is made
	bool validIn = false;
	while (!validIn) {
		// Print the opening text
		std::cout << txt << "\nPossible Options:\n";

		// Print each option
		for (int i = 0; i < opts.size(); i++) {
			std::cout << std::to_string(i + 1) << ". " << opts[i] << "\n";
		}

		// Take the user's input
		std::cin >> userInput;

		// Ensure the input is valid
		if (userInput.find_first_not_of("0123456789") == std::string::npos)
			validIn = stoi(userInput) <= opts.size() && stoi(userInput) >= 1;

		// If valid, save, if not, repeat
		if (!validIn)
			std::cout << "Invalid Input\n";

		std::cout << "\n";
	}

	return stoi(userInput);
}
