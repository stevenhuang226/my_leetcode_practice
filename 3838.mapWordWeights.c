#include "shdstd.h"

#define CHAR_CODE(a) ((a) - 'a')

char *mapWordWeights(char **words, int words_size, int *weights, int weights_size)
{
	char *res = malloc((words_size+1) * sizeof(int));

	for (int i = 0; i < words_size; ++i) {
		int sum = 0;

		int ch;
		int p = 0;
		while ((ch = words[i][p++]) != '\0') {
			int code = CHAR_CODE(ch);

			sum += weights[code];
		}

		res[i] = (25 - (sum % 26)) + 'a';
	}

	res[words_size] = '\0';

	return res;
}
