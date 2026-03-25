#include "shdstd.h"

int minFlips(int a, int b, int c)
{
	int count = 0;
	while (c || a || b) {
		int cb = c & 1;
		int ab = a & 1;
		int bb = b & 1;

		if (cb) {
			count += !(ab | bb);
		} else {
			count += ab + bb;
		}

		c >>= 1;
		a >>= 1;
		b >>= 1;
	}

	return count;
}

int main()
{
	int a = 8;
	int b = 3;
	int c = 5;

	printf("res: %d\n", minFlips(a, b, c));

	return 0;
}
