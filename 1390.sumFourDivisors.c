#include "shdstd.h"

#define IS_PRIME_SIZE 5000

int8_t is_prime[IS_PRIME_SIZE];
/*
 * -1 => not prime
 *  0 => not sure
 *  1 => prime
 */

int8_t check_prime(int num) {
	if (num == 2) {
		return true;
	}
	if (num % 2 == 0 || num < 2) {
		return false;
	}
	for (int i = 3; i * i <= num; i += 2) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

int8_t chk_prime(int num)
{
	if (is_prime[num] != 0) {
		if (is_prime[num] == 1) {
			return true;
		} else {
			return false;
		}
	}

	if (check_prime(num)) {
		is_prime[num] = 1;
		return true;
	} else {
		is_prime[num] = -1;
		return false;
	}
}

int sumFourDivisors(int *nums, int size)
{
	/*
	 * pre number
	 * finding first left => nums[i] % left == 0 && is_prime(left)
	 * finding right => nums[i] / left = right && is_prime(right) => this nums[i] has exactly 4 divisor
	 */

	int sum = 0;

	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		for (int left = 2; left * left < num; ++left) {
			if (num % left != 0) {
				continue;
			}
			if (! chk_prime(left)) {
				continue;
			}

			if (left * left * left == num) {
				sum += (1 + left + left * left + num);
			}

			int right = num / left;

			if (chk_prime(right)) {
				sum += (1 + left + right + num);
			}
			break;
		}
	}

	return sum;
}
