#include "shdstd.h"

#define MOD 1000000007
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int cmp32(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int maximizeSquareArea(int m, int n, int *h_fences, int h_size, int *v_fences, int v_size)
{
	int *h = malloc((h_size + 2) * sizeof(int));
	memcpy(h, h_fences, h_size * sizeof(int));
	h[h_size++] = 1;
	h[h_size++] = m;

	int *v = malloc((v_size + 2) * sizeof(int));
	memcpy(v, v_fences, v_size * sizeof(int));
	v[v_size++] = 1;
	v[v_size++] = n;

	qsort(h, h_size, sizeof(int), cmp32);
	qsort(v, v_size, sizeof(int), cmp32);

	int *h_delta = malloc((h_size * h_size / 2) * sizeof(int));
	int *v_delta = malloc((v_size * v_size / 2) * sizeof(int));
	int h_delta_size = 0;
	int v_delta_size = 0;

	for (int i = 0; i < h_size; ++i) {
		for (int i2 = i + 1; i2 < h_size; ++i2) {
			h_delta[h_delta_size++] = h[i2] - h[i];
		}
	}

	for (int i = 0; i < v_size; ++i) {
		for (int i2 = i + 1; i2 < v_size; ++i2) {
			v_delta[v_delta_size++] = v[i2] - v[i];
		}
	}

	qsort(h_delta, h_delta_size, sizeof(int), cmp32);
	qsort(v_delta, v_delta_size, sizeof(int), cmp32);

	int64_t max = -1;

	int hptr = h_delta_size - 1;
	int vptr = v_delta_size - 1;
	while (hptr >= 0 && vptr >= 0) {
		if (h_delta[hptr] == v_delta[vptr]) {
			max = h_delta[hptr];
			break;
		}
		if (h_delta[hptr] > v_delta[vptr]) {
			--hptr;
		} else {
			--vptr;
		}
	}

	free(h);
	free(v);

	free(h_delta);
	free(v_delta);

	if (max < 0) {
		return -1;
	}

	int64_t res = (max * max) % MOD;

	return (int)res;
}
