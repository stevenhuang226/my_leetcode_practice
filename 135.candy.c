#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int candy(int *ratings, int size)
{
	int *candies = malloc(size * sizeof(int));
	for (int i = 0; i < size; ++i) {
		candies[i] = 1;
	}

	for (int left = 0; left < size - 1; ++left) {
		if (ratings[left] < ratings[left + 1]) {
			candies[left + 1] = candies[left] + 1;
		}
	}

	int sum = 0;

	for (int right = size - 2; right >= 0; --right) {
		sum += candies[right + 1];
		if (ratings[right] > ratings[right + 1]) {
			candies[right] = MAX(candies[right], candies[right + 1] + 1);
		}
	}
	sum += candies[0];

	free(candies);

	return sum;
}
