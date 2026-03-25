#include "shdstd.h"

char *removeStars(char *s)
{
	int size = strlen(s);
	char *ret = malloc((size+1) * sizeof(char));
	int ret_size = 0;

	int i = 0;
	char c;
	while ((c = s[i++]) != '\0') {
		if (c == '*') {
			--ret_size;
			continue;
		}
		ret[ret_size++] = c;
	}
	ret[ret_size] = '\0';

	return ret;
}
