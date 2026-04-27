#include "shdstd.h"

typedef struct {
	int r;
	int c;
} Direction;

int8_t **visited;

int **grid;
int rows;
int cols;

Direction d_map[6][2] = {
    {{ 0,-1},{ 0, 1}},
    {{-1, 0},{ 1, 0}},
    {{ 0,-1},{ 1, 0}},
    {{ 0, 1},{ 1, 0}},
    {{ 0,-1},{-1, 0}},
    {{-1, 0},{ 0, 1}}
};

int8_t dfs(int currR, int currC, int in_id) {
	if (visited[currR][currC]) {
		return false;
	}

	if (currR == rows-1 && currC == cols-1) return true;
	visited[currR][currC] = true;

	int curr_id = grid[currR][currC]-1;

	int newR = currR + d_map[curr_id][!in_id].r;
	int newC = currC + d_map[curr_id][!in_id].c;

	if (newR < 0 || newR >= rows || newC < 0 || newC >= cols) {
		return false;
	}
	if (visited[newR][newC]) {
		return false;
	}

	int new_id = grid[newR][newC]-1;

	if (newR + d_map[new_id][0].r == currR &&
		newC + d_map[new_id][0].c == currC) {
		return dfs(newR, newC, 0);
	}
	if (newR + d_map[new_id][1].r == currR &&
		newC + d_map[new_id][1].c == currC) {
		return dfs(newR, newC, 1);
	}
	return false;
}

bool hasValidPath(int **_grid, int size, int *col_size)
{
	grid = _grid;
	rows = size;
	cols = col_size[0];

	visited = malloc(rows * sizeof(int8_t *));
	int8_t *visited_flat = calloc(rows * cols, sizeof(int8_t));
	for (int i = 0; i < rows; ++i) {
		visited[i] = visited_flat + i * cols;
	}

	int currR = 0;
	int currC = 0;

	int8_t res = false;
	res |= dfs(currR, currC, 0);
	visited[0][0] = false;
	res |= dfs(currR, currC, 1);

	return res;
}
