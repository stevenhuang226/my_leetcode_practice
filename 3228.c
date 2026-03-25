#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int maxOperations(char *s)
{
	int i;
	int size = strlen(s);

	int curr_count = 0;
	int total_count = 0;
	int8_t continuing = 0;

	for (i = 0; i < size; ++i) {
		if (s[i] == '1' && continuing) {
			++curr_count;
			continue;
		}
		if (s[i] == '1') {
			continuing = 1;
			++curr_count;
			continue;
		}
		if (continuing) {
			total_count += curr_count;
			continuing = 0;
		}
	}


	return total_count;
}

int main()
{
	char s[] = "0100011011110";

	int res = maxOperations(s);

	printf("%d\n", res);

	return 0;
}
