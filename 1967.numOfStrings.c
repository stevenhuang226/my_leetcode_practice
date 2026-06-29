#include "shdstd.h"

int numOfStrings(char **patterns, int patterns_size, char *word)
{
	int target_length = strlen(word);

	int count = 0;
	for (int i = 0; i < patterns_size; ++i) {
		int child_length = strlen(patterns[i]);
		if (child_length > target_length) continue;

		for (int i2 = 0; i2 < target_length; ++i2) {
			int8_t brk = false;
			int i3;
			for (i3 = 0; i3 < child_length && i2 + i3 < target_length; ++i3) {
				if (patterns[i][i3] != word[i2 + i3]) {
					brk = true;
					break;
				}
			}

			if (!brk && i3 == child_length) {
				++count;
				break;
			}
		}
	}

	return count;
}
