#include "shdstd.h"

int *plusOne(int *digits, int size, int *p_return_size)
{
	int ret_size;
	int *ret;

	for (int i = 0; i < size; ++i) {
		if (digits[i] != 9) {
			goto _nor;
		}
	}

	ret_size = size + 1;
	ret = malloc(ret_size * sizeof(int));
	ret[0] = 1;

	for (int i = 1; i < ret_size; ++i) {
		ret[i] = 0;
	}

	(*p_return_size) = ret_size;
	return ret;
_nor:
	ret_size = size;
	ret = malloc(ret_size * sizeof(int));

	int last = 1;
	for (int i = size - 1; i >= 0; --i) {
		int curr = last + digits[i];
		ret[i] = curr % 10;
		last = curr / 10;
	}

	(*p_return_size) = ret_size;
	return ret;
}
