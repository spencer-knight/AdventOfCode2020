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
#include "DaySeventeen.h"
#define lines 8
#define cycles 6

void dispSpace(std::vector<std::vector<std::vector<bool>>> space) {

	int dimensions = lines + (cycles * 2);
	for (int z = (dimensions - 1) / 2; z < dimensions - (dimensions - 1) / 2; z++) {

		for (int x = 0; x < dimensions; x++) {

			for (int y = 0; y < dimensions; y++) {

				std::cout << space[x][y][z];
			}

			std::cout << std::endl;
		}

		std::cout << std::endl << std::endl;
	}
	std::cout << "-----------" << std::endl;
}
int getActive(std::vector<std::vector<std::vector<bool>>> space, int x, int y, int z) {

	int active = 0;
	for (int zc = std::max(z - 1, 0); zc < std::min(z + 1 + 1, (int)space.size()); zc++) {

		for (int xc = std::max(x - 1, 0); xc < std::min(x + 1 + 1, (int)space.size()); xc++) {


			for (int yc = std::max(y - 1, 0); yc < std::min(y + 1 + 1, (int)space.size()); yc++) {

				//std::cout << space[xc][yc][zc];
				if (space[xc][yc][zc] && !((xc == x) && yc == y && zc == z)) {

					active++;
				}
			}

			//std::cout << std::endl;
		}

		//std::cout << std::endl << std::endl;
	}

	return active;
}
int sumActives(std::vector<std::vector<std::vector<bool>>> space) {

	int sum = 0;
	for (int z = 0; z < space.size(); z++) {

		for (int x = 0; x < space.size(); x++) {

			for (int y = 0; y < space.size(); y++) {

				if (space[x][y][z]) {

					sum++;
				}
			}
		}
	}

	return sum;
}
int daySeventeen() {

	int dimensions = lines + (cycles * 2);
	int mid = (dimensions - 1) / 2;
	std::fstream file("DaySeventeenInput.dat");
	std::string line;
	std::vector<std::vector<std::vector<bool>>> space( lines + (cycles * 2), std::vector<std::vector<bool>>(lines + (cycles * 2), std::vector<bool>(lines + (cycles * 2))));
	int ctr = 0;
	while (std::getline(file, line)) {

		//printf("%s\n", line.c_str());
		// Put parsing shit here
		for (int i = 0; i < line.length(); i++) {

			if (line[i] == '#') {

				space[ctr + (cycles)][i + (cycles)][mid] = 1;
			}
			else {

				//space[i][ctr][7] = 0;
			}
		}
		ctr++;
	}
	dispSpace(space);
//	std::cout << "space[6][6][7]: " << getActive(space, 6, 6, 7) << std::endl;
	
	for (int c = 1; c < cycles + 1; c++) {
		std::vector<std::vector<std::vector<bool>>> spacen = space;
		for (int z = mid - c; z < mid + c + 1; z++) {

			for (int x = 0; x < dimensions; x++) {

				for (int y = 0; y < dimensions; y++) {

					if (space[x][y][z]) {

						int actives = getActive(space, x, y, z);
						if (actives == 3 || actives == 2) {


						}
						else {

							spacen[x][y][z] = 0;
						}
					}
					else {

						int actives = getActive(space, x, y, z);
						if (actives == 3) {

							spacen[x][y][z] = 1;
						}
					}
				}
			}
		}
		space = spacen;
		dispSpace(space);
	}

	std::cout << sumActives(space) << std::endl;
	return 0;
}
