#include "shdstd.h"

#define MAX_BFS 300

typedef struct {
	int m;
	int n;
} Step;

int dsize = 4;
int dm[] = {0, 1, 0, -1};
int dn[] = {-1, 0, 1, 0};

int nearestExit(char **maze, int size, int *col_size,
	int *entrance, int entrance_size)
{
	int fcol_size = col_size[0];

	Step *quene = malloc(MAX_BFS * sizeof(Step));
	int quene_size = 0;

	Step *next = malloc(MAX_BFS * sizeof(Step));
	int next_size = 0;

	quene[0].m = entrance[0];
	quene[0].n = entrance[1];
	quene_size = 1;

	maze[entrance[0]][entrance[1]] = '+';

	int route_steps = 0;

	while (quene_size) {
		++route_steps;
		for (int i = 0; i < quene_size; ++i) {
			int m = quene[i].m;
			int n = quene[i].n;
			for (int k = 0; k < dsize; ++k) {
				int nm = m + dm[k];
				int nn = n + dn[k];

				if (nm < 0 || nm >= size ||
				nn < 0 || nn >= fcol_size) {
					continue;
				}

				if (maze[nm][nn] != '.') {
					continue;
				}

				if (nm == 0 || nm == size - 1 ||
				nn == 0 || nn == fcol_size - 1) {
					goto find_exit;
				}

				maze[nm][nn] = '+';

				next[next_size].m = nm;
				next[next_size].n = nn;
				++next_size;
			}
		}

		Step *tmp = quene;
		quene = next;
		next = tmp;

		quene_size = next_size;
		next_size = 0;
	}

	free(quene);
	free(next);

	return -1;

find_exit:
	free(quene);
	free(next);
	return route_steps;
}
