#include "Tracker.h"

void missingEntity::refacChar(const std::string& missingChar, std::vector<character>& characterList) {
	// Prompt for selection
	int selection = support::prompt("The character " + missingChar + " is missing", { "Rename", "Delete" });

	// Refactor based on selection
	switch (selection) {
	case 1:
		renameChar(missingChar, characterList);
		break;
	case 2:
		deleteChar(missingChar, characterList);
		break;
	}

	return;
}

void missingEntity::refacUnit(const std::string& missingUnit, std::vector<character>& characterList, std::vector<unit>& unitList) {
	// Prompt for selection
	int selection = support::prompt("The unit " + missingUnit + " is missing", { "Rename", "Delete", "Split" });

	// Refactor based on selection
	switch (selection) {
	case 1:
		renameUnit(missingUnit, characterList, unitList);
		break;
	case 2:
		deleteUnit(missingUnit, characterList, unitList);
		break;
	case 3:
		splitUnit(missingUnit, characterList, unitList);
		break;
	}

	return;
}

void missingEntity::renameChar(const std::string& missingChar, std::vector<character>& characterList) {
	// Declare name variables
	std::vector<std::string> possibleNames;

	// Append all character names to names
	for (character chara : characterList) {
		possibleNames.push_back(chara.name);
	}

	// Prompt for the true names
	int nameLoc = support::prompt("What is the true name of " + missingChar, possibleNames) - 1;

	// For every character's relation
	for (character& chara : characterList) {
		for (entity::tagFeature& relation : chara.relationVec) {
			// If the missing char's name was found, change it for the true name
			if (relation.name == missingChar)
				relation.name = possibleNames[nameLoc];
		}
	}
}

void missingEntity::renameUnit(const std::string& missingUnit, std::vector<character>& characterList, std::vector<unit>& unitList) {
	// Declare name variables
	std::vector<std::string> possibleNames;

	// Append all unit names to names
	for (unit unit : unitList) {
		possibleNames.push_back(unit.name);
	}

	// Prompt for the true names
	int nameLoc = support::prompt("What is the true name of " + missingUnit, possibleNames) - 1;

	// For every character's member
	for (character& chara : characterList) {
		// If the missing unit's name was found, change it for the true name
		if (chara.member == missingUnit)
			chara.member = possibleNames[nameLoc];
	}

	// For every unit
	for (unit& uni : unitList) {
		// If the missing unit's name is the member, change it for the true name
		if (uni.member == missingUnit)
			uni.member = possibleNames[nameLoc];

		// For each of the unit's relations
		for (entity::tagFeature& relation : uni.relationVec) {
			// If the missing unit's name was found, change it for the true name
			if (relation.name == missingUnit)
				relation.name = possibleNames[nameLoc];
		}
	}
}

void missingEntity::splitUnit(const std::string& missingUnit, std::vector<character>& characterList, std::vector<unit>& unitList) {
	std::vector<int> freeChars;
	std::vector<std::string> possibleNames;
	std::vector<int> newNames;

	// Append all unit names to names
	for (unit unit : unitList) {
		possibleNames.push_back(unit.name);
	}

	// Note all characters the are part of the unit
	for (character& chara : characterList) {
		if (chara.member == missingUnit) {
			// Prompt for a new unit
			int select = support::prompt("What unit does " + chara.name + " now belong to?", possibleNames) - 1;

			// Change the character's unit
			chara.member = possibleNames[select];
		}
	}

	for (unit& curUnit : unitList) {
		if (curUnit.member == missingUnit) {
			// Prompt for a new unit
			int select = support::prompt("What unit does " + curUnit.name + " now belong to?", possibleNames) - 1;

			// Change the unit's unit
			if (possibleNames[select] == curUnit.name) {
				curUnit.member = "None";
			}
			else {
				curUnit.member = possibleNames[select];
			}
		}
	}

}

void missingEntity::deleteChar(const std::string& missingChar, std::vector<character>& characterList) {
	// If element is found found, erase it 
	for (int i = characterList.size() - 1; i >= 0; i--) {
		if (characterList[i].name == missingChar) {
			characterList.erase(characterList.begin() + i);
			break;
		}
	}

	// Remove the unit from the characterList
	for (int i = characterList.size() - 1; i >= 0; i--) {
		for (int j = characterList[i].relationVec.size() - 1; j >= 0; j--) {
			if (characterList[i].relationVec[j].name == missingChar)
				characterList[i].relationVec.erase(characterList[i].relationVec.begin() + j);
		}
	}

	return;
}

void missingEntity::deleteUnit(const std::string& missingUnit, std::vector<character>& characterList, std::vector<unit>& unitList) {
	// If element is found found, erase it 
	for (int i = unitList.size() - 1; i >= 0; i--) {
		if (unitList[i].name == missingUnit) {
			unitList.erase(unitList.begin() + i);
			break;
		}
	}

	// Remove the unit from the characterList
	for (int i = characterList.size() - 1; i >= 0; i--) {
		if (characterList[i].member == missingUnit)
			characterList[i].member = "None";
	}

	// Remove the unit from the unitList
	for (int i = unitList.size() - 1; i >= 0; i--) {
		if (unitList[i].member == missingUnit)
			unitList[i].member = "None";

		for (int j = unitList[i].relationVec.size() - 1; j >= 0; j--) {
			if (unitList[i].relationVec[j].name == missingUnit)
				unitList[i].relationVec.erase(unitList[i].relationVec.begin() + j);
		}
	}

	return;
}