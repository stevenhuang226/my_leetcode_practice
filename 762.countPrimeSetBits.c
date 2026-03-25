#include "shdstd.h"



int countPrimeSetBits(const int left, const int right)
{
	int bits_count_is_prime_count = 0;

	for (int num = left; num <= right; ++num) {
		int tmp = num;

		int bits_count = 0;
		while (tmp) {
			bits_count += (tmp & 0x01);
			tmp >>= 1;
		}

		switch (bits_count) {
			case 2:
			case 3:
			case 5:
			case 7:
			case 11:
			case 13:
			case 17:
			case 19:
			case 23:
			case 29:
			case 31:
				++bits_count_is_prime_count;
				break;
		}
	}

	return bits_count_is_prime_count;
}
