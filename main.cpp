#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

enum class Options
{
	Quit,
	OnePassword,
	SeveralPasswords
};

enum class PasswordDifficulty
{
	Easy, Normal, Hard
};

void showMenu();
bool SaveToFileMenu();
bool isNumber(const std::string& s);

int getInput();
int getNumber();
int getLength();
PasswordDifficulty getDifficulty();

std::string generatePassword(int length, PasswordDifficulty difficulty);
void generatePasswords(std::vector<std::string>& passwords, int amount, int length, PasswordDifficulty difficulty);

void printVector(const std::vector<std::string>& v);
void saveToFile(const std::vector<std::string>& passwords);


std::string easySymbols   = "1234567890qwertyuiopasdfghjklzxcvbmn";
std::string normalSymbols = easySymbols + "QWERTYUIOPMNBVZCXASDFGHLKJ";
std::string hardSymbols   = normalSymbols + " !\"#$%&\'()*+-,./;:<=>?@[\\]^_`{|}";

int main()
{
	srand((unsigned int)time(0));

	bool quit = false;

	std::vector<std::string> passwords; // Vector to store current passwords.

	do {
		showMenu();
		int option = getInput();

		Options e = static_cast<Options>(option);

		int passwordsAmount;
		int passwordsLength;
		PasswordDifficulty difficulty;

		switch (e)
		{
		case Options::Quit:
			quit = true;
			exit(0);
			break;
		case Options::OnePassword:
			std::cout << "OnePassword: \n";
			difficulty = getDifficulty();
			passwordsLength = getLength();
			generatePasswords(passwords, 1, passwordsLength, difficulty);
			printVector(passwords);
			break;
		case Options::SeveralPasswords:
			std::cout << "Several Passwords: \n";
			difficulty = getDifficulty();
			passwordsLength = getLength();
			passwordsAmount = getNumber();
			generatePasswords(passwords, passwordsAmount, passwordsLength, difficulty);
			printVector(passwords);
			break;
		}

		bool result = SaveToFileMenu();

		if (result)
		{
			saveToFile(passwords);
		}

	} while (!quit);

	return 0;
}

void showMenu()
{
	std::cout << "Choose option from list below: \n"
		<< "0 - Quit\n"
		<< "1 - Generate 1 password.\n"
		<< "2 - Generate several passwords. \n";
}

int getInput()
{
	std::string value;
	do {
		std::cout << "Enter option[0;2]: ";
		std::getline(std::cin, value);

	} while ((char)value[0] - '0' < 0 || (char)value[0] - '0' > 2 || value.size()>1);
	return (int) (value[0]-'0');
}

bool SaveToFileMenu()
{
	std::cout << "Save to file(Y/N)?" << std::endl;

	std::string input;
	do {
		std::getline(std::cin, input);

	} while (!(tolower(input[0]) == 'y' || tolower(input[0]) == 'n') || input.size() > 1);

	return tolower(input[0]) == 'y';
}

bool isNumber(const std::string& s)
{
	if (s.empty())
		return false;
	for (auto c : s)
	{
		if ((c < '0') || (c > '9'))
			return false;

	}
	return true;
}

int getNumber()
{
	std::string s;
	int n;
	do {
		std::cout << "Enter number of passwords you want to generate(from 1 to 12): " << std::endl;
		std::getline(std::cin, s);
		while (!isNumber(s))
		{
			std::getline(std::cin, s);
		}
		n = stoi(s);
	} while (n < 1 || n > 12);
	return n;
}

std::string generatePassword(int length, PasswordDifficulty difficulty)
{
	std::string result;
	for (int i = 0; i < length; i++)
	{
		switch (difficulty)
		{
		case PasswordDifficulty::Easy:
			result += easySymbols[(rand() % easySymbols.size() + rand() % easySymbols.size())/2];
			break;
		case PasswordDifficulty::Normal:
			result += normalSymbols[rand() % normalSymbols.size()];
			break;
		case PasswordDifficulty::Hard:
			result += hardSymbols[rand() % hardSymbols.size()];
			break;
		}
	}
	return result;
}

void generatePasswords(std::vector<std::string>& passwords, int amount, int length, PasswordDifficulty difficulty)
{
	passwords.clear();
	for (int i = 0; i < amount; i++)
	{
		passwords.push_back(generatePassword(length, difficulty));
	}
}

void printVector(const std::vector<std::string>& v)
{
	std::cout << "---Printing---" << std::endl;
	for (const auto& x : v)
	{
		std::cout << x << std::endl;
	}
	std::cout << "--------------" << std::endl;
}

int getLength()
{
	std::string s;
	int n;
	do {
		std::cout << "Enter password's length (from 8 to 12):" << std::endl;
		std::getline(std::cin, s);
		while (!isNumber(s))
		{
			std::cout << "Enter password's length (from 8 to 12):" << std::endl;
			std::getline(std::cin, s);
		}
		n = stoi(s);
	} while (n < 8 || n > 12);
	return n;
}

PasswordDifficulty getDifficulty()
{
	std::cout << "Choose password difficulty: \n"
		<< "0 - Easy\n"
		<< "1 - Normal.\n"
		<< "2 - Hard. \n";

	std::string value;
	do {
		std::cout << "Enter option[0;2]: ";
		std::getline(std::cin, value);

	} while (value[0] - '0' < 0 || value[0] - '0' > 2 || value.size() > 1);
	return static_cast<PasswordDifficulty>(value[0] - '0'); // returns entered difficulty
}

//Creates file passwords.txt and adds to it generated passwords or just appends if already exists
void saveToFile(const std::vector<std::string>& passwords)
{
	std::ofstream outputFile("passwords.txt", std::fstream::out | std::fstream::app); 
	
	if (outputFile.is_open())
	{
		std::time_t current_time = std::time(0);
		std::tm* timestamp = std::localtime(&current_time);
		char buffer[80];//buffer for storing timestamp
		strftime(buffer, 80, "%c", timestamp);

		outputFile << '[' << buffer << ']' << std::endl;
		for (const auto& password : passwords)
		{
			outputFile << password << std::endl;
		}
		std::cout << "Successfully saved in \"passwords.txt\"" << std::endl;
	} 
	else
	{
		std::cerr << "An error occured while saving in file!" << std::endl;
	}

	outputFile.close();
}
