#include "shdstd.h"

int compare(const void *l, const void *r)
{
	return *(int *)r - *(int *)l;
}

int minimumBoxes(int *apple, int apple_size, int *capacity, int capacity_size)
{
	int apple_count = 0;
	for (int i = 0; i < apple_size; ++i) {
		apple_count += apple[i];
	}

	qsort(capacity, capacity_size, sizeof(int), compare);

	for (int i = 0; i < capacity_size; ++i) {
		apple_count -= capacity[i];

		if (apple_count <= 0) {
			return i + 1;
		}
	}

	return capacity_size;
}
