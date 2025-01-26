/*
 *	General.h
 *	Contains simple functions that could easily be repurposed in the future.
 *  Created on: Oct 9, 2018
 */

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

namespace support {
	// Prompt for user input from a list of options
	int prompt(std::string txt, std::vector<std::string> opts);

	// Split a string based on a generic list of delims
	std::vector<std::string> splitByDelim(std::string input);
	// Split a string based on a custom list of delims
	std::vector<std::string> splitByDelim(std::string input, std::vector<std::string> delimList);
}

namespace simpleFind {
	int find(const std::vector<std::string>& arr, const std::string& val);
	int find(const std::string& val, const std::vector<std::string>& arr);
}