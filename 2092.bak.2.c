#include "shdstd.h"

int comp(const void *a, const void *b) {
	return (*(int **)a)[2] - (*(int **)b)[2];
}

int find_root(int *roots, int target)
{
	if (roots[target] == target) {
		return target;
	}
	roots[target] = find_root(roots, roots[target]);
	return roots[target];
}

void find_link(int *roots, int a, int b)
{
	int root_a = find_root(roots, a);
	int root_b = find_root(roots, b);

	if (root_a == root_b) {
		return;
	}

	/* a will point to root_a, using root_a direct will faster */
	roots[root_a] = root_b;
	return;
}

int *find_create(int size)
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
	int *roots = find_create(n);
	find_link(roots, 0, first_person);

	qsort(meetings, size, sizeof(int *), comp);

	int ptr = 0;
	int window_start = 0;
	while (ptr < size) {
		int curr_time = meetings[ptr][2];
		window_start = ptr;

		while (ptr < size && meetings[ptr][2] == curr_time) {
			int p1 = meetings[ptr][0];
			int p2 = meetings[ptr][1];
			find_link(roots, p1, p2);

			++ptr;
		}
		for (int i = window_start; i < ptr; ++i) {
			int p1 = meetings[i][0];
			int p2 = meetings[i][1];

			if (find_root(roots, p1) != 0) {
				roots[p1] = p1;
			}
			if (find_root(roots, p2) != 0) {
				roots[p2] = p2;
			}
		}
	}

	int *ret = malloc(n * sizeof(int));
	int ret_size = 0;

	for (int i = 0; i < n; ++i) {
		if (find_root(roots, i) == 0) {
			ret[ret_size++] = i;
		}
	}

	*p_ret_size = ret_size;
	free(roots);

	return ret;
}
