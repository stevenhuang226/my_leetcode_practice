#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

int maximumEnergy(int *energy, int energySize, int k)
{
	int i,ii;
	int max = INT_MIN;
	for (i = 1; i <= k; i++) {
		int suf = 0;
		int best = INT_MIN;
		for (ii = energySize - i; ii >= 0; ii -= k) {
			suf += energy[ii];
			if (suf > best) best = suf;
		}
		if (best > max) max = best;
	}

	return max;
}
