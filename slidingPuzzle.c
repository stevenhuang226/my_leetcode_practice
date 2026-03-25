#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

uint8_t *visited;

void mark_visited(uint8_t board[6])
{
	uint16_t index = 0;
	for (int i = 0; i < 6; ++i) {
		index += board[i];
		index *= 10;
	}
	index /= 10;

	visited[index / 8] |= (1 << (index % 8));
}

uint8_t is_visited(uint8_t board[6])
{
	uint16_t index = 0;
	for (int i = 0; i < 6; ++i) {
		index += board[i];
		index *= 10;
	}
	index /= 10;

	return (visited[index / 8] >> (index % 8)) & 1;
}

int slidingPuzzle(int **board, int boardSize, int *boardColSize)
{
	visited = calloc(15432, sizeof(uint8_t));
	int depth = 1;
	uint8_t *now_list;
	uint8_t *new_list;

	now_list = malloc(6 * sizeof(uint8_t));
	int now_size = 1;

	now_list[0] = (uint8_t)board[0][0];
	now_list[1] = (uint8_t)board[0][1];
	now_list[2] = (uint8_t)board[0][2];
	now_list[3] = (uint8_t)board[1][0];
	now_list[4] = (uint8_t)board[1][1];
	now_list[5] = (uint8_t)board[1][2];

	if (now_list[0] == 1 &&
		now_list[1] == 2 &&
		now_list[2] == 3 &&
		now_list[3] == 4 &&
		now_list[4] == 5 &&
		now_list[5] == 0) {
		free(visited);
		free(now_list);
		return 0;
	}

	int new_ptr = 0;
	new_list = malloc(12 * 6 * sizeof(uint8_t));

_next_surface:
	for (int i = 0; i < now_size; ++i) {
		uint8_t temp_board[6];
		if (now_list[i*6 + 0] == 0) {
			temp_board[1] = now_list[i*6 + 0]; // move 0 right;
			temp_board[0] = now_list[i*6 + 1];
			temp_board[2] = now_list[i*6 + 2];
			temp_board[3] = now_list[i*6 + 3];
			temp_board[4] = now_list[i*6 + 4];
			temp_board[5] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
			temp_board[3] = now_list[i*6 + 0]; // move 0 down
			temp_board[1] = now_list[i*6 + 1];
			temp_board[2] = now_list[i*6 + 2];
			temp_board[0] = now_list[i*6 + 3];
			temp_board[4] = now_list[i*6 + 4];
			temp_board[5] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
		}
		else if (now_list[i*6 + 1] == 0) {
			temp_board[0] = now_list[i*6 + 0]; // move 0 right;
			temp_board[2] = now_list[i*6 + 1];
			temp_board[1] = now_list[i*6 + 2];
			temp_board[3] = now_list[i*6 + 3];
			temp_board[4] = now_list[i*6 + 4];
			temp_board[5] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
			temp_board[0] = now_list[i*6 + 0]; // move 0 down;
			temp_board[4] = now_list[i*6 + 1];
			temp_board[2] = now_list[i*6 + 2];
			temp_board[3] = now_list[i*6 + 3];
			temp_board[1] = now_list[i*6 + 4];
			temp_board[5] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
			temp_board[1] = now_list[i*6 + 0]; // move 0 left;
			temp_board[0] = now_list[i*6 + 1];
			temp_board[2] = now_list[i*6 + 2];
			temp_board[3] = now_list[i*6 + 3];
			temp_board[4] = now_list[i*6 + 4];
			temp_board[5] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
		}
		else if (now_list[i*6 + 2] == 0) {
			temp_board[0] = now_list[i*6 + 0]; // move 0 left;
			temp_board[2] = now_list[i*6 + 1];
			temp_board[1] = now_list[i*6 + 2];
			temp_board[3] = now_list[i*6 + 3];
			temp_board[4] = now_list[i*6 + 4];
			temp_board[5] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
			temp_board[0] = now_list[i*6 + 0]; // move 0 down;
			temp_board[1] = now_list[i*6 + 1];
			temp_board[5] = now_list[i*6 + 2];
			temp_board[3] = now_list[i*6 + 3];
			temp_board[4] = now_list[i*6 + 4];
			temp_board[2] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
		}
		else if (now_list[i*6 + 3] == 0) {
			temp_board[0] = now_list[i*6 + 0]; // move 0 right;
			temp_board[1] = now_list[i*6 + 1];
			temp_board[2] = now_list[i*6 + 2];
			temp_board[4] = now_list[i*6 + 3];
			temp_board[3] = now_list[i*6 + 4];
			temp_board[5] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
			temp_board[3] = now_list[i*6 + 0]; // move 0 up;
			temp_board[1] = now_list[i*6 + 1];
			temp_board[2] = now_list[i*6 + 2];
			temp_board[0] = now_list[i*6 + 3];
			temp_board[4] = now_list[i*6 + 4];
			temp_board[5] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
		}
		else if (now_list[i*6 + 4] == 0) {
			temp_board[0] = now_list[i*6 + 0]; // move 0 left;
			temp_board[1] = now_list[i*6 + 1];
			temp_board[2] = now_list[i*6 + 2];
			temp_board[4] = now_list[i*6 + 3];
			temp_board[3] = now_list[i*6 + 4];
			temp_board[5] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
			temp_board[0] = now_list[i*6 + 0]; // move 0 up;
			temp_board[4] = now_list[i*6 + 1];
			temp_board[2] = now_list[i*6 + 2];
			temp_board[3] = now_list[i*6 + 3];
			temp_board[1] = now_list[i*6 + 4];
			temp_board[5] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
			temp_board[0] = now_list[i*6 + 0]; // move 0 right;
			temp_board[1] = now_list[i*6 + 1];
			temp_board[2] = now_list[i*6 + 2];
			temp_board[3] = now_list[i*6 + 3];
			temp_board[5] = now_list[i*6 + 4];
			temp_board[4] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
		}
		else if (now_list[i*6 + 5] == 0) {
			temp_board[0] = now_list[i*6 + 0]; // move 0 left;
			temp_board[1] = now_list[i*6 + 1];
			temp_board[2] = now_list[i*6 + 2];
			temp_board[3] = now_list[i*6 + 3];
			temp_board[5] = now_list[i*6 + 4];
			temp_board[4] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
			temp_board[0] = now_list[i*6 + 0]; // move 0 up;
			temp_board[1] = now_list[i*6 + 1];
			temp_board[5] = now_list[i*6 + 2];
			temp_board[3] = now_list[i*6 + 3];
			temp_board[4] = now_list[i*6 + 4];
			temp_board[2] = now_list[i*6 + 5];
			if (temp_board[0] == 1 &&
				temp_board[1] == 2 &&
				temp_board[2] == 3 &&
				temp_board[3] == 4 &&
				temp_board[4] == 5 &&
				temp_board[5] == 0) {
				goto _ret_ans;
			}
			if (! is_visited(temp_board)) {
				mark_visited(temp_board);
				memcpy(&new_list[new_ptr * 6], temp_board, 6);
				new_ptr++;
			}
		}
	}
	free(now_list);
	now_list = new_list;
	now_size = new_ptr;
	if (now_size > 0) {
		new_list = malloc(now_size * 2 * 6 * sizeof(uint8_t));
		new_ptr = 0;
		++depth;
		goto _next_surface;
	}
	else {
		free(now_list);
		free(visited);
		return -1;
	}
_ret_ans:
	free(now_list);
	free(new_list);
	free(visited);
	return depth;
}

int main()
{
	int **board = malloc(2 * sizeof(uint8_t *));
	for (int i = 0; i < 2; ++i) {
		board[i] = malloc(3 * sizeof(uint8_t));
	}

	board[0][0] = 1; board[0][1] = 2; board[0][2] = 3;
	board[1][0] = 4; board[1][1] = 0; board[1][2] = 5;
	int boardSize = 0;
	int boardColSize = 0;

	int ans = slidingPuzzle(board, boardSize, &boardColSize);
	free(board[0]);
	free(board[1]);
	free(board);
	printf("%d\n", ans);
	return 0;
}
