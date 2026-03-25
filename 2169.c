#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

int countOperations(int num1, int num2)
{
	int count = 0;
	for (; num1 && num2; ) {
		if (num1 >= num2) num1 -= num2;
		else num2 -= num1;
		++count;
	}

	return count;
}

int main()
{
	int num1 = 10;
	int num2 = 10;

	int ans = countOperations(num1, num2);

	printf("%" PRId32 "\n", ans);

	return 0;
}
