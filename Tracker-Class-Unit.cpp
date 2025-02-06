#include "Tracker.h"

/*
	Unit Scripts
*/

std::string unit::output() const {
	std::string returnStr;

	returnStr += "Name: " + name + "\n";
	returnStr += "Rank: " + GroupList.ranks[rank] + "\n";
	returnStr += "Member: " + member + "\n";
	for (std::string aspect : aspects)
		returnStr += "Aspect: " + aspect + "\n";

	return returnStr;
}

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