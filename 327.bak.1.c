#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TREE_SIZE 200008
#define LOWBIT(x) ((x) & (-(x)))

#define OFS 100004 /* 2^31 + 1 */

uint32_t *tree;

void update(uint32_t index)
{
	while (index < TREE_SIZE) {
		++tree[index];
		index += LOWBIT(index);
	}
	return;
}

uint32_t query(uint32_t target)
{
	uint32_t sum = 0;
	while (target > 0) {
		sum += tree[target];
		target -= LOWBIT(target);
	}

	return sum;
}

int countRangeSum(int *nums, int numsSize, int lower, int upper)
{
	/* using fenwick tree, update all of nums[i] in it.
	 * then query lower-1 get suffix
	 * query upper get prefix
	 *
	 * prefix - suffix -> result
	 */
	tree = calloc(TREE_SIZE, sizeof(uint32_t));

	int i;
	for (i = 0; i < numsSize; ++i) {
		uint32_t index = nums[i] + OFS;
		update(index);
	}

	uint32_t lower_prefix = query((uint32_t)(lower + OFS - 1));
	printf("%d\n", lower_prefix);
	uint32_t upper_prefix = query((uint32_t)(upper + OFS));
	printf("%d\n", upper_prefix);
	
	free(tree);

	return (int)(upper_prefix - lower_prefix);
}

int main()
{
	int nums[] = { -2, 5, 1 };
	int lower = -2;
	int upper = 2;
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = countRangeSum(nums, size, lower, upper);

	printf("%d\n", res);

	return 0;
}
