#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int minPartitions(char *n)
{
	int len = strlen(n);

	int max = 0;

	for (int i = 0; i < len; ++i) {
		int digital = n[i] - '0';
		max = MAX(max, digital);
	}

	return max;
}
