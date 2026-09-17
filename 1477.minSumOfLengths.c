#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define INF32 (INT32_MAX / 4)
int minSumOfLengths(int *arr, int arr_size, int target)
{
	int l = 0;
	int curr = 0;

	int *best = malloc((arr_size+1) * sizeof(int));
	for (int i = 0; i <= arr_size; ++i) {
		best[i] = INF32;
	}

	int best_sum = INF32;
	for (int r = 0; r < arr_size; ++r) {
		curr += arr[r];
		while (l < r && curr > target) {
			curr -= arr[l++];
		}

		best[r+1] = best[r];

		if (curr != target)
			continue;

		int len = r - l + 1;
		best_sum = MIN(best_sum, best[l] + len);
		best[r+1] = MIN(best[r], len);

	}

	free(best);

	if (best_sum >= INF32) {
		return -1;
	}
	return best_sum;
}

int test1()
{
	int arr[] = {1,6,1};
	int arr_sz = sizeof(arr) / sizeof(arr[0]);

	int trg = 7;

	return minSumOfLengths(arr, arr_sz, trg);
}

int test2()
{
	int arr[] = {3, 2, 2, 4, 3};
	int arr_sz = sizeof(arr) / sizeof(arr[0]);

	int trg = 3;

	return minSumOfLengths(arr, arr_sz, trg);
}

int test3()
{
	int arr[] = {2,1,3,3,2,3,1};
	int arr_sz = sizeof(arr) / sizeof(arr[0]);

	int trg = 6;

	return minSumOfLengths(arr, arr_sz, trg);
}

int main()
{
	printf("test1: %d e: -1\n", test1());
	printf("test2: %d e: 2\n", test2());
	printf("test3: %d e: 5\n", test3());
	return 0;
}
