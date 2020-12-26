#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <inttypes.h>
#include <regex>
//#include "Day.h"

int getLoopSize(int base, int subject, int div, int end) {

	int counter = 0;
	while (base != end) {

		counter++;
		base *= subject;
		base = base % div;
	}

	return counter;
}
int transform(uint64_t base, int subject, int loop, int div) {

	for (int i = 0; i < loop; i++) {

		base *= subject;
		base %= div;
	}

	return base;
}
int dayTwentyfive() {

	std::fstream file("DayTwentyfiveInput.dat");
	std::string line;

	int door;
	file >> door;
	int card;
	file >> card;

	int doorloop;
	int cardloop;
	int div = 20201227;
	doorloop = getLoopSize(1, 7, div, door);
	cardloop = getLoopSize(1, 7, div, card);
	std::cout << doorloop << std::endl << cardloop << std::endl;
	std::cout << "Part1: " << transform(1, card, doorloop, div) << std::endl;
	return 0;
}
int main() {

	dayTwentyfive();
	return 0;
}