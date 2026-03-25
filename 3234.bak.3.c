#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int numberOfSubstrings(char *s)
{
	int size = strlen(s);
	int *prefix;
	prefix = malloc((size+1) * sizeof(int));

	int i;
	for (i = 0; i < size; ++i) {
	}
}
