#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

int countBalancedPermutations(char *num)
{
	int8_t nums[80];
	int size = strlen(num);

	int total = 0;

	for (int i = 0; i < size; ++i) {
		nums[i] = num[i] - '0';
		total += num[i] - '0';
	}

	if (total %2 == 1) {
		return 0;
	}
}

int main()
{
	return 0;
}
