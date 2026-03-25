#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define INF32 (INT32_MAX / 4)

int minCost(int **grid, int size, int *col_size, int tele_lim)
{
	int rows = size;
	int cols = col_size[0];

	int ***cost = malloc((tele_lim + 1) * sizeof(int **));
	int **cost_flat = malloc((tele_lim + 1) * rows * sizeof(int *));
	int *cost_flat2 = malloc((tele_lim +1) * rows * cols * sizeof(int));
	for (int i = 0; i < tele_lim + 1; ++i) {
		cost[i] = cost_flat + i * rows;
		for (int i2 = 0; i2 < rows; ++i2) {
			cost[i][i2] = cost_flat2 + i2 * cols;
			for (int i3 = 0; i3 < cols; ++i3) {
				cost[i][i2][i3] = INF32;
			}
		}
	}

	cost[0][0][0] = 0;

	int max_val = 0;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			max_val = MAX(max_val, grid[r][c]);
		}
	}

	int *min_cost_from_ge_val = malloc((max_val+2) * sizeof(int));
	int *next_min_cost_from_ge_val = malloc((max_val+2) * sizeof(int));

	for (int i = 0; i < max_val + 2; ++i) {
		next_min_cost_from_ge_val[i] = INF32;
		min_cost_from_ge_val[i] = INF32;
	}

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int value = grid[r][c];

			if (r > 0) {
				int top = cost[0][r-1][c] + value;
				cost[0][r][c] = MIN(cost[0][r][c], top);
			}
			if (c > 0) {
				int left = cost[0][r][c-1] + value;
				cost[0][r][c] = MIN(cost[0][r][c], left);
			}

			max_val = MAX(max_val, value);
			next_min_cost_from_ge_val[value] = MIN(
					next_min_cost_from_ge_val[value],
					cost[0][r][c]);
		}
	}

	for (int used = 1; used <= tele_lim; ++used) {
		int *tmp = min_cost_from_ge_val;
		min_cost_from_ge_val = next_min_cost_from_ge_val;
		next_min_cost_from_ge_val = tmp;

		for (int i = max_val; i >= 0; --i) {
			min_cost_from_ge_val[i] = MIN(
					min_cost_from_ge_val[i],
					min_cost_from_ge_val[i+1]);
			next_min_cost_from_ge_val[i] = INF32;
		}

		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				int value = grid[r][c];

				cost[used][r][c] = MIN(cost[used-1][r][c],
						min_cost_from_ge_val[value]
						);

				if (r > 0) {
					int top = cost[used][r-1][c] + value;
					cost[used][r][c] = MIN(cost[used][r][c], top);
				}
				if (c > 0) {
					int left = cost[used][r][c-1] + value;
					cost[used][r][c] = MIN(cost[used][r][c], left);
				}

				next_min_cost_from_ge_val[value] = MIN(
						next_min_cost_from_ge_val[value],
						cost[used][r][c]);
			}
		}
	}

	int min_cost = INF32;
	for (int i = 0; i <= tele_lim; ++i) {
		min_cost = MIN(min_cost, cost[i][rows-1][cols-1]);
	}

	free(cost_flat2);
	free(cost_flat);
	free(cost);
	free(min_cost_from_ge_val);
	free(next_min_cost_from_ge_val);

	if (min_cost == INF32) {
		return -1;
	}

	return min_cost;
}
