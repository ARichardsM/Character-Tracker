#include "Tracker.h"

/*
	Unit Scripts
*/

void unit::print() const {
	std::cout << "Name: " << name << "\n";
	std::cout << "Rank: " << unitRankings[rank] << "\n";
	std::cout << "Member: " << member << "\n";
	for (std::string aspect : aspects)
		std::cout << "Aspect: " << aspect << "\n";
	for (relation relation : relationVec) {
		std::cout << "Relations: " << relation.returnRelation() << "\n";
	}
}

std::string unit::output() const {
	std::string returnStr;

	returnStr += "Name: " + name + "\n";
	returnStr += "Rank: " + unitRankings[rank] + "\n";
	returnStr += "Member: " + member + "\n";
	for (std::string aspect : aspects)
		returnStr += "Aspect: " + aspect + "\n";
	for (relation relation : relationVec) {
		returnStr += "Relation: " + relation.returnRelation() + "\n";
	}

	return returnStr;
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

void unit::addFeature(std::string featString, std::vector<std::string>& history) {
	// Attempt to split the input string by delims
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
		entity::addFeature(featString, history);
}