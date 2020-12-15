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
uint64_t si;

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
					
					for (int p = 0; p < pos; p++) {

						prevVal[p]++;
					}
					si++;
					return 0;
				}
			}
		}
	}
}
uint64_t solve(std::vector<uint64_t>& buses) {

//	printf("solve1: %d\n", buses.size());
	uint64_t i = 1;
	i *= 1000;
	si = i;
	for (; ; i++) {

		//std::cout << buses[0] * i << std::endl;
		if (solve(buses, 1, buses[0] * si, true) == 1) {

			return si * buses[0];
		}
	}
}

struct multStruct {

	uint64_t mul;
	uint64_t base;
	uint64_t diff;
	uint64_t val;
};
//solve(...) is a terrible inneficient bruteforce method, imma implement u/dangermaximum's solution because I caved in on this problem, going through a dark place
//Can you blame me though? I have finals.
//So implementing the idea still requires braincells, I can have a little pride in my answer
int stolenRec(std::vector<multStruct> ms, int pos) {

	while (true) {


	}
	return 0;
}
void inc(multStruct& ms) {

	ms.val += ms.mul;
}
int stolenRec(std::vector<multStruct> mults) {

	while (true) {

		//check if all vals are the same
		bool same = true;
		for (int i = 1; i < mults.size(); i++) {

			if (mults[i].val != mults[i - 1].val) {

				same = false;
			}
		}


		int minPos = 0;
		if (!same) {

			uint64_t min = 0xFFFFFFFFFFFFFFFF;
			for (int i = 0; i < mults.size(); i++) {

				if (mults[i].val < min && mults[i].mul != 0) {

					min = mults[i].val;
					minPos = i;
				}
			}
		}
		else {

			return mults[0].val;
		}
		//	std::cout << mults[0].val << std::endl;
		if (mults[0].val > 1068781 && false) {

			std::cout << "You have arrived" << std::endl;
			for (int i = 0; i < mults.size(); i++) {

				std::cout << mults[i].val << std::endl;
			}
			std::cin.get();
		}
		inc(mults[minPos]);
	}
	return 0;
}
uint64_t stolen(std::vector<uint64_t>& buses) {

	std::vector<multStruct> mults;
	for (int i = 1; i < buses.size(); i++) {

		int64_t base = buses[0];
		int64_t mult = buses[i];
		if (buses[i] != 0) {
			while (mult - base != i) {

				if( i == 49 && mult - base < 80 && mult - base > 20)
				std::cout << mult - base << std::endl;
				if (base < mult - i) {

					base += buses[0];
					//	std::cout << base << std::endl;
				}
				else {

					mult += buses[i];
				}
			}
		}
		else {

			//Do nothing
		}

		std::cout << base << " * " << mult << " = ";
		std::cout << base * mult << std::endl;
		if (buses[i] != 0) {
			multStruct ms;
			ms.mul = buses[0] * buses[i];
			ms.base = base;
			ms.val = base;
			ms.diff = mult - base;
			mults.push_back(ms);
		}
	}

	std::cout << "Starting checking" << std::endl;
	return stolenRec(mults);
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
	int out = stolen(buses);
	auto end2 = std::chrono::high_resolution_clock::now();
	long long duration2 = std::chrono::duration_cast<std::chrono::seconds>(end2 - start2).count();
	long long duration3 = std::chrono::duration_cast<std::chrono::minutes>(end2 - start2).count();
	std::cout << "Part2: " << out << std::endl;
	std::cout << "Duration(s): " <<  duration2 << std::endl;
	std::cout << "Duration(m): " << duration3 << std::endl;
	return out;
}