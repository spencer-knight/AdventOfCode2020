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
	std::string half;
	bool split = false;
	bool loop = false;
	for (int i = 0; i < items.size(); i++) {

		if (items[i] != "|") {

			//std::cout << items[i] << std::endl;
			int rule = stoi(items[i]);
			//std::string half;
			if (rules[rule] != "") {

				buff += rules[rule];
			}
			else if (rule == pos) {

				loop = true;
				//half += "+";
				//buff += half;
				buff += ".";
			}
			else {

				makeRule(rules, sRules, rule);
				buff += rules[rule];
			}
		}
		else {

		//	std::cout << buff << std::endl << std::endl;
			half = "(" + buff + ")";
			buff = "";
			split = true;
			//buff += "|";
		}

	//	std::cout << buff << std::endl;
	}

//	std::cout << buff << std::endl;
	buff = "(" + buff + ")";
	if (loop) {

		int dot = util::indexOf('.', buff);
		//std::cout << dot << std::endl;
		std::string buffNoDot = buff.substr(0, dot) + half + "+|" + buff.substr(dot + 1) + "+";
		std::string ruleNoDot = "(" + half + "|" + buffNoDot + ")";
		std::string rec = ruleNoDot;
		buff = buff.substr(0, dot) + rec + buff.substr(dot + 1);
		std::string rule = "(" + half + "|" + buff + ")";
		//std::string ruleNoDot = rule.substr(0, dot) + rule.substr(dot + 1);
		//rule = rule.substr(0, dot) + ruleNoDot + rule.substr(dot + 1);
		rules[pos] = rule;
	}
	//std::cout << buff << std::endl << std::endl;
	else {

		if (split) {
			rules[pos] = "(" + half + "|" + buff + ")";
		}
		else {

			rules[pos] = "(" + buff + ")";
		}
	}
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

	//for (int i = 0; i < sRules.size(); i++) {

		//printf("%s\n", sRules[i].c_str());
		makeRule(rules, sRules, 0);
//	}

	std::cout << rules[0] << std::endl;
	int sum = 0;
	//this will get the strings to match
	int i = 1;
	while (std::getline(file, line)) {

		//unfortunately regex_match takes ages to finish comparing.
		std::regex reg("^" + rules[0] + "$");
		std::cout << int((i / 487.0f) * 10000)/100.0f << "% : " << line << std::endl;
		if (std::regex_match(line, reg)) {

			//std::cout << line << std::endl;
			sum++;
		}

		i++;
	}

	std::cout << "Part1: " << sum << std::endl;
	return sum;
}
int main19() {

	dayNineteen();


	return 0;
}