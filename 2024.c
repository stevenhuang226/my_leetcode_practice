#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int maxConsecutiveAnswers(char *s, int k)
{
	int size = strlen(s);

	int max = 0;

	int i,t;
	t = 2;
	char target = 'T';
	for (i = 0; i < t; ++i) {
		int r;
		int l = 0;
		int nsum = 0;

		for (r = 0; r < size; ++r) {
			nsum += (s[r] == target);

			while (nsum > k) {
				nsum -= (s[l++] == target);
			}

			int len = r - l;
			if (len > max) {
				max = len;
			}
		}

		target = 'F';
	}

	return max + 1;
}
