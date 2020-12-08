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
void memDump(std::vector<instruction> mem) {

	for (int i = 0; i < mem.size(); i++) {

		printf("%d: %s ", i, mem[i].instr.c_str());

		for (int j = 0; j < mem[i].params.size(); j++) {

			printf("%d ", mem[i].params[j]);
		}
		printf("\n");
	}
}
void executeInstruction(int &pc, std::vector<instruction> &mem) {

	mem[pc].count++;
	if (mem[pc].instr == "jmp") {

		pc += mem[pc].params[0];
	}
	else if (mem[pc].instr == "acc") {

		accumulator += mem[pc].params[0];
		pc++;
	}
	else if (mem[pc].instr == "nop") {

		pc++;
	}
}
bool runProgram(std::vector<instruction> mem) {

	int pc = 0;
	accumulator = 0;
	for (int i = 0; i < mem.size(); i++) {

		mem[i].count = 0;
	}
	while (pc < mem.size()) {

		if (mem[pc].count > 1) {

			//probably need to remove this later
			//printf("Infinite loop\n");
			return false;
		}
		executeInstruction(pc, mem);
	}

	return true;
}
std::vector<instruction> loadMemory(std::string fName) {

	std::fstream file(fName);
	std::string line;
	std::vector<instruction> memory;

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
		memory.push_back(iLine);
		//printf("%s %d\n", iLine.instr.c_str(), iLine.params[0]);
	}

	return memory;
}
int part2(std::vector<instruction> mem) {

	for (int j = 0; j < mem.size(); j++) {

		std::string temp = mem[j].instr;
		mem[j].instr = "nop";
		
		if (runProgram(mem)) {

			mem[j].instr = temp;
			return accumulator;
		}
		mem[j].instr = temp;
		
	}

	return 0;
}
int dayEight() {

	
	std::vector<instruction> memory = loadMemory("DayEightInput.dat");
	//memDump(memory);
	//runProgram(memory);
	//int out = accumulator;
	//for part one you would just run the un altered memory.
	int out = part2(memory);
	return out;
}