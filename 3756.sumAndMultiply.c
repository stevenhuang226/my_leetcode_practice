#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define EXP_MAX (int)1e5+8
int64_t mod = 1e9 + 7;
static int8_t hasP10 = false;
static int64_t p10[EXP_MAX];
static int64_t inv10[EXP_MAX];

int64_t spow(int64_t base, int64_t e)
{
	int64_t res = 1;
	while (e) {
		if (e & 1) {
			res = (res * base) % mod;
		}

		base = (base * base) % mod;

		e >>= 1;
	}
	return res;
}

void initp10(int size)
{
	if (hasP10)
		return;

	p10[0] = 1;
	for (int i = 0; i < size - 1; ++i) {
		p10[i+1] = (p10[i] * 10) % mod;
	}

	int64_t inv = spow(10, mod-2);

	inv10[0] = 1;
	for (int i = 0; i < size - 1; ++i) {
		inv10[i+1] = (inv10[i] * inv) % mod;
	}

	hasP10 = true;
}

int *sumAndMultiply(char *s, int **queries, int size, int *col_size, int *ret_size)
{
	initp10(EXP_MAX-1);

	int len = strlen(s);

	int *nz_prefix = malloc((len+1) * sizeof(int));
	int *sum_prefix = malloc((len+1) * sizeof(int));
	int *digits_prefix = malloc((len+1) * sizeof(int));

	sum_prefix[0] = 0;
	nz_prefix[0] = 0;
	digits_prefix[0] = 0;
	int rank = 0;
	for (int i = 0; i < len; ++i) {
		int d = s[i] - '0';

		sum_prefix[i+1] = sum_prefix[i] + d;
		if (d == 0) {
			digits_prefix[i+1] = digits_prefix[i];
		} else {
			digits_prefix[i+1] = (digits_prefix[i] + d * inv10[rank]) % mod;
			++rank;
		}
		nz_prefix[i+1] = rank;
	}

	int *res = malloc(size * sizeof(int));
	*ret_size = size;

	for (int i = 0; i < size; ++i) {
		int left = queries[i][0];
		int right = queries[i][1];

		int nzc = nz_prefix[right+1] - 1;
		nzc = MAX(nzc, 0);

		int64_t digits = (((digits_prefix[right+1] - digits_prefix[left]) * p10[nzc]) + mod) % mod;
		int64_t sum = sum_prefix[right+1] - sum_prefix[left];

		res[i] = ((digits * sum) % mod + mod) % mod;
	}

	free(nz_prefix);
	free(sum_prefix);
	free(digits_prefix);

	return res;
}
