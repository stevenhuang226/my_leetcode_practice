#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CNT_SIZE 100
#define CNT_COL_SIZE 2

#define ID 0
#define TTF 1

/*
 * request mini_heap push/pop, with captivity to handle different source to read
 */

void mini_heap_push(int **heap, int *size, int new, int side)
{
	int index = *size;
	int parent;

	heap[index][side] = new;
	++(*size);

	while (index > 0) {
		parent = (index - 1)/2;
		if (heap[parent][side] <= heap[index][side]) {
			break;
		}

		int tmp = heap[parent][side];
		heap[parent][side] = heap[index][side];
		heap[index][side] = tmp;

		index = parent;
	}

	return;
}

int mini_heap_pop(int **heap, int *size, int side) /* return id anyway */
{
	int ret_id = heap[0][ID];
	int last = heap[*size - 1][side];
	int index = 0;

	--(*size);

	for (;;) {
		int child_a = index * 2 + 1;
		int child_b = index * 2 + 2;

		int min_id = index;

		if (heap[child_a][side] < heap[min_id][side]) {
			min_id = child_a;
		}
		if (heap[child_b][side] < heap[min_id][side]) {
			min_id = child_b;
		}

		if (min_id == index) {
			break;
		}

		int tmp = heap[index][side];
		heap[index][side] = heap[min_id][side];
		heap[min_id][side] = tmp;
	}

	return ret_id;
}

int mostBooked(int room, int **meetings, int meetings_size, int *meetings_col_size)
{
	int *free_room_flat = malloc(CNT_SIZE * CNT_COL_SIZE * sizeof(int));
	int **free_room = malloc(CNT_SIZE * sizeof(int *));
	int free_size = 0;

	int *meeting_flat = malloc(CNT_SIZE * CNT_COL_SIZE * sizeof(int));
	int **meeting = malloc(CNT_SIZE * sizeof(int *));
	int meeting_size = 0;

	int cnt_id[CNT_SIZE+1] = {0};

	int i;
	for (i = 0; i < CNT_SIZE; ++i) {
		free_room[i][0] = i;
		free_room[i][1] = 0;
	}

	for (i = 0; i < meetings_size; ++i) {
		if (id_size > 0) {
			int id = mini_heap_pop(room_id, id_size, ID);
			mini_heap_push(meeting, meeting_size, id, TTF);
		}
		/*
		 * pop from ttf
		 *
		 * making ttf = 0, recode id, push back to room_id
		 */

		int id = mini_heap_pop()
	}
}
