#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int findSubstringInWraproundString(char *s)
{
	int len = strlen(s);
	int *dp = calloc(len, sizeof(int));

	int freq[26] = {0};

	dp[0] = 1;
	freq[s[0] - 'a'] = 1;
	for (int i = 0; i < len - 1; ++i) {
		int curr = s[i+1] - 'a';
		int prev = s[i] - 'a';

		if ((curr - prev + 26) % 26 == 1) {
			dp[i+1] = dp[i] + 1;
		} else {
			dp[i+1] = 1;
		}

		freq[curr] = MAX(freq[curr], dp[i+1]);
	}

	int sum = 0;
	for (int i = 0; i < 26; ++i) {
		sum += freq[i];
	}

	free(dp);

	return sum;
}
