#include "shdstd.h"

#define TREE_LIMIT 20

#define LOWBIT(x) ((x) & (-(x)))

typedef struct {
	int *tree;
	int size;
} NumArray;

int query(NumArray *obj, int target)
{
	int sum = 0;

	int *tree = obj->tree;
	int tree_size = obj->size;
	
	while (target > 0) {
		sum += tree[target];
		target -= LOWBIT(target);
	}

	return sum;
}

int8_t raw_update(NumArray *obj, int index, int val)
{
	int *tree = obj->tree;
	int tree_size = obj->size;
	
	if (index <= 0) return -1;

	while (index < tree_size) {
		tree[index] += val;
		index += LOWBIT(index);
	}

	return 0;
}

NumArray* numArrayCreate(int *nums, int size)
{
	NumArray *obj = malloc(sizeof(NumArray));
	
	obj->size = TREE_LIMIT;
	obj->tree = calloc(obj->size, sizeof(int));
	
	int i;
	for (i = 0; i < size; ++i) {
		raw_update(obj, i + 1, nums[i]);
	}

	return obj;
}

void numArrayUpdate(NumArray *obj, int index, int val)
{
	int old = query(obj, index+1) - query(obj, index);
	int offset = val - old;

	raw_update(obj, index+1, offset);
}

int numArraySumRange(NumArray *obj, int left, int right)
{
	int left_prefix = query(obj, left);
	int right_prefix = query(obj, right+1);

	return right_prefix - left_prefix;
}

void numArrayFree(NumArray *obj)
{
	free(obj->tree);
	free(obj);
}

/**
 * Your NumArray struct will be instantiated and called as such:
 * NumArray* obj = numArrayCreate(nums, numsSize);
 * numArrayUpdate(obj, index, val);
 
 * int param_2 = numArraySumRange(obj, left, right);
 
 * numArrayFree(obj);
*/
