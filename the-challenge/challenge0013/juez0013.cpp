#include <iostream>
#include <fstream>

int main()
{
	char ch;
	std::ifstream fp("star.txt", std::ifstream::in);

	if (fp.is_open()==false) {
		std::cout << "star.txt must be in the same folder as this program" << std::endl;
		return 0;
	}

	while (fp >> std::noskipws >> ch) {
		std::cout << ch; 
	}

	fp.close();

	return 1;
}