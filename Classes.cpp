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
		std::vector<std::string> splitLine;

		while (line.find(": ") != std::string::npos) {
			splitLine.push_back(line.substr(0, line.find(": ")));
			line = line.substr(line.find(": ") + 2);
		}

		splitLine.push_back(line);

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
			switch (splitLine.size()) {
			case 2:
				relations.push_back({ splitLine[1], "Unknown Relation" });
				break;
			case 3:
				relations.push_back({ splitLine[1], splitLine[2] });
				break;
			}
		}
	}
}

void character::print() const {
	std::cout << "Name: " << name << "\n";
	std::cout << "Rank: " << characterRankings[rank] << "\n";
	std::cout << "Member: " << member << "\n";
	for (std::string aspect : aspects)
		std::cout << "Aspect: " << aspect << "\n";
	for (std::vector<std::string> relation : relations)
		std::cout << "Relations: " << relation[0] << " - " << relation[1] << "\n";
}

void character::fullprint(const std::vector<unit>& unitList) const {
	// If not a member, simply print
	if (member == "None")
		print();
	else {
		// Print Name and Rank
		std::cout << "Name: " << name << "\n";
		std::cout << "Rank: " << characterRankings[rank] << "\n";

		// Record the character's aspects and relations
		std::vector<std::string> fullAspects = aspects;
		std::vector<std::vector<std::string>> fullRelations = relations;

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

					// Update the next member, while preventing an infinte loop
					if (nextMember != unit.member)
						nextMember = unit.member;
					else
						nextMember = "None";

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

		for (std::vector<std::string> relation : fullRelations)
			std::cout << "Relation: " << relation[0] << " - " << relation[1] << "\n";
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
		std::vector<std::string> splitLine;

		while (line.find(": ") != std::string::npos) {
			splitLine.push_back(line.substr(0, line.find(": ")));
			line = line.substr(line.find(": ") + 2);
		}

		splitLine.push_back(line);

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
			switch (splitLine.size()) {
			case 2:
				relations.push_back({ splitLine[1], "Unknown Relation" });
				break;
			case 3:
				relations.push_back({ splitLine[1], splitLine[2] });
				break;
			}
		}
	}
}

void unit::print() const {
	std::cout << "Name: " << name << "\n";
	std::cout << "Rank: " << unitRankings[rank] << "\n";
	std::cout << "Member: " << member << "\n";
	for (std::string aspect : aspects)
		std::cout << "Aspect: " << aspect << "\n";
	for (std::vector<std::string> relation : relations)
		std::cout << "Relation: " << relation[0] << " - " << relation[1] << "\n";
}

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
		for (std::vector<std::string> member : character.relations) {
			// If the member's name can't be found in charNames, add it to the return
			if (find(charNames.begin(), charNames.end(), member[0]) == charNames.end())
				returnList.insert(member[0]);
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
		for (std::vector<std::string> member : unit.relations) {
			// If the member's name can't be found in charNames, report it
			if (find(unitNames.begin(), unitNames.end(), member[0]) == unitNames.end())
				returnList.insert(member[0]);
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
		for (std::vector<std::string> relation : characterList[i].relations) {
			// Find the relation's name in `names`
			auto relPos = find(names.begin(), names.end(), relation[0]);
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
		for (std::vector<std::string> relation : unitList[i].relations) {
			// Find the relation's name in `names`
			auto relPos = find(names.begin(), names.end(), relation[0]);
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
		for (std::vector<std::string> relation : characterList[i].relations) {
			relateNames.push_back(relation[0]);
		}

		// For every entity
		for (int j = 0; j < entitySize; j++) {
			// if a relation doesn't exist, continue
			if (!relationMatrix[i][j])
				continue;

			// if the relation isn't already present, add it
			if (find(relateNames.begin(), relateNames.end(), names[j]) == relateNames.end()) {
				characterList[i].relations.push_back({ names[j], "New Relation" });
			}
		}
	}

	// For each unit
	for (int i = 0; i < unitList.size(); i++) {
		// Adjust i to accomdate the characters
		int adjI = i + characterList.size();

		// Record the unit's relation names
		std::vector<std::string> relateNames;
		for (std::vector<std::string> relation : unitList[i].relations) {
			relateNames.push_back(relation[0]);
		}

		// For every entity
		for (int j = 0; j < entitySize; j++) {
			// if a relation doesn't exist, continue
			if (!relationMatrix[adjI][j])
				continue;

			// if the relation isn't already present, add it
			if (find(relateNames.begin(), relateNames.end(), names[j]) == relateNames.end()) {
				unitList[i].relations.push_back({ names[j], "New Relation" });
			}
		}
	}
}

void interactions::renameChar(std::set<std::string> unknownList, std::vector<character>& characterList) {
	// Declare name variables
	std::vector<std::string> possibleNames;
	std::vector<std::string> trueNames;

	// Append all character names to names
	for (character chara : characterList) {
		possibleNames.push_back(chara.name);
	}

	// Prompt for the true names
	for (std::string unknownName : unknownList) {
		int nameLoc = support::prompt("What is the true name of " + unknownName, possibleNames) - 1;
		trueNames.push_back(possibleNames[nameLoc]);
	}

	// For every character's relation
	for (character &chara : characterList) {
		for (std::vector<std::string> &relation : chara.relations) {
			// Try to find the relation's name in `unknownList`
			auto relPos = find(unknownList.begin(), unknownList.end(), relation[0]);
			int intPos = std::distance(unknownList.begin(), relPos);

			// If the name was found, change it for the true name
			if (relPos != unknownList.end())
				relation[0] = trueNames[intPos];
		}	
	}
}

void interactions::renameUnit(std::set<std::string> unknownList, std::vector<character>& characterList, std::vector<unit>& unitList) {
	// Declare name variables
	std::vector<std::string> possibleNames;
	std::vector<std::string> trueNames;

	// Append all unit names to names
	for (unit unit : unitList) {
		possibleNames.push_back(unit.name);
	}

	// Prompt for the true names
	for (std::string unknownName : unknownList) {
		int nameLoc = support::prompt("What is the true name of " + unknownName, possibleNames) - 1;
		trueNames.push_back(possibleNames[nameLoc]);
	}

	// For every character's member
	for (character& chara : characterList) {
		// Try to find the member's name in `unknownList`
		auto relPos = find(unknownList.begin(), unknownList.end(), chara.member);
		int intPos = std::distance(unknownList.begin(), relPos);

		// If the name was found, change it for the true name
		if (relPos != unknownList.end())
			chara.member = trueNames[intPos];
	}

	// For every unit
	for (unit& uni : unitList) {
		// Try to find the member's name in `unknownList`
		auto relPos = find(unknownList.begin(), unknownList.end(), uni.member);
		int intPos = std::distance(unknownList.begin(), relPos);

		// If the name was found, change it for the true name
		if (relPos != unknownList.end())
			uni.member = trueNames[intPos];

		// For each of the unit's relations
		for (std::vector<std::string>& relation : uni.relations) {
			// Try to find the relation's name in `unknownList`
			auto relPos = find(unknownList.begin(), unknownList.end(), relation[0]);
			int intPos = std::distance(unknownList.begin(), relPos);

			// If the name was found, change it for the true name
			if (relPos != unknownList.end())
				relation[0] = trueNames[intPos];
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
		for (std::vector<std::string> relation : chara.relations)
			outFile << "Relation: " << relation[0] << ": " << relation[1] << "\n";

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
		for (std::vector<std::string> relation : unit.relations)
			outFile << "Relation: " << relation[0] << ": " << relation[1] << "\n";

		// Rewrite the spare contents
		outFile << contents;
		outFile.close();
	}
	std::cout << "Write to File\n";
}

std::vector<std::string> rules::genRules(const std::vector<std::string>& crewNames) {
	// Declare Variables
	std::vector<std::string> rulesList = {};
	bool cont = true;

	// Until the user calls 'Done'
	while (cont) {
		// If there are rules in the rules list
		if (rulesList.size() != 0) {
			// Print out the rules
			std::cout << "Current Rules\n";
			for (std::string rule : rulesList)
				std::cout << rule << "\n";

		}

		// Prompt the user
		switch (support::prompt("Select", { "Done", "Add Rule", "Remove Rule" })) {
		case 1:
			// Break the while loop
			cont = false;
			break;
		case 2:
		{
			// Declare the variable for all possible rules
			std::vector<std::string> possibleRules = {};

			// If the limit by entity was set to crew
			if (find(rulesList.begin(), rulesList.end(), "Only:Crew") != rulesList.end()) {
				for (std::string rank : unitRankings) {
					// If the rank is not already in the rules list, add it to the possible rules
					if (find(rulesList.begin(), rulesList.end(), "Ranking:" + rank) == rulesList.end())
						possibleRules.push_back("Ranking:" + rank);
				}
			}
			// If the limit by entity was set to character
			else if (find(rulesList.begin(), rulesList.end(), "Only:Character") != rulesList.end()) {
				for (std::string rank : characterRankings) {
					// If the rank is not already in the rules list, add it to the possible rules
					if (find(rulesList.begin(), rulesList.end(), "Ranking:" + rank) == rulesList.end())
						possibleRules.push_back("Ranking:" + rank);
				}
			}
			else
				// Add a rule to limit by entity type
				possibleRules.insert(possibleRules.end(), { "Only:Unit", "Only:Character" });

			// If there are no member rules currently in the rules list
			if (std::find_if(rulesList.begin(), rulesList.end(), [](const std::string& str)
				{ return str.find("Member") != std::string::npos; }) == rulesList.end()) {

				// Add a rule to limit by membership
				for (std::string crew : crewNames)
					possibleRules.push_back("Member:" + crew);
			}

			// Prompt for a rule selection
			int selection = support::prompt("Select a Rule to Add", possibleRules);

			// Add the selected rule to the rules list
			if (selection != -1)
				rulesList.push_back(possibleRules[selection - 1]);
			break;
		}
		case 3:
		{
			// If the rules list is empty, do nothing
			if (rulesList.size() == 0)
				break;

			// Prompt for a rule selection
			int selection = support::prompt("Select a Rule to Remove", rulesList) - 1;

			// If the selected rule is one of the `Only` rules
			if (rulesList[selection].find("Only:") != std::string::npos) {
				// Remove the selected rule
				rulesList.erase(rulesList.begin() + selection);

				// Remove all `Ranking` rules
				for (int i = rulesList.size() - 1; i >= 0; i--) {
					if (rulesList[i].find("Ranking:") != std::string::npos)
						rulesList.erase(rulesList.begin() + i);
				}
			} else 
				// Remove the selected rule
				rulesList.erase(rulesList.begin() + selection);

			break;
		}
		}
	}

	// Return the list of rules
	return rulesList;
}

void rules::filterRules(const std::vector<std::string>& rulesList, std::vector<character>& characterList, std::vector<unit>& unitList) {
	// Declare variable for holding entity information
	std::vector<std::vector<std::string>> possibleEntities = {};
	std::vector<std::string> possibleNames = {};

	// Pull all neccessary entity information
	for (character ent : characterList) {
		possibleNames.push_back(ent.name);
		possibleEntities.push_back({ ent.name, characterRankings[ent.rank], ent.member, "Character" });
	}

	for (unit ent : unitList) {
		possibleNames.push_back(ent.name);
		possibleEntities.push_back({ ent.name, unitRankings[ent.rank], ent.member, "Unit" });
	}

	// For each of the rules
	for (std::string rule : rulesList) {
		// Declare variable to note the filtered entities
		std::vector<bool> filtEnti = {};

		// For every possible entity
		for (std::vector<std::string> ent : possibleEntities) {
			std::string ruleType = rule.substr(0, rule.find(":"));
			// 'Only' Rules
			if (ruleType == "Only") {
				// Verify the unit type
				if (rule.substr(rule.find(":") + 1) == ent[3])
					filtEnti.push_back(false);
				else
					filtEnti.push_back(true);
			}

			// 'Ranking' Rules
			if (ruleType == "Ranking") {
				// Verify the ranking
				if (rule.substr(rule.find(":") + 1) == ent[1])
					filtEnti.push_back(false);
				else
					filtEnti.push_back(true);
			}

			// 'Member' Rules
			if (ruleType == "Member") {
				// Verify the membership
				if (rule.substr(rule.find(":") + 1) == ent[2])
					filtEnti.push_back(false);
				// Treat unit as a member of themselves
				else if (rule.substr(rule.find(":") + 1) == ent[0])
					filtEnti.push_back(false);
				else
					filtEnti.push_back(true);
			}
		}

		// Filter out entities that don't follow the current rule
		for (int i = filtEnti.size() - 1; i >= 0; i--) {
			if (filtEnti[i]) {
				possibleNames.erase(possibleNames.begin() + i);
				possibleEntities.erase(possibleEntities.begin() + i);
			}
		}

	}

	for (int i = characterList.size() - 1; i >= 0; i--) {
		// If the character's name can't be found in possibleNames, remove it from the Vector
		if (find(possibleNames.begin(), possibleNames.end(), characterList[i].name) == possibleNames.end())
			characterList.erase(characterList.begin() + i);
	}

	for (int i = unitList.size() - 1; i >= 0; i--) {
		// If the unit's name can't be found in possibleNames, remove it from the Vector
		if (find(possibleNames.begin(), possibleNames.end(), unitList[i].name) == possibleNames.end())
			unitList.erase(unitList.begin() + i);
	}
}

void output::printAll(const std::vector<character>& characterList, const std::vector<unit>& unitList) {
	// Print all characters
	std::cout << "Characters" << "\n";
	for (character entry : characterList) {
		entry.print();
		std::cout << "\n";
	}

	// Print all units
	std::cout << "Units" << "\n";
	for (unit entry : unitList) {
		entry.print();
		std::cout << "\n";
	}
}

void output::printRank(const std::vector<character>& characterList, const std::vector<unit>& unitList) {
	// Declare a variable to track the previously printed rank
	int prevRank = -1;

	// Sort characters in order of rank integer
	std::sort(characterList.begin(), characterList.end(),
		[](character a, character b) {
			return a.rank < b.rank;
		});

	// Sort units in order of rank integer
	std::sort(unitList.begin(), unitList.end(),
		[](unit a, unit b) {
			return a.rank < b.rank;
		});

	// For each unit
	for (unit uni : unitList) {
		// If the rank has changed, print a new header
		if (prevRank != uni.rank) {
			std::cout << "\n" << unitRankings[uni.rank] << "\n";
			prevRank = uni.rank;
		}

		// Print the unit and it's membership
		std::cout << uni.name;
		if (uni.member != "None")
			std::cout << " [" << uni.member << "]";
		std::cout << "\n";
	}

	// For each character
	for (character chara : characterList) {
		// If the rank has changed, print a new header
		if (prevRank != chara.rank) {
			std::cout << "\n" << characterRankings[chara.rank] << "\n";
			prevRank = chara.rank;
		}

		// Print the unit and it's membership
		std::cout << chara.name;
		if (chara.member != "None")
			std::cout << " [" << chara.member << "]";
		std::cout << "\n";
	}

	// Final newline for formatting
	std::cout << "\n";
}

void output::printFull(const std::vector<character>& characterList, const std::vector<unit>& unitList) {
	// Break if there are no possible names
	if (characterList.size() == 0)
		return;

	// Randomly select
	int select = rand() % characterList.size();

	// Full print the selected character
	characterList[select].fullprint(unitList);
}
