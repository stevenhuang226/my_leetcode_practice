#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


int i, ii;

int64_t *cost_time_flat;
int64_t **cost_time;

int64_t *brew_time;


int64_t minTime(int *skill, int skillSize, int *mana, int manaSize)
{
	cost_time_flat = malloc(skillSize * manaSize * sizeof(uint64_t));
	cost_time = malloc(manaSize * sizeof(uint64_t *));
	for (i = 0; i < manaSize; i++) {
		cost_time[i] = cost_time_flat + i * skillSize;
	}

	brew_time = malloc(skillSize * sizeof(uint64_t));
	int64_t now_brew;
	int64_t last_brew;

	cost_time[0][0] = skill[0] * mana[0];
	for (i = 1; i < skillSize; i++) {
		cost_time[0][i] = cost_time[0][i-1] + (uint64_t)skill[i] * mana[0];
	}
	int64_t last_offset = 0;
	int64_t offset = 0;

	int last = skillSize - 1;

	for (i = 1; i < manaSize; i++) {
		last_brew = skill[last] * mana[i];
		cost_time[i][last] = cost_time[i-1][last] + last_offset + last_brew;
		for (ii = last - 1; ii >= 0; ii--) {
			now_brew = skill[ii] * mana[i];
			cost_time[i][ii] = cost_time[i][ii+1] - last_brew;

			int64_t top_min = cost_time[i-1][ii] + last_offset + now_brew;
			if (offset < top_min - cost_time[i][ii]) {
				offset = top_min - cost_time[i][ii];
			}

			last_brew = now_brew;
		}

		last_offset = offset;
		offset = 0;
	}


	int64_t result = cost_time[manaSize-1][skillSize-1] + last_offset;
	free(cost_time);
	free(cost_time_flat);
	free(brew_time);

	return result;
}

int main()
{
	int skill[] = {1,5,2,4};
	int skill_size = sizeof(skill)/sizeof(skill[0]);
	int mana[] = {5,1,4,2};
	int mana_size = sizeof(mana)/sizeof(mana[0]);

	int64_t ans = minTime(skill, skill_size, mana, mana_size);

	printf("%" PRId64 "\n", ans);

	return 0;
}
