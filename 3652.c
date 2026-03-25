#include "shdstd.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int64_t maxProfit(
const int *prices, const int size,
const int *strategy, const int strategy_size,
const int k)
{
	int64_t res = 0;
	for (int i = 0; i < size; ++i) {
		res += (int64_t)prices[i] * strategy[i];
	}
	/* here is source's result */

	int64_t edited = 0; /* the value after edite the strategy */
	int i;
	/* ignore 0~ k/2 because all of them will multiply by 0 */
	/* k/2 ~ k - 1. prices[i] * 1 */
	for (i = k / 2; i < k; ++i) {
		edited += (int64_t)prices[i] * 1;
	}
	/* remained part. k ~ size prices[i] * strategy[i] */
	for (i = k; i < size; ++i) {
		edited += (int64_t)prices[i] * strategy[i];
	}
	res = MAX(res, edited);

	/* ---000111------ */
	/* ----000111----- */
	/*    ↑ =>append original value */
	/*       ↑ =>drop this value */
	/*          ↑ =>
	 * 	strategy[base] == 1  => we don't need to add it, it already in remained part
	 * 	strategy[base] == 0  => add it one time
	 * 	strategy[base] == -1 => add it two times
	 *
	 * 	aka  (1 - strategy[base])
	 */
	for (i = 0; i < size - k; ++i) {
		int base = i + k;
		edited += (int64_t)prices[base - k] * strategy[base - k];
		edited -= (int64_t)prices[base - (k/2)] * 1;
		edited += (int64_t)prices[base] * (1 - strategy[base]);

		res = MAX(res, edited);
	}

	return res;
}
