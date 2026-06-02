#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int earliestFinishTime(int *land_start, int land_start_size,
		int *land_duration, int land_duration_size,
		int *water_start, int water_start_size,
		int *water_duration, int water_duration_size)
{
	int land_size = land_start_size;
	int water_size = water_start_size;

	int best = INT32_MAX;

	int earliest_land_end = INT32_MAX;
	for (int i = 0; i < land_size; ++i) {
		int end = land_start[i] + land_duration[i];
		earliest_land_end = MIN(earliest_land_end, end);
	}

	for (int i = 0; i < water_size; ++i) {
		int duration = water_duration[i];
		int start = MAX(water_start[i], earliest_land_end);
		best = MIN(best, start + duration);
	}

	int earliest_water_end = INT32_MAX;
	for (int i = 0; i < water_size; ++i) {
		int end = water_start[i] + water_duration[i];
		earliest_water_end = MIN(earliest_water_end, end);
	}

	for (int i = 0; i < land_size; ++i) {
		int duration = land_duration[i];
		int start = MAX(land_start[i], earliest_water_end);
		best = MIN(best, start + duration);
	}

	return best;
}
