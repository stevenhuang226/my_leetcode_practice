#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    const int *ia = *(const int **)a;
    const int *ib = *(const int **)b;

    if (ia[1] == ib[1]) {
        return ib[0] - ia[0];
    }
    return ia[1] - ib[1];
}

int intersectionSizeTwo(int **intervals, int intervals_size, int *intervals_col_size)
{
	qsort(intervals, intervals_size, sizeof(int *), compare);

	int tail;
	int prev;
	int i;

	prev = intervals[0][1] - 1;
	tail = intervals[0][1];

	int count = 2;

	for (i = 1; i < intervals_size; ++i) {
		int *range = intervals[i];
		if (range[0] > tail) {
			tail = range[1];
			prev = range[1] - 1;
			count += 2;
		} else if (range[0] > prev) {
			prev = tail;
			tail = range[1];
			++count;
		}
	}

	return count;
}
