#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int maxIncreasingSubarrays(int *nums, int numsSize)
{
	int i;
	int combos = 1;
	int last_combos = 1;
	int max_solo_combos = 1;
	int max_combos = 1;
	for (i = 1; i < numsSize; i++) {
		if (nums[i] > nums[i-1]) {
			combos++;
			continue;
		}
		if (combos > max_solo_combos) {
			max_solo_combos = combos;
		}
		if (last_combos > max_combos && combos > max_combos) {
			if (last_combos < combos) {
				max_combos = last_combos;
			} else {
				max_combos = combos;
			}
		}
		last_combos = combos;
		combos = 1;
	}
	if (combos > max_solo_combos) {
		max_solo_combos = combos;
	}
	if (last_combos > max_combos && combos > max_combos) {
		if (last_combos < combos) {
			max_combos = last_combos;
		} else {
			max_combos = combos;
		}
	}

	int res;
	if (max_solo_combos/2 > max_combos) {
		res = max_solo_combos / 2;
	} else {
		res = max_combos;
	}

	return res;
}
