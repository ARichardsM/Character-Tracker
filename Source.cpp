#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "Tracker.h"
#include "General.h"

using namespace std;
namespace fs = filesystem;

// Pull character and group information
void startUp(vector<unit>& unitList, vector<character>& charList, vector<string>& history) {
    // Pull `Character Files` from the `Characters` Directory
    fs::path charPath = fs::current_path() / "Characters";

    if (exists(charPath))
        for (const auto& entry : fs::directory_iterator(charPath))
            // Load the character
            input::loadChar(entry.path().filename().string(), charList, history);
    else
        cout << "'Characters' directory cannot be found.\n";

    // Pull `Unit Files` from the `Units` Directory
    fs::path unitPath = fs::current_path() / "Units";

    if (exists(unitPath))
        for (const auto& entry : fs::directory_iterator(unitPath))
            // Load the unit
            input::loadUnit(entry.path().filename().string(), unitList, history);
    else
        cout << "'Units' directory cannot be found.\n";

    // Declare variables
    set<string> setA, setB;

    // Verify the units
    setA = interactions::verifyMemberships(charList, unitList);

    setA.insert(setB.begin(), setB.end());

    // Verify the characters
    setB = interactions::verifyRelations(charList);

    // Report any missing entities
    for (string unitName : setA)
        cout << "The unit " << unitName << " cannot be found\n";

    for (string charName : setB)
        cout << "The character " << charName << " cannot be found\n";

    cout << "\n";

    // If there are missing entities
    if ((setA.size() != 0) || (setB.size() != 0)) {
        if (support::prompt("Refactor missing entities?", { "Yes", "No" }) == 1) {
            // Refactor missing units
            for (string unitName : setA)
                missingEntity::refacUnit(unitName, charList, unitList);

            // Refactor missing characters
            for (string charName : setB)
                missingEntity::refacChar(charName, charList);
        }
    }
}

// Read the parameter document
void readParameter(std::vector<std::vector<std::string>>& tags, std::vector<std::string>& characterRanks, std::vector<std::string>& groupRanks) {
    // Access the unit markdown file
    std::ifstream inputFile;
    inputFile.open("Parameter-Document.txt");

    // For each line
    std::string line;
    vector<std::string> parts;

    while (getline(inputFile, line)) {
        // Divide the line in parts based on common delims
        parts = support::splitByDelim(line);

        switch (parts.size()) {
        case 1:
            // Skip if the line can't be Split
            continue;
        case 2:
            // Determine if the input is a rank or a tag
            switch (simpleFind::find(parts[0], { "Character Ranks", "Group Ranks" })) {
            case -1:
                // Add to list of tags
                tags.push_back(parts);
                break;
            case 0:
                // Set character ranks
                characterRanks = support::splitByDelim(parts[1], { ", " });
                break;
            case 1:
                // Set group ranks
                groupRanks = support::splitByDelim(parts[1], { ", " });
                break;
            }
            break;
        }
    }
}

// Main function for all edit functions
void editFunc(unitList& unitData, vector<character>& charList) {
    // Declare variables
    bool cont = true;
    int select;

    while (cont) {
        select = support::prompt(
            "Select",
            { "Verify Unit Size", "Add Missing Relations", "Main Menu" }
        );

        switch (select) {
        case 1:
            // Verify the sizes of all units
            interactions::verifySizes(charList, unitData.units);
            cout << "\n";
            break;
        case 2:
            // Add any one-sided unit or character relations
            modifyRelations::addMissingRelations(charList, unitData.units);
            break;
        case 3:
            // Break the loop
            cont = false;
            break;
        }

    }

    // Exit 
    return;
}

// Main function for all print functions
void printFunc(unitList& unitData, vector<character>& charList, vector<string>& history) {
    // Declare variables
    bool cont = true;
    int select;

    while (cont) {
        select = support::prompt(
            "Select",
            { "Print (Screen)", "Write (File)", "Main Menu" }
        );

        switch (select) {
        case 1:
        {
            // Prompt user for the desired print
            int printSelectA = support::prompt("Apply A Filter?", { "Yes", "No" });
            int printSelectB = support::prompt("What Type Of Print?", { "Print All", "Print By Rank", "Random Full Print", "Print Multiple" });

            // Create temporary copies of the list
            vector<character> tempCharList = charList;
            vector<unit> tempUnitList = unitData.units;

            // Potentially apply a filter
            if (printSelectA == 1) {
                // Declare unit name variable
                vector<string> unitNames;

                // Append all unit names to unitNames
                for (unit unit : unitData.units) {
                    unitNames.push_back(unit.name);
                }

                // Generate the rules
                vector<string> rulesList = rules::genRules(unitNames);

                // Filter according to the rules
                rules::filterRules(rulesList, tempCharList, tempUnitList);
            }

            // Perform the specified print
            switch (printSelectB) {
            case 1:
                // Print all characters and units
                output::printAll(tempCharList, tempUnitList);

                break;
            case 2:
                // Print according to the ranks
                output::printRank(tempCharList, unitData);

                break;
            case 3:
                // Print according to the ranks
                output::printFull(tempCharList, tempUnitList);

                break;
            case 4:
                // Print according to the ranks
                output::multiPrint(tempCharList, tempUnitList);

                break;
            }

            break;
        }
        case 2:
        {
            // Prompt user for the desired write
            int writeSelect = support::prompt("Which Write?", { "[All] Markdown", "[All] File" });

            // Perform the specified write
            switch (writeSelect) {
            case 0:
                // Write all characters and units to markdown files
                output::logListsMD(charList, unitData.units, history);
                break;
            case 1:
                // Write all characters and units to their files
                interactions::writeToFile(charList, unitData.units);
                break;
            }

            break;
        }
        case 3:
            // Break the loop
            cont = false;
            break;
        }
    }

    // Exit 
    return;
}


int main()
{
    // Declare variables
    unitList groupData;
    bool cont = true;
    int select;

    // Run initial preparations
    readParameter(CharacterList.tags, CharacterList.ranks, groupData.ranks);
    startUp(groupData.units, CharacterList.characters, CharacterList.other);

    // Print
    while (cont) {
        select = support::prompt(
            "Select",
            { "Test Current Function", "Edit Functions", "Print Functions", "Done (Exit Program)" }
        );

        switch (select) {
        case 1:
            cout << "Character Ranks\n";
            for (string i : CharacterList.ranks)
                cout << i << "\n";

            cout << "\nGroup Ranks\n";
            for (string i : CharacterList.ranks)
                cout << i << "\n";

            cout << "\nCharacter Tags\n";
            for (vector<string> i : CharacterList.tags)
                cout << "Name: " << i[0] << "\n Description: " << i[1] << "\n\n";
            break;
        case 2:
            // Run Edit Functions
            editFunc(groupData, CharacterList.characters);
            break;
        case 3:
            // Run Print Functions
            printFunc(groupData, CharacterList.characters, CharacterList.other);
            break;
        case 4:
            // End the loop
            cont = false;
            break;
        }
    }
}