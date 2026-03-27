#include "shdstd.h"

bool areSimilar(int **mat, int mat_size, int *mat_col_size, int k)
{
	int rows = mat_size;
	int cols = mat_col_size[0];

	int shift = k % cols;

	for (int r = 0; r < rows; ++r) {
		int offset;

		if (r % 2 == 0) {
			offset = cols - shift;
		} else {
			offset = shift;
		}

		for (int c = 0; c < cols; ++c) {
			int src = mat[r][c];
			int trg = mat[r][(c+offset) % cols];

			if (src != trg) {
				return false;
			}
		}
	}

	return true;
}
