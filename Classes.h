#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include "General.h"

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
	std::vector<std::vector<std::string>> relations = {};
};

// Unit Information
class unit : public entity {
public:
	unit(std::string fileSTEM);
	unit() = default;

	// Print out the unit
	void print();
};

// Character Information
class character : public entity {
public:
	std::string nickname = "None";

	character(std::string fileSTEM);
	character() = default;

	// Print out the character
	void print();
	// Print out the character and all member unit information
	void fullprint(std::vector<unit> unitList);
};

namespace interactions {
	// Verify all members in the character and unit list
	std::set<std::string> verifyMemberships(std::vector<character> characterList, std::vector<unit> unitList);

	// Verify that all relations in a character list exist in the list
	std::set<std::string> verifyRelations(std::vector<character> list);
	// Verify that all relations in a unit list exist in the list
	std::set<std::string> verifyRelations(std::vector<unit> list);

	// Verify the size of all units
	void verifySizes(std::vector<character> characterList, std::vector<unit> unitList);

	// Add any missing relations in the lists
	void addMissingRelations(std::vector<character> &characterList, std::vector<unit> &unitList);

	// Rename all characters
	void renameChar(std::set<std::string> unknownList, std::vector<character>& characterList);
	// Rename all units
	void renameUnit(std::set<std::string> unknownList, std::vector<character>& characterList, std::vector<unit>& unitList);

	// Write list contents to their respective files
	void writeToFile(std::vector<character> characterList, std::vector<unit> unitList);

	// Generate a set of rules for printing
	std::vector<std::string> genPrintRules(std::vector<std::string> crewNames);

	// Print according to a vector of rules
	void printRules(std::vector<std::string> rulesList, std::vector<character> characterList, std::vector<unit> unitList);
}