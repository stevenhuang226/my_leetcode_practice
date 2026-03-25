#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int bestClosingTime(char *customers)
{
	int size = strlen(customers);
	int *y_suffix = malloc((size+1) * sizeof(int));
	y_suffix[size] = 0;

	for (int i = size; i > 0; --i) {
		y_suffix[i-1] = y_suffix[i] + (customers[i-1] == 'Y');
	}

	int min = INT_MAX;
	int min_id = -1;
	int n_prefix = 0;
	for (int i = 0; i < size; ++i) {
		int penalty = y_suffix[i] + n_prefix;
		if (penalty < min) {
			min = penalty;
			min_id = i;
		}

		n_prefix += (customers[i] == 'N');
	}
	if (n_prefix < min) {
		min = n_prefix;
		min_id = size;
	}

	free(y_suffix);
	return min_id;
}
