#include "shdstd.h"


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int start_r;
int start_c;
int end_r;
int end_c;

static inline uint64_t compute_next(int r, int c, int off)
{
	while (off > 0) {
		if (r == start_r && c != start_c) {
			int sc = c;
			c = MAX(start_c, c - off);
			off -= sc - start_c;
			continue;
		}
		if (c == start_c && r != end_r) {
			int sr = r;
			r = MIN(end_r, r + off);
			off -= end_r - sr;
			continue;
		}
		if (r == end_r && c != end_c) {
			int sc = c;
			c = MIN(end_c, c + off);
			off -= end_c - sc;
			continue;
		}
		if (c == end_c && r != start_r) {
			int sr = r;
			r = MAX(start_r, r - off);
			off -= sr - start_r;
			continue;
		}
	}

	uint64_t res = (uint64_t)r;
	res = (res << 32) + (uint32_t)c;

	return res;
}

int **rotateGrid(int **grid, int size, int *col_size, int offset, int *ret_size, int **ret_col_size)
{
	int rows = size;
	int cols = col_size[0];

	int **res = malloc(rows * sizeof(int *));
	int *res_flat = malloc(rows * cols * sizeof(int));

	for (int i = 0; i < rows; ++i) {
		res[i] = res_flat + i * cols;
	}

	start_r = 0;
	start_c = 0;

	end_r = rows - 1;
	end_c = cols - 1;

	while (start_r < end_r && start_c < end_c) {

		int cyc_len = ((end_r - start_r) + (end_c - start_c)) * 2;
		int off = offset % cyc_len;

		int r = start_r;
		int c = start_c;

		for (int i = 0; i < cyc_len; ++i) {
			uint64_t wrt = compute_next(r, c, off);
			int w_r = wrt >> 32;
			int w_c = wrt;

			res[w_r][w_c] = grid[r][c];

			uint64_t new = compute_next(r, c, 1);
			int new_r = new >> 32;
			int new_c = (uint32_t)new;

			r = new_r;
			c = new_c;
		}

		++start_r;
		++start_c;
		--end_r;
		--end_c;
	}

	*ret_size = rows;
	*ret_col_size = malloc(rows * sizeof(int));
	for (int i = 0; i < rows; ++i) {
		(*ret_col_size)[i] = cols;
	}

	return res;
}
