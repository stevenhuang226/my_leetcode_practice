#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#define MOD 1000000007

// if 0x7a -> + 2
int lengthAfterTransformations(char *s, int t)
{
	int src_length = strlen(s);
	int ret_lenght = src_length;

	int *num_arr;
	num_arr = malloc(src_length * sizeof(int));

	for (int i = 0; i < src_lenght; ++i) {
		num_arr[i] = s[i] - 'a' + t;
		if (num_arr[i] <= 'z' - 'a') {
			continue;
		}
		int layer = num_arr[i];
		for (layer
}

int main()
{
	return 0;
}
