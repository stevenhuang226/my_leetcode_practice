#include "shdstd.h"


#define LEN_LIM 4 // maximum lenght of digit for same char's combo

int compress(char *s, int size)
{
	int edit = 0; // pointer to re-write char array
	int ptr = 1; // pointer to read

	char last_c = s[0]; // last char
	char c;// curr char

	int combo_length = 1; // lenght of same char
	while (ptr < size) {
		c = s[ptr++];
		if (c == last_c) {
			++combo_length;
			continue;
		}

		s[edit++] = last_c;
		last_c = c;

		if (combo_length == 1) continue; // skip if lenght of same char is 1

		int bfr[LEN_LIM + 1]; // buffer for write digit into
		int bfr_size = 0;

		/*
		 * write digit into char array
		 */
		while (combo_length) {
			bfr[bfr_size++] = combo_length % 10;
			combo_length /= 10;
		}

		while (--bfr_size >= 0) {
			s[edit++] = bfr[bfr_size] + '0';
		}

		combo_length = 1; // reset lenght of same char
	}

	// last check
	s[edit++] = last_c;
	if (combo_length != 1) {
		int bfr[LEN_LIM + 1];
		int bfr_size = 0;
		while (combo_length) {
			bfr[bfr_size++] = combo_length % 10;
			combo_length /= 10;
		}
		while (--bfr_size >= 0) {
			s[edit++] = bfr[bfr_size] + '0';
		}
	}

	return edit;
}

int main()
{
	char s[] = {'a', 'a', 'b', 'b', 'c', 'c', 'c'};
	int size = sizeof(s) / sizeof(s[0]);
	int res = compress(s, size);
	printf("compressed length: %d\n", res);

	int i;
	for (i = 0; i < res; ++i) {
		printf("%c", s[i]);
	}
	printf("\n");

	return 0;
}
