#include "shdstd.h"

char map[10][5] = {
    [2] = "abc",
    [3] = "def",
    [4] = "ghi",
    [5] = "jkl",
    [6] = "mno",
    [7] = "pqrs",
    [8] = "tuv",
    [9] = "wxyz",
};

int pow_int(int k, const int n)
{
	int sum = k;
	for (int i = 0; i < n; ++i) {
		sum *= k;
	}

	return sum;
}

char **letterCombinations(char *digits, int *return_size)
{

	int size = strlen(digits);

	int node_split[5] = {0};

	int ret_size = 1;

	for (int i = 0; i < size; ++i) {
		int num = digits[i] - '0';
		if (num == 7 || num == 9) {
			ret_size *= 4;
			node_split[i] = ret_size;
		} else {
			ret_size *= 3;
			node_split[i] = ret_size;
		}
	}

	char **ret = malloc(ret_size * sizeof(char *));
	char *ret_flat = malloc(ret_size * (size+1) * sizeof(char));
	for (int i = 0; i < ret_size; ++i) {
		ret[i] = ret_flat + i * (size+1);
	}

	for (int i = 0; i < size; ++i) {
		int num = digits[i] - '0';
		int str_s = strlen(map[num]);
		int part = ret_size / node_split[i];
		int c = 0;


		for (int i2 = 0; i2 < ret_size; ++i2) {
			ret[i2][i] = map[num][c%str_s];
			if ((i2 + 1) % part == 0) {
				++c;
			}
		}
	}

	for (int i = 0; i < ret_size; ++i) {
		ret[i][size] = '\0';
	}

	*return_size = ret_size;
	return ret;
}

/*
 * adg
 * adh
 * adi
 * aeg
 * aeh
 * aei
 * afg
 * afh
 * afi
 * b*6
 * c*6
 */
