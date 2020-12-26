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
#include <queue>
#define deckSize 25
//#include "DayX.h"

int dayTwentytwo() {

	std::fstream file("DayTwentytwoInput.dat");
	std::string line;
	std::queue<int> p1;
	std::queue<int> p2;
	std::getline(file, line);
	for (int i = 0; i < deckSize; i++) {

		std::getline(file, line);
		p1.push(stoi(line));
	}
	std::getline(file, line);
	std::getline(file, line);
	for (int i = 0; i < deckSize; i++) {

		std::getline(file, line);
		p2.push(stoi(line));
	}

	while (p1.size() != 0 && p2.size() != 0) {

		int one = p1.front();
		p1.pop();
		int two = p2.front();
		p2.pop();
		if (one > two) {

			p1.push(one);
			p1.push(two);
		}
		else {

			p2.push(two);
			p2.push(one);
		}
	}
	std::queue<int> winner;
	if (p1.size() != 0) {

		winner = p1;
	}
	else {

		winner = p2;
	}
	int size = winner.size();
	int score = 0;
	for (int i = 0; i < size; i++) {

		int scr = winner.front() * (size - i);
		score += scr;
		winner.pop();
	}

	std::cout << "Part1: " << score << std::endl;
	return 0;
}
int main22() {

	dayTwentytwo();
	return 0;
}