#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
char *addBinary(char *a, char *b)
{
	int offset = -'0';
	int size_a = strlen(a);
	int size_b = strlen(b);

	int res_size = MAX(size_a, size_b)+1;
	char *res = malloc((res_size+1) * sizeof(char));
	res[0] = '0';
	res[res_size] = '\0';
	int res_ptr = res_size - 1;

	int ptr_a = size_a - 1;
	int ptr_b = size_b - 1;

	int last = 0;

	while (res_ptr >= 0) {
		int sum = last;
		if (ptr_a >= 0) {
			sum += a[ptr_a--] + offset;
		}
		if (ptr_b >= 0) {
			sum += b[ptr_b--] + offset;
		}

		res[res_ptr--] = (sum%2) - offset;
		last = sum >> 1;
	}

	if (res[0] == '0') {
		memmove(res, res+1, res_size);
	}

	return res;
}
