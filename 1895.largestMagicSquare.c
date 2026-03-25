#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int largestMagicSquare(int **grid, int grid_size, int *grid_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int **row_prefix = malloc(rows * sizeof(int *));
	int *row_prefix_flat = malloc(rows * (cols + 1) * sizeof(int));
	for (int i = 0; i < rows; ++i) {
		row_prefix[i] = row_prefix_flat + i * (cols + 1);
	}
	for (int row = 0; row < rows; ++row) {
		row_prefix[row][0] = 0;
		for (int col = 0; col < cols; ++col) {
			row_prefix[row][col+1] = row_prefix[row][col] + grid[row][col];
		}
	}

	int **col_prefix = malloc((rows + 1) * sizeof(int *));
	int *col_prefix_flat = malloc((rows + 1) * cols * sizeof(int));
	for (int i = 0; i < rows + 1; ++i) {
		col_prefix[i] = col_prefix_flat + i * cols;
	}
	for (int col = 0; col < cols; ++col) {
		col_prefix[0][col] = 0;
		for (int row = 0; row < rows; ++row) {
			col_prefix[row+1][col] = col_prefix[row][col] + grid[row][col];
		}
	}

	int **main_dia = malloc((rows + 1) * sizeof(int *));
	int *main_dia_flat = calloc((rows + 1) * (cols + 1), sizeof(int));
	for (int i = 0; i < rows + 1; ++i) {
		main_dia[i] = main_dia_flat + i * (cols + 1);
	}
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			main_dia[row+1][col+1] =
				main_dia[row][col] + grid[row][col];
		}
	}

	int **anti_dia = malloc((rows + 1) * sizeof(int *));
	int *anti_dia_flat = calloc((rows + 1) * (cols + 1), sizeof(int));
	for (int i = 0; i < rows + 1; ++i) {
		anti_dia[i] = anti_dia_flat + i * (cols + 1);
	}
	for (int row = 0; row < rows; ++row) {
		for (int col = cols - 1; col >= 0; --col) {
			anti_dia[row+1][col] =
				anti_dia[row][col+1] + grid[row][col];
		}
	}

	int max = 1;

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			int lim_k = MIN(rows - row, cols - col);
			for (int k = max + 1; k <= lim_k; ++k) {
				int chk =
					row_prefix[row][col+k] - row_prefix[row][col];
				for (int i = 1; i < k; ++i) {
					int rp =
						row_prefix[row+i][col+k] - row_prefix[row+i][col];
					if (rp != chk) {
						goto _brk;
					}
				}
				for (int i = 0; i < k; ++i) {
					int cp =
						col_prefix[row+k][col+i] - col_prefix[row][col+i];
					if (cp != chk) {
						goto _brk;
					}
				}
				int mdp =
					main_dia[row+k][col+k] - main_dia[row][col];
				if (mdp != chk) {
					continue;
				}
				int adp =
					anti_dia[row+k][col] - anti_dia[row][col+k];
				if (adp != chk) {
					continue;
				}

				max = k;
_brk:
				continue;
			}
		}
	}

	free(row_prefix_flat);
	free(row_prefix);
	free(col_prefix_flat);
	free(col_prefix);
	free(main_dia_flat);
	free(main_dia);
	free(anti_dia_flat);
	free(anti_dia);

	return max;
}
