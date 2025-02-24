#pragma once

#include <cstdlib>
#include <ctime>

inline short int new_rnd_num(int upTo) {
	if (upTo != 0) {
		return (rand() % upTo); //number between 0 and num
	}
	else {
		return 1;
	}
}