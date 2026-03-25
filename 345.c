#include "shdstd.h"

#define MAX_AEIOU_SIZE 300002

char *reverseVowels(char *s)
{
	int l, r;
	l = 0;
	r = strlen(s) - 1;

	while (l < r) {
		while (s[l] != 'A' && s[l] != 'a' &&
			s[l] != 'E' && s[l] != 'e' &&
			s[l] != 'I' && s[l] != 'i' &&
			s[l] != 'O' && s[l] != 'o' &&
			s[l] != 'U' && s[l] != 'u' &&
			l < r) {
			++l;
		}
		while (s[r] != 'A' && s[r] != 'a' &&
			s[r] != 'E' && s[r] != 'e' &&
			s[r] != 'I' && s[r] != 'i' &&
			s[r] != 'O' && s[r] != 'o' &&
			s[r] != 'U' && s[r] != 'u' &&
			l < r) {
			--r;
		}

		if(! (l < r)) {
			break;
		}

		char tmp = s[l];
		s[l] = s[r];
		s[r] = tmp;

		++l;
		--r;
	}

	return s;
}

int main()
{
	char s[] = "IceCreAm";

	char *res = reverseVowels(s);
	printf("%s", res);

	return 0;
}
