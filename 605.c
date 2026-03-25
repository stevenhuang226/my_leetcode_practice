#include "shdstd.h"

bool canPlaceFlowers(int *flowerbed, int size, int n)
{
	int i;
	int availble_bed = 0;

	for (i = 0; i < size; ++i) {
		int prev = (i == 0 || flowerbed[i-1] == 0);
		int next = (i == size - 1 || flowerbed[i+1] == 0);
		int curr = flowerbed[i] == 0;
		if (prev && next && curr) {
			++availble_bed;
			++i;
		}
	}

	return (n <= availble_bed);
}

int main()
{
	int nums[] = {1,0,0,0,0,1};
	int size = sizeof(nums) / sizeof(nums[0]);
	int n = 2;

	printf("%d\n", canPlaceFlowers(nums, size, n));

	return 0;
}
