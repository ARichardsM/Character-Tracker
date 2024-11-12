#include "Tracker.h"

/*
	Unit Scripts
*/

std::string unit::output() const {
	std::string returnStr;

	returnStr += "Name: " + name + "\n";
	returnStr += "Rank: " + unitRankings[rank] + "\n";
	returnStr += "Member: " + member + "\n";
	for (std::string aspect : aspects)
		returnStr += "Aspect: " + aspect + "\n";
	for (tagFeature relation : relationVec)
		returnStr += "Relation: " + relation.returnFeat() + "\n";

	return returnStr;
}

void unit::addFeature(const std::string& featString, std::vector<std::string>& history) {
	// Attempt to split the input string by delims
	std::vector<std::string> feat = input::splitDelim(featString);

	// Rank: Set the rank to [1]'s integer equivalent
	if (feat[0] == "Rank") {
		// Search for rank [1] in the character rankings
		int rankIt = simpleFind::find(unitRankings, feat[1]);

		// Assign the rank if it exists, otherwise stay unassigned
		rank = std::max(0, rankIt);
	}
	else
		entity::addFeature(featString, history);
}