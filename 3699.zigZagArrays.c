#include "shdstd.h"

int64_t mod = 1e9 + 7;

int zigZagArrays(int size, int l, int r)
{
	int range = r - l + 1;

	int **prev = malloc(2 * sizeof(int *));
	int *prev_flat = calloc(2 * range, sizeof(int));
	int **curr = malloc(2 * sizeof(int *));
	int *curr_flat = calloc(2 * range, sizeof(int));
	prev[0] = prev_flat; prev[1] = prev_flat + range;
	curr[0] = curr_flat; curr[1] = curr_flat + range;

	// prev[down/up][num] curr[down/up][num]

	for (int v = 0; v < range; ++v) {
		prev[0][v] = 1;
		prev[1][v] = 1;
	}
	for (int v = 0; v < range - 1; ++v) {
		prev[0][v+1] += prev[0][v];
		prev[1][v+1] += prev[1][v];
	}

	for (int i = 0; i < size - 1; ++i) {
		for (int v = 0; v < range; ++v) {
			if (v) {
				curr[1][v] = (curr[1][v] + prev[0][v-1]) % mod;
			}

			curr[0][v] = (curr[0][v] + prev[1][range-1] - prev[1][v] + mod) % mod;
		}

		int **tmp = prev;
		prev = curr;
		curr = tmp;
		memset(curr[0], 0x00, 2 * range * sizeof(int));

		for (int v = 0; v < range - 1; ++v) {
			prev[0][v+1] = (prev[0][v+1] + prev[0][v]) % mod;
			prev[1][v+1] = (prev[1][v+1] + prev[1][v]) % mod;

		}
	}

	int ans = (prev[0][range-1] + prev[1][range-1]) % mod;

	free(curr_flat);
	free(prev_flat);
	free(curr);
	free(prev);

	return ans;
}
