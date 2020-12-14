#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <inttypes.h>
#include <regex>
#include "DayThirteen.h"

std::vector<uint64_t> prevVal;
std::vector<std::string> getMatches2(std::string reg, std::string str) {

	std::vector<std::string> out;
	std::smatch sm;
	std::regex regex(reg);
	while (std::regex_search(str, sm, regex)) {

		out.push_back(sm.str(0));
		str = sm.suffix().str();
	}

	return out;
}
int d13p1(std::vector<uint64_t> buses, uint64_t earliest) {

//	printf("\n");
	bool found = false;
	//printf("%d", buses.size());
	int min = 2000000000;
	int minPos = 0;
	for (int i = 0; i < buses.size(); i++) {

		int temp = 0;
		if (buses[i] != 0) {

			for (int j = 1; buses[i] * j < earliest; j++) {

				temp = j + 1;
			}
			if (buses[i] * temp < min) {

				//printf("min: %d\n", min);
				min = buses[i] * temp;
				minPos = buses[i];
			}
		}
	}
	return (min - earliest) * minPos;
}
int solve(std::vector<uint64_t> &buses, int pos, uint64_t prev, bool matters) {

	if (pos == buses.size()) {

		return 1;
	}
	
	if (buses[pos] == 0) {

	//	printf("%d\n", pos);
		return solve(buses, pos + 1, prev + 1, true);
	}
	else {

		for (uint64_t i = prevVal[pos] + 1; ; i++) {

			if (buses[pos] * i > prev) {

			//	printf("%d: %d\n", pos, buses[pos] * i);
				if (matters && buses[pos] * i == prev + 1) {

					if (solve(buses, pos + 1, prev + 1, true) == 1) {

						return 1;
					}
				}
				else if (!matters) {

					prevVal[pos] = i;
					return solve(buses, pos + 1, prev + 1, true);
				}
				else {

					prevVal[pos] = i- 1;
					return 0;
				}
			}
		}
	}
}
int solve(std::vector<uint64_t>& buses) {

//	printf("solve1: %d\n", buses.size());
	uint64_t i = 1;
	i *= 1000;
	for (; ; i++) {

		//std::cout << buses[0] * i << std::endl;
		if (solve(buses, 1, buses[0] * i, true) == 1) {

			return i * buses[0];
		}
	}
}
int dayThirteen() {

	std::fstream file("DayThirteenInput.dat");
	//printf("here\n");
	std::string line;
	int earliest;
	file >> earliest;
	//file.ignore();
	//printf("here2");
	file >> line;
	std::vector<uint64_t> buses;
	std::vector<std::string> holder = getMatches2("\\w+", line);
	for (int i = 0; i < holder.size(); i++) {

		if (getMatches2("\\d+", holder[i]).size() == 0) {

			holder[i] == "-1";
		}
		uint64_t x;
		std::stringstream ss(holder[i]);
		ss >> x;
		buses.push_back(x);
		prevVal.push_back(1);
	}
	for (int i = 0; i < buses.size(); i++) {

		//printf("%d\n", buses[i]);
	}
	//std::cin.get();
	std::cout << "Part1: " << d13p1(buses, earliest) << std::endl;
	auto start2 = std::chrono::high_resolution_clock::now();
	int out = solve(buses);
	auto end2 = std::chrono::high_resolution_clock::now();
	long long duration2 = std::chrono::duration_cast<std::chrono::seconds>(end2 - start2).count();
	long long duration3 = std::chrono::duration_cast<std::chrono::minutes>(end2 - start2).count();
	std::cout << "Part2: " << out << std::endl;
	std::cout << "Duration(s): " <<  duration2 << std::endl;
	std::cout << "Duration(m): " << duration3 << std::endl;
	return out;
}