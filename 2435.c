#include "shdstd.h"

#define MOD 1000000007

int numberOfPaths(int **grid, int size, int *p_col_size, int k)
{
	int col_size = (*p_col_size);

	int ***map = malloc(size * sizeof(int **));
	int **map_flat = malloc(size * col_size * sizeof(int *));
	int *flat_flat = calloc(size * col_size * k, sizeof(int));

	int i,i2,i3;
	for (i = 0; i < size; ++i) {
		map[i] = map_flat + i * col_size;
		for (i2 = 0; i2 < col_size; ++i2) {
			map[i][i2] = flat_flat + (i * col_size + i2) * k;
		}
	} /* 3D memory space */

	int mod = grid[0][0] % k;
	++map[0][0][mod];
	/* init */

	for (i = 0; i < size; ++i) {
		for (i2 = 0; i2 < col_size; ++i2) {
			int *now = map[i][i2];/* now: a array in 3D cache
					       * now[mod] = how many path with
					       * same mod*/
			if (i > 0) {
				int *prev = map[i - 1][i2];
				for (i3 = 0; i3 < k; ++i3) {
					int mod = (i3 + grid[i][i2]) % k;
					/* prev mod + now_number -> new_mod */
					now[mod] = (now[mod] + prev[i3]) % MOD;
				}
			}
			if (i2 > 0) {
				int *prev = map[i][i2 - 1];
				for (i3 = 0; i3 < k; ++i3) {
					int mod = (i3 + grid[i][i2]) % k;
					now[mod] = (now[mod] + prev[i3]) % MOD;
				}
			}
		}
	}

	int res = map[size-1][col_size-1][0];

	free(map);
	free(map_flat);
	free(flat_flat);

	return res;
}
