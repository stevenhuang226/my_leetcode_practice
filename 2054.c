#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
typedef struct {
	int start;
	int end;
	int value;
	int max_value;
} Event;

int comp(const void *a, const void *b)
{
	Event *ea = (Event *)a;
	Event *eb = (Event *)b;

	if (ea->start == eb->start) {
		return ea->value - eb->value;
	}
	return ea->start - eb->start;
}

int max_val(Event *timeline, int trg, int l, int r)
{
	int mid;

	if (timeline[r-1].start < trg) {
		return 0;
	}

	while (l < r) {
		mid = (l + r) / 2;
		if (timeline[mid].start < trg) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}

	return timeline[l].max_value;
}

int maxTwoEvents(int **events, int size, int *p_col_size)
{
	Event *timeline = malloc(size * sizeof(Event));
	for (int i = 0; i < size; ++i) {
		timeline[i].start = events[i][0];
		timeline[i].end = events[i][1];
		timeline[i].value = events[i][2];
	}

	qsort(timeline, size, sizeof(Event), comp);

	int max_val_suff = 0;
	for (int i = size - 1; i >= 0; --i) {
		int val = timeline[i].value;
		max_val_suff = MAX(max_val_suff, val);
		timeline[i].max_value = max_val_suff;
	}

	int max = INT_MIN;

	for (int i = 0; i < size; ++i) {
		int end = timeline[i].end;
		int value = timeline[i].value;
		value += max_val(timeline, end+1, i+1, size);

		max = MAX(max, value);
	}

	free(timeline);

	return max;
}
