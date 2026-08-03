#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define INF32 (INT32_MAX / 4)
#define NEG_INF32 -(INF32)
char *stoneGameIII(int *stones, int stones_size)
{
	int *max_score = malloc(stones_size * sizeof(int));

	for (int i = stones_size-1; i >= 0; --i) {
		int take = 0;
		max_score[i] = NEG_INF32;
		for (int i2 = 0; i2 < 3; ++i2) {
			if (i + i2 >= stones_size)
				break;

			int next;
			if (i+i2+1 >= stones_size) {
				next = 0;
			} else {
				next = max_score[i+i2+1];
			}

			take += stones[i+i2];
			max_score[i] = MAX(max_score[i], take - next);
		}
	}

	char *res = malloc(10 * sizeof(char));
	int adv = max_score[0];
	free(max_score);

	if (adv > 0) {
		strcpy(res, "Alice");
		return res;
	}
	if (adv < 0) {
		strcpy(res, "Bob");
		return res;
	}
	strcpy(res, "Tie");
	return res;
}
