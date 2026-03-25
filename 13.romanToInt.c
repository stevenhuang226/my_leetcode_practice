#include "shdstd.h"

int romanToInt(char *s)
{
	/*
	 * I -> check next [V,X]
	 * X -> check next [L,C]
	 * C -> check next [D,M]
	 */

	int sum = 0;

	int c;
	int ptr = 0;
	while ((c = s[ptr++]) != '\0') {
		if (c == 'I') {
			if (s[ptr] == 'V') {
				sum += 4;
				++ptr;
			} else if (s[ptr] == 'X') {
				sum += 9;
				++ptr;
			} else {
				sum += 1;
			}
		} else if (c == 'V') {
			sum += 5;
		} else if (c == 'X') {
			if (s[ptr] == 'L') {
				sum += 40;
				++ptr;
			} else if (s[ptr] == 'C') {
				sum += 90;
				++ptr;
			} else {
				sum += 10;
			}
		} else if (c == 'L') {
			sum += 50;
		} else if (c == 'C') {
			if (s[ptr] == 'D') {
				sum += 400;
				++ptr;
			} else if (s[ptr] == 'M') {
				sum += 900;
				++ptr;
			} else {
				sum += 100;
			}
		} else if (c == 'D') {
			sum += 500;
		} else if (c == 'M') {
			sum += 1000;
		}
	}

	return sum;
}
