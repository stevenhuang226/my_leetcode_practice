#include "shdstd.h"

typedef struct {
	int sum;
	int left_index;
} SumPair;

int cmp_pair(const void *left, const void *right)
{
	SumPair *pair_left = *(SumPair *)left;
	SumPair *pair_right = *(SumPair *)right;

	if (pair_left->sum == pair_right->sum) {
		return pair_left->left_index - pair_right->left_index;
	}
	return pair_left->sum - pair_right->sum;
}

int minimumPairRemoval(int *nums, int size)
{
	SumPair *sum_pairs = malloc((size-1) * sizeof(SumPair));

	for (int i = 0; i < size - 1; ++i) {
		sum_pairs[i].left_index = i;
		sum_pairs[i].sum = nums[i] + nums[i+1];
	}
}
