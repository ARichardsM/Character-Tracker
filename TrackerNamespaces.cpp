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
		for (entity::relation member : character.relationVec) {
			// If the member's name can't be found in charNames, add it to the return
			if (find(charNames.begin(), charNames.end(), member.partner) == charNames.end())
				returnList.insert(member.partner);
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
		for (entity::relation member : unit.relationVec) {
			// If the member's name can't be found in charNames, report it
			if (find(unitNames.begin(), unitNames.end(), member.partner) == unitNames.end())
				returnList.insert(member.partner);
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
		for (entity::relation relation : characterList[i].relationVec) {
			// Find the relation's name in `names`
			auto relPos = find(names.begin(), names.end(), relation.partner);
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
		for (entity::relation relation : unitList[i].relationVec) {
			// Find the relation's name in `names`
			auto relPos = find(names.begin(), names.end(), relation.partner);
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
		for (entity::relation relation : characterList[i].relationVec) {
			relateNames.push_back(relation.partner);
		}

		// For every entity
		for (int j = 0; j < entitySize; j++) {
			// if a relation doesn't exist, continue
			if (!relationMatrix[i][j])
				continue;

			// if the relation isn't already present, add it
			if (find(relateNames.begin(), relateNames.end(), names[j]) == relateNames.end()) {
				entity::relation newRel;
				newRel.partner = names[j];
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
		for (entity::relation relation : unitList[i].relationVec) {
			relateNames.push_back(relation.partner);
		}

		// For every entity
		for (int j = 0; j < entitySize; j++) {
			// if a relation doesn't exist, continue
			if (!relationMatrix[adjI][j])
				continue;

			// if the relation isn't already present, add it
			if (find(relateNames.begin(), relateNames.end(), names[j]) == relateNames.end()) {
				entity::relation newRel;
				newRel.partner = names[j];
				newRel.desc = "New Relation";
				unitList[i].relationVec.push_back(newRel);
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
		for (entity::relation &relation : chara.relationVec) {
			// Try to find the relation's name in `unknownList`
			auto relPos = find(unknownList.begin(), unknownList.end(), relation.partner);
			int intPos = std::distance(unknownList.begin(), relPos);

			// If the name was found, change it for the true name
			if (relPos != unknownList.end())
				relation.partner = trueNames[intPos];
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
		for (entity::relation &relation : uni.relationVec) {
			// Try to find the relation's name in `unknownList`
			auto relPos = find(unknownList.begin(), unknownList.end(), relation.partner);
			int intPos = std::distance(unknownList.begin(), relPos);

			// If the name was found, change it for the true name
			if (relPos != unknownList.end())
				relation.partner = trueNames[intPos];
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
		for (entity::relation relation : chara.relationVec)
			outFile << "Relation: " << relation.partner << ": " << relation.desc << "\n";

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
		for (entity::relation relation : unit.relationVec)
			outFile << "Relation: " << relation.partner << ": " << relation.desc << "\n";

		// Rewrite the spare contents
		outFile << contents;
		outFile.close();
	}
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
		std::cout << entry.output();
		std::cout << "\n";
	}

	// Print all units
	std::cout << "Units" << "\n";
	for (unit entry : unitList) {
		std::cout << entry.output();
		std::cout << "\n";
	}
}

void output::printRank(std::vector<character> characterList, std::vector<unit> unitList) {
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

void output::logListsMD(const std::vector<character>& characterList, const std::vector<unit>& unitList, const std::vector<std::string>& history) {
	// Variables for output file
	std::ofstream outFileChar("characterMD.md");

	for (character chara : characterList) {
		// Write the content from the character
		outFileChar << "# " << chara.name << "\n";
		outFileChar << chara.output();

		if (chara.historyInd != -1)
			outFileChar << history[chara.historyInd];
	}

	// Close the Out File
	outFileChar.close();

	// Variables for output file
	std::ofstream outFileUnit("unitMD.md");

	for (unit unit : unitList) {

		// Write the content from the unit
		outFileUnit << "# " << unit.name << "\n";
		outFileUnit << unit.output();

		if (unit.historyInd != -1)
			outFileUnit << history[unit.historyInd];
	}

	// Close the Out File
	outFileUnit.close();
}

std::vector<std::string> input::splitDelim(std::string input) {
	// Variables for delims and their found position
	std::vector<std::string> delimList = { ": ", " - ", " > "};
	std::vector<int> delimPos;

	// Variable for the return
	std::vector<std::string> splitLine;

	// Split a maximum of ten times
	for (int i = 0; i < 10; i++) {
		// Find each delim in the string
		for (std::string delim : delimList) {
			// Find the delim
			int relPos = input.find(delim);

			// If the delim doesn't appear, set it to the array's size
			if (relPos == -1)
				delimPos.push_back(input.size());
			else
				delimPos.push_back(input.find(delim));
		}

		// Determine the first delim to appear
		auto minEleIter = std::min_element(delimPos.begin(), delimPos.end());
		int minEle = std::distance(delimPos.begin(), minEleIter);

		// If no delim's appeared, break
		if (delimPos[minEle] == input.size())
			break;

		// Split the line and continue with the remainder
		splitLine.push_back(input.substr(0, input.find(delimList[minEle])));
		input = input.substr(input.find(delimList[minEle]) + delimList[minEle].size());

		// Clear the delim positions
		delimPos.clear();
	}

	// Add the rest of the line to the return
	splitLine.push_back(input);

	return splitLine;
}

void input::loadChar(std::string file, std::vector<character>& characterList, std::vector<std::string>& history) {
	// Text file loading lambda
	auto loadCharTXT = [&]() {
		// Add the character to the character list
		int charIn = characterList.size();
		characterList.push_back(character());

		// Access the character's file
		std::ifstream inputFile;
		inputFile.open("Characters/" + file);

		// For each line
		std::string line;
		while (getline(inputFile, line)) {
			// Add the feature
			characterList[charIn].addFeature(line, history);
		}

		// Add the character's name
		characterList[charIn].name = file.substr(0, file.find("."));
	};

	// Markdown file loading lambda
	auto loadCharMD = [&]() {
		// Access the character markdown file
		std::ifstream inputFile;
		inputFile.open("Characters/" + file);

		// Initialize current character index
		int charIn = -1;

		// For each line
		std::string line;
		while (getline(inputFile, line)) {
			// Search for the header delim
			int findPos = line.find("# ");

			// If the delim appears, add a character and index it
			if (findPos != -1) {
				charIn = characterList.size();
				characterList.push_back(character());
				characterList[charIn].name = line.substr(findPos + 2);
				continue;
			}

			// If no character is indexed, skip
			if (charIn == -1)
				continue;

			// Attempt to add a festure
			characterList[charIn].addFeature(line, history);
		}
	};

	// Skip the template
	if (file.substr(0, file.find(".")) == "Template Character")
		return;

	// Check and add if the file is .txt
	if (file.substr(file.find(".")) == ".txt")
		loadCharTXT();

	// Check and add if the file is .md
	if (file.substr(file.find(".")) == ".md")
		loadCharMD();
}

void input::loadUnit(std::string file, std::vector<unit>& unitList, std::vector<std::string>& history) {
	// Text file loading lambda
	auto loadUnitTXT = [&]() {
		// Add the unit to the unit list
		int unitIn = unitList.size();
		unitList.push_back(unit());

		// Access the unit's file
		std::ifstream inputFile;
		inputFile.open("Units/" + file);

		// For each line
		std::string line;
		while (getline(inputFile, line)) {
			// Add the feature
			unitList[unitIn].addFeature(line, history);
		}

		// Add the unit's name
		unitList[unitIn].name = file.substr(0, file.find("."));
	};

	// Markdown file loading lambda
	auto loadUnitMD = [&]() {
		// Access the unit markdown file
		std::ifstream inputFile;
		inputFile.open("Units/" + file);

		// Initialize current unit index
		int unitIn = -1;

		// For each line
		std::string line;
		while (getline(inputFile, line)) {
			// Search for the header delim
			int findPos = line.find("# ");

			// If the delim appears, add a unit and index it
			if (findPos != -1) {
				unitIn = unitList.size();
				unitList.push_back(unit());
				unitList[unitIn].name = line.substr(findPos + 2);
				continue;
			}

			// If no unit is indexed, skip
			if (unitIn == -1)
				continue;

			// Attempt to add a festure
			unitList[unitIn].addFeature(line, history);
		}
	};

	// Skip the template
	if (file.substr(0, file.find(".")) == "Template Unit")
		return;

	// Check and add if the file is .txt
	if (file.substr(file.find(".")) == ".txt")
		loadUnitTXT();

	// Check and add if the file is .md
	if (file.substr(file.find(".")) == ".md")
		loadUnitMD();
}

void interactions::deleteChar(const std::string& removeChar, std::vector<character>& characterList) {
	bool removed = false;

	// If element is found found, erase it 
	for (int i = characterList.size() - 1; i >= 0; i--) {
		if (characterList[i].name == removeChar){
			characterList.erase(characterList.begin() + i);
			break;
		}
	}

	// If a character is removed
	if (removed) {
		// Remove the unit from the characterList
		for (int i = characterList.size() - 1; i >= 0; i--) {
			for (int j = characterList[i].relationVec.size() - 1; j >= 0; j--) {
				if (characterList[i].relationVec[j].partner == removeChar)
					characterList[i].relationVec.erase(characterList[i].relationVec.begin() + j);
			}
		}
	}

	return;
}

void interactions::deleteUnit(const std::string& removeUnit, std::vector<character>& characterList, std::vector<unit>& unitList) {
	bool removed = false;

	// If element is found found, erase it 
	for (int i = unitList.size() - 1; i >= 0; i--) {
		if (unitList[i].name == removeUnit) {
			unitList.erase(unitList.begin() + i);
			removed = true;
			break;
		}
	}

	// If a unit is removed
	if (removed) {
		// Remove the unit from the characterList
		for (int i = characterList.size() - 1; i >= 0; i--) {
			if (characterList[i].member == removeUnit)
				characterList[i].member = "None";
		}

		// Remove the unit from the unitList
		for (int i = unitList.size() - 1; i >= 0; i--) {
			if (unitList[i].member == removeUnit)
				unitList[i].member = "None";

			for (int j = unitList[i].relationVec.size() - 1; j >= 0; j--) {
				if (unitList[i].relationVec[j].partner == removeUnit)
					unitList[i].relationVec.erase(unitList[i].relationVec.begin() + j);
			}
		}
	}

	return;
}