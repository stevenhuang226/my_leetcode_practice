#include "shdstd.h"

#define INF32 (INT32_MAX / 4)
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
static inline void xor_swap(int *l, int *r)
{
	*l ^= *r;
	*r ^= *l;
	*l ^= *r;
}

int minFlips(char *s)
{
	ssize_t len = strlen(s);

	int odd_zero = 0;
	int odd_one = 0;

	int even_zero = 0;
	int even_one = 0;

	for (int i = 0; i < len; i += 2) {
		if (s[i] == '1') {
			++odd_one;
		} else {
			++odd_zero;
		}
	}
	for (int i = 1; i < len; i += 2) {
		if (s[i] == '1') {
			++even_one;
		} else {
			++even_zero;
		}
	}

	int min_move = MIN(odd_zero + even_one, odd_one + even_zero);
	
	if (len % 2 == 0) {
		return min_move;
	}

	for (int i = 0; i < len; ++i) {
		int ch = s[i];

		if (ch == '1') {
			--odd_one;
			++even_one;
		} else {
			--odd_zero;
			++even_zero;
		}

		xor_swap(&odd_one, &even_one);
		xor_swap(&odd_zero, &even_zero);

		int flip = MIN(odd_zero + even_one, odd_one + even_zero);

		min_move = MIN(min_move, flip);
	}

	return min_move;
}

int main()
{
	char s[] = "10001100101000000";

	int res = minFlips(s);

	printf("%d\n", res);
}

/*
 * oeoeoeoeoeo
 *
 * 01001001101 o1:3 o0:3 e1:2 e0:3
 * 10010011010 o1:2 o0:4 e1:3 e0:2
 * 00100110101 o1:4 o0:2 e1:1 e0:4
 * 01001101010
 *
 * 01010101010
 * 10101010101
 */
