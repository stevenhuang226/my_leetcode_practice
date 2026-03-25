#include "shdstd.h"

static int count;

int *links_flat;
int **links;
int *links_ptr;

int *val;

int dfs(int index, int source, int target)
{
	int links_size = links_ptr[index];
	int i;

	int sum = val[index] % target;

	for (i = 0; i < links_size; ++i) {
		int child = links[index][i];
		if (child == source) {
			continue;
		}
		int child_mod = dfs(child, index, target);
		sum = (sum + child_mod) % target;
	}

	if (sum == 0) {
		++count;
	}

	return sum;
}

int maxKDivisibleComponents(int n, int **edges, int size, int *col_size, int *values, int val_size, int k)
{
	if (n == 1) {
		return 1;
	}

	int i,i2;
	count = 0;

	val = values;

	int *deg = calloc(n, sizeof(int));
	links = malloc(n * sizeof(int *));
	links_ptr = malloc(n * sizeof(int));

	for (i = 0; i < size; ++i) {
		++deg[edges[i][0]];
		++deg[edges[i][1]];
	}

	for (i = 0; i < n; ++i) {
		links[i] = malloc(deg[i] * sizeof(int));
		links_ptr[i] = 0;
	}
	for (i = 0; i < size; ++i) {
		int a = edges[i][0];
		int b = edges[i][1];
		int *pa = &(links_ptr[a]);
		int *pb = &(links_ptr[b]);
		links[a][(*pa)++] = b;
		links[b][(*pb)++] = a;
	}

	dfs(0, -1, k);

	free(links_flat);
	free(links);
	free(links_ptr);

	return count;
}
