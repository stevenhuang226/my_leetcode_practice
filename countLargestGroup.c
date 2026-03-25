#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAXG 36

int countLargestGroup(int n)
{
	int groupd[MAXG] = {0};

	int up0 = 1;
	int up1 = 0;
	int up2 = 0;
	int up3 = 0;
	int up4 = 0;

	while (up0 + up1 * 10 + up2 * 100 + up3 * 1000 + up4 * 10000 <= n) {
		groupd[up0 + up1 + up2 + up3 + up4]++;
		if (up0 != 9) {
			up0++;
			continue;
		} else {
			up0 = 0;
		}
_up1p:
		if (up1 == 9) {
			up1 = 0;
			goto _up2p;
		} else {
			up1++;
			continue;
		}
_up2p:
		if (up2 == 9) {
			up2 = 0;
			goto _up3p;
		} else {
			up2++;
			continue;
		}
_up3p:
		if (up3 == 9) {
			up3 = 0;
			goto _up4p;
		} else {
			up3++;
			continue;
		}
_up4p:
		up4++;
	}

	int max = 0;
	int gmax = 0;
	for (int i = 0; i < MAXG; ++i) {
		if (groupd[i] > max) {
			max = groupd[i];
			gmax = 1;
			continue;
		}
		if (groupd[i] == max) {
			gmax++;
		}
	}

	return gmax;
}

int main()
{
	int n = 83;
	int ans = countLargestGroup(n);
	printf("%d\n", ans);

	return 0;
}
