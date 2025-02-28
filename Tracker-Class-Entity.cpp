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
}

std::string feature::returnFeat() {
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

		// End the tag and string with the description
		returnVal += "> " + desc;
	}
	else
		// End the string with the description
		returnVal += " - " + desc;

	// Return the string
	return returnVal;
}

