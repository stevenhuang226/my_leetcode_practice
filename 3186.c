#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include <math.h>

#define MAX_DAMAGE 11

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int64_t maximumTotalDamage(int *power, int powerSize)
{
	int i, ii;
	qsort(power, powerSize, sizeof(int), compare);

	uint64_t maxpos[3];
	maxpos[0] = 0;
	maxpos[1] = 0;
	maxpos[2] = 0;

	for (i = 0; i < powerSize; i++) {
		if (power[i] != 1) break;
		maxpos[1]++;
	}
	for (; i < powerSize; i++) {
		if (power[i] != 2) break;
		maxpos[2] += 2;
	}
	uint64_t last = 2;
	for (; i < powerSize; ) {
		uint64_t now = power[i];
		switch (now - last) {
			default:
				if (maxpos[2] > maxpos[0]) {
					maxpos[0] = maxpos[2];
				}
			case 2:
				if (maxpos[1] > maxpos[0]) {
					maxpos[0] = maxpos[1];
				}
				if (maxpos[2] > maxpos[1]) {
					maxpos[1] = maxpos[2];
				}
			case 1:
				break;
			case 0:
				break;
		}

		int l_i = i;
		for (i++; i < powerSize; i++) {
			if (now != power[i]) break;
		} 
		uint64_t max = maxpos[0] + now * (i - l_i);
		if (maxpos[2] > max) {
			max = maxpos[2];
		}
		if (maxpos[1] > max) {
			max = maxpos[1];
		}
		if (maxpos[1] > maxpos[0]) {
			maxpos[0] = maxpos[1];
		}
		maxpos[1] = maxpos[2];
		maxpos[2] = max;
		last = now;
	}
	if (maxpos[0] > maxpos[2]) {
		maxpos[2] = maxpos[0];
	}
	if (maxpos[1] > maxpos[2]) {
		maxpos[2] = maxpos[1];
	}


	return (int64_t)maxpos[2];
}

int main()
{
	int a[] = {6,4,1,6,7,1,4,7};
	int a_size = sizeof(a) / sizeof(a[0]);

	int64_t ans = maximumTotalDamage(a, a_size);
	printf("%" PRId64 "\n", ans);

	return 0;
}
