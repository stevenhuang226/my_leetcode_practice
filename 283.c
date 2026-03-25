#include "shdstd.h"

void moveZeroes(int *nums, int size)
{
	int pz = 0;
	int pnz = 0;

	for (;;) {
		while (pz < size && nums[pz] != 0) {
			++pz;
		}
		while (pnz < size && (nums[pnz] == 0 || pz > pnz)) {
			++pnz;
		}

		if (pz >= size || pnz >= size) {
			break;
		}

		nums[pz] = nums[pnz];
		nums[pnz] = 0;
	}

	return;
}
