#include "Tracker.h"

/*
* Output Namespace Functions
*
*/

void recPrint(const std::vector<unit>& unitList, const std::vector<character>& characterList, const std::vector<std::vector<std::string>>& unitDets, int thisUnitInd, int depth) {
	// Print blanks for indentation
	for (int i = 0; i < depth; i++)
		std::cout << "    ";

	// Print the name and rank
	std::cout << "[" << unitRankings[unitList[thisUnitInd].rank] << "] ";
	std::cout << unitList[thisUnitInd].name;

	// Print the size and max size
	for (std::vector<std::string> currUnit : unitDets) {
		if (currUnit[0] == unitList[thisUnitInd].name) {
			std::cout << " (" << currUnit[1] << "/";
			std::cout << (3 * pow(2, unitList[thisUnitInd].rank - 1)) << ")\n";
		}
	}

	// Print any units that belongs to this unit
	for (int i = 0; i < unitList.size(); i++) {
		if (unitList[i].member != unitList[thisUnitInd].name)
			continue;
		recPrint(unitList, characterList, unitDets, i, depth + 1);
	}

	// Print any character that belongs to this unit
	for (character currChar : characterList) {
		if (currChar.member != unitList[thisUnitInd].name)
			continue;

		for (int i = 0; i < depth + 1; i++)
			std::cout << "    ";

		std::cout << "[" << characterRankings[currChar.rank] << "] ";
		std::cout << currChar.name << "\n";
	}

	return;
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
	output::charPrintFull(characterList[select], unitList);
}


void output::printFullUnit(const std::vector<character>& characterList, const std::vector<unit>& unitList) {
	// Variables
	std::vector<std::vector<std::string>> unitDets;
	std::vector<std::vector<std::string>> unitInfo;
	std::vector<std::string> unitNames;
	std::vector<int> unitSizes;

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

	// Store the unit's name via sorted order and create a character holder
	for (std::vector<std::string> unit : unitInfo) {
		unitNames.push_back(unit[0]);
		unitDets.push_back({ unit[0], "0" });
	}

	// For each character
	for (character character : characterList) {
		// Try to find it's unit membership
		auto charMem = find(unitNames.begin(), unitNames.end(), character.member);

		// If it belongs to a unit, add to the unit's size
		if (charMem != unitNames.end()) {
			unitSizes[std::distance(unitNames.begin(), charMem)] += 1;
		}
	}

	// For each unit
	for (int i = 0; i < unitInfo.size(); i++) {
		// Try to find it's unit membership
		auto unitMem = find(unitNames.begin(), unitNames.end(), unitInfo[i][2]);

		// If it belongs to a unit, add it's size to the unit's size
		if (unitMem != unitNames.end())
			unitSizes[std::distance(unitNames.begin(), unitMem)] += unitSizes[i];

		unitDets[i][1] = std::to_string(unitSizes[i]);
	}

	// For each unit
	for (int i = 0; i < unitList.size(); i++) {
		// Try to find it's unit membership
		auto unitMem = find(unitNames.begin(), unitNames.end(), unitList[i].name);

		// If it doesn't belongs to a unit
		if (unitList[i].member == "None") {
			// Recusive print it and it's members
			recPrint(unitList, characterList, unitDets, i, 0);
		}
	}

	// Print a newline for spacing
	std::cout << "\n";
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

void output::multiPrint(const std::vector<character>& characterList, const std::vector<unit>& unitList) {
	// Initialize Variables
	std::string printNum;
	int entNum, entType;

	// Initialize Random
	std::srand(std::time(nullptr));

	// Determine number of entities to print
	do {
		std::cout << "How Many Entities Should Be Output? \t";
		std::cin >> printNum;
	} while (printNum.find_first_not_of("1234567890") != std::string::npos);

	entNum = std::stoi(printNum);

	// Determine whether to print characters or units
	if (characterList.size() == 0) {
		entType = 2;
	}
	else if (unitList.size() == 0) {
		entType = 1;
	}
	else {
		entType = support::prompt("Which Type of Entity?", { "Character", "Crew" });
	}

	// Based on the entity being printed
	switch (entType) {
	case 1:
	{
		// Bound characters to print
		if (entNum > characterList.size())
			entNum = characterList.size();

		// Prepare bool array of characters to print
		std::vector<bool> arr(characterList.size(), false);

		// For the number of characters to print
		for (int i = 0; i < entNum; i++) {
			// Select a random character
			int random_value = std::rand() % characterList.size();

			// If the character is going to be printed already
			while (arr[random_value]) {
				// Increment the selection value
				random_value = random_value + 1;

				// Bound the selection value
				if (random_value >= arr.size())
					random_value = 0;
			}

			// Mark the character to be printed
			arr[random_value] = true;
		}

		// Print all marked characters
		std::cout << "Characters" << "\n";
		for (int i = 0; i < characterList.size(); i++) {
			if (arr[i]) {
				std::cout << characterList[i].output();
				std::cout << "\n";
			}
			
		}
		break;
	}
	case 2:
	{
		// Bound units to print
		if (entNum > unitList.size())
			entNum = unitList.size();

		// Prepare bool array of units to print
		std::vector<bool> arr(unitList.size(), false);

		// For the number of units to print
		for (int i = 0; i < entNum; i++) {
			// Select a random unit
			int random_value = std::rand() % unitList.size();

			// If the unit is going to be printed already
			while (arr[random_value]) {
				// Increment the selection value
				random_value = random_value + 1;

				// Bound the selection value
				if (random_value >= arr.size())
					random_value = 0;
			}

			// Mark the unit to be printed
			arr[random_value] = true;
		}

		// Print all marked units
		std::cout << "Units" << "\n";
		for (int i = 0; i < unitList.size(); i++) {
			if (arr[i]) {
				std::cout << unitList[i].output();
				std::cout << "\n";
			}

		}

		break;
	}
	}
}

void output::charPrintFull(const character& acter, const std::vector<unit>& unitList) {
	// If not a member, simply print
	if (acter.member == "None")
		std::cout << acter.output();
	else {
		// Print Name and Rank
		std::cout << "Name: " << acter.name << "\n";
		std::cout << "Rank: " << characterRankings[acter.rank] << "\n";

		// Record the character's aspects and relations
		std::vector<std::string> fullAspects = acter.aspects;
		std::vector<std::vector<std::string>> fullRelations;
		for (entity::tagFeature rel : acter.relationVec) {
			std::vector<std::string> relString;
			relString.push_back(rel.name);
			for (std::string tag : rel.tags)
				relString.push_back(tag);
			relString.push_back(rel.desc);
			fullRelations.push_back(relString);
		}

		// Set next member and initilize the full member vector
		std::vector<std::string> fullMember;
		std::string nextMember = acter.member;

		// While a next member exists
		while (nextMember != "None") {

			// Check if the member exists
			if (simpleFind::find(unitList, nextMember) == -1)
				break;


			// Find the unit the entity belongs to
			for (unit unit : unitList) {
				if (unit.name == nextMember) {
					// Add the aspects, relations and membership
					fullAspects.insert(fullAspects.end(), unit.aspects.begin(), unit.aspects.end());
					fullMember.push_back(nextMember);
					std::vector<std::vector<std::string>> newRelations;
					for (entity::tagFeature rel : unit.relationVec) {
						std::vector<std::string> relString;
						relString.push_back(rel.name);
						for (std::string tag : rel.tags)
							relString.push_back(tag);
						relString.push_back(rel.desc);
						newRelations.push_back(relString);
					}
					fullRelations.insert(fullRelations.end(), newRelations.begin(), newRelations.end());

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
		std::cout << "Member: ";
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
* Input Namespace Functions
* 
*/

std::vector<std::string> input::splitDelim(std::string input) {
	// Variables for delims and their found position
	std::vector<std::string> delimList = { ": ", " - ", " > " };
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