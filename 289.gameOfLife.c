#include "shdstd.h"

int dr[] = {-1,-1, 0, 1, 1, 1, 0,-1};
int dc[] = { 0, 1, 1, 1, 0,-1,-1,-1};
int d_size = sizeof(dr) / sizeof(dr[0]);

void gameOfLife(int **board, int size, int *col_size)
{
	int rows = size;
	int cols = col_size[0];

	int **neighbors = malloc(rows * sizeof(int *));
	int *neighbors_flat = calloc(rows * cols, sizeof(int));

	for (int i = 0; i < rows; ++i) {
		neighbors[i] = neighbors_flat + i * cols;
	}

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (board[r][c] != 1) continue;

			for (int i = 0; i < d_size; ++i) {
				int wr = r + dr[i];
				int wc = c + dc[i];

				if (wr < 0 || wr >= rows) continue;
				if (wc < 0 || wc >= cols) continue;

				++neighbors[wr][wc];
			}
		}
	}

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int n_nerb = neighbors[r][c];
			switch (n_nerb) {
			case 0:
			case 1:
				board[r][c] = 0;
				break;
			case 2:
				break;
			case 3:
				board[r][c] = 1;
				break;
			default:
				board[r][c] = 0;
			}
		}
	}

	free(neighbors_flat);
	free(neighbors);
}
