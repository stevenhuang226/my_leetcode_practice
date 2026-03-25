#include "shdstd.h"

/*
int64_t sum_1ton(int64_t n)
{
	return n * n  - (n * n - n) / 2;
}
*/

int64_t sum_1ton_sqrt(int64_t n)
{
	n *= 2;

	int64_t left = 0;
	int64_t right = INT32_MAX;

	while (left <= right) {
		int64_t mid = ((left + right) / 2);
		if (mid * (mid + 1) <= n) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

	return right;
}
int64_t minNumberOfSeconds(int _mountain_height, int *worker_times, int worker_times_size)
{
	int64_t mountain_height = (int64_t)_mountain_height;

	int64_t bottom = 0;
	int64_t top = INT64_MAX / 8;

	while (bottom < top) {
		int64_t mid = (bottom + top) / 2;

		int64_t reduce = 0;
		for (int i = 0; i < worker_times_size; ++i) {
			/*
			reduce += sum_1ton_sqrt(mid / worker_times[i]);
			*/

			int64_t t = worker_times[i];
			int64_t n = mid / t;
			reduce += (sqrt(1 + 8*n) - 1) / 2;
		}

		if (reduce < mountain_height) {
			bottom = mid + 1;
		} else {
			top = mid;
		}
	}

	return bottom;
}
