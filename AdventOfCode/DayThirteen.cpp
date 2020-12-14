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
#include "DayThirteen.h"


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


int dayThirteen() {

	std::fstream file("DayThirteenInput.dat");
	//printf("here\n");
	std::string line;
	int earliest;
	file >> earliest;
	//file.ignore();
	//printf("here2");
	file >> line;
	std::vector<int> buses;
	std::vector<std::string> holder = getMatches2("\\d+", line);
	for (int i = 0; i < holder.size(); i++) {

		if (getMatches2("\\d+", holder[i]).size() == 0) {

			holder[i] == "-1";
		}
		int x;
		std::stringstream ss(holder[i]);
		ss >> x;
		buses.push_back(x);
		printf("%d ", x);
	}
	printf("\n");
	bool found = false;
	printf("%d", buses.size());
	int min = 2000000000;
	int minPos = 0;
	for (int i = 0; i < buses.size(); i++) {

		int temp = 0;
		for (int j = 1; buses[i] * j < earliest; j++) {

			temp = j + 1;
		}
		if (buses[i] * temp < min) {

			printf("min: %d\n", min);
			min = buses[i] * temp;
			minPos = buses[i];
		}
	}

	return (min - earliest) * minPos;
	return 0;
}