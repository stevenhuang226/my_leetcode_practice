#include "shdstd.h"

#define OBSTACLE '*'
#define EMPTY '.'
#define ITEM '#'

char **rotateTheBox(char **box, int box_size, int *box_col_size,
	int *ret_size, int **ret_col_size)
{
	int src_rows = box_size;
	int src_cols = box_col_size[0];

	int res_rows = src_cols;
	int res_cols = src_rows;

	char **res = malloc(res_rows * sizeof(char *));
	char *res_flat = malloc(res_rows * res_cols * sizeof(char));
	memset(res_flat, '.', res_rows * res_cols * sizeof(char));
	for (int i = 0; i < res_rows; ++i) {
		res[i] = res_flat + i * res_cols;
	}

	for (int sr = 0; sr < src_rows; ++sr) {
		int count = 0;
		for (int sc = 0; sc < src_cols; ++sc) {
			if (box[sr][sc] == EMPTY) continue;
			if (box[sr][sc] == ITEM) {
				++count;
				continue;
			}
			int c = res_cols-sr-1;
			int r = sc;
			res[r--][c] = OBSTACLE;
			for (int i = 0; i < count; ++i) {
				res[r--][c] = ITEM;
			}
			count = 0;
		}
		int c = res_cols-sr-1;
		int r = res_rows-1;
		for (int i = 0; i < count; ++i) {
			res[r--][c] = ITEM;
		}
	}

	*ret_size = res_rows;
	*ret_col_size = malloc(res_rows * sizeof(int));
	for (int i = 0; i < res_rows; ++i) {
		(*ret_col_size)[i] = res_cols;
	}

	return res;
}
