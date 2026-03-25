#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

const uint64_t u64m = (uint64_t)1 << 63;

typedef struct {
	uint64_t bits;
	ssize_t length;
} Block;

int cmpBlk(const void *l, const void *r)
{
	uint64_t l_bits = (*(Block *)l).bits;
	uint64_t r_bits = (*(Block *)r).bits;
	if (l_bits > r_bits) {
		return -1;
	} else if (l_bits < r_bits) {
		return 1;
	} else {
		return 0;
	}
}

uint64_t rebuild(uint64_t inside, ssize_t size)
{
	if (size == 0) {
		return 0;
	}

	Block blocks[size];
	int blk_count = 0;

	int balance = 0;

	uint64_t curr = 0;
	ssize_t curr_len = 0;

	for (int i = 0; i < size; ++i) {
		curr = (curr << 1) | (inside & u64m) >> 63;
		++curr_len;
		if (inside & u64m) {
			++balance;
		} else {
			--balance;
		}
		inside <<= 1;

		if (balance != 0) {
			continue;
		}

		uint64_t new = rebuild(curr << 64-curr_len+1, curr_len-2);
		new = u64m | (new >> 1);
		blocks[blk_count].bits = new;
		blocks[blk_count].length = curr_len;
		++blk_count;
		curr = 0;
		curr_len = 0;
	}

	qsort(blocks, blk_count, sizeof(Block), cmpBlk);

	uint64_t res = 0;
	ssize_t res_len = 0;
	for (int i = 0; i < blk_count; ++i) {
		res = res | (blocks[i].bits >> res_len);
		res_len += blocks[i].length;
	}

	return res;
}

char *makeLargestSpecial(char *s)
{
	ssize_t size = strlen(s);

	uint64_t rev_bits = 0;
	for (int i = 0; i < size; ++i) {
		rev_bits = (rev_bits << 1) | (s[i] == '1');
	}
	rev_bits <<= 64 - size;

	uint64_t res_bits = rebuild(rev_bits, size);
	char *res = malloc((size+1) * sizeof(char));

	for (int i = 0; i < size; ++i) {
		res[i] = ((res_bits & u64m) >> 63) + '0';
		res_bits <<= 1;
	}
	res[size] = '\0';

	return res;
}
