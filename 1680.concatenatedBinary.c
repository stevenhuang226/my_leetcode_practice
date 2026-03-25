#include "shdstd.h"

#define MOD 1000000007
int concatenatedBinary(int n)
{
	int64_t res = 0;

	int64_t lim = 0x01;
	int offset = 1;

	for (int i = 1; i <= n; ++i) {
		int64_t num = i;
		if (num > lim) {
			lim = (lim << 1) | 0x01;
			++offset;
		}
		res = ((res << offset) | num) % MOD;
	}

	return res;
}
