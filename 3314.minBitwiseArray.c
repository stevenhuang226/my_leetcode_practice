#include "shdstd.h"

/*
 * 0b0101(5)
 * mask = 0b0001
 * 0b0001 ^ 0b0101 = 0b0100(4)
 * 0b0100(4) + 0b0001(1) = 0b0101(5)
 * 0b0101(4) | 0b0100(5) = 0b0101(5)
 *
 *
 * 0b1011(11)
 * mask = 0b0010
 * 0b0010 ^ 0b1011 = 0b1001(9)
 * 0b1001( 9) + 0b0001( 1) = 0b1010(10)
 * 0b1010(10) | 0b1001( 9) = 0b1011(11)
 *
 * just finding mask
 */


int *minBitwiseArray(int *nums, int size, int *ret_size)
{
	*ret_size = size;
	int *ret = malloc((*ret_size) * sizeof(int));

	for (int i = 0; i < size; ++i) {
		int num = nums[i];

		/* thing that no fit in rule (aka % 2 == 0) */
		if (! (num & 0x01)) {
			ret[i] = -1;
			continue;
		}

		int mask = 0x01;
		int tmp = num;
		while (tmp & 0x01) {
			mask <<= 1;
			tmp >>= 1;
		}
		mask >>= 1;

		ret[i] = num ^ mask;
	}

	return ret;
}

int main()
{
	int nums[] = {2,3,5,7,11};
	int size = sizeof(nums) / sizeof(nums[0]);

	int ret_size;

	int *res = minBitwiseArray(nums, size, &ret_size);

	for (int i = 0; i < ret_size; ++i) {
		printf("%d ,", res[i]);
	}

	free(res);

	return 0;
}
