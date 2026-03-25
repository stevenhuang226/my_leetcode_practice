#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

#define INF 1000000000

int countCoveredBuildings(int n, int **buildings, int size, int *p_col_size)
{
	int i;


	int **x_asix = malloc((n+1) * sizeof(int *));
	int *x_flat = malloc((n+1) * 2 * sizeof(int));
	for (i = 0; i <= n; ++i) {
		x_asix[i] = x_flat + i * 2;
		x_asix[i][0] = INT_MAX;
		x_asix[i][1] = INT_MIN;
	}


	int **y_asix = malloc((n+1) * sizeof(int *));
	int *y_flat = malloc((n+1) * 2 * sizeof(int));
	for (i = 0; i <= n; ++i) {
		y_asix[i] = y_flat + i * 2;
		y_asix[i][0] = INT_MAX;
		y_asix[i][1] = INT_MIN;
	}

	for (int i = 0; i < size; ++i) {
		int x = buildings[i][0];
		int y = buildings[i][1];
		x_asix[x][0] = MIN(x_asix[x][0], y);
		x_asix[x][1] = MAX(x_asix[x][1], y);
		y_asix[y][0] = MIN(y_asix[y][0], x);
		y_asix[y][1] = MAX(y_asix[y][1], x);
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

