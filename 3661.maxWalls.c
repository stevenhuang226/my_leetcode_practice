#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
	int pos;
	int dist;
} Robot;

int cmp_Robot(const void *l, const void *r)
{
	return (*(Robot *)l).pos - (*(Robot *)r).pos;
}


int cmp_32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int between(int *arr, int arr_size, int src, int dst)
{
	if (src > dst) return 0;

	int left, right;
	left = 0; right = arr_size;
	while (left < right) {
		int mid = (left + right) / 2;
		if (arr[mid] < src) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}
	int src_id = left;

	left = 0; right = arr_size;
	while (left < right) {
		int mid = (left + right) / 2;
		if (arr[mid] <= dst) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}
	int dst_id = left;

	return dst_id - src_id;
}

int maxWalls(int *position, int pos_size,
	int *distance, int dist_size,
	int *walls, int walls_size)
{
	int size = pos_size;

	Robot *robots = malloc(size * sizeof(Robot));
	for (int i = 0; i < size; ++i) {
		robots[i].pos = position[i];
		robots[i].dist = distance[i];
	}

	qsort(robots, size, sizeof(Robot), cmp_Robot);
	qsort(walls, walls_size, sizeof(int), cmp_32);

	int (*dp)[2] = malloc((size+1) * sizeof(int[2]));
	dp[0][0] = 0; dp[0][1] = 0;

	for (int i = 0; i < size; ++i) {
		int r_lim = robots[i].pos + robots[i].dist;
		if (i + 1 < size) {
			r_lim = MIN(r_lim, robots[i+1].pos - 1);
		}

		int go_r = between(walls, walls_size,
			robots[i].pos, r_lim);
		dp[i+1][1] = MAX(dp[i][1], dp[i][0]) + go_r;

		int l_lim = robots[i].pos - robots[i].dist;
		if (i - 1 >= 0) {
			l_lim = MAX(l_lim, robots[i-1].pos + 1);
		}
		int go_l_pl = between(walls, walls_size, // curr go left and prev also go left
			l_lim, robots[i].pos);

		if (i - 1 >= 0) {
			l_lim = MAX(l_lim, robots[i-1].pos + robots[i-1].dist + 1);
		}
		int go_l_pr = between(walls, walls_size, // curr go left but prev go right
			l_lim, robots[i].pos);

		dp[i+1][0] = MAX((dp[i][0] + go_l_pl), (dp[i][1] + go_l_pr));
	}

	int res = MAX(dp[size][0], dp[size][1]);

	free(dp);
	free(robots);

	return res;
}
