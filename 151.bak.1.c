#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	return 0;
}

/* this thing is not finished yet */

char *reverseWords(char *s)
{
	int l = strlen(s);
	int r = l;
	char *res = malloc(l+1 * sizeof(char));
	int res_pos = 0;
	for (;l > 0; ) {
		l--;
		if (s[l] == ' ') {
			memcpy(&res[res_pos], &s[l+1], r-l);
		}
	}
}
