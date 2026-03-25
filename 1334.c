#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define INF 10000000

int findTheCity(int n, int **edges, int size, int *col_size, int distance_threshold)
{
	int *flat = malloc(n * n * sizeof(int));
	int **dist = malloc(n * sizeof(int *));

	int i,i2;

	for (i = 0; i < n; ++i) {
		dist[i] = flat + i * n;
		for (i2 = 0; i2 < n; ++i2) {
			dist[i][i2] = INF;
		}
	}

	for (i = 0; i < size; ++i) {
		int *now = edges[i];
		int a = now[0];
		int b = now[1];
		int dis = now[2];

		dist[a][b] = dist[b][a] = dis;
	}

	int k;
	for (k = 0; k < n; ++k) {
		for (i = 0; i < n; ++i) {
			for (i2 = 0; i2 < n; ++i2) {
				dist[i][i2] = MIN(dist[i][i2], dist[i][k] + dist[k][i2]);
			}
		}
	}

	int min = INT_MAX;
	int min_id = -1;
	for (i = 0; i < n; ++i) {
		int cnt = 0;
		for (i2 = 0; i2 < n; ++i2) {
			if (i == i2) {
				continue;
			}
			int dis = dist[i][i2];
			if (dis <= distance_threshold) {
				++cnt;
			}
		}
		if (cnt > min) continue;
		min = cnt;
		min_id = i;
	}

	free(dist);
	free(flat);

	return min_id;
}
