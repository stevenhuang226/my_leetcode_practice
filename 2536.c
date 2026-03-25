#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **rangeAddQueries(int n, int **queries, int queriesSize, int *queriesColSize, int *returnSize, int **returnColumnSizes)
{
	int i,i2;
	int32_t *sweep_flat = calloc(n * n, sizeof(int32_t));
	int32_t **sweep = malloc(n * sizeof(int32_t *));
	for (i = 0; i < n; ++i) {
		sweep[i] = sweep_flat + n * i;
	}

	for (i = 0; i < queriesSize; ++i) {
		int rs = queries[i][0];
		int cs = queries[i][1];
		int re = queries[i][2];
		int ce = queries[i][3];

		++sweep[rs][cs];

		if (re+1 < n) {
			--sweep[re+1][cs];
		}
		if (ce+1 < n) {
			--sweep[rs][ce+1];
		}
		if (re+1 < n && ce+1 < n) {
			++sweep[re+1][ce+1];
		}
	}

	for (i = 0; i < n; ++i) {
		for (i2 = 1; i2 < n; ++i2) {
			sweep[i][i2] += sweep[i][i2-1];
		}
	}

	for (i = 0; i < n; ++i) {
		for (i2 = 1; i2 < n; ++i2) {
			sweep[i2][i] += sweep[i2-1][i];
		}
	}


	*returnSize = n;
	*returnColumnSizes = malloc(n * sizeof(int));
	for (i = 0; i < n; ++i) {
		(*returnColumnSizes)[i] = n;
	}
	return sweep;
}
