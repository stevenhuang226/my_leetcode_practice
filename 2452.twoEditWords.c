#include "shdstd.h"

int str_diff(char *l, char *r)
{
	ssize_t l_len = strlen(l);
	ssize_t r_len = strlen(r);

	if (l_len != r_len) {
		return INT16_MAX;
	}

	int diff = 0;
	for (int i = 0; i < l_len; ++i) {
		if (l[i] != r[i]) {
			++diff;
		}
	}
	return diff;
}

char **twoEditWords(char **queries, int queries_size,
	char **dictionary, int dict_size, int *ret_size)
{
	ssize_t str_len = strlen(queries[0]);

	char **result = malloc(queries_size * sizeof(char *));
	char *result_flat = malloc(queries_size * (str_len+1) * sizeof(char));
	int w = 0;

	for (int i = 0; i < queries_size; ++i) {
		result[i] = result_flat + i * (str_len+1);
	}

	for (int i = 0; i < queries_size; ++i) {
		char *word = queries[i];
		for (int i2 = 0; i2 < dict_size; ++i2) {
			int diff = str_diff(word, dictionary[i2]);
			if (diff <= 2) {
				strncpy(result[w++], word, str_len+1);
				break;
			}
		}
	}

	*ret_size = w;

	return result;
}
