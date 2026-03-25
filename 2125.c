#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int numberOfBeams(char **bank, int bankSize)
{
	int i,ii;
	char *row;

	int prev = 0;
	int sum = 0;
	for (i = 0; i < bankSize; ++i) {
		row = bank[i];
		int devs = 0;
		for (ii = 0; row[ii] != '\0'; ++ii) {
			devs += (row[ii] == '1');
		}
		if (devs == 0) continue;
		sum += prev * devs;
		prev = devs;
	}

	return sum;
}
