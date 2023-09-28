#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "Classes.h"
#include "General.h"

using namespace std;
namespace fs = filesystem;

// Global variables
vector<character> charList; // Contains all characters as the `character` class
vector<unit> unitList;      // Contains all units as the `unit` class

int main()
{
    // Pull `Character Files` from the `Characters` Directory
    fs::path charPath = fs::current_path() / "Characters";

    if (exists(charPath))
        for (const auto& entry : fs::directory_iterator(charPath)) {
            // Skip the template
            if (entry.path().stem().string() == "Template Character")
                continue;

            // Skip non-text documents
            if (entry.path().extension().string() != ".txt")
                continue;

            // Add the character to the list
            charList.push_back(character(entry.path().stem().string()));
        }
    else
        cout << "'Characters' directory cannot be found.\n";

    // Pull `Unit Files` from the `Units` Directory
    fs::path unitPath = fs::current_path() / "Units";

    if (exists(unitPath))
        for (const auto& entry : fs::directory_iterator(unitPath)) {
            // Skip the template
            if (entry.path().stem().string() == "Template Unit")
                continue;

            // Skip non-text documents
            if (entry.path().extension().string() != ".txt")
                continue;

            // Add the unit to the list
            unitList.push_back(unit(entry.path().stem().string()));
        }
    else
        cout << "'Units' directory cannot be found.\n";

    // Declare variables
    bool cont = true;
    set<string> setA, setB;

    // Verify the units
    setA = interactions::verifyMemberships(charList, unitList);
    setB = interactions::verifyRelations(unitList);

    setA.insert(setB.begin(), setB.end());

    // Verify the characters
    setB = interactions::verifyRelations(charList);

    // Report any missing entities
    for (string unitName : setA)
        cout << "The unit " << unitName << " cannot be found\n";

    for (string charName : setB)
        cout << "The character " << charName << " cannot be found\n";

    cout << "\n";

    while (cont) {
        switch (support::prompt("Select", { "Done", "Verify Unit Size", "Verify Relations", "Print", "Random Pull", "Write to File" })) {
        case 1:
            // End the loop
            cont = false;
            break;
        case 2:
            // Verify the sizes of all units
            interactions::verifySizes(charList, unitList);
            break;
        case 3:
            // Add any one-sided unit or character relations
            interactions::addMissingRelations(charList, unitList);
            break;
        case 4:
            // Print all characters
            cout << "Characters" << endl;
            for (character entry : charList) {
                entry.print();
                cout << endl;
            }

            // Print all units
            cout << "Units" << endl;
            for (unit entry : unitList) {
                entry.print();
                cout << endl;
            }
            break;
        case 5:
            // Initialize rand
            srand(time(0));

            // Full print a random character
            charList[rand() % charList.size()].fullprint(unitList);
            break;
        case 6:
            // Write all characters and units to their files
            interactions::writeToFile(charList, unitList);
            break;
        }
    }
}