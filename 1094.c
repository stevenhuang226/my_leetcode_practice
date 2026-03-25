#include "shdstd.h"

#define ROUTE_LIMIT 1004

bool carPooling(int **trips, int size, int *col_size, int capacity)
{
	uint32_t seats = 0;

	int *route = calloc(ROUTE_LIMIT, sizeof(int));
	int ptr = 0;

	int i;
	for (i = 0; i < size; ++i) {
		int *trip = trips[i];

		int passengers = trip[0];
		int src = trip[1];
		int dist = trip[2];

		route[src] += passengers;
		route[dist] -= passengers;
	}
	while (ptr < ROUTE_LIMIT) {
		seats += route[ptr++];
		if (seats > capacity) {
			return false;
		}
	}

	free(route);

	return true;
}
