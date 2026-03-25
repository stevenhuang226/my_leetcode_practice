#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>


int main()
{
	return 0;
}
int minScoreTriangulation(int* values, int valuesSize)
{
	int i, ii;
	int len;
	int k;

	int width = valuesSize;
	uint32_t *dp;
	dp = calloc(width * width, sizeof(uint32_t));

	for (len = 3; len <= valuesSize; len++) {
		for (i = 0, ii = i+len-1; ii < valuesSize; i++, ii++) {
			dp[i*width + ii] = UINT32_MAX;
			for (k = i+1; k < ii; k++) {
				uint32_t tiswk = dp[i*width + k] + dp[k*width + ii] + values[i]*values[k]*values[ii];
				if (tiswk < dp[i*width + ii]) {
					dp[i*width + ii] = tiswk;
				}
			}
		}
	}

	int res = (int)dp[valuesSize - 1];
	free(dp);
	return res;
}
