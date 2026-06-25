#include "shdstd.h"

typedef struct {
	int size;
	int data[];
} FenwickTree;

FenwickTree *fenwick_create(int size)
{
	FenwickTree *tree = calloc(1, sizeof(FenwickTree) + size * sizeof(int));
	tree->size = size;

	return tree;
}

void fenwick_update(FenwickTree *tree, int pos, int delta)
{
	while (pos < tree->size) {
		tree->data[pos] += delta;
		pos += pos & -pos;
	}
}

int fenwick_query(FenwickTree *tree, int pos)
{
	int res = 0;
	while (pos > 0) {
		res += tree->data[pos];
		pos -= pos & -pos;
	}
	return res;
}

int countMajoritySubarrays(int *nums, int size, int target)
{
	int *balance = calloc(size, sizeof(int));
	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		if (num == target) {
			balance[i] = 1;
		} else {
			balance[i] = -1;
		}
	}

	int *prefix = malloc((size+1) * sizeof(int));
	prefix[0] = 0;
	for (int i = 0; i < size; ++i) {
		prefix[i+1] = prefix[i] + balance[i];
	}

	FenwickTree *fw = fenwick_create((size+1)*2);

	int off = size+1;
	int count = 0;
	for (int i = 0; i <= size; ++i) {
		int curr = prefix[i];
		count += fenwick_query(fw, curr-1+off);
		fenwick_update(fw, curr+off, 1);
	}

	free(fw);
	free(prefix);
	free(balance);

	return count;
}
