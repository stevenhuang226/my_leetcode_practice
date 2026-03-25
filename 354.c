#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b)
{
	int *ar = *(int **)a;
	int *br = *(int **)b;
	if (ar[0] == br[0]) {
		return br[1] - ar[1];
	}
	return ar[0] - br[0];
}

int lower_bound(int *arr, int size, int target)
{
	int left = 0;
	int right = size;

	while (left < right) {
		int mid = (left + right) / 2;
		if (arr[mid] >= target) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}

	return left;
}

int maxEnvelopes(int **envelopes, int envelope_size, int *envelopes_col_size)
{
	qsort(envelopes, envelope_size, sizeof(int *), compare);
	int i;
	int tail_size = 0;
	int *tail = calloc((envelope_size+1), sizeof(int));
	for (i = 0; i < envelope_size; ++i) {
		int trg = envelopes[i][1];
		if (trg > tail[tail_size]) {
			tail[++tail_size] = trg;
			continue;
		}
		int pos = lower_bound(tail, tail_size, trg);
		tail[pos] = trg;
	}
	free(tail);
	return tail_size;
}
