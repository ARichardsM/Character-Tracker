#include "Classes.h"

/*
	Character Scripts
*/

character::character(std::string fileSTEM) {
	// Set the name to be the file's stem
	name = fileSTEM;

	// Access the character's file
	std::ifstream inputFile;
	inputFile.open("Characters/" + fileSTEM + ".txt");

	// For each line
	std::string line;
	while (getline(inputFile, line)) {
		// if the string does not contain a `: `, skip
		if (line.find(": ") == std::string::npos)
			continue;

		// Split the line at `: `
		std::vector<std::string> splitLine = { line.substr(0, line.find(": ")), line.substr(line.find(": ") + 2) };

		// Depending on [0], set a variable to [1]
		if (splitLine[0] == "Name") {
			nickname = splitLine[1];
		}
		else if (splitLine[0] == "Rank") {
			rank = splitLine[1];
		}
		else if (splitLine[0] == "Member") {
			member = splitLine[1];
		}
		else if (splitLine[0] == "Aspect") {
			aspects.push_back(splitLine[1]);
		}
		else if (splitLine[0] == "Fact") {
			facts.push_back(splitLine[1]);
		}
		else if (splitLine[0] == "Relation") {
			relations.push_back(splitLine[1]);
		}
	}
}

void character::print() {
	std::cout << "Name: " << name << "\n";
	std::cout << "Rank: " << rank << "\n";
	std::cout << "Member: " << member << "\n";
	for (std::string aspect : aspects)
		std::cout << "Aspect: " << aspect << "\n";
	for (std::string fact : facts)
		std::cout << "Facts: " << fact << "\n";
	for (std::string relation : relations)
		std::cout << "Relations: " << relation << "\n";
}

/*
	Unit Scripts
*/

unit::unit(std::string fileSTEM) {
	// Set the unit's name
	name = fileSTEM;

	// Access the unit's file
	std::ifstream inputFile;
	inputFile.open("Units/" + fileSTEM + ".txt");

	// For each line
	std::string line;
	while (getline(inputFile, line)) {
		// if the string does not contain a `: `, skip
		if (line.find(": ") == std::string::npos)
			continue;

		// Split the line at `: `
		std::vector<std::string> splitLine = { line.substr(0, line.find(": ")), line.substr(line.find(": ") + 2) };

		// Depending on [0], set a variable to [1]
		if (splitLine[0] == "Rank") {
			rank = splitLine[1];
		}
		else if (splitLine[0] == "Member") {
			member = splitLine[1];
		}
		else if (splitLine[0] == "Aspect") {
			aspects.push_back(splitLine[1]);
		}
		else if (splitLine[0] == "Relation") {
			relations.push_back(splitLine[1]);
		}
	}
}

void unit::print() {
	std::cout << "Name: " << name << "\n";
	std::cout << "Rank: " << rank << "\n";
	std::cout << "Member: " << member << "\n";
	for (std::string aspect : aspects)
		std::cout << "Aspect: " << aspect << "\n";
	for (std::string relation : relations)
		std::cout << "Relations: " << relation << "\n";
}

/*
	Interaction Scripts
*/

void interactions::verifyMemberships(std::vector<character> characterList, std::vector<unit> unitList) {
	// Variables
	std::vector<std::string> unitNames = {"None"};

	// Append all character names to charNames
	for (unit unit : unitList) {
		unitNames.push_back(unit.name);
	}

	// For each character
	for (character character : characterList) {
		// If the member's name can't be found in unitNames, report it
		if (find(unitNames.begin(), unitNames.end(), character.member) == unitNames.end())
			std::cout << character.member << " from " << character.name << " cannot be found.\n";
	}

	// For each unit
	for (unit unit : unitList) {
		// If the member's name can't be found in unitNames, report it
		if (find(unitNames.begin(), unitNames.end(), unit.member) == unitNames.end())
			std::cout << unit.member << " from " << unit.name << " cannot be found.\n";
	}
}

void interactions::verifyRelations(std::vector<character> list) {
	// Variables
	std::vector<std::string> charNames;

	// Append all character names to charNames
	for (character character : list) {
		charNames.push_back(character.name);
	}

	// For each character
	for (character character : list) {
		// For each relation
		for (std::string member : character.relations) {
			// If the member's name can't be found in charNames, report it
			if (find(charNames.begin(), charNames.end(), member) == charNames.end())
				std::cout << member << " from " << character.name << " cannot be found.\n";
		}
	}
}

void interactions::verifyRelations(std::vector<unit> list) {
	// Variables
	std::vector<std::string> unitNames;

	// Append all unit names to unitNames
	for (unit unit : list) {
		unitNames.push_back(unit.name);
	}

	// For each unit
	for (unit unit : list) {
		// For each relation
		for (std::string member : unit.relations) {
			// If the member's name can't be found in charNames, report it
			if (find(unitNames.begin(), unitNames.end(), member) == unitNames.end())
				std::cout << member << " from " << unit.name << " cannot be found.\n";
		}
	}
}