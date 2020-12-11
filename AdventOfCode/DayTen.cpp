#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <inttypes.h>
#include <chrono>
#include "DayTen.h"

int find(std::vector<int> in, int toFind) {

	for (int i = 0; i < in.size(); i++) {

		if (in[i] == toFind) {

			return i;
		}
	}
	
	return -1;
}
int dayTen1(std::vector<int> input) {

	int current = 0;
	int threes = 0;
	int ones = 0;
	for (int i = 1; i <= 3; i++) {

		int fnd = find(input, current + i);
		//printf("%d, %d\n", input.size(), fnd);
		if (fnd == -1) {

			//nothing
		}
		else if (input[fnd] - current == 3) {

			threes++;
			i = 0;
			//printf("%d, %d\n", input.size(), fnd);
			current = input[fnd];
		}
		else if (input[fnd] - current == 1) {

			ones++;
			i = 0;
			//printf("%d, %d\n", input.size(), fnd);
			current = input[fnd];
			//printf("What");
		}
		else if (input[fnd] == -1) {

			//break;
		}
		else {

			printf("Fuck\n");
		}
	}



	return (threes + 1)* ones;
}

//store the results of previous computations. TIL that what I implemented was memoization, AoC really be teaching me.
std::unordered_map<uint64_t, uint64_t> results;
uint64_t recurSolve(std::vector<int> input, int current, int depth) {

	uint64_t sum = 0;
	//std::printf("%d\n", *std::max_element(input.begin(), input.end()));
	
	for (int i = 1; i <= 3; i++) {

		int ret = find(input, input[current] + i);
		if (ret != -1 && input[ret] == *std::max_element(input.begin(), input.end())) {
			
			sum += 1;
		}
		if (ret != -1) {

			uint64_t recurSov = 0;
			if (results.find(ret) == results.end()) { 

				recurSov = recurSolve(input, ret, depth + 1);
				results[ret] = recurSov;
			}
			else {

				recurSov = results[ret];
			}
			sum += recurSov;
		}
	}

	return sum;
}

uint64_t recurSolveNoMem(std::vector<int> input, int current, int depth) {

	uint64_t sum = 0;
	//std::printf("%d\n", *std::max_element(input.begin(), input.end()));

	for (int i = 1; i <= 3; i++) {

		int ret = find(input, input[current] + i);
		if (ret != -1 && input[ret] == *std::max_element(input.begin(), input.end())) {

			sum += 1;
		}
		if (ret != -1) {

			uint64_t recurSov = 0;
			recurSov = recurSolveNoMem(input, ret, depth + 1);
			sum += recurSov;
		}
	}

	return sum;
}

//bool func(int a, int b) {
//
//	return a < b;
//}
int dayTen() {

	// Read input line by line.
	std::fstream file("DayTenInput.dat");
	std::string line;
	std::vector<int> input;
	while (std::getline(file, line)) {

		//printf("%s\n", line.c_str());
		// Put parsing shit here
		std::stringstream ss(line);
		int outt;
		ss >> outt;
		input.push_back(outt);
	}

	//printf("long: %d\t uint64_t: %d\n", sizeof(long), sizeof(uint64_t));
	uint64_t outt;
	printf("Part 1: %d\n\n", dayTen1(input));
	input.push_back(0);
	auto start = std::chrono::high_resolution_clock::now();
	outt = recurSolve(input, input.size() - 1, 0);
	auto end = std::chrono::high_resolution_clock::now();
	long long duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	printf("Part 2(Efficient way): %" PRIu64 "\nTime(microseconds): %lld\n\n", outt, duration);
	//std::cin.get();

	//Lol i tried to run it to see how long it would take, then I did the math and realized that the universe would be dead before it finished. 
	/*auto start2 = std::chrono::high_resolution_clock::now();
	uint64_t outtt = recurSolveNoMem(input, input.size() - 1, 0);
	auto end2 = std::chrono::high_resolution_clock::now();
	long long duration2 = std::chrono::duration_cast<std::chrono::seconds>(end2 - start2).count();
	printf("Part 2(Inefficient way): %" PRIu64 "\nTime(seconds): %lld\n", outtt, duration2);
	long long duration2s = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();
	printf("Time(microseconds): %lld\n", duration2s);*/


	/*std::sort(input.begin(), input.end(), func);
	for (int i = 0; i < input.size(); i++) {

		printf("%d\n", input[i]);
	}*/
	return 0;
}