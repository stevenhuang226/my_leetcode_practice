#include <stdio.h>
#include <stdlib.h>

int finalValueAfterOperations(char **operations, int operationsSize)
{
	int i;
	int res = 0;
	for (i = 0; i < operationsSize; i++) {
		if (operations[i][1] == '+') {
			res++;
		} else {
			res--;
		}
	}

	return res;
}
