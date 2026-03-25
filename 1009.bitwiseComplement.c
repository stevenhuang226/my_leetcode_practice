#include "shdstd.h"

int bitwiseComplement(int n)
{
	uint32_t num = (uint32_t)n;
	uint32_t mask = 0;

	do {
		mask = (mask << 1) | 1;
		n >>= 1;
	} while (n);

	return (int)(num ^ mask);
}
