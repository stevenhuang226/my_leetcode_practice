#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int cmp32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int **minimumAbsDifference(int *arr, int size, int *ret_size, int **ret_col_size)
{
	qsort(arr, size, sizeof(int), cmp32);
	
	int min_abs_diff = INT32_MAX;

	int **buff = malloc((size - 1) * sizeof(int *));
	int *buff_flat = malloc((size - 1) * 2 * sizeof(int));
	int ret_ptr = 0;

	(*ret_col_size) = malloc((size - 1) * sizeof(int));

	for (int i = 0; i + 1 < size; ++i) {
		buff[i] = buff_flat + i * 2;

		int diff = arr[i+1] - arr[i];
		if (diff < min_abs_diff) {
			min_abs_diff = diff;
			ret_ptr = 0;
		}
		if (diff == min_abs_diff) {
			buff[ret_ptr][0] = arr[i];
			buff[ret_ptr][1] = arr[i+1];
			(*ret_col_size)[ret_ptr] = 2;

			++ret_ptr;
		}
	}

	(*ret_size) = ret_ptr;
	int **ret = malloc((*ret_size) * sizeof(int *));
	int *ret_flat = malloc((*ret_size) * 2 * sizeof(int));

	for (int i = 0; i < ret_ptr; ++i) {
		ret[i] = ret_flat + i * 2;
		ret[i][0] = buff[i][0];
		ret[i][1] = buff[i][1];
	}

	free(buff);
	free(buff_flat);

	return ret;
}
