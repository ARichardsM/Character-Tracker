#include "Tracker.h"

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
	characterList[select].fullprint(unitList);
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
	std::string printNum;
	int entNum, entType;

	std::srand(std::time(nullptr));

	do {
		std::cout << "How Many Entities Should Be Output? \t";
		std::cin >> printNum;
	} while (printNum.find_first_not_of("1234567890") != std::string::npos);

	entNum = std::stoi(printNum);

	if (characterList.size() == 0) {
		entType = 2;
	}
	else if (unitList.size() == 0) {
		entType = 1;
	}
	else {
		entType = support::prompt("Which Type of Entity?", { "Character", "Crew" });
	}

	switch (entType) {
	case 1:
	{
		if (entNum > characterList.size())
			entNum = characterList.size();

		std::vector<bool> arr(characterList.size(), false);

		for (int i = 0; i < entNum; i++) {
			int random_value = std::rand() % characterList.size();

			while (arr[random_value]) {
				random_value = random_value + 1;

				if (random_value >= arr.size())
					random_value = 0;
			}

			arr[random_value] = true;

			
		}

		// Print all characters
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
		if (entNum > unitList.size())
			entNum = unitList.size();

		std::vector<bool> arr(unitList.size(), false);

		for (int i = 0; i < entNum; i++) {
			int random_value = std::rand() % unitList.size();

			while (arr[random_value]) {
				random_value = random_value + 1;

				if (random_value >= arr.size())
					random_value = 0;
			}

			arr[random_value] = true;


		}

		// Print all units
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