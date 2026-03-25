#include "shdstd.h"

int lengthOfLastWord(char *s)
{
	int back = 0;
	int front = 0;

	int8_t text = false;

	int c;
	int ptr = 0;

	while ((c = s[ptr++]) != '\0') {
		if (c != ' ' && ! text) {
			back = ptr;
			text = true;
		}
		if (c == ' ' && text) {
			front = ptr;
			text = false;
		}
	}
	if (c == '\0' && text) {
		front = ptr;
	}

	return front - back;
}
