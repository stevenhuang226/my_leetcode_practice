#include "shdstd.h"

typedef enum {
	LEFT,
	RIGHT,
} driection_t;

typedef struct {
	int position;
	int health;
	driection_t driection;
	uint32_t id;
} Robot;

int cmpRobot(const void *l, const void *r)
{
	return (*(Robot *)l).position - (*(Robot *)r).position;
}

int cmpRes(const void *l, const void *r)
{
	return (*(Robot *)l).id - (*(Robot *)r).id;
}

int *survivedRobotsHealths(int *position, int position_size,
	int *healths, int healths_size,
	char *driections,
	int *ret_size) {

	int width = position_size;
	Robot *robots = malloc(width * sizeof(Robot));

	for (int i = 0; i < width; ++i) {
		robots[i].health = healths[i];
		robots[i].position = position[i];
		if (driections[i] == 'R') {
			robots[i].driection = RIGHT;
		} else {
			robots[i].driection = LEFT;
		}
		robots[i].id = (uint32_t)i;
	}

	qsort(robots, width, sizeof(Robot), cmpRobot);

	Robot *stack = malloc(width * sizeof(Robot));
	int go_right_size = -1;
	int go_left_size = -1;

	Robot *res_tmp = malloc(width * sizeof(Robot));
	int result_count = 0;

	for (int i = width - 1; i >= 0; --i) {
		int curr_health = robots[i].health;
		int curr_id = robots[i].id;
		driection_t curr_driection = robots[i].driection;

		if (curr_driection == LEFT) {
			++go_left_size;
			stack[go_left_size].health = curr_health;
			stack[go_left_size].id = curr_id;
			continue;
		}

		while (go_left_size >= 0 &&
			stack[go_left_size].health < curr_health) {
			--curr_health;
			--go_left_size;
		}

		if (go_left_size < 0) continue;

		if (stack[go_left_size].health == curr_health) {
			--go_left_size;
			continue;
		}
		if (curr_health > 0) {
			--stack[go_left_size].health;
		}
	}

	for (int i = 0; i <= go_left_size; ++i) {
		res_tmp[result_count].id = stack[i].id;
		res_tmp[result_count].health = stack[i].health;
		++result_count;
	}

	for (int i = 0; i < width; ++i) {
		int curr_health = robots[i].health;
		int curr_id = robots[i].id;
		driection_t curr_driection = robots[i].driection;

		if (curr_driection == RIGHT) {
			++go_right_size;
			stack[go_right_size].health = curr_health;
			stack[go_right_size].id = curr_id;
			continue;
		}

		while (go_right_size >= 0 &&
			stack[go_right_size].health < curr_health) {
			--curr_health;
			--go_right_size;
		}

		if (go_right_size < 0) continue;

		if (stack[go_right_size].health == curr_health) {
			--go_right_size;
			continue;
		}
		if (curr_health > 0){
			--stack[go_right_size].health;
		}
	}

	for (int i = 0; i <= go_right_size; ++i) {
		res_tmp[result_count].id = stack[i].id;
		res_tmp[result_count].health = stack[i].health;
		++result_count;
	}

	free(stack);
	free(robots);

	qsort(res_tmp, result_count, sizeof(Robot), cmpRes);

	int *result = malloc(result_count * sizeof(int));
	for (int i = 0; i < result_count; ++i) {
		result[i] = res_tmp[i].health;
	}
	free(res_tmp);

	*ret_size = result_count;

	return result;
}
