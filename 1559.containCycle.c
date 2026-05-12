#include "shdstd.h"

typedef struct {
	int R;
	int C;
} Cell;

typedef struct {
	int rows;
	int cols;
	int8_t **visited;
	char **grid;
} Grid;

int dr[] = {-1, 0, 1, 0};
int dc[] = { 0, 1, 0,-1};
int d_size = sizeof(dr) / sizeof(dr[0]);

int8_t dfs(Grid *grid, Cell curr, Cell parent)
{
	grid->visited[curr.R][curr.C] = true;

	Cell new;
	for (int i = 0; i < d_size; ++i) {
		new.R = curr.R + dr[i];
		new.C = curr.C + dc[i];

		if (new.R == parent.R &&
		new.C == parent.C) continue;

		if (new.R < 0 || new.R >= grid->rows) continue;
		if (new.C < 0 || new.C >= grid->cols) continue;

		if (grid->grid[new.R][new.C] != grid->grid[curr.R][curr.C]) continue;
		if (grid->visited[new.R][new.C] ||
			dfs(grid, new, curr)) {
			return true;
		}
	}

	return false;
}

bool containsCycle(char **_grid, int size, int *col_size)
{
	int rows = size;
	int cols = col_size[0];

	Grid grid;
	grid.rows = rows;
	grid.cols = cols;
	grid.grid = _grid;
	grid.visited = malloc(rows * sizeof(int8_t *));
	int8_t *visited_flat = calloc(rows * cols, sizeof(int8_t));
	for (int i = 0; i < rows; ++i) {
		grid.visited[i] = visited_flat + i * cols;
	}

	int8_t find_cycle = false;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (grid.visited[r][c]) continue;
			Cell parent = {-1, -1};
			Cell curr = { r, c };
			if(dfs(&grid, curr, parent)) {
				find_cycle = true;
				break;
			}
		}
	}

	free(visited_flat);
	free(grid.visited);

	if (find_cycle) {
		return true;
	}
	return false;
}
