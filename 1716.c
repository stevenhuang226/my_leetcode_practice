#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int totalMoney(int n)
{
	int i;
	int week_income = 1;

	int ans = 0;
	for (i = 0; i < n; ++i) {
		if (i % 7 == 0) {
			week_income = (i / 7) + 1;
		}
		ans += week_income;
		++week_income;
	}

	return ans;
}
