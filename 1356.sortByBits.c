#include "shdstd.h"

typedef struct {
	uint8_t bits_count;
	int num;
} numBits;

int cmp(const void *l, const void *r)
{
	int l_bits = (int)((*(numBits *)l).bits_count);
	int r_bits = (int)((*(numBits *)r).bits_count);

	int l_num = (*(numBits *)l).num;
	int r_num = (*(numBits *)r).num;

	if (l_bits == r_bits) {
		return l_num - r_num;
	}

	return l_bits - r_bits;
}

int *sortByBits(int *arr, int arr_size, int *ret_size)
{
	numBits *num_bits = malloc(arr_size * sizeof(numBits));

	for(int i = 0; i < arr_size; ++i) {
		int num = arr[i];
		int bits_count = 0;
		num_bits[i].num = num;
		while (num) {
			bits_count += num & 1;
			num >>= 1;
		}
		num_bits[i].bits_count = bits_count;
	}

	qsort(num_bits, arr_size, sizeof(numBits), cmp);

	int *res = malloc(arr_size * sizeof(int));

	for (int i = 0; i < arr_size; ++i) {
		res[i] = num_bits[i].num;
	}

	free(num_bits);

	(*ret_size) = arr_size;

	return res;
}
