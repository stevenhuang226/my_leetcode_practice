#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define OFFSET 10001 /* leetcode 315 only reach - 10^4, because fenwick tree require 1 base (lowbit require non zero */
#define TREE_SIZE 100001
#define LOWBIT(x) ((x) & (-(x)))
uint32_t *tree;

void update_one(uint32_t index)
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSmaller(int *nums, int numsSize, int *returnSize)
{
	tree = calloc(TREE_SIZE, sizeof(uint32_t));
	int *res = malloc(numsSize * sizeof(int));

	int i;
	for (i = numsSize - 1; i >= 0; --i) {
		/* tran int to uint32_t */
		uint32_t target = (int64_t)nums[i] + OFFSET;
		res[i] = query(target - 1);
		update_one(target);
	}

	*returnSize = numsSize;
	return res;
}
