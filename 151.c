#include "shdstd.h"

char *reverseWords(char *s)
{
	int size = strlen(s);
	char *ret = malloc((size+1) * sizeof(char));
	int ret_size = 0;

	int ptr = size - 1;
	while (ptr >= 0) {
		while (ptr >= 0 && s[ptr] == ' ') {
			--ptr;
		}

		int length = ptr;
		while (ptr >= 0 && s[ptr] != ' ') {
			--ptr;
		}
		if (length == ptr) {
			break;
		}

		length = length - ptr;

		memcpy(ret + ret_size, s + ptr + 1, length);
		ret_size += length;
		ret[ret_size++] = ' ';
	}
	ret[ret_size-1] = '\0';
	return ret;
}

int main()
{
	char *s = " hello world ";
	char *res = reverseWords(s);
	printf("%s\n", res);
	free(res);
	return 0;
}
