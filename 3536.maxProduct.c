#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int maxProduct(int n)
{
	int digits[10];
	int d = 0;
	while (n) {
		digits[d++] += n % 10;
		n /= 10;
	}

	int best = 0;
	for (int i = 0; i < d; ++i) {
		for (int i2 = i+1; i2 < d; ++i2) {
			int pro = digits[i] * digits[i2];
			best = MAX(best, pro);
		}
	}

	return best;
}
