#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "DaySix.h"
#define LINES 2179

int getUniqueChars(std::string in) {

	int out = 0;
	std::vector<char> chars;
	chars.push_back(' ');
	for (int i = 0; i < in.length(); i++) {

		bool found = false;
		for (int j = 0; j < chars.size(); j++) {

			if (in[i] == chars[j]) {

				found = true;
			}
		}

		if (found) {

			//nothing
		}
		else {

			out++;
			chars.push_back(in[i]);
		}
	}

	return out;
}
bool isntInAll(char in, std::vector<std::string> resps) {
	
	for (int i = 0; i < resps.size(); i++) {

		bool found = false;
		for (int j = 0; j < resps[i].length(); j++) {

			if (resps[i][j] == in) {

				found = true;
			}
		}
		if (!found) {

			return true;
		}
	}

	return false;
}
int getUnan(std::string in) {

	std::vector<std::string> userResps;
	std::string holder;
	for (int i = 0; i < in.size(); i++) {

		if (in[i] != ' ') {

			holder += in[i];
		}
		else {

			userResps.push_back(holder);
			holder = "";
		}
	}
	int out = 0;
	for (int i = 0; i < userResps[0].length(); i++) {

		if (!isntInAll(userResps[0][i], userResps)) {

			
			out++;
		}
	}

	//printf("%d\n", out);
	return out;
}
int daySix() {

	std::vector<std::string> groupResponses;
	std::string line;
	std::string holder;
	std::ifstream file("DaySixInput.dat");

	for (int i = 0; i < LINES; i++) {

		std::getline(file, line);
		if (line.length() == 0) {

			groupResponses.push_back(holder);
			holder = "";
		}
		else {

			holder += line + " ";
		}
	}
	groupResponses.push_back(holder);

	int out = 0;
	for (int i = 0; i < groupResponses.size(); i++) {

		out += getUnan(groupResponses[i]);
		//out += getUniqueChars(groupResponses[i]); <-- for part one uncomment this and comment the above line
		//printf("%d\n", getUniqueChars(groupResponses[i]));
	}
	return out;
}