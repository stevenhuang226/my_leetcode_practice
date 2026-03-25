#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX_SENATE 10004

char *predictPartyVictory(char *senate)
{
	char *r_win = "Radiant";
	char *d_win = "Dire";

	int size = strlen(senate);

	int *d_pos = malloc(MAX_SENATE * sizeof(int));
	int *r_pos = malloc(MAX_SENATE * sizeof(int));
	int d_left = 0, d_right = 0;
	int r_left = 0, r_right = 0;

	for (int i = 0; i < size; ++i) {
		char c = senate[i];
		if (c == 'D') {
			d_pos[d_right++] = i;
		} else {
			r_pos[r_right++] = i;
		}
	}

	while (d_left < d_right && r_left < r_right) {
		int d = d_pos[d_left++];
		int r = r_pos[r_left++];

		if (d < r) {
			d_pos[d_right++] = d + size;
		} else {
			r_pos[r_right++] = r + size;
		}
	}

	free(d_pos);
	free(r_pos);

	if (d_left < d_right) {
		return d_win;
	} else {
		return r_win;
	}
}

