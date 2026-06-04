#include "shdstd.h"

int totalWaviness(int start, int end)
{
	int count = 0;

	for (int num = start; num <= end; ++num) {
		int tmp = num;

		int left;
		int d;
		int right;

		right = tmp % 10;
		tmp /= 10;
		d = tmp % 10;
		tmp /= 10;

		while (tmp) {
			left = tmp % 10;
			tmp /= 10;

			if (d > left && d > right) {
				++count;
			} else if (d < left && d < right) {
				++count;
			}

			right = d;
			d = left;
		}
	}

	return count;
}
