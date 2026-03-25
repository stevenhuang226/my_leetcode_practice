#include "shdstd.h"

#define SIZE_MRK 2002
#define OFFSET 1001

int **findDifference(int *numsA, int numsA_size, int *numsB, int numsB_size, int *p_ret_size, int **p_ret_col_size)
{
	int8_t *mrk = calloc(1, SIZE_MRK * sizeof(int8_t));
	int offset = OFFSET;

	int **res = malloc(2 * sizeof(int *));
	res[0] = malloc(SIZE_MRK * sizeof(int));
	int res_a_size = 0;
	res[1] = malloc(SIZE_MRK * sizeof(int));
	int res_b_size = 0;

	for (int i = 0; i < numsA_size; ++i) {
		int index = numsA[i] + offset;
		if (mrk[index] >= 1) continue;
		mrk[index] += 1;
	}
	for (int i = 0; i < numsB_size; ++i) {
		int index = numsB[i] + offset;
		if (mrk[index] >= 2) continue;
		mrk[index] += 2;
	}

	for (int i = 0; i < SIZE_MRK; ++i) {
		if (mrk[i] == 0 || mrk[i] == 3) {
			continue;
		}
		if (mrk[i] == 1) { /* only show in a */
			res[0][res_a_size++] = i - offset;
		} else { /* only show in b */
			res[1][res_b_size++] = i - offset;
		}
	}

	(*p_ret_size) = 2;

	(*p_ret_col_size) = malloc(2 * sizeof(int));
	(*p_ret_col_size)[0] = res_a_size;
	(*p_ret_col_size)[1] = res_b_size;

	return res;
}
