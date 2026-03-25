#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int intcmp(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int maximizeSquareHoleArea(int n, int m, int *h_bars, int h_size, int *v_bars, int v_size)
{
	qsort(h_bars, h_size, sizeof(int), intcmp);
	qsort(v_bars, v_size, sizeof(int), intcmp);

	int max_h_consecutive = 1;
	int max_v_consecutive = 1;

	int combo = 1;
	for (int i = 0; i < h_size - 1; ++i) {
		if (h_bars[i] + 1 == h_bars[i+1]) {
			++combo;
		} else {
			combo = 1;
		}
		max_h_consecutive = MAX(max_h_consecutive, combo);
	}

	combo = 1;
	for (int i = 0; i < v_size - 1; ++i) {
		if (v_bars[i] + 1 == v_bars[i+1]) {
			++combo;
		} else {
			combo = 1;
		}
		max_v_consecutive = MAX(max_v_consecutive, combo);
	}

	int res = MIN(max_h_consecutive, max_v_consecutive) + 1;

	return res * res;
}


int main()
{
	int n = 3, m = 2;

	int h_bar[] = {3,2,4};
	int h_size = sizeof(h_bar) / sizeof(h_bar[0]);

	int v_bar[] = {3,2};
	int v_size = sizeof(v_bar) / sizeof(v_bar[0]);

	int res = maximizeSquareHoleArea(n, m, h_bar, h_size, v_bar, v_size);

	printf("res: %d\n", res);

	return 0;
}
