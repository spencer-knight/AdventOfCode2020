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
//#include "DayX.h"

struct imageTile {

	std::vector<std::vector<char>> img;
	int id;
	void print() {

		std::cout << "ID: " << id << std::endl;
		for (int r = 0; r < img.size(); r++) {

			for (int c = 0; c < img.size(); c++) {

				std::cout << img[r][c];
			}

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	void rotate() {

		std::vector<std::vector<char>> out = img;
		for (int r = 0; r < 10; r++) {

			for (int c = 0; c < 10; c++) {

				out[c][10 - 1 - r] = img[r][c];
			}
		}

		img = out;
	}
};
int dayTwenty() {

	std::fstream file("DayTwentyInput.dat");
	std::string line;
	std::vector<imageTile> its;
	
	//loops through all tiles in input
	for (int i = 0; i < 9; i++) {

		imageTile it;
		std::getline(file, line);
		it.id = stoi(line.substr(5, line.length() - 1));
		it.img = std::vector<std::vector<char>>( 10, std::vector<char>(10, ' '));

		//loops through rows
		for (int r = 0; r < 10; r++) {

			std::getline(file, line);
			//columns
			for (int c = 0; c < 10; c++) {

				it.img[r][c] = line[c];
			}
		}
		its.push_back(it);
		//it.print();
		std::getline(file, line);
	}

	its[0].print();
	its[0].rotate();
	its[0].print();
	return 0;
}
int main() {

	dayTwenty();
	return 0;
}