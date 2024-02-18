#include "Tracker.h"

/*
	Entity Scripts
*/

void entity::addFeature(std::string featString) {
	// Split the input string by delims
	std::vector<std::string> feat = input::splitDelim(featString);

	// Name: Set the name to [1]
	if (feat[0] == "Name") {
		name = feat[1];
	}
	// Member: Set the member to [1]
	else if (feat[0] == "Member") {
		member = feat[1];
	}
	// Aspect: Add [1] to the aspect array
	else if (feat[0] == "Aspect") {
		aspects.push_back(feat[1]);
	}
	// Relation: Add [1] to the relation array with a descriptor ([2] if available)
	else if (feat[0] == "Relation") {
		switch (feat.size()) {
		case 2:
			relations.push_back({ feat[1], "Unknown Relation" });
			break;
		case 3:
			relations.push_back({ feat[1], feat[2] });
			break;
		}
	}
}

/*
	Character Scripts
*/

character::character(const std::string& file) {
	// Set the name to be the file's stem
	name = file;

	// Access the character's file
	std::ifstream inputFile;
	inputFile.open("Characters/" + file + ".txt");

	// For each line
	std::string line;
	while (getline(inputFile, line)) {
		// Add the feature
		addFeature(line);
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

void character::addFeature(std::string featString) {
	// Split the input string by delims
	std::vector<std::string> feat = input::splitDelim(featString);

	// Rank: Set the rank to [1]'s integer equivalent
	if (feat[0] == "Rank") {
		// Search for rank [1] in the character rankings
		auto rankIter = find(characterRankings.begin(), characterRankings.end(), feat[1]);

		// Assign the rank if it exists, otherwise stay unassigned
		if (rankIter != characterRankings.end())
			rank = std::distance(characterRankings.begin(), rankIter);
	}
	else
		entity::addFeature(featString);
}

/*
	Unit Scripts
*/

unit::unit(const std::string& file) {
	// Set the unit's name
	name = file;

	// Access the unit's file
	std::ifstream inputFile;
	inputFile.open("Units/" + file + ".txt");

	// For each line
	std::string line;
	while (getline(inputFile, line)) {
		// Add the feature
		addFeature(line);
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

void unit::addFeature(std::string featString) {
	// Split the input string by delims
	std::vector<std::string> feat = input::splitDelim(featString);

	// Rank: Set the rank to [1]'s integer equivalent
	if (feat[0] == "Rank") {
		// Search for rank [1] in the character rankings
		auto rankIter = find(unitRankings.begin(), unitRankings.end(), feat[1]);

		// Assign the rank if it exists, otherwise stay unassigned
		if (rankIter != unitRankings.end())
			rank = std::distance(unitRankings.begin(), rankIter);
	}
	else
		entity::addFeature(featString);
}