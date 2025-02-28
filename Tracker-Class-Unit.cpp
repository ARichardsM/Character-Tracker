#include "Tracker.h"

void recPrint(const std::vector<unit>& unitList, const std::vector<std::string>& unitRanks, const std::vector<character>& characterList, const std::vector<std::vector<std::string>>& unitDets, int thisUnitInd, int depth) {
	// Print blanks for indentation
	for (int i = 0; i < depth; i++)
		std::cout << "    ";

	// Print the name and rank
	std::cout << "[" << unitRanks[unitList[thisUnitInd].rank] << "] ";
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
		recPrint(unitList, unitRanks, characterList, unitDets, i, depth + 1);
	}

	// Print any character that belongs to this unit
	for (character currChar : characterList) {
		if (currChar.member != unitList[thisUnitInd].name)
			continue;

		for (int i = 0; i < depth + 1; i++)
			std::cout << "    ";

		std::cout << "[" << CharacterList.ranks[currChar.rank] << "] ";
		std::cout << currChar.name << "\n";
	}

	return;
}

/*
	Unit Scripts
*/

std::string unit::output() const {
	std::string returnStr;

	returnStr += "Name: " + name + "\n";
	//returnStr += "Rank: " + GroupList.ranks[rank] + "\n";
	returnStr += "Member: " + member + "\n";
	for (std::string aspect : aspects)
		returnStr += "Aspect: " + aspect + "\n";

	return returnStr;
}

/*
void unit::addFeature(const std::string& featString) {
	// Attempt to split the input string by delims
	std::vector<std::string> feat = input::splitDelim(featString);

	// Rank: Set the rank to [1]'s integer equivalent
	if (feat[0] == "Rank") {
		// Search for rank [1] in the character rankings
		int rankIt = simpleFind::find(GroupList.ranks, feat[1]);

		// Assign the rank if it exists, otherwise stay unassigned
		rank = std::max(0, rankIt);
	}
	else
		entity::addFeature(featString);
}
*/

/*
	Unit List Class Scripts
*/

std::string unitList::output(const int& select) const {
	// Initialize string variable
	std::string returnStr;

	// Return if select is out of range
	if (select > units.size())
		return returnStr;

	// Append the output to the returned string
	returnStr += "Name: " + units[select].name + "\n";
	returnStr += "Rank: " + ranks[units[select].rank] + "\n";
	returnStr += "Member: " + units[select].member + "\n";

	// Return string
	return returnStr;
}

void unitList::addFeature(const int& select, const std::string& featString) {
	// Attempt to split the input string by delims
	std::vector<std::string> feat = input::splitDelim(featString);

	// Rank: Set the rank to [1]'s integer equivalent
	if (feat[0] == "Rank") {
		// Search for rank [1] in the character rankings
		int rankIt = simpleFind::find(ranks, feat[1]);

		// Assign the rank if it exists, otherwise stay unassigned
		units[select].rank = std::max(0, rankIt);
	}
	else
		units[0].entity::addFeature(featString);
}

void unitList::fullPrint(const std::vector<character>& characterList) {
	// Variables
	std::vector<std::vector<std::string>> unitDets;
	std::vector<std::vector<std::string>> unitInfo;
	std::vector<std::string> unitNames;
	std::vector<int> unitSizes;

	// Store the unit's name and necessary information and initialize the units' size
	for (unit unit : units) {
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
	for (int i = 0; i < units.size(); i++) {
		// Try to find it's unit membership
		auto unitMem = find(unitNames.begin(), unitNames.end(), units[i].name);

		// If it doesn't belongs to a unit
		if (units[i].member == "None") {
			// Recusive print it and it's members
			recPrint(units, ranks, characterList, unitDets, i, 0);
		}
	}

	// Print a newline for spacing
	std::cout << "\n";
}