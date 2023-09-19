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
			// Search for rank [1] in the character rankings
			auto rankIter = find(characterRankings.begin(), characterRankings.end(), splitLine[1]);

			// Assign the rank if it exists, otherwise stay unassigned
			if (rankIter != characterRankings.end())
				rank = std::distance(characterRankings.begin(), rankIter);
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

void character::print() {
	std::cout << "Name: " << name << "\n";
	std::cout << "Rank: " << characterRankings[rank] << "\n";
	std::cout << "Member: " << member << "\n";
	for (std::string aspect : aspects)
		std::cout << "Aspect: " << aspect << "\n";
	for (std::string relation : relations)
		std::cout << "Relations: " << relation << "\n";
}

void character::fullprint(std::vector<unit> unitList) {
	// If not a member, simply print
	if (member == "None")
		print();
	else {
		// Print Name and Rank
		std::cout << "Name: " << name << "\n";
		std::cout << "Rank: " << characterRankings[rank] << "\n";

		// Record the character's aspects and relations
		std::vector<std::string> fullAspects = aspects;
		std::vector<std::string> fullRelations = relations;

		// Set next member and initilize the full member vector
		std::vector<std::string> fullMember;
		std::string nextMember = member;

		// While a next member exists
		while (nextMember != "None") {

			// Find the unit the entity belongs to
			for (unit unit : unitList) {
				if (unit.name == nextMember) {
					// Add the aspects, relations and membership
					fullAspects.insert(fullAspects.end(), unit.aspects.begin(), unit.aspects.end());
					fullRelations.insert(fullRelations.end(), unit.relations.begin(), unit.relations.end());
					fullMember.push_back(nextMember);

					// Update the next member
					nextMember = unit.member;

					break;
				}
			}
		}

		// Print the full memberships, aspects and relations
		std::cout << "Member: " ;
		for (std::string membership : std::vector<std::string>(fullMember.begin(), fullMember.end() - 1))
			std::cout << membership << " - ";
		std::cout << fullMember.back() << "\n";

		for (std::string aspect : fullAspects)
			std::cout << "Aspect: " << aspect << "\n";

		for (std::string relation : fullRelations)
			std::cout << "Relations: " << relation << "\n";
	}
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
			// Search for rank [1] in the unit rankings
			auto rankIter = find(unitRankings.begin(), unitRankings.end(), splitLine[1]);

			// Assign the rank if it exists, otherwise stay unassigned
			if (rankIter != unitRankings.end())
				rank = std::distance(unitRankings.begin(), rankIter);
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
	std::cout << "Rank: " << unitRankings[rank] << "\n";
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

	// Append all unit names to unitNames
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

void interactions::verifySizes(std::vector<character> characterList, std::vector<unit> unitList) {
	// Variables
	std::vector<std::string> unitNames = {  };
	std::vector<std::vector<std::string>> unitInfo = { };
	std::vector<int> unitSizes = { };

	// Store the unit's name and necessary information and intilize the units' size
	for (unit unit : unitList) {
		//unitNames.push_back(unit.name);
		unitInfo.push_back({ unit.name, std::to_string(unit.rank), unit.member });
		unitSizes.push_back(0);
	}

	// Sort unit info in order of rank integer
	std::sort(unitInfo.begin(), unitInfo.end(),
		[](std::vector<std::string> a, std::vector<std::string> b) {
			return stoi(a[1]) < stoi(b[1]);
		});

	// Store the unit's name via sorted order
	for (std::vector<std::string> unit : unitInfo) {
		unitNames.push_back(unit[0]);
	}

	// For each character
	for (character character : characterList) {
		// Try to find it's unit membership
		auto charMem = find(unitNames.begin(), unitNames.end(), character.member);

		// If it belongs to a unit, add to the unit's size
		if (charMem != unitNames.end())
			unitSizes[std::distance(unitNames.begin(), charMem)] += 1;
	}

	// For each unit
	for (int i = 0; i < unitInfo.size(); i++) {
		// Try to find it's unit membership
		auto unitMem = find(unitNames.begin(), unitNames.end(), unitInfo[i][2]);

		// If it belongs to a unit, add it's size to the unit's size
		if (unitMem != unitNames.end())
			unitSizes[std::distance(unitNames.begin(), unitMem)] += unitSizes[i];

		// Print out the size
		std::cout << "[" << unitRankings[stoi(unitInfo[i][1])] << "] " << unitNames[i] << ": Size " << unitSizes[i] << ".";

		// If the size is invalid, report it
		if (!(pow(2, stoi(unitInfo[i][1])) <= unitSizes[i] && unitSizes[i] <= (3 * pow(2, stoi(unitInfo[i][1]) - 1))))
			std::cout << " Invalid Size";
		
		std::cout << "\n";
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