#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

struct Node {
	int16_t x;
	int16_t y;
	int8_t next_cost;
};

int minTimeToReach(int **moveTime, int moveTimeSize, int moveTimeColSize)
{
	int *timeTable;
	timeTable = calloc(0, moveTimeSize * moveTimeColSize * sizeof(int));

	int16_t xptr = 0;
	int16_t yptr = 0;

	int16_t now_size = 1;
	int16_t new_ptr = 0;

_build_now_queue:
	struct Node *now_queue = malloc(now_size * sizeof(struct Node));
_build_new_queue:
	struct Node *new_queue = malloc(now_size * 2 * sizeof(struct Node));
_loop:
	for (int i = 0; i < now_size; ++i) {
_checkX:
		int nowTime = timeTable[now_queue[i].x + now_queue[i].y * moveTimmeSize];
		int *nextTime = timeTable[now_queue[i].x + 1 + now_queue[i].y * moveTimeSize];
		if (*nextTime == 0) {
			*nextTime = nowTime + now_queue[i].next_cost;
			if (moveTime[now_queue[i].y][now_queue[i].x + 1] > *nextTime) {
				*nextTime = moveTime[now_queue[i].y][now_queue[i].x + 1] + now_queue[i].next_cost;a
			}
		}
	}
}

int main()
{
	return 0;
}
