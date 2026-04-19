#include "shdstd.h"

#define MA(c) ((c) - 'a')

bool isAnagram(char *src, char *trg)
{
	ssize_t src_len = strlen(src);
	ssize_t trg_len = strlen(trg);

	if (src_len != trg_len) {
		return false;
	}

	int src_freq[26];
	int trg_freq[26];

	for (int i = 0; i < src_len; ++i) {
		int src_ch = src[i];
		int trg_ch = trg[i];
		++src_freq[MA(src_ch)];
		++trg_freq[MA(trg_ch)];
	}

	for (int i = 0; i < 26; ++i) {
		if (src_freq[i] != trg_freq[i]) {
			return false;
		}
	}

	return true;
}
