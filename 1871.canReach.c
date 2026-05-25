#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static inline int smax(const int left, const int right)
{
	return MAX(left, right);
}
static inline int smin(const int left, const int right)
{
	return MIN(left, right);
}

bool canReach(char *s, int min, int max)
{
	int length = strlen(s);

	int8_t ans = false;

	int8_t *visited = calloc(length, sizeof(int8_t));

	int *queue = malloc(length * sizeof(int));
	int front, back;
	front = back = 0;

	queue[front++] = 0;
	visited[0] = true;

	int scaned = 0;
	while (back < front) {
		int curr = queue[back++];

		if (curr == length-1) {
			goto _reachable;
		}

		int start = smax(curr + min, scaned);
		int end = smin(curr + max, length - 1);
		scaned = end + 1;

		for (int i = start; i <= end; ++i) {
			if (s[i] == '0' && !visited[i]) {
				visited[i] = true;
				queue[front++] = i;
			}
		}
	}

	goto _end;

_reachable:
	ans = true;

_end:
	free(visited);
	free(queue);

	return ans;
}
