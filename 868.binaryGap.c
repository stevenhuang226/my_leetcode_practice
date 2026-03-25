#include "shdstd.h"


#define INF32 (INT32_MAX / 4)
#define NEG_INF32 -(INF32)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int binaryGap(int n)
{
	int max_gap = 0;
	int curr = NEG_INF32;
	while (n) {
		if (n & 1) {
			max_gap = MAX(max_gap, curr);
			curr = 1;
		} else {
			++curr;
		}

		n >>= 1;
	}
	
	return max_gap;
}

int main()
{
	int n = 5;
	int res = binaryGap(n);

	printf("%" SCNd32, res);

	return 0;
}
