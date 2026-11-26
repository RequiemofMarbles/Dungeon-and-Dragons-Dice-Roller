#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>

// Reads one line and returns it only if it is a single integer within [min, max].
// Asks again on invalid input, and exits if the input stream ends.
int readInt(int min, int max)
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream input(line);
		int value = 0;
		char extra;
		if (input >> value && !(input >> extra) && value >= min && value <= max)
		{
			return value;
		}
		std::cout << "Maybe a typo? Try not doing that. Enter a number from " << min << " to " << max << ": ";
	}
	std::exit(0);
}

int main()
{
	srand(time(0));
	int choice = 0;
	std::vector<std::string> history;

	while (choice != 10)
	{
		std::cout << "Welcome To Dungeons and Dragons Dice Roller!" << std::endl;
		std::cout << "Choose which dice you need to roll: " << std::endl;
		std::cout << "1. D20" << std::endl;
		std::cout << "2. D12" << std::endl;
		std::cout << "3. D10" << std::endl;
		std::cout << "4. D8" << std::endl;
		std::cout << "5. D6" << std::endl;
		std::cout << "6. D4" << std::endl;
		std::cout << "7. Percentile Dice (00-100)" << std::endl;
		std::cout << "8. Rolling New Character Stats" << std::endl;
		std::cout << "9. View Roll History" << std::endl;
		std::cout << "10. Exit" << std::endl;
		choice = readInt(1, 10);

		int numDice = 1;
		int modifier = 0;
		int total = 0;

		if (choice >= 1 && choice <= 7)
		{
			std::cout << "How many dice do you need to roll? ";
			numDice = readInt(1, 100); // Arbitrary upper limit for number of dice
			std::cout << "Enter any modifier you need (ie: enter 0 for none, or a negative like -12): ";
			modifier = readInt(-100, 100); // Arbitrary upper limit for modifier
		}

		int result = 0;

		if (choice == 1)
		{
			int rollType = 1;
			std::cout << "Select D20 roll type: " << std::endl;
			std::cout << "1. Normal Roll" << std::endl;
			std::cout << "2. Advantage Roll (Roll twice and take the higher)" << std::endl;
			std::cout << "3. Disadvantage Roll (Roll twice and take the lower)" << std::endl;
			std::cout << "Enter your choice: ";
			rollType = readInt(1, 3);

			for (int i = 0; i < numDice; i++)
			{
				int keptRoll = 0;

				if (rollType == 2) // Advantage
				{
					int roll1 = rand() % 20 + 1;
					int roll2 = rand() % 20 + 1;
					std::cout << "Roll " << (i + 1) << " (Advantage): rolled " << roll1 << " and " << roll2;

					if (roll1 >= roll2)
					{
						keptRoll = roll1;
					}
					else
					{
						keptRoll = roll2;
					}
					std::cout << " -> Keeping " << keptRoll << std::endl;
				}
				else if (rollType == 3) // Disadvantage
				{
					int roll1 = rand() % 20 + 1;
					int roll2 = rand() % 20 + 1;
					std::cout << "Roll " << (i + 1) << " (Disadvantage): rolled " << roll1 << " and " << roll2;

					if (roll1 <= roll2)
					{
						keptRoll = roll1;
					}
					else
					{
						keptRoll = roll2;
					}
					std::cout << " -> Keeping " << keptRoll << std::endl;
				}
				else // Normal Roll (or default if they typed an invalid number)
				{
					keptRoll = rand() % 20 + 1;
					std::cout << "Roll " << (i + 1) << ": " << keptRoll << std::endl;
				}

				total += keptRoll;
				if (keptRoll == 20)
				{
					int msg = rand() % 3 + 1;
					switch (msg)
					{
					case 1:
						std::cout << "  -> Natty 20!! Critical Hit! What the fuck is even happening right now" << std::endl;
						break;
					case 2:
						std::cout << "  -> Nat 20! My dude your frodo when he drops the ring into fires of Mount Doom! The EXP, The Gold, The GLORY!" << std::endl;
						break;
					case 3:
						std::cout << "  -> NATURAL 20! FUCKING LEGENDARY! YOUR CHARCTER GOES SSJ 3!!!!!" << std::endl;		
						break;
					}
				}
				else if (keptRoll == 1)
				{
					int msg = rand() % 3 + 1;
					switch (msg)
					{
					case 1:
						std::cout << "  -> 1... You rolled a 1. Fuck it, might as well just kill character." << std::endl;
						break;
					case 2:
						std::cout << "  -> Critical Fail! The DM is going to have a field day with your ass!" << std::endl;
						break;
					case 3:
						std::cout << "  -> Natural 1! You rolled a 1, a fucking 1 bro. Just get in the front leaning rest." << std::endl;
						break;
					}
				}
			}
			std::cout << "D20 roll w/o modifiers: " << total << std::endl;
			total += modifier;
			std::cout << "D20 roll (with modifier " << modifier << "): " << total << std::endl;
			// Add the roll to history
			history.push_back(std::to_string(numDice) + "D20 (mod " + std::to_string(modifier) + ") = " + std::to_string(total));
			if (history.size() > 10)
			{
				history.erase(history.begin());
			}
		}
		else if (choice == 2)
		{
			for (int i = 0; i < numDice; i++)
			{
				int roll = rand() % 12 + 1;
				std::cout << "Roll " << (i + 1) << ": " << roll << std::endl;
				total += roll;
			}
			std::cout << "D12 roll w/o modifiers: " << total << std::endl;
			total += modifier;
			std::cout << "D12 roll (with modifier " << modifier << "): " << total << std::endl;
			// Add the roll to history
			history.push_back(std::to_string(numDice) + "D12 (mod " + std::to_string(modifier) + ") = " + std::to_string(total));
			if (history.size() > 10)
			{
				history.erase(history.begin());
			}
		}
		else if (choice == 3)
		{
			for (int i = 0; i < numDice; i++)
			{
				int roll = rand() % 10 + 1;
				std::cout << "Roll " << (i + 1) << ": " << roll << std::endl;
				total += roll;
			}
			std::cout << "D10 roll w/o modifiers: " << total << std::endl;
			total += modifier;
			std::cout << "D10 roll (with modifier " << modifier << "): " << total << std::endl;
			// Add the roll to history
			history.push_back(std::to_string(numDice) + "D10 (mod " + std::to_string(modifier) + ") = " + std::to_string(total));
			if (history.size() > 10)
			{
				history.erase(history.begin());
			}
		}
		else if (choice == 4)
		{
			for (int i = 0; i < numDice; i++)
			{
				int roll = rand() % 8 + 1;
				std::cout << "Roll " << (i + 1) << ": " << roll << std::endl;
				total += roll;
			}
			std::cout << "D8 roll w/o modifiers: " << total << std::endl;
			total += modifier;
			std::cout << "D8 roll (with modifier " << modifier << "): " << total << std::endl;
			// Add the roll to history
			history.push_back(std::to_string(numDice) + "D8 (mod " + std::to_string(modifier) + ") = " + std::to_string(total));
			if (history.size() > 10)
			{
				history.erase(history.begin());
			}
		}
		else if (choice == 5)
		{
			for (int i = 0; i < numDice; i++)
			{
				int roll = rand() % 6 + 1;
				std::cout << "Roll " << (i + 1) << ": " << roll << std::endl;
				total += roll;
			}
			std::cout << "D6 roll w/o modifiers: " << total << std::endl;
			total += modifier;
			std::cout << "D6 roll (with modifier " << modifier << "): " << total << std::endl;
			// Add the roll to history
			history.push_back(std::to_string(numDice) + "D6 (mod " + std::to_string(modifier) + ") = " + std::to_string(total));
			if (history.size() > 10)
			{
				history.erase(history.begin());
			}
		}
		else if (choice == 6)
		{
			for (int i = 0; i < numDice; i++)
			{
				int roll = rand() % 4 + 1;
				std::cout << "Roll " << (i + 1) << ": " << roll << std::endl;
				total += roll;
			}
			std::cout << "D4 roll w/o modifiers: " << total << std::endl;
			total += modifier;
			std::cout << "D4 roll (with modifier " << modifier << "): " << total << std::endl;
			// Add the roll to history
			history.push_back(std::to_string(numDice) + "D4 (mod " + std::to_string(modifier) + ") = " + std::to_string(total));
			if (history.size() > 10)
			{
				history.erase(history.begin());
			}
		}
		else if (choice == 7)
		{
			result = rand() % 11 * 10;
			std::cout << "You rolled the Percentile Dice the results are: " << result << std::endl;
			// Add the roll to history
			history.push_back("Percentile Dice = " + std::to_string(result));
			if (history.size() > 10)
				{
					history.erase(history.begin());
				}
		}
		else if (choice == 8)
		{
			std::cout << "\n +++ Rolling New Character Stats +++" << std::endl;

			for (int stat = 1; stat <= 6; stat++)
			{
				if (stat == 1) std::cout << "Strength:   ";
				else if (stat == 2) std::cout << "Dexterity:   ";
				else if (stat == 3) std::cout << "Constitution:   ";
				else if (stat == 4) std::cout << "Intelligence:   ";
				else if (stat == 5) std::cout << "Wisdom:   ";
				else if (stat == 6) std::cout << "Charisma:   ";

				int statSum = 0;
				int lowestRoll = 7;

				std::cout << "[ ";
				for (int d = 0; d < 4; d++)
				{
					int roll = rand() % 6 + 1;
					std::cout << roll << " ";
					statSum += roll;

					if (roll < lowestRoll)
					{
						lowestRoll = roll;
					}
				}
				int finalStat = statSum - lowestRoll;
				std::cout << " ] (Dropped " << lowestRoll << ") -> Total: " << finalStat << std::endl;
			}
		}
		else if (choice == 9)
		{
			std::cout << "\n +++ Roll History +++" << std::endl;
			if (history.empty())
			{
				std::cout << "Nothing has been written to the SCROLLS OF TIME." << std::endl;
			}
			else
			{
				for (int i = 0; i < history.size(); i++)
				{
					std::cout << (i + 1) << ". " << history[i] << std::endl;
				}
			}
		}
		else if (choice == 10)
		{
			std::cout << "You decided to exit and use real life dice :( " << std::endl;
		}
	}

return 0;
}
