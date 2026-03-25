#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TREE_LIMIT 20
#define MOD 1000000007

#define LOWBIT(x) ((x) & (-(x)))

/* 
 * fenwick_tree -> size = n + 1 with init 0
 * calloc(n+1, sizeof(uint32_t))
 */
uint32_t *tree;
uint32_t tree_size;

void update(uint32_t index)
{
	while (index < TREE_LIMIT) {
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

int createSortedArray(int *instructions, int instructionsSize)
{
	tree = calloc(TREE_LIMIT, sizeof(uint32_t));

	uint32_t inserted = 0;

	int count = 0;

	int i;
	for (i = 0; i < instructionsSize; ++i) {
		uint32_t k = instructions[i];
		uint32_t prefix = query(k-1);
		uint32_t suffix = inserted - query(k);
		/*
		printf("k:%d prefix: %d, suffix: %d\n", k, prefix, suffix);
		*/
		update(k);
		++inserted;
		if (prefix > suffix) {
			count = (suffix + count)%MOD;
		} else {
			count = (prefix + count)%MOD;
		}
	}

	free(tree);

	return count;
}

int main()
{
	int a[] = {1,3,3,3,2,4,2,1,2};
	int size = sizeof(a) / sizeof(a[0]);

	int res = createSortedArray(a, size);
	printf("res: %d\n", res);

	return 0;
}
