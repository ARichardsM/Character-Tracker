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
			relTags = input::splitDelim(feat[2], {", ", ",", " , ", " ,"});

			for (std::string tag: relTags) {
				newRelation.tags.push_back(tag);
			}

			newRelation.desc = feat.back();
			break;
		}

		// Push the feature into the relation array
		relations.push_back(newRelation);
	}
}

void entity::addFeature(const std::string& featString, std::vector<std::string>& history) {
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

		// End the tag and string with the description
		returnVal += "> " + desc;
	}
	else
		// End the string with the description
		returnVal += " - " + desc;

	// Return the string
	return returnVal;
}

