#include "shdstd.h"

bool check(int *nums, int size)
{
	int off;
	for (off = 0; off < size; ++off) {
		int left = (off + size - 1) % size;
		if (nums[left] > nums[off]) {
			break;
		}
	}

	for (int i = 0; i < size - 1; ++i) {
		int curr = (off+i) % size;
		int next = (off+i+1) % size;

		if (nums[curr] > nums[next]) {
			return false;
		}
	}

	return true;
}
