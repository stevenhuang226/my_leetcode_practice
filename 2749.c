#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

int main()
{
}

int makeTheIntegerZero(int num1, int num2)
{
	if (num1 == 0) {
		return 0;
	}
	for (int i = 0; i < 61; i++) {
		int64_t x = num1 - i*num2;
		if (x < i) {
			continue;
		}
		int c = 0;
		while(x) {
			x &= (x-1);
			c++;
		}
		if (c <= i) {
			return i;
		}
	}

	return -1;
}
