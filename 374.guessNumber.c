#include "shdstd.h"

int guess(int num);

int guessNumber(int n)
{
	int left = 1;
	int right = n;

	while (left <= right) {
		int mid = left + ((right - left) / 2);

		int gue = guess(mid);

		if (gue == 0) return mid;

		if (gue > 0) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

	return -1;
}
