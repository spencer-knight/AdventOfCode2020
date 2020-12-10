#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace cgx {

	void cmd(std::string cmd);
	void cls();
	void saveCursor();
	void loadCursor();
	void print(std::string in);
	void left(int count = 1);
	void move(int x, int y);
	void home();
	void setAtt(std::string arg);
	void up(int count = 1);
	void down(int count = 1);
	void right(int count = 1);
}

namespace cgx {

	char esc = char(0x1B);

	void cmd(std::string cmd) {

		//saveCursor();
		//printf("%c%s", esc, cmd); // For some reason the escape character doesn't work with printf :( cout it is.
		std::cout << esc << cmd;
		//loadCursor();
	}
	void cls() {

		cmd("[2J");
	}
	void saveCursor() {

		//Done manually so that there isn't a recursive loop(loop?)
		std::cout << esc << "[s";
		//std::cout << esc << "[u";
	}
	void loadCursor() {

		//Done manually so that there isn't a recursive loop(loop?)
		std::cout << esc << "[u";
	}
	void print(int x, int y, std::string in) {

		move(x, y);
		std::cout << in;
	}
	void move(int x, int y) {

		std::stringstream ss("");
		ss << "[" << y << ";" << x << "f";
		std::string command = ss.str();
		cmd(command);
	}
	void left(int count) {

		std::stringstream ss("");
		ss << "[" << count << "D";
		std::string command = ss.str();
		cmd(command);
	}
	void home() {

		cmd("[H");
	}
	void setAtt(std::string att) {

		int i_arg = 0;

		// Settings
		if (att == "reset") {

			i_arg = 0;
		}
		else if (att == "bright") {

			i_arg = 1;
		}
		else if (att == "dim") {

			i_arg = 2;
		}
		else if (att == "underscore") {

			i_arg = 4;
		}
		else if (att == "blink") {

			i_arg = 5;
		}
		else if (att == "reverse") {

			i_arg = 7;
		}
		else if (att == "hidden") {

			i_arg = 8;
		}

		// Text colors
		else if (att == "fblack") {

			i_arg = 30;
		}
		else if (att == "fred") {

			i_arg = 31;
		}
		else if (att == "fgreen") {

			i_arg = 32;
		}
		else if (att == "fyellow") {

			i_arg = 33;
		}
		else if (att == "fblue") {

			i_arg = 34;
		}
		else if (att == "fmagenta") {

			i_arg = 35;
		}
		else if (att == "fcyan") {

			i_arg = 36;
		}
		else if (att == "fwhite") {

			i_arg = 37;
		}

		// Background colors
		else if (att == "bblack") {

			i_arg = 40;
		}
		else if (att == "bred") {

			i_arg = 41;
		}
		else if (att == "bgreen") {

			i_arg = 42;
		}
		else if (att == "byellow") {

			i_arg = 43;
		}
		else if (att == "bblue") {

			i_arg = 44;
		}
		else if (att == "bmagenta") {

			i_arg = 45;
		}
		else if (att == "bcyan") {

			i_arg = 46;
		}
		else if (att == "bwhite") {

			i_arg = 47;
		}

		// Finish setting
		std::stringstream ss("");
		ss << "[" << i_arg << "m";
		cmd(ss.str());
	}
	void right(int count) {

		std::stringstream ss("");
		ss << "[" << count << "C";
		std::string command = ss.str();
		cmd(command);
	}
	void up(int count) {

		std::stringstream ss("");
		ss << "[" << count << "A";
		std::string command = ss.str();
		cmd(command);
	}
	void down(int count) {

		std::stringstream ss("");
		ss << "[" << count << "B";
		std::string command = ss.str();
		cmd(command);
	}
}