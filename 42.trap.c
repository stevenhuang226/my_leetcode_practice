#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int trap(int *height, int size)
{
	int trapped = 0;

	int left = 0;
	int right = size - 1;

	int left_max = 0;
	int right_max = 0;

	for (; left < right; ) {
		if (height[left] < height[right]) {
			left_max = MAX(left_max, height[left]);
			trapped += left_max - height[left++];
		} else {
			right_max = MAX(right_max, height[right]);
			trapped += right_max - height[right--];
		}
	}

	return trapped;
}

int main()
{
	int height[] = {0,1,0,2,1,0,1,3,2,1,2,1};
	int size = sizeof(height) / sizeof(height[0]);
	int ans = trap(height, size);
	printf("%d\n", ans);
}
