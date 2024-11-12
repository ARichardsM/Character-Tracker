#include "Tracker.h"

/*
	Interaction Scripts
*/

std::set<std::string> interactions::verifyMemberships(std::vector<character> characterList, std::vector<unit> unitList) {
	// Variables
	std::vector<std::string> unitNames = {"None"};
	std::set<std::string> returnList;

	// Append all unit names to unitNames
	for (unit unit : unitList) {
		unitNames.push_back(unit.name);
	}

	// For each character
	for (character character : characterList) {
		// If the member's name can't be found in unitNames, report it
		if (find(unitNames.begin(), unitNames.end(), character.member) == unitNames.end())
			returnList.insert(character.member);
	}

	// For each unit
	for (unit unit : unitList) {
		// If the member's name can't be found in unitNames, report it
		if (find(unitNames.begin(), unitNames.end(), unit.member) == unitNames.end())
			returnList.insert(unit.member);
	}

	// Return the list
	return returnList;
}

void interactions::verifySizes(std::vector<character> characterList, std::vector<unit> unitList) {
	// Variables
	std::vector<std::string> unitNames = {  };
	std::vector<std::vector<std::string>> unitInfo = { };
	std::vector<int> unitSizes = { };

	// Store the unit's name and necessary information and initialize the units' size
	for (unit unit : unitList) {
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

std::set<std::string> interactions::verifyRelations(std::vector<character> list) {
	// Variables
	std::vector<std::string> charNames;
	std::set<std::string> returnList;

	// Append all character names to charNames
	for (character character : list) {
		charNames.push_back(character.name);
	}

	// For each character
	for (character character : list) {
		// For each relation
		for (entity::tagFeature member : character.relationVec) {
			// If the member's name can't be found in charNames, add it to the return
			if (find(charNames.begin(), charNames.end(), member.name) == charNames.end())
				returnList.insert(member.name);
		}
	}

	// Return the list
	return returnList;
}

std::set<std::string> interactions::verifyRelations(std::vector<unit> list) {
	// Variables
	std::vector<std::string> unitNames;
	std::set<std::string> returnList;

	// Append all unit names to unitNames
	for (unit unit : list) {
		unitNames.push_back(unit.name);
	}

	// For each unit
	for (unit unit : list) {
		// For each relation
		for (entity::tagFeature member : unit.relationVec) {
			// If the member's name can't be found in charNames, report it
			if (find(unitNames.begin(), unitNames.end(), member.name) == unitNames.end())
				returnList.insert(member.name);
		}
	}

	// Return the list
	return returnList;
}

void interactions::addMissingRelations(std::vector<character> &characterList, std::vector<unit> &unitList) {
	// Variables
	unsigned int entitySize = characterList.size() + unitList.size();
	std::vector<std::vector<bool>> relationMatrix;
	std::vector<std::string> names;

	// Append all character names to names
	for (character chara : characterList) {
		names.push_back(chara.name);
	}

	// Append all unit names to names
	for (unit unit : unitList) {
		names.push_back(unit.name);
	}

	// Fill the relation matrix with false, representing no bond
	for (int i = 0; i < entitySize; i++)
		relationMatrix.push_back(std::vector<bool>(entitySize, false));

	// For each character's relation
	for (int i = 0; i < characterList.size(); i++) {
		for (entity::tagFeature relation : characterList[i].relationVec) {
			// Find the relation's name in `names`
			auto relPos = find(names.begin(), names.end(), relation.name);
			int intPos = std::distance(names.begin(), relPos);

			// If the relation exists
			if (relPos != names.end()){
				// Modify the relation matrix
				relationMatrix[i][intPos] = true;
				relationMatrix[intPos][i] = true;
			}
		}
	}
	
	// For each unit's relation
	for (int i = 0; i < unitList.size(); i++) {
		for (entity::tagFeature relation : unitList[i].relationVec) {
			// Find the relation's name in `names`
			auto relPos = find(names.begin(), names.end(), relation.name);
			int intPos = std::distance(names.begin(), relPos);

			// Adjust i to accomdate the characters
			int adjI = i + characterList.size();

			// If the relation exists
			if (relPos != names.end()) {
				// Modify the relation matrix
				relationMatrix[adjI][intPos] = true;
				relationMatrix[intPos][adjI] = true;
			}
		}
	}

	// For each character
	for (int i = 0; i < characterList.size(); i++) {
		// Record the character's relation names
		std::vector<std::string> relateNames;
		for (entity::tagFeature relation : characterList[i].relationVec) {
			relateNames.push_back(relation.name);
		}

		// For every entity
		for (int j = 0; j < entitySize; j++) {
			// if a relation doesn't exist, continue
			if (!relationMatrix[i][j])
				continue;

			// if the relation isn't already present, add it
			if (find(relateNames.begin(), relateNames.end(), names[j]) == relateNames.end()) {
				entity::tagFeature newRel;
				newRel.name = names[j];
				newRel.desc = "New Relation";
				characterList[i].relationVec.push_back(newRel);
			}
		}
	}

	// For each unit
	for (int i = 0; i < unitList.size(); i++) {
		// Adjust i to accomdate the characters
		int adjI = i + characterList.size();

		// Record the unit's relation names
		std::vector<std::string> relateNames;
		for (entity::tagFeature relation : unitList[i].relationVec) {
			relateNames.push_back(relation.name);
		}

		// For every entity
		for (int j = 0; j < entitySize; j++) {
			// if a relation doesn't exist, continue
			if (!relationMatrix[adjI][j])
				continue;

			// if the relation isn't already present, add it
			if (find(relateNames.begin(), relateNames.end(), names[j]) == relateNames.end()) {
				entity::tagFeature newRel;
				newRel.name = names[j];
				newRel.desc = "New Relation";
				unitList[i].relationVec.push_back(newRel);
			}
		}
	}
}

void interactions::writeToFile(std::vector<character> characterList, std::vector<unit> unitList) {
	for (character chara : characterList) {
		// Variables for input file and spare contents
		std::ifstream inFile("Characters/" + chara.name + ".txt");
		std::string contents = "";

		// For each line in the file
		std::string line;
		while (getline(inFile, line)) {
			// if the string does not contain a `: `, save it for later
			if (line.find(": ") == std::string::npos)
				contents += line + "\n";
		}
		inFile.close();

		// Reopen the file as an output file
		std::ofstream outFile("Characters/" + chara.name + ".txt");

		// Write the content from the character
		outFile << "Rank: " << characterRankings[chara.rank] << "\n";
		outFile << "Member: " << chara.member << "\n";
		for (std::string aspect : chara.aspects)
			outFile << "Aspect: " << aspect << "\n";
		for (entity::tagFeature relation : chara.relationVec)
			outFile << "Relation: " << relation.name << ": " << relation.desc << "\n";

		// Rewrite the spare contents
		outFile << contents;
		outFile.close();
	}

	for (unit unit : unitList) {
		// Variables for input file and spare contents
		std::ifstream inFile("Units/" + unit.name + ".txt");
		std::string contents = "";

		// For each line in the file
		std::string line;
		while (getline(inFile, line)) {
			// if the string does not contain a `: `, save it for later
			if (line.find(": ") == std::string::npos)
				contents += line + "\n";
		}
		inFile.close();

		// Reopen the file as an output file
		std::ofstream outFile("Units/" + unit.name + ".txt");

		// Write the content from the unit
		outFile << "Rank: " << unitRankings[unit.rank] << "\n";
		outFile << "Member: " << unit.member << "\n";
		for (std::string aspect : unit.aspects)
			outFile << "Aspect: " << aspect << "\n";
		for (entity::tagFeature relation : unit.relationVec)
			outFile << "Relation: " << relation.name << ": " << relation.desc << "\n";

		// Rewrite the spare contents
		outFile << contents;
		outFile.close();
	}
}
