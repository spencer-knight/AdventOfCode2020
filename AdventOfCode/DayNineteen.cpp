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
#include "util.h"
//#include "DayNineteen.h"
void makeRule(std::vector<std::string>& rules, std::vector<std::string>& sRules, int pos) {

	if (rules[pos] != "") {

		return;
	}

	if (sRules[pos][0] == '\"') {

		rules[pos] = "(";
		rules[pos] += sRules[pos][1];
		rules[pos] += ")";
		return;
	}

	std::string buff;
	std::vector<std::string> items = util::split(sRules[pos]);
	for (int i = 0; i < items.size(); i++) {

		if (items[i] != "|") {

			//std::cout << items[i] << std::endl;
			int rule = stoi(items[i]);
			if (rules[rule] != "") {

				buff += rules[rule];
			}
			else {

				makeRule(rules, sRules, rule);
				buff += rules[rule];
			}
		}
		else {

			buff += "|";
		}

		//std::cout << buff;
	}

	rules[pos] = "(" + buff + ")";
}
int dayNineteen() {

	std::fstream file("DayNineteenInput.dat");
	std::string line;
	std::vector <std::string> sRules(138, "");
	std::vector <std::string> rules(138, "");
	while (std::getline(file, line)) {

	//	printf("\"%s\"\n", line.c_str());
		// Put parsing shit here
		if (line == "") {

			break;
		}
		int colon = util::indexOf(':', line) + 1;
		sRules[stoi(line.substr(0, colon - 1))] = (line.substr( colon + 1));
		rules.push_back("");
	}

	for (int i = 0; i < sRules.size(); i++) {

		//printf("%s\n", sRules[i].c_str());
		makeRule(rules, sRules, i);
	}

	int sum = 0;
	//this will get the strings to match
	while (std::getline(file, line)) {

		std::regex reg("^" + rules[0] + "$");
		if (std::regex_match(line, reg)) {

			//std::cout << line << std::endl;
			sum++;
		}
	}

	std::cout << "Part1: " << sum << std::endl;
	return sum;
}
int main() {

	dayNineteen();


	return 0;
}