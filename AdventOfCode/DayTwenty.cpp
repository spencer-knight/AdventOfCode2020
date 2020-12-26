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
	int x;
	int y;
	std::vector<int> matches;
	bool inMatches(int i) {

		for (int j = 0; j < matches.size(); j++) {

			if (matches[j] == i) {

				return true;
			}
		}
		return false;
	}
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
	std::string getEdge(std::string side) {

		std::string ret;
		if (side == "left") {

			for (int i = 0; i < img.size(); i++) {

				ret += img[i][0];
			}
		}
		else if (side == "right") {

			for (int i = 0; i < img.size(); i++) {

				ret += img[i][img.size() - 1];
			}
		}
		else if (side == "top") {

			for (int i = 0; i < img.size(); i++) {

				ret += img[0][i];
			}
		}
		else if (side == "bottom") {

			for (int i = 0; i < img.size(); i++) {

				ret += img[img.size() - 1][i];
			}
		}
		else {

			ret = "none";
		}

		return ret;
	}
};
void printGrid(std::vector<std::vector<imageTile>> grid) {

	for (int i = 0; i < grid.size(); i++) {

		for (int j = 0; j < grid.size(); j++) {

			std::cout << grid[i][j].id << " ";
		}
		std::cout << std::endl;
	}
}
int dayTwenty() {

	std::fstream file("DayTwentyInput.dat");
	std::string line;
	std::vector<imageTile> its;
	
	//loops through all tiles in input
	for (int i = 0; i < 144; i++) {

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

	//its[0].print();
	//std::cout << its[0].getEdge("top") << std::endl;
	//std::cout << its[0].getEdge("right") << std::endl;
	//std::cout << its[0].getEdge("bottom") << std::endl;
	//std::cout << its[0].getEdge("left") << std::endl;
	//its[0].rotate();
	//its[0].print();
	//std::cout << std::endl;
	//std::cout << its[0].getEdge("top") << std::endl;
	imageTile it;
	it.id = 0;
	//size is arbitrary, just needs to fit everything with no overflow
	std::vector<std::vector<imageTile>> grid(std::sqrt(its.size()) * 2, std::vector<imageTile>(std::sqrt(its.size()) * 2, it));

	grid[12][12] = its[0];
	its[0].x = 12;
	its[0].y = 12;
	//loop through all image tiles and check each side
	bool broke = false;
	for (int i = 0; i < its.size(); i++) {

		if (!broke) {

			std::cout << "NOT FOUND!" << std::endl;
		}
		broke = false;
		its[i].print();
		printGrid(grid);
		std::cout << i << std::endl;
		//Check all sides of current tile

		for (int j = 0; j < 4 && !broke; j++) {

			//loop through all other cubes;
			for (int c = 0; c < its.size() && !broke; c++) {

				if (c != i && !its[i].inMatches(c)) {

					if (c == 142) {

						std::cout << "here" << std::endl;
					}
					//check all sides of each cube
					for (int s = 0; s < 4 && !broke; s++) {

						if (j == 0) {

							//check right and left
							if (its[i].getEdge("right") == its[c].getEdge("left")) {

								its[i].print();
								its[c].print();
								std::cout << i << std::endl;

								
								grid[its[i].y][its[i].x + 1] = its[c];
								its[c].x = its[i].x + 1;
								its[c].y = its[i].y;
								
								its[c].matches.push_back(i);
								its[i].matches.push_back(c);
								i = c - 1;
								broke = true;
								its[c].rotate();
								its[c].rotate();
								its[c].rotate();
								break;
							}
						}
						else if (j == 1) {

							//check  botom and top
							if (its[i].getEdge("bottom") == its[c].getEdge("top")) {

								its[i].print();
								its[c].print();
								std::cout << i << std::endl;

								
								grid[its[i].y - 1][its[i].x] = its[c];
								its[c].x = its[i].x;
								its[c].y = its[i].y - 1;
								
								its[c].matches.push_back(i);
								its[i].matches.push_back(c);
								i = c - 1;
								broke = true;
								its[c].rotate();
								its[c].rotate();
								its[c].rotate();
								break;
							}
						}
						else if (j == 2) {

							//check left and right
							if (its[i].getEdge("left") == its[c].getEdge("right")) {

								its[i].print();
								its[c].print();
								std::cout << i << std::endl;
								
								grid[its[i].y][its[i].x - 1] = its[c];
								its[c].x = its[i].x - 1;
								its[c].y = its[i].y;
								
								its[c].matches.push_back(i);
								its[i].matches.push_back(c);
								i = c - 1;
								broke = true;
								its[c].rotate();
								its[c].rotate();
								its[c].rotate();
								break;
							}
						}
						else if (j == 3) {

							//check top and bottom
							if (its[i].getEdge("top") == its[c].getEdge("bottom")) {

								its[i].print();
								its[c].print();
								std::cout << i << std::endl;
							
								grid[its[i].y + 1][its[i].x] = its[c];
								its[c].x = its[i].x;
								its[c].y = its[i].y + 1;
								
								its[c].matches.push_back(i);
								its[i].matches.push_back(c);
								i = c - 1;
								broke = true;
								its[c].rotate();
								its[c].rotate();
								its[c].rotate();
								break;
							}
						}
						its[c].rotate();
					}
					its[c].rotate();
				}
			}
		}
	}
	printGrid(grid);
	return 0;
}
int main20() {

	dayTwenty();
	return 0;
}