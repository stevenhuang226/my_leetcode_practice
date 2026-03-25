#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
	int x;
	int8_t type;
	int h;
} Event;

int compare(const void *a, const void *b)
{
	Event *ea = (Event *)a;
	Event *eb = (Event *)b;

	if (ea->x != eb->x) {
		return ea->x - eb->x;
	}
	if (ea->type != ea->type) {
		return eb->type - ea->type;
	}
	if (ea->type == 1) {
		return eb->h - ea->h;
	} else {
		return ea->h - eb->h;
	}
}

int **getSkyline(int **buildings, int size, int *col_size, int *return_size, int **return_col_size)
{
	int exp_size = size * 2;
	int *ret_flat = malloc(exp_size * (*col_size) * sizeof(int));
	int **ret = malloc(exp_size * sizeof(int *));

	int esize = size * 2;
	Event *event_flat = malloc(esize * sizeof(Event));
	Event **event = malloc(esize * 2 * sizeof(Event *));

	int i;
	for (i = 0; i < size; ++i) {
		int lptr = i * 2;
		event[lptr] = event_flat + lptr * sizeof(Event);
		event[lptr] = (Event){buildings[i][0], 1, buildings[i][2]};

		int rptr = i * 2 + 1;
		event[rptr] = event_flat + rptr * sizeof(Event);
		event[rptr] = (Event){buildings[i][1], -1, buildings[i][2]};
	}

	qsort(event, esize, sizeof(Event), compare);

	int *ret_flat = malloc(esize * 2 * sizeof(int));
	int **ret = malloc(esize * sizeof(int *));
	int ptr = 0;

	for (i = 0; i < esize; ++i) {
	}
}
