#include "shdstd.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MAX_SIZE 2002

int gcd(int a, int b)
{
	int k = 1;
	while (k) {
		k = a % b;
		a = b;
		b = k;
	}

	return a;
}

char *gcdOfStrings(char *l, char *r)
{
	int i;
	int size_l = strlen(l);
	int size_r = strlen(r);

	char lpr[MAX_SIZE];
	char rpl[MAX_SIZE];

	char *ret = malloc((size_l + size_r + 1) * sizeof(char));

	strcpy(lpr, l);
	strcpy(lpr + size_l, r);
	strcpy(rpl, r);
	strcpy(rpl + size_r, l);

	if (strcmp(lpr, rpl) != 0) {
		ret[0] = '\0';
		return ret;
	}

	int sub_end = gcd(size_l, size_r);

	for (i = 0; i < sub_end; ++i) {
		ret[i] = r[i];
	}
	ret[i] = '\0';

	return ret;
}
