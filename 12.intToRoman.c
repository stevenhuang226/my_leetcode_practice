#include "shdstd.h"


static char roman[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

char *intToRoman(int num)
{
	int tmp_size = 20;
	char tmp[tmp_size];
	tmp[tmp_size-1] = '\0';

	int ptr = tmp_size - 2;
	int curr = 0;

	while (num) {
		int n = num % 10;

		switch (n) {
			case 9:
				tmp[ptr--] = roman[curr + 2];
				tmp[ptr--] = roman[curr];
				break;
			case 8:
				tmp[ptr--] = roman[curr];
			case 7:
				tmp[ptr--] = roman[curr];
			case 6:
				tmp[ptr--] = roman[curr];
			case 5:
				tmp[ptr--] = roman[curr + 1];
				break;
			case 4:
				tmp[ptr--] = roman[curr + 1];
				tmp[ptr--] = roman[curr];
				break;
			case 3:
				tmp[ptr--] = roman[curr];
			case 2:
				tmp[ptr--] = roman[curr];
			case 1:
				tmp[ptr--] = roman[curr];
				break;
		}

		num /= 10;
		curr += 2;
	}

	++ptr;
	char *ret_str = malloc((tmp_size - ptr) * sizeof(char));
	for (int i = ptr; i < tmp_size; ++i) {
		ret_str[i-ptr] = tmp[i];
	}

	return ret_str;
}
