#include "shdstd.h"

int strStr(char *haystack, char *needle)
{
	int haystack_len = strlen(haystack);
	int needle_len = strlen(needle);

	if (needle_len > haystack_len) {
		return -1;
	}

	for (int i = 0; i <= haystack_len - needle_len; ++i) {
		if (haystack[i] != needle[0] || haystack[i+needle_len-1] != needle[needle_len-1]) {
			continue;
		}

		int8_t brk = false;
		for (int i2 = 0; i2 < needle_len; ++i2) {
			if (haystack[i+i2] != needle[i2]) {
				brk = true;
				break;
			}
		}

		if (brk) {
			continue;
		}

		return i;
	}
	return -1;
}
