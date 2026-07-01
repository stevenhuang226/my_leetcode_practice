#include "shdstd.h"

#define CODE(a, b) ((a) * rows + (b))
#define DECODE_R(a) ((a) / rows)
#define DECODE_C(b) ((b) % rows)

int dr[] = {-1, 0, 1, 0};
int dc[] = { 0, 1, 0,-1};

typedef struct {
	int capacity;
	int parent[];
} UnionFind;

typedef struct {
	int r;
	int c;
	int dis;
} Node;

UnionFind *uf_create(int capacity)
{
	UnionFind *uf = malloc(sizeof(UnionFind) + capacity * sizeof(int));
	for (int i = 0; i < capacity; ++i) {
		uf->parent[i] = i;
	}
	uf->capacity = capacity;
	return uf;
}

int uf_find(UnionFind *uf, int trg)
{
	if (uf->parent[trg] == trg) {
		return trg;
	}
	uf->parent[trg] = uf_find(uf, uf->parent[trg]);
	return uf->parent[trg];
}

void uf_union(UnionFind *uf, int a, int b)
{
	int root_a = uf_find(uf, a);
	int root_b = uf_find(uf, b);

	if (root_a == root_b) {
		return;
	}

	uf->parent[root_a] = root_b;
}

int8_t uf_same_root(UnionFind *uf, int a, int b)
{
	return (uf_find(uf, a) == uf_find(uf, b));
}

int maximumSafenessFactor(int **grid, int grid_size, int *grid_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int *queue = malloc(rows * cols * sizeof(int));
	int q_size = 0;
	int *nxt_queue = malloc(rows * cols * sizeof(int));
	int n_size = 0;

	Node *nodes = malloc(rows * cols * sizeof(Node));
	int ncnt = 0;

	int8_t **visited = malloc(rows * sizeof(int8_t *));
	int8_t *visited_flat = calloc(1, rows * cols * sizeof(int8_t));

	for (int r = 0; r < rows; ++r) {
		visited[r] = visited_flat + r * cols;
		for (int c = 0; c < cols; ++c) {
			if (grid[r][c] != 1) continue;
			queue[q_size++] = CODE(r, c);
			nodes[ncnt].dis = 0;
			nodes[ncnt].r = r;
			nodes[ncnt].c = c;
			++ncnt;

			visited[r][c] = true;
		}
	}

	int dis = 1;
	while (q_size) {
		for (int i = 0; i < q_size; ++i) {
			int curr_code = queue[i];
			int curr_r = DECODE_R(curr_code);
			int curr_c = DECODE_C(curr_code);

			for (int i2 = 0; i2 < 4; ++i2) {
				int new_r = curr_r + dr[i2];
				int new_c = curr_c + dc[i2];
				if (new_r < 0 || new_r >= rows) continue;
				if (new_c < 0 || new_c >= cols) continue;
				if (visited[new_r][new_c]) continue;
				visited[new_r][new_c] = true;

				nodes[ncnt].r = new_r;
				nodes[ncnt].c = new_c;
				nodes[ncnt].dis = dis;
				++ncnt;

				nxt_queue[n_size++] = CODE(new_r, new_c);
			}
		}
		++dis;

		int *tmp = queue;
		queue = nxt_queue;
		nxt_queue = tmp;
		q_size = n_size;
		n_size = 0;
	}

	free(queue);
	free(nxt_queue);

	memset(visited_flat, 0x00, rows * cols * sizeof(int8_t));

	UnionFind *uf = uf_create(ncnt);

	int res = 0;

	int nptr = ncnt-1;
	while (dis-- > 0 && nptr > 0) {
		while (nptr > 0 && nodes[nptr].dis == dis) {
			int curr_r = nodes[nptr].r;
			int curr_c = nodes[nptr].c;
			for (int i = 0; i < 4; ++i) {
				int new_r = curr_r + dr[i];
				int new_c = curr_c + dc[i];
				if (new_r < 0 || new_r >= rows) continue;
				if (new_c < 0 || new_c >= cols) continue;
				if (!visited[new_r][new_c]) continue;

				uf_union(uf, CODE(curr_r, curr_c), CODE(new_r, new_c));
			}

			visited[curr_r][curr_c] = true;
			--nptr;
		}

		if (uf_same_root(uf, CODE(0, 0), CODE(rows-1, cols-1))) {
			res = dis;
			break;
		}
	}

	free(visited);
	free(nodes);
	free(uf);

	return res;
}
