#include "DayTwo.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int charPosition(std::string in, char delim) {

	for (int i = 0; i < in.length(); i++) {

		if (in[i] == delim)
			return i;
	}
	return -1;
}
int getNum(std::string in, int l, int h) {

	std::string sNum;
	for (int i = l; i < h; i++) {

		sNum += in[i];
	}
	std::stringstream ssNum(sNum);
	int out;
	ssNum >> out;
	return out;
}
bool isValid(std::string in) {

	int hyphenPos = charPosition(in, '-');
	int lower = getNum(in, 0, hyphenPos);
	int spacePos = charPosition(in, ' ');
	int upper = getNum(in, hyphenPos + 1, spacePos);
	char toTrack = in[spacePos + 1];

	std::string password;
	int count = 0;
	for (int i = spacePos + 4; in[i] != 0; i++) {

		password += in[i];
		if (in[i] == toTrack) {

			count++;
		}
	}
	if (count >= lower && count <= upper) {
	
		return 1;
	}
	//printf("%s\n", password.c_str());
	return 0;
}
bool isValid2(std::string in) {
	int hyphenPos = charPosition(in, '-');
	int lower = getNum(in, 0, hyphenPos);
	int spacePos = charPosition(in, ' ');
	int upper = getNum(in, hyphenPos + 1, spacePos);
	char toTrack = in[spacePos + 1];

	std::string password;

	for (int i = spacePos + 4; in[i] != 0; i++) {

		password += in[i];
	}
	return password[lower - 1] == toTrack ^ password[upper - 1] == toTrack;
}
int dayTwo() {

	std::ifstream file("DayTwoInput.dat");
	std::string line;
	int count = 0;
	while (std::getline(file, line)) {

		if (isValid2(line)) {

			printf("%d\n", isValid2(line));
			count++;
		}
	}

	return count;
}