#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HEAP_SIZE 40005

typedef struct {
	int h;
	int i;
	int j;
} Cell;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int i, ii, d;

int8_t *visited_flat;
int8_t **visited;

Cell *heap;
int heap_size;
int heap_capacity;

int push(Cell c)
{
	int ptr = heap_size;
	heap[heap_size++] = c;

	for (; ptr > 0; ) {
		int parent = (ptr - 1) / 2;
		if (heap[parent].h <= heap[ptr].h) {
			break;
		}
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
	heap[0] = heap[--heap_size];
	int ptr = 0;


	for (;;) {
		int l = ptr * 2 + 1;
		int r = ptr * 2 + 2;
		int small = ptr;
		if (l < heap_size && heap[l].h < heap[small].h) {
			small = l;
		}
		if (r < heap_size && heap[r].h < heap[small].h) {
			small = r;
		}
		if (small == ptr) {
			break;
		}
		Cell tmp = heap[ptr];
		heap[ptr] = heap[small];
		heap[small] = tmp;

		ptr = small;
	}
	return ret;
}

int trapRainWater(int **heightMap, int heightMapSize, int* heightMapColSize)
{
	if (heightMapSize == 0 || *heightMapColSize == 0) {
		return 0;
	}
	int m,n;
	m = heightMapSize;
	n = *heightMapColSize;

	visited_flat = calloc(m * n, sizeof(int8_t));
	visited = malloc(m * sizeof(int8_t *));
	for (i = 0; i < m; i++) {
		visited[i] = visited_flat + i*n;
	}

	heap_size = 0;
	heap = malloc(HEAP_SIZE * sizeof(Cell));

	/* create visited, mini-heap */

	for (i = 0; i < m; i++) {
		push((Cell){heightMap[i][0], i, 0});
		push((Cell){heightMap[i][n-1], i, n-1});
		visited[i][0] = 1;
		visited[i][n-1] = 1;
	}
	for (i = 0; i < n; i++) {
		push((Cell){heightMap[0][i], 0, i});
		push((Cell){heightMap[m-1][i], m-1, i});
		visited[0][i] = 1;
		visited[m-1][i] = 1;
	}

	int water_count = 0;
	for (; heap_size > 0; ) {
		Cell ptr = pop();
		for (int d = 0; d < 4; d++) {
			int ni = ptr.i + dx[d];
			int nj = ptr.j + dy[d];
			if (ni < 0 || nj < 0 || ni >= m || nj >= n || visited[ni][nj]) {
				continue;
			}
			visited[ni][nj] = 1;
			int nh = heightMap[ni][nj];
			if (nh < ptr.h) {
				water_count += ptr.h - nh;
				push((Cell){ptr.h, ni, nj});
			} else {
				push((Cell){nh, ni, nj});
			}
		}
	}

	free(visited_flat);
	free(visited);
	free(heap);

	return water_count;
}

