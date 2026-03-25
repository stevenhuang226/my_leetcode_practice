#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* yes, we will need mini-heap here */

typedef struct {
	int h;
	int m;
	int n;
} Cell;

Cell *heap;
int heap_size;

int8_t *visited_flat;
int8_t **visited;

int i, ii, d;

int dm[4] = {1, -1, 0, 0};
int dn[4] = {0, 0, 1, -1};

int push(Cell cell)
{
	int ptr = heap_size++;
	heap[ptr] = cell;
	for (; ptr > 0; ) {
		int parent = (ptr - 1) / 2;
		if (heap[parent].h <= heap[ptr].h) break;
		Cell tmp = heap[parent];
		heap[parent] = heap[ptr];
		heap[ptr] = tmp;

		ptr = parent;
	}

	return 0;
}

Cell pop()
{
	Cell ret = heap[0];

	int ptr = 0;
	heap[ptr] = heap[--heap_size];

	int min = ptr;
	for (;;) {
		int l = ptr * 2 + 1;
		int r = ptr * 2 + 2;
		if (l < heap_size && heap[l].h < heap[min].h) min = l;
		if (r < heap_size && heap[r].h < heap[min].h) min = r;
		if (min == ptr) break;
		Cell tmp = heap[ptr];
		heap[ptr] = heap[min];
		heap[min] = tmp;

		ptr = min;
	}

	return ret;
}

int swimInWater(int **grid, int gridSize, int *gridColSize)
{
	int m = gridSize;
	int n = *gridColSize;

	heap_size = 0;
	heap = malloc(m * n * sizeof(Cell));

	visited_flat = calloc(m * n, sizeof(int8_t));
	visited = malloc(m * n * sizeof(int8_t *));
	for (i = 0; i < m; i++) {
		visited[i] = visited_flat + i*n;
	}

	push((Cell){grid[0][0], 0, 0});
	for (; heap_size > 0; ) {
		Cell ptr = pop();
		for (d = 0; d < 4; d++) {
			int nm = ptr.m + dm[d];
			int nn = ptr.n + dn[d];
			if (nm < 0 || nm >= m || nn < 0 || nn >= n || visited[nm][nn]) continue;

			visited[nm][nn] = 1;
			if (grid[nm][nn] < ptr.h) {
				grid[nm][nn] = ptr.h;
			}
			push((Cell){grid[nm][nn], nm, nn});

			if (nm == m-1 && nn == n-1) {
				break;
			}
		}
	}

	int ans = grid[m-1][n-1];

	free(heap);
	free(visited_flat);
	free(visited);

	return ans;
}
