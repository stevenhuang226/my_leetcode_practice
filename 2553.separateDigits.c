#include "shdstd.h"

int *separateDigits(int *nums, int size, int *ret_size)
{
	int *res = malloc(size * 6 * sizeof(int));
	int res_size = 0;

	int tmp[6];
	for (int i = 0; i < size; ++i) {
		int num = nums[i];

		int p = 0;
		while (num) {
			tmp[p++] = num % 10;
			num /= 10;
		}
		while (p) {
			res[res_size++] = tmp[--p];
		}
	}

	*ret_size = res_size;

	return res;
}
