#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

#define INF 1000000000

int countCoveredBuildings(int n, int **buildings, int size, int *p_col_size)
{
	int i;

	uint64_t *xa = malloc((n+1) * sizeof(int));
	uint64_t *ya = malloc((n+1) * sizeof(int));
	for (i = 0; i <= n; ++i) {
		xa[i] = ((uint64_t)INT_MAX << 32 + INT_MIN);
		ya[i] = ((uint64_t)INT_MAX << 32 + INT_MIN);
	}

	for (int i = 0; i < size; ++i) {
		int x = buildings[i][0];
		int y = buildings[i][1];

		int64_t x_min = MIN(y, xa[x] >> 32);
		int64_t x_max = MAX(y, xa[x] & 0x0000ffff);
		xa[x] = ((uint64_t)x_max << 32 + x_min);

		int64_t y_min = MIN(x, ya[y] >> 32);
		int64_t y_max = MAX(x, ya[y] & 0x0000ffff);
		ya[x] = ((uint64_t)y_max << 32 + y_min);
	}

	int count = 0;
	for (i = 0; i < size; ++i) {
		int x = buildings[i][0];
		int y = buildings[i][1];
		if (x_asix[x][0] == INT_MAX ||
			x_asix[x][1] == INT_MIN ||
			y_asix[y][0] == INT_MAX ||
			y_asix[y][1] == INT_MIN) {
			continue;
		}

		if (x > y_asix[y][0] &&
			x < y_asix[y][1] &&
			y > x_asix[x][0] &&
			y < x_asix[x][1]) {
			++count;
		}
	}

	free(x_flat);
	free(x_asix);
	free(y_flat);
	free(y_asix);

	return count;
}

