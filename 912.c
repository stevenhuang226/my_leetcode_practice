#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

int *arr;

void merge(int *src, int l, int r)
{
	if (r - l <= 1) {
		return;
	}

	int mid = (l + r) / 2;

	merge(src, l, mid);
	merge(src, mid, r);

	if (src[mid-1] <= src[mid]) {
		return;
	}

	int pl,pr,ptr;

	ptr = pl = l;
	pr = mid;

	while (pl < mid && pr < r) {
		if (src[pl] < src[pr]) {
			arr[ptr++] = src[pl];
			++pl;
		} else {
			arr[ptr++] = src[pr];
			++pr;
		}
	}

	while (pl < mid) {
		arr[ptr++] = src[pl++];
	}

	while (pr < r) {
		arr[ptr++] = src[pr++];
	}

	for (int i = l; i < r; ++i) {
		src[i] = arr[i];
	}

	return;
}

int *sortArray(int *nums, int size, int *p_return_size)
{
	arr = malloc(size * sizeof(int));
	(*p_return_size) = size;

	arr[0] = 0;

	merge(nums, 0, size);

	memcpy(arr, nums, size * sizeof(int));

	return arr;
}

int main()
{
	int nums[] = {5,2,1,3};
	int size = sizeof(nums) / sizeof(nums[0]);
	int ret_size;
	int *res = sortArray(nums, size , &ret_size);
	printf("%d %d %d %d\n", res[0], res[1], res[2], res[3]);
	free(res);
	return 0;
}
