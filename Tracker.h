#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include "General.h"

// Declare Global variables
const std::vector<std::string> unitRankings = {"Unassigned", "Crew", "Squad", "Regiment", "Faction"};											// List of eligible unit rankings
const std::vector<std::string> characterRankings = {"Unassigned", "Known", "Novice", "Apprentice", "Adept", "Expert", "Legend", "Myth"};		// List of eligible character rankings

// Abstract Entity Information
class entity {
public:
	std::string name = "None";
	std::string member = "None";

	int rank = 0;

	std::vector<std::string> aspects = {};
	std::vector<std::vector<std::string>> relations = {};

	// Add a feature based on an input string
	void addFeature(std::string featString);
};

// Unit Information
class unit : public entity {
public:
	unit(const std::string& file);
	unit() = default;

	// Add a feature based on an input string
	void addFeature(std::string featString);

	// Print out the unit
	void print() const;
};

// Character Information
class character : public entity {
public:
	std::string nickname = "None";

	character(const std::string& file);
	character() = default;

	// Add a feature based on an input string
	void addFeature(std::string featString);

	// Print out the character
	void print() const;
	// Print out the character and all member unit information
	void fullprint(const std::vector<unit>& unitList) const;
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
	void addMissingRelations(std::vector<character>& characterList, std::vector<unit>& unitList);

	// Rename all characters
	void renameChar(std::set<std::string> unknownList, std::vector<character>& characterList);
	// Rename all units
	void renameUnit(std::set<std::string> unknownList, std::vector<character>& characterList, std::vector<unit>& unitList);

	// Write list contents to their respective files
	void writeToFile(std::vector<character> characterList, std::vector<unit> unitList);
	
	// Load from a multi-character markdown file
	void loadMD(std::vector<character>& characterList, std::string file);
	// Load from a multi-unit markdown file
	void loadMD(std::vector<unit>& unitList, std::string file);
}

namespace input {
	// Split a string based on a list of delims
	std::vector<std::string> splitDelim(std::string input);
}

namespace output {
	// Print all in the provided vectors
	void printAll(const std::vector<character>& characterList, const std::vector<unit>& unitList);
	// Print according to rank
	void printRank(std::vector<character> characterList, std::vector<unit> unitList);
	// Full print according to a vector of rules
	void printFull(const std::vector<character>& characterList, const std::vector<unit>& unitList);
}

namespace rules {
	// Generate a set of rules for printing
	std::vector<std::string> genRules(const std::vector<std::string>& crewNames);
	// Filter the two lists according to the rules
	void filterRules(const std::vector<std::string>& rulesList, std::vector<character>& characterList, std::vector<unit>& unitList);
}