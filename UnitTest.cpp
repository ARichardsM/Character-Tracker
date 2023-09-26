#include "pch.h"
#include "CppUnitTest.h"
#include "../CharacterTracker/Classes.h"
#include "../CharacterTracker/General.h"
#include "../CharacterTracker/Classes.cpp"
#include "../CharacterTracker/General.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Basic_Error_Test
{
	TEST_CLASS(Three_Unit_Three_Character)
	{
	public:
		std::vector<character> charList; // Contains all characters as the `character` class
		std::vector<unit> unitList;      // Contains all units as the `unit` class

		void init() {
			for (int i = 0; i < 3; i++) {
				charList.push_back(character());
				unitList.push_back(unit());
			}
		}

		TEST_METHOD(Basic_Print)
		{
			init();
			try {
				// Print all characters
				for (character entry : charList) {
					entry.print();
				}

				// Print all units
				for (unit entry : unitList) {
					entry.print();
				}
			}
			// If any exception is thrown, fail
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(Full_Print)
		{
			init();
			try {
				// Print all characters
				for (character entry : charList) {
					entry.fullprint(unitList);
				}
			}
			// If any exception is thrown, fail
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(Verify)
		{
			init();
			try {
				// Verify the units and characters
				interactions::verifyMemberships(charList, unitList);
				interactions::verifyRelations(charList);
				interactions::verifyRelations(unitList);
				interactions::verifySizes(charList, unitList);
				interactions::addMissingRelations(charList, unitList);
			}
			// If any exception is thrown, fail
			catch (...) {
				Assert::Fail();
			}
		}
	};

	TEST_CLASS(One_Unit_One_Character)
	{
	public:
		std::vector<character> charList; // Contains all characters as the `character` class
		std::vector<unit> unitList;      // Contains all units as the `unit` class

		void init() {
			charList.push_back(character());
			unitList.push_back(unit());
		}

		TEST_METHOD(Basic_Print)
		{
			init();
			try {
				// Print all characters
				for (character entry : charList) {
					entry.print();
				}

				// Print all units
				for (unit entry : unitList) {
					entry.print();
				}
			}
			// If any exception is thrown, fail
			catch (...){
				Assert::Fail();
			}
		}

		TEST_METHOD(Full_Print)
		{
			init();
			try {
				// Print all characters
				for (character entry : charList) {
					entry.fullprint(unitList);
				}
			}
			// If any exception is thrown, fail
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(Verify)
		{
			init();
			try {
				// Verify the units and characters
				interactions::verifyMemberships(charList, unitList);
				interactions::verifyRelations(charList);
				interactions::verifyRelations(unitList);
				interactions::verifySizes(charList, unitList);
				interactions::addMissingRelations(charList, unitList);
			}
			// If any exception is thrown, fail
			catch (...) {
				Assert::Fail();
			}
		}
	};

	TEST_CLASS(No_Unit_No_Character)
	{
	public:
		std::vector<character> charList; // Contains all characters as the `character` class
		std::vector<unit> unitList;      // Contains all units as the `unit` class

		TEST_METHOD(Verify)
		{
			try {
				// Verify the units and characters
				interactions::verifyMemberships(charList, unitList);
				interactions::verifyRelations(charList);
				interactions::verifyRelations(unitList);
				interactions::verifySizes(charList, unitList);
				interactions::addMissingRelations(charList, unitList);
			}
			// If any exception is thrown, fail
			catch (...) {
				Assert::Fail();
			}
		}
	};
}
