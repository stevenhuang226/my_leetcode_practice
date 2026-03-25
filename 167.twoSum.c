#include "shdstd.h"

int *twoSum(int *nums, int size, int target, int *ret_size)
{
	int *result = malloc(2 * sizeof(int));
	*ret_size = 2;

	int left = 0;
	int right = size - 1;

	while (left < right) {
		int sum = nums[left] + nums[right];

		if (sum == target) {
			result[0] = left + 1;
			result[1] = right + 1;
			return result;
		}

		if (sum < target) {
			++left;
		} else {
			--right;
		}
	}

	return NULL;
}
