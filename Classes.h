#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

// Declare Global variables
const std::vector<std::string> unitRankings = {"Unassigned", "Crew", "Squad", "Regiment", "Faction"};							// List of eligible unit rankings
const std::vector<std::string> characterRankings = {"Unassigned", "Known", "Notable", "Expert", "Adept", "Legend", "Myth"};		// List of eligible character rankings

// Abstract Entity Information
class entity {
public:
	std::string name = "None";
	std::string member = "None";

	int rank = 0;

	std::vector<std::string> aspects = {};
	std::vector<std::string> relations = {};
};

// Unit Information
class unit : public entity {
public:
	unit(std::string fileSTEM);

	// Print out the unit
	void print();
};

// Character Information
class character : public entity {
public:
	std::string nickname = "None";

	character(std::string fileSTEM);

	// Print out the character
	void print();
	// Print out the character and all member unit information
	void fullprint(std::vector<unit> unitList);
};

namespace interactions {
	// Verify all members in the character and unit list
	void verifyMemberships(std::vector<character> characterList, std::vector<unit> unitList);

	// Verify that all relations in a character list exist in the list
	void verifyRelations(std::vector<character> list);
	// Verify that all relations in a unit list exist in the list
	void verifyRelations(std::vector<unit> list);
}