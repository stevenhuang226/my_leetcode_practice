#include "shdstd.h"

char *shortestBeautifulSubstring(char *s, int k)
{
	int right = 0;
	int best_len = INT32_MAX;
	int best_left = 0;

	int len = strlen(s);

	int count = 0;
	for (int left = 0; left < len; ++left) {
		while (right < len && count < k) {
			count += (s[right++] == '1');
		}

		int curr_len = right - left;
		if (count == k && curr_len <= best_len) {
			int8_t change = true;
			if (curr_len == best_len) {
				change = false;

				for (int i = 0; i < best_len; ++i) {
					int a = best_left + i;
					int b = left + i;

					if (s[a] < s[b])
						break;
					if (s[a] == s[b])
						continue;

					change = true;
					break;
				}
			}

			if (change) {
				best_left = left;
			}

			best_len = curr_len;
		}

		count -= (s[left] == '1');
	}

	if (best_len == INT32_MAX)
		return "";

	s[best_left + best_len] = '\0';

	return &s[best_left];
}
