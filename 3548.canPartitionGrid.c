#include "shdstd.h"

/*
 * this code run very slow on leetcode test case.
 *
 * if you want less runtime. try to move freq_a and freq_b into stack instead of heap. That will be extremely faster (I ask GPT to edit my code. And get ~40ms)
 *
 * But anyway I love alloc more. So I keep this code using heap.
 */

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

bool canPartitionGrid(int **grid, int grid_size, int *grid_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int min_num = INT32_MAX;
	int max_num = 0;

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int num = grid[r][c];
			min_num = MIN(min_num, num);
			max_num = MAX(max_num, num);
		}
	}

	int offset = -min_num;

	int64_t exp_max = max_num - min_num + 1;
	uint16_t *freq_a = malloc(exp_max * sizeof(uint16_t));
	uint16_t *freq_b = malloc(exp_max * sizeof(uint16_t));

	uint16_t *above = freq_a;
	uint16_t *below = freq_b;
	memset(above, 0, exp_max * sizeof(uint16_t));
	memset(below, 0, exp_max * sizeof(uint16_t));

	int64_t above_sum = 0;
	int64_t below_sum = 0;

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int num = grid[r][c];

			++below[num + offset];
			below_sum += num;
		}
	}

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int num = grid[r][c];

			++above[num + offset];
			above_sum += num;

			--below[num + offset];
			below_sum -= num;
		}

		if (above_sum == below_sum) {
			goto _ret_true;
		}

		if (above_sum > below_sum) {
			int64_t diff = above_sum - below_sum;
			if (diff < min_num || diff > max_num || above[diff + offset] <= 0) {
				continue;
			}
			if (r == 0 && diff != grid[0][0] && diff != grid[0][cols-1]) {
				continue;
			}
			if (cols == 1 && diff != grid[r][0] && diff != grid[0][0]) {
				continue;
			}
			goto _ret_true;
		} else {
			int64_t diff = below_sum - above_sum;
			if (diff < min_num || diff > max_num || below[diff + offset] <= 0) {
				continue;
			}
			if (r == rows-2 && diff != grid[rows-1][0] && diff != grid[rows-1][cols-1]) {
				continue;
			}
			if (cols == 1 && diff != grid[r][0] && diff != grid[rows-1][0]) {
				continue;
			}
			goto _ret_true;
		}
	}


	uint16_t *left = freq_a;
	uint16_t *right = freq_b;
	memset(left, 0, exp_max * sizeof(uint16_t));
	memset(right, 0, exp_max * sizeof(uint16_t));

	int64_t left_sum = 0;
	int64_t right_sum = 0;

	for (int c = 0; c < cols; ++c) {
		for (int r = 0; r < rows; ++r) {
			int num = grid[r][c];
			++right[num + offset];
			right_sum += num;
		}
	}

	for (int c = 0; c < cols; ++c) {
		for (int r = 0; r < rows; ++r) {
			int num = grid[r][c];

			++left[num + offset];
			left_sum += num;

			--right[num + offset];
			right_sum -= num;
		}

		if (left_sum == right_sum) {
			goto _ret_true;
		}

		if (left_sum > right_sum) {
			int64_t diff = left_sum - right_sum;
			if (diff < min_num || diff > max_num || left[diff + offset] <= 0) {
				continue;
			}
			if (c == 0 && diff != grid[0][0] && diff != grid[rows-1][0]) {
				continue;
			}
			if (rows == 1 && diff != grid[0][c] && diff != grid[0][0]) {
				continue;
			}
			goto _ret_true;
		} else {
			int64_t diff = right_sum - left_sum;
			if (diff < min_num || diff > max_num || right[diff + offset] <= 0) {
				continue;
			}
			if (c == cols-2 && diff != grid[0][cols-1] && diff != grid[rows-1][cols-1]) {
				continue;
			}
			if (rows == 1 && diff != grid[0][c] && diff != grid[0][cols-1]) {
				continue;
			}
			goto _ret_true;
		}
	}

	free(freq_a);
	free(freq_b);
	return false;

_ret_true:
	free(freq_a);
	free(freq_b);

	return true;
}
