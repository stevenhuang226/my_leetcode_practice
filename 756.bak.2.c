#include "shdstd.h"

#define CHAR_NUM 26
#define CHAR_OFFSET (-'A')
#define MAX_BOTTOM 6

#define FAIL_SIZE 800

typedef struct {
	int size;
	uint32_t key;
} Fail;

uint8_t find_map[CHAR_NUM][CHAR_NUM][CHAR_NUM];
int find_size[CHAR_NUM][CHAR_NUM];

Fail failed[FAIL_SIZE];
int fail_size;

uint32_t encode_row(const uint8_t *row, int size)
{
	uint32_t key = 0;
	for (int i = 0; i < size; ++i) {
		key = key * CHAR_NUM + row[i];
	}
	return key;
}

int8_t is_failed(const uint8_t *row, int size)
{
	uint32_t key = encode_row(row, size);
	for (int i = 0; i < fail_size; ++i) {
		if (failed[i].size == size && failed[i].key == key) {
			return true;
		}
	}
	return false;
}

void mrk_failed(const uint8_t *row, int size)
{
	uint32_t key = encode_row(row, size);
	failed[fail_size].size = size;
	failed[fail_size].key = key;
	++fail_size;

	return;
}

void append(char b1, char b2, char new)
{
	int b1n = b1 + CHAR_OFFSET;
	int b2n = b2 + CHAR_OFFSET;
	int8_t newn = new + CHAR_OFFSET;
	find_map[b1n][b2n][find_size[b1n][b2n]++] = newn;

	return;
}

int8_t dfs(const uint8_t *bottom, int level, int pos, uint8_t *buffer)
{
	if (level < 0) {
		return true;
	}

	if (pos > level) {
		if (is_failed(buffer, level + 1)) {
			return false;
		}

		uint8_t *new_buffer = malloc(MAX_BOTTOM * sizeof(uint8_t));
		int8_t res = dfs(buffer, level - 1, 0, new_buffer);
		free(new_buffer);

		if (res) {
			return res;
		} else {
			mrk_failed(buffer, level + 1);
			return false;
		}
	}

	int lbn = bottom[pos];
	int rbn = bottom[pos + 1];

	int allow_size = find_size[lbn][rbn];

	for (int i = 0; i < allow_size; ++i) {
		buffer[pos] = find_map[lbn][rbn][i];
		if (dfs(bottom, level, pos + 1, buffer)) {
			return true;
		}
	}
	return false;
}

bool pyramidTransition(char *bottom, char **allowed, int allowed_size)
{
	for (int i = 0; i < CHAR_NUM; ++i) {
		for (int i2 = 0; i2 < CHAR_NUM; ++i2) {
			find_size[i][i2] = 0;
		}
	}
	fail_size = 0;

	for (int i = 0; i < allowed_size; ++i) {
		char c1 = allowed[i][0];
		char c2 = allowed[i][1];
		char ct = allowed[i][2];
		append(c1, c2, ct);
	}

	uint8_t *new_buffer = malloc(MAX_BOTTOM * sizeof(uint8_t));
	int level = strlen(bottom) - 1;

	for (int i = 0; i <= level; ++i) {
		bottom[i] += CHAR_OFFSET;
	}

	int8_t res = dfs(bottom, level - 1, 0, new_buffer);
	free(new_buffer);
	return res;
}
