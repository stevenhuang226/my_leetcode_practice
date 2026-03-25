#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>

int main()
{
	return 0;
}

int* closestRoom(int **rooms, int roomsSize, int *roomsColSize, int **queries, int queriesSize, int *queriesColSize, int *returnSize)
{
	int *retArr;
	retArr = malloc(sizeof(int) * queriesSize);

	for (int i = 0; i < queriesSize; i++) {
		int preferred = queries[i][0];
		int minSize = queries[i][1];

		int min_gaps = INT_MAX;
		int room_id = -1;

		for (int ii = 0; ii < roomsSize; ii++) {
			if (rooms[ii][1] < minSize) {
				continue;
			}
			int gaps = abs(rooms[ii][0] - preferred);
			if (gaps > min_gaps) {
				continue;
			}
			if (gaps == min_gaps && rooms[ii][0] > room_id && room_id != -1) {
				continue;
			}
			min_gaps = gaps;
			room_id = rooms[ii][0];
		}
		retArr[i] = room_id;
	}

	*returnSize = queriesSize;

	return retArr;
}
