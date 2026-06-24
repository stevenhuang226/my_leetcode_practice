#include "shdstd.h"

int range;
int state_cnt;
int64_t mod = 1e9 + 7;

static int up(int v)
{
	return range + v;
}

static int down(int v)
{
	return v;
}

int tmp[150 * 150];
int bfr[150 * 150];
int base[150 * 150];

void mat_mult(int *res, int *A, int *B, int n)
{
	memset(res, 0x00, n * n * sizeof(int));
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			for (int i = 0; i < n; ++i) {
				res[r * n + c] = 
					(res[r * n + c] +
					 (int64_t)A[r * n + i] * B[c + i * n]) % mod;
			}
		}
	}
}

void mat_fst_pow(int *base, int64_t e)
{
	int size_of_base = state_cnt * state_cnt * sizeof(int);

	memset(tmp, 0x00, state_cnt * state_cnt * sizeof(int));
	for (int i = 0; i < state_cnt; ++i) {
		tmp[i * state_cnt + i] = 1;
	}

	while (e) {
		if (e & 1) {
			mat_mult(bfr, tmp, base, state_cnt);
			memcpy(tmp, bfr, sizeof(tmp));
		}
		mat_mult(bfr, base, base, state_cnt);
		memcpy(base, bfr, size_of_base);
		e >>= 1;
	}
}

int zigZagArrays(int n, int L, int R)
{
	range = R - L + 1;
	state_cnt = range * 2;

	int V[state_cnt];
	int T[state_cnt][state_cnt];
	memset(T, 0x00, sizeof(T));

	for (int i = 0; i < range; ++i) {
		for (int i2 = 0; i2 < i; ++i2) {
			T[up(i)][down(i2)] = 1;
		}
		for (int i2 = i+1 ; i2 < range; ++i2) {
			T[down(i)][up(i2)] = 1;
		}
	}

	for (int i = 0; i < range; ++i) {
		V[up(i)] = i;
		V[down(i)] = range-1-i;
	}

	mat_fst_pow((int *)T, n - 2);

	memset(bfr, 0x00, sizeof(bfr));
	for (int r = 0; r < state_cnt; ++r) {
		for (int i = 0; i < state_cnt; ++i) {
			bfr[r] = (bfr[r] +
					(int64_t)V[r] * tmp[r * state_cnt + i]) % mod;
		}
	}

	int ans = 0;
	for (int i = 0; i < state_cnt; ++i) {
		ans = (ans + bfr[i]) % mod;
	}

	return ans;
}
