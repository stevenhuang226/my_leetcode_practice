#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int maxProfit(int *prices, int size, int fee)
{
	int old_hold = - prices[0] - fee;
	int old_sold = 0;

	int curr_hold;
	int curr_sold;

	for (int i = 1; i < size; ++i) {
		curr_hold = MAX(
				old_hold,
				old_sold - prices[i] - fee
			       );
		curr_sold = MAX(
				old_sold,
				old_hold + prices[i]
			       );

		old_hold = curr_hold;
		old_sold = curr_sold;
	}

	return MAX(curr_hold, curr_sold);
}
