#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
static int lower_bound(int64_t *arr, int64_t target, int left, int right)
{
	int L = left;
	int R = right;

	while (L < R) {
		int mid = (L + R) / 2;
		if (arr[mid] < target) {
			L = mid + 1;
		} else {
			R = mid;
		}
	}
	if (L >= right) {
		return -1;
	}
	return L;
}

int cmp_i32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int cmp_i64(const void *l, const void *r)
{
	if (*(int64_t *)l < *(int64_t *)r) {
		return -1;
	} else if (*(int64_t *)l > *(int64_t *)r) {
		return 1;
	} else {
		return 0;
	}
}

int maxDistance(int64_t side, int **points, int size, int *col_size, int k)
{
	int ext_size = size * 2;
	int64_t *extended = malloc(ext_size * sizeof(int64_t));
	for (int i = 0; i < size; ++i) {
		int x = points[i][0];
		int y = points[i][1];
		if (y == 0) {
			extended[i] = x; continue;
		}
		if (x == 0) {
			extended[i] = 4 * side - y; continue;
		}
		if (x == side) {
			extended[i] = side + y; continue;
		}
		if (y == side) {
			extended[i] = 3 * side - x; continue;
		}
	}

	qsort(extended, size, sizeof(int64_t), cmp_i64);

	for (int i = 0; i < size; ++i) {
		extended[i + size] = extended[i] + 4 * side;
	}

	int64_t d_left = 0;
	int64_t d_right = 2 * side;

	int64_t best = 0;

	while (d_left <= d_right) {
		int64_t mid = (d_left + d_right) / 2;
		int8_t res = false;

		for (int i = 0; i < size; ++i) {
			int64_t prev = extended[i];
			int prev_id = i;
			int8_t brk = false;

			for (int i2 = 0; i2 < k - 1; ++i2) {
				int next = lower_bound(extended, prev + mid, prev_id + 1, i + size);
				if (next < 0) {
					brk = true; break;
				}
				prev = extended[next];
				prev_id = next;
			}

			if (brk) continue;

			if (extended[i+size] - prev < mid) continue;

			best = MAX(best, mid);
			res = true;
			break;
		}

		if (res) {
			d_left = mid+1;
		} else {
			d_right = mid-1;
		}
	}

	free(extended);
	return best;
}
