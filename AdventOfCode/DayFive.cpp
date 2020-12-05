#include "DayFive.h"
#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

int getRow(std::string in) {

	int lower = 0;
	int upper = 127;

	for (int i = 0; i < in.length() - 3; i++) {

		if (in[i] == 'F') {

			int diff = upper - lower;
			upper = upper - std::ceil(diff / (double)2);
		}
		else if (in[i] == 'B') {

			int diff = upper - lower;
			lower = lower + std::ceil(diff / (double)2);
		}
	}

	return lower;
}
int getCol(std::string in) {

	int lower = 0;
	int upper = 7;

	for (int i = in.length() - 3; i < in.length(); i++) {

		if (in[i] == 'L') {

			int diff = upper - lower;
			upper = upper - std::ceil(diff / (double)2);
		}
		else if (in[i] == 'R') {

			int diff = upper - lower;
			lower = lower + std::ceil(diff / (double)2);
		}
	}

	return lower;
}
int getID(std::string in) {

	return getRow(in) * 8 + getCol(in);
}
bool removeID(int ID, std::vector<int>& seats) {

	for (int i = 0; i < seats.size(); i++) {

		if (seats[i] == ID) {

			seats.erase(seats.begin() + i);
			return 1;
		}
	}

	return 0;
}
int dayFive() {

	std::vector<int> seats;
	for (int r = 0; r < 128; r++) {

		for (int c = 0; c < 8; c++) {

			seats.push_back(r * 8 + c);
		}
	}
	std::ifstream file("DayFiveInput.dat");
	int highest = 0;
	std::string line;
	while (std::getline(file, line)) {

		removeID(getID(line), seats);
		//printf("Removing ID: %d\n", getID(line));
	}
	for (int i = 0; i < seats.size(); i++) {

		printf("%d\n", seats[i]);
	}

	//I kinda fucked up the code, but by looking at the output I was able to figure out which ID was my seat. 
	//It was only partially luck.... I think.
	return 0;
}