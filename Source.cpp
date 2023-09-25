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

    bool cont = true;
    while (cont) {
        switch (support::prompt("Select", { "Done", "Verify", "Print", "Random Pull", "Write to File" })) {
        case 1:
            cont = false;
            break;
        case 2:
            // Verify the units and characters
            interactions::verifyMemberships(charList, unitList);
            interactions::verifyRelations(charList);
            interactions::verifyRelations(unitList);
            interactions::verifySizes(charList, unitList);
            interactions::addMissingRelations(charList, unitList);
            break;
        case 3:
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
        case 4:
            // Initialize rand
            srand(time(0));

            // Full print a random character
            charList[rand() % charList.size()].fullprint(unitList);
            break;
        case 5:
            // Write all characters and units to their files
            interactions::writeToFile(charList, unitList);
            break;
        }
    }
}