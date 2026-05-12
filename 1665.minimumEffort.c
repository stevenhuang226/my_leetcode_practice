#include "shdstd.h"

/*
 * auth: stevenhuang.dog@gmail.com
 * help with chatGPT
 */

int cmp_task(const void *l, const void *r)
{
	int l_diff = (*(int **)l)[1] - (*(int **)l)[0];
	int r_diff = (*(int **)r)[1] - (*(int **)r)[0];

	if (l_diff != r_diff) {
		return r_diff - l_diff;
	}

	return (*(int **)r)[1] - (*(int **)l)[1];
}

int minimumEffort(int **tasks, int size, int *col_size)
{
	qsort(tasks, size, sizeof(int *), cmp_task);

	int energy = 0;
	int answer = 0;

	for (int i = 0; i < size; ++i) {
		if (energy < tasks[i][1]) {
			answer += tasks[i][1] - energy;
			energy = tasks[i][1];
		}

		energy -= tasks[i][0];
	}

	return answer;
}
