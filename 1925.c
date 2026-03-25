#include "shdstd.h"

int32_t countTriples(int32_t n)
{
	int32_t i, i2;
	
	int32_t count = 0;

	int8_t sqr[(n+1) * (n+1)];
	memset(sqr, 0x00, sizeof(sqr));

	for (i = 1; i <= n; ++i) {
		sqr[i * i] = 2;
	}

	for (i = 1; i < n; ++i) {
		for (i2 = i; i * i + i2 * i2 <= n * n; ++i2) {
			count += sqr[i * i + i2 * i2];
		}
	}

	return count;
}

int main()
{
	int n = 5;

	int res = countTriples(n);
	printf("%d\n", res);

	return 0;
}
