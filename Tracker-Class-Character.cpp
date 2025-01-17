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

	// If the input cannot split
	if (feat.size() == 1) {
		// If no history has been added previously
		if (historyIndex == -1) {
			// Add a new history entry and note the index
			historyIndex = history.size();
			history.push_back(featString + "\n");
		}
		// Else add to history
		else {
			history[historyIndex] += featString + "\n";
		}
	}
	// Rank: Set the rank to [1]'s integer equivalent
	else if (feat[0] == "Rank") {
		// Search for rank [1] in the character rankings
		int rankIt = simpleFind::find(characterRankings, feat[1]);

		// Assign the rank if it exists, otherwise stay unassigned
		rank = std::max(0, rankIt);
	}
	// Relation: Add character name [1] to the relation array with a descriptor [END] ([2...End-1] are tags if available)
	else if (feat[0] == "Relation") {
		// Create a temporary feature for the relation
		tagFeature newRelation;

		// Create a variable for possible tags
		std::vector<std::string> relTags;

		switch (feat.size()) {
		case 1:
			break;
		case 2:
			newRelation.name = feat[1];
			newRelation.desc = "Unknown Relation";
			break;
		case 3:
			newRelation.name = feat[1];
			newRelation.desc = feat[2];
			break;
		default:
			newRelation.name = feat[1];
			relTags = input::splitDelim(feat[2], { ", ", ",", " , ", " ," });

			for (std::string tag : relTags) {
				newRelation.tags.push_back(tag);
			}

			newRelation.desc = feat.back();
			break;
		}

		// Push the feature into the relation array
		relations.push_back(newRelation);
	}
	else
		entity::addFeature(featString);
}