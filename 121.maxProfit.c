#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int maxProfit(int *prices, int size)
{
	int min_price = INT32_MAX;
	int max_profit = INT32_MIN;

	for (int i = 0; i < size; ++i) {
		min_price = MIN(min_price, prices[i]);
		max_profit = MAX(max_profit, prices[i] - min_price);
	}

	return max_profit;
}
