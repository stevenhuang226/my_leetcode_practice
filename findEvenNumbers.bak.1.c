#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int *findEvenNumbers(int *digits, int digitsSize, int *returnSize)
{
	uint8_t *recorded;
	recorded = malloc(1000 * sizeof(uint8_t));
	memset(recorded, 0x00, 1000);

	int num;
	*returnSize = 0;
	for (int i = 0; i < digitsSize; ++i) {
		for (int ii = 0; ii < digitsSize; ++ii) {
			for (int iii = 0; iii < digitsSize; ++iii) {
				if (i == ii || ii == iii || i == iii) {
					continue;
				}
				num = digits[i] * 100 + digits[ii] * 10 + digits[iii];
				if (num < 100 || digits[iii] % 2 != 0) {
					continue;
				}
				if (recorded[num] == 0x00) {
					++ *returnSize;
					recorded[num] = 0x01;
				}
			}
		}
	}

	int *output;
	int ptr = 0;
	output = malloc(*returnSize * sizeof(int));
	for (int i = 100; i < 1000; ++i)  {
		if (recorded[i] != 0x00) {
			output[ptr] = i;
			++ptr;
		}
	}
	free(recorded);

	return output;
}

int main() {
	int test[4] = {2,1,3,0};
	int retSize;
	int *ans = findEvenNumbers(test, 4, &retSize);

	printf("%d\n", retSize);

	for (int i = 0; i < retSize; ++i) {
		printf("%d\n", ans[i]);
	}

	free(ans);

	return 0;
}
