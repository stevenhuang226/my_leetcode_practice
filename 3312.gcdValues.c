#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static inline int64_t choose2(int64_t c)
{
	return c * (c-1) / 2;
}

int *gcdValues(int *nums, int nums_size,
	int64_t *queries, int queries_size,
	int *ret_size)
{
	int num_max = 0;
	for (int i = 0; i < nums_size; ++i) {
		num_max = MAX(num_max, nums[i]);
	}
	++num_max;

	int *freq = calloc(num_max, sizeof(int));
	for (int i = 0; i < nums_size; ++i) {
		int num = nums[i]-1;
		++freq[num];
	}

	int *multiple = malloc(num_max * sizeof(int));
	for (int i = 0; i < num_max; ++i) {
		multiple[i] = 0;
		for (int i2 = i; i2 < num_max; i2 += (i+1)) {
			multiple[i] += freq[i2];
		}
	}

	int64_t *exact = malloc(num_max * sizeof(int64_t));
	for (int i = num_max-1; i >= 0; --i) {
		exact[i] = choose2(multiple[i]);

		int step = i+1;
		for (int i2 = i + step; i2 < num_max; i2 += step) {
			exact[i] -= exact[i2];
		}
	}

	free(freq);
	free(multiple);

	int64_t *prefix = malloc((num_max+1) * sizeof(int64_t));
	prefix[0] = 0;
	for (int i = 0; i < num_max; ++i) {
		prefix[i+1] = prefix[i] + exact[i];
	}

	free(exact);

	int *res = malloc(queries_size * sizeof(int));
	*ret_size = queries_size;
	for (int i = 0; i < queries_size; ++i) {
		int64_t query = queries[i];
		int L = 0;
		int R = num_max;
		while (L < R) {
			int M = (L + R) / 2;
			if (prefix[M] <= query) {
				L = M+1;
			} else {
				R = M;
			}
		}
		res[i] = L;
	}
	free(prefix);
	return res;
}
