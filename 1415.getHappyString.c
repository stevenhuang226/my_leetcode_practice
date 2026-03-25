#include "shdstd.h"

int bit_pow(int base, int e)
{
	int res = 1;

	while (e) {

		if (e & 1) {
			res = res * base;
		}

		base = base * base;

		e >>= 1;
	}

	return res;
}

char *result;
int size;

void build(int target,int index, char parent)
{
	if (index >= size) return;

	char curr = 'a';
	int next_comb = bit_pow(2, size - index);
	if (target > next_comb) {
		target -= next_comb;
		++curr;
	}

	if (parent == 'a') {
		++curr;
	} else if (parent == 'b' && curr == 'b') {
		++curr;
	}

	result[index] = curr;

	build(target, index + 1, curr);
}

char *getHappyString(int n, int k)
{
	int group_combination = bit_pow(2, n - 1);
	int all_combination = 3 * group_combination;

	if (k > all_combination) {
		result = malloc(sizeof(char));
		result[0] = '\0';
		return result;
	}

	result = malloc((n + 1) * sizeof(char));
	size = n;

	if (k <= group_combination) {
		result[0] = 'a';
		build(k, 1, 'a');
	} else if (k <= 2 * group_combination) {
		result[0] = 'b';
		build(k - group_combination, 1, 'b');
	} else {
		result[0] = 'c';
		build(k - 2 * group_combination, 1, 'c');
	}

	result[size] = '\0';
	return result;
}
