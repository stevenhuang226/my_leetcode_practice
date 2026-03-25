#include "shdstd.h"

char *findDifferentBinaryString(char **nums, int nums_size)
{
	ssize_t len = strlen(nums[0]);

	char *result = malloc((len+1) * sizeof(char));

	for (int i = 0; i < len; ++i) {
		int ch = nums[i][i];
		if (ch == '1') {
			result[i] = '0';
		} else {
			result[i] = '1';
		}
	}

	result[len] = '\0';

	return result;
}
