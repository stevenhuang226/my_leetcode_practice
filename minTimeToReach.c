#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#define INF 0xFFFFFFFF

int minTimeToReach(int **moveTime, int moveTimeSize, int moveTimeColSize)
{
	int **time_table;
	*time_table = malloc(moveTimeSize * sizeof(int *));
	for (int i = 0; i < moveTimeSize; ++i) {
		time_table[i] = calloc(INF, moveTimeColSize * sizeof(int));
	}
	time_table[0][0] = 0;

	int8_t **cost_table;
	*cost_table = malloc(moveTimeSize * sizeof(int8_t *));
	for (int i = 0; i < now_size; ++i) {
		cost_table = malloc(moveTimeColSie * sizeof(int8_t));
	}

	int now_size = 1;

	int16_t *now_n_queue;
	int16_t *now_m_queue;
	now_n_queue = malloc(now_size * sizeof(int16_t));
	now_m_queue = malloc(now_size * sizeof(int16_t));
	int16_t *new_n_queue;
	int16_t *new_m_queue;
	new_n_queue = malloc(now_size * 3 * sizeof(int16_t));
	new_m_queue = malloc(now_size * 3 * sizeof(int16_t));

	for (int i = 0; i < now_size; ++i) {
	}
}

int main()
{
}
