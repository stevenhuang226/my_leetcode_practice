#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int minEatingSpeed(int *piles, int piles_size, int h)
{
	int i;

	int l = 1;
	int r;
	for (i = 0; i < piles_size; ++i) {
		int n = piles[i];
		if (n > r) r = n;
	}

	while (l < r) {
		int mid = (l + r) / 2;
		int sum = 0;
		for (i = 0; i < piles_size; ++i) {
			int pile = piles[i];
			sum += ((pile / mid) + (!(pile%mid == 0)));
		}
		if (sum > h) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}
	return l;
}
