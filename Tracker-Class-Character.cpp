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
	for (tagFeature relation : relations) {
		returnStr += "Relation: " + relation.returnFeat() + "\n";
	}

	return returnStr;
}

void character::addFeature(std::string featString, std::vector<std::string>& history) {
	// Attempt to split the input string by delims
	std::vector<std::string> feat = input::splitDelim(featString);

	// Rank: Set the rank to [1]'s integer equivalent
	if (feat[0] == "Rank") {
		// Search for rank [1] in the character rankings
		int rankIt = simpleFind::find(characterRankings, feat[1]);

		// Assign the rank if it exists, otherwise stay unassigned
		rank = std::max(0, rankIt);
	}
	else
		entity::addFeature(featString, history);
}