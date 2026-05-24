#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int distance;
int *max_jump;
int *height;
int size;

int smax(const int left, const int right)
{
	return MAX(left, right);
}

int dfs(int id)
{
	if (max_jump[id] > 0) {
		return max_jump[id];
	}

	++max_jump[id];
	int curr_max = height[id];
	int off = 0;
	while (off++ < distance) {
		int Lid = id - off;
		if (Lid < 0) break;
		if (height[Lid] <= curr_max) continue;

		max_jump[id] = smax(max_jump[id], dfs(Lid) + 1);
		curr_max = smax(curr_max, height[Lid]);
	}

	curr_max = height[id];
	off = 0;
	while (off++ < distance) {
		int Rid = id + off;
		if (Rid >= size) break;
		if (height[Rid] <= curr_max) continue;

		max_jump[id] = smax(max_jump[id], dfs(Rid) + 1);
		curr_max = smax(curr_max, height[Rid]);
	}

	return max_jump[id];
}

int maxJumps(int *arr, int _size, int d)
{
	height = arr;
	size = _size;
	distance = d;

	max_jump = malloc(size * sizeof(int));
	memset(max_jump, 0x00, size * sizeof(int));

	int best = 0;
	for (int i = 0; i < size; ++i) {
		best = smax(best, dfs(i));
	}

	free(max_jump);

	return best;
}
