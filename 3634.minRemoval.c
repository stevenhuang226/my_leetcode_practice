#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int cmp32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int minRemoval(int *nums, int size, int k)
{
	int min_remove = INT32_MAX;

	qsort(nums, size, sizeof(int), cmp32);

	for (int i = 0; i < size; ++i) {
		if (i >= min_remove) {
			break;
		}

		int num = nums[i];

		int left = i + 1;
		int right = size;

		int trg = MIN(INT32_MAX, (int64_t)num * k);

		while (left < right) {
			int mid = left + (right - left) / 2;

			if (nums[mid] > trg) {
				right = mid;
			} else {
				left = mid + 1;
			}
		}

		int rm = i + (size - right);

		min_remove = MIN(min_remove, rm);
	}

	return min_remove;
}

int main()
{
	int nums[] = {2,1,5};
	int size = sizeof(nums) / sizeof(nums[0]);
	int k = 2;

	int res = minRemoval(nums, size, k);

	printf("res: %d\n", res);

	return 0;
}
