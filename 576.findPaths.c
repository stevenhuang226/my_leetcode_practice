#include "shdstd.h"

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};
int findPaths(int rows, int cols, int max_move, int start_row, int start_col)
{
	int mod = 1e9 + 7;

	int **curr = malloc(rows * sizeof(int *));
	int *curr_flat = calloc(1, rows * cols * sizeof(int));

	int **next = malloc(rows * sizeof(int *));
	int *next_flat = calloc(1, rows * cols * sizeof(int));

	for (int i = 0; i < rows; ++i) {
		curr[i] = curr_flat + i * cols;
		next[i] = next_flat + i * cols;
	}

	curr[start_row][start_col] = 1;

	int out_ways = 0;

	for (int m = 0; m < max_move; ++m) {
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				if (curr[r][c] <= 0)
					continue;

				for (int d = 0; d < 4; ++d) {
					int nr = r + dr[d];
					int nc = c + dc[d];

					if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
						out_ways = (out_ways + curr[r][c]) % mod;
						continue;
					}

					next[nr][nc] = (next[nr][nc] + curr[r][c]) % mod;
				}
			}
		}

		int **tmp = curr;
		curr = next;
		next = tmp;

		memset(next[0], 0x00, rows * cols * sizeof(int));
	}

	free(curr_flat);
	free(next_flat);
	free(curr);
	free(next);

	return out_ways;
}
