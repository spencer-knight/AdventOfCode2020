#include <vector>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "DayNine.h"
int part1(std::vector<int> input) {

	int invalid = 0;
	int preamble = 25;
	int search = 25;
	for (int i = preamble; i < input.size(); i++) {

		bool found = false;
		for (int j = std::max(0, i - search); j < input.size(); j++) {

			for (int z = std::max(0, i - search); z < input.size(); z++) {

				if (input[i] == input[j] + input[z] && i != j) {


					found = true;
					if (input[i] == 15690279) {

						//printf("%d + %d = 15690279", input[j], input[z]);
					}
				}
			}
		}

		if (!found) {

			return input[i];
		}
	}
	printf("part 1: %d\n", invalid);
}
int dayNine() {

	std::fstream file("DayNineInput.dat");
	std::string line;
	std::vector<int> input;
	while (std::getline(file, line)) {

		int push;
		std::stringstream ss(line);
		ss >> push;
		input.push_back(push);
		//printf("%s\n", line.c_str());
	}
	int invalid = part1(input);
	printf("part1: %d\n", invalid);
	for (int i = 0; i < input.size(); i++) {
	
		int sum = 0;
		int j = i;
		while (sum < invalid && j < input.size() && input[j] != invalid) {

			sum += input[j];
			//printf("%d\n", sum);
			if (sum == invalid) {
				
				int min = 100000000;
				int max = 0;
				for (int z = i; z < j; z++) {
					//printf("%d + ", input[z]);
					min = std::min(min, input[z]);
					max = std::max(max, input[z]);
				}
				//printf("= %d\n", invalid);
				std::printf("part2: %d", min + max);
				return 0;
			}

			j++;
		}
	}
	return 0;
}