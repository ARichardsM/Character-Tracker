#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

// Abstract Entity Information
class entity {
public:
	std::string name = "None";
	std::string rank = "None";
	std::string member = "None";

	std::vector<std::string> aspects = {};
	std::vector<std::string> relations = {};
};

// Character Information
class character : public entity {
public:
	std::string nickname = "None";

	std::vector<std::string> facts = {};

	character(std::string fileSTEM);

	// Print out the character
	void print();
};

// Unit Information
class unit : public entity {
public:
	unit(std::string fileSTEM);

	// Print out the unit
	void print();
};

namespace interactions {
	// Verify all members in the character and unit list
	void verifyMemberships(std::vector<character> characterList, std::vector<unit> unitList);

	// Verify that all relations in a character list exist in the list
	void verifyRelations(std::vector<character> list);
	// Verify that all relations in a unit list exist in the list
	void verifyRelations(std::vector<unit> list);
}