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
#include "DayFifteen.h"
struct turn {

	int pos;
	int said;
};
int dayFifteen1(std::vector<int> nums) {

	std::vector<int> turns;
	for (int i = 0; i < nums.size(); i++) {

		turns.push_back(nums[i]);
	}
	for (int i = 0; i < 2020 - nums.size(); i++) {

		bool found = false;
		int diff = -1;
		for (int j = 0; j < turns.size() - 1; j++) {

			if (turns[j] == turns[turns.size() - 1]) {

				found = true;
				diff = turns.size() - 1 - j;
			}
		}

		if (found) {

			//std::cout << diff << std::endl;
			turns.push_back(diff);
		}
		else {

			turns.push_back(0);
			//std::cout << 0 << std::endl;
		}

		std::cout << i + 4 << ": " << turns[turns.size() - 1] << std::endl;
	}

	return turns[turns.size() - 1];
}
bool less(turn a, turn b) {

	if (a.said < b.said) {

		return true;
	}
	else if (a.said == b.said) {

		return a.pos > b.pos;
	}
	else {

		return false;
	}
}
//returns pos of said
int find( int said, std::vector<turn> in, int low, int high) {

	if (high >= low && low != in.size()) {

		int mid = low + (high - low) / 2;
 		if (in[mid].said == said) {

			//return mid;
			int ret = 0;
			//do thing
			
			for (int i = mid; i > 0; i--) {

				if (in[i].said != in[i - 1].said) {

					return i;
				}
			}

			return 0;
		}
		if (in[mid].said > said) {

			return find(said, in, low, mid - 1);
		}

		return find(said, in, mid + 1, high);
	}

	return -1;
}
int dayFifteen2(std::vector<int> nums) {

	turn last;
	std::vector<turn> turns;
	for (int i = 0; i < nums.size(); i++) {

		turn t;
		t.pos = i;
		t.said = nums[i];
		turns.push_back(t);
		last = t;
	}
	for (int i = 0; i < 30000000 - nums.size(); i++) {

		int diff;
		bool found = false;
		//replace this with binary search
		int j = find(last.said, turns, 0, turns.size());
		
		//std::cout << last.said;
		if (j != -1) {
		
			//std::cout << i + 3 << ": " << last.said << " " << turns[j].said << std::endl;
			//std::cout << "I am getting run" << std::endl;
			diff = last.pos - turns[j].pos;
		//	std::cout << last.pos << " - " << turns[j].pos << " = " << diff << std::endl;
		//	if( j >= 1)
		//	std::cout << "pos" << turns[j - 1].pos << std::endl;
			found = true;
			//std::cout << "I'm not causing errors" << std::endl;
		}
		/*
		for (int i = 0; i < turns.size(); i++) {

			if (turns[i].said == last.said) {

				diff = last.pos - turns[i].pos;
				found = true;
			}
		}
		*/
		//*std::binary_search(turns.begin(), turns.end(), last, sort);
		//insert rather than sort find() - 1 or 0
		int newPos = std::max(find(last.said, turns, 0, turns.size()) - 1, 0);
		if (found) {

			//insert this into sorted array
		//	turns.push_back(last);
			turns.insert(turns.begin() + newPos, last);
			last.pos++;
			last.said = diff;
		//	std::cout << last.said << std::endl;
		}
		else {

		//	turns.push_back(last);
			turns.insert(turns.begin() + newPos, last);
			last.pos++;
			last.said = 0;
		//	std::cout << last.said << std::endl;
		}
		//std::cout << i + 4 << ": " << last.said << std::endl;
		//add map with just the most recent calls to a number?
		std::sort(turns.begin(), turns.end(), less);
	}

	return last.said;
}
int dayFifteen() {

	std::fstream file("DayFifteenInput.dat");
	std::string line;
	std::getline(file, line);

	std::vector<int> nums = util::getInts(line);
	std::cout << "Part1: " << dayFifteen2(nums);
	return 0;
}