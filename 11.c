#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
}

int maxArea(int *height, int heightSize)
{
	int l = 0;
	int r = heightSize - 1;
	int max = 0;
	int hl, hr, mh;
	for (; l < r; ) {
		hl = height[l];
		hr = height[r];
		if (hl > hr) {
			mh = hr;
			r--;
		} else {
			mh = hl;
			l++;
		}
		if (mh * (r-l+1) > max) {
			max = mh * (r-l+1);
		}

	}

	return max;
}
