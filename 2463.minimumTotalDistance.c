#include "shdstd.h"

#define INF64 (INT64_MAX / 4)
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int cmp_i32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int cmp_Arr(const void *l, const void *r)
{
	return (*(int **)l)[0] - (*(int **)r)[0];
}

int64_t minimumTotalDistance(int *robot, int robot_size,
	int **factory, int factory_size, int *factory_col_size)
{
	qsort(robot, robot_size, sizeof(int), cmp_i32);
	qsort(factory, factory_size, sizeof(int *), cmp_Arr);

	uint64_t dp[robot_size][factory_size];
	for (int i = 0; i < robot_size; ++i) {
		for (int i2 = 0; i2 < factory_size; ++i2) {
			dp[i][i2] = INF64;
		}
	}

	int64_t l_cost = 0;
	for (int i = 0; i < robot_size && i < factory[0][1]; ++i) {
		l_cost += llabs((int64_t)robot[i] - factory[0][0]);
		dp[i][0] = l_cost;
	}

	for (int r = 0; r < robot_size; ++r) {
		for (int f = 1; f < factory_size; ++f) {
			int64_t cost = 0;
			int64_t f_pos = factory[f][0];
			int f_lim = factory[f][1];
			dp[r][f] = MIN(dp[r][f], dp[r][f-1]);

			for (int i = 0; i < f_lim && i <= r; ++i) {
				cost += llabs(robot[r-i] - f_pos);
				if (r-i > 0) {
					dp[r][f] = MIN(dp[r][f],
						dp[r-i-1][f-1] + cost);
				} else {
					dp[r][f] = MIN(dp[r][f], cost);
				}
			}
		}
	}

	return dp[robot_size-1][factory_size-1];
}
