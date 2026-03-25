#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

int numSub(char *s)
{
	int size = strlen(s);
	int res_count = 0;

	int left, right;
	left = 0;
	while (right < size) {
		while (s[left] == '0' && left < size) {
			++left;
		}
		if (left == size) break;
		right = left;
		while (s[right+1] == '1') {
			++right;
		}
		if (right == size) break;

		uint64_t x = (right - left + 1);
		res_count = (((x + 1) * x) / 2 + res_count) % MOD;
		left = right + 1;
	}

	return res_count;
}

int main()
{
	char *s = "0110111";
	int res = numSub(s);

	printf("%d\n", res);

	return 0;
}
