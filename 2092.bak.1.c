#include "shdstd.h"

typedef struct {
	int parent;
	int last_time;
} Node;

int comp(const void *a, const void *b) {
	return (*(int **)a)[2] - (*(int **)b)[2];
}

Node *find_create(int size, int default_time)
{
	Node *roots = malloc(size * sizeof(Node));
	for (int i = 0; i < size; ++i) {
		roots[i].parent = i;
		roots[i].last_time = default_time;
	}

	return roots;
}

int find_root(Node *roots, int target)
{
	int parent_id = roots[target].parent;
	if (parent_id == target) {
		return target;
	}

	if (roots[parent_id].last_time > roots[target].last_time) {
		return target;
	}

	roots[target].parent = find_root(roots, parent_id);
	return roots[target].parent;
}

void set_root(Node *roots, int dest, int src, int curr_time)
{
	roots[dest].last_time = curr_time;
	roots[dest].parent = find_root(roots, src);
	return;
}

int *findAllPeople(int n,
	int **meetings, int size, int *p_col_size,
	int first_person, int *p_ret_size)
{
	Node *roots = find_create(n, -1);

	set_root(roots, first_person, 0, -1);

	qsort(meetings, size, sizeof(int *), comp);
	
	for(int i = 0; i < size; ++i) {
		int p1 = meetings[i][0];
		int p2 = meetings[i][1];
		int curr_time = meetings[i][2];
		set_root(roots, p2, p1, curr_time);
		set_root(roots, p1, p2, curr_time);
	}

	int *ret = malloc(n * sizeof(int));
	int ret_size = 0;

	for (int i = 0; i < size; ++i) {
		int root = find_root(roots, i);
		if (root == 0) {
			ret[ret_size++] = i;
		}
	}

	*p_ret_size = ret_size;
	return ret;
}
