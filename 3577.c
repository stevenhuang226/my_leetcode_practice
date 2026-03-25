#include "shdstd.h"

#define MOD 1000000007
int countPermutations(int *complexity, int size)
{
	int i;

	int init = complexity[0];

	for (i = 1; i < size; ++i) {
		int num = complexity[i];
		if (num <= init) {
			return 0;
		}
	}

	int64_t ans = 1;

	for (i = 1; i < size; ++i) {
		ans *= i;

		ans %= MOD;
	}

	return ans;
}
