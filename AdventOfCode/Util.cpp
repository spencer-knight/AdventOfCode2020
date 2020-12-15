#include <vector>
#include <string>
#include "util.h"
#include <regex>

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
}