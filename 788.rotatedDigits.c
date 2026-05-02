#include "shdstd.h"

int rotatedDigits(int n)
{
	int good_count = 0;

	int start = 1;
	for (int i = start; i <= n; ++i) {
		int tmp = i;

		int8_t is_good = true;
		int8_t changed = false;
		while (tmp) {
			int d = tmp % 10;

			switch (d) {
			case 3:
			case 4:
			case 7:
				is_good = false;
				break;
			case 0:
			case 1:
			case 8:
				break;
			case 2:
			case 5:
			case 6:
			case 9:
				changed = true;
				break;
			}

			if (!is_good) break;

			tmp /= 10;
		}

		if (is_good && changed) {
			++good_count;
		}
	}

	return good_count;
}
