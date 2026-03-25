#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char *pushDominoes(char *domines)
{
	int size = strlen(domines);
	char *output;
	output = malloc(size + 1 * sizeof(char));
	memset(output, 0x2e, size + 1);

	int last_mark = -1;
	for (int i = 0; i < size; ++i) {
		if (domines[i] == '.') {
			continue;
		}
		else if (domines[i] == 'R') {
			int next_L = 0;
			int next_R = 0;
			for (int ii = i+1; ii < size; ++ii) {
				if (domines[ii] == '.') {
					continue;
				}
				else if (domines[ii] == 'R') {
					last_mark = ii;
					next_R = ii;
					break;
				}
				else if (domines[ii] == 'L') {
					last_mark = ii;
					next_L = ii;
					break;
				}
			}
			if (next_R != 0) {
				for (int ii = i; ii <= next_R; ++ii) {
					output[ii] = 'R';
				}
				i = next_R - 1;
				continue;
			}
			if (next_L == 0) {
				for (int ii = i; ii < size; ++ii) {
					output[ii] = 'R';
				}
				break;
			}
			int length = next_L - i;
			if (length%2 == 0) {
				for (int ii = i; ii <= i + (length - 2) / 2; ++ii) {
					output[ii] = 'R';
				}
				for (int ii = i + (length - 2) / 2 + 2; ii <= next_L; ++ii) {
					output[ii] = 'L';
				}
			}
			else {
				for (int ii = i; ii <= i + (length - 1) / 2; ++ii) {
					output[ii] = 'R';
				}
				for (int ii = i + (length - 1) / 2 + 1; ii <= next_L; ++ii) {
					output[ii] = 'L';
				}
			}
			i = next_L;
			continue;
		}
		else if (domines[i] == 'L') {
			for (int ii = last_mark + 1; ii <= i; ++ii) {
				output[ii] = 'L';
			}
			last_mark = i;
		}
	}
	output[size] = 0x00;
	return output;
}

int main()
{
	char a[] = {'.','L','.','R','.','.','.','L','R','.','.','L','.','.'};
	for (int i = 0; i < 14; ++i) {
		printf("%c", a[i]);
	}
	printf("\n");
	char *o = pushDominoes(a);
	for (int i = 0; i < strlen(o); ++i) {
		printf("%c", o[i]);
	}
	free(o);
	printf("\n");
	return 0;
}
