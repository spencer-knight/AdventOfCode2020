#include <vector>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "DayNine.h"

//Pass in cipher and position, and optionally preamble length. It will tell you if the number at that position is invalid.
bool isInvalid(std::vector<int> &input, int pos, int preamble = 25) {

	for (int i = std::max(0, pos - preamble); i < pos; i++) {

		for (int j = std::max(0, pos - preamble); j < pos; j++) {

			if (j != i && input[i] + input[j] == input[pos]) {

				return false;
			}
		}
	}
	return true;
}

//given an invalid position, this will return the "weakness" of the cipher, which is just an int.
int findWeakness(std::vector<int>& cipher, int invalid, int preamble = 25) {

	for (int i = 0; i < cipher.size(); i++) {

		std::vector<int> nums;
		int sum = 0;
		for (int j = i; j < cipher.size() && sum < invalid; j++) {

			sum += cipher[j];
			nums.push_back(cipher[j]);
			//printf("%d + ", cipher[j]);
			if (sum == invalid && nums.size() > 1) {

				//printf("min: %d\nmax: %d\n", *std::min_element(nums.begin(), nums.end()), *std::max_element(nums.begin(), nums.end()));
				return *std::min_element(nums.begin(), nums.end()) + *std::max_element(nums.begin(), nums.end());
			}
		}
		//printf("= %d\n", sum);
	}

	return -1;
}

//takes input and optionally preamble length and return the first invalid number position in cipher, doesn't check for any further ones. if none are found it returns -1;
//returns the #### POSITION ####
int findInvalid(std::vector<int> input, int preamble = 25) {

	int invalid = -1;
	for (int i = preamble; i < input.size() && invalid == -1; i++) {
	
		invalid = isInvalid(input, i, preamble) ? i : invalid;
	}

	return invalid;
}

//takes cipher input and optionally preamble length to return a list of invalid numbers, index 0 will be -1 if none are found
//returns the #### POSITIONS ####
//Seems to break on first day list because of integer overflow, hopefully this doesn't need to work on things that big
std::vector<int> findInvalids(std::vector<int> input, int preamble = 25) {

	bool noneFound = true;
	std::vector<int> invalids;
	for (int i = preamble; i < input.size(); i++) {

		if (isInvalid(input, i, preamble)) {

			invalids.push_back(i);
		}
	}
	if (invalids.size() == 0) {

		invalids.push_back(-1);
	}

	return invalids;
}


int part1(std::vector<int> input) {

	int invalid = 0;
	int preamble = 25;
	int search = 25;
	for (int i = preamble; i < input.size() && invalid == 0; i++) {

		printf("Checking %d\n", input[i]);
		if (isInvalid(input, i)) {

			invalid = input[i];
			break;
		}
	}
	//printf("part 1: %d\n", invalid);
	return invalid;
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


	int invalid = input[findInvalid(input, 5)];
	int weakness = findWeakness(input, invalid, 5);
	printf("Invalid: %d\nWeakness: %d\n", invalid, weakness);

	return 0;
}