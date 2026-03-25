#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int *prefix;

int numSub(char *s)
{
	int str_size = strlen(s);
	prefix = malloc((str_size+1) * sizeof(int));
	int i;

	for (i = 0; i < str_size; ++i) {
		prefix[i+1] = prefix[i] + (s[i] == '1');
	}

	int win_size;

	int res_count = 0;
	for (win_size = 0; win_size < str_size; ++win_size) {
		int right;
		/*printf("win_size: %d\n", win_size); /**/
		for (right = win_size; right < str_size; ++right) {
			int left = right - win_size;
			int cnt_one = prefix[right+1] - prefix[left];
			/*printf("l: %d, r: %d cnt: %d\n", left, right, cnt_one); /**/
			if (cnt_one == win_size + 1) {
				++res_count;
			}
		}
	}
	
	free(prefix);

	return res_count;
}

int main()
{
	char *s = "0110111";
	int res = numSub(s);

	printf("%d\n", res);

	return 0;
}
