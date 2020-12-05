#include "DayThree.h"
#include <fstream>
#include <string>
#define LINES 323
#define WIDTH 31

int findHits(int dy, int dx, std::string strings[LINES]) {

	int x = 0;
	int hits = 0;
	for (int i = dy; i < LINES; i += dy) {

		x += dx;
		if (strings[i][x % WIDTH] == '#') {
			//printf("x: %d y: %d\n", x, i);
			hits++;
		}
	}

	return hits;
}
int dayThree() {

	std::ifstream file("DayThreeInput.dat");
	std::string strings[LINES];
	int dx = 3;
	int dy = 1;
	for (int i = 0; i < LINES; i++) {

		std::getline(file, strings[i]);
	}

	int hits = 1;
	hits *= findHits(1, 3, strings);
	hits *= findHits(1, 1, strings);
	hits *= findHits(1, 5, strings);
	hits *= findHits(1, 7, strings);
	hits *= findHits(2, 1, strings);

	return hits;
}