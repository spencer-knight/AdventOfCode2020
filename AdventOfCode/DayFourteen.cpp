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
#include <bitset>
#include "DayFourteen.h"
uint64_t binToNum(std::string bin) {

	uint64_t out = 0;
	uint64_t pow = 1;
	for (int i = 0; i < bin.length() - 1; i++) {

		pow *= 2;
	}
	for (int i = 0; i < bin.length(); i++) {

		if (bin[i] == '1') {

			out += pow;
		}

		pow /= 2;
	}

	return out;
}
std::vector<uint64_t> getVals(std::string map) {

	std::vector<uint64_t> out;
	std::string zero = map;
	std::string one = map;

	for (int i = 0; i < map.length(); i++) {

		if (map[i] == 'X') {

			zero[i] = '0';
			one[i] = '1';
			std::vector<uint64_t> zeroV = getVals(zero);
			std::vector<uint64_t> oneV = getVals(one);
			for (int i = 0; i < zeroV.size(); i++) {

				oneV.push_back(zeroV[i]);
			}

			return oneV;
		}
	}

	out.push_back(binToNum(zero));
//	out.push_back(binToNum(one));

	return out;
}
std::vector<uint64_t> applyMask2(uint64_t in, std::string mask) {

//	std::cout << mask.length() << std::endl;
	std::vector<uint64_t> out;
	std::stringstream ss("");
	ss << std::bitset<36>(in);
	//std::cout << ss.str() << std::endl;
	std::string s_in = ss.str();
	//std::cout << s_in << std::endl;
	for (int i = 0; i < mask.length(); i++) {

		int maskPos = (mask.size() - 1) - i;
		//	maskPos = i;
		//int inPos = (64 - i);
		//std::cout << mask[maskPos];
		if (mask[i] == '0') {

			s_in[i] = s_in[i];
			//std::cout << "bit: " << i << "set to 0" << std::endl;
			//uint64_t one = 0b111111111111111111111111111111111111;
			//one ^= 1 << i;
			//in &= one;
			//std::cout << "I get called" << in << std::endl;
		}
		else if(mask[i] == '1'){

			//in |= 1 << i;
			s_in[i] = '1';
			//std::cout << "bit: " << i << "set to 1" << std::endl;
		}
		else {

			s_in[i] = 'X';
		}
	}
	//std::cout << s_in << std::endl << std::endl;

	in = binToNum(s_in);
	out = getVals(s_in);
	for (int i = 0; i < out.size(); i++) {

		//std::cout << "Val: " << out[i] << std::endl;
	}
	//std::cout << "post: " << in << std::endl;
	return out;
}

std::unordered_map<uint64_t, uint64_t> runProgram2(std::vector<std::string> program) {

	std::unordered_map<uint64_t, uint64_t> mem;
	std::string mask;
	for (int i = 0; i < program.size(); i++) {

		//checks to see if the line is it is a mask assignment
		//std::cout << "char: " << program[i][1] << std::endl;
		if (program[i][1] == 'a') {

			mask = "";
			for (int j = 7; j < program[i].length(); j++) {

				mask += (char)program[i][j];
			//	std::cout << program[i][j];
			}
		//	std::cout << "mask: " << mask << std::endl;
		}
		else {

			std::vector<std::string> args = util::getMatches("\\d+", program[i]);
			std::stringstream ss(args[0]);
			uint64_t addr;
			ss >> addr;
			std::stringstream ss2(args[1]);
			uint64_t val;
			ss2 >> val;
			//set memory of these addreses to val;
			std::vector<uint64_t> addrs = applyMask2(addr, mask);
			for (int i = 0; i < addrs.size(); i++) {

				mem[addrs[i]] = val;
			}
			//std::cout << "mem[" << addr << "] = " << std::bitset<36>(mem[addr]) << "\t" << mask << std::endl;
		}
	}
	return mem;
}
uint64_t applyMask(uint64_t in, std::string mask) {

	//	std::cout << mask.length() << std::endl;
	std::stringstream ss("");
	ss << std::bitset<36>(in);
	//std::cout << ss.str() << std::endl;
	std::string s_in = ss.str();
	for (int i = 0; i < mask.length(); i++) {

		int maskPos = (mask.size() - 1) - i;
		//	maskPos = i;
		//int inPos = (64 - i);
		//std::cout << mask[maskPos];
		if (mask[i] == '0') {

			s_in[i] = '0';
			//std::cout << "bit: " << i << "set to 0" << std::endl;
			//uint64_t one = 0b111111111111111111111111111111111111;
			//one ^= 1 << i;
			//in &= one;
			//std::cout << "I get called" << in << std::endl;
		}
		else if (mask[i] == '1') {

			//in |= 1 << i;
			s_in[i] = '1';
			//std::cout << "bit: " << i << "set to 1" << std::endl;
		}
	}
	//std::cout << s_in << std::endl;

	in = binToNum(s_in);
	//std::cout << "post: " << in << std::endl;
	return in;
}

std::unordered_map<uint64_t, uint64_t> runProgram(std::vector<std::string> program) {

	std::unordered_map<uint64_t, uint64_t> mem;
	std::string mask;
	for (int i = 0; i < program.size(); i++) {

		//checks to see if the line is it is a mask assignment
		//std::cout << "char: " << program[i][1] << std::endl;
		if (program[i][1] == 'a') {

			mask = "";
			for (int j = 7; j < program[i].length(); j++) {

				mask += (char)program[i][j];
				//	std::cout << program[i][j];
			}
			//	std::cout << "mask: " << mask << std::endl;
		}
		else {

			std::vector<std::string> args = util::getMatches("\\d+", program[i]);
			std::stringstream ss(args[0]);
			uint64_t addr;
			ss >> addr;
			std::stringstream ss2(args[1]);
			uint64_t val;
			ss2 >> val;
			mem[addr] = applyMask(val, mask);
			//std::cout << "mem[" << addr << "] = " << std::bitset<36>(mem[addr]) << "\t" << mask << std::endl;
		}
	}
	return mem;
}
int dayFourteen() {

	std::fstream file("DayFourteenInput.dat");
	std::string line;
	std::vector<std::string> program;
	while (std::getline(file, line)) {

		//printf("%s\n", line.c_str());
		// Put parsing shit here
		program.push_back(line);
	}

	uint64_t sum = 0;
	std::unordered_map<uint64_t, uint64_t> mem = runProgram(program);
	for (auto i = mem.begin(); i != mem.end(); ++i) {

		//std::cout << i->second << std::endl;
		sum += i->second;
		//std::cout << sum << std::endl;
	}

	std::cout << "Part1: " << sum << std::endl;
	std::cout << "Part2: ";
	sum = 0;
	mem = runProgram2(program);
	for (auto i = mem.begin(); i != mem.end(); ++i) {

		//std::cout << i->second << std::endl;
		sum += i->second;
		//std::cout << sum << std::endl;
	}
	std::cout << sum << std::endl;
	return 0;
}