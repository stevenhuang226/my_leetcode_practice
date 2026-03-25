#include "shdstd.h"


int **g_rooms;
int *g_col_size;

int *visited;

/* give dfs a room_id that is unlocked */
void dfs(int room_id)
{
	int size = g_col_size[room_id];
	for (int i = 0; i < size; ++i) {
		int key = g_rooms[room_id][i];
		if (visited[key]) {
			continue;
		}
		visited[key] = 1;
		dfs(g_rooms[room_id][i]);
	}

	return;
}

bool canVisitAllRooms(int **rooms, int room_size, int *col_size)
{
	g_rooms = rooms;
	g_col_size = col_size;

	visited = calloc(1, room_size * sizeof(int));

	visited[0] = 1;
	dfs(0);

	for (int i = 0; i < room_size; ++i) {
		if (! visited[i]) {
			free(visited);
			return false;
		}
	}

	free(visited);
	return true;
}
