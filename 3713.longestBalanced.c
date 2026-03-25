#include "shdstd.h"

/*
 * auth: stevenhuang.dog@gmail.com
 * with chatgpt help
 */
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int longestBalanced(char *s)
{
	int size = strlen(s);
	int offset = -('a');

	int freq[26];

	int best_length = 0;

	for (int l = 0; l < size; ++l) {
		memset(freq, 0x00, 26 * sizeof(int));
		int curr_dist = 0;
		int max_freq = 0;
		for (int r = l; r < size; ++r) {
			int c = s[r] + offset;
			++freq[c];

			if (freq[c] == 1) {
				++curr_dist;
			}

			max_freq = MAX(max_freq, freq[c]);

			int length = r-l+1;
			if (max_freq * curr_dist == length) {
				best_length = MAX(best_length, length);
			}
		}
	}

	return best_length;
}
