#include "shdstd.h"

int offset = 'A' - 'a';

bool isPalindrome(char *s)
{
	int size = strlen(s);

	int left = 0;
	int right = size - 1;

	while (left < right) {
		if (s[left] >= 'A' && s[left] <= 'Z') {
			s[left] = s[left] - offset;
		}
		if (s[right] >= 'A' && s[right] <= 'Z') {
			s[right] = s[right] - offset;
		}

		if (! ((s[left] >= 'a' && s[left] <= 'z') || (s[left] >= '0' && s[left] <= '9'))) {
			++left;
			continue;
		}
		if (! ((s[right] >= 'a' && s[right] <= 'z') || (s[right] >= '0' && s[right] <= '9'))) {
			--right;
			continue;
		}

		if (s[left] != s[right]) {
			return false;
		}

		++left, --right;
	}

	return true;
}
