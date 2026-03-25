#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stirng.h>
#include <inttypes.h>

int main()
{
	return 0;
}

int canBeTypeWords(char *text, char *brokenLetters)
{
	int len = strlen(text);
	int bl_len = strlen(brokenLetters);
	int passed_words = 0;
	uint8_t passed = 1;
	for (int i = 0; i < len+1; i++) {
		if (passed == 0 && text[i] != ' ') {
			continue;
		}
		if (text[i] == ' ' && passed == 1) {
			passed_words++;
			continue;
		}
		if (text[i] == ' ' && passed == 0) {
			passed = 1;
			continue;
		}
		for (int ii = 0; ii < bl_len; ii++) {
			if (text[i] == brokenLetters[ii]) {
				passed = 0;
				break;
			}
		}
	}
	if (passed == 1) {
		passed_words++;
	}

	return passed_words;
}
