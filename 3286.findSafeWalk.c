#include "shdstd.h"

#define CODE(a, b) ((a) * cols + (b))
#define DCR(a) ((a) / cols)
#define DCC(b) ((b) % cols)

static int dr[] = {0, 1,-1, 0};
static int dc[] = {1, 0, 0,-1};

bool findSafeWalk(int **grid, int size, int *col_size, int health)
{
	int rows = size;
	int cols = col_size[0];

	int **remained = malloc(rows * sizeof(int *));
	int *remained_flat = calloc(1, rows * cols * sizeof(int));

	for (int r = 0; r < rows; ++r) {
		remained[r] = remained_flat + r * cols;
	}

	int *queue = malloc(rows * cols * sizeof(int));
	int q_size = 0;
	int *nxt = malloc(rows * cols * sizeof(int));
	int n_size = 0;

	int8_t res = false;

	queue[q_size++] = CODE(0, 0);
	remained[0][0] = health - (grid[0][0] == 1);

	while (q_size) {
		for (int i = 0; i < q_size; ++i) {
			int curr = queue[i];
			int R = DCR(curr);
			int C = DCC(curr);
			for (int i2 = 0; i2 < 4; ++i2) {
				int nR = R + dr[i2];
				int nC = C + dc[i2];
				if (nR < 0 || nR >= rows) continue;
				if (nC < 0 || nC >= cols) continue;

				int new = remained[R][C] - grid[nR][nC];
				if (new <= remained[nR][nC] || new <= 0) continue;

				remained[nR][nC] = new;
				nxt[n_size++] = CODE(nR, nC);

				if (nR == rows-1 && nC == cols-1) {
					res = true;
					break;
				}
			}
		}

		if (res) {
			break;
		}

		int *tmp = queue;
		queue = nxt;
		nxt = tmp;

		q_size = n_size;
		n_size = 0;
	}

	if (remained[rows-1][cols-1] >= 1) {
		res = true;
	}

	free(queue);
	free(nxt);

	free(remained_flat);
	free(remained);

	return res;
}
