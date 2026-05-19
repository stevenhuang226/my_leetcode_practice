#include "shdstd.h"

int getCommon(int *numsa, int a_size, int *numsb, int b_size)
{
	int ptra = 0;
	int ptrb = 0;

	while (ptra < a_size && ptrb < b_size) {
		if (numsa[ptra] == numsb[ptrb]) {
			return numsa[ptra];
		}

		if (numsa[ptra] > numsb[ptrb]) {
			++ptrb;
		} else {
			++ptra;
		}
	}

	return -1;
}
