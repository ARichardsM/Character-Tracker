#include "Tracker.h"

void output::multiPrint(const std::vector<character>& characterList, const std::vector<unit>& unitList) {
	std::string printNum;
	int entNum, entType;

	std::srand(std::time(nullptr));

	do {
		std::cout << "How Many Entities Should Be Output? \t";
		std::cin >> printNum;
	} while (printNum.find_first_not_of("1234567890") != std::string::npos);

	entNum = std::stoi(printNum);

	if (characterList.size() == 0) {
		entType = 2;
	}
	else if (unitList.size() == 0) {
		entType = 1;
	}
	else {
		entType = support::prompt("Which Type of Entity?", { "Character", "Crew" });
	}

	switch (entType) {
	case 1:
	{
		if (entNum > characterList.size())
			entNum = characterList.size();

		std::vector<bool> arr(characterList.size(), false);

		for (int i = 0; i < entNum; i++) {
			int random_value = std::rand() % characterList.size();

			while (arr[random_value]) {
				random_value = random_value + 1;

				if (random_value >= arr.size())
					random_value = 0;
			}

			arr[random_value] = true;

			
		}

		// Print all characters
		std::cout << "Characters" << "\n";
		for (int i = 0; i < characterList.size(); i++) {
			if (arr[i]) {
				std::cout << characterList[i].output();
				std::cout << "\n";
			}
			
		}
		break;
	}
	case 2:
	{
		if (entNum > unitList.size())
			entNum = unitList.size();

		std::vector<bool> arr(unitList.size(), false);

		for (int i = 0; i < entNum; i++) {
			int random_value = std::rand() % unitList.size();

			while (arr[random_value]) {
				random_value = random_value + 1;

				if (random_value >= arr.size())
					random_value = 0;
			}

			arr[random_value] = true;


		}

		// Print all units
		std::cout << "Units" << "\n";
		for (int i = 0; i < unitList.size(); i++) {
			if (arr[i]) {
				std::cout << unitList[i].output();
				std::cout << "\n";
			}

		}

		break;
	}
	}
}