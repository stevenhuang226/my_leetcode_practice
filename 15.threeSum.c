#include "shdstd.h"

int cmp32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int **threeSum(int *nums, int size, int *ret_size, int **ret_col_size)
{
	if (size < 3) {
		*ret_size = 0;
		return NULL;
	}

	int **tmp = malloc(size * 20 * sizeof(int *));
	int *tmp_flat = malloc(size * 20 * 3 * sizeof(int));
	int tmp_count = 0;

	for (int i = 0; i < size * 20; ++i) {
		tmp[i] = tmp_flat + i * 3;
	}

	qsort(nums, size, sizeof(int), cmp32);

	if (nums[0] > 0) {
		*ret_size = 0;
		return NULL;
	}

	for (int i = 0; i < size - 2; ++i) {
		if (i != 0 && nums[i] == nums[i-1]) {
			continue;
		}
		
		int left = i + 1;
		int right = size - 1;

		while (left < right) {
			int sum = nums[left] + nums[right] + nums[i];

			if (sum < 0) {
				++left;
				continue;
			}
			if (sum > 0) {
				--right;
				continue;
			}

			tmp[tmp_count][0] = nums[i];
			tmp[tmp_count][1] = nums[left];
			tmp[tmp_count][2] = nums[right];
			++tmp_count;
			++left;
			while (left < right && nums[left] == nums[left-1]) ++left;
		}
	}

	*ret_size = tmp_count;
	int **ret = malloc(tmp_count * sizeof(int *));

	*ret_col_size = malloc(tmp_count * sizeof(int));

	for (int i = 0; i < tmp_count; ++i) {
		(*ret_col_size)[i] = 3;
		ret[i] = malloc(3 * sizeof(int));

		ret[i][0] = tmp[i][0];
		ret[i][1] = tmp[i][1];
		ret[i][2] = tmp[i][2];
	}

	free(tmp);
	free(tmp_flat);

	return ret;
}
