#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int numRabbits(int *answers, int answersSize);

int main()
{
	int a[5] = {0,0,1,1,1};
	int b = 5;
	int answer = numRabbits(a, b);
	printf("%d\n", answer);

	return 0;
}

int numRabbits(int *answers, int answersSize)
{
	int rabbits = 0;
	int16_t table[1000] = {0};
	for (int i = 0; i < answersSize; ++i) {
		if (answers[i] != 0 && table[answers[i]] > 0 ) {
			table[answers[i]] -= 1;
			continue;
		}
		rabbits += answers[i] + 1;
		table[answers[i]] = answers[i];
	}

	return rabbits;
}
