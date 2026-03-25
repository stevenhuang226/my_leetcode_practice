#include "shdstd.h"

int64_t getDescentPeriods(int *prices, int size)
{
	if (size == 1) {
		return 1;
	}

	int64_t sum = 1;
	int start = (prices[0] - prices[1] == 1) ? 0 : 1;
	int i;

	for (i = 1; i < size; ++i) {
		int prev = prices[i - 1];
		int curr = prices[i];
		if (prev - curr == 1) {
			sum += (i - start) + 1;
			continue;
		}
		sum += 1;
		start = i;
	}

	return sum;
}

int main()
{
	int nums[] = {3,2,1,4};
	int size = sizeof(nums) / sizeof(nums[0]);
	printf("%lld\n", getDescentPeriods(nums, size));

	return 0;
}
