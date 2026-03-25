#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int i,ii;

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *successfulPairs(int *spells, int spellsSize, int *potions, int potionsSize, long long success, int *returnSize)
{
	int *result;
	result = malloc(spellsSize * sizeof(int));

	qsort(potions, potionsSize, sizeof(int), compare);

	int ptr;
	for (ptr = 0; ptr < spellsSize; ptr++) {
		int left, right, mid;
		int64_t product;
		product = (int64_t)spells[ptr] * potions[potionsSize - 1];
		if (product < success) {
			result[ptr] = 0;
			continue;
		}
		product = (int64_t)spells[ptr] * potions[0];
		if (product >= success) {
			result[ptr] = potionsSize;
			continue;
		}
		left = 1;
		right = potionsSize - 1;
		for (; left < right; ) {
			mid = (left + right) / 2;
			product = (int64_t)spells[ptr] * potions[mid];
			if (product < success) {
				left = mid + 1;
				continue;
			}
			right = mid;
		}
		result[ptr] = potionsSize - left;
	}

	*returnSize = spellsSize;
	return result;
}

int main()
{
	int spells[]  = {1, 2, 3, 4, 5, 6, 7};
	int potions[] = {1, 2, 3, 4, 5, 6, 7};
	long long success = 25;

	int spellsSize = sizeof(spells) / sizeof(spells[0]);
	int potionsSize = sizeof(potions) / sizeof(potions[0]);
	int returnSize = 0;

	int *result = successfulPairs(spells, spellsSize, potions, potionsSize, success, &returnSize);

	printf("Output: [");
	for (int i = 0; i < returnSize; i++) {
		printf("%d", result[i]);
		if (i != returnSize - 1)
			printf(",");
	}
	printf("]\n");

	free(result);
	return 0;
}
