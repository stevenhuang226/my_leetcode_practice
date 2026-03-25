#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
char *convert(char *src, int num_rows)
{
	int size = strlen(src);
	char *ret = malloc((size+1) * sizeof(char));
	int retptr = 0;

	int cycle = num_rows + MAX(0, num_rows - 2);

	for (int i = 0; i < num_rows; ++i) {
		int ptr = i;
		int prev = i * 2;
		while (ptr < size) {
			ret[retptr++] = src[ptr];
			int offset = cycle - prev;
			if (offset == 0) {
				ptr += cycle;
			} else {
				ptr += offset;
			}
			prev = offset;
		}
	}
	ret[retptr++] = '\0';

	return ret;
}

int main()
{
	char s[] = "PAYPALISHIRING";
	int n = 3;

	char *ans = convert(s, n);
	printf("%s\n", ans);
	free(ans);
	return 0;
}
