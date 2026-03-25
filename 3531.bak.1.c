#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

#define INF 1000000000

int countCoveredBuildings(int n, int **buildings, int size, int *p_col_size)
{
	int i;


	int **x_asix = malloc(2 * sizeof(int *));
	int *x_asix_flat = malloc((n+1) * 2 * sizeof(int));
	x_asix[0] = x_asix_flat;
	x_asix[1] = x_asix_flat + (n+1);
	for (i = 0; i <= n; ++i) {
		x_asix[i][0] = INT_MAX;
		x_asix[i][1] = INT_MIN;
	}


	int **y_asix = malloc(2 * sizeof(int *));
	int *y_asix_flat = malloc((n+1) * 2 * sizeof(int));
	y_asix[0] = y_asix_flat;
	y_asix[1] = y_asix_flat + (n+1);
	for (i = 0; i <= n; ++i) {
		y_asix[i][0] = INT_MAX;
		y_asix[i][1] = INT_MIN;
	}

	for (int i = 0; i < size; ++i) {
		int x = buildings[i][0];
		int y = buildings[i][1];
		x_asix[x][0] = MIN(x_asix[x][0], y);
		x_asix[x][1] = MAX(x_asix[x][0], y);
		y_asix[y][0] = MIN(x_asix[x][0], x);
		y_asix[y][1] = MAX(x_asix[x][0], x);
	}

	int count = 0;
	for (int i = 0; i < size; ++i) {
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

	free(x_asix_flat);
	free(x_asix);
	free(y_asix_flat);
	free(y_asix);

	return count;
}

