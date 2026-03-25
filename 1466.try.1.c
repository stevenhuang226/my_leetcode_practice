#include "shdstd.h"

int comp(const void *l, const void *r)
{
	return (*(int **)l)[0] - (*(int **)r)[0];
}

int minReorder(int n, int **connections, int size, int *col_size)
{
	qsort(connections, size, sizeof(int *), comp);

	int counter = 0;

	int is_zero = 0;
	while (connections[is_zero][0] == 0) {
		++counter;
		int next_trg = connections[is_zero][1];
		int ptr = 1;
		while (connections[ptr][0] < next_trg) {
			if (connections[ptr][0] == next_trg) {
				++counter;
				next_trg = connections[ptr][1];
			}
			++ptr;
		}

		++is_zero;
	}

	for (int i = is_zero - 1; i < size - 1; ++i) {
		if (connections[i][0] == connections[i+1][0]) {
			++counter;
		}
	}

	return counter;
}
