#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char *fractionToDecimal(int numerator, int denominator);
int main()
{
	int32_t a = 1;
	int32_t b = 2;
	char *res = fractionToDecimal(a, b);
	printf(res);

	free(res);
	return 0;
}

char *fractionToDecimal(int numerator, int denominator)
{
	if (numerator == 0) {
		char *res = malloc(2 * sizeof(char));
		res[0] = '0';
		res[1] = '\0';
		return res;
	}

	char res[10000];

	uint8_t temp[16];
	uint8_t temp_pos = 15;
	for (uint16_t digit = numerator/denominator; digit != 0 && temp_pos != 15; digit /= 10) {
		temp[temp_pos--] = digit % 10;
	}
	int32_t pos;
	for (pos = 0; pos < 16, temp_pos < 16; pos++) {
		res[pos] = temp[++temp_pos] + '0';
	}
	res[++pos] = '.';

	int32_t seen[10000];
	memset(seen, -1, 10000);

	int32_t remainder = numerator % denominator;
	while (remainder != 0) {
		if (seen[remainder] != -1) {
			memmove(&res[seen[remainder]+1], &res[seen[remainder]], pos-seen[remainder]-1);
			res[seen[remainder]] = '(';
			res[pos++] = ')';
			break;
		}
		remainder *= 10;
		printf("%d\n", remainder);
		printf("%d\n", remainder / denominator);
		res[pos++] = (remainder / denominator) + '0';
		printf("%c\n", res[pos - 1]);
		remainder %= denominator;
	}

	char *ret;
	ret = malloc((pos) * sizeof(char));

	memcpy(ret, res, pos+1);
	ret[pos+1] = '\0';

	printf(ret);

	return ret;
}
