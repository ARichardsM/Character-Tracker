#include "Tracker.h"

/*
* Output Namespace Functions
*
*/



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

void output::printRank(std::vector<character> characterList, unitList unitData) {
	// Declare a variable to track the previously printed rank
	int prevRank = -1;

	// Sort characters in order of rank integer
	std::sort(characterList.begin(), characterList.end(),
		[](character a, character b) {
			return a.rank < b.rank;
		});

	// Sort units in order of rank integer
	std::sort(unitData.units.begin(), unitData.units.end(),
		[](unit a, unit b) {
			return a.rank < b.rank;
		});

	// For each unit
	for (unit uni : unitData.units) {
		// If the rank has changed, print a new header
		if (prevRank != uni.rank) {
			std::cout << "\n" << unitData.ranks[uni.rank] << "\n";
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
			std::cout << "\n" << CharacterList.ranks[chara.rank] << "\n";
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




void output::logListsMD(const std::vector<character>& characterList, const std::vector<unit>& unitList, const std::vector<std::string>& history) {
	// Variables for output file
	std::ofstream outFileChar("characterMD.md");

	for (character chara : characterList) {
		// Write the content from the character
		outFileChar << "# " << chara.name << "\n";
		outFileChar << chara.output();

		if (chara.historyIndex != -1)
			outFileChar << history[chara.historyIndex];
	}

	// Close the Out File
	outFileChar.close();

	// Variables for output file
	std::ofstream outFileUnit("unitMD.md");

	for (unit unit : unitList) {

		// Write the content from the unit
		outFileUnit << "# " << unit.name << "\n";
		outFileUnit << unit.output();
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
		std::cout << "Rank: " << CharacterList.ranks[acter.rank] << "\n";

		// Record the character's aspects and relations
		std::vector<std::string> fullAspects = acter.aspects;
		std::vector<std::vector<std::string>> fullRelations;
		for (entity::tagFeature rel : acter.relations) {
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
	// Prepare the standard delim list
	std::vector<std::string> delimList = { ": ", " - ", " < "," > ", "> " , " <" };

	// Pass and return
	return splitDelim(input, delimList);
}

std::vector<std::string> input::splitDelim(std::string input, std::vector<std::string> delimList) {
	// Variables for delims found position and tracking progress
	std::vector<int> delimPos;
	bool isRunning = true;

	// Variable for the return
	std::vector<std::string> splitLine;

	// Split until a delim cannot be found
	while (isRunning) {
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
		if (delimPos[minEle] == input.size()){
			isRunning = false;
			break;
		}

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
			unitList[unitIn].addFeature(line);
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
			unitList[unitIn].addFeature(line);
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