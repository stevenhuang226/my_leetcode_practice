#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

#define MAX_NUM 100004

static int32_t sum_freq[MAX_NUM];
static int32_t prev_freq[MAX_NUM];

int32_t specialTriplets(int32_t *nums, int32_t size)
{
	memset(sum_freq, 0x00, sizeof(sum_freq));
	memset(prev_freq, 0x00, sizeof(prev_freq));

	int i;
	for (i = 0; i < size; ++i) {
		int num = nums[i];
		++sum_freq[num];
	}

	int64_t count = 0;
	for (i = 0; i < size; ++i) {
		int64_t num = nums[i];
		int64_t target = num * 2;

		++prev_freq[num];
		if (target >= MAX_NUM) {
			continue;
		}

		int64_t prev = prev_freq[target] - (target == num);
		int64_t suff = sum_freq[target] - prev_freq[target];
		count += prev * suff;
	}

	return (int32_t)(count % MOD);
}
