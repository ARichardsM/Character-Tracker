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
	struct feature {
		std::string name;
		std::string desc;

		// Return the feature as a string
		std::string returnFeat();
	};

	struct tagFeature : public feature {
		std::vector<std::string> tags;

		// Return the tagged feature as a string
		std::string returnFeat();
	};

	std::string name = "None";
	std::string member = "None";

	int rank = 0;
	//int historyIndex = -1;

	std::vector<std::string> aspects = {};
	//std::vector<tagFeature> relations;

	// Add a feature based on an input string
	void addFeature(const std::string& featString);
};

// Unit Information
class unit : public entity {
public:
	// Initializer
	unit() = default;

	// Add a feature based on an input string
	void addFeature(const std::string& featString);

	// Output the unit
	std::string output() const;
};

// Character Information
class character : public entity {
public:
	// Variables
	std::vector<tagFeature> relations;
	int historyIndex = -1;

	// Initializer
	character() = default;

	// Add a feature or add to history based on an input string
	void addFeature(std::string featString, std::vector<std::string>& history);

	// Output the character
	std::string output() const;
};

struct UnitList {
	struct Tag{
		std::string name;
		int weight;
		std::string desc;
	};

	std::vector<unit> units;     // Contains all units as the `unit` class
	std::vector<Tag> bonds;		// Contains all possible relation tags
};

struct {
	struct Tag {
		std::string name;
		int weight;
		std::string desc;
	};

	std::vector<character> characters;     // Contains all units as the `unit` class
	std::vector<Tag> bonds;		// Contains all possible relation tags
} CharacterList;


namespace interactions {
	// Verify all members in the character and unit list
	std::set<std::string> verifyMemberships(std::vector<character> characterList, std::vector<unit> unitList);

	// Verify that all relations in a character list exist in the list
	std::set<std::string> verifyRelations(std::vector<character> list);

	// Verify the size of all units
	void verifySizes(std::vector<character> characterList, std::vector<unit> unitList);

	// Write list contents to their respective files
	void writeToFile(std::vector<character> characterList, std::vector<unit> unitList);
}

namespace modifyRelations {
	// Add any missing relations in the lists
	void addMissingRelations(std::vector<character>& characterList, std::vector<unit>& unitList);

	// Modify the relations between the provided characters
	void modCharacters(std::vector<character>& characterList);
}

namespace missingEntity{
	// Refactor a character
	void refacChar(const std::string& missingChar, std::vector<character>& characterList);
	// Refactor a unit
	void refacUnit(const std::string& missingUnit, std::vector<character>& characterList, std::vector<unit>& unitList);

	// Delete a selected character
	void deleteChar(const std::string& missingChar, std::vector<character>& characterList);
	// Delete a selected unit
	void deleteUnit(const std::string& missingUnit, std::vector<character>& characterList, std::vector<unit>& unitList);

	// Rename all characters
	void renameChar(const std::string& missingChar, std::vector<character>& characterList);
	// Rename all units
	void renameUnit(const std::string& missingUnit, std::vector<character>& characterList, std::vector<unit>& unitList);

	// Split a unit into other units
	void splitUnit(const std::string& missingUnit, std::vector<character>& characterList, std::vector<unit>& unitList);
}

namespace input {
	// Split a string based on a list of delims
	std::vector<std::string> splitDelim(std::string input);
	// Split a string based on a list of delims
	std::vector<std::string> splitDelim(std::string input, std::vector<std::string> delimList);

	// Load a character from a file
	void loadChar(std::string file, std::vector<character>& characterList, std::vector<std::string>& history);
	// Load a unit from a file
	void loadUnit(std::string file, std::vector<unit>& unitList, std::vector<std::string>& history);
}

namespace output {
	// Print all in the provided vectors
	void printAll(const std::vector<character>& characterList, const std::vector<unit>& unitList);
	// Print according to rank
	void printRank(std::vector<character> characterList, std::vector<unit> unitList);
	// Full print according to a vector of rules
	void printFull(const std::vector<character>& characterList, const std::vector<unit>& unitList);
	// Write the character and unit list to two seperate markdown files
	void logListsMD(const std::vector<character>& characterList, const std::vector<unit>& unitList, const std::vector<std::string>& history);

	// Print out the character and all member unit information
	void charPrintFull(const character& acter, const std::vector<unit>& unitList);

	// Print units and mention members
	void printFullUnit(const std::vector<character>& characterList, const std::vector<unit>& unitList);

	// Print multiple characters or units, chosen randomly
	void multiPrint(const std::vector<character>& characterList, const std::vector<unit>& unitList);
}

namespace rules {
	// Generate a set of rules for printing
	std::vector<std::string> genRules(const std::vector<std::string>& crewNames);
	// Filter the two lists according to the rules
	void filterRules(const std::vector<std::string>& rulesList, std::vector<character>& characterList, std::vector<unit>& unitList);
}

namespace simpleFind {
	int find(const std::vector<character>& arr, const std::string& val);
	int find(const std::vector<unit>& arr, const std::string& val);
}