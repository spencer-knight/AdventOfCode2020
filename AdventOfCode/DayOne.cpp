#include "DayOne.h"
#include <fstream>
#include <sstream> 
#include <string>
#include <iostream>

int dayOne() {
	int nums[200];
	std::ifstream file("DayOneInput.dat");
	std::string line;
	for (int i = 0; std::getline(file, line); i++) {

		std::stringstream ss(line);
		ss >> nums[i];
	}
	for (int i = 0; i < sizeof(nums) / sizeof(int); i++) {

		//printf("%d", i);
		for (int j = 0; j < sizeof(nums) / sizeof(int); j++) {
		
			for (int z = 0; z < sizeof(nums) / sizeof(int); z++) {
			
				if ((i != j && j != z) && nums[i] + nums[j] + nums[z] == 2020) {

					return nums[i] * nums[j] * nums[z];
				}
			}
		}
	}
	return 0;
}