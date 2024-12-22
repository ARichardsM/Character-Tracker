#include "Tracker.h"

/*
* Modify Relations Namespace Functions
*
*/

void modifyRelations::addMissingRelations(std::vector<character>& characterList, std::vector<unit>& unitList) {
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
		for (entity::tagFeature relation : characterList[i].relations) {
			// Find the relation's name in `names`
			auto relPos = find(names.begin(), names.end(), relation.name);
			int intPos = std::distance(names.begin(), relPos);

			// If the relation exists
			if (relPos != names.end()) {
				// Modify the relation matrix
				relationMatrix[i][intPos] = true;
				relationMatrix[intPos][i] = true;
			}
		}
	}

	// For each unit's relation
	for (int i = 0; i < unitList.size(); i++) {
		for (entity::tagFeature relation : unitList[i].relations) {
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
		for (entity::tagFeature relation : characterList[i].relations) {
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
				characterList[i].relations.push_back(newRel);
			}
		}
	}

	// For each unit
	for (int i = 0; i < unitList.size(); i++) {
		// Adjust i to accomdate the characters
		int adjI = i + characterList.size();

		// Record the unit's relation names
		std::vector<std::string> relateNames;
		for (entity::tagFeature relation : unitList[i].relations) {
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
				unitList[i].relations.push_back(newRel);
			}
		}
	}
}

void modifyRelations::modGroups(std::vector<unit>& unitList) {
	// Declare Variables
	int selectedUnitA, selectedUnitB;
	std::vector<std::string> unitNames, unitPossibles, unitRelations;

	// Prepare the Unit Name Vector
	for (unit currentUnit : unitList)
		unitNames.push_back(currentUnit.name);

	// Prompt for the first unit
	selectedUnitA = support::prompt("Select First Group", unitNames) - 1;

	// Prepare the Unit Name Vector
	for (entity::tagFeature currentRelation : unitList[selectedUnitA].relations)
		unitRelations.push_back(currentRelation.name);

	// Prompt for the second unit
	selectedUnitB = support::prompt(("First Group: " + unitNames[selectedUnitA] + "\nSelect Second Group"), unitNames) - 1;

	return;
}

void modifyRelations::modCharacters(std::vector<character>& characterList) {
	return;
}