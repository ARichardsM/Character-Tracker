#include "Tracker.h"

/*
* Simple Find Namespace Functions
*
*/

int simpleFind::find(const std::vector<character>& arr, const std::string& val) {
	// Initialize Variables
	std::vector<std::string> names;

	// Convert to strings
	for (character chara : arr)
		names.push_back(chara.name);

	// Return Array Simple Find
	return find(names, val);
}

int simpleFind::find(const std::vector<unit>& arr, const std::string& val) {
	// Initialize Variables
	std::vector<std::string> names;

	// Convert to strings
	for (unit uni : arr)
		names.push_back(uni.name);

	// Return Array Simple Find
	return find(names, val);
}

/*
* Rules Namespace Functions
* 
*/

std::vector<std::string> rules::genRules(const std::vector<std::string>& crewNames) {
	// Declare Variables
	std::vector<std::string> rulesList = {};
	bool cont = true;

	// Until the user calls 'Done'
	while (cont) {
		// If there are rules in the rules list
		if (rulesList.size() != 0) {
			// Print out the rules
			std::cout << "Current Rules\n";
			for (std::string rule : rulesList)
				std::cout << rule << "\n";

		}

		// Prompt the user
		switch (support::prompt("Select", { "Done", "Add Rule", "Remove Rule" })) {
		case 1:
			// Break the while loop
			cont = false;
			break;
		case 2:
		{
			// Declare the variable for all possible rules
			std::vector<std::string> possibleRules = {};

			// If the limit by entity was set to crew
			if (find(rulesList.begin(), rulesList.end(), "Only:Crew") != rulesList.end()) {
				for (std::string rank : unitRankings) {
					// If the rank is not already in the rules list, add it to the possible rules
					if (find(rulesList.begin(), rulesList.end(), "Ranking:" + rank) == rulesList.end())
						possibleRules.push_back("Ranking:" + rank);
				}
			}
			// If the limit by entity was set to character
			else if (find(rulesList.begin(), rulesList.end(), "Only:Character") != rulesList.end()) {
				for (std::string rank : characterRankings) {
					// If the rank is not already in the rules list, add it to the possible rules
					if (find(rulesList.begin(), rulesList.end(), "Ranking:" + rank) == rulesList.end())
						possibleRules.push_back("Ranking:" + rank);
				}
			}
			else
				// Add a rule to limit by entity type
				possibleRules.insert(possibleRules.end(), { "Only:Unit", "Only:Character" });

			// If there are no member rules currently in the rules list
			if (std::find_if(rulesList.begin(), rulesList.end(), [](const std::string& str)
				{ return str.find("Member") != std::string::npos; }) == rulesList.end()) {

				// Add a rule to limit by membership
				for (std::string crew : crewNames)
					possibleRules.push_back("Member:" + crew);
			}

			// Prompt for a rule selection
			int selection = support::prompt("Select a Rule to Add", possibleRules);

			// Add the selected rule to the rules list
			if (selection != -1)
				rulesList.push_back(possibleRules[selection - 1]);
			break;
		}
		case 3:
		{
			// If the rules list is empty, do nothing
			if (rulesList.size() == 0)
				break;

			// Prompt for a rule selection
			int selection = support::prompt("Select a Rule to Remove", rulesList) - 1;

			// If the selected rule is one of the `Only` rules
			if (rulesList[selection].find("Only:") != std::string::npos) {
				// Remove the selected rule
				rulesList.erase(rulesList.begin() + selection);

				// Remove all `Ranking` rules
				for (int i = rulesList.size() - 1; i >= 0; i--) {
					if (rulesList[i].find("Ranking:") != std::string::npos)
						rulesList.erase(rulesList.begin() + i);
				}
			}
			else
				// Remove the selected rule
				rulesList.erase(rulesList.begin() + selection);

			break;
		}
		}
	}

	// Return the list of rules
	return rulesList;
}

void rules::filterRules(const std::vector<std::string>& rulesList, std::vector<character>& characterList, std::vector<unit>& unitList) {
	// Declare variable for holding entity information
	std::vector<std::vector<std::string>> possibleEntities = {};
	std::vector<std::string> possibleNames = {};

	// Pull all neccessary entity information
	for (character ent : characterList) {
		possibleNames.push_back(ent.name);
		possibleEntities.push_back({ ent.name, characterRankings[ent.rank], ent.member, "Character" });
	}

	for (unit ent : unitList) {
		possibleNames.push_back(ent.name);
		possibleEntities.push_back({ ent.name, unitRankings[ent.rank], ent.member, "Unit" });
	}

	// For each of the rules
	for (std::string rule : rulesList) {
		// Declare variable to note the filtered entities
		std::vector<bool> filtEnti = {};

		// For every possible entity
		for (std::vector<std::string> ent : possibleEntities) {
			std::string ruleType = rule.substr(0, rule.find(":"));
			// 'Only' Rules
			if (ruleType == "Only") {
				// Verify the unit type
				if (rule.substr(rule.find(":") + 1) == ent[3])
					filtEnti.push_back(false);
				else
					filtEnti.push_back(true);
			}

			// 'Ranking' Rules
			if (ruleType == "Ranking") {
				// Verify the ranking
				if (rule.substr(rule.find(":") + 1) == ent[1])
					filtEnti.push_back(false);
				else
					filtEnti.push_back(true);
			}

			// 'Member' Rules
			if (ruleType == "Member") {
				// Verify the membership
				if (rule.substr(rule.find(":") + 1) == ent[2])
					filtEnti.push_back(false);
				// Treat unit as a member of themselves
				else if (rule.substr(rule.find(":") + 1) == ent[0])
					filtEnti.push_back(false);
				else
					filtEnti.push_back(true);
			}
		}

		// Filter out entities that don't follow the current rule
		for (int i = filtEnti.size() - 1; i >= 0; i--) {
			if (filtEnti[i]) {
				possibleNames.erase(possibleNames.begin() + i);
				possibleEntities.erase(possibleEntities.begin() + i);
			}
		}

	}

	for (int i = characterList.size() - 1; i >= 0; i--) {
		// If the character's name can't be found in possibleNames, remove it from the Vector
		if (find(possibleNames.begin(), possibleNames.end(), characterList[i].name) == possibleNames.end())
			characterList.erase(characterList.begin() + i);
	}

	for (int i = unitList.size() - 1; i >= 0; i--) {
		// If the unit's name can't be found in possibleNames, remove it from the Vector
		if (find(possibleNames.begin(), possibleNames.end(), unitList[i].name) == possibleNames.end())
			unitList.erase(unitList.begin() + i);
	}
}