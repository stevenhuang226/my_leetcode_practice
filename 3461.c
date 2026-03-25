#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

bool hasSameDigits(char *s)
{
	int i;
	for (i = 0; s[i] != '\0'; ++i) {
		s[i] = s[i] - '0';
	}
	int size = i;

	for (; size > 2; ) {
		for (i = 0; i < size - 1; ++i) {
			s[i] = (s[i] + s[i+1]) % 10;
		}
		size--;
	}


	return s[0] == s[1];
}

int main()
{
	char test[] = "3902";
	bool ans = hasSameDigits(test);

	printf("%d\n", ans);
	return 0;
}
