#include <vector>
#include <sstream>
#include <string>
#include "util.h"
#include <regex>
#include <iostream>

namespace util {
	
	std::vector<std::string> getMatches(std::string reg, std::string str) {

		std::vector<std::string> out;
		std::smatch sm;
		std::regex regex(reg);
		while (std::regex_search(str, sm, regex)) {

			out.push_back(sm.str(0));
			str = sm.suffix().str();
		}

		return out;
	}
	std::vector<int> getInts(std::string in) {

		std::vector<int> out;
		std::vector<std::string> s_out = getMatches("[0-9]+", in);
		for (int i = 0; i < s_out.size(); i++) {

			int buf = 0;
			std::stringstream ss(s_out[i]);
			ss >> buf;
			out.push_back(buf);
		}

		return out;
	}
}