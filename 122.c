#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

int maxProfit(int *prices, int size)
{
	int profit = 0;
	int i;
	for (i = 1; i < size; ++i) {
		int tmp = prices[i] - prices[i-1];
		if (tmp <= 0) {
			continue;
		}

		profit += tmp;
	}

	return profit;
}
