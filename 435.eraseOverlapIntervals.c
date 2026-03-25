#include "shdstd.h"

#define INF8 (INT8_MAX / 4)
#define INF16 (INT16_MAX / 4)
#define INF32 (INT32_MAX / 4)
#define INF64 (INT64_MAX / 4)
#define NEG_INF8 -(INF8)
#define NEG_INF16 -(INF16)
#define NEG_INF32 -(INF32)
#define NEG_INF64 -(INF64)
int comp(const void *a, const void *b)
{
	/*
	int *arr_a = *(int **)a;
	int *arr_b = *(int **)b;
	if (arr_a[1] == arr_b[1]) {
		return arr_a[0] - arr_b[0];
	}
	return arr_a[1] - arr_b[1];
	*/

	return (*(int **)a)[1] - (*(int **)b)[1];
}

int eraseOverlapIntervals(int **intervals, int size, int *col_size)
{
	qsort(intervals, size, sizeof(int *), comp);

	int end_time = NEG_INF32;
	int count = 0;
	for (int i = 0; i < size; ++i) {
		if (intervals[i][0] < end_time) {
			++count;
		} else {
			end_time = intervals[i][1];
		}
	}

	return count;
}
