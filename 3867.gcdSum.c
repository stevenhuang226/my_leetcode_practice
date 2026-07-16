#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int64_t sgcd(int64_t a, int64_t b)
{
	while (b) {
		int64_t t = a % b;
		a = b;
		b = t;
	}
	return a;
}

int cmp_i64(const void *l, const void *r)
{
	if (*(int64_t *)l > *(int64_t *)r) {
		return 1;
	} else if (*(int64_t *)l < *(int64_t *)r) {
		return -1;
	} else {
		return 0;
	}
}

int64_t gcdSum(int *nums, int size)
{
	int64_t *prefix_gcd = malloc(size * sizeof(int64_t));

	int mx = 0;
	for (int i = 0; i < size; ++i) {
		int curr = nums[i];
		mx = MAX(mx, curr);
		prefix_gcd[i] = sgcd(curr, mx);
	}

	qsort(prefix_gcd, size, sizeof(int64_t), cmp_i64);

	int64_t sum = 0;
	for (int L = 0; L * 2 + 1 < size; ++L) {
		int R = size - L - 1;

		int64_t left = prefix_gcd[L];
		int64_t right = prefix_gcd[R];

		sum += sgcd(left, right);
	}

	free(prefix_gcd);

	return sum;
}
