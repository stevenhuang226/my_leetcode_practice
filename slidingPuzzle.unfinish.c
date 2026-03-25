#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TARGET {1,2,3,4,5,0}

struct Node {
	int board[6];
	struct Node *parent;
	struct Node *last;
	struct Node *next;
	int depth;
};

uint8_t *visited;

void swap()
{
}

void mark_visited(int board[6])
{
	int16_t index = 0;
	for (int i = 0; i < 6; ++i) {
		index += board[i];
		index *= 10;
	}

	visited[index / 8] |= (1 << (index % 8));
}

int8_t is_visited(int board[6])
{
	int16_t index = 0;
	for (int i = 0; i < 6; ++i) {
		index += board[i];
		index *= 10;
	}

	return (visited[index / 8] >> (index % 8)) & 1;
}


int slidingPuzzle(int **board, int boardSize, int *boardColSize)
{
	visited = calloc(5833, sizeof(uint8_t));
	struct Node head = {
		.parent = NULL,
		.last = NULL,
		.next = NULL,
		.depth = 0
	};

	head.board[0] = board[0][0];
	head.board[1] = board[0][1];
	head.board[2] = board[0][2];
	head.board[3] = board[1][0];
	head.board[4] = board[1][1];
	head.board[5] = board[1][2];

	struct Node *array_head = {
		.parent = &head;
		.depth = 1;
	};

	struct Node *last;
	last = NULL;;

	struct Node *now;
	now = head;

	int8_t had_head = 0;
	int depth;

	int temp_board[6];

	for (;;) {
		if (now->board[0] == 0  && now->parent->board[1] != 0) {
			temp_board = now->board[0];
			swap(temp_board[0], temp_board[1]);
			if(is_visited(temp_board) == 1) {
				return;
			}
			if (temp_board[6] == TARGET) {
				depth = now->board + 1;
				break;
			}
			mark_visited(temp_board);
			else {
				struct Node *new;
				new = malloc(sizeof(struct Node));
				new->board = temp_board;
				new->last = last;
				new->depth = now->board + 1;
				last = new;
			}
		}
	}


	free(visited);
	return depth;
}

int main()
{
	return 0;
}
