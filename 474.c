#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int findMaxForm(char **strs, int strsSize, int m, int n)
{
	int i,i2,i3;
	int *dp_flat;
	int **dp;
	dp_flat = calloc((m+1) * (n+1), sizeof(int));
	dp = malloc((m+1) * sizeof(int *));
	for (i = 0; i <= m; ++i ) dp[i] = dp_flat + (n+1) * i;

	for (i = 0; i < strsSize; ++i) {
		int zc = 0;
		int oc = 0;
		char *p;
		for (p = strs[i]; *p; ++p) {
			*p == '0' ? ++zc : ++oc;
		}

		for (i2 = m - zc; i2 >= 0; --i2) {
			for (i3 = n - oc; i3 >= 0; --i3) {
				int tmp = dp[i2][i3] + 1;
				if (tmp > dp[i2+zc][i3+oc]) {
					dp[i2+zc][i3+oc] = tmp;
				}
			}
		}
	}

	int res = dp[m][n];
	free(dp);
	free(dp_flat);
	return res;
}

int main()
{
}
