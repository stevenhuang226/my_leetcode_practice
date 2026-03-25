#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/*
 * evey user have two state, online or offline.
 * 
 * mentions user by MESSAGE. using id, ALL  or HERE. All mentions all user even it offline. HERE will automatically mention user who is online.
 *
 * All user default to online
 *
 */

int *user_mentions;
int *user_stat;
int size;

int comp(const void *l, const void *r)
{
	char **l_event = *(char ***)l;
	char **r_event = *(char ***)r;
	int lnum = atoi(l_event[1]);
	int rnum = atoi(r_event[1]);
	if (lnum != rnum) {
		return lnum - rnum;
	}

	char ls = l_event[0][0] == 'O';
	char rs = r_event[0][0] == 'O';

	return rs - ls;
}

void make_offline(int timestamp, char *area)
{
	int end_time = timestamp + 60;
	int i;
	if (area[0] == 'A') {
		for (i = 0; i < size; ++i) {
			user_stat[i] = end_time;
		}

		return;
	}

	if (area[0] == 'H') {
		for (i = 0; i < size; ++i) {
			if (timestamp >= user_stat[i]) {
				user_mentions[i] = end_time;
			}
		}

		return;
	}

	i = 0;
	while (area[i] < '0' || area[i] > '9') {
		++i;
	}
	for (;;) {
		int id = 0;
		while (area[i] >= '0' && area[i] <= '9') {
			id *= 10;
			id += area[i] - '0';
			++i;
		}
		user_stat[id] = end_time;

		while (area[i] < '0' || area[i] > '9') {
			if (area[i] == '\0') {
				return;
			}
			++i;
		}
	}
}

void mention_user(int timestamp, char *area)
{
	int i = 0;
	if (area[0] == 'A') {
		for (i = 0; i < size; ++i) {
			++user_mentions[i];
		}

		return;
	}

	if (area[0] == 'H') {
		for (i = 0; i < size; ++i) {
			if (timestamp >= user_stat[i]) {
				++user_mentions[i];
			}
		}

		return;
	}

	i = 0;
	while (area[i] < '0' || area[i] > '9') {
		++i;
	}
	for (;;) {
		int id = 0;
		while (area[i] >= '0' && area[i] <= '9') {
			id *= 10;
			id += area[i] - '0';
			++i;
		}
		++user_mentions[id];
		while (area[i] < '0' || area[i] > '9') {
			if (area[i] == '\0') {
				return;
			}
			++i;
		}
	}
}

int *countMentions(int user_numbers, char ***events, int event_size, int *event_col_size, int *return_size)
{
	size = user_numbers;
	(*return_size) = size;

	qsort(events, event_size, sizeof(char ***), comp);

	user_mentions = calloc(1, size * sizeof(int));
	user_stat = calloc(1, size * sizeof(int));

	int i, i2;
	for (i = 0; i < event_size; ++i) {
		char *code = events[i][0];

		i2 = 0; char c;
		int timestamp = atoi(events[i][1]);
		char *area = events[i][2];

		if (code[0] == 'O') {
			make_offline(timestamp, area);
			continue;
		}

		if (code[0] == 'M') {
			mention_user(timestamp, area);
		}
	}

	free(user_stat);
	return user_mentions;
}

