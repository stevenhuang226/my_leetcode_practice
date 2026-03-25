#include "shdstd.h"

#define D_SIZE 4

int d1[] = {-1, -1, -1, 0};
int d2[] = {-1,  0,  1, 1};

#define S_SIZE 3

int s1[] = {-1, -1, -1};
int s2[] = {-1, 0, 1};

int **grid;

int8_t check(int l1, int l2)
{
	int size = D_SIZE;

	for (int k = 0; k < size; ++k) {
		int n1l1 = l1 + d1[k];
		int n1l2 = l2 + d2[k];
		int n2l1 = l1 - d1[k];
		int n2l2 = l2 - d2[k];
		
		int num1 = grid[n1l1][n1l2];
		int num2 = grid[n2l1][n2l2];

		if (num1 == 5 || num1 < 1 || num1 > 9) {
			return false;
		}

		if (num2 == 5 || num2 < 1 || num2 > 9) {
			return false;
		}

		if (num1 + num2 != 10) {
			return false;
		}
	}
	int s_size = S_SIZE;
	int sum = 0;
	for (int i = 0; i < s_size; ++i) {
		int nl1 = l1 + s1[i];
		int nl2 = l2 + s2[i];

		sum += grid[nl1][nl2];
	}
	if (sum != 15) {
		return false;
	}
	sum = 0;
	for (int i = 0; i < s_size; ++i) {
		int nl1 = l1 + s2[i];
		int nl2 = l2 + s1[i];

		sum += grid[nl1][nl2];
	}
	if (sum != 15) {
		return false;
	}
	return true;
}

int numMagicSquaresInside(int **_grid, int size,const int *col_size)
{
	grid = _grid;

	int count = 0;

	for (int i = 1; i < size - 1; ++i) {
		for (int i2 = 1; i2 < col_size[i] - 1; ++i2) {
			if (grid[i][i2] == 5 && check(i, i2)) {
				++count;
			}
		}
	}

	return count;
}
