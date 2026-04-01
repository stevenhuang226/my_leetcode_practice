#include "shdstd.h"

char *generateString(char *str1, char *str2)
{
	int size_1 = strlen(str1);
	int size_2 = strlen(str2);

	int res_size = size_1 + size_2 - 1;

	char *result = calloc((res_size+1), sizeof(char));

	for (int i = 0; i < size_1; ++i) {
		int ch = str1[i];
		if (ch != 'T') continue;

		for (int i2 = 0; i2 < size_2; ++i2) {
			if (result[i+i2] != 0 &&
					result[i + i2] != str2[i2]) {
				result[0] = '\0';
				return result;
			}
			result[i+i2] = str2[i2];
		}
	}

	char *old = malloc((res_size+1) * sizeof(char));
	memcpy(old, result, (res_size+1) * sizeof(char));

	for (int i = 0; i < res_size; ++i) {
		if (result[i] == 0) {
			result[i] = 'a';
		}
	}

	for (int i = 0; i < size_1; ++i) {
		int ch = str1[i];
		if (ch != 'F') continue;

		int8_t diff = false;
		for (int i2 = 0; i2 < size_2; ++i2) {
			if (result[i+i2] != str2[i2]) {
				diff = true;
				break;
			}
		}

		if (diff) continue;

		for (int i2 = size_2 - 1; i2 >= 0; --i2) {
			if (old[i+i2] == 0) {
				result[i+i2] = 'b';
				diff = true;
				break;
			}
		}

		if (! diff) {
			free(old);
			result[0] = '\0';
			return result;
		}
	}

	return result;
}
