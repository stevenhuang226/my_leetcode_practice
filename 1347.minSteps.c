#include "shdstd.h"

#define NCH(x) ((x) - 'a')

int minSteps(char *src, char *trg)
{
	int src_len = strlen(src);
	int trg_len = strlen(trg);

	if (src_len != trg_len) {
		return -1;
	}

	int src_freq[26] = {0};
	int trg_freq[26] = {0};

	for (int i = 0; i < src_len; ++i) {

		++src_freq[NCH(src[i])];
		++trg_freq[NCH(trg[i])];
	}

	int diff = 0;
	for (int i = 0; i < 26; ++i) {
		diff += abs(src_freq[i] - trg_freq[i]);
	}

	return diff / 2;
}
