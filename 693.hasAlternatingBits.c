#include "shdstd.h"

bool hasAlternatingBits(int n)
{
	int8_t last_bit = n & 1;
	n >>= 1;

	while (n) {
		if ((n & 1) == last_bit) {
			return false;
		}
		last_bit = n & 1;
		n >>= 1;
	}

	return true;
}

int main()
{
	int n = 4;

	int8_t res = hasAlternatingBits(n);

	printf("%d\n", res);

	return 0;
}
