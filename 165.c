#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int compareVersion(char *version1, char *version2);
int main()
{
	return 0;
}

int compareVersion(char *version1, char *version2)
{
	int32_t v1_ptr = 0;
	int32_t v2_ptr = 0;
	int32_t v1_len = strlen(version1);
	int32_t v2_len = strlen(version2);

	int32_t v1 = 0;
	int32_t v2 = 0;

	int result = 0;
	while (v1_ptr < v1_len || v2_ptr < v2_len) {
		if (version1[v1_ptr] == '.') {
			v1 = 0;
			v1_ptr++;
			continue;
		}
		if (version2[v2_ptr] == '.') {
			v2 = 0;
			v2_ptr++;
			continue;
		}
		while (v1_ptr < v1_len && (version1[v1_ptr] != '.')) {
			v1 *= 10;
			v1 += version1[v1_ptr++] - '0';
		}
		while (v2_ptr < v2_len && (version2[v2_ptr] != '.')) {
			v2 *= 10;
			v2 += version2[v2_ptr++] - '0';
		}
		if (v1 == v2) {
			v1 = v2 = 0;
			continue;
		}
		if (v1 > v2) {
			result = 1;
			break;
		}
		else {
			result = -1;
			break;
		}
	}

	return result;
}
