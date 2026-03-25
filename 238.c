#include "shdstd.h"

int *productExceptSelf(int *nums, int size, int *p_ret_size)
{
	int *right_product = malloc(size * sizeof(int));
	right_product[size-1] = nums[size-1];
	int *ret = right_product;
	int product_prefix = 1;

	int i;
	for (i = size - 2; i > 0; --i) {
		right_product[i] = right_product[i+1] * nums[i];
	}

	for (i = 0; i < size - 1; ++i) {
		int product = product_prefix * right_product[i+1];
		ret[i] = product;
		product_prefix *= nums[i];
	}
	ret[size-1] = product_prefix;
	(*p_ret_size) = size;
	return ret;
}
