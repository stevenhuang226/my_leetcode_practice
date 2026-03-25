#include "shdstd.h"

#define EXP_RET 1000
char **readBinaryWatch(int turn_on, int *ret_size)
{
	char **res = malloc(EXP_RET * sizeof(char *));
	int res_count = 0;
	for (int h = 0; h < 12; ++h) {
		for (int m = 0; m < 60; ++m) {
			int th = h;
			int tm = m;

			int bits_count = 0;
			while (th) {
				bits_count += th & 1;
				th >>= 1;
			}
			while (tm) {
				bits_count += tm & 1;
				tm >>= 1;
			}

			if (bits_count == turn_on) {
				res[res_count] = malloc(8 * sizeof(char));
				sprintf(res[res_count], "%d:%02d", h, m);
				++res_count;
			}
		}
	}

	*ret_size = res_count;
	return res;
}
