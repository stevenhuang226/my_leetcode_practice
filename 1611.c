#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int minimumOneBitOperations(int n)
{
	int output = 0;
	for (; n > 0; ) {
		output ^= n;
		n = n >> 1;
	}
	return output;
}
