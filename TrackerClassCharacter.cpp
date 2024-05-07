#include "Tracker.h"

/*
	Character Scripts
*/

std::string character::output() const {
	std::string returnStr;

	returnStr += "Name: " + name + "\n";
	returnStr += "Rank: " + characterRankings[rank] + "\n";
	returnStr += "Member: " + member + "\n";
	for (std::string aspect : aspects)
		returnStr += "Aspect: " + aspect + "\n";
	for (relation relation : relationVec) {
		returnStr += "Relation: " + relation.returnRelation() + "\n";
	}

	return returnStr;
}

void character::fullprint(const std::vector<unit>& unitList) const {
	// If not a member, simply print
	if (member == "None")
		std::cout << output();
	else {
		// Print Name and Rank
		std::cout << "Name: " << name << "\n";
		std::cout << "Rank: " << characterRankings[rank] << "\n";

		// Record the character's aspects and relations
		std::vector<std::string> fullAspects = aspects;
		std::vector<std::vector<std::string>> fullRelations;
		for (relation rel : relationVec) {
			std::vector<std::string> relString;
			relString.push_back(rel.partner);
			for (std::string tag : rel.tags)
				relString.push_back(tag);
			relString.push_back(rel.desc);
			fullRelations.push_back(relString);
		}

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
					fullMember.push_back(nextMember);
					std::vector<std::vector<std::string>> newRelations;
					for (relation rel : unit.relationVec) {
						std::vector<std::string> relString;
						relString.push_back(rel.partner);
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

void character::addFeature(std::string featString, std::vector<std::string>& history) {
	// Attempt to split the input string by delims
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
		entity::addFeature(featString, history);
}