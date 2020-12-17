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
#include "DaySixteen.h"

int daySixteen() {

	std::fstream file("DaySixteenInput.dat");
	std::string line;
	while (std::getline(file, line)) {

		printf("%s\n", line.c_str());
		// Put parsing shit here

	}

	return 0;
}
