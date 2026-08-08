#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
static inline int smax(const int a, const int b)
{
	return MAX(a, b);
}
int *validSequence(char *word1, char *word2, int *ret_size)
{
	int len1 = strlen(word1);
	int len2 = strlen(word2);

	int *suffix_match = malloc((len1+1) * sizeof(int));
	suffix_match[len1] = 0;
	for (int i = len1-1; i >= 0; --i) {
		int next = suffix_match[i+1];
		if (next == len2) {
			suffix_match[i] = len2;
			continue;
		}
		suffix_match[i] = next + (word1[i] == word2[len2-next-1]);
	}

	int *res = malloc(len2 * sizeof(int));

	int prefix_match = 0;
	int8_t changed = false;
	for (int i = 0; i < len1 && prefix_match < len2; ++i) {
		if (word1[i] == word2[prefix_match]) {
			res[prefix_match++] = i;
			continue;
		}

		if (!changed && prefix_match + suffix_match[i+1] + 1 >= len2) {
			res[prefix_match++] = i;
			changed = true;
		}
	}

	free(suffix_match);

	if (prefix_match < len2) {
		free(res);
		*ret_size = 0;
		return NULL;
	}

	*ret_size = len2;
	return res;
}

int main()
{
	char word1[] = "bacdc";
	char word2[] = "abc";
	int sz;

	int *res = validSequence(word1, word2, &sz);
	for (int i = 0; i < sz; ++i) {
		printf("%d ", res[i]);
	}
	printf("\n");

	free(res);

	return 0;
}
