#include "shdstd.h"

bool isTrionic(int *nums, int size)
{
	if (size < 4) {
		return false;
	}

	int step1, step2, step3;
	step1 = step2 = step3 = -1;

	int ptr = 0;
	while (ptr < size - 1 && nums[ptr] < nums[ptr+1]) ++ptr;
	step1 = ptr;

	if (step1 == 0) {
		return false;
	}

	while (ptr < size - 1 && nums[ptr] > nums[ptr+1]) ++ptr;
	step2 = ptr;

	if (step1 == step2) {
		return false;
	}

	while (ptr < size - 1 && nums[ptr] < nums[ptr+1]) ++ptr;
	step3 = ptr;

	if (step2 == step3) {
		return false;
	}

	return (ptr == size - 1);
}
