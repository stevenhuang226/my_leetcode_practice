#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char *fractionToDecimal(int numerator, int denominator);
int main()
{
	int32_t a = 4;
	int32_t b = 333;
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
	
	uint8_t neg_mark = 0;
	if (((numerator < 0) + (denominator < 0)) == 1) {
		neg_mark = 1;
	}
	int32_t num = abs(numerator);
	int32_t den = abs(denominator);


	char res[10000];

	char temp[16];
	uint8_t temp_pos = 15;

	int32_t digit = num / den;
	do {
		temp[temp_pos--] = digit % 10 + '0';
		digit /= 10;
	} while (digit != 0);

	int32_t pos;
	temp_pos++;
	for (pos = 0; temp_pos < 16; temp_pos++) {
		res[pos++] = temp[temp_pos];
	}

	res[pos] = '.';
	int32_t rem = num % den;
	if (rem == 0) {
		pos--;
		goto skip;
	}

	int32_t *seen;
	seen = malloc(sizeof(int32_t) * 214748364);
	memset(seen, -1, sizeof(int32_t) * 214748364);

	while (rem != 0) {
		if (seen[rem] != -1) {
			memmove(&res[seen[rem]+1], &res[seen[rem]], (++pos) - seen[rem]);
			res[seen[rem]] = '(';
			res[++pos] = ')';
			break;
		}
		seen[rem] = ++pos;
		rem *= 10;
		res[pos] = (rem/den) + '0';
		rem %= den;
	}

skip:
	char *ret;
	ret = malloc((pos+3) * sizeof(char));
	if (neg_mark == 1) {
		memcpy(&ret[1], &res, pos+1);
		ret[0] = '-';
		ret[pos+2] = '\0';
	}
	else {
		memcpy(ret, &res, pos+1);
		ret[pos+1] = '\0';
	}

	return ret;
}
