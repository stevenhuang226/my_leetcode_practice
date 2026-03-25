#include "shdstd.h"

#define MAX_ROTTED 50

typedef struct {
	int v;
	int h;
} Rotted;

int d_size = 4;
int dv[] = {-1, 0, 1, 0};
int dh[] = {0, 1, 0, -1};

int orangesRotting(int **grid, const int size, const int *arr_col_size)
{
	int col_size = arr_col_size[0];

	Rotted *quene = malloc(MAX_ROTTED * sizeof(Rotted));
	int quene_size = 0;

	Rotted *next = malloc(MAX_ROTTED * sizeof(Rotted));
	int next_size = 0;

	int8_t init_fresh = false;

	for (int i = 0; i < size; ++i) {
		for (int i2 = 0; i2 < col_size; ++i2) {
			if (grid[i][i2] == 1) init_fresh = true;
			if (grid[i][i2] != 2) continue;

			quene[quene_size].v = i;
			quene[quene_size].h = i2;
			++quene_size;
		}
	}

	if (! init_fresh) {
		free(quene);
		free(next);
		return 0;
	}

	int passed_time = 0;

	while (quene_size) {
		++passed_time;
		for (int i = 0; i < quene_size; ++i) {
			int ov = quene[i].v;
			int oh = quene[i].h;
			for (int k = 0; k < d_size; ++k) {
				int nv = ov + dv[k];
				int nh = oh + dh[k];

				if (nv < 0 || nv >= size ||
				nh < 0 || nh >= col_size) {
					continue;
				}

				if (grid[nv][nh] != 1) {
					continue;
				}

				grid[nv][nh] = 2;
				next[next_size].v = nv;
				next[next_size].h = nh;
				++next_size;
			}
		}
		
		Rotted *tmp = quene;
		quene = next;
		next = tmp;

		quene_size = next_size;
		next_size = 0;
	}

	int8_t have_fresh = false;
	for (int i = 0; i < size; ++i) {
		for (int i2 = 0; i2 < col_size; ++i2) {
			if (grid[i][i2] == 1) {
				have_fresh = true;
				break;
			}
		}
		if (have_fresh) {
			break;
		}
	}

	free(quene);
	free(next);

	if (have_fresh) {
		return -1;
	} else {
		return passed_time - 1;
	}
}
