#include "Tracker.h"

/*
	Entity Scripts
*/

void entity::addFeature(const std::string& featString) {
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
		{
			tagFeature newRelation;
			newRelation.name = feat[1];
			newRelation.desc = "Unknown Relation";
			relationVec.push_back(newRelation);

			break;
		}
		case 3:
		{
			tagFeature newRelation;
			newRelation.name = feat[1];
			newRelation.desc = feat[2];
			relationVec.push_back(newRelation);
			break;
		}
		}
	}
}

void entity::addFeature(const std::string& featString, std::vector<std::string>& history) {
	// Attempt to split the input string by delims
	std::vector<std::string> feat = input::splitDelim(featString);

	// If the input cannot split
	if (feat.size() == 1) {
		// If no history has been added previously
		if (historyInd == -1) {
			// Add a new history entry and note the index
			historyInd = history.size();
			history.push_back(featString + "\n");
		}
		// Else add to history
		else {
			history[historyInd] += featString + "\n";
		}
	}
	// Else add the feature normally
	else {
		entity::addFeature(featString);
	}
}

std::string entity::feature::returnFeat() {
	// Start the string with the partner's name
	std::string returnVal = name;

	// End the string with the description
	returnVal += " - " + desc;

	// Return the string
	return returnVal;
}

std::string entity::tagFeature::returnFeat() {
	// Start the string with the partner's name
	std::string returnVal = name;

	// If the relation has tags
	if (!tags.empty()) {
		// Add the first tag
		returnVal += " <" + tags[0];

		// Add any subsequent tags
		for (std::string tag : std::vector<std::string>(tags.begin() + 1, tags.end())) {
			returnVal += "," + tag;
		}

		// Close out the tags
		returnVal += ">";
	}

	// End the string with the description
	returnVal += " - " + desc;

	// Return the string
	return returnVal;
}

