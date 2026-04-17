#include "shdstd.h"

uint32_t char_code(const char ch)
{
	if (ch >= 'A' && ch <= 'Z') {
		return ch - 'A';
	} else {
		return ch - 'a' + 26;
	}
}

char *minWindow(char *src, char *trg)
{
	uint32_t src_size = strlen(src);
	uint32_t trg_size = strlen(trg);

	int best_length = INT32_MAX;
	int best_start = -1;

	int trg_freq[52] = {0};
	for (int i = 0; i < trg_size; ++i) {
		uint32_t cch = char_code(trg[i]);
		++trg_freq[cch];
	}

	int curr_freq[52] = {0};

	int L = 0;
	int R = 0;
	int match_count = 52;

	for (int i = 0; i < 52; ++i) {
		if (trg_freq[i] > 0) {
			--match_count;
		}
	}

	while (L < src_size) {
		while (match_count != 52 && R < src_size) {
			uint32_t cch = char_code(src[R]);
			++curr_freq[cch];

			if (curr_freq[cch] == trg_freq[cch]) {
				++match_count;
			}

			++R;
		}

		int curr_len = R - L;
		if (match_count == 52 && curr_len < best_length) {
			best_length = curr_len;
			best_start = L;
		}

		uint32_t cch = char_code(src[L]);
		if (curr_freq[cch] == trg_freq[cch]) {
			--match_count;
		}
		--curr_freq[cch];
		++L;
	}

	if (best_length == INT32_MAX) {
		best_length = 0;
	}

	char *best = malloc((best_length+1) * sizeof(char));

	if (best_length == 0) {
		best[0] = '\0';
		return best;
	}

	for (int i = 0; i < best_length; ++i) {
		best[i] = src[i + best_start];
	}
	best[best_length] = '\0';

	return best;
}
