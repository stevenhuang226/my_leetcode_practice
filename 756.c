#include "shdstd.h"

#define CHAR_NUM 26
#define CHAR_OFFSET (-('A'))

#define MAX_BOTTOM 6

#define MAX_FIND 300
#define MAX_CHAR_PRE_FIND 30
#define MAX_FAIL 8000

#define HASH(x, size) ((x) % (size))

uint8_t triangle[MAX_BOTTOM][MAX_BOTTOM];

typedef struct {
	uint32_t key;
	int size;
	uint8_t c[MAX_CHAR_PRE_FIND];
} Top;


Top find_top[MAX_FIND];
uint32_t find_top_def_key;

typedef struct {
	int len;
	uint32_t key;
} Fail;

Fail failed[MAX_FAIL];
uint32_t fail_def_key;

void top_find_insert(uint8_t b1, uint8_t b2, uint8_t c)
{
	int size = MAX_FIND;
	uint32_t def_key = find_top_def_key;
	uint32_t key = (b1 * CHAR_NUM) + b2;
	uint32_t hash = HASH(key, size);

	while (find_top[hash].key != def_key) {
		if (find_top[hash].key == key) {
			find_top[hash].c[find_top[hash].size++] = c;
			return;
		}
		hash = HASH(hash + 1, size);
	}

	find_top[hash].key = key;
	find_top[hash].c[0] = c;
	find_top[hash].size = 1;

	return;
}

Top *top_find_search(uint8_t b1, uint8_t b2)
{
	int size = MAX_FIND;
	uint32_t def_key = find_top_def_key;
	uint32_t key = (b1 * CHAR_NUM) + b2;

	uint32_t hash = HASH(key, size);

	while (find_top[hash].key != def_key) {
		if (find_top[hash].key == key) {
			return &(find_top[hash]);
		}

		hash = HASH(hash + 1, size);
	}

	return NULL;
}

uint32_t encode_row(const uint8_t *row, int size)
{
	uint32_t key = 0;
	for (int i = 0; i < size; ++i) {
		key = key * CHAR_NUM + row[i];
	}
	return key;
}

void isfail_insert(const uint8_t *row, int len)
{
	uint32_t key = encode_row(row, len);

	int size = MAX_FAIL;
	uint32_t def_key = fail_def_key;
	uint32_t hash = HASH(key, size);

	while (failed[hash].key != def_key) {
		if (failed[hash].key == key && failed[hash].len == len) {
			return;
		}
		hash = HASH(hash + 1, size);
	}

	failed[hash].key = key;
	failed[hash].len = len;

	return;
}

int8_t isfail_find(const uint8_t *row, int len)
{
	uint32_t key = encode_row(row, len);

	int size = MAX_FAIL;
	uint32_t def_key = fail_def_key;
	uint32_t hash = HASH(key, size);

	while (failed[hash].key != def_key) {
		if (failed[hash].key == key && failed[hash].len == len) {
			return true;
		}
		hash = HASH(hash + 1, size);
	}

	return false;
}

void append(char c1, char c2, char ct)
{
	uint8_t char_offset = CHAR_OFFSET;
	uint8_t n1 = c1 + char_offset;
	uint8_t n2 = c2 + char_offset;
	uint8_t nt = ct + char_offset;

	top_find_insert(n1, n2, nt);
	return;
}

int8_t dfs(int level, int pos) // level: the level this dfs should build. pos: position this dfs should build.
{
	if (level < 0) {
		return true;
	}

	uint8_t *curr_row = triangle[level];

	if (pos > level) {
		if (isfail_find(curr_row, level + 1)) {
			return false;
		}

		int8_t res = dfs(level - 1, 0);

		if (res) {
			return true;
		} else {
			isfail_insert(curr_row, level + 1);
			return false;
		}
	}

	uint8_t *bottom = triangle[level + 1];

	int left_num = bottom[pos];
	int right_num = bottom[pos + 1];

	Top *top = top_find_search(left_num, right_num);

	if (top == NULL) {
		return false;
	}

	for (int i = 0; i < top->size; ++i) {
		curr_row[pos] = top->c[i];
		if (dfs(level, pos + 1)) {
			return true;
		}
	}
	return false;
}

bool pyramidTransition(char *bottom, char **allowed, int allowed_size)
{
	find_top_def_key = UINT32_MAX;
	for (int i = 0; i < MAX_FIND; ++i) {
		find_top[i].size = 0;
		find_top[i].key = find_top_def_key;
	}

	fail_def_key = UINT32_MAX;
	for (int i = 0; i < MAX_FAIL; ++i) {
		failed[i].key = fail_def_key;
		failed[i].len = 0;
	}

	for (int i = 0; i < allowed_size; ++i) {
		append(allowed[i][0], allowed[i][1], allowed[i][2]);
	}

	int level = strlen(bottom) - 1;

	for (int i = 0; i <= level; ++i) {
		triangle[level][i] = bottom[i] + CHAR_OFFSET;
	}

	int8_t res = dfs(level - 1, 0);

	return res;
}
