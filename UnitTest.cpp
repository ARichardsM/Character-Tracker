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

namespace Verify_Test
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

			// Set Unit Names
			unitList[0].name = "Unit 0";
			unitList[1].name = "Unit 1";
			unitList[2].name = "Unit 2";

			// Set Character Names
			charList[0].name = "Character 0";
			charList[1].name = "Character 1";
			charList[2].name = "Character 2";
		}

		TEST_METHOD(Verify_Membership)
		{
			init();

			// Set valid memberships
			charList[0].member = "Unit 0";
			charList[1].member = "Unit 2";
			unitList[0].member = "Unit 1";

			// Set invalid memberships
			charList[2].member = "Unit 3";
			unitList[1].member = "Unit 3";

			// Run the verify
			std::set<std::string> returnErr = interactions::verifyMemberships(charList, unitList);

			// Try to find the invalid membership in the returned set
			Logger::WriteMessage("Invalid Membership Check");
			auto errLoc = returnErr.find("Unit 3");
			Assert::IsTrue(errLoc != returnErr.end());

			// Verify valid memberships aren't in the set
			Logger::WriteMessage("\nValid Membership Check");
			errLoc = returnErr.find("Unit 0");
			Assert::IsTrue(errLoc == returnErr.end());
			errLoc = returnErr.find("Unit 1");
			Assert::IsTrue(errLoc == returnErr.end());
			errLoc = returnErr.find("Unit 2");
			Assert::IsTrue(errLoc == returnErr.end());

			// Verify unknown memberships aren't in the set
			Logger::WriteMessage("\nRandom Membership Check");
			errLoc = returnErr.find("Unit 4");
			Assert::IsTrue(errLoc == returnErr.end());
		}

		TEST_METHOD(Verify_Character_Relations)
		{
			init();

			// Set valid relations
			charList[0].relations.push_back({ "Character 1", "Test" });
			charList[0].relations.push_back({ "Character 2", "Test" });
			charList[1].relations.push_back({ "Character 0", "Test" });
			charList[2].relations.push_back({ "Character 0", "Test" });

			// Set invalid relations
			charList[0].relations.push_back({ "Character 3", "Test" });
			charList[1].relations.push_back({ "Character 3", "Test" });

			// Run the verify
			std::set<std::string> returnErr = interactions::verifyRelations(charList);

			// Try to find the invalid membership in the returned set
			Logger::WriteMessage("Invalid Relation Check");
			auto errLoc = returnErr.find("Character 3");
			Assert::IsTrue(errLoc != returnErr.end());

			// Verify valid memberships aren't in the set
			Logger::WriteMessage("\nValid Relation Check");
			errLoc = returnErr.find("Character 0");
			Assert::IsTrue(errLoc == returnErr.end());
			errLoc = returnErr.find("Character 1");
			Assert::IsTrue(errLoc == returnErr.end());
			errLoc = returnErr.find("Character 2");
			Assert::IsTrue(errLoc == returnErr.end());

			// Verify unknown memberships aren't in the set
			Logger::WriteMessage("\nRandom Relation Check");
			errLoc = returnErr.find("Character 4");
			Assert::IsTrue(errLoc == returnErr.end());
		}

		TEST_METHOD(Verify_Unit_Relations)
		{
			init();

			// Set valid relations
			unitList[0].relations.push_back({ "Unit 1", "Test" });
			unitList[0].relations.push_back({ "Unit 2", "Test" });
			unitList[1].relations.push_back({ "Unit 0", "Test" });
			unitList[2].relations.push_back({ "Unit 0", "Test" });

			// Set invalid relations
			unitList[1].relations.push_back({ "Unit 3", "Test" });
			unitList[2].relations.push_back({ "Unit 3", "Test" });

			// Run the verify
			std::set<std::string> returnErr = interactions::verifyRelations(unitList);

			// Try to find the invalid membership in the returned set
			Logger::WriteMessage("Invalid Relation Check");
			auto errLoc = returnErr.find("Unit 3");
			Assert::IsTrue(errLoc != returnErr.end());

			// Verify valid memberships aren't in the set
			Logger::WriteMessage("\nValid Relation Check");
			errLoc = returnErr.find("Unit 0");
			Assert::IsTrue(errLoc == returnErr.end());
			errLoc = returnErr.find("Unit 1");
			Assert::IsTrue(errLoc == returnErr.end());
			errLoc = returnErr.find("Unit 2");
			Assert::IsTrue(errLoc == returnErr.end());

			// Verify unknown memberships aren't in the set
			Logger::WriteMessage("\nRandom Relation Check");
			errLoc = returnErr.find("Unit 4");
			Assert::IsTrue(errLoc == returnErr.end());
		}
	};
}
