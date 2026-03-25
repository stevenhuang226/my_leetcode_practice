#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MAX_CALL 10004

typedef struct {
	int *called_time;
	int left;
	int right;
} RecentCounter;

RecentCounter *recentCounterCreate()
{
	RecentCounter *counter = malloc(1 * sizeof(RecentCounter));
	counter->called_time = malloc(MAX_CALL * sizeof(int));
	counter->left = 0;
	counter->right = 0;

	return counter;
}

int recentCounterPing(RecentCounter *counter, int timestamp)
{
	int track_back = 3000;
	int tr = counter->right;
	int tl = counter->left;
	int *called = counter->called_time;
	called[tr++] = timestamp;
	while (called[tl] < timestamp - track_back) {
		++tl;
	}

	int ret = tr - tl;
	counter->right = tr;
	counter->left = tl;
	return ret;
}

void recentCounterFree(RecentCounter *counter)
{
	free(counter->called_time);
	free(counter);
	return;
}
