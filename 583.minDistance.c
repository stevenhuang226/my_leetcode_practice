#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static inline int smin(const int a, const int b)
{
	return MIN(a, b);
}

int minDistance(char *word1, char *word2)
{
	int len1 = strlen(word1);
	int len2 = strlen(word2);

	uint32_t **delete = malloc((len1+1) * sizeof(uint32_t *));
	uint32_t *delete_flat = malloc((len1+1) * (len2+1) * sizeof(uint32_t));
	memset(delete_flat, 0xff, (len1+1) * (len2+1) * sizeof(uint32_t));

	for (int i = 0; i <= len1; ++i) {
		delete[i] = delete_flat + i * (len2+1);
		delete[i][0] = i;
	}
	for (int i = 0; i <= len2; ++i) {
		delete[0][i] = i;
	}

	for (int i = 1; i <= len1; ++i) {
		for (int i2 = 1; i2 <= len2; ++i2) {
			if (word1[i-1] != word2[i2-1]) {
				delete[i][i2] = MIN(delete[i-1][i2] + 1, delete[i][i2-1] + 1);
			} else {
				delete[i][i2] = delete[i-1][i2-1];
			}
		}
	}

	int ans = delete[len1][len2];

	free(delete_flat);
	free(delete);

	return ans;
}
