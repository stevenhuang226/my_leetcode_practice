#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include <limits.h>

int numberOfPairs(int **points, int pointsSize, int *pointsColSize);

int main()
{
	int pointsSize = 3;
	int pointsColSize = 2;
	int **points = malloc(pointsSize * sizeof(int *));
	for (int i = 0; i < pointsSize; i++) {
		points[i] = malloc(pointsColSize * sizeof(int));
	}

	points[0][0] = 3; points[0][1] = 1;
	points[1][0] = 1; points[1][1] = 1;
	points[2][0] = 1; points[2][1] = 3;

	int ans = numberOfPairs(points, pointsSize, &pointsColSize);
	printf("ans= %d\n", ans);

	for (int i = 0; i < pointsSize; i++) {
		free(points[i]);
	}
	free(points);

	return 0;
}

int numberOfPairs(int **points, int pointsSize, int *pointsColSize)
{
/*
  	int illegals = 0;
	int x_max = INT_MIN;
	int y_min = INT_MAX;
	for (int i = 0; i < pointsSize; i++) {
		if (points[i][0] > x_max) {
			x_max = points[i][0];
		}
		if (points[i][1] < y_min) {
			y_min = points[i][1];
		}
	}
*/
	int illegals = 0;
	for (int i = 0; i < pointsSize; i++) {
		int x_scan = points[i][0];
		int y_scan = points[i][1];

//		printf("scaning for\npoints[%d], %d %d\n", i, x_scan, y_scan);

		int y_gaps_min_limit = 0;
		int x_limit = INT_MAX;

		for (int j = 0; j < pointsSize; j++) {

			int y_gaps_min = INT_MAX;
			int x_min = INT_MAX;
			int hitted = -1;

			for (int ii = 0; ii < pointsSize; ii++) {
				if (i == ii) {
					continue;
				}
				int gaps = y_scan - points[ii][1];
		//		printf("points[%d], %d %d\n", ii, points[ii][0], points[ii][1]);
		//		printf("gaps %d\n", gaps);
				if (gaps < y_gaps_min_limit || points[ii][0] < x_scan) {
					continue;
				}
				if (gaps == y_gaps_min && points[ii][0] < x_min) {
					hitted = ii;
					x_min = points[ii][0];
				}
				if (gaps < y_gaps_min && points[ii][0] < x_limit) {
					y_gaps_min = gaps;
					x_min = points[ii][0];
					hitted = ii;
				}
			}
			if (hitted == - 1) {
				break;
			}
			illegals++;
			x_limit = points[hitted][0];
			y_gaps_min_limit = y_gaps_min + 1;

		//	printf("hitted points[%d], %d %d\n", hitted, points[hitted][0], points[hitted][1]);
		}
	}

	return illegals;
}
