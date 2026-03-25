#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

#define MOD 1000000007

uint64_t lengthAfterTransformations(char *s, int t, int* nums, int numsSize)
{
	int length = strlen(s);
	uint64_t *cnt = calloc(26, sizeof(uint64_t));
	for (int i = 0; i < length; ++i) {
		cnt[s[i] - 'a'] ++;
	}

	int ptr = 25;
	uint64_t *next = calloc(26, sizeof(uint64_t));
	uint64_t *tmp = next;
	for (int i = 0; i < t; ++i) {
		for (int ii = 0; ii < 26; ++ii) {
			for (int iii = 1; iii <= nums[ii]; ++iii) {
				next[(ii + iii) % 26] = (next[(ii + iii) % 26] + cnt[ii]) % MOD;
			}
		}
		next = cnt;
		memset(next, 0, 26 * sizeof(uint64_t));
		cnt = tmp;
		tmp = next;
	}

	uint64_t ans = 0;
	for (int i = 0; i < 26; ++i) {
		ans = (ans + cnt[i]) % MOD;
	}

	free(cnt);
	free(next);

	return ans;
}

int main()
{
	char s[] = "abcyy";
	int t = 2;
	int nums[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2};
	int numsSize = 26;
	uint64_t ans = lengthAfterTransformations(s, t, nums, numsSize);
	printf("%" PRIu64 "\n", ans);
	return 0;
}
