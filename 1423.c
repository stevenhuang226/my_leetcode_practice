#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int maxScore(int *card_points, int size, int k)
{
	int i;

	int l = 0;
	int r;

	int total_sum = 0;
	int win_sum = 0;

	int min_win_sum = INT_MAX;

	for (r = 0, i = 0; r < (size - k); ++r, ++i) {
		total_sum += card_points[r];
		win_sum = total_sum;
	}
	for (; i < size; ++i) {
		total_sum += card_points[i];
	}

	while (r < size) {
		if (win_sum < min_win_sum) {
			min_win_sum = win_sum;
		}
		win_sum += card_points[r++];
		win_sum -= card_points[l++];
	}
	if (win_sum < min_win_sum) {
		min_win_sum = win_sum;
	}

	return total_sum - min_win_sum;
}

int main()
{
	int nums[] = {96,90,41,82,39,74,64,50,30};
	int k = 8;
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = maxScore(nums, size, k);
	printf("%d\n", res);

	return 0;
}
