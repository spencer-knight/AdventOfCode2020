#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>
#include "DayEight.h"
#include <sstream>

/*
GLOBALS/REGISTERS
*/

int accumulator;
struct instruction{

	std::string instr;
	std::vector<int> params;
	int count = 0;
};

int dayEight() {

	std::fstream file("DayEightInput.dat");
	std::string line;
	std::vector<instruction> instrs;

	for (int i = 0; std::getline(file, line); i++) {

		std::regex rgx("^[A-z]{1,3}");
		std::smatch sm;
		std::regex_search(line, sm, rgx);
		
		instruction iLine;
		iLine.instr = sm.str();

		std::regex rgx2("[-]?[0-9]+");
		std::smatch sm2;
		std::regex_search(line, sm2, rgx2);
		std::stringstream ss(sm2.str());
		int j;
		ss >> j;
		iLine.params.push_back(j);
		instrs.push_back(iLine);
		//printf("%s %d\n", iLine.instr.c_str(), iLine.params[0]);
	}

	for (int j = 0; j < instrs.size(); j++) {
		std::string temp = instrs[j].instr;
		instrs[j].instr = "nop";
		for (int i = 0; i < instrs.size(); i++) {

			printf("%s %d\n", instrs[i].instr.c_str(), instrs[i].params[0]);
			instrs[i].count = 0;
		}
		printf("\n");
		accumulator = 0;
		
		for (int i = 0; i < instrs.size(); i++) {

			if (instrs[i].count == 1) {

				break;
			}
			instrs[i].count++;
			if (instrs[i].instr == "jmp") {

				i += instrs[i].params[0] - 1;
			}
			else if (instrs[i].instr == "acc") {

				printf("Accumulator += %d", instrs[i].params[0]);
				accumulator += instrs[i].params[0];
			} 
			

			if (i + 1 >= instrs.size()) {

				return accumulator;
			}
		}
		instrs[j].instr = temp;
	}
	return 0;
}