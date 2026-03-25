#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int idealArrays(int n, int maxValue);
int ideal(int *n, int initValue, int *maxValue, int times, int **table);
void tableAdd(int **table, int initValue, int times, int value);
int tableCheck(int **table, int initValue, int times);

int main()
{
	int n = 184;
	int maxValue = 389;
	int ans = idealArrays(n, maxValue);
	printf("%d\n", ans);
	return 0;
}

int idealArrays(int n, int maxValue)
{
	int **table = malloc(10000 * sizeof(int *));
	for (int i = 0; i < 10000; ++i) {
		table[i] = calloc(10000, sizeof(int));
	}

	int ans = ideal(&n, 1, &maxValue, 0, table);

	for (int i = 0; i < 10000; ++i) {
		free(table[i]);
	}
	free(table);
	return ans;
}

int ideal(int *n, int initValue, int *maxValue, int times, int **table)
{
	int check = tableCheck(table, initValue, times);
	if (check != 0) {
		return check;
	}
	if (times == *n) {
		return 1;
	}


	int arrays = 0;
	int mult = 1;
	for (int i = initValue; i <= *maxValue; i = initValue * mult) {
		mult++;
		arrays += ideal(n, i, maxValue, times + 1, table);
	}
	tableAdd(table, initValue, times, arrays);

	return arrays;
}

void tableAdd(int **table, int initValue, int times, int value)
{
	table[times][initValue] = value;
	return;
}

int tableCheck(int **table, int initValue, int times)
{
	return table[times][initValue];
}
