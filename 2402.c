#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define SIZE 100
/* maximum size n will be */

int compare(const void *a, const void *b)
{
	return (*(int **)a)[0] - (*(int **)b)[0];
}

int mostBooked(int n, int **meetings, int meetings_size, int *meeting_col_size)
{
	/*
	 * sort meetings small -> big
	 */
	qsort(meetings, meetings_size, sizeof(int *), compare);
	/*
	 * book_cnt => how many time this room used
	 * room_ttf => room time to free
	 */
	int64_t book_cnt[SIZE] = {0};
	int64_t room_ttf[SIZE] = {0};
	int i, i2;
	for (i = 0; i < meetings_size; ++i) {
		/*
		 * tts => time to start meeting
		 * tte => time to end meeting
		 * min => used for find minimum time room will free
		 * minid => minimum time room's id
		 */
		int64_t tts = meetings[i][0];
		int64_t tte = meetings[i][1];
		int64_t min = INT64_MAX;
		int minid = -1;

		for (i2 = 0; i2 < n; ++i2) {
			if (room_ttf[i2] <= tts) {
				minid = i2;
				break;
			}
			if (room_ttf[i2] < min) {
				min = room_ttf[i2];
				minid = i2;
			}
			/* 1st if
			 * check this room will become free before this meeting start
			 * 2nd if
			 * find the room will become free in less time
			 */
		}
		++book_cnt[minid];
		if (room_ttf[minid] < tts) {
			/*
			 * if this room will be free before meeting start, set time to free to this meeting's time to end
			 */
			room_ttf[minid] = tte;
		} else {
			/*
			 * this meeting will be delay, set time to free to time this meeting will take
			 */
			room_ttf[minid] += tte - tts;
		}
	}


	/*
	 * find maximum number in book_cnt
	 */
	int max = book_cnt[0];
	int max_id = 0;
	for (i = 0; i < n; ++i) {
		if (book_cnt[i] > max) {
			max = book_cnt[i];
			max_id = i;
		}
	}

	return max_id;
}
