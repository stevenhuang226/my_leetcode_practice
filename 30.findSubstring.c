#include "shdstd.h"

/*
 * auth: stevenhuang.dog@gmail.com
 */

#define ROLL_BASE 131
int8_t chk_freq(int *l, int *r)
{
	for (int i = 0; i < 26; ++i) {
		if (l[i] != r[i]) {
			return false;
		}
	}
	return true;
}

uint64_t encode(char *s, int width)
{
	uint64_t res = 0;
	for (int i = 0; i < width; ++i) {
		res = res * ROLL_BASE + (s[i] - 'a' + 1);
	}

	return res;
}

int *findSubstring(char *s, char **words, int word_size, int *ret_size)
{
	int word_length = strlen(words[0]);
	int size = strlen(s);
	int win_size = word_size * word_length;

	int offset = -('a');

	uint64_t trg_xor = 0;
	uint64_t trg_sum = 0;
	int trg_freq[26] = {0};
	for (int i = 0; i < word_size; ++i) {
		for (int i2 = 0; i2 < word_length; ++i2) {
			int c = words[i][i2] + offset;
			++trg_freq[c];
		}

		uint64_t coded = encode(words[i], word_length);
		trg_xor ^= coded;
		trg_sum += coded;
	}


	int *ret = malloc(size * sizeof(int));
	int ret_count = 0;

	int curr_freq[26] = {0};
	for (int r = 0; r < size; ++r) {
		int rc = s[r] + offset;
		++curr_freq[rc];

		int l = r - win_size;
		if (l >= 0) {
			int lc = s[l] + offset;
			--curr_freq[lc];
		}

		if (! chk_freq(curr_freq, trg_freq)) continue;

		uint64_t curr_xor = 0;
		uint64_t curr_sum = 0;
		for (int i = l + 1; i <= r; i += word_length) {
			uint64_t coded = encode(&(s[i]), word_length);
			curr_xor ^= coded;
			curr_sum += coded;
		}

		if (curr_xor == trg_xor && curr_sum == trg_sum) {
			ret[ret_count++] = l + 1;
		}
	}

	*ret_size = ret_count;
	return ret;
}
