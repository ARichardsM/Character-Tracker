#include "Tracker.h"

void output::multiPrint(const std::vector<character>& characterList, const std::vector<unit>& unitList) {
	std::string printNum;
	int entNum;

	std::srand(std::time(nullptr));

	do {
		std::cout << "How Many Entities Should Be Output? \t";
		std::cin >> printNum;
	} while (printNum.find_first_not_of("1234567890") != std::string::npos);

	entNum = std::stoi(printNum);

	switch (support::prompt("Which Type of Entity?", { "Character", "Crew" })) {
	case 1:
	{
		if (entNum > characterList.size())
			entNum = characterList.size();

		std::vector<bool> arr(characterList.size(), false);

		for (bool in : arr)
			std::cout << in << " INIT ARRAY \n";

		for (int i = 0; i < entNum; i++) {
			int random_value = std::rand() % characterList.size();

			while (arr[random_value]) {
				random_value = random_value + 1;

				if (random_value >= arr.size())
					random_value = 0;
			}

			arr[random_value] = true;

			
		}

		for (bool in : arr)
			std::cout << in << " After ARRAY \n";

		std::cout << entNum;

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

		std::cout << entNum;

		// Print all units
		std::cout << "Units" << "\n";
		for (unit entry : unitList) {
			std::cout << entry.output();
			std::cout << "\n";
		}
		break;
	}
	}
}