#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

int main()
{
}

int64_t minOperations(int **queries, int queriesSize, int *queriesColSize)
{
	int64_t total = 0;
	for (int i = 0; i < queriesSize; i++) {
		int64_t part_num = 0;
		int min = queries[i][0];
		int max = queries[i][1];
		int64_t square = 4;
		int64_t last_square = 0;
		for (int ii = 1; ii < max; ii++) {
			if (square >= max && last_square < min) {
				part_num += (max - min + 1) * ii;
				break;
			}
			else if (last_square < min && square > min) {
				part_num += (square - min) * ii;
				continue;
			}
			else if (last_square < max && square >= max) {
				part_num += (max - last_square + 1) * ii;
				break;
			}
			else if (last_square >= min && square < max) {
				part_num += (square - last_square) * ii;
			}
			last_square = square;
			square *= 4;
		}
		
		total += part_num/2;
	}

	return total;
}
