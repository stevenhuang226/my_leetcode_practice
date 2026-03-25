#include "shdstd.h"

int *g_roots;

int comp(const void *a, const void *b) {
	return (*(int **)a)[2] - (*(int **)b)[2];
}

int find(int target)
{
	if (g_roots[target] == target) {
		return target;
	}

	g_roots[target] = find(g_roots[target]);
	return g_roots[target];
}

void group(int dest, int src)
{
	int dest_root = find(dest);
	int src_root = find(src);
	if (dest_root == src_root) {
		return;
	}

	g_roots[src_root] = dest_root;
	return;
}

int *roots_create(int size)
{
	int *roots = malloc(size * sizeof(int));
	for (int i = 0; i < size; ++i) {
		roots[i] = i;
	}
	return roots;
}

int *findAllPeople(int n,
	int **meetings, int size, int *p_col_size,
	int first_person, int *p_ret_size)
{
	int *roots = roots_create(n);
	g_roots = roots;

	qsort(meetings, size, sizeof(int *), comp);

	group(0, first_person);

	int ptr = 0;
	int window_start;
	while (ptr < size) {
		int curr_time = meetings[ptr][2];
		window_start = ptr;

		while (ptr < size && meetings[ptr][2] == curr_time) {
			int p1 = meetings[ptr][0];
			int p2 = meetings[ptr][1];
			group(p1, p2);

			++ptr;
		}
		int find_zero = find(0);
		for (int i = window_start; i < ptr; ++i) {
			int p1 = meetings[i][0];
			int p2 = meetings[i][1];

			if (find(p1) != find_zero) {
				g_roots[p1] = p1;
			}
			if (find(p2) != find_zero) {
				g_roots[p2] = p2;
			}
		}
	}

	int *ret = malloc(n * sizeof(int));
	int ret_size = 0;

	int find_zero = find(0);
	for (int i = 0; i < n; ++i) {
		if (find(i) == find_zero) {
			ret[ret_size++] = i;
		}
	}

	*p_ret_size = ret_size;
	free(roots);

	return ret;
}
