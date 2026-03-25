#include "shdstd.h"

char findKthBit(int n, int k)
{
	int length = (1 << n) - 1;
	int target = k - 1;

	int8_t invert = false;

	while (length > 1) {
		int mid = length >> 1; /* length / 2 */

		if (target == mid) {
			return ! invert + '0';
		}

		if (target > mid) {
			target = length - 1 - target;
			invert = !invert;
		}

		length = mid;
	}

	return invert + '0';
}

int main()
{
	int n = 3;
	int k = 7;

	int res = findKthBit(n,k);
	printf("%c\n", res);

	return 0;
}
