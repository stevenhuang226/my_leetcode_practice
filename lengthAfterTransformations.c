#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#define MOD 1000000007

int lengthAfterTransformations(char *s, int t)
{
	int length = strlen(s);
	uint64_t cnt[26] = {0};
	for (int i = 0; i < length; ++i) {
		cnt[s[i] - 'a']++;
	}
	
	int ptr = 25;
	for (int i = 0; i < t; ++i) {
		cnt[(ptr + 1) % 26] = cnt[(ptr + 1) % 26] % MOD + cnt[ptr] % MOD;
		ptr--;
		if (ptr == -1) {
			ptr = 25;
		}
	}

	uint64_t ans = 0;
	for (int i = 0; i < 26; ++i) {
		ans = (ans + cnt[i]) % MOD;
	}

	return ans;
}

int main()
{
	char a[] = "jqktcurgdvlibczdsvnsg";
	int t = 7517;
	uint64_t ans = lengthAfterTransformations(a, t);

	printf("%" PRIu64 "\n", ans);
	return 0;
}
