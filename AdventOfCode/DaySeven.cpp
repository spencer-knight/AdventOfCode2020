#include "DaySeven.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>

struct rule {

	std::string bagType;
	int quantity;
};
struct bagRule {

	std::string bagType;
	std::vector<rule> rules;
};

//shit show below, be warned.
bagRule makeBagRule(std::string sRules) {

	int numSpaces = 0;
	bagRule out;
	std::string holder;
	int endBagLabel = 0;
	for (int i = 0; i < sRules.length(); i++) {

		if (sRules[i] == ' ') {

			numSpaces++;
		}
		if (numSpaces > 1) {

			out.bagType = holder; 
			//printf("I run");
			endBagLabel = i;
			break;
		}
		holder += sRules[i];
	}

	//printf("%s.\n", out.bagType.c_str());
	std::string numHolder;
	holder = "";
	if (sRules[14 + endBagLabel] == 'n') {

		rule outRule;
		outRule.bagType = "none";
		outRule.quantity = 0;

		out.rules.push_back(outRule);
		//printf("rule created: [%s][%s:%d]\n", out.bagType.c_str(), outRule.bagType.c_str(), outRule.quantity);
		return out;
	}
	for (int i = 14 + endBagLabel; i < sRules.length(); i++) {

		if (sRules[i] == ',') {

			rule outRule;
			std::stringstream ss(numHolder);
			ss >> outRule.quantity;

			std::string newHolder;
			int diff;
		
			if (holder[holder.length() - 1] == '.') {
			
				if (holder[holder.length() - 2] == 's') {
				
					diff = 6;
				}
				else {

					diff = 5;
				}
			}
			else if (holder[holder.length() - 1] == 's') {

				diff = 5;
			}
			else {
				diff = 4;
			}
			for (int j = 0; j < holder.length() - diff; j++) {

				newHolder += holder[j];
			}
			outRule.bagType = newHolder;
			out.rules.push_back(outRule);
			//printf("rule created: [%s][%s:%d]\n", out.bagType.c_str(), outRule.bagType.c_str(), outRule.quantity);
			holder = "";
			numHolder = "";
			i++;
		}
		else if (sRules[i] > 47 && sRules[i] < 58) {

			numHolder += sRules[i];
			if (sRules[i + 1] == ' ') {

				i++;
			}
		}
		else {

			holder += sRules[i];
		}
	}
	rule outRule;
	std::stringstream ss(numHolder);
	ss >> outRule.quantity;

	std::string newHolder;
	int diff;
	if (holder[holder.length() - 1] == '.') {

		if (holder[holder.length() - 2] == 's') {

			diff = 6;
		}
		else {

			diff = 5;
		}
	}
	else if (holder[holder.length() - 1] == 's') {

		diff = 5;
	}
	else {
		diff = 4;
	}
	for (int j = 0; j < holder.length() - diff; j++) {

		newHolder += holder[j];
	}
	outRule.bagType = newHolder;
	out.rules.push_back(outRule);
	//printf("rule created: [%s][%s:%d]\n", out.bagType.c_str(), outRule.bagType.c_str(), outRule.quantity);
	holder = "";
	return out;
}
int daySeven1() {

	std::ifstream file("DaySevenInput.dat");
	std::string line;
	std::vector<bagRule> rules;
	while (std::getline(file, line)) {

		//printf("I run");
		rules.push_back(makeBagRule(line));
	}
	std::vector<std::string> bags;
	for (int i = 0; i < rules.size(); i++) {

		for (int j = 0; j < rules[i].rules.size(); j++) {
		
			if (rules[i].rules[j].bagType == "shiny gold") {

				bool isIn = false;
				for (int z = 0; z < bags.size(); z++) {
				
					if (bags[z] == rules[i].bagType) {

						isIn = true;
					}
				}
				if (!isIn) {

					bags.push_back(rules[i].bagType);
					//printf("%s\n", rules[i].bagType.c_str());
				}
			}
		}
	}

	for (int b = 0; b < bags.size(); b++) {

		for (int i = 0; i < rules.size(); i++) {

			for (int j = 0; j < rules[i].rules.size(); j++) {

				if (rules[i].rules[j].bagType == bags[b]) {

					bool isIn = false;
					for (int z = 0; z < bags.size(); z++) {

						if (bags[z] == rules[i].bagType) {

							isIn = true;
						}
					}
					if (!isIn) {

						bags.push_back(rules[i].bagType);
						//printf("%s\n", rules[i].bagType.c_str());
					}
				}
			}
		}
	}


	return bags.size();
}
int containedIn(std::vector<bagRule> rules, std::string bag, int l) {

	int out = 0;
	for (int i = 0; i < rules.size(); i++) {

		if (rules[i].bagType == bag) {

			//printf("%s ", bag.c_str());
			if (rules[i].rules[0].bagType == "none") {

				//printf("|-");
				for (int t = 0; t < l; t++) {

					printf("--");
				}
				//printf("%s\n", rules[i].rules[0].bagType.c_str());
				//printf("0\n");
				
				return 0;
			}
			else {

				for (int j = 0; j < rules[i].rules.size(); j++) {

					printf("|-");
					for (int t = 0; t < l; t++) {

						printf("--");
					}
					//printf("%s\n", rules[i].rules[j].bagType.c_str());
					//printf("%s ", rules[i].rules[j].bagType.c_str());
					//printf("%d\n", rules[i].rules[j].quantity);
					out += rules[i].rules[j].quantity + rules[i].rules[j].quantity*containedIn(rules, rules[i].rules[j].bagType, l + 1);
				}
			}
		}
	}

	return out;
}
int daySeven2() {

	std::ifstream file("DaySevenInput.dat");
	std::string line;
	std::vector<bagRule> rules;
	while (std::getline(file, line)) {

		//printf("I run");
		rules.push_back(makeBagRule(line));
	}
	int cnt = containedIn(rules, "shiny gold", 0);
	//printf("%d\n", cnt);
	return cnt;
}