/*
	name: Bowen Lyons
	course: csce 3110
	due: 6/3/2019
*/
#include <iostream>

bool isFormXYZ(const char*,int);

int main(int argc, char *args[]) {
	std::string str = "";
	if (argc < 1) {
		std::cout << "usage: ./a.out <string>\n";
		return -1;
	}
	for (int i = 1; i < argc; i++) {
		str += args[i];
	}
	std::cout << str << std::endl;
	int N = str.size();
	if (!isFormXYZ(str.c_str(),N)) {
		std::cout << "String is not of form xYz.\n";
		return -1;
	}
	std::cout << "String is of form xYz.\n";
	return 0;
}

bool isFormXYZ(const char *str, int N) {
	for (int i = 0; i < (N / 2); i++) {
		if (str[i] != str[N-i-1]) {
			return false;
		}
	}
	if (str[N / 2] != 'y') {
		return false;
	}
	return true;
}
