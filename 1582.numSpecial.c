#include "shdstd.h"

int numSpecial(int **mat, int mat_size, int *mat_col_size)
{
	int rows = mat_size;
	int cols = mat_col_size[0];

	int *row_pos_mrk = calloc(rows, sizeof(int));
	int *col_pos_mrk = calloc(cols, sizeof(int));

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (mat[r][c] == 1) {
				++row_pos_mrk[r];
				++col_pos_mrk[c];
			}
		}
	}

	int count = 0;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (row_pos_mrk[r] == 1 &&
					col_pos_mrk[c] == 1 &&
					mat[r][c] == 1) {
				++count;
			}
		}
	}

	free(row_pos_mrk);
	free(col_pos_mrk);

	return count;
}
