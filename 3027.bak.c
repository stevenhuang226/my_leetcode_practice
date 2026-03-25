int numberOfPairs(int **points, int pointsSize, int *pointsColSize) {
	uint8_t matrix[1001][1001] = {0};

	int x_max = 0;
	int y_max = 1001;

	for (int i = 0; i < pointsSize; i++) {
		if (points[i][0] > x_max) {
			x_max = points[i][0];
		}
		if (points[i][1] < y_min) {
			y_min = points[i][1];
		}
		matrix[points[i][1]][points[i][0]] = 1;
	}

	int illegals = 0;

	for (int i = 0; i < pointsSize; i++) {
		int y_scan = points[i][1];
		int x_scan = points[i][0];
		int x_max_scan = x_max;
		int y_min_scan = y_min;
		for (int i = y_scan; i >= y_min_scan; i--) {
			if (matrix[i][x_scan] == 1 && i != y_scan) {
				illegals++;
				break;
			}
			for (int ii = x_scan+1; ii <= x_max_scan; ii++) {
				if (matrix[i][ii] == 1) {
					illegals++;
					x_max_scan = ii-1;
					break;
				}
			}
		}
	}

	return illegals;
}
