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
#include "DayTwelve.h"


std::vector<std::string> getMatches(std::string reg, std::string str) {

	std::vector<std::string> out;
	std::smatch sm;
	std::regex regex(reg);
	while (std::regex_search(str, sm, regex)) {

		out.push_back(sm.str(0));
		str = sm.suffix().str();
	}

	return out;
}
int dayTwelve2(std::vector<std::pair<char, int>> dirs) {

	int angle = 0;
	int north = 1;
	int east = 10;
	int south = 0;
	int west = 0;
	int x = 10;
	int y = 1;
	int sx = 0;
	int sy = 0;
	for (int i = 0; i < dirs.size(); i++) {

		//printf("%c %d", dirs[i].first, dirs[i].second);
		//printf("(%d, %d)\n", x, y);
		if (dirs[i].first == 'F') {

			sx += x * dirs[i].second;
			sy += y * dirs[i].second;
			//printf("\t( %d, %d)\n", sx, sy);
		}

		if (dirs[i].first == 'N') {

			y += dirs[i].second;
		}
		else if (dirs[i].first == 'E') {

			x += dirs[i].second;
		}
		else if (dirs[i].first == 'W') {

			x -= dirs[i].second;
		}
		else if (dirs[i].first == 'S') {

			y -= dirs[i].second;
		}
		else if (dirs[i].first == 'R') {

			int d = dirs[i].second / 90;
			//printf("%c%d\t%d ", dirs[i].first, dirs[i].second / 90, angle);
			angle = (angle + dirs[i].second / 90) % 4;
			if (d == 1) {

				int temp = x;
				x = y;
				y = -1 * temp;
			}
			if (d == 2) {

				x = -1 * x;
				y = -1 * y;
			}
			if (d == 3) {

				int temp = x;
				x = -1 * y;
				y = temp;
			}
			//printf("%d\n", angle);
		}
		else if (dirs[i].first == 'L') {

			//printf("%c%d\t%d ", dirs[i].first, dirs[i].second / 90, angle);
			angle = (angle - dirs[i].second / 90) % 4;
			int d = dirs[i].second / 90;
			//printf("%d\n", angle);
			if (d == 3) {

				int temp = x;
				x = y;
				y = -1 * temp;
			}
			if (d == 2) {

				x = -1 * x;
				y = -1 * y;
			}
			if (d == 1) {

				int temp = x;
				x = -1 * y;
				y = temp;
			}
		}

	}

	//printf("%d", east);

	return std::abs(sx) + std::abs(sy);
}
int dayTwelve1(std::vector<std::pair<char, int>> dirs) {

	int angle = 0;
	int north = 0;
	int east = 0;
	int south = 0;
	int west = 0;
	for (int i = 0; i < dirs.size(); i++) {

		if (dirs[i].first == 'F') {

			if (angle < 0) {

				angle = 4 + angle;
			}
			switch (angle) {

			case 0:
				east += dirs[i].second;
				break;
			case 1:
				south += dirs[i].second;
				break;
			case 2:
				west += dirs[i].second;
				break;
			case 3:
				north += dirs[i].second;
				break;
			}
		}

		if (dirs[i].first == 'N') {

			north += dirs[i].second;
		}
		else if (dirs[i].first == 'E') {

			east += dirs[i].second;
		}
		else if (dirs[i].first == 'W') {

			west += dirs[i].second;
		}
		else if (dirs[i].first == 'S') {

			south += dirs[i].second;
		}
		else if (dirs[i].first == 'R') {

			//printf("%c%d\t%d ", dirs[i].first, dirs[i].second / 90, angle);
			angle = (angle + dirs[i].second / 90) % 4;
			//printf("%d\n", angle);
		}
		else if (dirs[i].first == 'L') {

			//printf("%c%d\t%d ", dirs[i].first, dirs[i].second / 90, angle);
			angle = (angle - dirs[i].second / 90) % 4;
			//printf("%d\n", angle);
		}

	}

	//printf("%d", east);

	return std::abs(north - south) + std::abs(east - west);
}
int dayTwelve() {

	std::fstream file("DayTwelveInput.dat");
	std::string line;
	std::vector<std::pair<char, int>> dirs;
	while (std::getline(file, line)) {

		//printf("%s\n", line.c_str());
		// Put parsing shit here
		std::pair<char, int> p;
		//std::printf("%d\n", getMatches("[A-z]", line).size());
		p.first = getMatches("[A-z]", line)[0][0];
		std::stringstream ss(getMatches("\\d+", line)[0]);
		ss >> p.second;
		dirs.push_back(p);
	}
	for (int i = 0; i < dirs.size(); i++) {

		//printf("%c %d\n", dirs[i].first, dirs[i].second);
	}
	
	int out = dayTwelve1(dirs );


	return out;
}