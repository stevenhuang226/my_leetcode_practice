#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

int32_t countOdds(int32_t low, int32_t hight)
{
	return (hight - low) / 2 + ((hight % 2 != 0) | (low % 2 != 0));
}
