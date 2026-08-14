#include "shdstd.h"

int dfs(uint32_t mask, int id, int len)
{
	if (id >= len) {
		return 1;
	}

	int count = 0;
	for (int i = 0; i < len; ++i) {
		if (mask & 1 << i)
			continue;
		if ((i+1) % (id+1) == 0 || (id+1) % (i+1) == 0)
			count += dfs(mask | 1 << i, id+1, len);
	}

	return count;
}

int countArrangement(int n)
{
	return dfs(0, 0, n);
}
