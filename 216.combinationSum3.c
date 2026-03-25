#include "shdstd.h"

int pop_count(int num, int *highest_bit)
{
	int count = 0;
	*highest_bit = 0;
	while (num) {
		if (num & 1) {
			++count;
		}
		++(*highest_bit);
		num = num >> 1;
	}
	return count;
}

int bitmask_sum(int mask)
{
	int sum = 0;
	int i = 1;
	while (mask) {
		if (mask & 1) {
			sum += i;
		}
		++i;
		mask = mask >> 1;
	}
	return sum;
}

int **ret;
int ret_ptr;

void record(int mask, int k)
{
	ret[ret_ptr] = malloc(k * sizeof(int));
	int *arr = ret[ret_ptr];
	++ret_ptr;

	int ptr = 0;
	int i = 0;
	while (ptr < k && i < 10) {
		if (mask & (1 << i)) {
			arr[ptr++] = i + 1;
		}
		++i;
	}
}

void dfs(int mask, int k, int n)
{
	int highest_bit = 0;
	int count = pop_count(mask, &highest_bit);
	int sum = bitmask_sum(mask);

	if (count == k && sum == n) {
		record(mask, k);
		return;
	}

	if (count > k || sum > n) {
		return;
	}

	for (int bit = highest_bit; bit < 9; ++bit) {
		dfs(mask | (1 << bit), k, n);
	}
	return;
}

int **combinationSum3(int k, int n, int *ret_size, int **ret_col_size)
{
	int size = 100;
	ret_ptr = 0;

	ret = malloc(size * sizeof(int *));
	(*ret_col_size) = malloc(size * sizeof(int));
	dfs(0, k, n);

	(*ret_size) = ret_ptr;
	for (int i = 0; i < size; ++i) {
		(*ret_col_size)[i] = k;
	}

	return ret;
}
