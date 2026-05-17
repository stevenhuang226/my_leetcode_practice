#include "shdstd.h"

bool canReach(int *arr, int size, int start)
{
	int8_t *visited = calloc(size, sizeof(int8_t));

	int *queue = malloc(size * sizeof(int));
	int front = 0;
	int back = 0;

	queue[front++] = start;
	visited[start] = true;

	while (back < front) {
		int curr = queue[back++];
		if (arr[curr] == 0) {
			goto rt_true;
		}

		int left = curr - arr[curr];
		int right = curr + arr[curr];

		if (left >= 0 && !visited[left]) {
			visited[left] = true;
			queue[front++] = left;
		}
		if (right < size && !visited[right]) {
			visited[right] = true;
			queue[front++] = right;
		}
	}

	free(visited);
	free(queue);
	return false;
rt_true:
	free(visited);
	free(queue);
	return true;
}
