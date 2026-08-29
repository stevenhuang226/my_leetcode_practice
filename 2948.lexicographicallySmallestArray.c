#include "shdstd.h"

typedef struct {
	int value;
	int index;
} Node;

int cmpNode(const void *a, const void *b)
{
	return ((Node *)a)->value - ((Node *)b)->value;
}

int cmp_i32(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int *lexicographicallySmallestArray(int *nums, int nums_size, int limit, int *ret_size)
{
	Node *nodes = malloc(nums_size * sizeof(Node));
	for (int i = 0; i < nums_size; ++i) {
		nodes[i].value = nums[i];
		nodes[i].index = i;
	}
	qsort(nodes, nums_size, sizeof(Node), cmpNode);

	int *indices = malloc(nums_size * sizeof(int));
	int cnt = 0;

	int *res = malloc(nums_size * sizeof(int));

	for (int ptr = 0; ptr < nums_size; ) {
		cnt = 0;
		int start_id = ptr;

		indices[cnt++] = nodes[ptr].index;
		int prev = nodes[ptr++].value;

		while (ptr < nums_size && prev + limit >= nodes[ptr].value) {
			prev = nodes[ptr].value;
			indices[cnt++] = nodes[ptr++].index;
		}

		qsort(indices, cnt, sizeof(int), cmp_i32);

		for (int i2 = 0; i2 < cnt; ++i2) {
			int val = nodes[start_id + i2].value;
			int id = indices[i2];

			res[id] = val;
		}
	}

	free(indices);
	free(nodes);

	*ret_size = nums_size;
	return res;
}
