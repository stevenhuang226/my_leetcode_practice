#include "shdstd.h"

int canCompleteCircuit(int *gas, int gas_size, int *cost, int cost_size)
{
	int total = 0;
	int curr = 0;

	int start = 0;

	for (int i = 0; i < gas_size; ++i) {
		int adj = gas[i] - cost[i];

		total += adj;
		curr += adj;

		if (curr < 0) {
			start = i + 1;
			curr = 0;
		}
	}

	if (total >= 0) {
		return start;
	}

	return -1;
}

