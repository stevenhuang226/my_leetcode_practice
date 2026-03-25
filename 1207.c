#include "shdstd.h"

#define INF32 (INT32_MAX / 4)
#define NEG_INF32 -(INF32)
#define MAX_DIFF 2001

int comp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

bool uniqueOccurrences(int *arr, int size)
{
	int8_t *mrk = calloc(1, MAX_DIFF * sizeof(int8_t));
	qsort(arr, size, sizeof(int), comp);
	int last = arr[0];

	int count = 0;
	for (int i = 1; i < size; ++i) {
		if (arr[i] == last) {
			++count;
			continue;
		}

		if (mrk[count]) {
			free(mrk);
			return false;
		}
		mrk[count] = 1;
		count = 0;
		last = arr[i];
	}
	if (mrk[count]) {
		free(mrk);
		return false;
	}

	free(mrk);
	return true;
}

int main()
{
	int nums[] = {-3,0,1,-3,1,1,1,-3,10,0};
	int size = sizeof(nums) / sizeof(nums[0]);

	bool res = uniqueOccurrences(nums, size);
	printf("res:%d", res);

	return 0;
}
