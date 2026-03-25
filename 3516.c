#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int main()
{
}

int findClosest(int x, int y, int z)
{
	int xz = abs(x - z);
	int yz = abs(y - z);

	if (xz < yz) {
		return 1;
	}
	if (yz < xz) {
		return 2;
	}
	return 0;
}
