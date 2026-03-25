#include "shdstd.h"

bool findRotation(int **mat, int mat_size, int *mat_col_size,
		int **target, int trg_size, int *trg_col_size)
{
	int rows = mat_size;
	int cols = mat_col_size[0];

	int8_t not_equal = false;
	for (int read_r = 0; read_r < rows; ++read_r) {
		for (int read_c = 0; read_c < cols; ++read_c) {
			int check_r = read_r;
			int check_c = read_c;
			if (mat[read_r][read_c] != target[check_r][check_c]) {
				not_equal = true;
				break;
			}
		}
		if (not_equal) break;
	}

	if (not_equal == false) {
		return true;
	}

	not_equal = false;
	for (int read_r = 0; read_r < rows; ++read_r) {
		for (int read_c = 0; read_c < cols; ++read_c) {
			int check_r = cols - read_c - 1;
			int check_c = read_r;
			if (mat[read_r][read_c] != target[check_r][check_c]) {
				not_equal = true;
				break;
			}
		}
		if (not_equal) break;
	}

	if (not_equal == false) {
		return true;
	}

	not_equal = false;
	for (int read_r = 0; read_r < rows; ++read_r) {
		for (int read_c = 0; read_c < cols; ++read_c) {
			int check_r = rows - read_r - 1;
			int check_c = cols - read_c - 1;
			if (mat[read_r][read_c] != target[check_r][check_c]) {
				not_equal = true;
				break;
			}
		}
		if (not_equal) break;
	}
	if (not_equal == false) {
		return true;
	}

	not_equal = false;
	for (int read_r = 0; read_r < rows; ++read_r) {
		for (int read_c = 0; read_c < cols; ++read_c) {
			int check_r = read_c;
			int check_c = rows - read_r - 1;
			if (mat[read_r][read_c] != target[check_r][check_c]) {
				not_equal = true;
				break;
			}
		}
		if (not_equal) break;
	}
	if (not_equal == false) {
		return true;
	}

	return false;
}
