#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>
#include "DayEight.h"
#include "ConsoleGraphics.h"
#include <sstream>
#include <chrono>
#include <thread>
#include <iomanip>

//Program exit flags
struct flagList {

	bool infiniteLoop = false;
	bool programFinished = false;
};

//Things like the pc and the accumulator
struct registers {

	int accumulator = 0;
	int pc = 0;
};

//Structure of, well, instruction
struct instruction{

	std::string instr;
	std::vector<int> params;
	int count = 0;
};

//prints the memory
void memDump(std::vector<instruction> mem) {

	for (int i = 0; i < mem.size(); i++) {

		printf("%d: %s ", i, mem[i].instr.c_str());

		for (int j = 0; j < mem[i].params.size(); j++) {

			printf("%d ", mem[i].params[j]);
		}
		printf("\n");
	}
}

//executes Instuction, obviously
void executeInstruction(std::vector<instruction> &mem, registers &reg) {

	//printf("Accumulator: %d\npc: %d\nInstruction: %s %d\n\n", reg.accumulator, reg.pc, mem[reg.pc].instr.c_str(), mem[reg.pc].params[0]);
	mem[reg.pc].count++;

	//might make a dictionary with the commands that links them to a function so that all I have to do to add a new command is add 2 things to the dictionary, not much but it would be nice
	if (mem[reg.pc].instr == "jmp") {

		reg.pc += mem[reg.pc].params[0];
	}
	else if (mem[reg.pc].instr == "acc") {

		reg.accumulator += mem[reg.pc].params[0];
		reg.pc++;
	}
	else if (mem[reg.pc].instr == "nop") {

		reg.pc++;
	}
	else {

		printf("Unknown command: %s. ignoring.", mem[reg.pc].instr.c_str());
		reg.pc++;
	}
}

//Takes memory and reference to registers to run the program, returns a flagList 
flagList runProgram(std::vector<instruction> mem, registers &reg) {

	for (int i = 0; i < mem.size(); i++) {

		mem[i].count = 0;
	}
	while (reg.pc < mem.size()) {

		if (mem[reg.pc].count >= 1) {

			//probably need to remove this later
			//printf("Infinite loop\n");
			flagList flags;
			flags.infiniteLoop = true;
			return flags;
		}
		executeInstruction( mem, reg);
	}

	flagList flags;
	flags.programFinished = true;
	return flags;
}

//takes file input and loads program memory from that file
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
		
		registers reg;
		if (runProgram(mem, reg).programFinished) {

			mem[j].instr = temp;
			return reg.accumulator;
		}
		mem[j].instr = temp;
		
	}

	return 0;
}
int part1(std::vector<instruction> memory) {
	
	registers reg;
	flagList flags = runProgram(memory, reg);
	int out = reg.accumulator;

	return out;
}


std::string int_to_hex(int i)
{
	std::stringstream stream;
	stream << "0x"
		<< std::setfill('0') << std::setw(sizeof(int) * 2)
		<< std::hex << i;
	return stream.str();
}
//Hopefully mimics runProgram while visuializing the program
flagList runProgramG(std::vector<instruction> mem, registers& reg) {

	cgx::setAtt("bblack");
	cgx::setAtt("fcyan");
	cgx::cls();
	cgx::cmd("[?25l");






	for (int i = 0; i < mem.size(); i++) {

		mem[i].count = 0;
	}
	while (reg.pc < mem.size()) {

		if (mem[reg.pc].count >= 1) {

			//probably need to remove this later
			//printf("Infinite loop\n");
			flagList flags;
			flags.infiniteLoop = true;
			return flags;
		}
		executeInstruction(mem, reg);
		








		for (int i = 0; i < mem.size(); i++) {
			std::string outS = mem[i].instr;
			cgx::print(((i % 16) + 1) * 4, (i / 16) + 1, outS);
		}
		cgx::cmd("[?25h");
		cgx::move(((reg.pc % 16) + 1) * 4, (reg.pc / 16));
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		cgx::cmd("[?25l");






	}

	flagList flags;
	flags.programFinished = true;
	return flags;
}


int dayEight() {

	
	std::vector<instruction> memory = loadMemory("DayEightInput.dat");
	//memDump(memory);
	
	registers reg;
	runProgramG(memory, reg);
	//printf("Infinite loop: %d\nExit: %d\n", flags.infiniteLoop, flags.programFinished);
	//int out = part2(memory);
	//for part one you would just run the un altered memory.
	//int out = part2(memory);
	return 0;
}