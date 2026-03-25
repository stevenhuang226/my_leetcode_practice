#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TREE_SIZE 100005
#define LOWBIT(x) ((x) & (-(x)))

int64_t *tree;

void update(uint64_t index, int64_t val)
{
	while (index < TREE_SIZE) {
		tree[index] += val;
		index += LOWBIT(index);
	}
	return;
}

int64_t query(uint32_t target)
{
	int64_t sum = 0;
	while (target > 0) {
		sum += tree[target];
		target -= LOWBIT(target);
	}

	return sum;
}

int countRangeSum(int *nums, int numsSize, int lower, int upper)
{
	tree = calloc(TREE_SIZE, sizeof(int64_t));
	int64_t *prefix_arr = malloc((numsSize+1) * sizeof(int64_t));
	prefix_arr[0] = 0;
	/* write its prefix into prefix_arr after query(target)
	 * i2 for loop doing:
	 * 	query(curr) - prefix_arr[i2]
	 * if [lower,upper] -> count++
	 */
	int i,i2;
	int count = 0;
	for (i = 0; i < numsSize; ++i) {
		int off = i+1;
		update(off, (int64_t)nums[i]);
		int64_t prefix = query(off);
		/*
		printf("prefix: %d\n", prefix);
		*/
		prefix_arr[off] = prefix;
		for (i2 = 0; i2 < off; ++i2) {
			int64_t sum = prefix - prefix_arr[i2];
			if (sum >= lower && sum <= upper) ++count;
		}
	}

	return (int)count;
}

int main()
{
	int nums[] = {-2147483647,0,-2147483647,2147483647};
	int lower = -564;
	int upper = 3864;
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = countRangeSum(nums, size, lower, upper);

	printf("%d\n", res);

	return 0;
}
