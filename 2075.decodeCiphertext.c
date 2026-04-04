#include "shdstd.h"

char *decodeCiphertext(char *encoded_text, int rows)
{
	uint32_t size = strlen(encoded_text);
	char *result = malloc((size+1) * sizeof(char));
	int wptr = 0;

	int cols = size / rows;

	for (int i = 0; i < cols; ++i) {
		uint32_t rptr = (uint32_t)i;
		while (rptr < size) {
			result[wptr++] = encoded_text[rptr];
			rptr += cols + 1;
		}
	}

	while (wptr > 0) {
		int ch = result[wptr];
		if (result[wptr-1] != ' ' && (! (ch >= 'a' && ch <= 'z'))) {
			result[wptr] = '\0';
			break;
		}
		--wptr;
	}
	result[size] = '\0';


	return result;
}
