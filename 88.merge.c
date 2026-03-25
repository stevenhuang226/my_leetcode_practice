#include "shdstd.h"

void merge(int *numsa, int a_size, int m, int *numsb, int b_size, int n)
{
	int ptra = m - 1;
	int ptrb = n - 1;
	int retptr = a_size - 1;

	while (ptra >= 0 && ptrb >= 0) {
		if (numsa[ptra] > numsb[ptrb]) {
			numsa[retptr--] = numsa[ptra--];
		} else {
			numsa[retptr--] = numsb[ptrb--];
		}
	}

	while (ptra >= 0) {
		numsa[retptr--] = numsa[ptra--];
	}
	while (ptrb >= 0) {
		numsa[retptr--] = numsb[ptrb--];
	}
}
