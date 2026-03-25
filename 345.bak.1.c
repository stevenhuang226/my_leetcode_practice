#include "shdstd.h"

#define MAX_AEIOU_SIZE 300002

char *reverseVowels(char *s)
{
	int *pos = malloc(MAX_AEIOU_SIZE * sizeof(int));
	int pos_size = 0;

	int i = 0;
	char c;
	while ((c = s[i]) != '\0') {
		switch (c) {
			case 'a':
			case 'A':
			case 'e':
			case 'E':
			case 'i':
			case 'I':
			case 'o':
			case 'O':
			case 'u':
			case 'U':
				pos[pos_size++] = i;
				break;
		}
		++i;
	}

	int ret_cap = i + 1;
	char *ret = malloc(ret_cap * sizeof(char));
	int ret_size = 0;

	memcpy(ret, s, ret_cap);

	i = 0;
	while (i < --pos_size) {
		int front = pos[i++];
		int rear = pos[pos_size];

		char tmp = ret[front];
		ret[front] = ret[rear];
		ret[rear] = tmp;
	}

	return ret;
}

int main()
{
	char *s = "IceCreAm";

	char *res = reverseVowels(s);
	printf("%s", res);
	free(res);

	return 0;
}
