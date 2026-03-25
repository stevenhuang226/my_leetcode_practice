#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_LAKE 2999999999

uint16_t *last_seen;

int *ans;

int *dry_arr;
int dry_ptr;

int nz_start;

int i, ii;

int *avoidFlood(int *rains, int rainsSize, int *returnSize)
{
	last_seen = calloc(MAX_LAKE, sizeof(uint16_t));
	ans = calloc(rainsSize, sizeof(int));
	dry_arr = malloc(rainsSize * sizeof(int));

	nz_start = dry_ptr = 0;

	for (i = 0; i < rainsSize; i++) {
		int now = rains[i];
		if (now == 0) {
			dry_arr[dry_ptr++] = i;
			continue;
		}
		ans[i] = -1;
		if (last_seen[now] == 0) {
			last_seen[now] = i+1;
			continue;
		}

		int l = last_seen[now] - 1;
		int fz = 0;

		for (ii = nz_start; ii < dry_ptr; ii++) {
			if (dry_arr[ii] < 0) {
				continue;
			}
			int nd = dry_arr[ii];

			if (l < nd && nd < i) {
				ans[nd] = now;
				dry_arr[ii] = -1;
				fz = 1;

				if (ii == nz_start) {
					nz_start++;
				}
				break;
			}
		}

		if (! fz) {
			*returnSize = 0;
			return NULL;
		}

		last_seen[now] = i + 1;
	}

	free(last_seen);

	*returnSize = rainsSize;
	for (i = 0; i < rainsSize; i++) {
		if (ans[i] == 0) {
			ans[i] = 1;
		}
	}
	return ans;
}

int main()
{
	int rains[] = {1,0,2,0,2,1};
	int n = sizeof(rains) / sizeof(rains[0]);
	int returnSize;
	printf("Input: [");
	for (int i = 0; i < n; i++) {
		printf("%d", rains[i]);
		if (i < n - 1) printf(", ");
	}
	printf("]\n");
	int *mans = avoidFlood(rains, n, &returnSize);

	printf("Output: [");
	for (int i = 0; i < returnSize; i++) {
		printf("%d", mans[i]);
		if (i < returnSize - 1) printf(", ");
	}
	printf("]\n");

	free(ans);
	return 0;
}
