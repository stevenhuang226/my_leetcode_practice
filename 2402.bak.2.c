#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_SIZE 102

void mh_free_push(int *heap, int *size, int id)
{
	int index = *size;
	int parent;
	++(*size);
	heap[index] = id;
	while (index > 0) {
		parent = (index - 1) / 2;

		if (heap[parent] <= heap[index]) {
			break;
		}

		int tmp = heap[parent];
		heap[parent] = heap[index];
		heap[index] = tmp;
	}
	return;
}

int mh_free_pop(int *heap, int *size)
{
	int ret = heap[0];
	int last = heap[(*size) - 1];
	int index = 0;
	--(*size);

	if (*size <= 0) {
		return ret;
	}

	int child_a;
	int child_b;

	for (;;) {
		child_a = index * 2 + 1;
		child_b = index * 2 + 2;

		if (child_a > *size) {
			break;
		}

		int min = child_a;
		if (child_b < *size && heap[child_b] < heap[min]) {
			min = child_b;
		}

		if (heap[index] < heap[min]) {
			break;
		}

		int tmp = heap[min];
		heap[min] = heap[index];
		heap[index] = tmp;
	}

	return ret;
}

void mh_meeting_push(int **heap, int *size, int id, int ttf)
{
}

int mh_meeting_pop(int **heap, int *size) /* by min ttf*/
{
}

int mostBooked(int n, int **meetings, int meetings_size, int *meeting_col_size)
{
	int i;
	int *free_room = malloc(n * sizeof(int));
	int free_size = 0;

	int *meet_flat = malloc(n * 2 * sizeof(int));
	int **meet = malloc(n * sizeof(int *));
	int meet_size = 0;

	uint32_t book[n];

	for (i = 0; i < n; ++i) {
		mh_free_push(free_room, &free_size, i);
		meet[i] = meet_flat + i * 2;
		book[i] = 0;
	}

	for (i = 0; i < meetings_size; ++i) {
		int ttf = meetings[i][1] - meetings[i][0];
		if (free_size > 0) {
			int id = mh_free_pop(free_room, &free_size);
			++book[id];
			mh_meeting_push(meet, &meet_size, id, ttf);
			continue;
		}
		int id = mh_meeting_pop(meet, &meet_size);
		mh_free_push(free_room, &free_size, id);
	}

	int max = 0;
	for (i = 0; i < n; ++i) {
		if (book[i] > max) {
			max = book[i];
		}
	}

	return max;
}
