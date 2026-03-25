#include "shdstd.h"

char *mergeAlternately(char *stra, char *strb)
{
	int sizea = strlen(stra);
	int sizeb = strlen(strb);

	char *ret = malloc((sizea + sizeb + 1) * sizeof(char));
	int ret_size = 0;

	int pa, pb;
	pa = pb = 0;

	while (pa < sizea && pb < sizeb) {
		ret[ret_size++] = stra[pa++];
		ret[ret_size++] = strb[pb++];
	}

	while (pa < sizea) {
		ret[ret_size++] = stra[pa++];
	}

	while (pb < sizeb) {
		ret[ret_size++] = strb[pb++];
	}

	ret[ret_size] = '\0';

	return ret;
}

int main()
{
	char *a = "abc";
	char *b = "pqr";

	char *res = mergeAlternately(a, b);

	printf("%s", res);

	free(res);

	return 0;
}
