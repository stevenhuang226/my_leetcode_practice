#include "shdstd.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MOD 1000000007
#define INF8 (INT8_MAX / 4)
#define INF16 (INT16_MAX / 4)
#define INF32 (INT32_MAX / 4)
#define INF64 (INT64_MAX / 4)
#define NEG_INF8 -(INF8)
#define NEG_INF16 -(INF16)
#define NEG_INF32 -(INF32)
#define NEG_INF64 -(INF64)

double findMaxAverage(int *nums, int size, int k)
{
	int sum = 0;
	int max;

	for (int i = 0; i < k; ++i) {
		sum += nums[i];
	}
	max = sum;

	for (int i = k; i < size; ++i) {
		int drop = nums[i-k];
		int add = nums[i];

		sum -= drop;
		sum += add;

		max = MAX(max, sum);
	}

	double ret = (double)max;

	return ret / k;
}
