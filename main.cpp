#include <iostream>

void showMenu();

int main()
{
	std::cout << "Testing purposes" << std::endl;

	return 0;
}

void showMenu()
{
	std::cout << "Choose option from list below: \n"
		<< "1 - Generate 1 password.\n"
		<< "2 - Generate several passwords. \n"
		<< "3 - Generate 1 password to file. \n"
		<< "4 - Generate several passwords to file. \n";
}
