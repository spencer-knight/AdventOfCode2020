#include "DayFour.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#define LINES 957


int findFieldPos(std::string field, std::vector<std::string> fields) {

	for (int i = 0; i < fields.size(); i++) {

		if (fields[i] == field) {

			return i;
		}
	}
}
bool isIn(std::string sub, std::vector<std::string> vec) {

	for (int i = 0; i < vec.size(); i++) {

		if (sub == vec[i]) {


			return true;
		}
	}

	return false;
}
bool isValidPassport(std::string passport) {

	std::string fields[] = {

		"byr",
		"iyr",
		"eyr",
		"hgt",
		"hcl",
		"ecl",
		"pid",
		"cid"
	};

	std::string eyeColors[] = {

		"amb",
		"blu",
		"brn",
		"gry",
		"grn",
		"hzl",
		"oth"
	};

	std::vector<std::string> passportFields;
	std::vector<std::string> vals;
	//std::string first;
	//first += passport[0];
	//first += passport[1];
	//first += passport[2];
	//passportFields.push_back(first);
	
	for (int i = 0; i < passport.length() - 1; i++) {

		if (passport[i] == ' ' || i == 0) {
			std::string holder;
			if( i != 0)
				i++;
			for (int j = i + 3; i < j && i < passport.length(); i++) {

				holder += passport[i];
			}
			
			std::string valHolder;
			for (i++; passport[i] != ' ' && i < passport.length(); i++) {
			
				valHolder += passport[i];
			}
			i--;
			passportFields.push_back(holder);
			vals.push_back(valHolder);
		}
	}

	//for (int i = 0; i < passportFields.size(); i++) {

		//printf("%d: %s:%s\n", i, passportFields[i].c_str(), passportFieldVals[i].c_str());
	//}
	//printf("\n");

	//manually check every field and whether or not it is valid
	for (int i = 0; i < 7; i++) {

		if (!isIn(fields[i], passportFields)) {

			return 0;
		}
	}
	//every passport from here on has every needed field, so we can check their values without seeing if they exist.
	//byr (Birth Year) - four digits; at least 1920 and at most 2002.
	int byrPos = findFieldPos("byr", passportFields);
	int byr;
	std::stringstream ssByr(vals[byrPos]);
	ssByr >> byr;
	if (byr > 2002 || byr < 1920) {
	
		printf("Invalid byr: %d\n", byr);
		return 0;
	}
	//iyr (Issue Year) - four digits; at least 2010 and at most 2020.
	int iyrPos = findFieldPos("iyr", passportFields);
	int iyr;
	std::stringstream ssIyr(vals[iyrPos]);
	ssIyr >> iyr;
	if (iyr > 2020 || iyr < 2010) {

		printf("Invalid iyr: %d\n", iyr);
		return 0;
	}
	//eyr(Expiration Year) - four digits; at least 2020 and at most 2030.
	int eyrPos = findFieldPos("eyr", passportFields);
	int eyr;
	std::stringstream ssEyr(vals[eyrPos]);
	ssEyr >> eyr;
	if (eyr > 2030 || eyr < 2020) {

		printf("Invalid eyr: %d\n", eyr);
		return 0;
	}
	//hgt (Height) - a number followed by either cm or in:
	//	If cm, the number must be at least 150 and at most 193.
	//	If in, the number must be at least 59 and at most 76.
	int hgtPos = findFieldPos("hgt", passportFields);
	std::string hNum;
	std::string hUnit;
	//add digits to hNum
	for (int i = 0; i < vals[hgtPos].length() - 2; i++) {

		hNum += vals[hgtPos][i];
	}
	hUnit += vals[hgtPos][vals[hgtPos].length() - 2];
	hUnit += vals[hgtPos][vals[hgtPos].length() - 1];
	std::stringstream ssHNum(hNum);
	int hgt;
	ssHNum >> hgt;
	if (hUnit == "cm") {

		if (hgt < 150 || hgt > 193) {

			printf("Invalid hgt: %d%s\n", hgt, hUnit.c_str());
			return 0;
		}
	}
	else if (hUnit == "in") {

		if (hgt < 59 || hgt > 76) {

			printf("Invalid hgt: %d%s\n", hgt, hUnit.c_str());
			return 0;
		}
	}
	else {

		printf("Invalid hgt: %d%s. %s not a valid unit\n", hgt, hUnit.c_str(), hUnit.c_str());
		return 0;
	}
	//hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
	int hclPos = findFieldPos("hcl", passportFields);
	//get rid of improper size and # lacking hcls
	if (vals[hclPos].length() < 7 || vals[hclPos][0] != '#' || vals[hclPos].length() > 7) {

		printf("Invalid hcl: %s\n", vals[hclPos].c_str());
		return 0;
	}
	//check for 0-9 or a-f 0=48 0=57 a=97 f=102
	for (int i = 1; i < vals[hclPos].length(); i++) {

		char chr = vals[hclPos][i];
		if (!(chr <= '9' && chr >= '0') && !(chr <= 'f' && chr >= 'a')) {

			printf("Invalid hcl: %s\n", vals[hclPos].c_str());
			return 0;
		}
	}
	//ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
	int eclPos = findFieldPos("ecl", passportFields);
	std::string ecl = vals[eclPos];
	bool isValidEcl = false;
	for (int i = 0; i < 7; i++) {

		isValidEcl = isValidEcl || eyeColors[i] == ecl;
	}
	if (!isValidEcl) {

		printf("Invalid ecl: %s\n", ecl.c_str());
		return 0;
	}
	//pid (Passport ID) - a nine-digit number, including leading zeroes. ################################################# DOES NOT CHECK IF IT IS A NUMBER
	int pidPos = findFieldPos("pid", passportFields);
	if (vals[pidPos].length() != 9) {

		printf("Invalid pid: %s\n", vals[pidPos].c_str());
		return 0;
	}
	std::string pid = vals[pidPos];
	for (int i = 0; i < pid.length(); i++) {

		if (!(pid[i] <= '9' || pid[i] >= '0')) {

			printf("Invalid pid: %s\n", vals[pidPos].c_str());
			return 0;
		}
	}

	return 1;
}

int dayFour() {

	std::ifstream file("DayFourInput2.dat");
	std::string passport;
	std::string holder;
	std::vector<std::string> svPassports;
	for (int i = 0; i < LINES; i++) {
	
		std::getline(file, holder);
		if (holder.length() != 0) {

			passport += holder + " ";
		}
		else {

			svPassports.push_back(passport);
			passport = "";
		}
		
	}
	svPassports.push_back(passport);

	int validCount = 0;
	for (int i = 0; i < svPassports.size(); i++) {

		if (isValidPassport(svPassports[i])) {

			validCount++;
			printf("Valid: %s\n\n", svPassports[i].c_str());
		}
		else {

			printf("Invalid: %s\n\n", svPassports[i].c_str());
		}
	}

	return validCount;
}