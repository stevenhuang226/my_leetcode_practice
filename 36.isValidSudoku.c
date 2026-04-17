#include "shdstd.h"


int dr[] = {0,-1,-1, 0, 1, 1, 1, 0,-1};
int dc[] = {0, 0, 1, 1, 1, 0,-1,-1,-1};
int d_size = 9;

static inline int ch_code(char ch)
{
	if (ch >= '1' && ch <= '9') {
		return ch - '0';
	}

	return 0;
}

bool isValidSudoku(char **board, int size, int *col_size)
{
	int rows = size;		// actually both of them will always equal 9
	int cols = col_size[0];

	uint16_t curr_freq;
	uint16_t prev_freq;

	for (int r = 0; r < rows; ++r) {
		curr_freq = 0;
		prev_freq = 0;
		for (int c = 0; c < cols; ++c) {
			int num = ch_code(board[r][c]);

			if (num == 0) continue;

			curr_freq ^= (1 << num);
			if (curr_freq < prev_freq) {
				return false;
			}
			prev_freq = curr_freq;
		}
	}

	for (int c = 0; c < cols; ++c) {
		curr_freq = 0;
		prev_freq = 0;
		for (int r = 0; r < rows; ++r) {
			int num = ch_code(board[r][c]);

			if (num == 0) continue;

			curr_freq ^= (1 << num);
			if (curr_freq < prev_freq) {
				return false;
			}
			prev_freq = curr_freq;
		}
	}

	for (int r = 1; r < rows; r += 3) {
		for (int c = 1; c < cols; c += 3) {
			curr_freq = 0;
			prev_freq = 0;
			for (int d = 0; d < d_size; ++d) {
				int nr = r + dr[d];
				int nc = c + dc[d];

				int num = ch_code(board[nr][nc]);

				if (num == 0) continue;

				curr_freq ^= (1 << num);
				if (curr_freq < prev_freq) {
					return false;
				}
				prev_freq = curr_freq;
			}
		}
	}

	return true;
}
