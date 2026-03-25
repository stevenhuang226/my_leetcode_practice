#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

int *sortl;
int *sortr;
int *ret_arr;

int dry_days;
int l, l_size;
int r, r_size;
int ret_ptr;
int last_ret;

int rain_ptr;

int i, ii;

int *tmp;

int8_t boom;

int compare(const void *a, const void *b)
{
	if (*(int *)a == *(int *)b) boom = 1;
	return *(int *)a - *(int *)b;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *avoidFlood(int *rains, int rainsSize, int *returnSize) {
	sortl = malloc(rainsSize * sizeof(int));
	sortr = malloc(rainsSize * sizeof(int));
	ret_arr = malloc(rainsSize * sizeof(int));

	int *ans;
	int ans_ptr = 0;
	ans = malloc(rainsSize * sizeof(int));

	dry_days = rain_ptr = l_size = boom = last_ret = 0;

	for (;rain_ptr < rainsSize;) {
		for (; rain_ptr < rainsSize; rain_ptr++) {
			if (rains[rain_ptr] != 0) break;
			dry_days++;
		}
		for (r_size = 0; rain_ptr < rainsSize; rain_ptr++) {
			if (rains[rain_ptr] == 0) break;
			sortr[r_size++] = rains[rain_ptr];
		}
		qsort(sortl, l_size, sizeof(int), compare);
		qsort(sortr, r_size, sizeof(int), compare);

		for (l = r = 0; l < l_size && r < r_size; ) {
			if (sortl[l] < sortr[r]) {
				sortr[r_size++] = sortl[l];
				l++;
				continue;
			}
			if (sortl[l] > sortr[r]) {
				r++;
				continue;
			}

			ans[ans_ptr++] = sortl[l];
			l++;
			r++;

			if ((--dry_days) < 0) {
				boom = 1;
				break;
			}
		}
		for (; l < l_size; l++) {
			sortr[r_size++] = sortl[l];
		}

		if (boom) break;

		for (ret_ptr = rain_ptr - 1; ret_ptr >= last_ret || ans_ptr > 0; ret_ptr--) {
			if (rains[ret_ptr] != 0) {
				ret_arr[ret_ptr] = -1;
				continue;
			}
			if (ans_ptr <= 0) {
				ret_arr[ret_ptr] = 1;
				continue;
			}
			ret_arr[ret_ptr] = ans[--ans_ptr];
		}
		last_ret = rain_ptr - 1;

		tmp = sortl;
		sortl = sortr;
		sortr = tmp;
		l_size = r_size;
	}

	if (boom) {
		*returnSize = 0;
		return ans;
	}

	*returnSize = rainsSize;
	return ret_arr;
}
int main()
{
	int rains[] = {1,0,2,0,3,0,2,0,0,0,1,2,3};
	int n = sizeof(rains) / sizeof(rains[0]);
	int returnSize;
	int *ans = avoidFlood(rains, n, &returnSize);

	printf("Input: [");
	for (int i = 0; i < n; i++) {
		printf("%d", rains[i]);
		if (i < n - 1) printf(", ");
	}
	printf("]\nOutput: [");
	for (int i = 0; i < returnSize; i++) {
		printf("%d", ans[i]);
		if (i < returnSize - 1) printf(", ");
	}
	printf("]\n");

	free(ans);
	return 0;
}
