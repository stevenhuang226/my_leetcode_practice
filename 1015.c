#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


int smallestRepunitDivByK(int k)
{
	if (k % 2 == 0 || k % 5 == 0) return -1;

	int i;
	int n = 0;
	for (i = 0; i < k; ++i) {
		n *= 10;
		n += 1;

		n = n % k;

		if (n == 0) {
			return i+1;
		}
	}

	return -1;
}

int main()
{
	int k = 23;
	int res = smallestRepunitDivByK(k);

	printf("res:%d\n", res);

	return 0;
}
