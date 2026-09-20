#include "shdstd.h"

int reverseDegree(char *s)
{
	int sum = 0;
	int p = 0;
	int ch;

	while ((ch = s[p++]) != '\0') {
		sum += (26 - ch + 'a') * p;
	}

	return sum;
}
