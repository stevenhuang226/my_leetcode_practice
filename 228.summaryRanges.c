#include "shdstd.h"

char** summaryRanges(int* nums, int size, int* ret_size)
{
	char** res = malloc(size * sizeof(char *));
	int res_size = 0;

	for (int i = 0; i < size; ++i) {
		int start = nums[i];
		int end = nums[i];
		while (i < size-1 && nums[i+1] == nums[i]+1) {
			++i;
			++end;
		}

		if (start == end) {
			res[res_size] = malloc(20 * sizeof(char));
			sprintf(res[res_size], "%d", start);
			++res_size;
			continue;
		}
		res[res_size] = malloc(40 * sizeof(char));
		sprintf(res[res_size], "%d->%d", start, end);
		++res_size;
	}

	*ret_size = res_size;
	return res;
}
