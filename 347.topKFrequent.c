#include "shdstd.h"

typedef struct {
	int val;
	int freq;
} Freq;

int cmp(const void *l, const void *r)
{
	return ((Freq *)r)->freq - ((Freq *)l)->freq;
}

int *topKFrequent(int *nums, int nums_size, int k, int *ret_size)
{
	int offset = - (1e4 + 2);

	int exp_max = 2e4 + 8;
	Freq *freq = malloc(exp_max * sizeof(Freq));
	for (int i = 0; i < exp_max; ++i) {
		freq[i].val = i + offset;
		freq[i].freq = 0;
	}

	for (int i = 0; i < nums_size; ++i) {
		int num = nums[i];
		++freq[num - offset].freq;
	}

	qsort(freq, exp_max, sizeof(Freq), cmp);

	int *res = malloc(k * sizeof(int));
	*ret_size = k;

	for (int i = 0; i < k; ++i) {
		res[i] = freq[i].val;
	}

	free(freq);

	return res;
}
