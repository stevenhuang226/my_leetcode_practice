#include "shdstd.h"

int g_row;
int g_col;

int *parent;

int dr[] = {0, 1, 0, -1};
int dc[] = {-1, 0, 1, 0};

int encode21d(int r, int c)
{
	return r * g_col + c;
}

int uf_find(int id)
{
	if (parent[id] == id) {
		return id;
	}

	parent[id] = uf_find(parent[id]);

	return parent[id];
}

void uf_merge(int left, int right)
{
	int root_left = uf_find(left);
	int root_right = uf_find(right);

	if (root_left == root_right) {
		return;
	}

	parent[root_left] = root_right;
	return;
}

int latestDayToCross(int row, int col, int **cells, int cell_size, int *cell_col_size)
{
	g_row = row;
	g_col = col;

	/*
	 * fake node for top lands and fake node for bottom lands
	 *
	 * when land's r == 1 || r == row => link to TOP_FAKE || BOTTOM_FAKE
	 *
	 * maybe keep 1-base index. Because this doesn't effect union find
	 *
	 * using 0-0 as TOP_FAKE using 0-1 as BOTTOM_FAKE
	 */

	int8_t **land = malloc((row + 1) * sizeof(int8_t *));
	int8_t *land_flat = calloc((row+1) * (col+1), sizeof(int8_t));
	for (int i = 0; i <= row; ++i) {
		land[i] = land_flat + i * (col+1);
	}

	parent = malloc((row+1) * (col+1) * sizeof(int));

	for (int i = 1; i <= row; ++i) {
		for (int i2 = 1; i2 <= col; ++i2) {
			int id = encode21d(i, i2);
			parent[id] = id;
		}
	}
	int top_id = encode21d(0, 0);
	int bottom_id = encode21d(0, 1);

	parent[top_id] = top_id;
	parent[bottom_id] = bottom_id;

	int i;
	for (i = cell_size - 1; i >= 0; --i) {
		int r = cells[i][0];
		int c = cells[i][1];

		land[r][c] = true;
		int curr_id = encode21d(r, c);

		if (r == 1) {
			uf_merge(curr_id, top_id);
		}
		if (r == row) {
			uf_merge(curr_id, bottom_id);
		}
		for (int k = 0; k < 4; ++k) {
			int nr = r + dr[k];
			int nc = c + dc[k];

			if (nr <= 0 || nr > row || nc <= 0 || nc > col) {
				continue;
			}

			if (land[nr][nc]) {
				uf_merge(curr_id, encode21d(nr, nc));
			}
		}

		if (uf_find(top_id) == uf_find(bottom_id)) {
			break;
		}
	}

	free(land);
	free(parent);

	return i;
}
