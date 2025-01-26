/*
 *	General.cpp
 *	CPP File for the functions defined in General.h
 *  Created on: Oct 9, 2018
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
		std::cout << txt << "\n";

		// Print each option
		for (int i = 0; i < opts.size(); i++) {
			std::cout << std::to_string(i + 1) << ". " << opts[i] << "\n";
		}

		// Denote the input line
		std::cout << "\n> ";

		// Take the user's input
		std::cin >> userInput;

		// Ensure the input is valid
		if (userInput.find_first_not_of("0123456789") == std::string::npos)
			validIn = stoi(userInput) <= opts.size() && stoi(userInput) >= 1;

		// If valid, save, if not, repeat
		if (!validIn)
			std::cout << "Input is invalid, please try again.\n";

		std::cout << "\n";
	}

	return stoi(userInput);
}

std::vector<std::string> support::splitByDelim(std::string input) {
	// Prepare the standard delim list
	std::vector<std::string> delimList = { ": ", " - ", " < "," > ", "> " , " <" };

	// Pass and return
	return splitByDelim(input, delimList);
}

std::vector<std::string> support::splitByDelim(std::string input, std::vector<std::string> delimList) {
	// Variables for delims found position and tracking progress
	std::vector<int> delimPos;
	bool isRunning = true;

	// Variable for the return
	std::vector<std::string> splitLine;

	// Split until a delim cannot be found
	while (isRunning) {
		// Find each delim in the string
		for (std::string delim : delimList) {
			// Find the delim
			int relPos = input.find(delim);

			// If the delim doesn't appear, set it to the array's size
			if (relPos == -1)
				delimPos.push_back(input.size());
			else
				delimPos.push_back(input.find(delim));
		}

		// Determine the first delim to appear
		auto minEleIter = std::min_element(delimPos.begin(), delimPos.end());
		int minEle = std::distance(delimPos.begin(), minEleIter);

		// If no delim's appeared, break
		if (delimPos[minEle] == input.size()) {
			isRunning = false;
			break;
		}

		// Split the line and continue with the remainder
		splitLine.push_back(input.substr(0, input.find(delimList[minEle])));
		input = input.substr(input.find(delimList[minEle]) + delimList[minEle].size());

		// Clear the delim positions
		delimPos.clear();
	}

	// Add the rest of the line to the return
	splitLine.push_back(input);

	return splitLine;
}

int simpleFind::find(const std::vector<std::string>& arr, const std::string& val) {
	// Try to find val
	auto loc = find(arr.begin(), arr.end(), val);

	// If it's in the array return it
	if (loc != arr.end()) {
		return std::distance(arr.begin(), loc);
	} 

	// Otherwise return -1
	return -1;
}

int simpleFind::find(const std::string& val, const std::vector<std::string>& arr) {
	return find(arr, val); 
}