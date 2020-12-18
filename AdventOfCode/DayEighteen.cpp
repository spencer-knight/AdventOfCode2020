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
//#include "DayEighteen.h"
struct token {
	std::string type;
	std::string val;
};
std::string tknToStr(token& t) {

	//return "[" + t.type + " : " + t.val + "]";
	return t.val + " ";
}
uint64_t solveParen(std::vector<token>& tokens, int &pos) {

	uint64_t ans = 0;
	bool first = true;
	for (; pos < tokens.size(); pos++) {
		
		if (first) {

			if (tokens[pos].val == "(") {

				pos++;
				ans = solveParen(tokens, pos);
				if (!(pos < tokens.size())) {

					return ans;
				}
			}
			else {
				ans = stoi(tokens[pos].val);
			}
			pos++;
			first = false;
		}
		std::string op = tokens[pos].val;

		pos++;

		uint64_t b;
		if (tokens[pos].val == "(") {

			pos++;
			b = solveParen(tokens, pos);
		//	pos++;
			if (!(pos < tokens.size())) {

				return ans;
			}
		}
		else {

			b = stoi(tokens[pos].val);
		}
		if (op == "+") {

			ans += b;
		}
		else {

			ans *= b;
		}
		if (tokens[pos + 1].val == ")") {

			pos += 1;
			break;
		}
		//i++;
	}

//	std::cout << ans << std::endl;
	return ans;

}
uint64_t solveEq(std::vector<token> &tokens) {

	uint64_t ans = 0;
	for (int i = 0; i < tokens.size(); i++) {
		
		if (i == 0) {

			if (tokens[i].val == "(") {

				i++;
				ans = solveParen(tokens, i);
				i++;
				if (!(i < tokens.size())) {

					return ans;
				}
			}
			else {
				ans = stoi(tokens[i].val);
				i++;
			}
			//i++;
		}
		std::string op = tokens[i].val;

		i++;

		uint64_t b;
		if (tokens[i].val == "(") {

			i++;
			b = solveParen(tokens, i);
			if (!(i < tokens.size())) {

				return ans;
			}
		}
		else {

			b = stoi(tokens[i].val);
		}
		if (op == "+") {

			ans += b;
		}
		else {

			ans *= b;
		}
		//i++;
	}

	//std::cout << ans << std::endl;
	return ans;
}
int dayEighteen() {

	std::fstream file("DayEighteenInput.dat");
	std::string line;
	uint64_t sum = 0;
	int j = 0; 
	while (std::getline(file, line)) {
		j++;
		//printf("%s\n", line.c_str());
		// Put parsing shit here
		std::vector<token> tokens;
		std::string num;
		for (int i = 0; i < line.length(); i++) {

			if (line[i] == '+' || line[i] == '*' || line[i] == '(') {

				token t;
				t.type = "operator";
				t.val = line[i];//fix here
				tokens.push_back(t);
			}
			else if((line[i] == ' ' || line[i] == ')')&& num.length() != 0) {

				token t;
				t.type = "number";
				t.val = num;
				tokens.push_back(t);
				num = "";
				if (line[i] == ')') {

					t.type = "operator";
					t.val = ')';
					tokens.push_back(t);
				}
			}
			else {

				if (line[i] != ' ') {
					num += line[i];
				}
			}
		}
		if (num.length() != 0) {

			token t;
			t.type = "number";
			t.val = num;
			tokens.push_back(t);
			num = "";
		}

		for (int i = 0; i < tokens.size(); i++) {

			//std::cout << tknToStr(tokens[i]);
		}
		//std::cout << "= ";
		sum += solveEq(tokens);
		//std::cout << j << ": " << sum << std::endl;
		//std::cout << "########################" << std::endl;
	}
	
	std::cout << "Part1: " <<  sum << std::endl;
	return 0;
}
int main() {

	dayEighteen();
}
