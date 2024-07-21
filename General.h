/*
 * General.h
 *
 *  Created on: Oct 9, 2018
 *      Author: Adrian
 */

#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace support {
	// Prompt for user input from a list of options
	int prompt(std::string txt, std::vector<std::string> opts);
}

namespace simpleFind {
	int find(const std::vector<std::string>& arr, const std::string& val);
}