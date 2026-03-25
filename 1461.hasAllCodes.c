#include "shdstd.h"

typedef struct {
	int8_t *mrk;
	uint32_t rm_diff;
	uint32_t capacity;
} Codes;

Codes *create_codes(uint32_t capacity)
{
	Codes *codes = malloc(sizeof(Codes));
	codes->mrk = malloc(capacity * sizeof(int8_t));
	memset(codes->mrk, false, capacity * sizeof(int8_t));
	codes->rm_diff = capacity;
	codes->capacity = capacity;

	return codes;
}

uint32_t encode(char *s, int len)
{
	uint32_t res = 0;
	for (int i = 0; i < len; ++i) {
		res = (res << 1) | (s[i] - '0');
	}
	return res;
}

static inline int32_t codes_mark(Codes *codes, uint32_t key)
{
	if (codes->mrk[key] == true) {
		return codes->rm_diff;
	}

	codes->mrk[key] = true;
	--codes->rm_diff;

	return codes->rm_diff;
}

void codes_clean(Codes *codes)
{
	free(codes->mrk);
	free(codes);
}

bool hasAllCodes(char *s, int k)
{
	ssize_t len = strlen(s);

	if (len <= k) {
		return false;
	}

	uint32_t capacity = 0;
	for (int i = 0; i < k; ++i) {
		capacity = (capacity << 1) | 0x01;
	}
	++capacity;

	uint32_t mask = ~(0x01 << k);

	Codes *codes = create_codes(capacity);

	uint32_t key = encode(s, k - 1);
	for (int i = k - 1; i < len; ++i) {
		key = ((key << 1) | s[i] - '0') & mask;

		if (codes_mark(codes, key) == 0) {
			codes_clean(codes);
			return true;
		}
	}

	codes_clean(codes);
	return false;
}
