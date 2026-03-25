#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int *ones_prefix;
int *zero_pos;

int numberOfSubstrings(char *s)
{
	int size = strlen(s);
	/*
	ones_prefix = malloc((size+1) * sizeof(int));
	ones_prefix[0] = 0;
	zero_pos = malloc(size * sizeof(int));
	*/

	/*
	int i,zp_size = 0;
	for (i = 0; i < size; ++i) {
		ones_prefix[i+1] = ones_prefix[i] + (s[i] - '0');
		if (s[i] == '0') {
			zero_pos[zp_size++] = i;
		}
	}
	*/

	int count = 0;
	int zero_lim = (int)sqrt(size) + 2;

	int zeros, left, right;
	for (zeros = 0; zeros < zero_lim; ++zeros) {
		left = 0;
		right = 0;
		int zero_count = 0;
		int one_count = 0;
		int p = 0;
		while (right < size) {
			if (s[right] == '0') {
				++zero_count;
			} else {
				++one_count;
			}
			while (zero_count > zeros) {
				if (s[left++] == '0') {
					--zero_count;
				} else {
					--one_count;
				}
			}
			if (zero_count == zeros && one_count && one_count >= zeros * zeros) {
				if (p < left) {
					p = left;
				}
				while (p < right && s[p] == '1') {
					++p;
				}

				int leading = p - left;
				int extra_one = one_count - zeros * zeros;

				count += 1 + (leading < extra_one ? leading : extra_one);
			}
			++right;
		}
	}

	return count;
}

int main()
{
	char *a = "00011";
	int res = numberOfSubstrings(a);
	printf("%d\n", res);
	char *b = "101101";
	res = numberOfSubstrings(b);
	printf("%d\n", res);
	return 0;
}
