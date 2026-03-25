#include "shdstd.h"

bool isSubsequence(char *s, char *t)
{
	char cs;
	char ct;

	int ps = 0;
	int pt = 0;
	while ((cs = s[ps]) != '\0' && (ct = t[pt++]) != '\0') {
		if (cs == ct) {
			++ps;
		}
	}

	return cs == '\0';
}

int main()
{
	char *s = "axc";
	char *t = "ahbgdc";

	printf("%d\n", isSubsequence(s, t));
	return 0;
}
