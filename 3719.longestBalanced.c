#include "shdstd.h"

/*
 * auth: stevenhuang.dog@gmail.com
 */

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define EXP_SIZE (1e5 + 8)

int longestBalanced(int *nums, int size)
{
	int *mrk = calloc(EXP_SIZE, sizeof(int));

	int longest = 0;

	for (int left = 0; left < size; ++left) {
		int right;
		int odds = 0;
		int evens = 0;
		for (right = left; right < size; ++right) {
			int num = nums[right];
			++mrk[num];

			if (mrk[num] == 1) {
				evens += (num % 2 == 0);
				odds += (num % 2 == 1);
			}

			if (evens == odds) {
				int length = right - left + 1;
				longest = MAX(longest, length);
			}
		}
		for (--right; right >= left; --right) {
			int num = nums[right];
			--mrk[num];
		}
	}

	free(mrk);

	return longest;
}

int main()
{
	int nums[] = {1,2,3,2};
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = longestBalanced(nums, size);

	printf("%d\n", res);

	return 0;
}
