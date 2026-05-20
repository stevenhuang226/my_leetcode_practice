#include "shdstd.h"

#define EXP_MAX 50 + 8

int *findThePrefixCommonArray(int *arra, int sizea, int *arrb, int sizeb, int *ret_size)
{
	int size = sizea;
	int *res = malloc(size * sizeof(int));
	*ret_size = size;

	int freqa[EXP_MAX] = {0};
	int freqb[EXP_MAX] = {0};

	int common = 0;
	for (int i = 0; i < size; ++i) {
		int numa = arra[i];
		int numb = arrb[i];

		++freqa[numa];
		++freqb[numb];

		if (freqa[numa] == freqb[numa]) {
			++common;
		}
		if (freqa[numb] == freqb[numb] && numb != numa) {
			++common;
		}

		res[i] = common;
	}

	return res;
}
