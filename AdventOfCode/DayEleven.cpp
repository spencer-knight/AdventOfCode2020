#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <inttypes.h>
//#include "ConsoleGraphics.h"
#include "DayEleven.h"

void printSeats(std::vector<std::vector<char>> seats) {

	for (int r = 0; r < seats.size(); r++) {
		for (int c = 0; c < seats[r].size(); c++) {

			printf("%c", seats[r][c]);
		}
		printf("\n");
	}
	printf("\n");
}
int adjacentOcc(int rS, int cS, std::vector<std::vector<char>> &seats) {

	int occ = 0;
	for (int r = rS - 1; r < rS + 2; r++) {

		for (int c = cS - 1; c < cS + 2; c++) {

			if (r != rS || c != cS) {

				if (!(r >= seats.size() || r < 0) && !(c >= seats[r].size() || c < 0) && seats[r][c] == '#') {

					occ++;
				}
			}
		}
	}

	return occ;
}
int dayEleven1(std::vector<std::vector<char>> seats) {

	//This code segment works, but it is very slow. Maybe because I am using vectors?
	std::vector<std::vector<char>> newSeats;
	bool change = true;
	for (int i = 0; change; i++) {

		change = false;
		//seats is the same type as newSeats (std::vector<std::vector<char>>)
		newSeats = seats;

		// Go through all seats and apply rules to them, I know that the issue is in this bit.
		for (int r = 0; r < seats.size(); r++) {

			for (int c = 0; c < seats[r].size(); c++) {

				//This returns the number of adjacent occupied seats.
				int occ = adjacentOcc(r, c, seats);

				if (seats[r][c] == 'L' && occ == 0) {

					// Put changes in new array, can't do it in old array because that would cause it to be wrong.
					newSeats[r][c] = '#';
					// This just shows that there is still change so the loop needs to keep looping
					change = true;
				}
				else if (seats[r][c] == '#' && occ >= 4) {

					newSeats[r][c] = 'L';
					change = true;
				}
			}
		}

		//sets the original "array" to the new one so that the loop operates on the new one next time.
		seats = newSeats;
		//printf("%d\n", i);
		//system("cls");
		//printSeats(seats);
	}

	//printSeats(seats);
	int sum = 0;
	for (int r = 0; r < seats.size(); r++) {
		for (int c = 0; c < seats[r].size(); c++) {

			if (seats[r][c] == '#') {

				sum++;
			}
		}
	}

	return sum;
}
int occSeenRec(std::vector<std::vector<char>> &seats, int r, int c, int dr, int dc) {

	//check to see if x and y are in seats
	if (r >= 0 && r < seats.size() && c >= 0 && c < seats[r].size()) {

		//printf("(%d, %d): %c\n", dc, dr, seats[r][c]);
		//std::cin.get();
		if (seats[r][c] == '#') {

			return 1;
		}
		else if (seats[r][c] == 'L') {

			return 0;
		}
		else {

			return occSeenRec(seats, r + dr, c + dc, dr, dc);
		}
	}
	
	return 0;
}
int occSeen(std::vector<std::vector<char>> &seats, int rS, int cS) {

	int occ = 0;
	for (int r = rS - 1; r < rS + 2; r++) {

		for (int c = cS - 1; c < cS + 2; c++) {

			if (r != rS || c != cS) {

				if (!(r >= seats.size() || r < 0) && !(c >= seats[r].size() || c < 0)) {

					//printf("%c", seats[r][c]);
					//printf("(%d, %d)", cS, rS);
					occ += occSeenRec(seats, r, c, r - rS, c - cS);
					//printf("(%d, %d)\n", c, r);
				}
			}
			else {

				//printf("X");
			}
		}
		//printf("\n");
	}
	//printf("(%d, %d): %d\n", cS + 1, rS + 1, occ);
	//std::cin.get();
	return occ;
}
int dayEleven2(std::vector<std::vector<char>> seats) {

	//This code segment works, but it is very slow. Maybe because I am using vectors?
	std::vector<std::vector<char>> newSeats;
	bool change = true;
	for (int i = 0; change; i++) {

		change = false;
		//seats is the same type as newSeats (std::vector<std::vector<char>>)
		newSeats = seats;

		// Go through all seats and apply rules to them, I know that the issue is in this bit.
		for (int r = 0; r < seats.size(); r++) {

			for (int c = 0; c < seats[r].size(); c++) {

				//This returns the number of adjacent occupied seats.
				int occ = occSeen(seats, r, c);
				int oOcc = adjacentOcc(r, c, seats);

				if (seats[r][c] == 'L' && occ == 0) {

					// Put changes in new array, can't do it in old array because that would cause it to be wrong.
					newSeats[r][c] = '#';
					// This just shows that there is still change so the loop needs to keep looping
					change = true;
				}
				else if (seats[r][c] == '#' && occ >= 5) {

					newSeats[r][c] = 'L';
					change = true;
				}
			}
		}

		//sets the original "array" to the new one so that the loop operates on the new one next time.
		seats = newSeats;
		//printf("%d\n", i);
		if (1 == 1) {
			//system("cls");
			//printSeats(seats);
		}
		//std::cin.get();
	}

	//printSeats(seats);
	int sum = 0;
	for (int r = 0; r < seats.size(); r++) {
		for (int c = 0; c < seats[r].size(); c++) {

			if (seats[r][c] == '#') {

				sum++;
			}
		}
	}

	return sum;
}
int dayEleven() {

	std::vector<std::vector<char>> seats;
	std::fstream file("DayElevenInput.dat");
	std::string line;
	while (std::getline(file, line)) {

		std::vector<char> holder;
		for (int i = 0; i < line.length(); i++) {

			holder.push_back(line[i]);
		}
		seats.push_back(holder);
	}

	int sum = dayEleven2(seats);

	return sum;
}