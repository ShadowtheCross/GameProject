#pragma once
#include <iostream>




inline void doubleDotSplit(std::string primary,std::string& part1, std::string& part2) {
	bool dotFound = false;
	part1 = "";
	part2 = "";
	for (int i = 0; i < primary.size(); i++) {
		if (primary[i] == ':') {
			dotFound = true;
		}
		else if (dotFound) {
			part2 += primary[i];
		}
		else{
			part1 += primary[i];
		}
	}

}

inline void tripleDotSplit(std::string primary, std::string& part1, std::string& part2, std::string& part3) {
	int countDots =0;
	int i = 0;
	part1 = ""; part2 = ""; part3 = "";
	while (i < primary.size() && countDots == 0) {
		if (primary[i] != ':') {
			part1 += primary[i];
		}
		else {
			countDots++;
		}
		i++;
	}
	while (i < primary.size() && countDots == 1) {
		if (primary[i] != ':') {
			part2 += primary[i];
		}
		else {
			countDots++;
		}
		
		i++;
	}
	while (i < primary.size() && countDots == 2) {
		if (primary[i] != ':') {
			part3 += primary[i];
		}
		else {
			countDots++;
		}
		i++;
	}

}

inline int sign(float x) {
	if (x < 0) {
		return -1;
	}
	else if (x > 0) {
		return 1;
	}
	else {
		return 0;
	}


}