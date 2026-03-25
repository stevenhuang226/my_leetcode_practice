#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int nextBeautifulNumber(int n)
{
	int i;
	int ans = n;
	int8_t brk = 1;

	for (;; ++ans, brk = 0) {
		int temp = ans;
		int nums_count[10] = {0};
		for (; temp > 0; ) {
			++nums_count[temp%10];
			temp/=10;
		}

		for (i = 0; i < 10; ++i) {
			if (nums_count[i] > 0 && nums_count[i] != i) {
				brk = 1;
				break;
			}
		}
		if (! brk) break;
	}

	return ans;
}

int main()
{
	int n = 233320;
	int ans = nextBeautifulNumber(n);

	printf("%d\n", ans);

	return 0;
}
