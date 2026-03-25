#include <stdio.h>
#include <string.h>
#include <stdint.h>

int *findEvenNumbers(int *digits, int digitsSize, int *returnSize)
{
	int num_stack[10] = {0,0,0,0,0,0,0,0,0,0};
	uint8_t *recorded;
	recorded = calloc(1000, sizeof(uint8_t));

	for (int i = 0; i < digitsSize; ++i) {
		num_stack[digits[i]]++;
	}

	int single;
	int ten;
	int hundred;

	*returnSize = 0;

	for (int i = 100; i < 1000; i += 2) {
		single = i % 10;
		ten = i % 100 / 10;
		hundred = i %1000 / 100;
		if (single == ten && ten == hundred && num_stack[single] < 3) {
			continue;
		}
		if ((single == ten || single == hundred) && num_stack[single] < 2) {
			continue;
		}
		if ((ten == hundred) && num_stack[ten] < 2) {
			continue;
		}
		if (num_stack[single] < 1) {
			continue;
		}
		if (num_stack[ten] < 1) {
			continue;
		}
		if (num_stack[hundred] < 1) {
			continue;
		}
		recorded[i] = (uint8_t)0x01;
		++ *returnSize;
	}

	int *output = malloc(*returnSize * sizeof(int));
	int ptr = 0;

	for (int i = 0; i < 1000; ++i) {
		if (recorded[i] == 0x01) {
			output[ptr] = i;
			ptr++;
		}
	}

	free(recorded);
	return output;
}
