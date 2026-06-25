#include "shdstd.h"

typedef struct {
	int size;
	int data[];
} FenwickTree;

FenwickTree *fw_create(int size)
{
	FenwickTree *fw = calloc(1, sizeof(FenwickTree) + size * sizeof(int));
	fw->size = size;
	return fw;
}

void fw_update(FenwickTree *fw, int idx, int delta)
{
	while (idx < fw->size) {
		fw->data[idx] += delta;
		idx += idx & -idx;
	}
}

int fw_query(FenwickTree *fw, int idx)
{
	int res = 0;
	while (idx) {
		res += fw->data[idx];
		idx -= idx & -idx;
	}
	return res;
}

int64_t countMajoritySubarrays(int *nums, int size, int target)
{
	int *prefix = malloc((size+1) * sizeof(int));
	prefix[0] = 0;
	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		int curr;
		if (num == target) {
			curr = 1;
		} else {
			curr = -1;
		}

		prefix[i+1] = prefix[i] + curr;
	}

	FenwickTree *fw = fw_create(size * 2 + 8);

	int64_t count = 0;
	int offset = size+1;
	for (int i = 0; i <= size; ++i) {
		int curr = prefix[i];
		count += fw_query(fw, (curr-1) + offset);
		fw_update(fw, curr + offset, 1);
	}

	free(prefix);
	free(fw);

	return count;
}
