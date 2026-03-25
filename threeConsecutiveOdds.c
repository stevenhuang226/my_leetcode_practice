#include <stdio.h>
#include <stdbool.h>

bool threeConsecutiveOdds(int* arr, int arrSize)
{
	int8_t ok_1 = 0;
	int8_t ok_2 = 0;

	for (int i = 0; i < arrSize; ++i) {
		if (arr[i] %2 == 0) {
			ok_1 = 0;
			ok_2 = 0;
			continue;
		}

		if (ok_1 == 1 && ok_2 == 1) {
			return true;
		}
		if (ok_1 == 1) {
			ok_2 = 1;
			continue;
		}
		ok_1 = 1;
	}
	return false;
}
