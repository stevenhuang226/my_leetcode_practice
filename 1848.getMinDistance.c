#include "shdstd.h"

int getMinDistance(int *nums, int size, int target, int start)
{
	int left_off = 0;
	int right_off = 0;

	while (start + left_off >= 0 || start + right_off < size) {
		if (start + left_off >= 0 &&
			nums[start+left_off] == target) {
			return -left_off;
		}
		if (start + right_off < size &&
			nums[start+right_off] == target) {
			return right_off;
		}
		--left_off;
		++right_off;
	}

	return -1;
}
