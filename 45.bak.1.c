#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int32_t jump(int32_t *nums, int32_t size)
{
	int32_t *step_arr = malloc(size * sizeof(int32_t));
	int32_t i, i2;

	for (i = 0; i < size; ++i) {
		step_arr[i] = INT_MAX;
	}
	step_arr[0] = 0;

	for (i = 0; i < size; ++i) {
		int32_t step = step_arr[i];
		int32_t max_forward = MIN(size, i + nums[i] + 1);

		for (i2 = i + 1; i2 < max_forward; ++i2) {
			step_arr[i2] = MIN(step_arr[i2], step + 1);
		}
	}

	int32_t res = step_arr[size - 1];

	free(step_arr);

	return res;
}
