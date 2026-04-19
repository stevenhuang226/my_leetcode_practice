#include "shdstd.h"

static inline int code(char x)
{
	return x - 'a';
}

bool canConstruct(char *target, char *source)
{
	int trg_freq[26] = {0};
	int src_freq[26] = {0};

	int trg_len = strlen(target);
	int src_len = strlen(source);

	for (int i = 0; i < trg_len; ++i) {
		++trg_freq[code(target[i])];
	}
	for (int i = 0; i < src_len; ++i) {
		++src_freq[code(source[i])];
	}

	for (int i = 0; i < 26; ++i) {
		if (trg_freq[i] > src_freq[i]) {
			return false;
		}
	}
	return true;
}
