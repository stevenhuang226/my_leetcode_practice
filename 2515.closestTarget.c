#include "shdstd.h"

int closestTarget(char **words, int word_size, char *target, int start_index)
{
	int left_off = 0;
	int right_off = 0;

	int target_len = strlen(target);

	while (right_off < word_size) {
		int L = (start_index + left_off + word_size) % word_size;
		int R = (start_index + right_off) % word_size;

		int left_len = strlen(words[L]);
		if (left_len == target_len &&
			strcmp(words[L], target) == 0) {
			return -left_off;
		}

		int right_len = strlen(words[R]);
		if (right_len == target_len &&
			strcmp(words[R], target) == 0) {
			return right_off;
		}

		--left_off;
		++right_off;
	}

	return -1;
}
